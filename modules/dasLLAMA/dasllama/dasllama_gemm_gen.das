options gen2
options indenting = 4

module dasllama_gemm_gen shared private

require llvm/daslib/llvm_boost
require llvm/daslib/llvm_jit_code
require llvm/daslib/llvm_jit_common
require daslib/ast_boost
require dasllama/dasllama_gemm_schema

// The perm-parameterized Q8 GEMM tile generator (gemm_generator_plan.md part 3, promoted from
// the M2 hand perm): emits the mr-row x 4-token register tile as LLVM IR — the loop nest,
// interleaved loads, accumulators, scale folds and stores are generic IR (proven to lower
// hand-shaped on arm64, M1 experiment); only the dot primitive is per-ISA. Layout is
// repack=grp<mr> (f32 scales, strides derived from q8q8_repack_type so kernel and repack
// cannot desync), acc=i32reg, scale=block_fold, load=bcast_x. Knobs read from the [llvm_code]
// annotation args (stamped by the [tune] macro; defaults = the M2 perm, kstep=2 nrsplit=4):
//   kstep   blocks per main-loop iteration (1|2|4); the remainder is a chain of conditional
//           single blocks, so kstep=2 reproduces the M2 CFG exactly
//   nrsplit tokens per accumulator slice (4|2); the 4-token call contract is fixed — nrsplit=2
//           runs the k-loop twice over half the tokens (halves live accumulators)
//   mr      rows per interleave group; must be a multiple of the dot width's rows-per-vector
//           (4 on NEON q-regs, 8 on ymm, 16 on zmm) inside the vreg budget; the layout
//           companion (q8q8_layout below) reports the same mr to the runtime repack
//   gkstep  the GEMV companion's blocks per K-iteration (1|2|4) — fresh int accumulators per
//           block give the single-token loop the independent dot chains a serial laneq
//           chain lacks; the tile ignores it (its K knob is kstep)
//   dot     the per-ISA dot primitive: "sdot" (NEON indexed sdot — the arm64 leg),
//           "maddubs" (x64 VPMADDUBSW+VPMADDWD sign-trick pair), "vpdpbusd" (x64 VNNI,
//           sign trick, one dot op), "vpdpbssd" (x64 AVX-VNNI-INT8, native s8·s8),
//           "smmla" (NEON i8mm 2×2 MMA, slice J — implies the kg8 plane; tile only, the
//           gemv/mx4 companions ride the sdot lattice), "amx_int8" (x64 TMUL TDPBSSD
//           macro-tile over the plain grp16/kg4 plane, slice I — tile only; nrsplit ≙
//           tiles per macro side, kstep pinned 1; the gemv/mx4 companions ride the
//           sign-trick busd512 lattice)
//   width   vector width in bits: 128 (NEON, implied by sdot), 256 (ymm), 512 (zmm)
//   bias    128 = bias128 (vpdpbusd only): the repack bakes w^0x80 into the grp<mr> plane,
//           dots run plain vpdpbusd(acc, w_biased, x) — no abs/sign ops — and the exactness
//           correction −128·Σx(block) becomes the accumulator init (slice H)
// Illegal perms decline (return false) and the reference body compiles instead — the decline
// path is the fallback tier; every companion declines in LOCKSTEP (the one shared
// perm_declines), so repacks and kernels fall back to the grp4 reference family together.
// Runs in the llvm-jit context; wired via llvm_user_modules.das. The stubs it generates for
// are dasllama/dasllama_math_gen.das::q8q8_tile_gen, ::q8q8_layout_gen, ::q8q8_wbias_gen,
// ::q8q8_kgroup_gen, ::q8q8_tokstep_gen, ::q8q8_gemv_gen, ::mx4q8_gemv_gen,
// ::q8q8_family_live (the witness), the wscale_f16 twins ::q8q8_tile_s16_gen /
// ::q8q8_gemv_s16_gen (same perm, same fold order — only the scale-fold load widens f16), and
// the K-quant rows cores ::k4q8_gemv_gen / ::k5q8_gemv_gen / ::k6q8_gemv_gen (unsigned-quant
// superblock GEMVs over the grp<mr> kq planes — kq stage 4).

// dot-primitive kinds (TilePerm.dotPrim, parsed once into TileEmit.dotKind)
let DOT_SDOT = 0
let DOT_MADDUBS = 1
let DOT_VPDPBUSD = 2
let DOT_VPDPBSSD = 3
let DOT_SMMLA = 4
let DOT_AMX = 5

def private dot_kind(prim : string) : int {
    if (prim == "maddubs") return DOT_MADDUBS
    if (prim == "vpdpbusd") return DOT_VPDPBUSD
    if (prim == "vpdpbssd") return DOT_VPDPBSSD
    if (prim == "smmla") return DOT_SMMLA
    if (prim == "amx_int8") return DOT_AMX
    return DOT_SDOT
}

// under an amx stamp the VECTOR companions (gemv/mx4 — the tile is the only TMUL slot) ride
// the busd lattice over the same grp16/kg4 plane: plain sign-trick for the unbiased rows
// (design fork (a), gemm_generator_plan.md slice I), the BIASED busd lattice for bias=128
// rows (slice K I3 — bias flows through, killing the fork's gemv penalty). Everything
// downstream then treats the perm exactly like the matching vpdpbusd row.
def private companion_perm(p : TilePerm) : TilePerm {
    var cp = p
    if (cp.dotPrim == "amx_int8") { cp.dotPrim = "vpdpbusd" }
    return cp
}

// the perm's plane kgroup (k-bytes per row per interleave group): smmla reads row-pair × 8-k
// MMA operands straight off a kg8 plane ([kg8][r][8b], slice J); every vector-dot perm reads
// the dword-group kg4 plane. Feeds q8q8_repack_type so kernel strides, the kgroup companion
// and the runtime repack derive from the one schema.
def private kgroup_of(p : TilePerm) : int => p.dotPrim == "smmla" ? 8 : 4

// the perm vector both generators read off the [llvm_code] annotation args
struct private TilePerm {
    kstep : int = 2
    nrsplit : int = 4
    mr : int = GEMM_REFERENCE_MR
    gkstep : int = 1
    dotPrim : string = "sdot"
    width : int = 128
    bias : int = 0        // 128 = bias128: grp<mr> bytes baked as w^0x80, plain vpdpbusd dots
    pipe : int = 0        // 1 = software-pipelined amx fold (slice K I4): double-buffered C
                          // scratch, block i−1's scale fold interleaved with block i's TMUL ops
    latch : int = 0       // 1 = raw immediate-tmm amx ops (slice K I1): no per-call
                          // ldtilecfg/tilerelease — the cfg companion owns per-chunk config
}

def private parse_perm(gc : LlvmCodeCtx) : TilePerm {
    var p = TilePerm()
    let kv = find_arg(gc.ann.arguments, "kstep")
    if (kv is tInt) { p.kstep = kv as tInt }
    let nv = find_arg(gc.ann.arguments, "nrsplit")
    if (nv is tInt) { p.nrsplit = nv as tInt }
    let mv = find_arg(gc.ann.arguments, "mr")
    if (mv is tInt) { p.mr = mv as tInt }
    let gv = find_arg(gc.ann.arguments, "gkstep")
    if (gv is tInt) { p.gkstep = gv as tInt }
    let dv = find_arg(gc.ann.arguments, "dot")
    if (dv is tString) { p.dotPrim = dv as tString }
    let wv = find_arg(gc.ann.arguments, "width")
    if (wv is tInt) { p.width = wv as tInt }
    let bv = find_arg(gc.ann.arguments, "bias")
    if (bv is tInt) { p.bias = bv as tInt }
    let pv = find_arg(gc.ann.arguments, "pipe")
    if (pv is tInt) { p.pipe = pv as tInt }
    let lv = find_arg(gc.ann.arguments, "latch")
    if (lv is tInt) { p.latch = lv as tInt }
    return p
}

// the ONE decline predicate all four generators share — the tile and its companions must fall
// back together on every rail, or repack and kernel desync (the two-function-stamp contract).
// Rails in order: knob validity, schema, then the per-ISA leg: target arch, width, tier truth
// (cpuid on host targets, DAS_JIT_X64_FORCE_FEATURES-only on cross triples — the emission
// rail), row/vector geometry, vreg budget, dot machinery availability (belt).
def private perm_declines(var gc : LlvmCodeCtx; p : TilePerm) : bool {
    if (p.dotPrim == "amx_int8") {
        // the TMUL leg (slice I): batch tile = 2×2 TDPBSSD macro over the grp16/kg4 plane
        // (byte-for-byte the TDPBSSD B-tile layout — zero new repack). kstep pinned 1 (Q8's
        // per-block scale boundary — i32 cannot accumulate across blocks); nrsplit ≙ tiles
        // per macro side (1 = the probe shape, 2 = the 8-tmm production macro). bias=0 rows
        // run s8·s8 TDPBSSD over the unbiased plane (companions forced to the sign-trick
        // busd512 lattice — companion_perm); bias=128 rows (slice K I3) run TDPBSUD (signed
        // activations × unsigned w^0x80 plane) with the −128·Σx bsum folded in the scale
        // stage, and their companions ride the BIASED busd512 lattice — one plane, both
        // slots optimal. The runtime enable is Linux arch_prctl, so a non-linux target
        // declines the whole family.
        if ((p.kstep != 1)
            || (p.nrsplit != 1 && p.nrsplit != 2)
            || (p.gkstep != 1 && p.gkstep != 2 && p.gkstep != 4)
            || (p.mr != 16) || (p.width != 512)
            || (p.bias != 0 && p.bias != 128)
            || (p.pipe != 0 && p.pipe != 1)
            || (p.latch != 0 && p.latch != 1)
            || (!g_target_is_x64) || (!g_target_x64_amx)
            || (!g_target_x64_avx512vnni)     // the companions' busd512 lattice + zmm fold
            || (!g_target_os_linux)) return true
        let rt = q8q8_repack_type(p.mr, p.bias, kgroup_of(p))
        if (rt.interleave != p.mr || !rt.f32_scales) return true
        // tile + companion machinery availability (belt — shared, so the family stays lockstep)
        let mod = LLVMGetGlobalParent(gc.impl)
        var noTypes : array<LLVMOpaqueType?>
        for (nm in fixed_array("llvm.x86.tileloadd64.internal", "llvm.x86.tdpbssd.internal",
                               "llvm.x86.tilestored64.internal", "llvm.x86.tilezero.internal",
                               "llvm.x86.avx512.vpdpbusd.512", "llvm.x86.avx512.pshuf.b.512")) {
            let id = LLVMLookupIntrinsicID(nm)
            if (LLVMGetIntrinsicDeclaration(mod, id, noTypes) == null) return true
        }
        if (p.latch != 0) {
            // the raw immediate-tmm leg (slice K I1) + the cfg companion's LDTILECFG
            for (nm in fixed_array("llvm.x86.tileloadd64", "llvm.x86.tdpbssd", "llvm.x86.tdpbsud",
                                   "llvm.x86.tilestored64", "llvm.x86.tilezero", "llvm.x86.ldtilecfg")) {
                let id = LLVMLookupIntrinsicID(nm)
                if (LLVMGetIntrinsicDeclaration(mod, id, noTypes) == null) return true
            }
        }
        if (p.bias != 0 && LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.tdpbsud.internal"), noTypes) == null) {
            return true       // the biased leg's signed×unsigned TMUL dot
        }
        var v64i8 = LLVMVectorType(gc.jit.types.t_int8, 64u)
        let absId = LLVMLookupIntrinsicID("llvm.abs")
        var absTypes <- [v64i8]
        return LLVMGetIntrinsicDeclaration(mod, absId, absTypes) == null
    }
    // bias128 is a vpdpbusd-only knob: u8 = w+128 feeds the dot's unsigned side exactly;
    // maddubs saturates word pair-sums at biased magnitudes, bssd/sdot are native s8·s8.
    // pipe/latch are TMUL-only knobs — vector dots have no tile spill or tile config
    if ((p.kstep != 1 && p.kstep != 2 && p.kstep != 4)
        || (p.nrsplit != 2 && p.nrsplit != 4)
        || (p.gkstep != 1 && p.gkstep != 2 && p.gkstep != 4)
        || (p.mr < 4) || (p.pipe != 0) || (p.latch != 0)
        || (p.bias != 0 && (p.bias != 128 || p.dotPrim != "vpdpbusd"))) return true
    let rt = q8q8_repack_type(p.mr, p.bias, kgroup_of(p))
    if (rt.interleave != p.mr || !rt.f32_scales) return true
    if (p.dotPrim == "smmla") {
        // the i8mm MMA leg (slice J): NEON widths, row-quad geometry (the fold transpose and
        // the gemv kg8→kg4 fixup both work in quads), s8·s8 native (bias128 already declined
        // above), the SAME q-reg budget space as sdot (w 2mr + acc nrsplit·mr/4 + act
        // 2·nrsplit + 2 — MMA patches and A pairs land on the same counts), and the i8mm tier
        // flag (host LLVM features / DAS_JIT_ARM64_FORCE_FEATURES — M1 is dotprod-only)
        if ((!g_target_is_aarch64) || (!g_target_arm64_i8mm) || (p.width != 128)
            || (p.mr % 4 != 0)
            || (2 * p.mr + p.nrsplit * p.mr / 4 + 2 * p.nrsplit + 2 > 32)) return true
        let mod = LLVMGetGlobalParent(gc.impl)
        var v16i8 = LLVMVectorType(gc.jit.types.t_int8, 16u)
        let mmId = LLVMLookupIntrinsicID("llvm.aarch64.neon.smmla")
        var mmTypes <- [gc.jit.types->LLVMInt4Type(), v16i8]
        if (LLVMGetIntrinsicDeclaration(mod, mmId, mmTypes) == null) return true
        // the gemv/mx4 companions ride the sdot lattice over the kg8 plane — both rails
        let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
        var declTypes <- [gc.jit.types->LLVMInt4Type(), v16i8]
        if (LLVMGetIntrinsicDeclaration(mod, id, declTypes) == null) return true
        let tblId = LLVMLookupIntrinsicID("llvm.aarch64.neon.tbl1")
        var tblTypes <- [v16i8]
        return LLVMGetIntrinsicDeclaration(mod, tblId, tblTypes) == null
    }
    if (p.dotPrim == "sdot") {
        // the NEON leg (the M2 shape): 128-bit q-regs, 4-row sdot lane structure, q-reg
        // budget (weights 2*mr + acc nrsplit*mr/4 + activations 2*nrsplit + 2 scratch)
        if ((!g_target_is_aarch64) || (p.width != 128)
            || (p.mr % 4 != 0)
            || (2 * p.mr + p.nrsplit * p.mr / 4 + 2 * p.nrsplit + 2 > 32)) return true
        let mod = LLVMGetGlobalParent(gc.impl)
        var v16i8 = LLVMVectorType(gc.jit.types.t_int8, 16u)
        let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
        var declTypes <- [gc.jit.types->LLVMInt4Type(), v16i8]
        if (LLVMGetIntrinsicDeclaration(mod, id, declTypes) == null) return true
        // the mx4 companion's dequant primitive — part of the shared predicate so the mx4
        // gemv can never fall to its grp4 reference body while the layout stamps another mr
        let tblId = LLVMLookupIntrinsicID("llvm.aarch64.neon.tbl1")
        var tblTypes <- [v16i8]
        return LLVMGetIntrinsicDeclaration(mod, tblId, tblTypes) == null
    }
    // the x64 legs. The mx4 companion's pshufb dequant is implied by the tiers below
    // (avx2 carries pshuf.b ymm, avx512bw carries pshuf.b.512), so no separate rail.
    if ((p.dotPrim != "maddubs" && p.dotPrim != "vpdpbusd" && p.dotPrim != "vpdpbssd")
        || (!g_target_is_x64)
        || (p.width != 256 && p.width != 512)
        || (p.dotPrim == "vpdpbssd" && p.width != 256)) return true    // 512-bit bssd is AVX10 — unproven
    if (p.width == 256) {
        if ((p.dotPrim == "maddubs" && !g_target_x64_avx2)
            || (p.dotPrim == "vpdpbusd" && !g_target_x64_vnni256)
            || (p.dotPrim == "vpdpbssd" && !g_target_x64_vnniint8)) return true
    } else {
        if ((p.dotPrim == "maddubs" && !g_target_x64_avx512bw)
            || (p.dotPrim == "vpdpbusd" && !g_target_x64_avx512vnni)) return true
    }
    let rv = p.width / 32                         // rows per vector = i32 acc lanes
    if (p.mr % rv != 0) return true
    let vq = p.mr / rv
    if ((vq > 2)                                  // the weight bank is 8 dword-groups x vq
        || (p.nrsplit * vq > 8)) return true      // accumulator bank (emit_slice phi arrays)
    // vreg budget: float + int acc tiles + x splat/sign scratch + weight/|weight| in flight
    return 2 * p.nrsplit * vq + 6 > (p.width == 512 ? 32 : 16)
}

