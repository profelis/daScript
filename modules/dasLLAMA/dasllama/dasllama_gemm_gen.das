options gen2
options indenting = 4

module dasllama_gemm_gen shared private

require llvm/daslib/llvm_boost
require llvm/daslib/llvm_jit_code
require llvm/daslib/llvm_jit_common
require daslib/ast_boost
require dasllama/dasllama_gemm_schema

// The perm-parameterized Q8 GEMM tile generator (gemm_generator_plan.md part 3, promoted from
// the M2 hand perm): emits the laneq mr-row x 4-token register tile as LLVM IR — dot=sdot
// (indexed, via target intrinsic + lane shuffle per the M1 experiment), width=128,
// repack=grp<mr> (f32 scales, strides derived from q8q8_repack_type so kernel and repack
// cannot desync), acc=i32reg, scale=block_fold, load=bcast_x. Knobs read from the [llvm_code]
// annotation args (stamped by the [tune] macro; defaults = the M2 perm, kstep=2 nrsplit=4):
//   kstep   blocks per main-loop iteration (1|2|4); the remainder is a chain of conditional
//           single blocks, so kstep=2 reproduces the M2 CFG exactly
//   nrsplit tokens per accumulator slice (4|2); the 4-token call contract is fixed — nrsplit=2
//           runs the k-loop twice over half the tokens (halves live accumulators)
//   mr      rows per interleave group (4|8: a positive multiple of 4 — the sdot lane
//           structure — inside the q-reg budget); the layout companion (q8q8_layout below)
//           reports the same mr to the runtime repack
//   gkstep  the GEMV companion's blocks per K-iteration (1|2|4) — fresh int accumulators per
//           block give the single-token loop the independent sdot chains a serial laneq
//           chain lacks; the tile ignores it (its K knob is kstep)
//   dot     dot primitive; only "sdot" has an emitter on this (NEON) leg
// Illegal perms decline (return false) and the reference body compiles instead — the decline
// path is the fallback tier; every companion declines in LOCKSTEP (the one shared
// perm_declines), so repacks and kernels fall back to the grp4 reference family together.
// Runs in the llvm-jit context; wired via llvm_user_modules.das. The stubs it generates for
// are dasllama/dasllama_math_gen.das::q8q8_tile_gen, ::q8q8_layout_gen, ::q8q8_gemv_gen and
// ::mx4q8_gemv_gen.

// the perm vector both generators read off the [llvm_code] annotation args
struct private TilePerm {
    kstep : int = 2
    nrsplit : int = 4
    mr : int = GEMM_REFERENCE_MR
    gkstep : int = 1
    dotPrim : string = "sdot"
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
    return p
}

// the ONE decline predicate both generators share — the tile and its layout companion must
// fall back together on every rail, or repack and kernel desync (the two-function-stamp
// contract). Rails in order: ISA, per-ISA dot emitter, illegal perm values, sdot lane
// structure (4 rows per v4i32 accumulator), q-reg budget (weights 2*mr + acc nrsplit*mr/4 +
// activations 2*nrsplit + 2 scratch), schema, target dotprod availability.
def private perm_declines(var gc : LlvmCodeCtx; p : TilePerm) : bool {
    if ((!g_target_is_aarch64)
        || (p.dotPrim != "sdot")
        || (p.kstep != 1 && p.kstep != 2 && p.kstep != 4)
        || (p.nrsplit != 2 && p.nrsplit != 4)
        || (p.gkstep != 1 && p.gkstep != 2 && p.gkstep != 4)
        || (p.mr < 4 || p.mr % 4 != 0)
        || (2 * p.mr + p.nrsplit * p.mr / 4 + 2 * p.nrsplit + 2 > 32)) return true
    let rt = q8q8_repack_type(p.mr)
    if (rt.interleave != p.mr || !rt.f32_scales) return true
    let mod = LLVMGetGlobalParent(gc.impl)
    var v16i8 = LLVMVectorType(gc.jit.types.t_int8, 16u)
    let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
    var declTypes <- [gc.jit.types->LLVMInt4Type(), v16i8]
    if (LLVMGetIntrinsicDeclaration(mod, id, declTypes) == null) return true
    // the mx4 companion's dequant primitive — part of the shared predicate so the mx4 gemv
    // can never fall to its grp4 reference body while the layout stamps a different mr
    let tblId = LLVMLookupIntrinsicID("llvm.aarch64.neon.tbl1")
    var tblTypes <- [v16i8]
    return LLVMGetIntrinsicDeclaration(mod, tblId, tblTypes) == null
}

