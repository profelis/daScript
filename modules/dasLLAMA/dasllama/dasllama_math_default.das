options gen2

module dasllama_math_default shared public

require dasllama/dasllama_math       // KernelBackend + register_kernel_backend + the matmul_chunks shapers + repack_q8q8_identity
require dasllama/dasllama_tune       // [tuned]: reconstitute dot_q8q8 from its template with per-box loop hints
require llvm/daslib/f16_cvt          // dot_q8q8_f16s widens the binary16 weight scale in-loop
require daslib/jobque_boost public   // parallel_for / notify_and_release (the kernels expand parallel_for)
require dasllama/dasllama_par        // maybe_parallel_for
require math

// The PORTABLE Q8·Q8 kernel backend — auto-vectorized dot_q8q8, no repack (row-major weights). It is
// the default/fallback backend on every host, registered at [init] with the lowest priority; a platform
// module (dasllama_math_aarch64_neon, dasllama_math_gen) registers a higher-priority backend that
// wins the auto-select where its ISA kernels are available. dasllama_math owns the registry + the public
// matmul wrappers; this module supplies the portable kernels and registers them.

[hint(unsafe_range_check, noalias = wq, noalias = xq, noalias = ws, noalias = xs)]
def template dot_q8q8_template(wq : int8 const ?; ws : float const ?; xq : int8 const ?; xs : float const ?; n : int64) : float {
    var acc = 0.0
    let nb = n / 32l
    for (bi in range64(nb)) {
        let base = bi * 32l
        var iacc = 0
        for [tune = 1] (k in range64(32l)) {
            iacc += int(unsafe(wq[base + k])) * int(unsafe(xq[base + k]))
        }
        acc += float(iacc) * unsafe(ws[bi]) * unsafe(xs[bi])
    }
    return acc
}

//! Q8·Q8 dot: BOTH the weight (wq/ws) and the activation (xq/xs) are Q8 — int8 quants + one fp32
//! scale per 32-block. The inner block loop is a pure int8·int8 multiply-accumulate, which the LLVM
//! JIT lowers to ARM SDOT (vdotq_s32: 16 int8 MACs/instr, exact int32 accumulate) under the
//! fallback vec16. The two block scales multiply in once per 32-wide block. ~3.8x the
//! dequant-in-dot dot_q8 on the kernel bench. n must be a multiple of 32.
[hint(unsafe_range_check, noalias = wq, noalias = xq, noalias = ws, noalias = xs), tuned(fallback = "vec16")]
def dot_q8q8(wq : int8 const?; ws : float const?; xq : int8 const?; xs : float const?; n : int64) : float {}

[hint(unsafe_range_check, noalias = wq, noalias = xq, noalias = ws, noalias = xs)]
def template dot_q8q8_f16s_template(wq : int8 const ?; ws : uint16 const ?; xq : int8 const ?; xs : float const ?; n : int64) : float {
    var acc = 0.0
    let nb = n / 32l
    for (bi in range64(nb)) {
        let base = bi * 32l
        var iacc = 0
        for [tune = 1] (k in range64(32l)) {
            iacc += int(unsafe(wq[base + k])) * int(unsafe(xq[base + k]))
        }
        acc += float(iacc) * f16_to_f32(uint(unsafe(ws[bi]))) * unsafe(xs[bi])
    }
    return acc
}

//! The wscale_f16 twin of dot_q8q8: the per-block WEIGHT scale is a raw binary16 halfword,
//! widened in-loop (vcvtph2ps/fcvtl under the JIT — the f16-KV codec lesson). Bit-identical to
//! dot_q8q8 over the f32 plane those halfwords widen to. n must be a multiple of 32.
[hint(unsafe_range_check, noalias = wq, noalias = xq, noalias = ws, noalias = xs), tuned(fallback = "vec16")]
def dot_q8q8_f16s(wq : int8 const?; ws : uint16 const?; xq : int8 const?; xs : float const?; n : int64) : float {}

