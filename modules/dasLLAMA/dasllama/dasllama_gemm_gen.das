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
//           sign trick, one dot op), "vpdpbssd" (x64 AVX-VNNI-INT8, native s8·s8)
//   width   vector width in bits: 128 (NEON, implied by sdot), 256 (ymm), 512 (zmm)
// Illegal perms decline (return false) and the reference body compiles instead — the decline
// path is the fallback tier; every companion declines in LOCKSTEP (the one shared
// perm_declines), so repacks and kernels fall back to the grp4 reference family together.
// Runs in the llvm-jit context; wired via llvm_user_modules.das. The stubs it generates for
// are dasllama/dasllama_math_gen.das::q8q8_tile_gen, ::q8q8_layout_gen, ::q8q8_gemv_gen and
// ::mx4q8_gemv_gen.

// dot-primitive kinds (TilePerm.dotPrim, parsed once into TileEmit.dotKind)
let DOT_SDOT = 0
let DOT_MADDUBS = 1
let DOT_VPDPBUSD = 2
let DOT_VPDPBSSD = 3

def private dot_kind(prim : string) : int {
    if (prim == "maddubs") return DOT_MADDUBS
    if (prim == "vpdpbusd") return DOT_VPDPBUSD
    if (prim == "vpdpbssd") return DOT_VPDPBSSD
    return DOT_SDOT
}

// the perm vector both generators read off the [llvm_code] annotation args
struct private TilePerm {
    kstep : int = 2
    nrsplit : int = 4
    mr : int = GEMM_REFERENCE_MR
    gkstep : int = 1
    dotPrim : string = "sdot"
    width : int = 128
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
    return p
}

// the ONE decline predicate all four generators share — the tile and its companions must fall
// back together on every rail, or repack and kernel desync (the two-function-stamp contract).
// Rails in order: knob validity, schema, then the per-ISA leg: target arch, width, tier truth
// (cpuid on host targets, DAS_JIT_X64_FORCE_FEATURES-only on cross triples — the emission
// rail), row/vector geometry, vreg budget, dot machinery availability (belt).
def private perm_declines(var gc : LlvmCodeCtx; p : TilePerm) : bool {
    if ((p.kstep != 1 && p.kstep != 2 && p.kstep != 4)
        || (p.nrsplit != 2 && p.nrsplit != 4)
        || (p.gkstep != 1 && p.gkstep != 2 && p.gkstep != 4)
        || (p.mr < 4)) return true
    let rt = q8q8_repack_type(p.mr)
    if (rt.interleave != p.mr || !rt.f32_scales) return true
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
    wg : LLVMOpaqueValue?                // interleaved mr-row weight group base (mx4: nibble plane)
    sg : LLVMOpaqueValue?                // group scales (float x interleave per block; mx4: E8M0 bytes)
    x : LLVMOpaqueValue? [4]             // per-token activation base pointers
    xs : LLVMOpaqueValue? [4]            // per-token activation scale base pointers
    mx4 : bool                           // block emitter: mx4 LUT-dequant instead of Q8 loads
    tbl_decl : LLVMOpaqueValue?          // llvm.aarch64.neon.tbl1 (NEON mx4)
    tbl_ty : LLVMOpaqueType?
    pshuf_decl : LLVMOpaqueValue?        // llvm.x86.avx2.pshuf.b / avx512.pshuf.b.512 (x64 mx4)
    pshuf_ty : LLVMOpaqueType?
    lut : LLVMOpaqueValue?               // the doubled-e2m1 LUT: v16i8 on NEON; broadcast per
                                         // 16-byte lane to vwi8 on x64 (pshufb is per-lane)
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
    if (te.dotKind == DOT_SDOT) {
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
// false keeps -128 defined), hoisted once per weight vector. Null for dot kinds without it.
def private abs_w(var te : TileEmit; var wv : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    if (te.dotKind != DOT_MADDUBS && te.dotKind != DOT_VPDPBUSD) return null
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
    for (kg in range(8)) {
        for (qd in range(rq)) {
            let boff = kg * 4 * te.interleave + qd * (te.width / 8)
            var off = boff == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff)), "")
            wv[kg * rq + qd] = load_vec(te, te.vwi8, te.wg, off, "wv{kg * rq + qd}")
            uw[kg * rq + qd] = abs_w(te, wv[kg * rq + qd], "uw{kg * rq + qd}")
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
    var s4 : LLVMOpaqueValue? [4]
    var sgIdx0 = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave)), "")
    for (qd in range(rq)) {
        var idx = qd == 0 ? sgIdx0 : LLVMBuildAdd(b, sgIdx0, te.types->ConstI64(uint64(qd * te.rv)), "")
        var sgp = LLVMBuildGEP2(b, te.types.t_float, te.sg, idx, qd == 0 ? "sgp" : "sgp{qd}")
        s4[qd] = LLVMBuildLoad2Aligned(b, te.vnf32, sgp, 4u, qd == 0 ? "s4" : "s4{qd}")
    }
    for (i in range(tokCount)) {
        let tk = tokBase + i
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[tk], bi, "qp{tk}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "q{tk}")
        for (qd in range(rq)) {
            var af = LLVMBuildSIToFP(b, a[i * rq + qd], te.vnf32, "af{tk}")
            var m = LLVMBuildFMul(b, af, s4[qd], "")
            m = LLVMBuildFMul(b, m, splat_f32(te, q, "qs{tk}"), "")
            f[i * rq + qd] = LLVMBuildFAdd(b, f[i * rq + qd], m, "f{tk}")
        }
    }
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
            var m = LLVMBuildFMul(b, af, s4[qd], "")
            m = LLVMBuildFMul(b, m, splat_f32(te, q, "qs{tk}"), "")
            f[i * rq + qd] = LLVMBuildFAdd(b, f[i * rq + qd], m, "f{tk}")
        }
    }
}

