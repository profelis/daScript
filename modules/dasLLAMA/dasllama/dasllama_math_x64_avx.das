options gen2

module dasllama_math_x64_avx shared public

require dasllama/dasllama_math
require dasllama/dasllama_math_default  // dot_mx4q8_scalar: the bit-identity reference the probes/tests A/B against
require llvm/daslib/x64_avx  // dot32/dot32_mx4: JIT-emitted 256-bit x86 sign-trick dot (+ ymm PSHUFB MXFP4 dequant), scalar fallback elsewhere
require daslib/jobque_boost public  // kernels expand parallel_for; consumers need its symbols
require dasllama/dasllama_par  // maybe_parallel_for
require math  // min: the batch kernel's token-block clamp
require daslib/fio  // get_env_variable: the AVX kernel-matrix switches

// x86-64 dot32 backends for the Q8·Q8 matmuls — the x64 mirror of dasllama_math_aarch64_neon.das
// (read that header for the registry / threading / dispatch contract). Four backends, all
// registered at [init] gated on x86_64 + jit_enabled() + cpu_supports("avx2"): "x64-avx2" (row-major dot4x4, priority 10,
// the auto default), "x64-avx2-repack" (grp4 4-row block-interleave + token-blocked batch,
// priority 20, picked by select_matmul_backend_for_load), and two pinnable experiments —
// "x64-avx2-acc8" (llama.cpp-shaped float[8] memory accumulator, priority 9; fastest at LOW thread
// counts, wash at 32T) and "x64-avx2-ps" (fused float epilogue, priority 8; -13% on Zen2, kept for
// A/B). Off-JIT the dot intrinsics run their scalar fallbacks — slower than the vectorized portable
// kernels — so the portable backend stays selected there, as on every non-x64 host.
//
// EXACTNESS: dot32's sign-trick lowering requires activation bytes in [-127, 127]; daslang's Q8
// quantizer guarantees that by construction (d = amax/127 — see x64_avx.das). Weights may be any
// int8 including -128, so foreign-written GGUF Q8 weights are safe as-is.

//! x86 dot32 dot: 4 blocks/iter, 4 independent int4 accumulators (each block = ONE dot32 of a full
//! 32-byte Q8 block, ymm), hsum + dual-scale flushed per block into 4 separate float accumulators —
//! the same structure as the NEON sdot4x4 kernel. dot32's high/low-half fold regroups lanes within
//! a block, but the per-block hsum makes the flushed float identical to the two-dot4 form, so
//! results stay bit-for-bit close to dot_q8q8. Not `private`: called from inside the lifted
//! parallel_for worker lambdas, which can't see module-private functions.
[hint(unsafe_range_check, noalias = wq, noalias = xq, noalias = ws, noalias = xs)]
def dot_q8q8_x64dot4x4(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var f0 = 0.0
    var f1 = 0.0
    var f2 = 0.0
    var f3 = 0.0
    var bi = 0l
    unsafe {
        while (bi + 4l <= nb) {
            let bb = bi * 32l
            var a0 = int4(0, 0, 0, 0)
            var a1 = int4(0, 0, 0, 0)
            var a2 = int4(0, 0, 0, 0)
            var a3 = int4(0, 0, 0, 0)
            a0 = dot32(a0, wq + bb, xq + bb)
            a1 = dot32(a1, wq + bb + 32l, xq + bb + 32l)
            a2 = dot32(a2, wq + bb + 64l, xq + bb + 64l)
            a3 = dot32(a3, wq + bb + 96l, xq + bb + 96l)
            f0 += float(a0.x + a0.y + a0.z + a0.w) * ws[bi + 0l] * xs[bi + 0l]
            f1 += float(a1.x + a1.y + a1.z + a1.w) * ws[bi + 1l] * xs[bi + 1l]
            f2 += float(a2.x + a2.y + a2.z + a2.w) * ws[bi + 2l] * xs[bi + 2l]
            f3 += float(a3.x + a3.y + a3.z + a3.w) * ws[bi + 3l] * xs[bi + 3l]
            bi += 4l
        }
        while (bi < nb) {
            let base = bi * 32l
            var acc = int4(0, 0, 0, 0)
            acc = dot32(acc, wq + base, xq + base)
            f0 += float(acc.x + acc.y + acc.z + acc.w) * ws[bi] * xs[bi]
            bi++
        }
    }
    return f0 + f1 + f2 + f3
}