// ----- parallel_for dispatch profiler (off by default) -----
// When on, the batch kernel records each worker's start time (relative to the parallel_for start) into
// g_pf_ws[rb], then aggregates the first/last worker start and the wall time per call. A large gap
// between pf-start and last-worker-start = workers trickling in (the job pool waking from sleep), which
// is the suspected prefill stall. The recorder lives with the portable batch kernel so the A/B harness
// can pin the portable backend and measure the same parallel_for behavior in one module.
var g_pf_prof = false
var g_pf_ws : array<int64>   // per-call worker start (ns, relative to pf-start), indexed by chunk start row
var g_pf_first_sum = 0l      // Σ first-worker start (us) over calls
var g_pf_last_sum = 0l       // Σ last-worker start (us) over calls
var g_pf_wall_sum = 0l       // Σ parallel_for wall (us) over calls
var g_pf_n = 0l

//! Enable/disable the parallel_for dispatch profiler. max_rows must be >= the largest matmul output d.
def pf_prof_enable(on : bool; max_rows : int64) {
    g_pf_prof = on
    g_pf_ws |> resize(max_rows)
    g_pf_first_sum = 0l
    g_pf_last_sum = 0l
    g_pf_wall_sum = 0l
    g_pf_n = 0l
}

def pf_prof_report() {
    if (g_pf_n == 0l) {
        return
    }
    to_log(LOG_INFO, "=== parallel_for dispatch ({g_pf_n} batch-matmul calls) ===\n")
    to_log(LOG_INFO, "  avg first-worker start = {g_pf_first_sum / g_pf_n} us\n")
    to_log(LOG_INFO, "  avg last-worker start  = {g_pf_last_sum / g_pf_n} us  (time to full parallelism)\n")
    to_log(LOG_INFO, "  avg parallel_for wall  = {g_pf_wall_sum / g_pf_n} us\n")
    to_log(LOG_INFO, "  last-start as % of wall = {100l * g_pf_last_sum / max(g_pf_wall_sum, 1l)}% (high = workers trickle in / pool wake-up stall)\n")
}

// Portable kernels (auto-vectorized dot_q8q8). 1N threading (one chunk per hw job) measured fastest
// for this compute-light kernel (~52 vs ~51 tok/s at 2N end-to-end).
def private q8q8_kernel(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(0, int(d), matmul_chunks_gemv(int(d), 1, n * d)) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    if (g_pf_prof) {
        // instrumented path: raw parallel_for + per-worker start capture (see pf_prof_report)
        unsafe {
            var wsp0 = reinterpret<int64?>(addr(g_pf_ws[0]))
            for (k in range(int(d))) {
                wsp0[k] = 0l
            }
        }
        let pf0 = ref_time_ticks()
        unsafe {
            let wsbase = addr(g_pf_ws[0])
            parallel_for(0, int(d), matmul_chunks(int(d), 1, n * d * ntok)) $(rb, re, wg) {
                unsafe {
                    var wsw = reinterpret<int64?>(wsbase)
                    wsw[rb] = ref_time_ticks() - pf0
                    for (i in range(rb, re)) {
                        let wrow = wp + int64(i) * n
                        let srow = sp + int64(i) * nb
                        for (tk in range64(ntok)) {
                            myp[tk * d + int64(i)] = dot_q8q8(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                        }
                    }
                }
                wg |> notify_and_release
            }
        }
        let wall = (ref_time_ticks() - pf0) / 1000l
        var fs = 1l << 62l
        var ls = 0l
        for (k in range(int(d))) {
            let v = g_pf_ws[k]
            if (v != 0l) {
                fs = min(fs, v)
                ls = max(ls, v)
            }
        }
        g_pf_first_sum += fs / 1000l
        g_pf_last_sum += ls / 1000l
        g_pf_wall_sum += wall
        g_pf_n ++
        return
    }
    maybe_parallel_for(0, int(d), matmul_chunks(int(d), 1, n * d * ntok)) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

// Row-range core (mm_rows slot): rows [rb,re) of one region, no dispatch — the fused decode
// chains thread it from their own stage lambdas. Same dot_q8q8 rows as q8q8_kernel. Not `private`:
// invoked through the kernel pointer from lifted worker lambdas.
def q8q8_rows_kernel(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, rb, re : int64) {
    let nb = n / 32l
    unsafe {
        for (i in range64(rb, re)) {
            yp[i] = dot_q8q8(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

def private q8q8_group3_kernel(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                               woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    maybe_parallel_for(0, int(dtot), matmul_chunks_gemv(int(dtot), 1, n * dtot)) $(rb, re) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
    }
}

// ===== f16-scale twins (the wscale_f16 rail): the same portable loops over the binary16
// weight-scale plane, one dot swap — bit-identical to the f32 forms over the widened plane =====

def private q8q8_kernel_s16(var yp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(0, int(d), matmul_chunks_gemv(int(d), 1, n * d)) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                myp[i] = dot_q8q8_f16s(wp + int64(i) * n, sp + int64(i) * nb, xqp, xsp, n)
            }
        }
    }
}

def private q8q8_batch_kernel_s16(var yp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(0, int(d), matmul_chunks(int(d), 1, n * d * ntok)) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let wrow = wp + int64(i) * n
                let srow = sp + int64(i) * nb
                for (tk in range64(ntok)) {
                    myp[tk * d + int64(i)] = dot_q8q8_f16s(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
                }
            }
        }
    }
}