// emission context threaded through the helpers: builder/types + the per-function value handles
struct private TileEmit {
    builder : LLVMOpaqueBuilder?
    types : PrimitiveTypes?
    v16i8 : LLVMOpaqueType?              // one 16-byte activation chunk (fixed at any width)
    v4i32 : LLVMOpaqueType?              // the chunk's dword view (lane-splat source)
    vwi8 : LLVMOpaqueType?               // weight vector at the perm's width (v16i8/v32i8/v64i8)
    vni32 : LLVMOpaqueType?              // int accumulator (v4i32/v8i32/v16i32)
    vnf32 : LLVMOpaqueType?              // float accumulator (v4f32/v8f32/v16f32)
    width : int                          // vector bits (128 NEON / 256 ymm / 512 zmm)
    rv : int                             // rows per weight vector = i32 acc lanes
    dotKind : int                        // DOT_*
    sdot_decl : LLVMOpaqueValue?         // NEON
    sdot_ty : LLVMOpaqueType?
    abs_decl : LLVMOpaqueValue?          // x64 sign trick: llvm.abs (VPABSB)
    abs_ty : LLVMOpaqueType?
    psign_decl : LLVMOpaqueValue?        // x64 width-256 sign apply (VPSIGNB)
    psign_ty : LLVMOpaqueType?
    madd_decl : LLVMOpaqueValue?         // x64 maddubs pair (VPMADDUBSW)
    madd_ty : LLVMOpaqueType?
    maddwd_decl : LLVMOpaqueValue?       // (VPMADDWD)
    maddwd_ty : LLVMOpaqueType?
    dp_decl : LLVMOpaqueValue?           // x64 one-op dot (VPDPBUSD / VPDPBSSD)
    dp_ty : LLVMOpaqueType?
    interleave : int                     // rows per group (q8q8_repack_type(mr).interleave)
    rq : int                             // weight VECTORS per group (mr / rv; NEON: row quads)
    kgroup : int                         // k-bytes per row per group (4; 8 = the smmla plane)
    bias : int                           // 128 = bias128 dots (weight plane is w^0x80); 0 = sign trick
    smmla_decl : LLVMOpaqueValue?        // NEON i8mm 2x2 MMA (the smmla tile lattice)
    smmla_ty : LLVMOpaqueType?
    reduce_decl : LLVMOpaqueValue?       // llvm.vector.reduce.add at vni32 (the gemv inline bsum)
    reduce_ty : LLVMOpaqueType?
    wg : LLVMOpaqueValue?                // interleaved mr-row weight group base (mx4: nibble plane)
    sg : LLVMOpaqueValue?                // group scales (float x interleave per block; mx4: E8M0 bytes)
    x : LLVMOpaqueValue? [4]             // per-token activation base pointers
    xs : LLVMOpaqueValue? [4]            // per-token activation scale base pointers
    xbs : LLVMOpaqueValue? [4]           // per-token bsum bases (−128·Σx i32 per block) — the tile's
                                         // bias128 correction plane; null = compute inline (gemv)
    mx4 : bool                           // block emitter: mx4 LUT-dequant instead of Q8 loads
    kq : int                             // 4/5/6 = K-quant superblock emitter (0 = not kq): the
                                         // block unit is a 256-weight superblock over the grp<mr>
                                         // kq planes; dots run unsigned-q (kq_dot_lane)
    t_amx : LLVMOpaqueType?              // x86_amx — virtual tile values (the TMUL tile, slice I)
    tload_decl : LLVMOpaqueValue?        // llvm.x86.tileloadd64.internal (latch: raw tileloadd64)
    tload_ty : LLVMOpaqueType?
    tdp_decl : LLVMOpaqueValue?          // llvm.x86.tdpbssd.internal (latch: raw tdpbssd)
    tdp_ty : LLVMOpaqueType?
    tstore_decl : LLVMOpaqueValue?       // llvm.x86.tilestored64.internal (latch: raw tilestored64)
    tstore_ty : LLVMOpaqueType?
    tzero_decl : LLVMOpaqueValue?        // llvm.x86.tilezero.internal (latch: raw tilezero)
    tzero_ty : LLVMOpaqueType?
    rawTiles : bool                      // latch=1: immediate-tmm ops, void results, no backend
                                         // ldtilecfg/tilerelease (the cfg companion owns config)
    tbl_decl : LLVMOpaqueValue?          // llvm.aarch64.neon.tbl1 (NEON mx4)
    tbl_ty : LLVMOpaqueType?
    pshuf_decl : LLVMOpaqueValue?        // llvm.x86.avx2.pshuf.b / avx512.pshuf.b.512 (x64 mx4)
    pshuf_ty : LLVMOpaqueType?
    lut : LLVMOpaqueValue?               // the doubled-e2m1 LUT: v16i8 on NEON; broadcast per
                                         // 16-byte lane to vwi8 on x64 (pshufb is per-lane)
    sgF16 : bool                         // the wscale_f16 rail: the group-scale plane is raw
                                         // binary16 halfwords — scale loads widen via fpext
    vni16 : LLVMOpaqueType?              // <rv x i16> — the halfword scale-load type (sgF16)
    vnf16 : LLVMOpaqueType?              // <rv x half> — its bitcast view, the fpext source
}

// one indexed sdot: acc += w · (dword-group `lane` of x, splatted). The bitcast-to-v4i32 lane
// shuffle is what the AArch64 backend folds into the `sdot v,v,v[lane]` encoding (M1 experiment:
// the generic partial.reduce form leaves a dup per sdot instead).
def private sdot_lane(var te : TileEmit; var acc, wv, xv : LLVMOpaqueValue?; lane : int) : LLVMOpaqueValue? {
    var xi32 = LLVMBuildBitCast(te.builder, xv, te.v4i32, "")
    var xspl = LLVMBuildShuffleVector(te.builder, te.types, xi32, xi32, [lane, lane, lane, lane], "xlane")
    var xb = LLVMBuildBitCast(te.builder, xspl, te.v16i8, "")
    var args <- [acc, wv, xb]
    return LLVMBuildCall2(te.builder, te.sdot_ty, te.sdot_decl, args, "sdot")
}

// all-ones v(width/16)i16 — the VPMADDWD pair-sum operand of the maddubs chain
def private ones_i16(te : TileEmit) : LLVMOpaqueValue? {
    var elems <- [for (_i in range(te.width / 16)); LLVMConstInt(te.types.t_int16, 1ul, 0)]
    return LLVMConstVector(array_data_ptr(elems), uint(te.width / 16))
}

// one lane-dot: acc += w · (dword-group `lane` of the 16-byte x chunk, splatted across the acc
// lanes). NEON: the indexed sdot above. x64: a generic lane-splat shuffle (GVN folds the
// byte-identical re-emission across row vectors, like the NEON form), then the per-ISA chain —
// vpdpbssd is native s8·s8; vpdpbusd/maddubs run the exact sign-trick chain of the proven
// dot32/dot64 emitters (llvm_jit_intrin): uwv = |w| hoisted per weight vector by the caller,
// sx = sign(w) applied to x per dot (VPSIGNB at 256; no 512-bit VPSIGNB, so compare+negate+
// select there — w==0 lanes keep x, but they multiply |w| = 0 anyway). Same exactness
// precondition as dot32: x values in [-127, 127] (the Q8 quantizer's range); w may be -128.
def private dot_lane(var te : TileEmit; var acc, wv, uwv, xv : LLVMOpaqueValue?; lane : int) : LLVMOpaqueValue? {
    if (te.dotKind == DOT_SDOT || te.dotKind == DOT_SMMLA) {
        // SMMLA reaches here only off the MMA lattice's fallbacks — the gemv single-token
        // slice and the mx4 companion ride the sdot lattice (i8mm implies dotprod)
        return sdot_lane(te, acc, wv, xv, lane)
    }
    let b = te.builder
    var xi32 = LLVMBuildBitCast(b, xv, te.v4i32, "")
    let mask <- [for (_i in range(te.rv)); lane]
    var xspl = LLVMBuildShuffleVector(b, te.types, xi32, xi32, mask, "xlane")
    var xb = LLVMBuildBitCast(b, xspl, te.vwi8, "")
    if (te.dotKind == DOT_VPDPBSSD) {
        var dargs <- [acc, wv, xb]
        return LLVMBuildCall2(b, te.dp_ty, te.dp_decl, dargs, "dot")
    }
    if (te.bias != 0) {
        // bias128: the plane bytes ARE the unsigned side (w+128), x rides signed as-is —
        // no |w|, no sign apply; the −128·Σx correction is the accumulator's init value
        var dargs <- [acc, wv, xb]
        return LLVMBuildCall2(b, te.dp_ty, te.dp_decl, dargs, "dot")
    }
    var sx : LLVMOpaqueValue?
    if (te.width == 256) {
        var pargs <- [xb, wv]
        sx = LLVMBuildCall2(b, te.psign_ty, te.psign_decl, pargs, "signx")
    } else {
        var wneg = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, wv, LLVMConstNull(te.vwi8), "wneg")
        var xneg = LLVMBuildSub(b, LLVMConstNull(te.vwi8), xb, "negx")
        sx = LLVMBuildSelect(b, wneg, xneg, xb, "signx")
    }
    if (te.dotKind == DOT_VPDPBUSD) {
        var dargs <- [acc, uwv, sx]
        return LLVMBuildCall2(b, te.dp_ty, te.dp_decl, dargs, "dot")
    }
    var margs <- [uwv, sx]
    var pairs = LLVMBuildCall2(b, te.madd_ty, te.madd_decl, margs, "pairs")
    var wargs <- [pairs, ones_i16(te)]
    var quads = LLVMBuildCall2(b, te.maddwd_ty, te.maddwd_decl, wargs, "quads")
    return LLVMBuildAdd(b, acc, quads, "dot")
}

// |w| for the u8 side of the x64 sign trick (generic llvm.abs -> VPABSB; is_int_min_poison =
// false keeps -128 defined), hoisted once per weight vector. Null for dot kinds without it
// (bias128 included — the plane bytes are already the unsigned side).
def private abs_w(var te : TileEmit; var wv : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    if (te.bias != 0 || (te.dotKind != DOT_MADDUBS && te.dotKind != DOT_VPDPBUSD)) return null
    var args <- [wv, LLVMConstInt(te.types.t_int1, 0ul, 0)]
    return LLVMBuildCall2(te.builder, te.abs_ty, te.abs_decl, args, name)
}

def private load_vec(var te : TileEmit; ty : LLVMOpaqueType?; var base, off : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    var p = LLVMBuildGEP2(te.builder, te.types.t_int8, base, off, name)
    return LLVMBuildLoad2Aligned(te.builder, ty, p, 1u, name)
}

def private load_v16i8(var te : TileEmit; var base, off : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    return load_vec(te, te.v16i8, base, off, name)
}

def private splat_f32(var te : TileEmit; var v : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    var one = LLVMBuildInsertElement(te.builder, LLVMGetUndef(te.vnf32), v, te.types->ConstI32(0ul), "")
    let mask <- [for (_i in range(te.rv)); 0]
    return LLVMBuildShuffleVector(te.builder, te.types, one, one, mask, name)
}

def private splat_i32(var te : TileEmit; var v : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    var one = LLVMBuildInsertElement(te.builder, LLVMGetUndef(te.vni32), v, te.types->ConstI32(0ul), "")
    let mask <- [for (_i in range(te.rv)); 0]
    return LLVMBuildShuffleVector(te.builder, te.types, one, one, mask, name)
}

// the bias128 accumulator init: −128·Σx(block) for one token — the whole exactness
// correction (init + Σ(w+128)·x = Σw·x, so the scale fold sees the plain-s8 integer).
// Tile: one load off the bsums plane (splat folds to an embedded-broadcast). GEMV (no
// plane): concat the block's two 16-byte chunks, one vpdpbusd(0, splat(128u), x) at kernel
// width (zero-padded at 512 — padded dwords contribute 128·0), reduce, negate, splat.
def private bias_acc_init(var te : TileEmit; var bi, xlo, xhi : LLVMOpaqueValue?; tk : int) : LLVMOpaqueValue? {
    let b = te.builder
    var s : LLVMOpaqueValue?
    if (te.xbs[tk] != null) {
        var bp = LLVMBuildGEP2(b, te.types.t_int32, te.xbs[tk], bi, "bp{tk}")
        s = LLVMBuildLoad2Aligned(b, te.types.t_int32, bp, 4u, "bsum{tk}")
    } else {
        let cat <- [for (i in range(32)); i]
        var x32 = LLVMBuildShuffleVector(b, te.types, xlo, xhi, cat, "xcat")
        var xw = x32
        if (te.width == 512) {
            let pad <- [for (i in range(64)); i]     // lanes 32..63 read the zero vector
            xw = LLVMBuildShuffleVector(b, te.types, x32, LLVMConstNull(LLVMVectorType(te.types.t_int8, 32u)), pad, "xpad")
        }
        var dargs <- [LLVMConstNull(te.vni32), splat_i8w(te, 128), xw]
        var pdot = LLVMBuildCall2(b, te.dp_ty, te.dp_decl, dargs, "bdot")
        var rargs <- [pdot]
        var r = LLVMBuildCall2(b, te.reduce_ty, te.reduce_decl, rargs, "bsum")
        s = LLVMBuildSub(b, te.types->ConstI32(0ul), r, "nbsum")
    }
    var one = LLVMBuildInsertElement(b, LLVMGetUndef(te.vni32), s, te.types->ConstI32(0ul), "")
    let mask <- [for (_i in range(te.rv)); 0]
    return LLVMBuildShuffleVector(b, te.types, one, one, mask, "binit{tk}")
}

// one 32-k block for tokens [tokBase, tokBase+tokCount): 8*rq shared weight vectors x tokens =
// tokCount*rq*8 lane-dots at full width, then the per-block scale fold f[acc] +=
// float(a[acc]) * s[qd] * splat(q[i]) — the exact op order of the hand template
// dot_q8q8_laneq4x4_template, so fast-math contraction sees the same input (and for the sdot
// mr=4 perm the exact M2 instruction sequence). Accumulator index = token * rq + row-vector;
// the per-vector splat re-emission is byte-identical, so GVN folds it to one. Weight/scale
// strides come off te.interleave — the q8q8_repack_type derivation: dword-group kg of block bi
// holds mr rows x 4 k-bytes, vector qd's vwi8 at bi*mr*32 + kg*4*mr + qd*(width/8).
def private emit_block(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    let b = te.builder
    let rq = te.rq
    var wb = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave * 0x20)), "wb")
    var xb = LLVMBuildMul(b, bi, te.types->ConstI64(0x20ul), "xb")
    var wv : LLVMOpaqueValue? [16]
    var uw : LLVMOpaqueValue? [16]
    if (te.kgroup == 8) {
        // kg8 plane under the sdot lattice (the smmla stamp's gemv / single-token path): per
        // (kg8 group, row quad) two row-pair loads + uzp1/uzp2.4s reassemble the two
        // kg4-shaped weight vectors — [r0 klo, r1 klo, r2 klo, r3 klo] — and the lattice
        // below is untouched. Only smmla perms stamp kg8, so this path is NEON-width only.
        for (g in range(4)) {
            for (qd in range(rq)) {
                let boff = g * 8 * te.interleave + (2 * qd) * 16
                var off0 = boff == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff)), "")
                var p0 = load_v16i8(te, te.wg, off0, "wp{g * rq + qd}a")
                var off1 = LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff + 16)), "")
                var p1 = load_v16i8(te, te.wg, off1, "wp{g * rq + qd}b")
                var p0i = LLVMBuildBitCast(b, p0, te.v4i32, "")
                var p1i = LLVMBuildBitCast(b, p1, te.v4i32, "")
                var lo = LLVMBuildShuffleVector(b, te.types, p0i, p1i, [0, 2, 4, 6], "wlo{g * rq + qd}")
                var hi = LLVMBuildShuffleVector(b, te.types, p0i, p1i, [1, 3, 5, 7], "whi{g * rq + qd}")
                wv[(2 * g) * rq + qd] = LLVMBuildBitCast(b, lo, te.vwi8, "wv{(2 * g) * rq + qd}")
                wv[(2 * g + 1) * rq + qd] = LLVMBuildBitCast(b, hi, te.vwi8, "wv{(2 * g + 1) * rq + qd}")
                uw[(2 * g) * rq + qd] = abs_w(te, wv[(2 * g) * rq + qd], "uw{(2 * g) * rq + qd}")
                uw[(2 * g + 1) * rq + qd] = abs_w(te, wv[(2 * g + 1) * rq + qd], "uw{(2 * g + 1) * rq + qd}")
            }
        }
    } else {
        for (kg in range(8)) {
            for (qd in range(rq)) {
                let boff = kg * 4 * te.interleave + qd * (te.width / 8)
                var off = boff == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff)), "")
                wv[kg * rq + qd] = load_vec(te, te.vwi8, te.wg, off, "wv{kg * rq + qd}")
                uw[kg * rq + qd] = abs_w(te, wv[kg * rq + qd], "uw{kg * rq + qd}")
            }
        }
    }
    var xv0 : LLVMOpaqueValue? [4]
    var xv1 : LLVMOpaqueValue? [4]
    var xb1 = LLVMBuildAdd(b, xb, te.types->ConstI64(16ul), "")
    for (i in range(tokCount)) {
        xv0[i] = load_v16i8(te, te.x[tokBase + i], xb, "x{tokBase + i}lo")
        xv1[i] = load_v16i8(te, te.x[tokBase + i], xb1, "x{tokBase + i}hi")
    }
    var a : LLVMOpaqueValue? [8]
    if (te.bias == 0) {
        for (i in range(tokCount * rq)) {
            a[i] = LLVMConstNull(te.vni32)
        }
    } else {
        for (i in range(tokCount)) {    // one init per token, shared across the qd accumulators
            var init = bias_acc_init(te, bi, xv0[i], xv1[i], tokBase + i)
            for (qd in range(rq)) {
                a[i * rq + qd] = init
            }
        }
    }
    for (l in range(4)) {           // chunk 0 (k 0..15): lane l of each token vs shared weight vectors
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = dot_lane(te, a[i * rq + qd], wv[l * rq + qd], uw[l * rq + qd], xv0[i], l)
            }
        }
    }
    for (l in range(4)) {           // chunk 1 (k 16..31)
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = dot_lane(te, a[i * rq + qd], wv[(4 + l) * rq + qd], uw[(4 + l) * rq + qd], xv1[i], l)
            }
        }
    }
    emit_scale_fold(te, bi, a, f, tokBase, tokCount)
}

