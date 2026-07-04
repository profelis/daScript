options gen2

module dasllama_math_gen shared public

require dasllama/dasllama_math
require dasllama/dasllama_math_aarch64_neon
require llvm/daslib/llvm_tune  // [tune]/[tune_perm] + the [llvm_code] annotation it re-exports
require daslib/jobque_boost public
require dasllama/dasllama_par
require math

// The GEMM tile as a [tune] client (gemm_generator_plan.md part 3; promoted from the M2 GO/NO-GO
// experiment): the perm grid below stamps dasllama_gemm_gen::q8q8_tile perms through [llvm_code].
// Normal runs stamp exactly one winner (manifest > fallback kstep2 = the M2 perm) onto
// q8q8_tile_gen; DAS_TUNE_MODE=tune/test stamps the grid + the q8q8_tile_gen_variants()
// registry for the harness (gen_parity_probe / gen_tune_probe). This module also registers
// "arm64-laneq-gen" — the arm64-laneq backend with ONLY the batch tile swapped for the stub —
// so gemm_1core_probe A/Bs hand vs generated on identical traversal, repack and dispatch.
// The generator lives in dasllama/dasllama_gemm_gen.das (llvm-jit context, wired via
// llvm/daslib/llvm_user_modules.das). NOT in the production require chain: only probes/tests
// require this module.

//! The generated tile: 4 interleaved rows x 4 tokens (the q8q8_repack_type(4) layout — see
//! dasllama_gemm_schema). The reference body — 4 single-token laneq4 dots with the same
//! per-block fold order as the tile — runs on interp, AOT, non-arm64 JIT, and whenever the
//! generator declines; the last three grid rows decline by design (vreg budget, layout
//! contract, no per-ISA dot emitter) and pin that rail in test mode. Not `private`: called
//! from inside the lifted parallel_for worker lambda below.
[tune_perm(kstep = 1), tune_perm(kstep = 2), tune_perm(kstep = 4), tune_perm(kstep = 2, nrsplit = 2),
 tune_perm(suffix = "mr8_budget", mr = 8), tune_perm(suffix = "mr2_layout", mr = 2), tune_perm(dot = "vpdpbusd"),
 tune(gen = "dasllama_gemm_gen::q8q8_tile", fallback = "kstep2"),
 hint(unsafe_range_check, noalias = wg, noalias = sg, noalias = xqp, noalias = xsp)]
def q8q8_tile_gen(var yp : float?; wg : int8 const?; sg : float const?; xqp : int8 const?; xsp : float const?; n, d, g, t0 : int64) : void {
    let nb = n / 32l
    unsafe {
        for (t in range64(4l)) {
            let f = dot_q8q8_laneq4(wg, sg, xqp + (t0 + t) * n, xsp + (t0 + t) * nb, n)
            let r = g * 4l
            yp[(t0 + t) * d + r + 0l] = f.x
            yp[(t0 + t) * d + r + 1l] = f.y
            yp[(t0 + t) * d + r + 2l] = f.z
            yp[(t0 + t) * d + r + 3l] = f.w
        }
    }
}

// q8q8_batch_kernel_neon_laneq with the hand tile swapped for the generated one — traversal,
// token-blocking, chunking and tails identical (see the original for the design notes)
def private q8q8_batch_kernel_neon_laneq_gen(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let ng = d / 4l
    var myp = yp
    let TB = effective_token_block(g_q8_token_block, n)
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(ng), matmul_chunks(int(ng) * 4, get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        unsafe {
            var tb = 0l
            while (tb < ntok) {
                let tbe = min(tb + TB, ntok)
                let tb4 = tb + ((tbe - tb) / 4l) * 4l
                for (gi in range(rb, re)) {
                    let g = int64(gi)
                    let wgp = wp + g * 4l * n
                    let sgp = sp + g * 4l * nb
                    var tk = tb
                    while (tk < tb4) {
                        q8q8_tile_gen(myp, wgp, sgp, xqp, xsp, n, d, g, tk)
                        tk += 4l
                    }
                    while (tk < tbe) {
                        let f = dot_q8q8_laneq4(wgp, sgp, xqp + tk * n, xsp + tk * nb, n)
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
        for (i in range64(ng * 4l, d)) {
            let wrow = wp + i * n
            let srow = sp + i * nb
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_sdot4x4(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
}

[init]
def dasllama_math_gen_register() {
    // same gate as the laneq backend it borrows its slots from; the probe selects it by name
    // (needs_repack keeps it out of auto-select, priority < laneq keeps it out of load-select)
    if (get_architecture_name() == "arm64" && jit_enabled()) {
        register_kernel_backend(KernelBackend(name = "arm64-laneq-gen", mm = @@q8q8_kernel_neon_laneq,
            batch = @@q8q8_batch_kernel_neon_laneq_gen, group3 = @@q8q8_group3_kernel_neon_laneq,
            repack = @@repack_q8q8_neon,
            needs_repack = true, priority = 15))
    }
}
