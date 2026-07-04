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
//   mr      rows per interleave group; anything but GEMM_GEN_MR declines — the reference
//           body's layout IS the stub contract until repack generation lands (M4)
//   dot     dot primitive; only "sdot" has an emitter on this (NEON) leg
// Illegal perms decline (return false) and the reference body compiles instead — the decline
// path is the fallback tier. Runs in the llvm-jit context; wired via llvm_user_modules.das.
// The stub it generates for is dasllama/dasllama_math_gen.das::q8q8_tile_gen.

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
    wg : LLVMOpaqueValue?                // interleaved mr-row weight group base
    sg : LLVMOpaqueValue?                // group scales (float x interleave per block)
    x : LLVMOpaqueValue? [4]             // per-token activation base pointers
    xs : LLVMOpaqueValue? [4]            // per-token activation scale base pointers
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

// one 32-k block for tokens [tokBase, tokBase+tokCount): 8 shared weight vectors x tokens =
// 32 indexed sdots at full width, then the per-block scale fold f[i] += float4(a[i]) * s4 *
// splat(q[i]) — the exact op order of the hand template dot_q8q8_laneq4x4_template, so
// fast-math contraction sees the same input. Weight/scale strides come off te.interleave —
// the q8q8_repack_type derivation.
def private emit_block(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [4]; tokBase, tokCount : int) {
    let b = te.builder
    var wb = LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave * 0x20)), "wb")
    var xb = LLVMBuildMul(b, bi, te.types->ConstI64(0x20ul), "xb")
    var wv : LLVMOpaqueValue? [8]
    for (j in range(8)) {
        var off = j == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(j * 16)), "")
        wv[j] = load_v16i8(te, te.wg, off, "wv{j}")
    }
    var xv0 : LLVMOpaqueValue? [4]
    var xv1 : LLVMOpaqueValue? [4]
    var xb1 = LLVMBuildAdd(b, xb, te.types->ConstI64(16ul), "")
    for (i in range(tokCount)) {
        xv0[i] = load_v16i8(te, te.x[tokBase + i], xb, "x{tokBase + i}lo")
        xv1[i] = load_v16i8(te, te.x[tokBase + i], xb1, "x{tokBase + i}hi")
    }
    var a : LLVMOpaqueValue? [4]
    for (i in range(tokCount)) {
        a[i] = LLVMConstNull(te.v4i32)
    }
    for (l in range(4)) {           // chunk 0 (k 0..15): lane l of each token vs shared weight vector
        for (i in range(tokCount)) {
            a[i] = sdot_lane(te, a[i], wv[l], xv0[i], l)
        }
    }
    for (l in range(4)) {           // chunk 1 (k 16..31)
        for (i in range(tokCount)) {
            a[i] = sdot_lane(te, a[i], wv[4 + l], xv1[i], l)
        }
    }
    var sgp = LLVMBuildGEP2(b, te.types.t_float, te.sg, LLVMBuildMul(b, bi, te.types->ConstI64(uint64(te.interleave)), ""), "sgp")
    var s4 = LLVMBuildLoad2Aligned(b, te.v4f32, sgp, 4u, "s4")
    for (i in range(tokCount)) {
        let tk = tokBase + i
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[tk], bi, "qp{tk}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "q{tk}")
        var af = LLVMBuildSIToFP(b, a[i], te.v4f32, "af{tk}")
        var m = LLVMBuildFMul(b, af, s4, "")
        m = LLVMBuildFMul(b, m, splat_f32(te, q, "qs{tk}"), "")
        f[i] = LLVMBuildFAdd(b, f[i], m, "f{tk}")
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
// per-token v4f32 stores. `pred` must be terminator-free; returns the slice's merge block
// (also terminator-free). Main loop runs kstep blocks per iteration; the remainder is a chain
// of kstep-1 conditional single blocks — for kstep=2 this is head/body/tail_check/tail_body/
// after, the exact M2 CFG.
def private emit_slice(var te : TileEmit; var sa : SliceArgs; var pred : LLVMOpaqueBasicBlock?; tokBase, tokCount : int; sfx : string) : LLVMOpaqueBasicBlock? {
    let b = te.builder
    let K = sa.kstep
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
    var fPhi : LLVMOpaqueValue? [4]
    for (i in range(tokCount)) {
        fPhi[i] = LLVMBuildPhi(b, te.v4f32, "fphi{tokBase + i}")
    }
    var entryValsBi <- [LLVMConstNull(te.types.t_int64)]
    var entryBlocks <- [pred]
    LLVMAddIncoming(biPhi, entryValsBi, entryBlocks)
    for (i in range(tokCount)) {
        var zv <- [LLVMConstNull(te.v4f32)]
        var zb <- [pred]
        LLVMAddIncoming(fPhi[i], zv, zb)
    }
    var biPK = LLVMBuildAdd(b, biPhi, te.types->ConstI64(uint64(K)), "biP{K}")
    var stepCond = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLE, biPK, sa.nb, "pair")
    LLVMBuildCondBr(b, stepCond, body, K > 1 ? checks[0] : after)

    // body: K blocks per iteration
    LLVMPositionBuilderAtEnd(b, body)
    var fCur : LLVMOpaqueValue? [4]
    for (i in range(tokCount)) {
        fCur[i] = fPhi[i]
    }
    emit_block(te, biPhi, fCur, tokBase, tokCount)
    for (j in range(1, K)) {
        var bij = LLVMBuildAdd(b, biPhi, te.types->ConstI64(uint64(j)), "")
        emit_block(te, bij, fCur, tokBase, tokCount)
    }
    LLVMBuildBr(b, head)
    var bodyValsBi <- [biPK]
    var bodyBlocks <- [body]
    LLVMAddIncoming(biPhi, bodyValsBi, bodyBlocks)
    for (i in range(tokCount)) {
        var bv <- [fCur[i]]
        var bb <- [body]
        LLVMAddIncoming(fPhi[i], bv, bb)
    }

    // remainder chain: check j falls through to `after` when no blocks remain; its tail body
    // runs one more block. Track per-incoming f values for the merge phis.
    var mergeBlocks : array<LLVMOpaqueBasicBlock?>
    var mergeF : array<LLVMOpaqueValue? [4]>
    mergeBlocks |> reserve(K)
    mergeF |> reserve(K)
    var chainF : LLVMOpaqueValue? [4]
    for (i in range(tokCount)) {
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
        emit_block(te, chainBi, chainF, tokBase, tokCount)
        if (j + 1 < K - 1) {
            chainBi = LLVMBuildAdd(b, chainBi, te.types->ConstI64(1ul), "")
            LLVMBuildBr(b, checks[j + 1])
        } else {
            LLVMBuildBr(b, after)
            mergeBlocks |> push(tails[j])
            mergeF |> push(chainF)
        }
    }

    // after: merge phis (grouped first — verifier rule), then one v4f32 store per token
    // (cols g*interleave .. +3 are contiguous floats)
    LLVMPositionBuilderAtEnd(b, after)
    var fF : LLVMOpaqueValue? [4]
    for (i in range(tokCount)) {
        fF[i] = LLVMBuildPhi(b, te.v4f32, "ff{tokBase + i}")
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
        var yoff = LLVMBuildAdd(b, LLVMBuildMul(b, tRow, sa.d, ""), col, "")
        var yptr = LLVMBuildGEP2(b, te.types.t_float, sa.yp, yoff, "y{tk}")
        LLVMBuildStoreAligned(b, fF[i], yptr, 4u)
    }
    return after
}