// Not `private`: invoked through the kernel pointer from lifted worker lambdas.
def q8q8_rows_kernel_s16(var yp : float?; wp : int8 const?; sp : uint16 const?; xqp : int8 const?; xsp : float const?; n, rb, re : int64) {
    let nb = n / 32l
    unsafe {
        for (i in range64(rb, re)) {
            yp[i] = dot_q8q8_f16s(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

def private q8q8_group3_kernel_s16(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : uint16 const?;
                                   woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let dtot = d0 + d1 + d2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    maybe_parallel_for(0, int(dtot), matmul_chunks_gemv(int(dtot), 1, n * dtot)) $(rb, re) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                if (g < d0) {
                    w0[g] = dot_q8q8_f16s(wp + woff0 + g * n, sp + woff0 / 32l + g * nb, xqp, xsp, n)
                } elif (g < d0 + d1) {
                    let r = g - d0
                    w1[r] = dot_q8q8_f16s(wp + woff1 + r * n, sp + woff1 / 32l + r * nb, xqp, xsp, n)
                } else {
                    let r = g - d0 - d1
                    w2[r] = dot_q8q8_f16s(wp + woff2 + r * n, sp + woff2 / 32l + r * nb, xqp, xsp, n)
                }
            }
        }
    }
}

def q8q8_groupn_kernel_s16(var yp : float?; wp : int8 const?; sp : uint16 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(0, int(nregions * d), matmul_chunks_gemv(int(nregions * d), 1, n * d * nregions)) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let ii = int64(i)
                let r = ii / d
                let row = ii % d
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var v = dot_q8q8_f16s(wp + woff + row * n, sp + woff / 32l + row * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + row]
                }
                myp[ii] = v
            }
        }
    }
}

//! MXFP4·Q8 dot, scalar reference form (mirrors ggml_vec_dot_mxfp4_q8_0's tail loop): per 32-block,
//! each of the 16 nibble bytes pairs its low nibble with xq[j] and its high nibble with xq[j+16]
//! through the doubled-e2m1 `lut`, the exact int32 block sum flushing through e8m0_half(we) × xs.
//! The per-block flush order matches the NEON dot_mx4q8, so the two agree to reassociation. Not
//! `private`: the reference for the mx4 unit tests and callable from lifted worker lambdas.
[hint(unsafe_range_check, noalias = lut, noalias = wn, noalias = we, noalias = xq, noalias = xs)]
def dot_mx4q8_scalar(lut : int8 const?; wn : uint8 const?; we : uint8 const?; xq : int8 const?; xs : float const?; n : int64) : float {
    let nb = n / 32l
    var f = 0.0
    unsafe {
        for (bi in range64(nb)) {
            let wb = bi * 16l
            let xb = bi * 32l
            var s = 0
            for (j in range64(16l)) {
                let b = int(wn[wb + j])
                s += int(lut[b & 15]) * int(xq[xb + j])
                s += int(lut[b >> 4]) * int(xq[xb + j + 16l])
            }
            f += float(s) * e8m0_half(uint(we[bi])) * xs[bi]
        }
    }
    return f
}

// mx4q8_kernel / q8q8_groupn_kernel / mx4q8_groupn_kernel are NOT private: backends without a
// native mx4/groupn tier yet (the x64 family) register these portable forms to satisfy the
// every-backend-supplies-one contract (see KernelBackend in dasllama_math).
def mx4q8_kernel(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(0, int(d), matmul_chunks_gemv(int(d), 1, n * d)) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    myp[i] = dot_mx4q8_scalar(lutp, wn + int64(i) * (n / 2l), we + int64(i) * nb, xqp, xsp, n)
                }
            }
        }
    }
}