def private q8q8_kernel_x64_dot4x4(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_x64dot4x4(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_x64_dot4x4(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_x64dot4x4(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

def private q8q8_group3_kernel_x64_dot4x4(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                          woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    count_parallel_dispatch(matmul_chunks(int(dtot), get_dispatch_lanes()))   // dispatch observability (raw parallel_for site)
    parallel_for(0, int(dtot), matmul_chunks(int(dtot), get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_x64dot4x4(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_x64dot4x4(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_x64dot4x4(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
        wg |> notify_and_release
    }
}

// ===== ps backend (dot32_ps: fused float epilogue on row-major weights) =====
// Same row-major layout and block order as the dot4x4 family, but the per-block epilogue (int4
// hsum + scalar scale chain, ~10 µops/block) is fused into the dot32_ps intrinsic (VCVTDQ2PS +
// broadcast mul + vector add, 3 µops) and the horizontal reduce happens ONCE per row — the
// llama.cpp vec_dot shape. Float accumulation differs from dot4x4/portable (per-lane float
// partials, scaled per block), so this tier is tolerance-gated (A/B maxdiff + token parity),
// not bit-identity-gated.

//! One full Q8 row against one token via dot32_ps: float4 partial accumulators, 4-block unroll
//! for ILP, one horizontal reduce at row end. Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wq, noalias = ws, noalias = xq, noalias = xs)]
def dot_q8q8_x64ps(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var f0 = float4(0.0, 0.0, 0.0, 0.0)
    var f1 = float4(0.0, 0.0, 0.0, 0.0)
    var f2 = float4(0.0, 0.0, 0.0, 0.0)
    var f3 = float4(0.0, 0.0, 0.0, 0.0)
    var bi = 0l
    unsafe {
        while (bi + 4l <= nb) {
            let bb = bi * 32l
            f0 = dot32_ps(f0, wq + bb, xq + bb, ws[bi] * xs[bi])
            f1 = dot32_ps(f1, wq + bb + 32l, xq + bb + 32l, ws[bi + 1l] * xs[bi + 1l])
            f2 = dot32_ps(f2, wq + bb + 64l, xq + bb + 64l, ws[bi + 2l] * xs[bi + 2l])
            f3 = dot32_ps(f3, wq + bb + 96l, xq + bb + 96l, ws[bi + 3l] * xs[bi + 3l])
            bi += 4l
        }
        while (bi < nb) {
            f0 = dot32_ps(f0, wq + bi * 32l, xq + bi * 32l, ws[bi] * xs[bi])
            bi++
        }
    }
    let f = f0 + f1 + f2 + f3
    return f.x + f.y + f.z + f.w
}

def private q8q8_kernel_x64_ps(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_x64ps(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_x64_ps(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_x64ps(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

def private q8q8_group3_kernel_x64_ps(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                      woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    count_parallel_dispatch(matmul_chunks(int(dtot), get_dispatch_lanes()))   // dispatch observability (raw parallel_for site)
    parallel_for(0, int(dtot), matmul_chunks(int(dtot), get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_x64ps(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_x64ps(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_x64ps(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
        wg |> notify_and_release
    }
}

// ===== acc8 backend (dot32_acc8: 8-wide float accumulators, no per-block fold) =====
// Same row-major layout and block order as the dot4x4 family, but the per-block epilogue vanishes
// entirely: dot32_acc8 converts the 8 raw quads to float (VCVTDQ2PS ymm) and multiply-accumulates
// into a memory-backed float[8] that LICM promotes into a ymm register across the block loop —
// llama.cpp's vec_dot shape (under _jit_fast_math the mul+add contracts to VFMADD). No fold, no
// per-block hsum; ONE 32-lane reduce per row. Float accumulation differs from dot4x4/portable
// (per-lane partials), so this tier is tolerance-gated (A/B maxdiff + token parity), like ps.

//! One full Q8 row against one token via dot32_acc8: 4 memory-backed 8-lane float accumulators
//! (each promoted to a ymm by LICM), 4-block unroll to break the FMA latency chain, one 32-lane
//! horizontal reduce at row end. Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wq, noalias = ws, noalias = xq, noalias = xs)]
def dot_q8q8_x64acc8(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var a0 : float[8]
    var a1 : float[8]
    var a2 : float[8]
    var a3 : float[8]
    var bi = 0l
    unsafe {
        var p0 = addr(a0[0])
        var p1 = addr(a1[0])
        var p2 = addr(a2[0])
        var p3 = addr(a3[0])
        while (bi + 4l <= nb) {
            let bb = bi * 32l
            dot32_acc8(p0, wq + bb, xq + bb, ws[bi] * xs[bi])
            dot32_acc8(p1, wq + bb + 32l, xq + bb + 32l, ws[bi + 1l] * xs[bi + 1l])
            dot32_acc8(p2, wq + bb + 64l, xq + bb + 64l, ws[bi + 2l] * xs[bi + 2l])
            dot32_acc8(p3, wq + bb + 96l, xq + bb + 96l, ws[bi + 3l] * xs[bi + 3l])
            bi += 4l
        }
        while (bi < nb) {
            dot32_acc8(p0, wq + bi * 32l, xq + bi * 32l, ws[bi] * xs[bi])
            bi++
        }
    }
    var t = 0.0
    for (j in range(8)) {
        t += (a0[j] + a1[j]) + (a2[j] + a3[j])
    }
    return t
}

def private q8q8_kernel_x64_acc8(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_x64acc8(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_x64_acc8(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    // OVERSPLIT: more chunks than workers — idle workers pop a late-woken worker's remaining
    // chunks from the fifo, so a straggler strands one small chunk instead of a whole 1/K range.
    // Measured on the 3990X @32 workers, qo x 512 tokens: x1 473, x4 655, x8 627 GMAC/s (hardware
    // ceiling 772 same-session) — x4 is the knee; ggml's chunked mul_mat is the same defense.
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_x64acc8(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

def private q8q8_group3_kernel_x64_acc8(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                        woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    count_parallel_dispatch(matmul_chunks(int(dtot), get_dispatch_lanes()))   // dispatch observability (raw parallel_for site)
    parallel_for(0, int(dtot), matmul_chunks(int(dtot), get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_x64acc8(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_x64acc8(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_x64acc8(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
        wg |> notify_and_release
    }
}

// ===== grp4 backend (dot32 over block-interleaved 4-row groups) — Q8 model load only =====
// The x64 mirror of the NEON laneq tier, at BLOCK granularity: dot32 consumes whole 32-byte Q8
// blocks, so a 4-row group interleaves per block (row0's block | row1's | row2's | row3's = 128
// bytes at wg + bi*128 — the same group/stride arithmetic as NEON's laneq, only the inner byte
// order differs) and the scales go float4-per-block (sg[bi*4 + r]). One activation block feeds all
// 4 rows (the x load CSEs; the sign-trick's psign is per-row since it keys on the weight), and the
// flush is one float4 mul-add instead of 4 scalar chains. Activated only by
// select_matmul_backend_for_load at Q8 model load (direct row-major callers would read the
// interleaved layout as garbage). Tail rows (d % 4) stay row-major and run the dot4x4 fallback.
// Float accumulation order differs from the row-major kernel (per-block flush vs dot4x4's 4-block
// grouping) — A/B against portable is tolerance-gated, and parity gates token-for-token, as with
// the NEON laneq tier. [tuned]-rig migration for the tile is a follow-up once the shape settles.

//! dot32 over one 4-row block-interleaved group against one token: per block, the shared x block
//! against the 4 row blocks into 4 int4 accumulators, hsum'd into one float4 flush with the group's
//! float4 scales × the token block scale. Not `private`: called from inside the lifted parallel_for
//! worker lambdas.
[hint(unsafe_range_check, noalias = wg, noalias = sg, noalias = xq, noalias = xs)]
def dot_q8q8_x64grp4(wg : int8 const?; sg : float const?; xq : int8 const?; xs : float const?; n : int64) : float4 {
    let nb = n / 32l
    var f = float4(0.0, 0.0, 0.0, 0.0)
    unsafe {
        for (bi in range64(nb)) {
            let wb = bi * 128l
            let xb = xq + bi * 32l
            var a0 = int4(0, 0, 0, 0)
            var a1 = int4(0, 0, 0, 0)
            var a2 = int4(0, 0, 0, 0)
            var a3 = int4(0, 0, 0, 0)
            a0 = dot32(a0, wg + wb, xb)
            a1 = dot32(a1, wg + wb + 32l, xb)
            a2 = dot32(a2, wg + wb + 64l, xb)
            a3 = dot32(a3, wg + wb + 96l, xb)
            let s = float4(sg[bi * 4l], sg[bi * 4l + 1l], sg[bi * 4l + 2l], sg[bi * 4l + 3l])
            let xsb = xs[bi]
            f += float4(float(a0.x + a0.y + a0.z + a0.w), float(a1.x + a1.y + a1.z + a1.w),
                float(a2.x + a2.y + a2.z + a2.w), float(a3.x + a3.y + a3.z + a3.w)) * s * float4(xsb, xsb, xsb, xsb)
        }
    }
    return f
}

//! 4-row × 2-token tile: one interleaved group against 2 tokens, 8 int4 accumulators. Each weight
//! block's load+abs (the sign-trick's unsigned side) is shared across both tokens by CSE, each
//! token's x block across the 4 rows — the AVX2 analog of the NEON laneq4x4 tile at the register
//! budget dot32's per-pair accumulators allow (4 rows × 4 tokens would need 16 live xmm accs).
//! Writes 8 outputs token-major. ntok - t0 >= 2 assumed. Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wg, noalias = sg, noalias = xqp, noalias = xsp)]
def dot_q8q8_x64grp4x2(var yp : float?; wg : int8 const?; sg : float const?; xqp : int8 const?; xsp : float const?; n, d, g, t0 : int64) {
    let nb = n / 32l
    var f0 = float4(0.0, 0.0, 0.0, 0.0)
    var f1 = float4(0.0, 0.0, 0.0, 0.0)
    unsafe {
        let x0 = xqp + (t0 + 0l) * n
        let x1 = xqp + (t0 + 1l) * n
        let xs0 = xsp + (t0 + 0l) * nb
        let xs1 = xsp + (t0 + 1l) * nb
        for (bi in range64(nb)) {
            let wb = bi * 128l
            let xb = bi * 32l
            var a00 = int4(0, 0, 0, 0)
            var a01 = int4(0, 0, 0, 0)
            var a02 = int4(0, 0, 0, 0)
            var a03 = int4(0, 0, 0, 0)
            var a10 = int4(0, 0, 0, 0)
            var a11 = int4(0, 0, 0, 0)
            var a12 = int4(0, 0, 0, 0)
            var a13 = int4(0, 0, 0, 0)
            a00 = dot32(a00, wg + wb, x0 + xb); a10 = dot32(a10, wg + wb, x1 + xb)
            a01 = dot32(a01, wg + wb + 32l, x0 + xb); a11 = dot32(a11, wg + wb + 32l, x1 + xb)
            a02 = dot32(a02, wg + wb + 64l, x0 + xb); a12 = dot32(a12, wg + wb + 64l, x1 + xb)
            a03 = dot32(a03, wg + wb + 96l, x0 + xb); a13 = dot32(a13, wg + wb + 96l, x1 + xb)
            let s = float4(sg[bi * 4l], sg[bi * 4l + 1l], sg[bi * 4l + 2l], sg[bi * 4l + 3l])
            let q0 = xs0[bi]
            let q1 = xs1[bi]
            f0 += float4(float(a00.x + a00.y + a00.z + a00.w), float(a01.x + a01.y + a01.z + a01.w),
                float(a02.x + a02.y + a02.z + a02.w), float(a03.x + a03.y + a03.z + a03.w)) * s * float4(q0, q0, q0, q0)
            f1 += float4(float(a10.x + a10.y + a10.z + a10.w), float(a11.x + a11.y + a11.z + a11.w),
                float(a12.x + a12.y + a12.z + a12.w), float(a13.x + a13.y + a13.z + a13.w)) * s * float4(q1, q1, q1, q1)
        }
        let r = g * 4l
        yp[(t0 + 0l) * d + r + 0l] = f0.x
        yp[(t0 + 0l) * d + r + 1l] = f0.y
        yp[(t0 + 0l) * d + r + 2l] = f0.z
        yp[(t0 + 0l) * d + r + 3l] = f0.w
        yp[(t0 + 1l) * d + r + 0l] = f1.x
        yp[(t0 + 1l) * d + r + 1l] = f1.y
        yp[(t0 + 1l) * d + r + 2l] = f1.z
        yp[(t0 + 1l) * d + r + 3l] = f1.w
    }
}

// In-place repack of one Q8 weight region [d x n] into 4-row block-interleaved groups (+ float4-
// per-block scales). Copies the region to a scratch, then writes the interleaved layout back; tail
// rows (d % 4) stay row-major. Runs once per weight tensor at load, on the main context.
def private repack_q8q8_x64(var wp : int8?; var sp : float?; n, d : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var tw : array<int8>
    var ts : array<float>
    tw |> resize(d * n)
    ts |> resize(d * nb)
    unsafe {
        var twp = addr(tw[0])
        var tsp = addr(ts[0])
        for (i in range64(d * n)) {
            twp[i] = wp[i]
        }
        for (i in range64(d * nb)) {
            tsp[i] = sp[i]
        }
        for (g in range64(ng)) {
            let gbase = g * 4l * n
            for (bi in range64(nb)) {
                let dst = gbase + bi * 128l
                for (r in range64(4l)) {
                    let src = (g * 4l + r) * n + bi * 32l
                    for (k in range64(32l)) {
                        wp[dst + r * 32l + k] = twp[src + k]
                    }
                }
            }
            let sgbase = g * 4l * nb
            for (bi in range64(nb)) {
                for (r in range64(4l)) {
                    sp[sgbase + bi * 4l + r] = tsp[(g * 4l + r) * nb + bi]
                }
            }
        }
    }
    delete tw
    delete ts
}

def private q8q8_kernel_x64_grp4(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(ng), matmul_chunks(int(ng) * 4, get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                let f = dot_q8q8_x64grp4(wp + g * 4l * n, sp + g * 4l * nb, xqp, xsp, n)
                myp[g * 4l + 0l] = f.x
                myp[g * 4l + 1l] = f.y
                myp[g * 4l + 2l] = f.z
                myp[g * 4l + 3l] = f.w
            }
        }
    }
    unsafe {
        for (i in range64(ng * 4l, d)) {
            myp[i] = dot_q8q8_x64dot4x4(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

def private q8q8_batch_kernel_x64_grp4(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var myp = yp
    // Token-blocked like the NEON laneq batch kernel: TB tokens outer, groups inner, so the TB×n
    // activation slice stays cache-resident across this thread's groups (see that kernel's note).
    // OVERSPLIT (see the acc8 batch kernel note), FLOORED at 4 groups per chunk: the token-blocked
    // walk re-reads the TB x n activation slice per chunk, so 1-group chunks pay it 4x. Measured
    // @32 workers ntok=512: kv ng=128 x1 456 > x2 447 > x4 425 GMAC/s (floor binds -> x1); qo
    // ng=512 x4 473 > x1 430 (floor doesn't bind -> full oversplit).
    let TB = effective_token_block(g_q8_token_block, n)
    let lanes = get_dispatch_lanes()
    let njobs = matmul_chunks(int(ng) * 4, lanes * get_q8_batch_chunks_per_job())
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(ng), njobs) $(rb, re) {
        unsafe {
            var tb = 0l
            while (tb < ntok) {
                let tbe = min(tb + TB, ntok)
                let tb2 = tb + ((tbe - tb) / 2l) * 2l
                for (gi in range(rb, re)) {
                    let g = int64(gi)
                    let wgp = wp + g * 4l * n
                    let sgp = sp + g * 4l * nb
                    var tk = tb
                    while (tk < tb2) {     // 4-row × 2-token tiles (the throughput path)
                        dot_q8q8_x64grp4x2(myp, wgp, sgp, xqp, xsp, n, d, g, tk)
                        tk += 2l
                    }
                    while (tk < tbe) {    // token tail within this block: one token at a time
                        let f = dot_q8q8_x64grp4(wgp, sgp, xqp + tk * n, xsp + tk * nb, n)
                        myp[tk * d + g * 4l + 0l] = f.x
                        myp[tk * d + g * 4l + 1l] = f.y
                        myp[tk * d + g * 4l + 2l] = f.z
                        myp[tk * d + g * 4l + 3l] = f.w
                        tk++
                    }
                }
                tb += TB
            }
        }
    }
    unsafe {
        for (i in range64(ng * 4l, d)) {   // row tail (d % 4): row-major dot4x4
            let wrow = wp + i * n
            let srow = sp + i * nb
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_x64dot4x4(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
}

def private q8q8_group3_kernel_x64_grp4(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                        woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let ng0 = d0 / 4l
    let ng1 = d1 / 4l
    let ng2 = d2 / 4l
    let ngtot = ng0 + ng1 + ng2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    count_parallel_dispatch(matmul_chunks(int(ngtot) * 4, get_dispatch_lanes()))   // dispatch observability (raw parallel_for site)
    parallel_for(0, int(ngtot), matmul_chunks(int(ngtot) * 4, get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < ng0) {
                    let f = dot_q8q8_x64grp4(wp + woff0 + g * 4l * n, sp + woff0 / 32l + g * 4l * nb, xqp, xsp, n)
                    w0[g * 4l + 0l] = f.x
                    w0[g * 4l + 1l] = f.y
                    w0[g * 4l + 2l] = f.z
                    w0[g * 4l + 3l] = f.w
                } elif (g < ng0 + ng1) {
                    let r = g - ng0
                    let f = dot_q8q8_x64grp4(wp + woff1 + r * 4l * n, sp + woff1 / 32l + r * 4l * nb, xqp, xsp, n)
                    w1[r * 4l + 0l] = f.x
                    w1[r * 4l + 1l] = f.y
                    w1[r * 4l + 2l] = f.z
                    w1[r * 4l + 3l] = f.w
                } else {
                    let r = g - ng0 - ng1
                    let f = dot_q8q8_x64grp4(wp + woff2 + r * 4l * n, sp + woff2 / 32l + r * 4l * nb, xqp, xsp, n)
                    w2[r * 4l + 0l] = f.x
                    w2[r * 4l + 1l] = f.y
                    w2[r * 4l + 2l] = f.z
                    w2[r * 4l + 3l] = f.w
                }
            }
        }
        wg |> notify_and_release
    }
    unsafe {
        for (i in range64(ng0 * 4l, d0)) {
            w0[i] = dot_q8q8_x64dot4x4(wp + woff0 + i * n, sp + woff0 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng1 * 4l, d1)) {
            w1[i] = dot_q8q8_x64dot4x4(wp + woff1 + i * n, sp + woff1 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng2 * 4l, d2)) {
            w2[i] = dot_q8q8_x64dot4x4(wp + woff2 + i * n, sp + woff2 / 32l + i * nb, xqp, xsp, n)
        }
    }
}

// ===== MXFP4·Q8 native tier (dot32_mx4: ymm PSHUFB LUT dequant feeding the dot32 chain) =====
// Row-major planes on every backend (repack_mx4 stays identity on x64 — the Q8 grp4 interleave is
// a separate decision; a native mx4 4-row tile is a follow-up). The mx4 row dot's per-block int
// sum is exact and its flush order matches dot_mx4q8_scalar, so the mx4 kernels are BIT-IDENTICAL
// to the portable forms (the grp4 Q8 tier's maxdiff-0 property). The Q8 groupn kernels reuse the
// backend's own row dots, so they are bit-exact vs a per-region loop of the SAME backend and
// tolerance-gated vs portable (dot4x4's float partitioning differs, as everywhere). Checked by
// harness/mx4x64_probe.das.

//! x86 MXFP4·Q8 row dot: 4 blocks/iter, one dot32_mx4 per 32-block (ymm PSHUFB dequant +
//! sign-trick dot), the exact int32 block sums flushing into 4 independent float accumulators —
//! the dot4x4 structure. The single-chain form measured 1-core-bound on the serial float add
//! (9.5-10.7 GMAC/s vs 14.1-14.5 broken, 2880-wide row; [unroll_count] hints did NOT recover it —
//! LLVM never reassociates the loop-carried accumulator, fast-math or not — and the acc8 shape
//! measured slower, the ps-experiment port-split story). Block sums stay exact; the 4-way float
//! partitioning makes this TOLERANCE-class vs dot_mx4q8_scalar / the NEON dot_mx4q8 (same status
//! as dot4x4 vs portable). Not `private`: called from inside the lifted parallel_for worker
//! lambdas.
[hint(unsafe_range_check, noalias = lut, noalias = wn, noalias = we, noalias = xq, noalias = xs)]
def dot_mx4q8_x64(lut : int8 const?; wn : uint8 const?; we : uint8 const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var f0 = 0.0
    var f1 = 0.0
    var f2 = 0.0
    var f3 = 0.0
    var bi = 0l
    unsafe {
        while (bi + 4l <= nb) {
            var a0 = int4(0, 0, 0, 0)
            var a1 = int4(0, 0, 0, 0)
            var a2 = int4(0, 0, 0, 0)
            var a3 = int4(0, 0, 0, 0)
            a0 = dot32_mx4(a0, lut, wn + bi * 16l, xq + bi * 32l)
            a1 = dot32_mx4(a1, lut, wn + bi * 16l + 16l, xq + bi * 32l + 32l)
            a2 = dot32_mx4(a2, lut, wn + bi * 16l + 32l, xq + bi * 32l + 64l)
            a3 = dot32_mx4(a3, lut, wn + bi * 16l + 48l, xq + bi * 32l + 96l)
            f0 += float(a0.x + a0.y + a0.z + a0.w) * e8m0_half(uint(we[bi])) * xs[bi]
            f1 += float(a1.x + a1.y + a1.z + a1.w) * e8m0_half(uint(we[bi + 1l])) * xs[bi + 1l]
            f2 += float(a2.x + a2.y + a2.z + a2.w) * e8m0_half(uint(we[bi + 2l])) * xs[bi + 2l]
            f3 += float(a3.x + a3.y + a3.z + a3.w) * e8m0_half(uint(we[bi + 3l])) * xs[bi + 3l]
            bi += 4l
        }
        while (bi < nb) {
            var acc = int4(0, 0, 0, 0)
            acc = dot32_mx4(acc, lut, wn + bi * 16l, xq + bi * 32l)
            f0 += float(acc.x + acc.y + acc.z + acc.w) * e8m0_half(uint(we[bi])) * xs[bi]
            bi++
        }
    }
    return f0 + f1 + f2 + f3
}

def private mx4q8_kernel_x64(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    myp[i] = dot_mx4q8_x64(lutp, wn + int64(i) * (n / 2l), we + int64(i) * nb, xqp, xsp, n)
                }
            }
        }
    }
}

// ===== region-list (groupN) kernels — the MoE decode dispatch fuse, x64 forms =====
// One parallel_for over nregions * d rows: all k routed experts' gates (or ups, or downs) in ONE
// fork/join. Per-row math identical to the single-region kernels — bit-exact, only the scheduling
// changes (the NEON groupn contract, mirrored).

def private q8q8_groupn_kernel_x64(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * d), matmul_chunks(int(nregions * d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let ii = int64(i)
                let r = ii / d
                let row = ii % d
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var v = dot_q8q8_x64dot4x4(wp + woff + row * n, sp + woff / 32l + row * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + row]
                }
                myp[ii] = v
            }
        }
    }
}

// grp4 twin for the repack backend: region rows live in the 4-row block-interleaved layout, so the
// group walk uses dot_q8q8_x64grp4; row tails (d % 4) stay row-major dot4x4 per region.
def private q8q8_groupn_kernel_x64_grp4(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var myp = yp
    maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * ng), matmul_chunks(int(nregions * ng) * 4, get_dispatch_lanes())) $(gb, ge) {
        unsafe {
            for (gi in range(gb, ge)) {
                let gg = int64(gi)
                let r = gg / ng
                let g = gg % ng
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var f = dot_q8q8_x64grp4(wp + woff + g * 4l * n, sp + woff / 32l + g * 4l * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    let bb = boffs[r] + g * 4l
                    f += float4(bp[bb], bp[bb + 1l], bp[bb + 2l], bp[bb + 3l])
                }
                let yb = r * d + g * 4l
                myp[yb + 0l] = f.x
                myp[yb + 1l] = f.y
                myp[yb + 2l] = f.z
                myp[yb + 3l] = f.w
            }
        }
    }
    unsafe {
        for (r in range64(nregions)) {   // row tails (d % 4): row-major dot4x4 per region
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            for (i in range64(ng * 4l, d)) {
                var v = dot_q8q8_x64dot4x4(wp + woff + i * n, sp + woff / 32l + i * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + i]
                }
                myp[r * d + i] = v
            }
        }
    }
}

def private mx4q8_groupn_kernel_x64(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * d), matmul_chunks(int(nregions * d), get_dispatch_lanes())) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    let ii = int64(i)
                    let r = ii / d
                    let row = ii % d
                    let woff = offs[r * 2l]
                    let xoff = offs[r * 2l + 1l]
                    var v = dot_mx4q8_x64(lutp, wn + woff / 2l + row * (n / 2l), we + woff / 32l + row * nb,
                        xqp + xoff, xsp + xoff / 32l, n)
                    if (bp != null) {
                        v += bp[boffs[r] + row]
                    }
                    myp[ii] = v
                }
            }
        }
    }
}

// ===== MXFP4·Q8 batch tier (grouped MoE prefill) — strip dequant into L1 scratch + the Q8 dots =====
// The batch GEMM dequants a small weight strip (one row, or one 4-row grp4 group) into per-chunk
// scratch and runs this backend's OWN Q8 row dots off it — expand_mx4_region_q8's grouped-prefill
// design at L1 granularity: the same expanded bytes, the same dots, the same flush order, so the
// result is BIT-IDENTICAL to expand + repack + Q8 batch on the same backend, while the 3·d·n Q8
// scratch round-trip through DRAM (87% of gpt-oss prefill wall, the moe_expand bucket) collapses
// to a ~3-13KB strip that never leaves L1. The parallel domain is CHUNK IDS (njobs == nchunks, so
// each job owns exactly one chunk and one scratch slot); the scratch is module-global and grow-only
// (matmuls dispatch from the main compute thread only, like every kernel here).

var g_mx4b_wq : array<int8>    // per-chunk strip dequant scratch (grow-only)
var g_mx4b_ws : array<float>

def private mx4b_reserve(qneed, sneed : int64) {
    if (int64(length(g_mx4b_wq)) < qneed) {
        g_mx4b_wq |> resize(int(qneed))
    }
    if (int64(length(g_mx4b_ws)) < sneed) {
        g_mx4b_ws |> resize(int(sneed))
    }
}

//! Dequant one mx4 row (16 nibble bytes + 1 raw E8M0 byte per 32-block) into row-major Q8 bytes +
//! float scales — byte-for-byte expand_mx4_region_q8's row-major form (mx4_dequant32 = one ymm
//! PSHUFB + store per block under JIT; its scalar fallback writes the same bytes). Not `private`:
//! called from inside the lifted parallel_for worker lambdas.
[hint(unsafe_range_check, noalias = lut, noalias = wn, noalias = we, noalias = q, noalias = s)]
def mx4_dequant_row_x64(lut : int8 const?; wn : uint8 const?; we : uint8 const?; var q : int8?; var s : float?; n : int64) {
    let nb = n / 32l
    unsafe {
        for (bi in range64(nb)) {
            mx4_dequant32(lut, wn + bi * 16l, q + bi * 32l)
            s[bi] = e8m0_half(uint(we[bi]))
        }
    }
}

//! Dequant one 4-row mx4 group into the grp4 block-interleaved layout (row r's block bi at
//! q[bi*128 + r*32], scales float4-per-block at s[bi*4 + r]) — byte-for-byte what the row-major
//! expand + repack_q8q8_x64 produce for one group (mx4_dequant32 = one ymm PSHUFB + store per
//! block under JIT; its scalar fallback writes the same bytes). wn/we point at the group's FIRST
//! row (rows are n/2 / n/32 bytes apart). Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = lut, noalias = wn, noalias = we, noalias = q, noalias = s)]
def mx4_dequant_grp4_x64(lut : int8 const?; wn : uint8 const?; we : uint8 const?; var q : int8?; var s : float?; n : int64) {
    let nb = n / 32l
    unsafe {
        for (r in range64(4l)) {
            let wrow = wn + r * (n / 2l)
            let erow = we + r * nb
            for (bi in range64(nb)) {
                mx4_dequant32(lut, wrow + bi * 16l, q + bi * 128l + r * 32l)
                s[bi * 4l + r] = e8m0_half(uint(erow[bi]))
            }
        }
    }
}

// Row-major mx4 batch (the dot4x4-family backends): 1-row strips — dequant the row once, then the
// token sweep runs dot4x4 off the L1-hot strip. Bit-identical to expand + q8q8_batch_kernel_x64_
// dot4x4 (same bytes, same dot, rows independent).
def private mx4q8_batch_kernel_x64(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let nchunks = matmul_chunks(int(d), get_dispatch_lanes())
    mx4b_reserve(int64(nchunks) * n, int64(nchunks) * nb)
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
            unsafe {
                for (ci0 in range(cb, ce)) {
                    let ci = int64(ci0)
                    var qrow = qsp + ci * n
                    var srow = ssp + ci * nb
                    for (i in range64(ci * d / int64(nchunks), (ci + 1l) * d / int64(nchunks))) {
                        mx4_dequant_row_x64(lutp, wn + i * (n / 2l), we + i * nb, qrow, srow, n)
                        for (tk in range64(ntok)) {
                            myp[tk * d + i] = dot_q8q8_x64dot4x4(qrow, srow, xqp + tk * n, xsp + tk * nb, n)
                        }
                    }
                }
            }
        }
    }
}

// grp4 mx4 batch (the repack backend): 4-row group strips dequanted into the grp4 interleave, then
// the token-blocked grp4x2/grp4 tiles — the same TB + oversplit clamp as the Q8 grp4 batch kernel.
// The strip dequant re-runs per (token-block, group): ~one row-dot equivalent per TB tokens, noise.
// Bit-identical to expand + repack + q8q8_batch_kernel_x64_grp4 (same bytes, same dots); vs a
// per-token dot_mx4q8_x64 GEMV sweep it is tolerance-class (the GEMV's 4-acc float partitioning).
def private mx4q8_batch_kernel_x64_grp4(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let ng = d / 4l
    let TB = effective_token_block(g_q8_token_block, n)
    let lanes = get_dispatch_lanes()
    let nchunks = matmul_chunks(int(ng) * 4, lanes * get_q8_batch_chunks_per_job())
    mx4b_reserve(max(int64(nchunks) * 4l * n, n), max(int64(nchunks) * 4l * nb, nb))
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        if (ng > 0l) {
            maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
                unsafe {
                    for (ci0 in range(cb, ce)) {
                        let ci = int64(ci0)
                        let g0 = ci * ng / int64(nchunks)
                        let g1 = (ci + 1l) * ng / int64(nchunks)
                        if (g0 == g1) {
                            continue
                        }
                        var gq = qsp + ci * 4l * n
                        var gs = ssp + ci * 4l * nb
                        var tb = 0l
                        while (tb < ntok) {
                            let tbe = min(tb + TB, ntok)
                            let tb2 = tb + ((tbe - tb) / 2l) * 2l
                            for (gi in range64(g0, g1)) {
                                mx4_dequant_grp4_x64(lutp, wn + gi * 4l * (n / 2l), we + gi * 4l * nb, gq, gs, n)
                                var tk = tb
                                while (tk < tb2) {     // 4-row × 2-token tiles (the throughput path)
                                    dot_q8q8_x64grp4x2(myp, gq, gs, xqp, xsp, n, d, gi, tk)
                                    tk += 2l
                                }
                                while (tk < tbe) {    // token tail within this block: one at a time
                                    let f = dot_q8q8_x64grp4(gq, gs, xqp + tk * n, xsp + tk * nb, n)
                                    myp[tk * d + gi * 4l + 0l] = f.x
                                    myp[tk * d + gi * 4l + 1l] = f.y
                                    myp[tk * d + gi * 4l + 2l] = f.z
                                    myp[tk * d + gi * 4l + 3l] = f.w
                                    tk++
                                }
                            }
                            tb += TB
                        }
                    }
                }
            }
        }
        for (i in range64(ng * 4l, d)) {   // row tail (d % 4): row-major, chunk 0's slot (post-join)
            mx4_dequant_row_x64(lutp, wn + i * (n / 2l), we + i * nb, qsp, ssp, n)
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_x64dot4x4(qsp, ssp, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
}

// Row-major mx4 batch groupN: the region-list twin of mx4q8_batch_kernel_x64 — flattened
// (region, row) items, one row strip per chunk, each item sweeping its region's token rows with
// dot4x4. Bias folds as an add-after pass over the item's just-written outputs (bit-identical to
// the caller-side add_bias it replaces).
def private mx4q8_batch_groupn_kernel_x64(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let items = nregions * d
    let nchunks = matmul_chunks(int(items), get_dispatch_lanes())
    mx4b_reserve(int64(nchunks) * n, int64(nchunks) * nb)
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
            unsafe {
                for (ci0 in range(cb, ce)) {
                    let ci = int64(ci0)
                    var qrow = qsp + ci * n
                    var srow = ssp + ci * nb
                    for (ii in range64(ci * items / int64(nchunks), (ci + 1l) * items / int64(nchunks))) {
                        let r = ii / d
                        let row = ii % d
                        let woff = offs[r * 3l]
                        let row0 = offs[r * 3l + 1l]
                        let cnt = offs[r * 3l + 2l]
                        if (cnt == 0l) {
                            continue
                        }
                        mx4_dequant_row_x64(lutp, wn + woff / 2l + row * (n / 2l), we + woff / 32l + row * nb, qrow, srow, n)
                        for (tk in range64(cnt)) {
                            myp[(row0 + tk) * d + row] = dot_q8q8_x64dot4x4(qrow, srow, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                        }
                        if (bp != null) {
                            let b = bp[boffs[r] + row]
                            for (tk in range64(cnt)) {
                                myp[(row0 + tk) * d + row] += b
                            }
                        }
                    }
                }
            }
        }
    }
}

// grp4 mx4 batch groupN (the repack backend): flattened (region, group) items, one 4-row group
// strip per chunk — dequant the group once, sweep its region's token rows with the grp4x2/grp4
// tiles. Chunks span experts, so bucket-count imbalance load-balances through the fifo (the
// llama.cpp mul_mat_id shape). Bias folds as an add-after pass over the item's outputs.
def private mx4q8_batch_groupn_kernel_x64_grp4(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let ng = d / 4l
    let lanes = get_dispatch_lanes()
    let items = nregions * ng
    let nchunks = matmul_chunks(int(items) * 4, lanes * get_q8_batch_chunks_per_job())
    mx4b_reserve(max(int64(nchunks) * 4l * n, n), max(int64(nchunks) * 4l * nb, nb))
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        if (ng > 0l) {
            maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
                unsafe {
                    for (ci0 in range(cb, ce)) {
                        let ci = int64(ci0)
                        let i0 = ci * items / int64(nchunks)
                        let i1 = (ci + 1l) * items / int64(nchunks)
                        var gq = qsp + ci * 4l * n
                        var gs = ssp + ci * 4l * nb
                        for (ii in range64(i0, i1)) {
                            let r = ii / ng
                            let g = ii % ng
                            let woff = offs[r * 3l]
                            let row0 = offs[r * 3l + 1l]
                            let cnt = offs[r * 3l + 2l]
                            if (cnt == 0l) {
                                continue
                            }
                            mx4_dequant_grp4_x64(lutp, wn + woff / 2l + g * 4l * (n / 2l), we + woff / 32l + g * 4l * nb, gq, gs, n)
                            let cnt2 = (cnt / 2l) * 2l
                            var tk = 0l
                            while (tk < cnt2) {     // 4-row × 2-token tiles (the throughput path)
                                dot_q8q8_x64grp4x2(myp, gq, gs, xqp, xsp, n, d, g, row0 + tk)
                                tk += 2l
                            }
                            while (tk < cnt) {      // odd-count tail: one token at a time
                                let f = dot_q8q8_x64grp4(gq, gs, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                                myp[(row0 + tk) * d + g * 4l + 0l] = f.x
                                myp[(row0 + tk) * d + g * 4l + 1l] = f.y
                                myp[(row0 + tk) * d + g * 4l + 2l] = f.z
                                myp[(row0 + tk) * d + g * 4l + 3l] = f.w
                                tk++
                            }
                            if (bp != null) {
                                let bb = boffs[r] + g * 4l
                                let b0 = bp[bb]
                                let b1 = bp[bb + 1l]
                                let b2 = bp[bb + 2l]
                                let b3 = bp[bb + 3l]
                                for (t2 in range64(cnt)) {
                                    let yb = (row0 + t2) * d + g * 4l
                                    myp[yb + 0l] += b0
                                    myp[yb + 1l] += b1
                                    myp[yb + 2l] += b2
                                    myp[yb + 3l] += b3
                                }
                            }
                        }
                    }
                }
            }
        }
        for (r in range64(nregions)) {   // row tails (d % 4): row-major, chunk 0's slot (post-join)
            let woff = offs[r * 3l]
            let row0 = offs[r * 3l + 1l]
            let cnt = offs[r * 3l + 2l]
            for (i in range64(ng * 4l, d)) {
                mx4_dequant_row_x64(lutp, wn + woff / 2l + i * (n / 2l), we + woff / 32l + i * nb, qsp, ssp, n)
                for (tk in range64(cnt)) {
                    var v = dot_q8q8_x64dot4x4(qsp, ssp, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                    if (bp != null) {
                        v += bp[boffs[r] + i]
                    }
                    myp[(row0 + tk) * d + i] = v
                }
            }
        }
    }
}

// ===== AVX KERNEL MATRIX (experimental, default OFF) =====
// VNNI / AVX-512 twins of the shipped kernels, one backend per (ISA tier x kernel shape) cell so a
// bare-metal box that has the tiers can A/B them in-process via DASLLAMA_PIN_BACKEND (this 3990X
// has none — the matrix exists to be measured on rented hardware, then promoted or deleted).
// Registration is gated g_avx_matrix_enabled && cpu_supports(...); priorities all sit BELOW the
// shipped backends, so even with the flag on nothing auto-selects — pin-only by construction.
// Every dot delegates to a proven intrinsic when its tier is absent (see x64_avx.das), so a
// force-registered backend on this box runs the ymm sign-trick path and stays CORRECT — that is
// what the exactness probes exercise here.

var public g_avx_matrix_enabled = false   // DASLLAMA_AVX_MATRIX=1 — master switch, default OFF
var public g_avx_matrix_force = false     // DASLLAMA_AVX_MATRIX_FORCE=1 — register tiers the box lacks (fallback-correct; probe/validation only)

def private matrix_has(feature : string) : bool {
    return g_avx_matrix_force || cpu_supports(feature)
}

//! dot_q8q8_x64dot4x4 with the VNNI dot step (dot32_vnni: ONE VPDPBUSD per block instead of the
//! VPMADDUBSW+VPMADDWD pair) — identical exact block sums, identical flush. Not `private` (worker
//! lambdas call it).
[hint(unsafe_range_check, noalias = wq, noalias = ws, noalias = xq, noalias = xs)]
def dot_q8q8_x64vnni(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var f0 = 0.0
    var f1 = 0.0
    var f2 = 0.0
    var f3 = 0.0
    var bi = 0l
    unsafe {
        while (bi + 4l <= nb) {
            let bb = bi * 32l
            var a0 = int4(0, 0, 0, 0)
            var a1 = int4(0, 0, 0, 0)
            var a2 = int4(0, 0, 0, 0)
            var a3 = int4(0, 0, 0, 0)
            a0 = dot32_vnni(a0, wq + bb, xq + bb)
            a1 = dot32_vnni(a1, wq + bb + 32l, xq + bb + 32l)
            a2 = dot32_vnni(a2, wq + bb + 64l, xq + bb + 64l)
            a3 = dot32_vnni(a3, wq + bb + 96l, xq + bb + 96l)
            f0 += float(a0.x + a0.y + a0.z + a0.w) * ws[bi + 0l] * xs[bi + 0l]
            f1 += float(a1.x + a1.y + a1.z + a1.w) * ws[bi + 1l] * xs[bi + 1l]
            f2 += float(a2.x + a2.y + a2.z + a2.w) * ws[bi + 2l] * xs[bi + 2l]
            f3 += float(a3.x + a3.y + a3.z + a3.w) * ws[bi + 3l] * xs[bi + 3l]
            bi += 4l
        }
        while (bi < nb) {
            let base = bi * 32l
            var acc = int4(0, 0, 0, 0)
            acc = dot32_vnni(acc, wq + base, xq + base)
            f0 += float(acc.x + acc.y + acc.z + acc.w) * ws[bi] * xs[bi]
            bi++
        }
    }
    return f0 + f1 + f2 + f3
}

//! dot_q8q8_x64acc8 with the VNNI dot step (dot32_acc8_vnni) — identical exact quads, identical
//! float tail. Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wq, noalias = ws, noalias = xq, noalias = xs)]
def dot_q8q8_x64acc8vnni(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var a0 : float[8]
    var a1 : float[8]
    var a2 : float[8]
    var a3 : float[8]
    var bi = 0l
    unsafe {
        var p0 = addr(a0[0])
        var p1 = addr(a1[0])
        var p2 = addr(a2[0])
        var p3 = addr(a3[0])
        while (bi + 4l <= nb) {
            let bb = bi * 32l
            dot32_acc8_vnni(p0, wq + bb, xq + bb, ws[bi] * xs[bi])
            dot32_acc8_vnni(p1, wq + bb + 32l, xq + bb + 32l, ws[bi + 1l] * xs[bi + 1l])
            dot32_acc8_vnni(p2, wq + bb + 64l, xq + bb + 64l, ws[bi + 2l] * xs[bi + 2l])
            dot32_acc8_vnni(p3, wq + bb + 96l, xq + bb + 96l, ws[bi + 3l] * xs[bi + 3l])
            bi += 4l
        }
        while (bi < nb) {
            dot32_acc8_vnni(p0, wq + bi * 32l, xq + bi * 32l, ws[bi] * xs[bi])
            bi++
        }
    }
    var t = 0.0
    for (j in range(8)) {
        t += (a0[j] + a1[j]) + (a2[j] + a3[j])
    }
    return t
}

//! dot_q8q8_x64grp4 with the VNNI dot step — identical exact block sums and float4 flush. Not
//! `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wg, noalias = sg, noalias = xq, noalias = xs)]
def dot_q8q8_x64grp4_vnni(wg : int8 const?; sg : float const?; xq : int8 const?; xs : float const?; n : int64) : float4 {
    let nb = n / 32l
    var f = float4(0.0, 0.0, 0.0, 0.0)
    unsafe {
        for (bi in range64(nb)) {
            let wb = bi * 128l
            let xb = xq + bi * 32l
            var a0 = int4(0, 0, 0, 0)
            var a1 = int4(0, 0, 0, 0)
            var a2 = int4(0, 0, 0, 0)
            var a3 = int4(0, 0, 0, 0)
            a0 = dot32_vnni(a0, wg + wb, xb)
            a1 = dot32_vnni(a1, wg + wb + 32l, xb)
            a2 = dot32_vnni(a2, wg + wb + 64l, xb)
            a3 = dot32_vnni(a3, wg + wb + 96l, xb)
            let s = float4(sg[bi * 4l], sg[bi * 4l + 1l], sg[bi * 4l + 2l], sg[bi * 4l + 3l])
            let xsb = xs[bi]
            f += float4(float(a0.x + a0.y + a0.z + a0.w), float(a1.x + a1.y + a1.z + a1.w),
                float(a2.x + a2.y + a2.z + a2.w), float(a3.x + a3.y + a3.z + a3.w)) * s * float4(xsb, xsb, xsb, xsb)
        }
    }
    return f
}

//! dot_q8q8_x64grp4x2 with the VNNI dot step — identical exact tile, token-major writes unchanged.
//! ntok - t0 >= 2 assumed. Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wg, noalias = sg, noalias = xqp, noalias = xsp)]
def dot_q8q8_x64grp4x2_vnni(var yp : float?; wg : int8 const?; sg : float const?; xqp : int8 const?; xsp : float const?; n, d, g, t0 : int64) {
    let nb = n / 32l
    var f0 = float4(0.0, 0.0, 0.0, 0.0)
    var f1 = float4(0.0, 0.0, 0.0, 0.0)
    unsafe {
        let x0 = xqp + (t0 + 0l) * n
        let x1 = xqp + (t0 + 1l) * n
        let xs0 = xsp + (t0 + 0l) * nb
        let xs1 = xsp + (t0 + 1l) * nb
        for (bi in range64(nb)) {
            let wb = bi * 128l
            let xb = bi * 32l
            var a00 = int4(0, 0, 0, 0)
            var a01 = int4(0, 0, 0, 0)
            var a02 = int4(0, 0, 0, 0)
            var a03 = int4(0, 0, 0, 0)
            var a10 = int4(0, 0, 0, 0)
            var a11 = int4(0, 0, 0, 0)
            var a12 = int4(0, 0, 0, 0)
            var a13 = int4(0, 0, 0, 0)
            a00 = dot32_vnni(a00, wg + wb, x0 + xb); a10 = dot32_vnni(a10, wg + wb, x1 + xb)
            a01 = dot32_vnni(a01, wg + wb + 32l, x0 + xb); a11 = dot32_vnni(a11, wg + wb + 32l, x1 + xb)
            a02 = dot32_vnni(a02, wg + wb + 64l, x0 + xb); a12 = dot32_vnni(a12, wg + wb + 64l, x1 + xb)
            a03 = dot32_vnni(a03, wg + wb + 96l, x0 + xb); a13 = dot32_vnni(a13, wg + wb + 96l, x1 + xb)
            let s = float4(sg[bi * 4l], sg[bi * 4l + 1l], sg[bi * 4l + 2l], sg[bi * 4l + 3l])
            let q0 = xs0[bi]
            let q1 = xs1[bi]
            f0 += float4(float(a00.x + a00.y + a00.z + a00.w), float(a01.x + a01.y + a01.z + a01.w),
                float(a02.x + a02.y + a02.z + a02.w), float(a03.x + a03.y + a03.z + a03.w)) * s * float4(q0, q0, q0, q0)
            f1 += float4(float(a10.x + a10.y + a10.z + a10.w), float(a11.x + a11.y + a11.z + a11.w),
                float(a12.x + a12.y + a12.z + a12.w), float(a13.x + a13.y + a13.z + a13.w)) * s * float4(q1, q1, q1, q1)
        }
        let r = g * 4l
        yp[(t0 + 0l) * d + r + 0l] = f0.x
        yp[(t0 + 0l) * d + r + 1l] = f0.y
        yp[(t0 + 0l) * d + r + 2l] = f0.z
        yp[(t0 + 0l) * d + r + 3l] = f0.w
        yp[(t0 + 1l) * d + r + 0l] = f1.x
        yp[(t0 + 1l) * d + r + 1l] = f1.y
        yp[(t0 + 1l) * d + r + 2l] = f1.z
        yp[(t0 + 1l) * d + r + 3l] = f1.w
    }
}

//! dot_mx4q8_x64 with the VNNI dot step (dot32_mx4_vnni: PSHUFB dequant + ONE VPDPBUSD) — identical
//! exact block sums, identical 4-acc flush. Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = lut, noalias = wn, noalias = we, noalias = xq, noalias = xs)]
def dot_mx4q8_x64vnni(lut : int8 const?; wn : uint8 const?; we : uint8 const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var f0 = 0.0
    var f1 = 0.0
    var f2 = 0.0
    var f3 = 0.0
    var bi = 0l
    unsafe {
        while (bi + 4l <= nb) {
            var a0 = int4(0, 0, 0, 0)
            var a1 = int4(0, 0, 0, 0)
            var a2 = int4(0, 0, 0, 0)
            var a3 = int4(0, 0, 0, 0)
            a0 = dot32_mx4_vnni(a0, lut, wn + bi * 16l, xq + bi * 32l)
            a1 = dot32_mx4_vnni(a1, lut, wn + bi * 16l + 16l, xq + bi * 32l + 32l)
            a2 = dot32_mx4_vnni(a2, lut, wn + bi * 16l + 32l, xq + bi * 32l + 64l)
            a3 = dot32_mx4_vnni(a3, lut, wn + bi * 16l + 48l, xq + bi * 32l + 96l)
            f0 += float(a0.x + a0.y + a0.z + a0.w) * e8m0_half(uint(we[bi])) * xs[bi]
            f1 += float(a1.x + a1.y + a1.z + a1.w) * e8m0_half(uint(we[bi + 1l])) * xs[bi + 1l]
            f2 += float(a2.x + a2.y + a2.z + a2.w) * e8m0_half(uint(we[bi + 2l])) * xs[bi + 2l]
            f3 += float(a3.x + a3.y + a3.z + a3.w) * e8m0_half(uint(we[bi + 3l])) * xs[bi + 3l]
            bi += 4l
        }
        while (bi < nb) {
            var acc = int4(0, 0, 0, 0)
            acc = dot32_mx4_vnni(acc, lut, wn + bi * 16l, xq + bi * 32l)
            f0 += float(acc.x + acc.y + acc.z + acc.w) * e8m0_half(uint(we[bi])) * xs[bi]
            bi++
        }
    }
    return f0 + f1 + f2 + f3
}

//! One Q8 row against one token on zmm: dot64_acc16 consumes TWO blocks per call into 4
//! memory-backed float[16] accumulators (LICM-promoted; the acc8 structure at 512 bits, 8 blocks
//! per unrolled iter), odd-block tail via dot32_acc8 into the first accumulator's low half, one
//! 64-lane reduce at row end. TOLERANCE-class vs portable (per-lane float partials, like acc8).
//! Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wq, noalias = ws, noalias = xq, noalias = xs)]
def dot_q8q8_x64z16(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var a0 : float[16]
    var a1 : float[16]
    var a2 : float[16]
    var a3 : float[16]
    var bi = 0l
    unsafe {
        var p0 = addr(a0[0])
        var p1 = addr(a1[0])
        var p2 = addr(a2[0])
        var p3 = addr(a3[0])
        while (bi + 8l <= nb) {
            let bb = bi * 32l
            dot64_acc16(p0, wq + bb, xq + bb, ws[bi] * xs[bi], ws[bi + 1l] * xs[bi + 1l])
            dot64_acc16(p1, wq + bb + 64l, xq + bb + 64l, ws[bi + 2l] * xs[bi + 2l], ws[bi + 3l] * xs[bi + 3l])
            dot64_acc16(p2, wq + bb + 128l, xq + bb + 128l, ws[bi + 4l] * xs[bi + 4l], ws[bi + 5l] * xs[bi + 5l])
            dot64_acc16(p3, wq + bb + 192l, xq + bb + 192l, ws[bi + 6l] * xs[bi + 6l], ws[bi + 7l] * xs[bi + 7l])
            bi += 8l
        }
        while (bi + 2l <= nb) {
            let bb = bi * 32l
            dot64_acc16(p0, wq + bb, xq + bb, ws[bi] * xs[bi], ws[bi + 1l] * xs[bi + 1l])
            bi += 2l
        }
        if (bi < nb) {
            dot32_acc8(p0, wq + bi * 32l, xq + bi * 32l, ws[bi] * xs[bi])
        }
    }
    var t = 0.0
    for (j in range(16)) {
        t += (a0[j] + a1[j]) + (a2[j] + a3[j])
    }
    return t
}

//! dot_q8q8_x64z16 with the VNNI dot step (dot64_acc16_vnni: ONE zmm VPDPBUSD per block pair).
//! Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = wq, noalias = ws, noalias = xq, noalias = xs)]
def dot_q8q8_x64z16vnni(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var a0 : float[16]
    var a1 : float[16]
    var a2 : float[16]
    var a3 : float[16]
    var bi = 0l
    unsafe {
        var p0 = addr(a0[0])
        var p1 = addr(a1[0])
        var p2 = addr(a2[0])
        var p3 = addr(a3[0])
        while (bi + 8l <= nb) {
            let bb = bi * 32l
            dot64_acc16_vnni(p0, wq + bb, xq + bb, ws[bi] * xs[bi], ws[bi + 1l] * xs[bi + 1l])
            dot64_acc16_vnni(p1, wq + bb + 64l, xq + bb + 64l, ws[bi + 2l] * xs[bi + 2l], ws[bi + 3l] * xs[bi + 3l])
            dot64_acc16_vnni(p2, wq + bb + 128l, xq + bb + 128l, ws[bi + 4l] * xs[bi + 4l], ws[bi + 5l] * xs[bi + 5l])
            dot64_acc16_vnni(p3, wq + bb + 192l, xq + bb + 192l, ws[bi + 6l] * xs[bi + 6l], ws[bi + 7l] * xs[bi + 7l])
            bi += 8l
        }
        while (bi + 2l <= nb) {
            let bb = bi * 32l
            dot64_acc16_vnni(p0, wq + bb, xq + bb, ws[bi] * xs[bi], ws[bi + 1l] * xs[bi + 1l])
            bi += 2l
        }
        if (bi < nb) {
            dot32_acc8_vnni(p0, wq + bi * 32l, xq + bi * 32l, ws[bi] * xs[bi])
        }
    }
    var t = 0.0
    for (j in range(16)) {
        t += (a0[j] + a1[j]) + (a2[j] + a3[j])
    }
    return t
}

//! mx4_dequant_row_x64 at zmm granularity: mx4_dequant64 expands TWO blocks per call (one zmm
//! VPSHUFB + 64-byte store), odd-block tail via mx4_dequant32. Byte-for-byte the row-major expand.
//! Not `private` (worker lambdas call it).
[hint(unsafe_range_check, noalias = lut, noalias = wn, noalias = we, noalias = q, noalias = s)]
def mx4_dequant_row_x64z(lut : int8 const?; wn : uint8 const?; we : uint8 const?; var q : int8?; var s : float?; n : int64) {
    let nb = n / 32l
    var bi = 0l
    unsafe {
        while (bi + 2l <= nb) {
            mx4_dequant64(lut, wn + bi * 16l, q + bi * 32l)
            s[bi] = e8m0_half(uint(we[bi]))
            s[bi + 1l] = e8m0_half(uint(we[bi + 1l]))
            bi += 2l
        }
        if (bi < nb) {
            mx4_dequant32(lut, wn + bi * 16l, q + bi * 32l)
            s[bi] = e8m0_half(uint(we[bi]))
        }
    }
}

// Matrix kernel wrappers: verbatim copies of the shipped kernels with only the row dot swapped
// (the house per-variant pattern — no function-pointer indirection in hot loops). Grouped by
// backend family; scheduling, oversplit, and TB choices mirror each wrapper's source kernel so a
// pin-A/B isolates the dot alone.

// --- x64-vnni256 (row-major dot4x4 shape, dot32_vnni) ---

def private q8q8_kernel_x64_vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_x64vnni(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_x64_vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_x64vnni(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

def private q8q8_group3_kernel_x64_vnni(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                        woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    parallel_for(0, int(dtot), matmul_chunks(int(dtot), get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_x64vnni(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_x64vnni(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_x64vnni(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
        wg |> notify_and_release
    }
}

def private q8q8_groupn_kernel_x64_vnni(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * d), matmul_chunks(int(nregions * d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let ii = int64(i)
                let r = ii / d
                let row = ii % d
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var v = dot_q8q8_x64vnni(wp + woff + row * n, sp + woff / 32l + row * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + row]
                }
                myp[ii] = v
            }
        }
    }
}

def private mx4q8_kernel_x64_vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    myp[i] = dot_mx4q8_x64vnni(lutp, wn + int64(i) * (n / 2l), we + int64(i) * nb, xqp, xsp, n)
                }
            }
        }
    }
}

def private mx4q8_groupn_kernel_x64_vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * d), matmul_chunks(int(nregions * d), get_dispatch_lanes())) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    let ii = int64(i)
                    let r = ii / d
                    let row = ii % d
                    let woff = offs[r * 2l]
                    let xoff = offs[r * 2l + 1l]
                    var v = dot_mx4q8_x64vnni(lutp, wn + woff / 2l + row * (n / 2l), we + woff / 32l + row * nb,
                        xqp + xoff, xsp + xoff / 32l, n)
                    if (bp != null) {
                        v += bp[boffs[r] + row]
                    }
                    myp[ii] = v
                }
            }
        }
    }
}