def private tile_gen(var gc : LlvmCodeCtx) : bool {
    // decline off-aarch64 or on a foreign signature: the reference body compiles instead
    if (!g_target_is_aarch64 || !is_tile_signature(gc.fn)) return false

    // perm knobs from the [llvm_code] annotation args; defaults = the M2 perm
    var kstep = 2
    var nrsplit = 4
    var mr = GEMM_GEN_MR
    var dotPrim = "sdot"
    let kv = find_arg(gc.ann.arguments, "kstep")
    if (kv is tInt) { kstep = kv as tInt }
    let nv = find_arg(gc.ann.arguments, "nrsplit")
    if (nv is tInt) { nrsplit = nv as tInt }
    let mv = find_arg(gc.ann.arguments, "mr")
    if (mv is tInt) { mr = mv as tInt }
    let dv = find_arg(gc.ann.arguments, "dot")
    if (dv is tString) { dotPrim = dv as tString }

    // decline rails: no per-ISA dot emitter (only NEON sdot on this leg), illegal perm values,
    // or a q-reg budget bust (weights 2*mr + acc nrsplit*mr/4 + activations 2*nrsplit + 2 scratch)
    if ((dotPrim != "sdot")
        || (kstep != 1 && kstep != 2 && kstep != 4)
        || (nrsplit != 2 && nrsplit != 4)
        || (2 * mr + nrsplit * mr / 4 + 2 * nrsplit + 2 > 32)) return false
    // the stub's reference body reads the q8q8_repack_type(GEMM_GEN_MR) layout — that IS the
    // call contract; other-mr perms wait for repack generation (M4)
    let rt = q8q8_repack_type(mr)
    if (rt.interleave != GEMM_GEN_MR || !rt.f32_scales) return false

    let mod = LLVMGetGlobalParent(gc.impl)
    let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
    var te = TileEmit(builder = gc.jit.builder, types = gc.jit.types, interleave = rt.interleave)
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

// Called from llvm_user_modules::register_user_llvm_code_generators — the JIT invokes that in the
// context that reads the registry, so the direct call lands in the right table copy.
[macro_function]
def public register_dasllama_gemm_generators {
    register_llvm_code_generator("dasllama_gemm_gen::q8q8_tile", @@tile_gen)
}