// Portable mx4 batch: rows-outer / tokens-inner over the scalar row dot. NOT flagged
// mx4_native_batch — in-model grouped prefill keeps the expand-to-Q8 + vectorized Q8 batch path,
// which beats per-token scalar LUT dots; this form exists as the probe/A-B reference (bit-identical
// to ntok x mx4q8_kernel).
def mx4q8_batch_kernel(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(0, int(d), matmul_chunks(int(d), 1, n * d * ntok)) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    let wrow = wn + int64(i) * (n / 2l)
                    let erow = we + int64(i) * nb
                    for (tk in range64(ntok)) {
                        myp[tk * d + int64(i)] = dot_mx4q8_scalar(lutp, wrow, erow, xqp + tk * n, xsp + tk * nb, n)
                    }
                }
            }
        }
    }
}

// Portable mx4 batch groupN: per (region, row) scalar dots over each region's token-row range —
// the probe/A-B reference twin of mx4q8_batch_kernel (NOT flagged; see that kernel's note).
def mx4q8_batch_groupn_kernel(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(0, int(nregions * d), matmul_chunks(int(nregions * d), 1, n * d * nregions)) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    let ii = int64(i)
                    let r = ii / d
                    let row = ii % d
                    let woff = offs[r * 3l]
                    let row0 = offs[r * 3l + 1l]
                    let cnt = offs[r * 3l + 2l]
                    let wrow = wn + woff / 2l + row * (n / 2l)
                    let erow = we + woff / 32l + row * nb
                    for (tk in range64(cnt)) {
                        var v = dot_mx4q8_scalar(lutp, wrow, erow, xqp + (row0 + tk) * n, xsp + (row0 + tk) * nb, n)
                        if (bp != null) {
                            v += bp[boffs[r] + row]
                        }
                        myp[(row0 + tk) * d + row] = v
                    }
                }
            }
        }
    }
}

def q8q8_groupn_kernel(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    maybe_parallel_for(0, int(nregions * d), matmul_chunks_gemv(int(nregions * d), 1, n * d * nregions)) $(rb, re) {
        unsafe {
            for (i in range(rb, re)) {
                let ii = int64(i)
                let r = ii / d
                let row = ii % d
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                var v = dot_q8q8(wp + woff + row * n, sp + woff / 32l + row * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + row]
                }
                myp[ii] = v
            }
        }
    }
}

def mx4q8_groupn_kernel(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(0, int(nregions * d), matmul_chunks_gemv(int(nregions * d), 1, n * d * nregions)) $(rb, re) {
            unsafe {
                for (i in range(rb, re)) {
                    let ii = int64(i)
                    let r = ii / d
                    let row = ii % d
                    let woff = offs[r * 2l]
                    let xoff = offs[r * 2l + 1l]
                    var v = dot_mx4q8_scalar(lutp, wn + woff / 2l + row * (n / 2l), we + woff / 32l + row * nb,
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

//! Register the portable Q8·Q8 backend (row-major, no repack). Lowest priority — a platform ISA backend
//! out-ranks it in the auto-select where available; it stays the fallback everywhere else.
[init]
def dasllama_math_default_register() {
    register_kernel_backend(KernelBackend(name = "portable", mm = @@q8q8_kernel, batch = @@q8q8_batch_kernel,
        group3 = @@q8q8_group3_kernel, repack = @@repack_q8q8_identity, mm_mx4 = @@mx4q8_kernel,
        mx4_batch = @@mx4q8_batch_kernel, mx4_batch_groupn = @@mx4q8_batch_groupn_kernel,
        groupn = @@q8q8_groupn_kernel, groupn_mx4 = @@mx4q8_groupn_kernel,
        mm_rows = @@q8q8_rows_kernel,
        mm_s16 = @@q8q8_kernel_s16, batch_s16 = @@q8q8_batch_kernel_s16,
        group3_s16 = @@q8q8_group3_kernel_s16, groupn_s16 = @@q8q8_groupn_kernel_s16,
        mm_rows_s16 = @@q8q8_rows_kernel_s16,
        needs_repack = false, priority = 0))
}