def private mx4q8_batch_kernel_x64_vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let nchunks = matmul_chunks(int(d), get_dispatch_lanes())
    mx4b_reserve(int64(nchunks) * n, int64(nchunks) * nb)
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
            unsafe {
                for (ci0 in range(cb, ce)) {
                    let ci = int64(ci0)
                    var qrow = qsp + ci * n
                    var srow = ssp + ci * nb
                    for (i in range64(ci * d / int64(nchunks), (ci + 1l) * d / int64(nchunks))) {
                        mx4_dequant_row_x64(lutp, wn + i * (n / 2l), we + i * nb, qrow, srow, n)
                        for (tk in range64(ntok)) {
                            myp[tk * d + i] = dot_q8q8_x64vnni(qrow, srow, xqp + tk * n, xsp + tk * nb, n)
                        }
                    }
                }
            }
        }
    }
}

def private mx4q8_batch_groupn_kernel_x64_vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let items = nregions * d
    let nchunks = matmul_chunks(int(items), get_dispatch_lanes())
    mx4b_reserve(int64(nchunks) * n, int64(nchunks) * nb)
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
            unsafe {
                for (ci0 in range(cb, ce)) {
                    let ci = int64(ci0)
                    var qrow = qsp + ci * n
                    var srow = ssp + ci * nb
                    for (ii in range64(ci * items / int64(nchunks), (ci + 1l) * items / int64(nchunks))) {
                        let r = ii / d
                        let row = ii % d
                        let woff = offs[r * 3l]
                        let row0 = offs[r * 3l + 1l]
                        let cnt = offs[r * 3l + 2l]
                        if (cnt == 0l) {
                            continue
                        }
                        mx4_dequant_row_x64(lutp, wn + woff / 2l + row * (n / 2l), we + woff / 32l + row * nb, qrow, srow, n)
                        for (tk in range64(cnt)) {
                            myp[(row0 + tk) * d + row] = dot_q8q8_x64vnni(qrow, srow, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                        }
                        if (bp != null) {
                            let b = bp[boffs[r] + row]
                            for (tk in range64(cnt)) {
                                myp[(row0 + tk) * d + row] += b
                            }
                        }
                    }
                }
            }
        }
    }
}