// block-emitter dispatch: the slice/loop machinery is quant-agnostic
def private emit_one_block(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    if (te.mx4) {
        emit_block_mx4(te, bi, f, tokBase, tokCount)
    } else {
        emit_block(te, bi, f, tokBase, tokCount)
    }
}

def private is_tile_signature(fn : Function const?) : bool {
    if (length(fn.arguments) != 9 || fn.result.baseType != Type.tVoid) return false
    for (i in range(5)) {
        if (fn.arguments[i]._type.baseType != Type.tPointer) return false
    }
    for (i in range(5, 9)) {
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
    let rt = q8q8_repack_type(p.mr)
    te.builder = gc.jit.builder
    te.types = gc.jit.types
    te.interleave = rt.interleave
    te.dotKind = dot_kind(p.dotPrim)
    te.width = te.dotKind == DOT_SDOT ? 128 : p.width
    te.rv = te.width / 32
    te.rq = rt.interleave / te.rv
    te.v16i8 = LLVMVectorType(te.types.t_int8, 16u)
    te.v4i32 = te.types->LLVMInt4Type()
    te.vwi8 = LLVMVectorType(te.types.t_int8, uint(te.width / 8))
    te.vni32 = LLVMVectorType(te.types.t_int32, uint(te.rv))
    te.vnf32 = LLVMVectorType(te.types.t_float, uint(te.rv))
    let mod = LLVMGetGlobalParent(gc.impl)
    if (te.dotKind == DOT_SDOT) {
        let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
        var declTypes <- [te.vni32, te.v16i8]
        te.sdot_decl = LLVMGetIntrinsicDeclaration(mod, id, declTypes)
        if (te.sdot_decl == null) return false      // no NEON dotprod on this target: decline
        var fnArgTypes <- [te.vni32, te.v16i8, te.v16i8]
        te.sdot_ty = LLVMFunctionType(te.vni32, fnArgTypes)
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
        if (te.dotKind != DOT_VPDPBSSD) {
            // the sign-trick machinery (the proven dot32/dot64 emitter chains): |w| via
            // generic llvm.abs, sign apply via VPSIGNB at 256 (compare+negate+select at 512
            // — emitted inline in dot_lane, no decl needed)
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

def private tile_gen(var gc : LlvmCodeCtx) : bool {
    // decline on a foreign signature, and on every shared rail (perm_declines — the layout
    // companion declines in lockstep): the reference body compiles instead
    if (!is_tile_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false

    var te = TileEmit()
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
    let n = LLVMGetParam(gc.impl, 5u)
    sa.d = LLVMGetParam(gc.impl, 6u)
    sa.g = LLVMGetParam(gc.impl, 7u)
    sa.t0 = LLVMGetParam(gc.impl, 8u)
    sa.nb = LLVMBuildSDiv(b, n, te.types->ConstI64(32ul), "nb")
    for (tk in range(4)) {
        var tRow = LLVMBuildAdd(b, sa.t0, te.types->ConstI64(uint64(tk)), "")
        te.x[tk] = LLVMBuildGEP2(b, te.types.t_int8, xqp, LLVMBuildMul(b, tRow, n, ""), "x{tk}")
        te.xs[tk] = LLVMBuildGEP2(b, te.types.t_float, xsp, LLVMBuildMul(b, tRow, sa.nb, ""), "xs{tk}")
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
def private gemv_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_gemv_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false

    var te = TileEmit()
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
    te.sg = LLVMBuildGEP2(b, te.types.t_float, sp, LLVMBuildMul(b, gRow, sa.nb, ""), "sg")

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

// The MXFP4 quarter of the stamp: the same rows-range GEMV as gemv_gen over the
// grp<mr>-interleaved nibble/exponent planes — emit_block_mx4 swaps the weight-load stage for
// LUT dequant (constant LUT; tbl1 on NEON, pshufb on x64) and the scale loads for the
// in-register e8m0 fold; the loop machinery, gkstep knob, and decline rails are shared.
def private mx4_gemv_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_gemv_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false

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

// Called from llvm_user_modules::register_user_llvm_code_generators — the JIT invokes that in the
// context that reads the registry, so the direct call lands in the right table copy.
[macro_function]
def public register_dasllama_gemm_generators {
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_tile", @@tile_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_layout", @@layout_gen)
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_gemv", @@gemv_gen)
    register_llvm_code_generator("dasllama_gemm_gen::mx4_gemv", @@mx4_gemv_gen)
}