// the fold's a·b+c as @llvm.fmuladd — the SAME intrinsic daslang's mad() lowers to
// (intrinsic_mad in llvm_jit_intrin): generated IR never passes das-level lowering, so the
// generator must license the fusion itself. Falls back to fmul+fadd when unresolvable.
def private fold_fma(var te : TileEmit; var a, b, c : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    let bld = te.builder
    let id = LLVMLookupIntrinsicID("llvm.fmuladd")
    if (id != 0u) {
        var mod = LLVMGetGlobalParent(LLVMGetBasicBlockParent(LLVMGetInsertBlock(bld)))
        var tys <- [te.vnf32]
        var decl = LLVMGetIntrinsicDeclaration(mod, id, tys)
        if (decl != null) {
            var fty = LLVMFunctionType(te.vnf32, [te.vnf32, te.vnf32, te.vnf32])
            var args <- [a, b, c]
            return LLVMBuildCall2(bld, fty, decl, args, name)
        }
    }
    return LLVMBuildFAdd(bld, LLVMBuildFMul(bld, a, b, ""), c, name)
}

// one vnf32 group-scale vector at element index `idx` off `base` — the f32-plane load, or
// (sgF16) the raw-binary16 plane widened via bitcast-to-half + fpext (fcvtl / vcvtph2ps: the
// scalar f16_to_f32 JIT lowering, vectorized). Every weight-scale load in the family goes
// through here, so the two planes differ ONLY in this load and the fold order is shared.
def private load_scale_vec(var te : TileEmit; var base, idx : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    let b = te.builder
    if (!te.sgF16) {
        var sgp = LLVMBuildGEP2(b, te.types.t_float, base, idx, name)
        return LLVMBuildLoad2Aligned(b, te.vnf32, sgp, 4u, name)
    }
    var sgp = LLVMBuildGEP2(b, te.types.t_int16, base, idx, name)
    var hv = LLVMBuildLoad2Aligned(b, te.vni16, sgp, 2u, name)
    return LLVMBuildFPExt(b, LLVMBuildBitCast(b, hv, te.vnf16, ""), te.vnf32, name)
}

// the per-block Q8 scale fold shared by the sdot/x64 lattice and the smmla MMA form: f[acc] +=
// float(a[acc]) * s[qd] * splat(q[i]) — the exact op order of the hand template
// dot_q8q8_laneq4x4_template, so every emitter's fast-math contraction sees the same input and
// the one grp4 oracle serves all layouts. `a` is token-major (token * rq + row-vector).
def private emit_scale_fold(var te : TileEmit; var bi : LLVMOpaqueValue?; a : LLVMOpaqueValue? [8]; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    let b = te.builder
    let rq = te.rq
    var s4 : LLVMOpaqueValue? [4]
    var sgIdx0 = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave)), "")
    for (qd in range(rq)) {
        var idx = qd == 0 ? sgIdx0 : LLVMBuildAdd(b, sgIdx0, te.types->ConstI64(uint64(qd * te.rv)), "")
        s4[qd] = load_scale_vec(te, te.sg, idx, qd == 0 ? "s4" : "s4{qd}")
    }
    for (i in range(tokCount)) {
        let tk = tokBase + i
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[tk], bi, "qp{tk}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "q{tk}")
        for (qd in range(rq)) {
            var af = LLVMBuildSIToFP(b, a[i * rq + qd], te.vnf32, "af{tk}")
            var sq = LLVMBuildFMul(b, s4[qd], splat_f32(te, q, "qs{tk}"), "")
            f[i * rq + qd] = fold_fma(te, af, sq, f[i * rq + qd], "f{tk}")
        }
    }
}

// one 32-k block, SMMLA form (the kg8 plane, slice J): B operands are row-pair × 8-k
// 16-byte loads straight off the plane (4 k-slices × mr/2 row pairs — the repack did the
// marshalling); A operands pair tokens (2tp, 2tp+1) per k-slice via zip1/zip2.2d byte
// shuffles off the same chunk loads as the sdot form (4 per token pair, reused across every
// row pair); the MMA lattice accumulates 2×2 patches m[tp][rp] = [t0·ra, t0·rb, t1·ra,
// t1·rb]; then a 2-shuffle i32 transpose per (token pair, row quad) hands token-major
// accumulators to the SAME per-block scale fold — fold order preserved, one oracle.
// tokCount is even by construction (nrsplit ∈ {2,4}; single-token slices ride emit_block).
def private emit_block_smmla(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    let b = te.builder
    let rq = te.rq                    // row quads — the transpose/fold granularity
    let nrp = te.interleave / 2       // row pairs — the MMA granularity
    let ntp = tokCount / 2            // token pairs
    var wb = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave * 0x20)), "wb")
    var xb = LLVMBuildMul(b, bi, te.types->ConstI64(0x20ul), "xb")
    var wv : LLVMOpaqueValue? [16]    // [g * nrp + rp]; 4 * nrp <= 16 under the budget rail
    for (g in range(4)) {
        for (rp in range(nrp)) {
            let boff = g * 8 * te.interleave + rp * 16
            var off = boff == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff)), "")
            wv[g * nrp + rp] = load_v16i8(te, te.wg, off, "wv{g * nrp + rp}")
        }
    }
    var xv0 : LLVMOpaqueValue? [4]
    var xv1 : LLVMOpaqueValue? [4]
    var xb1 = LLVMBuildAdd(b, xb, te.types->ConstI64(16ul), "")
    for (i in range(tokCount)) {
        xv0[i] = load_v16i8(te, te.x[tokBase + i], xb, "x{tokBase + i}lo")
        xv1[i] = load_v16i8(te, te.x[tokBase + i], xb1, "x{tokBase + i}hi")
    }
    // A[tp][g] = tokens (2tp, 2tp+1) k-bytes (8g..8g+7): zip1/zip2.2d byte-shuffle shapes
    let mlo <- [for (i in range(16)); i < 8 ? i : 8 + i]        // [0..7, 16..23]
    let mhi <- [for (i in range(16)); i < 8 ? 8 + i : 16 + i]   // [8..15, 24..31]
    var av : LLVMOpaqueValue? [8]     // [tp * 4 + g]; ntp * 4 <= 8
    for (tp in range(ntp)) {
        let i0 = 2 * tp
        av[tp * 4 + 0] = LLVMBuildShuffleVector(b, te.types, xv0[i0], xv0[i0 + 1], mlo, "a{tp}k0")
        av[tp * 4 + 1] = LLVMBuildShuffleVector(b, te.types, xv0[i0], xv0[i0 + 1], mhi, "a{tp}k1")
        av[tp * 4 + 2] = LLVMBuildShuffleVector(b, te.types, xv1[i0], xv1[i0 + 1], mlo, "a{tp}k2")
        av[tp * 4 + 3] = LLVMBuildShuffleVector(b, te.types, xv1[i0], xv1[i0 + 1], mhi, "a{tp}k3")
    }
    var m : LLVMOpaqueValue? [8]      // [tp * nrp + rp]; ntp * nrp <= 8 under the budget rail
    for (i in range(ntp * nrp)) {
        m[i] = LLVMConstNull(te.vni32)
    }
    for (g in range(4)) {
        for (tp in range(ntp)) {
            for (rp in range(nrp)) {
                var margs <- [m[tp * nrp + rp], av[tp * 4 + g], wv[g * nrp + rp]]
                m[tp * nrp + rp] = LLVMBuildCall2(b, te.smmla_ty, te.smmla_decl, margs, "mm")
            }
        }
    }
    // transpose the 2×2 patches to token-major row quads: a[2tp][q] = [mA.0, mA.1, mB.0,
    // mB.1] (uzp1.2d shape), a[2tp+1][q] = [mA.2, mA.3, mB.2, mB.3] (uzp2.2d)
    var a : LLVMOpaqueValue? [8]
    for (tp in range(ntp)) {
        for (q in range(rq)) {
            var mA = m[tp * nrp + 2 * q]
            var mB = m[tp * nrp + 2 * q + 1]
            a[(2 * tp) * rq + q] = LLVMBuildShuffleVector(b, te.types, mA, mB, [0, 1, 4, 5], "at{tokBase + 2 * tp}q{q}")
            a[(2 * tp + 1) * rq + q] = LLVMBuildShuffleVector(b, te.types, mA, mB, [2, 3, 6, 7], "at{tokBase + 2 * tp + 1}q{q}")
        }
    }
    emit_scale_fold(te, bi, a, f, tokBase, tokCount)
}

// constant i8 splat at the weight-vector width
def private splat_i8w(te : TileEmit; v : int) : LLVMOpaqueValue? {
    var elems <- [for (_i in range(te.width / 8)); LLVMConstInt(te.types.t_int8, uint64(v & 255), 0)]
    return LLVMConstVector(array_data_ptr(elems), uint(te.width / 8))
}

// constant i32 splat at the accumulator width
def private splat_i32n(te : TileEmit; v : int) : LLVMOpaqueValue? {
    var elems <- [for (_i in range(te.rv)); LLVMConstInt(te.types.t_int32, uint64(v), 0)]
    return LLVMConstVector(array_data_ptr(elems), uint(te.rv))
}

// the LUT dequant of one nibble-index vector: NEON tbl1 (v16i8 LUT), x64 pshufb (the LUT
// broadcast per 16-byte lane — indices are 0..15 with bit 7 clear, so pshufb's zeroing path
// never fires and its per-lane semantics match the broadcast exactly)
def private lut_lookup(var te : TileEmit; var idx : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    if (te.dotKind == DOT_SDOT) {
        var targs <- [te.lut, idx]
        return LLVMBuildCall2(te.builder, te.tbl_ty, te.tbl_decl, targs, name)
    }
    var pargs <- [te.lut, idx]
    return LLVMBuildCall2(te.builder, te.pshuf_ty, te.pshuf_decl, pargs, name)
}

// one 32-k block, MXFP4 form (mx4 planes): per row vector per dword-group j, ONE vwi8 nibble
// load feeds LUT-lo (k j*4..j*4+3, the LUT baked as a constant vector) and LUT-hi (k
// j*4+16..+19) — 4*rq loads + 8*rq lookups replace the Q8 block's 8*rq weight loads; the
// lane-dot lattice and the per-block fold are the Q8 emitter's, with the scale computed
// in-register from mr E8M0 bytes: bits = e < 2 ? 0x00200000 << e : (e - 1) << 23 (e8m0_half's
// exact bit trick, vectorized per row vector; the not-taken shl-by-(e-1) arm at e=0 is poison
// LLVM's select never selects).
def private emit_block_mx4(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    let b = te.builder
    let rq = te.rq
    var wb = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave * 16)), "wb")
    var xb = LLVMBuildMul(b, bi, te.types->ConstI64(0x20ul), "xb")
    var wlo : LLVMOpaqueValue? [8]
    var whi : LLVMOpaqueValue? [8]
    var ulo : LLVMOpaqueValue? [8]
    var uhi : LLVMOpaqueValue? [8]
    for (j in range(4)) {
        for (qd in range(rq)) {
            let boff = j * 4 * te.interleave + qd * (te.width / 8)
            var off = boff == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff)), "")
            var nv = load_vec(te, te.vwi8, te.wg, off, "nv{j * rq + qd}")
            var loIdx = LLVMBuildAnd(b, nv, splat_i8w(te, 15), "nib.lo")
            var hiIdx = LLVMBuildLShr(b, nv, splat_i8w(te, 4), "nib.hi")
            wlo[j * rq + qd] = lut_lookup(te, loIdx, "wlo{j * rq + qd}")
            whi[j * rq + qd] = lut_lookup(te, hiIdx, "whi{j * rq + qd}")
            ulo[j * rq + qd] = abs_w(te, wlo[j * rq + qd], "ulo{j * rq + qd}")
            uhi[j * rq + qd] = abs_w(te, whi[j * rq + qd], "uhi{j * rq + qd}")
        }
    }
    var xv0 : LLVMOpaqueValue? [4]
    var xv1 : LLVMOpaqueValue? [4]
    var xb1 = LLVMBuildAdd(b, xb, te.types->ConstI64(16ul), "")
    for (i in range(tokCount)) {
        xv0[i] = load_v16i8(te, te.x[tokBase + i], xb, "x{tokBase + i}lo")
        xv1[i] = load_v16i8(te, te.x[tokBase + i], xb1, "x{tokBase + i}hi")
    }
    var a : LLVMOpaqueValue? [8]
    for (i in range(tokCount * rq)) {
        a[i] = LLVMConstNull(te.vni32)
    }
    for (l in range(4)) {           // chunk 0 (k 0..15): low-nibble weights
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = dot_lane(te, a[i * rq + qd], wlo[l * rq + qd], ulo[l * rq + qd], xv0[i], l)
            }
        }
    }
    for (l in range(4)) {           // chunk 1 (k 16..31): high-nibble weights
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = dot_lane(te, a[i * rq + qd], whi[l * rq + qd], uhi[l * rq + qd], xv1[i], l)
            }
        }
    }
    var vri8 = LLVMVectorType(te.types.t_int8, uint(te.rv))
    var s4 : LLVMOpaqueValue? [4]
    var sgIdx0 = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave)), "")
    for (qd in range(rq)) {
        var idx = qd == 0 ? sgIdx0 : LLVMBuildAdd(b, sgIdx0, te.types->ConstI64(uint64(qd * te.rv)), "")
        var egp = LLVMBuildGEP2(b, te.types.t_int8, te.sg, idx, qd == 0 ? "egp" : "egp{qd}")
        var ev = LLVMBuildLoad2Aligned(b, vri8, egp, 1u, qd == 0 ? "e4" : "e4{qd}")
        var e32 = LLVMBuildZExt(b, ev, te.vni32, "")
        var lt2 = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntULT, e32, splat_i32n(te, 2), "")
        var loBits = LLVMBuildShl(b, splat_i32n(te, int(0x00200000)), e32, "")
        var hiBits = LLVMBuildShl(b, LLVMBuildSub(b, e32, splat_i32n(te, 1), ""), splat_i32n(te, 23), "")
        var bits = LLVMBuildSelect(b, lt2, loBits, hiBits, "")
        // NOTE: the name is hoisted — a TERNARY string fed straight to a raw extern's
        // `string implicit` param SIGSEGVs the compiler (issue #3374)
        let s4name = qd == 0 ? "s4" : "s4{qd}"
        s4[qd] = LLVMBuildBitCast(b, bits, te.vnf32, s4name)
    }
    for (i in range(tokCount)) {
        let tk = tokBase + i
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[tk], bi, "qp{tk}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "q{tk}")
        for (qd in range(rq)) {
            var af = LLVMBuildSIToFP(b, a[i * rq + qd], te.vnf32, "af{tk}")
            var sq = LLVMBuildFMul(b, s4[qd], splat_f32(te, q, "qs{tk}"), "")
            f[i * rq + qd] = fold_fma(te, af, sq, f[i * rq + qd], "f{tk}")
        }
    }
}