// --- x64-vnni256-acc8 (row-major acc8 shape, dot32_acc8_vnni) ---

def private q8q8_kernel_x64_acc8vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_x64acc8vnni(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_x64_acc8vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    // OVERSPLIT: mirrors the acc8 batch kernel (idle workers steal a late-woken worker's chunks)
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_x64acc8vnni(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

def private q8q8_group3_kernel_x64_acc8vnni(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                            woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    parallel_for(0, int(dtot), matmul_chunks(int(dtot), get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_x64acc8vnni(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_x64acc8vnni(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_x64acc8vnni(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
        wg |> notify_and_release
    }
}

// --- x64-vnni256-repack (grp4 block-interleave shape, dot32_vnni tiles) ---

def private q8q8_kernel_x64_grp4vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(ng), matmul_chunks(int(ng) * 4, get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                let f = dot_q8q8_x64grp4_vnni(wp + g * 4l * n, sp + g * 4l * nb, xqp, xsp, n)
                myp[g * 4l + 0l] = f.x
                myp[g * 4l + 1l] = f.y
                myp[g * 4l + 2l] = f.z
                myp[g * 4l + 3l] = f.w
            }
        }
    }
    unsafe {
        for (i in range64(ng * 4l, d)) {
            myp[i] = dot_q8q8_x64vnni(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

def private q8q8_batch_kernel_x64_grp4vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var myp = yp
    // Token-blocked + oversplit floored at 4 groups/chunk — mirrors the grp4 batch kernel
    let TB = effective_token_block(g_q8_token_block, n)
    let lanes = get_dispatch_lanes()
    let njobs = matmul_chunks(int(ng) * 4, lanes * get_q8_batch_chunks_per_job())
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(ng), njobs) $(rb, re) {
        unsafe {
            var tb = 0l
            while (tb < ntok) {
                let tbe = min(tb + TB, ntok)
                let tb2 = tb + ((tbe - tb) / 2l) * 2l
                for (gi in range(rb, re)) {
                    let g = int64(gi)
                    let wgp = wp + g * 4l * n
                    let sgp = sp + g * 4l * nb
                    var tk = tb
                    while (tk < tb2) {     // 4-row × 2-token tiles (the throughput path)
                        dot_q8q8_x64grp4x2_vnni(myp, wgp, sgp, xqp, xsp, n, d, g, tk)
                        tk += 2l
                    }
                    while (tk < tbe) {    // token tail within this block: one token at a time
                        let f = dot_q8q8_x64grp4_vnni(wgp, sgp, xqp + tk * n, xsp + tk * nb, n)
                        myp[tk * d + g * 4l + 0l] = f.x
                        myp[tk * d + g * 4l + 1l] = f.y
                        myp[tk * d + g * 4l + 2l] = f.z
                        myp[tk * d + g * 4l + 3l] = f.w
                        tk++
                    }
                }
                tb += TB
            }
        }
    }
    unsafe {
        for (i in range64(ng * 4l, d)) {   // row tail (d % 4): row-major
            let wrow = wp + i * n
            let srow = sp + i * nb
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_x64vnni(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
}

def private q8q8_group3_kernel_x64_grp4vnni(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                            woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let ng0 = d0 / 4l
    let ng1 = d1 / 4l
    let ng2 = d2 / 4l
    let ngtot = ng0 + ng1 + ng2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    parallel_for(0, int(ngtot), matmul_chunks(int(ngtot) * 4, get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < ng0) {
                    let f = dot_q8q8_x64grp4_vnni(wp + woff0 + g * 4l * n, sp + woff0 / 32l + g * 4l * nb, xqp, xsp, n)
                    w0[g * 4l + 0l] = f.x
                    w0[g * 4l + 1l] = f.y
                    w0[g * 4l + 2l] = f.z
                    w0[g * 4l + 3l] = f.w
                } elif (g < ng0 + ng1) {
                    let r = g - ng0
                    let f = dot_q8q8_x64grp4_vnni(wp + woff1 + r * 4l * n, sp + woff1 / 32l + r * 4l * nb, xqp, xsp, n)
                    w1[r * 4l + 0l] = f.x
                    w1[r * 4l + 1l] = f.y
                    w1[r * 4l + 2l] = f.z
                    w1[r * 4l + 3l] = f.w
                } else {
                    let r = g - ng0 - ng1
                    let f = dot_q8q8_x64grp4_vnni(wp + woff2 + r * 4l * n, sp + woff2 / 32l + r * 4l * nb, xqp, xsp, n)
                    w2[r * 4l + 0l] = f.x
                    w2[r * 4l + 1l] = f.y
                    w2[r * 4l + 2l] = f.z
                    w2[r * 4l + 3l] = f.w
                }
            }
        }
        wg |> notify_and_release
    }
    unsafe {
        for (i in range64(ng0 * 4l, d0)) {
            w0[i] = dot_q8q8_x64vnni(wp + woff0 + i * n, sp + woff0 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng1 * 4l, d1)) {
            w1[i] = dot_q8q8_x64vnni(wp + woff1 + i * n, sp + woff1 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng2 * 4l, d2)) {
            w2[i] = dot_q8q8_x64vnni(wp + woff2 + i * n, sp + woff2 / 32l + i * nb, xqp, xsp, n)
        }
    }
}

def private q8q8_groupn_kernel_x64_grp4vnni(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var myp = yp
    maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * ng), matmul_chunks(int(nregions * ng) * 4, get_dispatch_lanes())) $(gb, ge) {
        unsafe {
            for (gi in range(gb, ge)) {
                let gg = int64(gi)
                let r = gg / ng
                let g = gg % ng
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var f = dot_q8q8_x64grp4_vnni(wp + woff + g * 4l * n, sp + woff / 32l + g * 4l * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    let bb = boffs[r] + g * 4l
                    f += float4(bp[bb], bp[bb + 1l], bp[bb + 2l], bp[bb + 3l])
                }
                let yb = r * d + g * 4l
                myp[yb + 0l] = f.x
                myp[yb + 1l] = f.y
                myp[yb + 2l] = f.z
                myp[yb + 3l] = f.w
            }
        }
    }
    unsafe {
        for (r in range64(nregions)) {   // row tails (d % 4): row-major per region
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            for (i in range64(ng * 4l, d)) {
                var v = dot_q8q8_x64vnni(wp + woff + i * n, sp + woff / 32l + i * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + i]
                }
                myp[r * d + i] = v
            }
        }
    }
}

def private mx4q8_batch_kernel_x64_grp4vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let ng = d / 4l
    let TB = effective_token_block(g_q8_token_block, n)
    let lanes = get_dispatch_lanes()
    let nchunks = matmul_chunks(int(ng) * 4, lanes * get_q8_batch_chunks_per_job())
    mx4b_reserve(max(int64(nchunks) * 4l * n, n), max(int64(nchunks) * 4l * nb, nb))
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        if (ng > 0l) {
            maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
                unsafe {
                    for (ci0 in range(cb, ce)) {
                        let ci = int64(ci0)
                        let g0 = ci * ng / int64(nchunks)
                        let g1 = (ci + 1l) * ng / int64(nchunks)
                        if (g0 == g1) {
                            continue
                        }
                        var gq = qsp + ci * 4l * n
                        var gs = ssp + ci * 4l * nb
                        var tb = 0l
                        while (tb < ntok) {
                            let tbe = min(tb + TB, ntok)
                            let tb2 = tb + ((tbe - tb) / 2l) * 2l
                            for (gi in range64(g0, g1)) {
                                mx4_dequant_grp4_x64(lutp, wn + gi * 4l * (n / 2l), we + gi * 4l * nb, gq, gs, n)
                                var tk = tb
                                while (tk < tb2) {     // 4-row × 2-token tiles (the throughput path)
                                    dot_q8q8_x64grp4x2_vnni(myp, gq, gs, xqp, xsp, n, d, gi, tk)
                                    tk += 2l
                                }
                                while (tk < tbe) {    // token tail within this block: one at a time
                                    let f = dot_q8q8_x64grp4_vnni(gq, gs, xqp + tk * n, xsp + tk * nb, n)
                                    myp[tk * d + gi * 4l + 0l] = f.x
                                    myp[tk * d + gi * 4l + 1l] = f.y
                                    myp[tk * d + gi * 4l + 2l] = f.z
                                    myp[tk * d + gi * 4l + 3l] = f.w
                                    tk++
                                }
                            }
                            tb += TB
                        }
                    }
                }
            }
        }
        for (i in range64(ng * 4l, d)) {   // row tail (d % 4): row-major, chunk 0's slot (post-join)
            mx4_dequant_row_x64(lutp, wn + i * (n / 2l), we + i * nb, qsp, ssp, n)
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_x64vnni(qsp, ssp, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
}

def private mx4q8_batch_groupn_kernel_x64_grp4vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let ng = d / 4l
    let lanes = get_dispatch_lanes()
    let items = nregions * ng
    let nchunks = matmul_chunks(int(items) * 4, lanes * get_q8_batch_chunks_per_job())
    mx4b_reserve(max(int64(nchunks) * 4l * n, n), max(int64(nchunks) * 4l * nb, nb))
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        if (ng > 0l) {
            maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
                unsafe {
                    for (ci0 in range(cb, ce)) {
                        let ci = int64(ci0)
                        let i0 = ci * items / int64(nchunks)
                        let i1 = (ci + 1l) * items / int64(nchunks)
                        var gq = qsp + ci * 4l * n
                        var gs = ssp + ci * 4l * nb
                        for (ii in range64(i0, i1)) {
                            let r = ii / ng
                            let g = ii % ng
                            let woff = offs[r * 3l]
                            let row0 = offs[r * 3l + 1l]
                            let cnt = offs[r * 3l + 2l]
                            if (cnt == 0l) {
                                continue
                            }
                            mx4_dequant_grp4_x64(lutp, wn + woff / 2l + g * 4l * (n / 2l), we + woff / 32l + g * 4l * nb, gq, gs, n)
                            let cnt2 = (cnt / 2l) * 2l
                            var tk = 0l
                            while (tk < cnt2) {     // 4-row × 2-token tiles (the throughput path)
                                dot_q8q8_x64grp4x2_vnni(myp, gq, gs, xqp, xsp, n, d, g, row0 + tk)
                                tk += 2l
                            }
                            while (tk < cnt) {      // odd-count tail: one token at a time
                                let f = dot_q8q8_x64grp4_vnni(gq, gs, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                                myp[(row0 + tk) * d + g * 4l + 0l] = f.x
                                myp[(row0 + tk) * d + g * 4l + 1l] = f.y
                                myp[(row0 + tk) * d + g * 4l + 2l] = f.z
                                myp[(row0 + tk) * d + g * 4l + 3l] = f.w
                                tk++
                            }
                            if (bp != null) {
                                let bb = boffs[r] + g * 4l
                                let b0 = bp[bb]
                                let b1 = bp[bb + 1l]
                                let b2 = bp[bb + 2l]
                                let b3 = bp[bb + 3l]
                                for (t2 in range64(cnt)) {
                                    let yb = (row0 + t2) * d + g * 4l
                                    myp[yb + 0l] += b0
                                    myp[yb + 1l] += b1
                                    myp[yb + 2l] += b2
                                    myp[yb + 3l] += b3
                                }
                            }
                        }
                    }
                }
            }
        }
        for (r in range64(nregions)) {   // row tails (d % 4): row-major, chunk 0's slot (post-join)
            let woff = offs[r * 3l]
            let row0 = offs[r * 3l + 1l]
            let cnt = offs[r * 3l + 2l]
            for (i in range64(ng * 4l, d)) {
                mx4_dequant_row_x64(lutp, wn + woff / 2l + i * (n / 2l), we + woff / 32l + i * nb, qsp, ssp, n)
                for (tk in range64(cnt)) {
                    var v = dot_q8q8_x64vnni(qsp, ssp, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                    if (bp != null) {
                        v += bp[boffs[r] + i]
                    }
                    myp[(row0 + tk) * d + i] = v
                }
            }
        }
    }
}

// --- x64-avx512bw / x64-avx512vnni (row-major z16 shape, dot64_acc16 / dot64_acc16_vnni) ---

def private q8q8_kernel_x64_z16(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_x64z16(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_x64_z16(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    // OVERSPLIT: mirrors the acc8 batch kernel (idle workers steal a late-woken worker's chunks)
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_x64z16(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

def private q8q8_group3_kernel_x64_z16(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                       woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    parallel_for(0, int(dtot), matmul_chunks(int(dtot), get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_x64z16(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_x64z16(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_x64z16(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
        wg |> notify_and_release
    }
}

def private q8q8_groupn_kernel_x64_z16(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * d), matmul_chunks(int(nregions * d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let ii = int64(i)
                let r = ii / d
                let row = ii % d
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var v = dot_q8q8_x64z16(wp + woff + row * n, sp + woff / 32l + row * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + row]
                }
                myp[ii] = v
            }
        }
    }
}

def private q8q8_kernel_x64_z16vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_x64z16vnni(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_x64_z16vnni(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    // OVERSPLIT: mirrors the acc8 batch kernel (idle workers steal a late-woken worker's chunks)
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(d), matmul_chunks(int(d), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_x64z16vnni(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

def private q8q8_group3_kernel_x64_z16vnni(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                           woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    parallel_for(0, int(dtot), matmul_chunks(int(dtot), get_dispatch_lanes())) $(rb, re, wg) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_x64z16vnni(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_x64z16vnni(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_x64z16vnni(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
        wg |> notify_and_release
    }
}

def private q8q8_groupn_kernel_x64_z16vnni(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * d), matmul_chunks(int(nregions * d), get_dispatch_lanes())) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let ii = int64(i)
                let r = ii / d
                let row = ii % d
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var v = dot_q8q8_x64z16vnni(wp + woff + row * n, sp + woff / 32l + row * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + row]
                }
                myp[ii] = v
            }
        }
    }
}

def private mx4q8_batch_kernel_x64_z16vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let nchunks = matmul_chunks(int(d), get_dispatch_lanes())
    mx4b_reserve(int64(nchunks) * n, int64(nchunks) * nb)
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
            unsafe {
                for (ci0 in range(cb, ce)) {
                    let ci = int64(ci0)
                    var qrow = qsp + ci * n
                    var srow = ssp + ci * nb
                    for (i in range64(ci * d / int64(nchunks), (ci + 1l) * d / int64(nchunks))) {
                        mx4_dequant_row_x64z(lutp, wn + i * (n / 2l), we + i * nb, qrow, srow, n)
                        for (tk in range64(ntok)) {
                            myp[tk * d + i] = dot_q8q8_x64z16vnni(qrow, srow, xqp + tk * n, xsp + tk * nb, n)
                        }
                    }
                }
            }
        }
    }
}

def private mx4q8_batch_groupn_kernel_x64_z16vnni(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let items = nregions * d
    let nchunks = matmul_chunks(int(items), get_dispatch_lanes())
    mx4b_reserve(int64(nchunks) * n, int64(nchunks) * nb)
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        var qsp = addr(g_mx4b_wq[0])
        var ssp = addr(g_mx4b_ws[0])
        maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, nchunks, nchunks) $(cb, ce) {
            unsafe {
                for (ci0 in range(cb, ce)) {
                    let ci = int64(ci0)
                    var qrow = qsp + ci * n
                    var srow = ssp + ci * nb
                    for (ii in range64(ci * items / int64(nchunks), (ci + 1l) * items / int64(nchunks))) {
                        let r = ii / d
                        let row = ii % d
                        let woff = offs[r * 3l]
                        let row0 = offs[r * 3l + 1l]
                        let cnt = offs[r * 3l + 2l]
                        if (cnt == 0l) {
                            continue
                        }
                        mx4_dequant_row_x64z(lutp, wn + woff / 2l + row * (n / 2l), we + woff / 32l + row * nb, qrow, srow, n)
                        for (tk in range64(cnt)) {
                            myp[(row0 + tk) * d + row] = dot_q8q8_x64z16vnni(qrow, srow, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                        }
                        if (bp != null) {
                            let b = bp[boffs[r] + row]
                            for (tk in range64(cnt)) {
                                myp[(row0 + tk) * d + row] += b
                            }
                        }
                    }
                }
            }
        }
    }
}

[init]
def dasllama_math_x64_avx_register() {
    g_avx_matrix_enabled = get_env_variable("DASLLAMA_AVX_MATRIX") == "1"
    g_avx_matrix_force = get_env_variable("DASLLAMA_AVX_MATRIX_FORCE") == "1"
    // Only register under JIT on x86-64 WITH AVX2. Off-JIT (interpreter or AOT) dot32 runs its SCALAR
    // fallback body — slower than the portable dot_q8q8, which the vectorizer handles — so the
    // portable backend stays selected everywhere the hardware sequence isn't emitted. The
    // cpu_supports("avx2") half mirrors the JIT's own emitter gate (g_target_x64_avx2): on an
    // AVX2-less x64 box the emitter refuses the intrinsics anyway, so these kernels would be the
    // same scalar fallbacks — registering them would replace portable with something slower.
    if (get_architecture_name() == "x86_64" && jit_enabled() && cpu_supports("avx2")) {
        // The mx4/groupn tiers are native across all four backends: dot32_mx4 (ymm PSHUFB dequant)
        // row dots + the groupn dispatch-fuse kernels, bit-identical to the portable forms (exact
        // int block sums, same flush order), + the strip-dequant mx4 batch kernels
        // (mx4_native_batch: grouped MoE prefill skips the Q8 expansion entirely). mx4 planes stay
        // row-major everywhere (repack_mx4 identity); only the repack backend's Q8 groupn reads
        // the grp4 interleave.
        // x64-avx2: dot4x4 on row-major weights — auto-selected default for direct callers
        // (tests, benchmarks). priority 10 out-ranks portable (0).
        register_kernel_backend(KernelBackend(name = "x64-avx2", mm = @@q8q8_kernel_x64_dot4x4,
            batch = @@q8q8_batch_kernel_x64_dot4x4, group3 = @@q8q8_group3_kernel_x64_dot4x4,
            repack = @@repack_q8q8_identity, needs_repack = false, priority = 10,
            mm_mx4 = @@mx4q8_kernel_x64, mx4_batch = @@mx4q8_batch_kernel_x64,
            mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64, mx4_native_batch = true,
            groupn = @@q8q8_groupn_kernel_x64, groupn_mx4 = @@mx4q8_groupn_kernel_x64))
        // x64-avx2-ps: dot32_ps fused float epilogue on the same row-major weights. MEASURED SLOWER
        // than the int-flush dot4x4 on Zen2 (27.9 vs 32.0 t/s decode): the scalar epilogue ran on
        // the idle scalar ALU ports in parallel with the ymm pmadd stream, while the vector epilogue
        // (fold+cvt+mul+add) competes for the same FP ports. Kept registered at priority 8 (never
        // auto-selected) as the pinnable A/B baseline for the 8-wide-accumulator follow-up.
        register_kernel_backend(KernelBackend(name = "x64-avx2-ps", mm = @@q8q8_kernel_x64_ps,
            batch = @@q8q8_batch_kernel_x64_ps, group3 = @@q8q8_group3_kernel_x64_ps,
            repack = @@repack_q8q8_identity, needs_repack = false, priority = 8,
            mm_mx4 = @@mx4q8_kernel_x64, mx4_batch = @@mx4q8_batch_kernel_x64,
            mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64, mx4_native_batch = true,
            groupn = @@q8q8_groupn_kernel_x64, groupn_mx4 = @@mx4q8_groupn_kernel_x64))
        // x64-avx2-acc8: dot32_acc8 — llama.cpp's vec_dot per-block shape (no fold, no per-block
        // hsum; VCVTDQ2PS + mul-add — VFMADD under fast-math — into LICM-promoted ymm accumulators,
        // one reduce per row). Priority 9: pinnable A/B experiment; promote above the dot4x4 tier
        // only if it measures faster in-model.
        register_kernel_backend(KernelBackend(name = "x64-avx2-acc8", mm = @@q8q8_kernel_x64_acc8,
            batch = @@q8q8_batch_kernel_x64_acc8, group3 = @@q8q8_group3_kernel_x64_acc8,
            repack = @@repack_q8q8_identity, needs_repack = false, priority = 9,
            mm_mx4 = @@mx4q8_kernel_x64, mx4_batch = @@mx4q8_batch_kernel_x64,
            mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64, mx4_native_batch = true,
            groupn = @@q8q8_groupn_kernel_x64, groupn_mx4 = @@mx4q8_groupn_kernel_x64))
        // x64-avx2-repack: grp4 + block-interleaved repack — the highest priority (20), but
        // needs_repack, so only select_matmul_backend_for_load (at Q8 model load, which then
        // repacks) activates it. The mx4 side stays row-major (repack_mx4 identity default), so
        // its mm_mx4/groupn_mx4 are the row-major natives; the Q8 groupn reads the grp4 interleave.
        register_kernel_backend(KernelBackend(name = "x64-avx2-repack", mm = @@q8q8_kernel_x64_grp4,
            batch = @@q8q8_batch_kernel_x64_grp4, group3 = @@q8q8_group3_kernel_x64_grp4,
            repack = @@repack_q8q8_x64, needs_repack = true, priority = 20,
            mm_mx4 = @@mx4q8_kernel_x64, mx4_batch = @@mx4q8_batch_kernel_x64_grp4,
            mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64_grp4, mx4_native_batch = true,
            groupn = @@q8q8_groupn_kernel_x64_grp4, groupn_mx4 = @@mx4q8_groupn_kernel_x64))
        // ===== AVX kernel matrix (see the section comment) — default OFF, pin-only priorities =====
        // The 3990X has none of these tiers; a slot without a per-tier twin points at the shipped
        // kernel it shares (mirrors x64-avx2-acc8 reusing the row-major mx4 natives), so a pin-A/B
        // against the donor backend isolates exactly the slots that differ.
        if (g_avx_matrix_enabled) {
            let has_vnni256 = matrix_has("avxvnni") || (matrix_has("avx512vnni") && matrix_has("avx512vl"))
            let has_zbw = matrix_has("avx512f") && matrix_has("avx512bw")
            let has_zvnni = has_zbw && matrix_has("avx512vnni")
            if (has_vnni256) {
                // x64-vnni256: dot4x4 family with the VPDPBUSD dot — A/B donor is x64-avx2
                register_kernel_backend(KernelBackend(name = "x64-vnni256", mm = @@q8q8_kernel_x64_vnni,
                    batch = @@q8q8_batch_kernel_x64_vnni, group3 = @@q8q8_group3_kernel_x64_vnni,
                    repack = @@repack_q8q8_identity, needs_repack = false, priority = 7,
                    mm_mx4 = @@mx4q8_kernel_x64_vnni, mx4_batch = @@mx4q8_batch_kernel_x64_vnni,
                    mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64_vnni, mx4_native_batch = true,
                    groupn = @@q8q8_groupn_kernel_x64_vnni, groupn_mx4 = @@mx4q8_groupn_kernel_x64_vnni))
                // x64-vnni256-acc8: acc8 family with the VPDPBUSD dot — A/B donor is x64-avx2-acc8
                register_kernel_backend(KernelBackend(name = "x64-vnni256-acc8", mm = @@q8q8_kernel_x64_acc8vnni,
                    batch = @@q8q8_batch_kernel_x64_acc8vnni, group3 = @@q8q8_group3_kernel_x64_acc8vnni,
                    repack = @@repack_q8q8_identity, needs_repack = false, priority = 6,
                    mm_mx4 = @@mx4q8_kernel_x64_vnni, mx4_batch = @@mx4q8_batch_kernel_x64_vnni,
                    mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64_vnni, mx4_native_batch = true,
                    groupn = @@q8q8_groupn_kernel_x64_vnni, groupn_mx4 = @@mx4q8_groupn_kernel_x64_vnni))
                // x64-vnni256-repack: grp4 family with the VPDPBUSD dot — A/B donor is
                // x64-avx2-repack (same interleave, same repack fn; pin BEFORE load_gguf)
                register_kernel_backend(KernelBackend(name = "x64-vnni256-repack", mm = @@q8q8_kernel_x64_grp4vnni,
                    batch = @@q8q8_batch_kernel_x64_grp4vnni, group3 = @@q8q8_group3_kernel_x64_grp4vnni,
                    repack = @@repack_q8q8_x64, needs_repack = true, priority = 5,
                    mm_mx4 = @@mx4q8_kernel_x64_vnni, mx4_batch = @@mx4q8_batch_kernel_x64_grp4vnni,
                    mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64_grp4vnni, mx4_native_batch = true,
                    groupn = @@q8q8_groupn_kernel_x64_grp4vnni, groupn_mx4 = @@mx4q8_groupn_kernel_x64_vnni))
            }
            if (has_zbw) {
                // x64-avx512bw: z16 family, VPMADDUBSW+VPMADDWD zmm chain — mx4 slots shared with
                // x64-avx2 (no zmm mx4 twin; the mx4 delta is the vnni/z16vnni backends' to show)
                register_kernel_backend(KernelBackend(name = "x64-avx512bw", mm = @@q8q8_kernel_x64_z16,
                    batch = @@q8q8_batch_kernel_x64_z16, group3 = @@q8q8_group3_kernel_x64_z16,
                    repack = @@repack_q8q8_identity, needs_repack = false, priority = 4,
                    mm_mx4 = @@mx4q8_kernel_x64, mx4_batch = @@mx4q8_batch_kernel_x64,
                    mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64, mx4_native_batch = true,
                    groupn = @@q8q8_groupn_kernel_x64_z16, groupn_mx4 = @@mx4q8_groupn_kernel_x64))
            }
            if (has_zvnni) {
                // x64-avx512vnni: z16 family with the zmm VPDPBUSD dot + mx4 strips through
                // mx4_dequant64 — A/B donors are x64-avx512bw (dot step) and x64-vnni256 (mx4)
                register_kernel_backend(KernelBackend(name = "x64-avx512vnni", mm = @@q8q8_kernel_x64_z16vnni,
                    batch = @@q8q8_batch_kernel_x64_z16vnni, group3 = @@q8q8_group3_kernel_x64_z16vnni,
                    repack = @@repack_q8q8_identity, needs_repack = false, priority = 3,
                    mm_mx4 = @@mx4q8_kernel_x64_vnni, mx4_batch = @@mx4q8_batch_kernel_x64_z16vnni,
                    mx4_batch_groupn = @@mx4q8_batch_groupn_kernel_x64_z16vnni, mx4_native_batch = true,
                    groupn = @@q8q8_groupn_kernel_x64_z16vnni, groupn_mx4 = @@mx4q8_groupn_kernel_x64_vnni))
            }
        }
    }
}