// emission context threaded through the helpers: builder/types + the per-function value handles
struct private TileEmit {
    builder : LLVMOpaqueBuilder?
    types : PrimitiveTypes?
    v16i8 : LLVMOpaqueType?
    v4i32 : LLVMOpaqueType?
    v4f32 : LLVMOpaqueType?
    sdot_decl : LLVMOpaqueValue?
    sdot_ty : LLVMOpaqueType?
    interleave : int                     // rows per group (q8q8_repack_type(mr).interleave)
    rq : int                             // row quads per group (mr / 4): accumulators per token
    wg : LLVMOpaqueValue?                // interleaved mr-row weight group base (mx4: nibble plane)
    sg : LLVMOpaqueValue?                // group scales (float x interleave per block; mx4: E8M0 bytes)
    x : LLVMOpaqueValue? [4]             // per-token activation base pointers
    xs : LLVMOpaqueValue? [4]            // per-token activation scale base pointers
    mx4 : bool                           // block emitter: mx4 tbl-dequant instead of Q8 loads
    tbl_decl : LLVMOpaqueValue?          // llvm.aarch64.neon.tbl1 (mx4 only)
    tbl_ty : LLVMOpaqueType?
    lut : LLVMOpaqueValue?               // the doubled-e2m1 LUT as a constant v16i8 (mx4 only)
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

def private load_v16i8(var te : TileEmit; var base, off : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    var p = LLVMBuildGEP2(te.builder, te.types.t_int8, base, off, name)
    return LLVMBuildLoad2Aligned(te.builder, te.v16i8, p, 1u, name)
}

def private splat_f32(var te : TileEmit; var v : LLVMOpaqueValue?; name : string) : LLVMOpaqueValue? {
    var one = LLVMBuildInsertElement(te.builder, LLVMGetUndef(te.v4f32), v, te.types->ConstI32(0ul), "")
    return LLVMBuildShuffleVector(te.builder, te.types, one, one, [0, 0, 0, 0], name)
}

// one 32-k block for tokens [tokBase, tokBase+tokCount): 2*mr shared weight vectors x tokens =
// tokCount*mr*2 indexed sdots at full width, then the per-block scale fold f[acc] +=
// float4(a[acc]) * s4[qd] * splat(q[i]) — the exact op order of the hand template
// dot_q8q8_laneq4x4_template, so fast-math contraction sees the same input (and for mr=4 the
// exact M2 instruction sequence). Accumulator index = token * rq + row-quad; the per-quad
// splat re-emission is byte-identical, so GVN folds it to one. Weight/scale strides come off
// te.interleave — the q8q8_repack_type derivation: dword-group kg of block bi holds mr rows x
// 4 k-bytes, quad qd's v16i8 at bi*mr*32 + kg*4*mr + qd*16.
def private emit_block(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    let b = te.builder
    let rq = te.rq
    var wb = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave * 0x20)), "wb")
    var xb = LLVMBuildMul(b, bi, te.types->ConstI64(0x20ul), "xb")
    var wv : LLVMOpaqueValue? [16]
    for (kg in range(8)) {
        for (qd in range(rq)) {
            let boff = kg * 4 * te.interleave + qd * 16
            var off = boff == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff)), "")
            wv[kg * rq + qd] = load_v16i8(te, te.wg, off, "wv{kg * rq + qd}")
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
        a[i] = LLVMConstNull(te.v4i32)
    }
    for (l in range(4)) {           // chunk 0 (k 0..15): lane l of each token vs shared weight vectors
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = sdot_lane(te, a[i * rq + qd], wv[l * rq + qd], xv0[i], l)
            }
        }
    }
    for (l in range(4)) {           // chunk 1 (k 16..31)
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = sdot_lane(te, a[i * rq + qd], wv[(4 + l) * rq + qd], xv1[i], l)
            }
        }
    }
    var s4 : LLVMOpaqueValue? [4]
    var sgIdx0 = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave)), "")
    for (qd in range(rq)) {
        var idx = qd == 0 ? sgIdx0 : LLVMBuildAdd(b, sgIdx0, te.types->ConstI64(uint64(qd * 4)), "")
        var sgp = LLVMBuildGEP2(b, te.types.t_float, te.sg, idx, qd == 0 ? "sgp" : "sgp{qd}")
        s4[qd] = LLVMBuildLoad2Aligned(b, te.v4f32, sgp, 4u, qd == 0 ? "s4" : "s4{qd}")
    }
    for (i in range(tokCount)) {
        let tk = tokBase + i
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[tk], bi, "qp{tk}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "q{tk}")
        for (qd in range(rq)) {
            var af = LLVMBuildSIToFP(b, a[i * rq + qd], te.v4f32, "af{tk}")
            var m = LLVMBuildFMul(b, af, s4[qd], "")
            m = LLVMBuildFMul(b, m, splat_f32(te, q, "qs{tk}"), "")
            f[i * rq + qd] = LLVMBuildFAdd(b, f[i * rq + qd], m, "f{tk}")
        }
    }
}