// one K-quant lane-dot: acc += q · (dword-group `lane` of x, splatted). The quants are UNSIGNED
// (0..15/31/63) straight off the expand — they ARE the u8 side of vpdpbusd/maddubs (signed x on
// the other side), and they fit s8 non-negatively for bssd/sdot — so no |w|, no sign apply, no
// bias plane on any leg. maddubs pair-sums stay exact: 2·63·127 < 32767.
def private kq_dot_lane(var te : TileEmit; var acc, qv, xv : LLVMOpaqueValue?; lane : int) : LLVMOpaqueValue? {
    if (te.dotKind == DOT_SDOT || te.dotKind == DOT_SMMLA) {
        return sdot_lane(te, acc, qv, xv, lane)
    }
    let b = te.builder
    var xi32 = LLVMBuildBitCast(b, xv, te.v4i32, "")
    let mask <- [for (_i in range(te.rv)); lane]
    var xspl = LLVMBuildShuffleVector(b, te.types, xi32, xi32, mask, "xlane")
    var xb = LLVMBuildBitCast(b, xspl, te.vwi8, "")
    if (te.dotKind == DOT_MADDUBS) {
        var margs <- [qv, xb]
        var pairs = LLVMBuildCall2(b, te.madd_ty, te.madd_decl, margs, "pairs")
        var wargs <- [pairs, ones_i16(te)]
        var quads = LLVMBuildCall2(b, te.maddwd_ty, te.maddwd_decl, wargs, "quads")
        return LLVMBuildAdd(b, acc, quads, "dot")
    }
    var dargs <- [acc, qv, xb]
    return LLVMBuildCall2(b, te.dp_ty, te.dp_decl, dargs, "dot")
}

// one <rv x i8> row-byte load at BYTE offset, each byte splatted across its row's 4 lanes to
// vwi8 (constant shufflevector — the backend picks tbl/pshufb itself; no intrinsic needed)
def private load_row_bytes_x4(var te : TileEmit; var base, off : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    var vri8 = LLVMVectorType(te.types.t_int8, uint(te.rv))
    var p = LLVMBuildGEP2(te.builder, te.types.t_int8, base, off, name)
    var v = LLVMBuildLoad2Aligned(te.builder, vri8, p, 1u, name)
    let mask <- [for (i in range(te.width / 8)); i / 4]
    return LLVMBuildShuffleVector(te.builder, te.types, v, v, mask, name)
}

// one <rv x i16> binary16 load at BYTE offset off, widened to vnf32 (the kq scale planes are
// byte-addressed; fcvtl / vcvtph2ps lowering, same as load_scale_vec's sgF16 arm)
def private load_f16_vec_at(var te : TileEmit; var base, off : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    let b = te.builder
    var p = LLVMBuildGEP2(b, te.types.t_int8, base, off, name)
    var hv = LLVMBuildLoad2Aligned(b, te.vni16, p, 2u, name)
    return LLVMBuildFPExt(b, LLVMBuildBitCast(b, hv, te.vnf16, ""), te.vnf32, name)
}

// or-in of a masked bit test as the nibble's 0x10: w |= (bytes & mask) != 0 ? 0x10 : 0
// (pcmpeqb+pand shape after lowering — the k5 high-bit deposit)
def private or_bit_x10(te : TileEmit; var w, bytes, maskv : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    let b = te.builder
    var hit = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntNE, LLVMBuildAnd(b, bytes, maskv, ""), LLVMConstNull(te.vwi8), "")
    var sel = LLVMBuildSelect(b, hit, splat_i8w(te, 16), LLVMConstNull(te.vwi8), name)
    return LLVMBuildOr(b, w, sel, name)
}

// One 256-weight SUPERBLOCK, K-quant grp<mr> form (te.kq = 4/5/6; single token — the kq family
// is GEMV-only). Plane layouts per superblock per mr-row group (see repack_k4/k5/k6_grp):
//   k4  quants [blk 0..7][j 0..3][row][4B] — byte t of (blk,j) = nibble pair for k blk*32+j*4+t
//       (low) / +16 (high), the mx4 pairing; scales [blk][mr f16 s][mr f16 o]
//   k5  = k4 + high bits [blk][j][row] 1B — bits 0..3 = the 4 low-k weights, 4..7 = high
//   k6  = k4-shaped low nibbles + high 2-bit groups [half 0..1][jj 0..7][row][4B] (jj covers the
//       half's 32 byte columns; block g of the half reads jj=j (lo) / j+4 (hi) at uniform shift
//       2g); scales [16 x mr int8 sc][mr f16 d] — NATIVE sub-scales, s = d·sc widened in-loop,
//       so the fold math is bit-identical to the portable dot's
// Fold per 32-sub-block: f += xs[b]·(s⊙float(Σq·a) − o⊙Σa) with Σa off the per-16 xbs plane
// (k6: o = 32·s folds as s⊙(float(Σq·a) − 32·Σa16) per 16-half). Identical loads re-emitted
// per sub-block (k6 qh groups, d vector) GVN to one — the file-wide splat discipline.
def private emit_block_kq(var te : TileEmit; var sbi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]) {
    let b = te.builder
    let rq = te.rq
    let mr = te.interleave
    let w8 = te.width / 8
    let qsb = te.kq == 4 ? 128 : (te.kq == 5 ? 160 : 192)
    var wb = LLVMBuildMul(b, sbi, te.types->ConstI64(uint64(mr * qsb)), "wb")
    var sb = LLVMBuildMul(b, sbi, te.types->ConstI64(uint64(mr * (te.kq == 6 ? 18 : 32))), "sb")
    var xb = LLVMBuildMul(b, sbi, te.types->ConstI64(0x100ul), "xb")
    var gb = LLVMBuildShl(b, sbi, te.types->ConstI64(3ul), "gb")
    var maskLoElems <- [for (i in range(w8)); LLVMConstInt(te.types.t_int8, uint64(1 << (i % 4)), 0)]
    var maskHiElems <- [for (i in range(w8)); LLVMConstInt(te.types.t_int8, uint64(16 << (i % 4)), 0)]
    var maskLo = LLVMConstVector(array_data_ptr(maskLoElems), uint(w8))
    var maskHi = LLVMConstVector(array_data_ptr(maskHiElems), uint(w8))
    for (blk in range(8)) {
        var xoff0 = LLVMBuildAdd(b, xb, te.types->ConstI64(uint64(blk * 32)), "")
        var xoff1 = LLVMBuildAdd(b, xb, te.types->ConstI64(uint64(blk * 32 + 16)), "")
        var xv0 = load_v16i8(te, te.x[0], xoff0, "x{blk}lo")
        var xv1 = load_v16i8(te, te.x[0], xoff1, "x{blk}hi")
        var a0 : LLVMOpaqueValue? [2]
        var a1 : LLVMOpaqueValue? [2]
        for (qd in range(rq)) {
            a0[qd] = LLVMConstNull(te.vni32)
            a1[qd] = LLVMConstNull(te.vni32)
        }
        for (j in range(4)) {
            for (qd in range(rq)) {
                var noff = LLVMBuildAdd(b, wb, te.types->ConstI64(uint64((blk * 16 + j * 4) * mr + qd * w8)), "")
                var nv = load_vec(te, te.vwi8, te.wg, noff, "nv{blk}_{j * rq + qd}")
                var wlo = LLVMBuildAnd(b, nv, splat_i8w(te, 15), "wlo{blk}_{j * rq + qd}")
                var whi = LLVMBuildLShr(b, nv, splat_i8w(te, 4), "whi{blk}_{j * rq + qd}")
                if (te.kq == 5) {
                    var hoff = LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(128 * mr + (blk * 4 + j) * mr + qd * te.rv)), "")
                    var hb = load_row_bytes_x4(te, te.wg, hoff, "qh{blk}_{j * rq + qd}")
                    wlo = or_bit_x10(te, wlo, hb, maskLo, "wlo5{blk}_{j * rq + qd}")
                    whi = or_bit_x10(te, whi, hb, maskHi, "whi5{blk}_{j * rq + qd}")
                } elif (te.kq == 6) {
                    let g2 = (blk % 4) * 2
                    let hbase = 128 * mr + ((blk / 4) * 8) * 4 * mr
                    var hloOff = LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(hbase + j * 4 * mr + qd * w8)), "")
                    var hhiOff = LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(hbase + (j + 4) * 4 * mr + qd * w8)), "")
                    var qhlo = load_vec(te, te.vwi8, te.wg, hloOff, "qhl{blk / 4}_{j * rq + qd}")
                    var qhhi = load_vec(te, te.vwi8, te.wg, hhiOff, "qhh{blk / 4}_{j * rq + qd}")
                    var dlo = LLVMBuildAnd(b, LLVMBuildLShr(b, qhlo, splat_i8w(te, g2), ""), splat_i8w(te, 3), "")
                    var dhi = LLVMBuildAnd(b, LLVMBuildLShr(b, qhhi, splat_i8w(te, g2), ""), splat_i8w(te, 3), "")
                    wlo = LLVMBuildOr(b, wlo, LLVMBuildShl(b, dlo, splat_i8w(te, 4), ""), "wlo6{blk}_{j * rq + qd}")
                    whi = LLVMBuildOr(b, whi, LLVMBuildShl(b, dhi, splat_i8w(te, 4), ""), "whi6{blk}_{j * rq + qd}")
                }
                a0[qd] = kq_dot_lane(te, a0[qd], wlo, xv0, j)
                a1[qd] = kq_dot_lane(te, a1[qd], whi, xv1, j)
            }
        }
        // per-sub-block fold; bIdx = the global 32-block index (activation scale/bsum space)
        var bIdx = LLVMBuildAdd(b, gb, te.types->ConstI64(uint64(blk)), "b{blk}")
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[0], bIdx, "qp{blk}")
        var qs = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "qs{blk}")
        var bi2 = LLVMBuildShl(b, bIdx, te.types->ConstI64(1ul), "")
        var bp0 = LLVMBuildGEP2(b, te.types.t_int32, te.xbs[0], bi2, "bp{blk}a")
        var bs0 = LLVMBuildLoad2Aligned(b, te.types.t_int32, bp0, 4u, "bs{blk}a")
        var bp1 = LLVMBuildGEP2(b, te.types.t_int32, te.xbs[0], LLVMBuildAdd(b, bi2, te.types->ConstI64(1ul), ""), "bp{blk}b")
        var bs1 = LLVMBuildLoad2Aligned(b, te.types.t_int32, bp1, 4u, "bs{blk}b")
        if (te.kq == 6) {
            // s16 chains: f += (float(acc) − 32·Σa16) · (d·sc16 · qs) per 16-half — the exact
            // portable term (all three factors of the integer part are exact in f32)
            var a16lo = LLVMBuildFMul(b, LLVMBuildSIToFP(b, bs0, te.types.t_float, ""), te.types->ConstReal(32.0lf), "a32{blk}a")
            var a16hi = LLVMBuildFMul(b, LLVMBuildSIToFP(b, bs1, te.types.t_float, ""), te.types->ConstReal(32.0lf), "a32{blk}b")
            var vri8 = LLVMVectorType(te.types.t_int8, uint(te.rv))
            for (qd in range(rq)) {
                var dv = load_f16_vec_at(te, te.sg, LLVMBuildAdd(b, sb, te.types->ConstI64(uint64(16 * mr + 2 * (qd * te.rv))), ""), "d{qd}")
                var sc0p = LLVMBuildGEP2(b, te.types.t_int8, te.sg, LLVMBuildAdd(b, sb, te.types->ConstI64(uint64(2 * blk * mr + qd * te.rv)), ""), "sc{blk}a")
                var sc1p = LLVMBuildGEP2(b, te.types.t_int8, te.sg, LLVMBuildAdd(b, sb, te.types->ConstI64(uint64((2 * blk + 1) * mr + qd * te.rv)), ""), "sc{blk}b")
                var sc0 = LLVMBuildSIToFP(b, LLVMBuildSExt(b, LLVMBuildLoad2Aligned(b, vri8, sc0p, 1u, ""), te.vni32, ""), te.vnf32, "")
                var sc1 = LLVMBuildSIToFP(b, LLVMBuildSExt(b, LLVMBuildLoad2Aligned(b, vri8, sc1p, 1u, ""), te.vni32, ""), te.vnf32, "")
                var qspl = splat_f32(te, qs, "qs{blk}v")
                var s0 = LLVMBuildFMul(b, LLVMBuildFMul(b, dv, sc0, ""), qspl, "s0{blk}_{qd}")
                var s1 = LLVMBuildFMul(b, LLVMBuildFMul(b, dv, sc1, ""), qspl, "s1{blk}_{qd}")
                var t0 = LLVMBuildFSub(b, LLVMBuildSIToFP(b, a0[qd], te.vnf32, ""), splat_f32(te, a16lo, ""), "t0{blk}_{qd}")
                var t1 = LLVMBuildFSub(b, LLVMBuildSIToFP(b, a1[qd], te.vnf32, ""), splat_f32(te, a16hi, ""), "t1{blk}_{qd}")
                f[qd] = fold_fma(te, t0, s0, f[qd], "f{blk}_{qd}a")
                f[qd] = fold_fma(te, t1, s1, f[qd], "f{blk}_{qd}b")
            }
        } else {
            // k4/k5: one 32-wide chain per qd (both 16-halves share the block's f16 (s,o) pair);
            // Σa32 = the two per-16 sums, offset term o·(qs·Σa) folds as a second fma
            var acc : LLVMOpaqueValue? [2]
            for (qd in range(rq)) {
                acc[qd] = LLVMBuildAdd(b, a0[qd], a1[qd], "acc{blk}_{qd}")
            }
            var a32 = LLVMBuildAdd(b, bs0, bs1, "a32{blk}")
            var qa = LLVMBuildFMul(b, qs, LLVMBuildSIToFP(b, a32, te.types.t_float, ""), "qa{blk}")
            var nqa = LLVMBuildFNeg(b, qa, "nqa{blk}")
            for (qd in range(rq)) {
                var sv = load_f16_vec_at(te, te.sg, LLVMBuildAdd(b, sb, te.types->ConstI64(uint64(blk * 4 * mr + 2 * (qd * te.rv))), ""), "s{blk}_{qd}")
                var ov = load_f16_vec_at(te, te.sg, LLVMBuildAdd(b, sb, te.types->ConstI64(uint64(blk * 4 * mr + 2 * mr + 2 * (qd * te.rv))), ""), "o{blk}_{qd}")
                var af = LLVMBuildSIToFP(b, acc[qd], te.vnf32, "af{blk}_{qd}")
                var sq = LLVMBuildFMul(b, sv, splat_f32(te, qs, "qs{blk}v"), "")
                f[qd] = fold_fma(te, af, sq, f[qd], "f{blk}_{qd}")
                f[qd] = fold_fma(te, ov, splat_f32(te, nqa, "nqa{blk}v"), f[qd], "f{blk}_{qd}o")
            }
        }
    }
}

// block-emitter dispatch: the slice/loop machinery is quant-agnostic. The MMA form needs a
// token PAIR — the gemv companion's single-token slices ride the sdot lattice (emit_block's
// kg8 weight fixup reads the same plane). kq blocks are SUPERBLOCKS (the kq gemv drives
// emit_slice with nb = n/256) and single-token by construction.
def private emit_one_block(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    if (te.kq != 0) {
        emit_block_kq(te, bi, f)
    } elif (te.mx4) {
        emit_block_mx4(te, bi, f, tokBase, tokCount)
    } elif (te.dotKind == DOT_SMMLA && tokCount >= 2) {
        emit_block_smmla(te, bi, f, tokBase, tokCount)
    } else {
        emit_block(te, bi, f, tokBase, tokCount)
    }
}

def private is_tile_signature(fn : Function const?) : bool {
    if (length(fn.arguments) != 10 || fn.result.baseType != Type.tVoid) return false
    for (i in range(6)) {
        if (fn.arguments[i]._type.baseType != Type.tPointer) return false
    }
    for (i in range(6, 10)) {
        if (fn.arguments[i]._type.baseType != Type.tInt64) return false
    }
    return true
}

// slice parameters shared by emit_slice and its caller
struct private SliceArgs {
    gc_impl : LLVMOpaqueValue?
    ctx : LLVMOpaqueContext?
    nb : LLVMOpaqueValue?
    d : LLVMOpaqueValue?
    g : LLVMOpaqueValue?
    t0 : LLVMOpaqueValue?
    yp : LLVMOpaqueValue?
    kstep : int
}

