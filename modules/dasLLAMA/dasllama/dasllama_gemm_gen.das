options gen2
options indenting = 4

module dasllama_gemm_gen shared private

require llvm/daslib/llvm_boost
require llvm/daslib/llvm_jit_code
require llvm/daslib/llvm_jit_common
require daslib/ast_boost

// The M2 hand-composed GEMM perm (gemm_generator_plan.md): an [llvm_code] generator that emits the
// laneq 4-row x 4-token register tile as LLVM IR — dot=sdot (indexed, via target intrinsic + lane
// shuffle per the M1 experiment), width=128, mr x nr=4x4, kstep=2 (paired-block loop + odd tail),
// repack=grp4 (f32 scales), acc=i32reg, scale=block_fold, load=bcast_x. Everything except the sdot
// call is platform-independent IR. Runs in the llvm-jit context; wired via llvm_user_modules.das.
// The stub it generates for is dasllama/dasllama_math_gen.das::q8q8_tile4x4_gen.

// emission context threaded through the helpers: builder/types + the per-function value handles
struct private TileEmit {
    builder : LLVMOpaqueBuilder?
    types : PrimitiveTypes?
    v16i8 : LLVMOpaqueType?
    v4i32 : LLVMOpaqueType?
    v4f32 : LLVMOpaqueType?
    sdot_decl : LLVMOpaqueValue?
    sdot_ty : LLVMOpaqueType?
    wg : LLVMOpaqueValue?               // interleaved 4-row weight group base
    sg : LLVMOpaqueValue?               // group scales (float4 per block)
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

// one 32-k block of the tile: 8 shared weight vectors x 4 tokens = 32 indexed sdots, then the
// per-block scale fold f[t] += float4(a[t]) * s4 * splat(q[t]) — the exact op order of the hand
// template dot_q8q8_laneq4x4_template, so fast-math contraction sees the same input
def private emit_block(var te : TileEmit; var bi : LLVMOpaqueValue?; var f : LLVMOpaqueValue? [4]) {
    let b = te.builder
    var wb = LLVMBuildMul(b, bi, te.types->ConstI64(0x80ul), "wb")
    var xb = LLVMBuildMul(b, bi, te.types->ConstI64(0x20ul), "xb")
    var wv : LLVMOpaqueValue? [8]
    for (j in range(8)) {
        var off = j == 0 ? wb : LLVMBuildAdd(b, wb, te.types->ConstI64(uint64(j * 16)), "")
        wv[j] = load_v16i8(te, te.wg, off, "wv{j}")
    }
    var xv0 : LLVMOpaqueValue? [4]
    var xv1 : LLVMOpaqueValue? [4]
    var xb1 = LLVMBuildAdd(b, xb, te.types->ConstI64(16ul), "")
    for (tk in range(4)) {
        xv0[tk] = load_v16i8(te, te.x[tk], xb, "x{tk}lo")
        xv1[tk] = load_v16i8(te, te.x[tk], xb1, "x{tk}hi")
    }
    var a : LLVMOpaqueValue? [4]
    for (tk in range(4)) {
        a[tk] = LLVMConstNull(te.v4i32)
    }
    for (l in range(4)) {           // chunk 0 (k 0..15): lane l of each token vs shared weight vector
        for (tk in range(4)) {
            a[tk] = sdot_lane(te, a[tk], wv[l], xv0[tk], l)
        }
    }
    for (l in range(4)) {           // chunk 1 (k 16..31)
        for (tk in range(4)) {
            a[tk] = sdot_lane(te, a[tk], wv[4 + l], xv1[tk], l)
        }
    }
    var sgp = LLVMBuildGEP2(b, te.types.t_float, te.sg, LLVMBuildMul(b, bi, te.types->ConstI64(4ul), ""), "sgp")
    var s4 = LLVMBuildLoad2Aligned(b, te.v4f32, sgp, 4u, "s4")
    for (tk in range(4)) {
        var qp = LLVMBuildGEP2(b, te.types.t_float, te.xs[tk], bi, "qp{tk}")
        var q = LLVMBuildLoad2Aligned(b, te.types.t_float, qp, 4u, "q{tk}")
        var af = LLVMBuildSIToFP(b, a[tk], te.v4f32, "af{tk}")
        var m = LLVMBuildFMul(b, af, s4, "")
        m = LLVMBuildFMul(b, m, splat_f32(te, q, "qs{tk}"), "")
        f[tk] = LLVMBuildFAdd(b, f[tk], m, "f{tk}")
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

def private tile4x4_gen(var gc : LlvmCodeCtx) : bool {
    // decline off-aarch64 or on a foreign signature: the reference body compiles instead
    if (!g_target_is_aarch64 || !is_tile_signature(gc.fn)) return false
    let mod = LLVMGetGlobalParent(gc.impl)
    let id = LLVMLookupIntrinsicID("llvm.aarch64.neon.sdot")
    var te = TileEmit(builder = gc.jit.builder, types = gc.jit.types)
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
    var head = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "head")
    var body = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "body")
    var tailc = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "tail_check")
    var tailb = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "tail_body")
    var after = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "after")

    // entry: per-token activation/scale bases; nb = n / 32
    LLVMPositionBuilderAtEnd(b, entry)
    let yp = LLVMGetParam(gc.impl, 0u)
    te.wg = LLVMGetParam(gc.impl, 1u)
    te.sg = LLVMGetParam(gc.impl, 2u)
    let xqp = LLVMGetParam(gc.impl, 3u)
    let xsp = LLVMGetParam(gc.impl, 4u)
    let n = LLVMGetParam(gc.impl, 5u)
    let d = LLVMGetParam(gc.impl, 6u)
    let g = LLVMGetParam(gc.impl, 7u)
    let t0 = LLVMGetParam(gc.impl, 8u)
    let nb = LLVMBuildSDiv(b, n, te.types->ConstI64(32ul), "nb")
    for (tk in range(4)) {
        var tRow = LLVMBuildAdd(b, t0, te.types->ConstI64(uint64(tk)), "")
        te.x[tk] = LLVMBuildGEP2(b, te.types.t_int8, xqp, LLVMBuildMul(b, tRow, n, ""), "x{tk}")
        te.xs[tk] = LLVMBuildGEP2(b, te.types.t_float, xsp, LLVMBuildMul(b, tRow, nb, ""), "xs{tk}")
    }
    LLVMBuildBr(b, head)

    // head: bi/f phis; run the paired-block body while bi+2 <= nb
    LLVMPositionBuilderAtEnd(b, head)
    var biPhi = LLVMBuildPhi(b, te.types.t_int64, "bi")
    var fPhi : LLVMOpaqueValue? [4]
    for (tk in range(4)) {
        fPhi[tk] = LLVMBuildPhi(b, te.v4f32, "fphi{tk}")
    }
    var entryValsBi <- [LLVMConstNull(te.types.t_int64)]
    var entryBlocks <- [entry]
    LLVMAddIncoming(biPhi, entryValsBi, entryBlocks)
    for (tk in range(4)) {
        var zv <- [LLVMConstNull(te.v4f32)]
        var zb <- [entry]
        LLVMAddIncoming(fPhi[tk], zv, zb)
    }
    var biP2 = LLVMBuildAdd(b, biPhi, te.types->ConstI64(2ul), "biP2")
    var pairCond = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLE, biP2, nb, "pair")
    LLVMBuildCondBr(b, pairCond, body, tailc)

    // body: two blocks per iteration (kstep=2 — the hand tier's shipped u2)
    LLVMPositionBuilderAtEnd(b, body)
    var fCur : LLVMOpaqueValue? [4]
    for (tk in range(4)) {
        fCur[tk] = fPhi[tk]
    }
    emit_block(te, biPhi, fCur)
    var biNext = LLVMBuildAdd(b, biPhi, te.types->ConstI64(1ul), "")
    emit_block(te, biNext, fCur)
    LLVMBuildBr(b, head)
    var bodyValsBi <- [biP2]
    var bodyBlocks <- [body]
    LLVMAddIncoming(biPhi, bodyValsBi, bodyBlocks)
    for (tk in range(4)) {
        var bv <- [fCur[tk]]
        var bb <- [body]
        LLVMAddIncoming(fPhi[tk], bv, bb)
    }

    // tail_check / tail_body: one more block when nb is odd
    LLVMPositionBuilderAtEnd(b, tailc)
    var oddCond = LLVMBuildICmp(b, LLVMIntPredicate.LLVMIntSLT, biPhi, nb, "odd")
    LLVMBuildCondBr(b, oddCond, tailb, after)
    LLVMPositionBuilderAtEnd(b, tailb)
    var fTail : LLVMOpaqueValue? [4]
    for (tk in range(4)) {
        fTail[tk] = fPhi[tk]
    }
    emit_block(te, biPhi, fTail)
    LLVMBuildBr(b, after)

    // after: merge phis (grouped first — verifier rule), then one v4f32 store per token
    // (cols g*4..g*4+3 are contiguous floats)
    LLVMPositionBuilderAtEnd(b, after)
    var fF : LLVMOpaqueValue? [4]
    for (tk in range(4)) {
        fF[tk] = LLVMBuildPhi(b, te.v4f32, "ff{tk}")
        var iv <- [fPhi[tk], fTail[tk]]
        var ib <- [tailc, tailb]
        LLVMAddIncoming(fF[tk], iv, ib)
    }
    var col = LLVMBuildMul(b, g, te.types->ConstI64(4ul), "col")
    for (tk in range(4)) {
        var tRow = LLVMBuildAdd(b, t0, te.types->ConstI64(uint64(tk)), "")
        var yoff = LLVMBuildAdd(b, LLVMBuildMul(b, tRow, d, ""), col, "")
        var yptr = LLVMBuildGEP2(b, te.types.t_float, yp, yoff, "y{tk}")
        LLVMBuildStoreAligned(b, fF[tk], yptr, 4u)
    }
    LLVMBuildRetVoid(b)
    return true
}

// Called from llvm_user_modules::register_user_llvm_code_generators — the JIT invokes that in the
// context that reads the registry, so the direct call lands in the right table copy.
[macro_function]
def public register_dasllama_gemm_generators {
    register_llvm_code_generator("dasllama_gemm_gen::tile4x4", @@tile4x4_gen)
}