def private splat16_i8(te : TileEmit; v : int) : LLVMOpaqueValue? {
    var elems <- [for (_i in range(16)); LLVMConstInt(te.types.t_int8, uint64(v & 255), 0)]
    return LLVMConstVector(array_data_ptr(elems), 16u)
}

def private splat4_i32(te : TileEmit; v : int) : LLVMOpaqueValue? {
    var elems <- [for (_i in range(4)); LLVMConstInt(te.types.t_int32, uint64(v), 0)]
    return LLVMConstVector(array_data_ptr(elems), 4u)
}

// one 32-k block, MXFP4 form (dot=mx4): per row quad per dword-group j, ONE v16i8 nibble load
// feeds tbl-lo (k j*4..j*4+3, the LUT baked as a constant vector) and tbl-hi (k j*4+16..+19) —
// 4*rq loads + 8*rq tbl replace the Q8 block's 8*rq weight loads; the sdot lattice and the
// per-block fold are the Q8 emitter's, with the scale computed in-register from mr E8M0 bytes:
// bits = e < 2 ? 0x00200000 << e : (e - 1) << 23 (e8m0_half's exact bit trick, vectorized per
// quad; the not-taken shl-by-(e-1) arm at e=0 is poison LLVM's select never selects).
// one 32-k block, MXFP4 form (dot=mx4): per row quad per dword-group j, ONE v16i8 nibble load
// feeds tbl-lo (k j*4..j*4+3, the LUT baked as a constant vector) and tbl-hi (k j*4+16..+19) —
// 4*rq loads + 8*rq tbl replace the Q8 block's 8*rq weight loads; the sdot lattice and the
// per-block fold are the Q8 emitter's, with the scale computed in-register from mr E8M0 bytes:
// bits = e < 2 ? 0x00200000 << e : (e - 1) << 23 (e8m0_half's exact bit trick, vectorized per
// quad; the not-taken shl-by-(e-1) arm at e=0 is poison LLVM's select never selects).
def private emit_block_mx4(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [8]; tokBase, tokCount : int) {
    let b = te.builder
    let rq = te.rq
    var wb = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave * 16)), "wb")
    var xb = LLVMBuildMul(b, bi, te.types->ConstI64(0x20ul), "xb")
    var wlo : LLVMOpaqueValue? [8]
    var whi : LLVMOpaqueValue? [8]
    for (j in range(4)) {
        for (qd in range(rq)) {
            let boff = j * 4 * te.interleave + qd * 16
            var off = boff == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(boff)), "")
            var nv = load_v16i8(te, te.wg, off, "nv{j * rq + qd}")
            var loIdx = LLVMBuildAnd(b, nv, splat16_i8(te, 15), "nib.lo")
            var hiIdx = LLVMBuildLShr(b, nv, splat16_i8(te, 4), "nib.hi")
            var loArgs <- [te.lut, loIdx]
            wlo[j * rq + qd] = LLVMBuildCall2(b, te.tbl_ty, te.tbl_decl, loArgs, "wlo{j * rq + qd}")
            var hiArgs <- [te.lut, hiIdx]
            whi[j * rq + qd] = LLVMBuildCall2(b, te.tbl_ty, te.tbl_decl, hiArgs, "whi{j * rq + qd}")
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
        a[i] = LLVMConstNull(te.v4i32)
    }
    for (l in range(4)) {           // chunk 0 (k 0..15): low-nibble weights
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = sdot_lane(te, a[i * rq + qd], wlo[l * rq + qd], xv0[i], l)
            }
        }
    }
    for (l in range(4)) {           // chunk 1 (k 16..31): high-nibble weights
        for (i in range(tokCount)) {
            for (qd in range(rq)) {
                a[i * rq + qd] = sdot_lane(te, a[i * rq + qd], whi[l * rq + qd], xv1[i], l)
            }
        }
    }
    var v4i8 = LLVMVectorType(te.types.t_int8, 4u)
    var s4 : LLVMOpaqueValue? [4]
    var sgIdx0 = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave)), "")
    for (qd in range(rq)) {
        var idx = qd == 0 ? sgIdx0 : LLVMBuildAdd(b, sgIdx0, te.types->ConstI64(uint64(qd * 4)), "")
        var egp = LLVMBuildGEP2(b, te.types.t_int8, te.sg, idx, qd == 0 ? "egp" : "egp{qd}")
        var ev = LLVMBuildLoad2Aligned(b, v4i8, egp, 1u, qd == 0 ? "e4" : "e4{qd}")
        var e32 = LLVMBuildZExt(b, ev, te.v4i32, "")
        var lt2 = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntULT, e32, splat4_i32(te, 2), "")
        var loBits = LLVMBuildShl(b, splat4_i32(te, int(0x00200000)), e32, "")
        var hiBits = LLVMBuildShl(b, LLVMBuildSub(b, e32, splat4_i32(te, 1), ""), splat4_i32(te, 23), "")
        var bits = LLVMBuildSelect(b, lt2, loBits, hiBits, "")
        // NOTE: the name is hoisted — a TERNARY string fed straight to a raw extern's
        // `string implicit` param SIGSEGVs the compiler (plain das wrappers are fine)
        let s4name = qd == 0 ? "s4" : "s4{qd}"
        s4[qd] = LLVMBuildBitCast(b, bits, te.v4f32, s4name)
    }
    for (i in range(tokCount)) {
        let tk = tokBase + i
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[tk], bi, "qp{tk}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "q{tk}")
        for (qd in range(rq)) {
            var af = LLVMBuildSIToFP(b, a[i * rq + qd], te.v4f32, "af{tk}")
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
// per-token v4f32 stores (one per row quad). `pred` must be terminator-free; returns the
// slice's merge block (also terminator-free). Main loop runs kstep blocks per iteration; the
// remainder is a chain of kstep-1 conditional single blocks — for kstep=2 this is head/body/
// tail_check/tail_body/after, the exact M2 CFG. Accumulator arrays hold tokCount*rq entries
// (token-major), max 4 tokens x 2 quads under the q-reg budget.
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
        fPhi[i] = LLVMBuildPhi(b, te.v4f32, "fphi{tokBase + i / te.rq}")
    }
    var entryValsBi <- [LLVMConstNull(te.types.t_int64)]
    var entryBlocks <- [pred]
    LLVMAddIncoming(biPhi, entryValsBi, entryBlocks)
    for (i in range(nacc)) {
        var zv <- [LLVMConstNull(te.v4f32)]
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

    // after: merge phis (grouped first — verifier rule), then one v4f32 store per token per
    // row quad (cols g*interleave .. +mr-1 are contiguous floats)
    LLVMPositionBuilderAtEnd(b, after)
    var fF : LLVMOpaqueValue? [8]
    for (i in range(nacc)) {
        fF[i] = LLVMBuildPhi(b, te.v4f32, "ff{tokBase + i / te.rq}")
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
            var yoff = qd == 0 ? yoffBase : LLVMBuildAdd(b, yoffBase, te.types->ConstI64(uint64(qd * 4)), "")
            var yptr = LLVMBuildGEP2(b, te.types.t_float, sa.yp, yoff, qd == 0 ? "y{tk}" : "y{tk}_{qd}")
            LLVMBuildStoreAligned(b, fF[i * te.rq + qd], yptr, 4u)
        }
    }
    return after
}