// one accumulator slice: the whole k loop for tokens [tokBase, tokBase+tokCount), then the
// per-token float-vector stores (one per row vector). `pred` must be terminator-free; returns
// the slice's merge block (also terminator-free). Main loop runs kstep blocks per iteration;
// the remainder is a chain of kstep-1 conditional single blocks — for kstep=2 this is head/
// body/tail_check/tail_body/after, the exact M2 CFG. Accumulator arrays hold tokCount*rq
// entries (token-major), max 8 under the decline rails.
def private emit_slice(var te : TileEmit; var sa : SliceArgs; var pred : LLVMOpaqueBasicBlock?; tokBase, tokCount : int; sfx : string) : LLVMOpaqueBasicBlock? {
    let b = te.builder
    let K = sa.kstep
    let nacc = tokCount * te.rq
    var head = LLVMAppendBasicBlockInContext(sa.ctx, sa.gc_impl, "head{sfx}")
    var body = LLVMAppendBasicBlockInContext(sa.ctx, sa.gc_impl, "body{sfx}")
    var checks : array<LLVMOpaqueBasicBlock?>
    var tails : array<LLVMOpaqueBasicBlock?>
    checks |> reserve(K - 1)
    tails |> reserve(K - 1)
    for (j in range(K - 1)) {
        let jsfx = j == 0 ? "" : "{j}"
        checks |> push(LLVMAppendBasicBlockInContext(sa.ctx, sa.gc_impl, "tail_check{jsfx}{sfx}"))
        tails |> push(LLVMAppendBasicBlockInContext(sa.ctx, sa.gc_impl, "tail_body{jsfx}{sfx}"))
    }
    var after = LLVMAppendBasicBlockInContext(sa.ctx, sa.gc_impl, "after{sfx}")

    LLVMPositionBuilderAtEnd(b, pred)
    LLVMBuildBr(b, head)

    // head: bi/f phis (all phis first — verifier rule); run the K-block body while bi+K <= nb
    LLVMPositionBuilderAtEnd(b, head)
    var biPhi = LLVMBuildPhi(b, te.types.t_int64, "bi{sfx}")
    var fPhi : LLVMOpaqueValue? [8]
    for (i in range(nacc)) {
        fPhi[i] = LLVMBuildPhi(b, te.vnf32, "fphi{tokBase + i / te.rq}")
    }
    var entryValsBi <- [LLVMConstNull(te.types.t_int64)]
    var entryBlocks <- [pred]
    LLVMAddIncoming(biPhi, entryValsBi, entryBlocks)
    for (i in range(nacc)) {
        var zv <- [LLVMConstNull(te.vnf32)]
        var zb <- [pred]
        LLVMAddIncoming(fPhi[i], zv, zb)
    }
    var biPK = LLVMBuildAdd(b, biPhi, te.types->ConstI64(uint64(K)), "biP{K}")
    var stepCond = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLE, biPK, sa.nb, "pair")
    LLVMBuildCondBr(b, stepCond, body, K > 1 ? checks[0] : after)

    // body: K blocks per iteration
    LLVMPositionBuilderAtEnd(b, body)
    var fCur : LLVMOpaqueValue? [8]
    for (i in range(nacc)) {
        fCur[i] = fPhi[i]
    }
    emit_one_block(te, biPhi, fCur, tokBase, tokCount)
    for (j in range(1, K)) {
        var bij = LLVMBuildAdd(b, biPhi, te.types->ConstI64(uint64(j)), "")
        emit_one_block(te, bij, fCur, tokBase, tokCount)
    }
    LLVMBuildBr(b, head)
    var bodyValsBi <- [biPK]
    var bodyBlocks <- [body]
    LLVMAddIncoming(biPhi, bodyValsBi, bodyBlocks)
    for (i in range(nacc)) {
        var bv <- [fCur[i]]
        var bb <- [body]
        LLVMAddIncoming(fPhi[i], bv, bb)
    }

    // remainder chain: check j falls through to `after` when no blocks remain; its tail body
    // runs one more block. Track per-incoming f values for the merge phis.
    var mergeBlocks : array<LLVMOpaqueBasicBlock?>
    var mergeF : array<LLVMOpaqueValue? [8]>
    mergeBlocks |> reserve(K)
    mergeF |> reserve(K)
    var chainF : LLVMOpaqueValue? [8]
    for (i in range(nacc)) {
        chainF[i] = fPhi[i]
    }
    var chainBi = biPhi
    if (K == 1) {
        mergeBlocks |> push(head)
        mergeF |> push(chainF)
    }
    for (j in range(K - 1)) {
        LLVMPositionBuilderAtEnd(b, checks[j])
        var oddCond = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, chainBi, sa.nb, "odd")
        LLVMBuildCondBr(b, oddCond, tails[j], after)
        mergeBlocks |> push(checks[j])
        mergeF |> push(chainF)
        LLVMPositionBuilderAtEnd(b, tails[j])
        emit_one_block(te, chainBi, chainF, tokBase, tokCount)
        if (j + 1 < K - 1) {
            chainBi = LLVMBuildAdd(b, chainBi, te.types->ConstI64(1ul), "")
            LLVMBuildBr(b, checks[j + 1])
        } else {
            LLVMBuildBr(b, after)
            mergeBlocks |> push(tails[j])
            mergeF |> push(chainF)
        }
    }

    // after: merge phis (grouped first — verifier rule), then one float-vector store per token
    // per row vector (cols g*interleave .. +mr-1 are contiguous floats)
    LLVMPositionBuilderAtEnd(b, after)
    var fF : LLVMOpaqueValue? [8]
    for (i in range(nacc)) {
        fF[i] = LLVMBuildPhi(b, te.vnf32, "ff{tokBase + i / te.rq}")
        for (m in range(length(mergeBlocks))) {
            var iv <- [mergeF[m][i]]
            var ib <- [mergeBlocks[m]]
            LLVMAddIncoming(fF[i], iv, ib)
        }
    }
    var col = LLVMBuildMul(b, sa.g, te.types->ConstI64(uint64(te.interleave)), "col")
    for (i in range(tokCount)) {
        let tk = tokBase + i
        var tRow = LLVMBuildAdd(b, sa.t0, te.types->ConstI64(uint64(tk)), "")
        var yoffBase = LLVMBuildAdd(b, LLVMBuildMul(b, tRow, sa.d, ""), col, "")
        for (qd in range(te.rq)) {
            var yoff = qd == 0 ? yoffBase : LLVMBuildAdd(b, yoffBase, te.types->ConstI64(uint64(qd * te.rv)), "")
            var yptr = LLVMBuildGEP2(b, te.types.t_float, sa.yp, yoff, qd == 0 ? "y{tk}" : "y{tk}_{qd}")
            LLVMBuildStoreAligned(b, fF[i * te.rq + qd], yptr, 4u)
        }
    }
    return after
}

// width-derived types + the per-ISA dot machinery for one generator invocation; false =
// decline (belt — perm_declines already gated the same rails). needMx4 additionally wires the
// LUT-dequant primitive (tbl1 / pshufb) and bakes the doubled-e2m1 LUT constant.
def private setup_tile_emit(var te : TileEmit; var gc : LlvmCodeCtx; p : TilePerm; needMx4 : bool) : bool {
    let rt = q8q8_repack_type(p.mr, p.bias, kgroup_of(p))
    te.builder = gc.jit.builder
    te.types = gc.jit.types
    te.interleave = rt.interleave
    te.dotKind = dot_kind(p.dotPrim)
    // the mx4/kq planes are kgroup-independent (their own repacks) — under an smmla perm those
    // companions ride the plain sdot lattice (i8mm implies dotprod)
    if ((te.mx4 || te.kq != 0) && te.dotKind == DOT_SMMLA) {
        te.dotKind = DOT_SDOT
    }
    te.kgroup = (te.mx4 || te.kq != 0) ? 4 : rt.kgroup
    // the perm's bias applies to the Q8 weight plane only — the mx4 LUT path and the kq
    // unsigned-quant planes never see the biased repack
    te.bias = (te.mx4 || te.kq != 0) ? 0 : p.bias
    te.width = (te.dotKind == DOT_SDOT || te.dotKind == DOT_SMMLA) ? 128 : p.width
    te.rv = te.width / 32
    te.rq = rt.interleave / te.rv
    te.v16i8 = LLVMVectorType(te.types.t_int8, 16u)
    te.v4i32 = te.types->LLVMInt4Type()
    te.vwi8 = LLVMVectorType(te.types.t_int8, uint(te.width / 8))
    te.vni32 = LLVMVectorType(te.types.t_int32, uint(te.rv))
    te.vnf32 = LLVMVectorType(te.types.t_float, uint(te.rv))
    te.vni16 = LLVMVectorType(te.types.t_int16, uint(te.rv))
    te.vnf16 = LLVMVectorType(LLVMHalfTypeInContext(gc.jit.ctx), uint(te.rv))
    let mod = LLVMGetGlobalParent(gc.impl)
    if (te.dotKind == DOT_SDOT || te.dotKind == DOT_SMMLA) {
        let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
        var declTypes <- [te.vni32, te.v16i8]
        te.sdot_decl = LLVMGetIntrinsicDeclaration(mod, id, declTypes)
        if (te.sdot_decl == null) return false      // no NEON dotprod on this target: decline
        var fnArgTypes <- [te.vni32, te.v16i8, te.v16i8]
        te.sdot_ty = LLVMFunctionType(te.vni32, fnArgTypes)
        if (te.dotKind == DOT_SMMLA) {
            let mmId = LLVMLookupIntrinsicID("llvm.aarch64.neon.smmla")
            var mmTypes <- [te.vni32, te.v16i8]
            te.smmla_decl = LLVMGetIntrinsicDeclaration(mod, mmId, mmTypes)
            if (te.smmla_decl == null) return false // lockstep with perm_declines' smmla rail
            var mmArgTypes <- [te.vni32, te.v16i8, te.v16i8]
            te.smmla_ty = LLVMFunctionType(te.vni32, mmArgTypes)
        }
        if (needMx4) {
            let tblId = LLVMLookupIntrinsicID("llvm.aarch64.neon.tbl1")
            var tblDeclTypes <- [te.v16i8]
            te.tbl_decl = LLVMGetIntrinsicDeclaration(mod, tblId, tblDeclTypes)
            if (te.tbl_decl == null) return false   // lockstep with perm_declines' tbl rail
            var tblArgTypes <- [te.v16i8, te.v16i8]
            te.tbl_ty = LLVMFunctionType(te.v16i8, tblArgTypes)
        }
    } else {
        var noTypes : array<LLVMOpaqueType?>
        var b2Types <- [te.vwi8, te.vwi8]
        if (te.dotKind != DOT_VPDPBSSD && te.bias == 0) {
            // the sign-trick machinery (the proven dot32/dot64 emitter chains): |w| via
            // generic llvm.abs, sign apply via VPSIGNB at 256 (compare+negate+select at 512
            // — emitted inline in dot_lane, no decl needed). bias128 needs neither: the
            // plane bytes are the unsigned side already.
            let absId = LLVMLookupIntrinsicID("llvm.abs")
            var absTypes <- [te.vwi8]
            te.abs_decl = LLVMGetIntrinsicDeclaration(mod, absId, absTypes)
            if (te.abs_decl == null) return false
            var absArgTypes <- [te.vwi8, te.types.t_int1]
            te.abs_ty = LLVMFunctionType(te.vwi8, absArgTypes)
            if (te.width == 256) {
                let psId = LLVMLookupIntrinsicID("llvm.x86.avx2.psign.b")
                te.psign_decl = LLVMGetIntrinsicDeclaration(mod, psId, noTypes)
                if (te.psign_decl == null) return false
                te.psign_ty = LLVMFunctionType(te.vwi8, b2Types)
            }
        }
        if (te.bias != 0) {
            // the gemv inline-bsum reduce (the tile reads the bsums plane instead; an
            // unused declaration is harmless)
            let redId = LLVMLookupIntrinsicID("llvm.vector.reduce.add")
            var redTypes <- [te.vni32]
            te.reduce_decl = LLVMGetIntrinsicDeclaration(mod, redId, redTypes)
            if (te.reduce_decl == null) return false
            var redArgTypes <- [te.vni32]
            te.reduce_ty = LLVMFunctionType(te.types.t_int32, redArgTypes)
        }
        if (te.dotKind == DOT_MADDUBS) {
            let maddId = LLVMLookupIntrinsicID(te.width == 256 ? "llvm.x86.avx2.pmadd.ub.sw" : "llvm.x86.avx512.pmaddubs.w.512")
            te.madd_decl = LLVMGetIntrinsicDeclaration(mod, maddId, noTypes)
            if (te.madd_decl == null) return false
            var vhi16 = LLVMVectorType(te.types.t_int16, uint(te.width / 16))
            te.madd_ty = LLVMFunctionType(vhi16, b2Types)
            let maddwdId = LLVMLookupIntrinsicID(te.width == 256 ? "llvm.x86.avx2.pmadd.wd" : "llvm.x86.avx512.pmaddw.d.512")
            te.maddwd_decl = LLVMGetIntrinsicDeclaration(mod, maddwdId, noTypes)
            if (te.maddwd_decl == null) return false
            var w2Types <- [vhi16, vhi16]
            te.maddwd_ty = LLVMFunctionType(te.vni32, w2Types)
        } else {
            let dpId = LLVMLookupIntrinsicID(te.dotKind == DOT_VPDPBSSD ? "llvm.x86.avx2.vpdpbssd.256"
                : (te.width == 256 ? "llvm.x86.avx512.vpdpbusd.256" : "llvm.x86.avx512.vpdpbusd.512"))
            te.dp_decl = LLVMGetIntrinsicDeclaration(mod, dpId, noTypes)
            if (te.dp_decl == null) return false
            var dpArgTypes <- [te.vni32, te.vwi8, te.vwi8]
            te.dp_ty = LLVMFunctionType(te.vni32, dpArgTypes)
        }
        if (needMx4) {
            let shId = LLVMLookupIntrinsicID(te.width == 256 ? "llvm.x86.avx2.pshuf.b" : "llvm.x86.avx512.pshuf.b.512")
            te.pshuf_decl = LLVMGetIntrinsicDeclaration(mod, shId, noTypes)
            if (te.pshuf_decl == null) return false
            te.pshuf_ty = LLVMFunctionType(te.vwi8, b2Types)
        }
    }
    if (needMx4) {
        // the doubled-e2m1 LUT (mxfp4_fill_lut) as a constant vector — no table pointer at
        // runtime; broadcast per 16-byte lane on x64 (pshufb is per-lane)
        let kv = fixed_array(0, 1, 2, 3, 4, 6, 8, 12, 0, -1, -2, -3, -4, -6, -8, -12)
        let lanes = te.dotKind == DOT_SDOT ? 1 : te.width / 128
        var lutElems : array<LLVMOpaqueValue?>
        lutElems |> reserve(16 * lanes)
        for (_lane in range(lanes)) {
            for (v in kv) {
                lutElems |> push(LLVMConstInt(te.types.t_int8, uint64(v & 255), 0))
            }
        }
        te.lut = LLVMConstVector(array_data_ptr(lutElems), uint(16 * lanes))
    }
    return true
}

// AMX machinery for the TMUL tile: virtual-tile x86_amx values through the .internal
// intrinsics (non-overloaded) — LLVM's x86 codegen-prep (lower-amx-type + fast tile config)
// materializes tmm allocation and ldtilecfg itself under +amx-tile,+amx-int8. A latch perm
// swaps in the RAW immediate-tmm intrinsics instead: fixed register plan, void results, and
// NO backend config ops — the cfg companion loads the palette per chunk. A bias perm's dot
// is TDPBSUD (signed A × unsigned biased plane). The fold runs on plain zmm vectors (rv =
// 16) either way, so splat_f32 and the store shapes are the busd512 tile's.
def private setup_amx_emit(var te : TileEmit; var gc : LlvmCodeCtx; p : TilePerm) : bool {
    let raw = p.latch != 0
    te.builder = gc.jit.builder
    te.types = gc.jit.types
    te.dotKind = DOT_AMX
    te.interleave = 16
    te.rv = 16
    te.rawTiles = raw
    te.bias = p.bias
    te.vni32 = LLVMVectorType(te.types.t_int32, 16u)
    te.vnf32 = LLVMVectorType(te.types.t_float, 16u)
    te.vni16 = LLVMVectorType(te.types.t_int16, 16u)
    te.vnf16 = LLVMVectorType(LLVMHalfTypeInContext(gc.jit.ctx), 16u)
    let mod = LLVMGetGlobalParent(gc.impl)
    var noTypes : array<LLVMOpaqueType?>
    var ptrTy = te.types->LLVMVoidPtrType()
    if (raw) {
        te.tload_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.tileloadd64"), noTypes)
        te.tdp_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID(p.bias != 0 ? "llvm.x86.tdpbsud" : "llvm.x86.tdpbssd"), noTypes)
        te.tstore_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.tilestored64"), noTypes)
        te.tzero_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.tilezero"), noTypes)
        if (te.tload_decl == null || te.tdp_decl == null || te.tstore_decl == null || te.tzero_decl == null) {
            return false      // belt — perm_declines already gated the same decls
        }
        var loadArgs <- [te.types.t_int8, ptrTy, te.types.t_int64]
        te.tload_ty = LLVMFunctionType(te.types.t_void, loadArgs)
        var dpArgs <- [te.types.t_int8, te.types.t_int8, te.types.t_int8]
        te.tdp_ty = LLVMFunctionType(te.types.t_void, dpArgs)
        var storeArgs <- [te.types.t_int8, ptrTy, te.types.t_int64]
        te.tstore_ty = LLVMFunctionType(te.types.t_void, storeArgs)
        var zeroArgs <- [te.types.t_int8]
        te.tzero_ty = LLVMFunctionType(te.types.t_void, zeroArgs)
        return true
    }
    te.t_amx = LLVMX86AMXTypeInContext(gc.jit.ctx)
    if (te.t_amx == null) return false
    te.tload_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.tileloadd64.internal"), noTypes)
    te.tdp_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID(p.bias != 0 ? "llvm.x86.tdpbsud.internal" : "llvm.x86.tdpbssd.internal"), noTypes)
    te.tstore_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.tilestored64.internal"), noTypes)
    te.tzero_decl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.tilezero.internal"), noTypes)
    if (te.tload_decl == null || te.tdp_decl == null || te.tstore_decl == null || te.tzero_decl == null) {
        return false      // belt — perm_declines already gated the same decls
    }
    var loadArgs <- [te.types.t_int16, te.types.t_int16, ptrTy, te.types.t_int64]
    te.tload_ty = LLVMFunctionType(te.t_amx, loadArgs)
    var dpArgs <- [te.types.t_int16, te.types.t_int16, te.types.t_int16, te.t_amx, te.t_amx, te.t_amx]
    te.tdp_ty = LLVMFunctionType(te.t_amx, dpArgs)
    var storeArgs <- [te.types.t_int16, te.types.t_int16, ptrTy, te.types.t_int64, te.t_amx]
    te.tstore_ty = LLVMFunctionType(te.types.t_void, storeArgs)
    var zeroArgs <- [te.types.t_int16, te.types.t_int16]
    te.tzero_ty = LLVMFunctionType(te.t_amx, zeroArgs)
    return true
}