def private tile_gen(var gc : LlvmCodeCtx) : bool {
    // decline on a foreign signature, and on every shared rail (perm_declines — the layout
    // companion declines in lockstep): the reference body compiles instead
    if (!is_tile_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false

    let kstep = p.kstep
    let nrsplit = p.nrsplit
    let rt = q8q8_repack_type(p.mr)
    let mod = LLVMGetGlobalParent(gc.impl)
    let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
    var te = TileEmit(builder = gc.jit.builder, types = gc.jit.types, interleave = rt.interleave, rq = rt.interleave / 4)
    te.v16i8 = LLVMVectorType(te.types.t_int8, 16u)
    te.v4i32 = te.types->LLVMInt4Type()
    te.v4f32 = te.types->LLVMFloat4Type()
    var declTypes <- [te.v4i32, te.v16i8]
    te.sdot_decl = LLVMGetIntrinsicDeclaration(mod, id, declTypes)
    if (te.sdot_decl == null) return false      // no NEON dotprod on this target: decline
    var fnArgTypes <- [te.v4i32, te.v16i8, te.v16i8]
    te.sdot_ty = LLVMFunctionType(te.v4i32, fnArgTypes)

    let b = gc.jit.builder
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")

    // entry: per-token activation/scale bases; nb = n / 32
    LLVMPositionBuilderAtEnd(b, entry)
    var sa = SliceArgs(gc_impl = gc.impl, ctx = gc.jit.ctx, kstep = kstep)
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
        pred = emit_slice(te, sa, pred, tokBase, nrsplit, tokBase == 0 ? "" : "_{tokBase}")
        tokBase += nrsplit
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
// accumulators per block are the independent sdot chains a serial single-token laneq chain
// lacks. Declines via the SAME perm_declines as the tile — the reference body (the grp4
// laneq rows walk) falls back in lockstep with the grp4 reference pair.
def private gemv_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_gemv_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false

    let rt = q8q8_repack_type(p.mr)
    let mod = LLVMGetGlobalParent(gc.impl)
    let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
    var te = TileEmit(builder = gc.jit.builder, types = gc.jit.types, interleave = rt.interleave, rq = rt.interleave / 4)
    te.v16i8 = LLVMVectorType(te.types.t_int8, 16u)
    te.v4i32 = te.types->LLVMInt4Type()
    te.v4f32 = te.types->LLVMFloat4Type()
    var declTypes <- [te.v4i32, te.v16i8]
    te.sdot_decl = LLVMGetIntrinsicDeclaration(mod, id, declTypes)
    if (te.sdot_decl == null) return false      // no NEON dotprod on this target: decline
    var fnArgTypes <- [te.v4i32, te.v16i8, te.v16i8]
    te.sdot_ty = LLVMFunctionType(te.v4i32, fnArgTypes)

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

// The MXFP4 quarter of the stamp (dot=mx4): the same rows-range GEMV as gemv_gen over the
// grp<mr>-interleaved nibble/exponent planes — emit_block_mx4 swaps the weight-load stage for
// tbl dequant (constant LUT) and the scale loads for the in-register e8m0 fold; the loop
// machinery, gkstep knob, and decline rails are shared.
// The MXFP4 quarter of the stamp (dot=mx4): the same rows-range GEMV as gemv_gen over the
// grp<mr>-interleaved nibble/exponent planes — emit_block_mx4 swaps the weight-load stage for
// tbl dequant (constant LUT) and the scale loads for the in-register e8m0 fold; the loop
// machinery, gkstep knob, and decline rails are shared.
def private mx4_gemv_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_gemv_signature(gc.fn)) return false
    let p = parse_perm(gc)
    if (perm_declines(gc, p)) return false

    let rt = q8q8_repack_type(p.mr)
    let mod = LLVMGetGlobalParent(gc.impl)
    var te = TileEmit(builder = gc.jit.builder, types = gc.jit.types, interleave = rt.interleave, rq = rt.interleave / 4, mx4 = true)
    te.v16i8 = LLVMVectorType(te.types.t_int8, 16u)
    te.v4i32 = te.types->LLVMInt4Type()
    te.v4f32 = te.types->LLVMFloat4Type()
    let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
    var declTypes <- [te.v4i32, te.v16i8]
    te.sdot_decl = LLVMGetIntrinsicDeclaration(mod, id, declTypes)
    if (te.sdot_decl == null) return false      // no NEON dotprod on this target: decline
    var fnArgTypes <- [te.v4i32, te.v16i8, te.v16i8]
    te.sdot_ty = LLVMFunctionType(te.v4i32, fnArgTypes)
    let tblId = LLVMLookupIntrinsicID("llvm.aarch64.neon.tbl1")
    var tblDeclTypes <- [te.v16i8]
    te.tbl_decl = LLVMGetIntrinsicDeclaration(mod, tblId, tblDeclTypes)
    if (te.tbl_decl == null) return false       // lockstep with perm_declines' tbl rail
    var tblArgTypes <- [te.v16i8, te.v16i8]
    te.tbl_ty = LLVMFunctionType(te.v16i8, tblArgTypes)
    // the doubled-e2m1 LUT (mxfp4_fill_lut) as a constant vector — no table pointer at runtime
    let kv = fixed_array(0, 1, 2, 3, 4, 6, 8, 12, 0, -1, -2, -3, -4, -6, -8, -12)
    var lutElems : array<LLVMOpaqueValue?>
    lutElems |> reserve(16)
    for (v in kv) {
        lutElems |> push(LLVMConstInt(te.types.t_int8, uint64(v & 255), 0))
    }
    te.lut = LLVMConstVector(array_data_ptr(lutElems), 16u)

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