// The raw register plan (latch perms — lcpp's): C tiles tmm0-3 by (r·nt+ts), A tiles tmm4+ts,
// B tiles tmm6+r; the cfg companion's palette sets exactly these shapes (C 16×64, A 16×32,
// B 8×64). Internal-SSA perms ignore the plan — the backend allocates tmm itself.
def private amx_tmm(te : TileEmit; v : int) : LLVMOpaqueValue? {
    return LLVMConstInt(te.types.t_int8, uint64(v), 0)
}

// one B-plane tile load: internal returns the virtual tile; raw loads into tmm6+r, null result
def private amx_load_b(var te : TileEmit; r : int; var wp : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    let b = te.builder
    if (te.rawTiles) {
        var largs <- [amx_tmm(te, 6 + r), wp, te.types->ConstI64(64ul)]
        LLVMBuildCall2(b, te.tload_ty, te.tload_decl, largs, "")
        return null
    }
    var largs <- [te.types->ConstI16(int16(8)), te.types->ConstI16(int16(64)), wp, te.types->ConstI64(64ul)]
    return LLVMBuildCall2(b, te.tload_ty, te.tload_decl, largs, name)
}

// one A-activation tile load (stride = n): internal virtual tile; raw into tmm4+ts
def private amx_load_a(var te : TileEmit; ts : int; var xp, n : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    let b = te.builder
    if (te.rawTiles) {
        var largs <- [amx_tmm(te, 4 + ts), xp, n]
        LLVMBuildCall2(b, te.tload_ty, te.tload_decl, largs, "")
        return null
    }
    var largs <- [te.types->ConstI16(int16(16)), te.types->ConstI16(int16(32)), xp, n]
    return LLVMBuildCall2(b, te.tload_ty, te.tload_decl, largs, name)
}

// one C chain head: zero + TDPBSSD. Internal returns the dotted virtual tile; raw runs on
// tmm(r·nt+ts) in place, null result
def private amx_dot(var te : TileEmit; nt, r, ts : int; var av, bv : LLVMOpaqueValue?) : LLVMOpaqueValue? {
    let b = te.builder
    if (te.rawTiles) {
        var zargs <- [amx_tmm(te, r * nt + ts)]
        LLVMBuildCall2(b, te.tzero_ty, te.tzero_decl, zargs, "")
        var dargs <- [amx_tmm(te, r * nt + ts), amx_tmm(te, 4 + ts), amx_tmm(te, 6 + r)]
        LLVMBuildCall2(b, te.tdp_ty, te.tdp_decl, dargs, "")
        return null
    }
    var zargs <- [te.types->ConstI16(int16(16)), te.types->ConstI16(int16(64))]
    var cz = LLVMBuildCall2(b, te.tzero_ty, te.tzero_decl, zargs, "cz")
    var dargs <- [te.types->ConstI16(int16(16)), te.types->ConstI16(int16(64)), te.types->ConstI16(int16(32)), cz, av, bv]
    return LLVMBuildCall2(b, te.tdp_ty, te.tdp_decl, dargs, "cd")
}

// spill one C tile to scratch (stride 64)
def private amx_store(var te : TileEmit; nt, r, ts : int; var cd, reg : LLVMOpaqueValue?) {
    let b = te.builder
    if (te.rawTiles) {
        var sargs <- [amx_tmm(te, r * nt + ts), reg, te.types->ConstI64(64ul)]
        LLVMBuildCall2(b, te.tstore_ty, te.tstore_decl, sargs, "")
        return
    }
    var sargs <- [te.types->ConstI16(int16(16)), te.types->ConstI16(int16(64)), reg, te.types->ConstI64(64ul), cd]
    LLVMBuildCall2(b, te.tstore_ty, te.tstore_decl, sargs, "")
}

// The TMUL batch tile (slice I): one call covers 16·nt tokens × nt grp16 row-groups (nt =
// nrsplit; groups g..g+nt-1, plane offset +16·n each — the batch wrapper walks nt-group units
// and 16·nt-token steps off the tokstep companion). Per 32-k block: nt B tile loads straight
// off the grp16 plane (a block's 8 dword-groups ARE the 8×64 TDPBSSD B tile — zero new
// repack), nt A tile loads straight off the activation rows (stride n), then nt² tilezero →
// TDPBSSD → tilestored-to-scratch, and the per-block scale fold f32-accumulates INTO yp
// (per C-tile token row: cvt(v16i32) · ws_vec[block] · splat(xs) — the vector tile's fold
// order, so the one grp4 oracle serves). yp IS the k-loop accumulator (registers cannot hold
// 32×32 f32 across blocks): the tile zero-inits its own y region first, which also makes the
// wrapper's overlapped token-tail recompute idempotent. kstep is pinned 1 — Q8's per-block
// scale boundary (i32 cannot accumulate across blocks).
def private emit_amx_tile(var gc : LlvmCodeCtx; p : TilePerm; f16s : bool) : bool {
    var te = TileEmit(sgF16 = f16s)
    if (!setup_amx_emit(te, gc, p)) return false
    let b = gc.jit.builder
    let nt = p.nrsplit
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    var head = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "head")
    var body = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "body")
    var after = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "after")

    LLVMPositionBuilderAtEnd(b, entry)
    var yp = LLVMGetParam(gc.impl, 0u)
    var wg = LLVMGetParam(gc.impl, 1u)
    var sg = LLVMGetParam(gc.impl, 2u)
    var xqp = LLVMGetParam(gc.impl, 3u)
    var xsp = LLVMGetParam(gc.impl, 4u)
    var xbsp = LLVMGetParam(gc.impl, 5u)
    var n = LLVMGetParam(gc.impl, 6u)
    var d = LLVMGetParam(gc.impl, 7u)
    var g = LLVMGetParam(gc.impl, 8u)
    var t0 = LLVMGetParam(gc.impl, 9u)
    var nb = LLVMBuildSDiv(b, n, te.types->ConstI64(32ul), "nb")
    var col = LLVMBuildMul(b, g, te.types->ConstI64(16ul), "col")
    // C spill: one 16×64 tile region, reused per (token tile, row group) fold
    var scratch = LLVMBuildArrayAlloca(b, te.types.t_int8, te.types->ConstI64(1024ul), "cspill")
    LLVMSetAlignment(scratch, 64u)
    var n16 = LLVMBuildMul(b, n, te.types->ConstI64(16ul), "n16")
    var nb16 = LLVMBuildMul(b, nb, te.types->ConstI64(16ul), "nb16")
    var wplane : LLVMOpaqueValue? [2]     // adjacent row-group planes (+16·n each)
    var sgoff : LLVMOpaqueValue? [2]      // their scale-region offsets (+16·nb floats)
    var xbase : LLVMOpaqueValue? [2]      // A tile activation bases (rows t0 + ts·16 ..)
    for (r in range(nt)) {
        wplane[r] = r == 0 ? wg : LLVMBuildGEP2(b, te.types.t_int8, wg, n16, "wplane{r}")
        sgoff[r] = r == 0 ? LLVMConstNull(te.types.t_int64) : nb16
    }
    for (ts in range(nt)) {
        var trow = ts == 0 ? t0 : LLVMBuildAdd(b, t0, te.types->ConstI64(uint64(ts * 16)), "")
        xbase[ts] = LLVMBuildGEP2(b, te.types.t_int8, xqp, LLVMBuildMul(b, trow, n, ""), "xbase{ts}")
    }
    // fold bases: y rows start at t0·d + col, xs/xbs rows at t0·nb — the fold walks them with
    // running pointers (see amx_fold_tile: a precomputed 64/32-entry pointer array is live
    // across the k-loop and spills). Zero-init walks y with the same running pointer.
    var ybase = LLVMBuildGEP2(b, te.types.t_float, yp, LLVMBuildAdd(b, LLVMBuildMul(b, t0, d, ""), col, ""), "ybase")
    var xsbase = LLVMBuildGEP2(b, te.types.t_float, xsp, LLVMBuildMul(b, t0, nb, ""), "xsbase")
    var xbsbase : LLVMOpaqueValue?
    if (te.bias != 0) {
        xbsbase = LLVMBuildGEP2(b, te.types.t_int32, xbsp, LLVMBuildMul(b, t0, nb, ""), "xbsbase")
    }
    var zrow = ybase
    for (t in range(16 * nt)) {
        if (t != 0) {
            zrow = LLVMBuildGEP2(b, te.types.t_float, zrow, d, "zr{t}")
        }
        for (r in range(nt)) {
            var zp = r == 0 ? zrow : LLVMBuildGEP2(b, te.types.t_float, zrow, te.types->ConstI64(uint64(r * 16)), "")
            LLVMBuildStoreAligned(b, LLVMConstNull(te.vnf32), zp, 4u)
        }
    }
    LLVMBuildBr(b, head)

    LLVMPositionBuilderAtEnd(b, head)
    var biPhi = LLVMBuildPhi(b, te.types.t_int64, "bi")
    var entryVals <- [LLVMConstNull(te.types.t_int64)]
    var entryBlocks <- [entry]
    LLVMAddIncoming(biPhi, entryVals, entryBlocks)
    var more = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, biPhi, nb, "more")
    LLVMBuildCondBr(b, more, body, after)

    LLVMPositionBuilderAtEnd(b, body)
    // B tiles: block bi is a contiguous 512-byte region per group plane (8 k-groups × 16×4)
    var wboff = LLVMBuildMul(b, biPhi, te.types->ConstI64(512ul), "wboff")
    var Bs : LLVMOpaqueValue? [2]
    for (r in range(nt)) {
        var wp2 = LLVMBuildGEP2(b, te.types.t_int8, wplane[r], wboff, "wb{r}")
        Bs[r] = amx_load_b(te, r, wp2, "bt{r}")
    }
    var xoff = LLVMBuildMul(b, biPhi, te.types->ConstI64(32ul), "xoff")
    var As : LLVMOpaqueValue? [2]
    for (ts in range(nt)) {
        var xp2 = LLVMBuildGEP2(b, te.types.t_int8, xbase[ts], xoff, "xa{ts}")
        As[ts] = amx_load_a(te, ts, xp2, n, "at{ts}")
    }
    var bi16 = LLVMBuildMul(b, biPhi, te.types->ConstI64(16ul), "bi16")
    for (r in range(nt)) {
        // ws_vec: the block's 16 group scales, mr-contiguous in the grp plane — one zmm
        var sidx = r == 0 ? bi16 : LLVMBuildAdd(b, bi16, sgoff[r], "")
        var ws = load_scale_vec(te, sg, sidx, "ws{r}")
        for (ts in range(nt)) {
            var cd = amx_dot(te, nt, r, ts, As[ts], Bs[r])
            amx_store(te, nt, r, ts, cd, scratch)
            amx_fold_tile(te, scratch, biPhi, ws, r, ts, ybase, d, xsbase, xbsbase, nb)
        }
    }
    var biNext = LLVMBuildAdd(b, biPhi, te.types->ConstI64(1ul), "binext")
    LLVMBuildBr(b, head)
    var bodyVals <- [biNext]
    var bodyBlocks <- [body]
    LLVMAddIncoming(biPhi, bodyVals, bodyBlocks)

    LLVMPositionBuilderAtEnd(b, after)
    LLVMBuildRetVoid(b)
    return true
}

// fold ONE spilled C tile — tile (r, ts) of k-block `bi`, 16 token rows — into its yp cells:
// cvt(i32 row)·ws·splat(xs[t][bi]) f32-accumulated onto yp (the serial tile's fold order,
// so the one grp4 oracle serves both amx structures). A bias perm lands the −128·Σx bsum on
// the raw i32 rows first (one embedded-broadcast vpaddd per row — "keep tilezero": the
// correction is fold-stage arithmetic, never an accumulator init). Addressing is RUNNING
// POINTERS off three live bases (ybase/xsbase/xbsbase + row strides) — the previous
// precomputed pointer arrays (64 y rows + 32 xs rows) stayed live across the k-loop and
// spilled: ~140 movq reloads per k-iteration, 28% of the steady loop (2026-07-09 census).
def private amx_fold_tile(var te : TileEmit; var region, bi, ws : LLVMOpaqueValue?; r, ts : int;
                          var ybase, d, xsbase, xbsbase, nb : LLVMOpaqueValue?) {
    let b = te.builder
    // tile row 0: y at (ts·16)·d + r·16, xs/xbs at (ts·16)·nb + bi — then step d / nb per row
    var yoff = LLVMBuildMul(b, d, te.types->ConstI64(uint64(ts * 16)), "")
    if (r != 0) {
        yoff = LLVMBuildAdd(b, yoff, te.types->ConstI64(uint64(r * 16)), "")
    }
    var yrow = LLVMBuildGEP2(b, te.types.t_float, ybase, yoff, "yr{ts}_{r}")
    var xoff = LLVMBuildAdd(b, LLVMBuildMul(b, nb, te.types->ConstI64(uint64(ts * 16)), ""), bi, "")
    var xsp = LLVMBuildGEP2(b, te.types.t_float, xsbase, xoff, "xr{ts}")
    var xbp : LLVMOpaqueValue?
    if (te.bias != 0) {
        xbp = LLVMBuildGEP2(b, te.types.t_int32, xbsbase, xoff, "br{ts}")
    }
    for (t16 in range(16)) {
        let t = ts * 16 + t16
        if (t16 != 0) {   // advance one token row: y by d floats, xs/xbs by nb elements
            yrow = LLVMBuildGEP2(b, te.types.t_float, yrow, d, "yr{t}_{r}")
            xsp = LLVMBuildGEP2(b, te.types.t_float, xsp, nb, "xr{t}")
            if (te.bias != 0) {
                xbp = LLVMBuildGEP2(b, te.types.t_int32, xbp, nb, "br{t}")
            }
        }
        var crp = t16 == 0 ? region : LLVMBuildGEP2(b, te.types.t_int8, region, te.types->ConstI64(uint64(t16 * 64)), "")
        var crow = LLVMBuildLoad2Aligned(b, te.vni32, crp, 64u, "c{t}_{r}")
        if (te.bias != 0) {
            var bsv = LLVMBuildLoad2Aligned(b, te.types.t_int32, xbp, 4u, "bsum{t}")
            crow = LLVMBuildAdd(b, crow, splat_i32(te, bsv, "bss{t}"), "cb{t}_{r}")
        }
        var cf = LLVMBuildSIToFP(b, crow, te.vnf32, "cf{t}_{r}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, xsp, 4u, "q{t}")
        var sq = LLVMBuildFMul(b, ws, splat_f32(te, q, "qs{t}"), "")
        var yv = LLVMBuildLoad2Aligned(b, te.vnf32, yrow, 4u, "")
        LLVMBuildStoreAligned(b, fold_fma(te, cf, sq, yv, "f{t}_{r}"), yrow, 4u)
    }
}

// The software-pipelined TMUL batch tile (slice K I4 — lcpp mmq.cpp's double-buffered C):
// same macro/space contract as emit_amx_tile (tokstep, layout, companions identical), but
// the per-block scale fold is deferred one k-iteration — block bi's TDPBSSD chain spills
// into C[cur] while block bi−1's fold reads C[pre], so the vector ports fold while TMUL
// crunches instead of the whole chain stalling behind every tilestored. Structure: peel
// block 0 (compute-only into buf0), steady-state loop folds bi−1 between bi's tile ops
// (buffer swap via phis), exit block folds the final spill (post-swap, cPre holds it).
def private emit_amx_tile_pipelined(var gc : LlvmCodeCtx; p : TilePerm; f16s : bool) : bool {
    var te = TileEmit(sgF16 = f16s)
    if (!setup_amx_emit(te, gc, p)) return false
    let b = gc.jit.builder
    let nt = p.nrsplit
    let ntiles = nt * nt
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    var head = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "head")
    var body = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "body")
    var after = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "after")

    LLVMPositionBuilderAtEnd(b, entry)
    var yp = LLVMGetParam(gc.impl, 0u)
    var wg = LLVMGetParam(gc.impl, 1u)
    var sg = LLVMGetParam(gc.impl, 2u)
    var xqp = LLVMGetParam(gc.impl, 3u)
    var xsp = LLVMGetParam(gc.impl, 4u)
    var xbsp = LLVMGetParam(gc.impl, 5u)
    var n = LLVMGetParam(gc.impl, 6u)
    var d = LLVMGetParam(gc.impl, 7u)
    var g = LLVMGetParam(gc.impl, 8u)
    var t0 = LLVMGetParam(gc.impl, 9u)
    var nb = LLVMBuildSDiv(b, n, te.types->ConstI64(32ul), "nb")
    var col = LLVMBuildMul(b, g, te.types->ConstI64(16ul), "col")
    // C spill: TWO ntiles-deep tile regions — the double buffer the fold deferral swaps over
    var scratch = LLVMBuildArrayAlloca(b, te.types.t_int8, te.types->ConstI64(uint64(2 * ntiles * 1024)), "cspill")
    LLVMSetAlignment(scratch, 64u)
    var buf1 = LLVMBuildGEP2(b, te.types.t_int8, scratch, te.types->ConstI64(uint64(ntiles * 1024)), "buf1")
    var n16 = LLVMBuildMul(b, n, te.types->ConstI64(16ul), "n16")
    var nb16 = LLVMBuildMul(b, nb, te.types->ConstI64(16ul), "nb16")
    var wplane : LLVMOpaqueValue? [2]     // adjacent row-group planes (+16·n each)
    var sgoff : LLVMOpaqueValue? [2]      // their scale-region offsets (+16·nb floats)
    var xbase : LLVMOpaqueValue? [2]      // A tile activation bases (rows t0 + ts·16 ..)
    for (r in range(nt)) {
        wplane[r] = r == 0 ? wg : LLVMBuildGEP2(b, te.types.t_int8, wg, n16, "wplane{r}")
        sgoff[r] = r == 0 ? LLVMConstNull(te.types.t_int64) : nb16
    }
    for (ts in range(nt)) {
        var trow = ts == 0 ? t0 : LLVMBuildAdd(b, t0, te.types->ConstI64(uint64(ts * 16)), "")
        xbase[ts] = LLVMBuildGEP2(b, te.types.t_int8, xqp, LLVMBuildMul(b, trow, n, ""), "xbase{ts}")
    }
    // fold bases: y rows start at t0·d + col, xs/xbs rows at t0·nb — the fold walks them with
    // running pointers (see amx_fold_tile: a precomputed 64/32-entry pointer array is live
    // across the k-loop and spills). Zero-init walks y with the same running pointer.
    var ybase = LLVMBuildGEP2(b, te.types.t_float, yp, LLVMBuildAdd(b, LLVMBuildMul(b, t0, d, ""), col, ""), "ybase")
    var xsbase = LLVMBuildGEP2(b, te.types.t_float, xsp, LLVMBuildMul(b, t0, nb, ""), "xsbase")
    var xbsbase : LLVMOpaqueValue?
    if (te.bias != 0) {
        xbsbase = LLVMBuildGEP2(b, te.types.t_int32, xbsp, LLVMBuildMul(b, t0, nb, ""), "xbsbase")
    }
    var zrow = ybase
    for (t in range(16 * nt)) {
        if (t != 0) {
            zrow = LLVMBuildGEP2(b, te.types.t_float, zrow, d, "zr{t}")
        }
        for (r in range(nt)) {
            var zp = r == 0 ? zrow : LLVMBuildGEP2(b, te.types.t_float, zrow, te.types->ConstI64(uint64(r * 16)), "")
            LLVMBuildStoreAligned(b, LLVMConstNull(te.vnf32), zp, 4u)
        }
    }
    // peel: block 0's TMUL chain into buf0 (its fold runs in the first loop iteration)
    var Bs : LLVMOpaqueValue? [2]
    var As : LLVMOpaqueValue? [2]
    for (r in range(nt)) {
        Bs[r] = amx_load_b(te, r, wplane[r], "bt0{r}")
    }
    for (ts in range(nt)) {
        As[ts] = amx_load_a(te, ts, xbase[ts], n, "at0{ts}")
    }
    for (r in range(nt)) {
        for (ts in range(nt)) {
            var cd = amx_dot(te, nt, r, ts, As[ts], Bs[r])
            let idx = r * nt + ts
            var reg = idx == 0 ? scratch : LLVMBuildGEP2(b, te.types.t_int8, scratch, te.types->ConstI64(uint64(idx * 1024)), "")
            amx_store(te, nt, r, ts, cd, reg)
        }
    }
    LLVMBuildBr(b, head)

    LLVMPositionBuilderAtEnd(b, head)
    var biPhi = LLVMBuildPhi(b, te.types.t_int64, "bi")
    var cPrePhi = LLVMBuildPhi(b, te.types->LLVMVoidPtrType(), "cpre")
    var cCurPhi = LLVMBuildPhi(b, te.types->LLVMVoidPtrType(), "ccur")
    var entryVals <- [te.types->ConstI64(1ul)]
    var entryBlocks <- [entry]
    LLVMAddIncoming(biPhi, entryVals, entryBlocks)
    var preEntryVals <- [scratch]
    LLVMAddIncoming(cPrePhi, preEntryVals, entryBlocks)
    var curEntryVals <- [buf1]
    LLVMAddIncoming(cCurPhi, curEntryVals, entryBlocks)
    var more = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, biPhi, nb, "more")
    LLVMBuildCondBr(b, more, body, after)

    LLVMPositionBuilderAtEnd(b, body)
    var ii = LLVMBuildSub(b, biPhi, te.types->ConstI64(1ul), "ii")
    var ii16 = LLVMBuildMul(b, ii, te.types->ConstI64(16ul), "ii16")
    // B tiles: block bi is a contiguous 512-byte region per group plane (8 k-groups × 16×4)
    var wboff = LLVMBuildMul(b, biPhi, te.types->ConstI64(512ul), "wboff")
    for (r in range(nt)) {
        var wp2 = LLVMBuildGEP2(b, te.types.t_int8, wplane[r], wboff, "wb{r}")
        Bs[r] = amx_load_b(te, r, wp2, "bt{r}")
    }
    var xoff = LLVMBuildMul(b, biPhi, te.types->ConstI64(32ul), "xoff")
    for (ts in range(nt)) {
        var xp2 = LLVMBuildGEP2(b, te.types.t_int8, xbase[ts], xoff, "xa{ts}")
        As[ts] = amx_load_a(te, ts, xp2, n, "at{ts}")
    }
    for (r in range(nt)) {
        // block bi−1's ws vector — the deferred fold's group scales (one zmm per r plane)
        var sidx = r == 0 ? ii16 : LLVMBuildAdd(b, ii16, sgoff[r], "")
        var ws = load_scale_vec(te, sg, sidx, "ws{r}")
        for (ts in range(nt)) {
            let idx = r * nt + ts
            // the deferral: fold tile (r, ts) of block bi−1 from C[pre] before this chain's
            // dot — vector ports work while the TMUL chain owns block bi
            var preReg = idx == 0 ? cPrePhi : LLVMBuildGEP2(b, te.types.t_int8, cPrePhi, te.types->ConstI64(uint64(idx * 1024)), "")
            amx_fold_tile(te, preReg, ii, ws, r, ts, ybase, d, xsbase, xbsbase, nb)
            var cd = amx_dot(te, nt, r, ts, As[ts], Bs[r])
            var curReg = idx == 0 ? cCurPhi : LLVMBuildGEP2(b, te.types.t_int8, cCurPhi, te.types->ConstI64(uint64(idx * 1024)), "")
            amx_store(te, nt, r, ts, cd, curReg)
        }
    }
    var biNext = LLVMBuildAdd(b, biPhi, te.types->ConstI64(1ul), "binext")
    LLVMBuildBr(b, head)
    var bodyVals <- [biNext]
    var bodyBlocks <- [body]
    LLVMAddIncoming(biPhi, bodyVals, bodyBlocks)
    var preBodyVals <- [cCurPhi]      // the swap: last-written buffer becomes next pre
    LLVMAddIncoming(cPrePhi, preBodyVals, bodyBlocks)
    var curBodyVals <- [cPrePhi]
    LLVMAddIncoming(cCurPhi, curBodyVals, bodyBlocks)

    LLVMPositionBuilderAtEnd(b, after)
    // final fold: block nb−1's spill — post-swap (and for nb==1, straight off the peel)
    // cPre holds the last-written buffer
    var iiF = LLVMBuildSub(b, nb, te.types->ConstI64(1ul), "iif")
    var iiF16 = LLVMBuildMul(b, iiF, te.types->ConstI64(16ul), "iif16")
    for (r in range(nt)) {
        var sidx = r == 0 ? iiF16 : LLVMBuildAdd(b, iiF16, sgoff[r], "")
        var ws = load_scale_vec(te, sg, sidx, "wsf{r}")
        for (ts in range(nt)) {
            let idx = r * nt + ts
            var preReg = idx == 0 ? cPrePhi : LLVMBuildGEP2(b, te.types.t_int8, cPrePhi, te.types->ConstI64(uint64(idx * 1024)), "")
            amx_fold_tile(te, preReg, iiF, ws, r, ts, ybase, d, xsbase, xbsbase, nb)
        }
    }
    LLVMBuildRetVoid(b)
    return true
}

// the tile emitter shared by the f32 and f16-scale entries: f16s swaps ONLY the scale-fold
// load (load_scale_vec) — same lattice, same fold order, same shared decline rails
def private tile_gen_impl(var gc : LlvmCodeCtx; f16s : bool) : bool {
    // decline on a foreign signature, and on every shared rail (perm_declines — the layout
    // companion declines in lockstep): the reference body compiles instead
    if (!is_tile_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false
    if (dot_kind(p.dotPrim) == DOT_AMX) {
        return p.pipe != 0 ? emit_amx_tile_pipelined(gc, p, f16s) : emit_amx_tile(gc, p, f16s)
    }

    var te = TileEmit(sgF16 = f16s)
    if (!setup_tile_emit(te, gc, p, false)) return false

    let b = gc.jit.builder
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")

    // entry: per-token activation/scale bases; nb = n / 32
    LLVMPositionBuilderAtEnd(b, entry)
    var sa = SliceArgs(gc_impl = gc.impl, ctx = gc.jit.ctx, kstep = p.kstep)
    sa.yp = LLVMGetParam(gc.impl, 0u)
    te.wg = LLVMGetParam(gc.impl, 1u)
    te.sg = LLVMGetParam(gc.impl, 2u)
    let xqp = LLVMGetParam(gc.impl, 3u)
    let xsp = LLVMGetParam(gc.impl, 4u)
    let xbsp = LLVMGetParam(gc.impl, 5u)
    let n = LLVMGetParam(gc.impl, 6u)
    sa.d = LLVMGetParam(gc.impl, 7u)
    sa.g = LLVMGetParam(gc.impl, 8u)
    sa.t0 = LLVMGetParam(gc.impl, 9u)
    sa.nb = LLVMBuildSDiv(b, n, te.types->ConstI64(32ul), "nb")
    for (tk in range(4)) {
        var tRow = LLVMBuildAdd(b, sa.t0, te.types->ConstI64(uint64(tk)), "")
        te.x[tk] = LLVMBuildGEP2(b, te.types.t_int8, xqp, LLVMBuildMul(b, tRow, n, ""), "x{tk}")
        te.xs[tk] = LLVMBuildGEP2(b, te.types.t_float, xsp, LLVMBuildMul(b, tRow, sa.nb, ""), "xs{tk}")
        if (te.bias != 0) {
            // the bsums plane (−128·Σx i32 per (token, block)) — the wrapper builds it for
            // biased stamps; unbiased stamps never touch the parameter
            te.xbs[tk] = LLVMBuildGEP2(b, te.types.t_int32, xbsp, LLVMBuildMul(b, tRow, sa.nb, ""), "xbs{tk}")
        }
    }

    // one k-loop slice per nrsplit tokens (nrsplit=4: single slice, the M2 shape)
    var pred = entry
    var tokBase = 0
    while (tokBase < 4) {
        pred = emit_slice(te, sa, pred, tokBase, p.nrsplit, tokBase == 0 ? "" : "_{tokBase}")
        tokBase += p.nrsplit
    }
    LLVMPositionBuilderAtEnd(b, pred)
    LLVMBuildRetVoid(b)
    return true
}

def private tile_gen(var gc : LlvmCodeCtx) : bool => tile_gen_impl(gc, false)

// the wscale_f16 tile twin (stamped as a companion with the SAME perm): the binary16 group-
// scale plane, widened in the fold load — bit-identical over the plane the halfwords widen to
def private tile_s16_gen(var gc : LlvmCodeCtx) : bool => tile_gen_impl(gc, true)

def private is_layout_signature(fn : Function const?) : bool {
    return empty(fn.arguments) && fn.result.baseType == Type.tInt
}

// the layout half of the two-function stamp: `() : int` returning the perm's repack
// interleave (mr) — the runtime repack asks it which layout the stamped tile reads. Declines
// via the SAME perm_declines as tile_gen, so a perm the tile can't emit keeps the grp4
// reference pair on both sides.
def private layout_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_layout_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    LLVMPositionBuilderAtEnd(gc.jit.builder, entry)
    LLVMBuildRet(gc.jit.builder, gc.jit.types->ConstI32(uint64(q8q8_repack_type(p.mr).interleave)))
    return true
}

// the wbias sixth of the stamp: `() : int` returning the perm's weight-plane bias (128 for
// the bias128 vpdpbusd perms, 0 otherwise) — the runtime repack and the mx4->Q8 expand ask
// it how the plane bytes are baked. Declines via the SAME perm_declines: a declined perm
// keeps the unbiased grp4 reference pair on every side.
def private wbias_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_layout_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    LLVMPositionBuilderAtEnd(gc.jit.builder, entry)
    LLVMBuildRet(gc.jit.builder, gc.jit.types->ConstI32(uint64(p.bias)))
    return true
}

// the kgroup seventh of the stamp (slice J): `() : int` returning the perm's plane kgroup —
// 8 for smmla perms (row-pair × 8-k layout), 4 for every vector-dot perm. The runtime repack,
// the token-tail generic and the mx4→Q8 expand map ask it how the plane groups its k-bytes.
// Declines via the SAME perm_declines: a declined perm keeps the kg4 grp4 reference pair.
def private kgroup_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_layout_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    LLVMPositionBuilderAtEnd(gc.jit.builder, entry)
    LLVMBuildRet(gc.jit.builder, gc.jit.types->ConstI32(uint64(q8q8_repack_type(p.mr, p.bias, kgroup_of(p)).kgroup)))
    return true
}

// the tokstep eighth of the stamp (slice I): `() : int` returning the tokens one tile call
// covers — 16·nrsplit for the amx perms (whose macro also spans tokstep/16 row-groups: amx
// macros are square in tile units), 4 for every vector perm. The batch wrapper walks its
// (token, group) space off it. Declines via the SAME perm_declines: a declined perm keeps
// the 4-token reference contract.
def private tokstep_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_layout_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    LLVMPositionBuilderAtEnd(gc.jit.builder, entry)
    let ts = dot_kind(p.dotPrim) == DOT_AMX ? 16 * p.nrsplit : 4
    LLVMBuildRet(gc.jit.builder, gc.jit.types->ConstI32(uint64(ts)))
    return true
}

def private is_witness_signature(fn : Function const?) : bool {
    return empty(fn.arguments) && fn.result.baseType == Type.tBool
}

// the witness fifth of the stamp: `() : bool` — did the stamped family actually EMIT on this
// target? Reference body returns false; the generated body is `return true`, and it declines
// via the SAME perm_declines as everything else — so "witness true" ⟺ "the whole family is
// generated code". Backend availability reads it at SELECTION time (never [init] — the
// slice C rule): on x64 a declined stamp must not load-select the gen backend, because the
// reference bodies there are the NEON functions' scalar fallbacks — correct but far slower
// than the portable backend.
def private witness_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_witness_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    let b = gc.jit.builder
    LLVMPositionBuilderAtEnd(b, entry)
    if (dot_kind(p.dotPrim) == DOT_AMX) {
        // TMUL executes only after the per-process XTILEDATA grant, so the enable IS the
        // witness: syscall(SYS_arch_prctl=158, ARCH_REQ_XCOMP_PERM=0x1023, XFEATURE_XTILEDATA
        // =18) == 0 via libc's syscall(2) as a JIT-resolved external symbol (glibc exports no
        // arch_prctl wrapper). Linux-only by construction — perm_declines gated the target OS.
        let mod = LLVMGetGlobalParent(gc.impl)
        var scTy : LLVMOpaqueType?
        var argTypes <- [gc.jit.types.t_int64, gc.jit.types.t_int64, gc.jit.types.t_int64]
        scTy = LLVMFunctionType(gc.jit.types.t_int64, argTypes)
        var sc = LLVMGetNamedFunction(mod, "syscall")
        if (sc == null) {
            sc = LLVMAddFunction(mod, "syscall", scTy)
        }
        var cargs <- [gc.jit.types->ConstI64(158ul), gc.jit.types->ConstI64(0x1023ul), gc.jit.types->ConstI64(18ul)]
        var rc = LLVMBuildCall2(b, scTy, sc, cargs, "xtile")
        var ok = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntEQ, rc, LLVMConstNull(gc.jit.types.t_int64), "ok")
        LLVMBuildRet(b, ok)
    } else {
        LLVMBuildRet(b, LLVMConstInt(gc.jit.types.t_int1, 1ul, 0))
    }
    return true
}

def private is_cfg_signature(fn : Function const?) : bool {
    return empty(fn.arguments) && fn.result.baseType == Type.tVoid
}

// the tile-config companion (slice K I1): `() : void`. For a latch=1 raw-tile perm the body
// LDTILECFGs the family's static 8-tile palette (C tmm0-3 16×64, A tmm4-5 16×32, B tmm6-7
// 8×64 — amx_tmm's plan) — those stamps carry no per-call config and no TILERELEASE, so the
// batch wrapper calls this once per dispatch chunk instead. Every other perm gets a bare
// `ret void`; declines via the SAME perm_declines keep the no-op das reference body.
def private cfg_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_cfg_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    let b = gc.jit.builder
    LLVMPositionBuilderAtEnd(b, entry)
    if (dot_kind(p.dotPrim) == DOT_AMX && p.latch != 0) {
        let mod = LLVMGetGlobalParent(gc.impl)
        var glob = LLVMGetNamedGlobal(mod, "dasllama.amx.tilecfg")
        if (glob == null) {
            // the 64-byte LDTILECFG image: palette 1, colsb u16 at [16+2i], rows u8 at [48+i]
            var cfgb : int[64]
            cfgb[0] = 1
            for (i in range(8)) {
                cfgb[16 + 2 * i] = i == 4 || i == 5 ? 32 : 64
                cfgb[48 + i] = i >= 6 ? 8 : 16
            }
            var elems : array<LLVMOpaqueValue?>
            elems |> reserve(64)
            for (i in range(64)) {
                elems |> push(LLVMConstInt(gc.jit.types.t_int8, uint64(cfgb[i]), 0))
            }
            glob = LLVMAddGlobal(mod, LLVMArrayType(gc.jit.types.t_int8, 64u), "dasllama.amx.tilecfg")
            LLVMSetInitializer(glob, LLVMConstArray(gc.jit.types.t_int8, array_data_ptr(elems), 64u))
            LLVMSetGlobalConstant(glob, 1)
            LLVMSetLinkage(glob, LLVMLinkage.LLVMPrivateLinkage)
            LLVMSetAlignment(glob, 64u)
        }
        var noTypes : array<LLVMOpaqueType?>
        var cfgDecl = LLVMGetIntrinsicDeclaration(mod, LLVMLookupIntrinsicID("llvm.x86.ldtilecfg"), noTypes)
        var cfgArgs <- [gc.jit.types->LLVMVoidPtrType()]
        var cfgTy = LLVMFunctionType(gc.jit.types.t_void, cfgArgs)
        var cargs <- [glob]
        LLVMBuildCall2(b, cfgTy, cfgDecl, cargs, "")
    }
    LLVMBuildRetVoid(b)
    return true
}

def private is_gemv_signature(fn : Function const?) : bool {
    if (length(fn.arguments) != 8 || fn.result.baseType != Type.tVoid) return false
    for (i in range(5)) {
        if (fn.arguments[i]._type.baseType != Type.tPointer) return false
    }
    for (i in range(5, 8)) {
        if (fn.arguments[i]._type.baseType != Type.tInt64) return false
    }
    return true
}

// The GEMV third of the stamp (the nr=1 perm sub-family): a rows-range core with the mm_rows
// slot signature — rows [rb, re) of one region, rb/re multiples of the perm's mr, the group
// loop INSIDE the generated function (one call per dispatch chunk). Per group it is
// emit_slice with a single token and gkstep blocks per K-iteration: emit_block's fresh int
// accumulators per block are the independent dot chains a serial single-token laneq chain
// lacks. Declines via the SAME perm_declines as the tile — the reference body (the grp4
// laneq rows walk) falls back in lockstep with the grp4 reference pair.
def private gemv_gen_impl(var gc : LlvmCodeCtx; f16s : bool) : bool {
    if (!is_gemv_signature(gc.fn)) return false
    let p0 = parse_perm(gc)
    if (perm_declines(gc, p0)) return false
    let p = companion_perm(p0)

    var te = TileEmit(sgF16 = f16s)
    if (!setup_tile_emit(te, gc, p, false)) return false

    let b = gc.jit.builder
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    var ghead = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "ghead")
    var gexit = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "gexit")

    // entry: group range off the row range; d=0/t0=0 turn emit_slice's store offset
    // (tRow*d + col) into the absolute row g*mr
    LLVMPositionBuilderAtEnd(b, entry)
    var sa = SliceArgs(gc_impl = gc.impl, ctx = gc.jit.ctx, kstep = p.gkstep)
    sa.yp = LLVMGetParam(gc.impl, 0u)
    let wp = LLVMGetParam(gc.impl, 1u)
    let sp = LLVMGetParam(gc.impl, 2u)
    te.x[0] = LLVMGetParam(gc.impl, 3u)
    te.xs[0] = LLVMGetParam(gc.impl, 4u)
    let n = LLVMGetParam(gc.impl, 5u)
    let rbv = LLVMGetParam(gc.impl, 6u)
    let rev = LLVMGetParam(gc.impl, 7u)
    sa.nb = LLVMBuildSDiv(b, n, te.types->ConstI64(32ul), "nb")
    sa.d = te.types->ConstI64(0ul)
    sa.t0 = te.types->ConstI64(0ul)
    let mrC = te.types->ConstI64(uint64(te.interleave))
    var g0 = LLVMBuildSDiv(b, rbv, mrC, "g0")
    var g1 = LLVMBuildSDiv(b, rev, mrC, "g1")
    var nonempty = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, g0, g1, "any")
    LLVMBuildCondBr(b, nonempty, ghead, gexit)

    // ghead: group phi + this group's weight/scale bases; the k loop hangs off it as its
    // per-iteration body (emit_slice re-enters with zeroed accumulators each group)
    LLVMPositionBuilderAtEnd(b, ghead)
    var gPhi = LLVMBuildPhi(b, te.types.t_int64, "g")
    var gEntryVals <- [g0]
    var gEntryBlocks <- [entry]
    LLVMAddIncoming(gPhi, gEntryVals, gEntryBlocks)
    sa.g = gPhi
    var gRow = LLVMBuildMul(b, gPhi, mrC, "grow")
    te.wg = LLVMBuildGEP2(b, te.types.t_int8, wp, LLVMBuildMul(b, gRow, n, ""), "wg")
    te.sg = LLVMBuildGEP2(b, f16s ? te.types.t_int16 : te.types.t_float, sp, LLVMBuildMul(b, gRow, sa.nb, ""), "sg")

    var after = emit_slice(te, sa, ghead, 0, 1, "")
    LLVMPositionBuilderAtEnd(b, after)
    var gNext = LLVMBuildAdd(b, gPhi, te.types->ConstI64(1ul), "gnext")
    var more = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, gNext, g1, "more")
    LLVMBuildCondBr(b, more, ghead, gexit)
    var gLoopVals <- [gNext]
    var gLoopBlocks <- [after]
    LLVMAddIncoming(gPhi, gLoopVals, gLoopBlocks)

    LLVMPositionBuilderAtEnd(b, gexit)
    LLVMBuildRetVoid(b)
    return true
}

def private gemv_gen(var gc : LlvmCodeCtx) : bool => gemv_gen_impl(gc, false)

// the wscale_f16 rows-core twin (stamped as a companion with the SAME perm) — see tile_s16_gen
def private gemv_s16_gen(var gc : LlvmCodeCtx) : bool => gemv_gen_impl(gc, true)

// The MXFP4 quarter of the stamp: the same rows-range GEMV as gemv_gen over the
// grp<mr>-interleaved nibble/exponent planes — emit_block_mx4 swaps the weight-load stage for
// LUT dequant (constant LUT; tbl1 on NEON, pshufb on x64) and the scale loads for the
// in-register e8m0 fold; the loop machinery, gkstep knob, and decline rails are shared.
def private mx4_gemv_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_gemv_signature(gc.fn)) return false
    let p0 = parse_perm(gc)
    if (perm_declines(gc, p0)) return false
    let p = companion_perm(p0)

    var te = TileEmit(mx4 = true)
    if (!setup_tile_emit(te, gc, p, true)) return false

    let b = gc.jit.builder
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    var ghead = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "ghead")
    var gexit = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "gexit")

    // entry: group range off the row range; plane strides are nibble n/2 and exponent n/32
    LLVMPositionBuilderAtEnd(b, entry)
    var sa = SliceArgs(gc_impl = gc.impl, ctx = gc.jit.ctx, kstep = p.gkstep)
    sa.yp = LLVMGetParam(gc.impl, 0u)
    let wn = LLVMGetParam(gc.impl, 1u)
    let we = LLVMGetParam(gc.impl, 2u)
    te.x[0] = LLVMGetParam(gc.impl, 3u)
    te.xs[0] = LLVMGetParam(gc.impl, 4u)
    let n = LLVMGetParam(gc.impl, 5u)
    let rbv = LLVMGetParam(gc.impl, 6u)
    let rev = LLVMGetParam(gc.impl, 7u)
    sa.nb = LLVMBuildSDiv(b, n, te.types->ConstI64(32ul), "nb")
    var nrow = LLVMBuildSDiv(b, n, te.types->ConstI64(2ul), "nrow")
    sa.d = te.types->ConstI64(0ul)
    sa.t0 = te.types->ConstI64(0ul)
    let mrC = te.types->ConstI64(uint64(te.interleave))
    var g0 = LLVMBuildSDiv(b, rbv, mrC, "g0")
    var g1 = LLVMBuildSDiv(b, rev, mrC, "g1")
    var nonempty = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, g0, g1, "any")
    LLVMBuildCondBr(b, nonempty, ghead, gexit)

    LLVMPositionBuilderAtEnd(b, ghead)
    var gPhi = LLVMBuildPhi(b, te.types.t_int64, "g")
    var gEntryVals <- [g0]
    var gEntryBlocks <- [entry]
    LLVMAddIncoming(gPhi, gEntryVals, gEntryBlocks)
    sa.g = gPhi
    var gRow = LLVMBuildMul(b, gPhi, mrC, "grow")
    te.wg = LLVMBuildGEP2(b, te.types.t_int8, wn, LLVMBuildMul(b, gRow, nrow, ""), "wg")
    te.sg = LLVMBuildGEP2(b, te.types.t_int8, we, LLVMBuildMul(b, gRow, sa.nb, ""), "eg")

    var after = emit_slice(te, sa, ghead, 0, 1, "")
    LLVMPositionBuilderAtEnd(b, after)
    var gNext = LLVMBuildAdd(b, gPhi, te.types->ConstI64(1ul), "gnext")
    var more = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, gNext, g1, "more")
    LLVMBuildCondBr(b, more, ghead, gexit)
    var gLoopVals <- [gNext]
    var gLoopBlocks <- [after]
    LLVMAddIncoming(gPhi, gLoopVals, gLoopBlocks)

    LLVMPositionBuilderAtEnd(b, gexit)
    LLVMBuildRetVoid(b)
    return true
}

def private is_kq_gemv_signature(fn : Function const?) : bool {
    if (length(fn.arguments) != 9 || fn.result.baseType != Type.tVoid) return false
    for (i in range(6)) {
        if (fn.arguments[i]._type.baseType != Type.tPointer) return false
    }
    for (i in range(6, 9)) {
        if (fn.arguments[i]._type.baseType != Type.tInt64) return false
    }
    return true
}

// The K-quant sixth of the stamp (kq stage 4): rows-range GEMVs over the grp<mr> kq planes —
// (yp, kq, ks, xq, xs, xbs, n, rb, re), rb/re multiples of mr. Same group walk as gemv_gen but
// the block unit is a 256-weight SUPERBLOCK (nb = n/256, kstep pinned 1 — 8 sub-block dot
// chains per unit already feed the ports; gkstep's extra unroll only bloats the body). The
// unpacks are generic IR and the dots ride the existing lattice via kq_dot_lane, so the family
// declines via the SAME perm_declines with NO new rails — witness lockstep holds for free.
def private kq_gemv_gen_impl(var gc : LlvmCodeCtx; fmt : int) : bool {
    if (!is_kq_gemv_signature(gc.fn)) return false
    let p0 = parse_perm(gc)
    if (perm_declines(gc, p0)) return false
    let p = companion_perm(p0)

    var te = TileEmit(kq = fmt)
    if (!setup_tile_emit(te, gc, p, false)) return false

    let b = gc.jit.builder
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    var ghead = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "ghead")
    var gexit = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "gexit")

    // entry: group range off the row range; per-row-per-superblock strides are the disk
    // footprints (the repack only reorders): quants 128/160/192 B, scales 32/32/18 B
    LLVMPositionBuilderAtEnd(b, entry)
    var sa = SliceArgs(gc_impl = gc.impl, ctx = gc.jit.ctx, kstep = 1)
    sa.yp = LLVMGetParam(gc.impl, 0u)
    let kqp = LLVMGetParam(gc.impl, 1u)
    let ksp = LLVMGetParam(gc.impl, 2u)
    te.x[0] = LLVMGetParam(gc.impl, 3u)
    te.xs[0] = LLVMGetParam(gc.impl, 4u)
    te.xbs[0] = LLVMGetParam(gc.impl, 5u)
    let n = LLVMGetParam(gc.impl, 6u)
    let rbv = LLVMGetParam(gc.impl, 7u)
    let rev = LLVMGetParam(gc.impl, 8u)
    sa.nb = LLVMBuildSDiv(b, n, te.types->ConstI64(0x100ul), "nsb")
    var qrow = LLVMBuildMul(b, sa.nb, te.types->ConstI64(uint64(fmt == 4 ? 128 : (fmt == 5 ? 160 : 192))), "qrow")
    var srow = LLVMBuildMul(b, sa.nb, te.types->ConstI64(uint64(fmt == 6 ? 18 : 32)), "srow")
    sa.d = te.types->ConstI64(0ul)
    sa.t0 = te.types->ConstI64(0ul)
    let mrC = te.types->ConstI64(uint64(te.interleave))
    var g0 = LLVMBuildSDiv(b, rbv, mrC, "g0")
    var g1 = LLVMBuildSDiv(b, rev, mrC, "g1")
    var nonempty = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, g0, g1, "any")
    LLVMBuildCondBr(b, nonempty, ghead, gexit)

    LLVMPositionBuilderAtEnd(b, ghead)
    var gPhi = LLVMBuildPhi(b, te.types.t_int64, "g")
    var gEntryVals <- [g0]
    var gEntryBlocks <- [entry]
    LLVMAddIncoming(gPhi, gEntryVals, gEntryBlocks)
    sa.g = gPhi
    var gRow = LLVMBuildMul(b, gPhi, mrC, "grow")
    te.wg = LLVMBuildGEP2(b, te.types.t_int8, kqp, LLVMBuildMul(b, gRow, qrow, ""), "wg")
    te.sg = LLVMBuildGEP2(b, te.types.t_int8, ksp, LLVMBuildMul(b, gRow, srow, ""), "sg")

    var after = emit_slice(te, sa, ghead, 0, 1, "")
    LLVMPositionBuilderAtEnd(b, after)
    var gNext = LLVMBuildAdd(b, gPhi, te.types->ConstI64(1ul), "gnext")
    var more = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, gNext, g1, "more")
    LLVMBuildCondBr(b, more, ghead, gexit)
    var gLoopVals <- [gNext]
    var gLoopBlocks <- [after]
    LLVMAddIncoming(gPhi, gLoopVals, gLoopBlocks)

    LLVMPositionBuilderAtEnd(b, gexit)
    LLVMBuildRetVoid(b)
    return true
}

def private k4_gemv_gen(var gc : LlvmCodeCtx) : bool => kq_gemv_gen_impl(gc, 4)
def private k5_gemv_gen(var gc : LlvmCodeCtx) : bool => kq_gemv_gen_impl(gc, 5)
def private k6_gemv_gen(var gc : LlvmCodeCtx) : bool => kq_gemv_gen_impl(gc, 6)

// Called from llvm_user_modules::register_user_llvm_code_generators — the JIT invokes that in the
// context that reads the registry, so the direct call lands in the right table copy.
[macro_function]
def public register_dasllama_gemm_generators {
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_tile", @@tile_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_layout", @@layout_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_wbias", @@wbias_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_kgroup", @@kgroup_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_tokstep", @@tokstep_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_amx_cfg", @@cfg_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_gemv", @@gemv_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_tile_s16", @@tile_s16_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_gemv_s16", @@gemv_s16_gen)
    register_llvm_code_generator("dasllama_gemm_gen::mx4_gemv", @@mx4_gemv_gen)
    register_llvm_code_generator("dasllama_gemm_gen::k4_gemv", @@k4_gemv_gen)
    register_llvm_code_generator("dasllama_gemm_gen::k5_gemv", @@k5_gemv_gen)
    register_llvm_code_generator("dasllama_gemm_gen::k6_gemv", @@k6_gemv_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_witness", @@witness_gen)
}
