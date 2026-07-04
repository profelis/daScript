options gen2

module dasllama_math_gen shared public

require dasllama/dasllama_math
require dasllama/dasllama_math_aarch64_neon
require llvm/daslib/llvm_tune  // [tune]/[tune_perm]/[tune_companion] + the [llvm_code] annotation it re-exports
require dasllama/dasllama_gemm_schema
require daslib/jobque_boost public
require dasllama/dasllama_par
require math

// The GEMM tile as a [tune] client (gemm_generator_plan.md part 3; promoted from the M2 GO/NO-GO
// experiment): the perm grid below stamps dasllama_gemm_gen::q8q8_tile perms through [llvm_code],
// and the [tune_companion] row stamps q8q8_layout_gen from the same entry — the two-function
// stamp: the runtime repack asks the layout companion which interleave the stamped tile reads,
// and both generators share one decline predicate, so kernel and repack cannot desync on any
// tier. Normal runs stamp exactly one winner (manifest > fallback kstep2 = the M2 perm);
// DAS_TUNE_MODE=tune/test stamps the grid + the *_variants() registries for the harness
// (gen_parity_probe / gen_tune_probe). This module also registers "arm64-laneq-gen" — the
// arm64-laneq backend with the batch tile swapped for the stub (and, off the grp4 layout, the
// generic grp<mr> mm/group3/tail forms). Since slice C this IS the arm64 load-select tier
// (priority 25 over laneq's 20): dasllama_common pulls it in behind a path guard
// (`require ?llvm/daslib/llvm_tune`), so any Q8 model load on arm64+jit runs the generated
// batch tile. The generator lives in dasllama/dasllama_gemm_gen.das (llvm-jit context, wired
// via llvm/daslib/llvm_user_modules.das).

//! The layout companion (the two-function stamp): the repack interleave (mr) the stamped tile
//! reads. Reference body = the reference tile's grp4; the generator emits the perm's mr and
//! declines in lockstep with the tile generator (shared perm_declines), so a perm the tile
//! can't emit keeps the grp4 reference pair on both sides — on every tier, JIT-time declines
//! included.
def q8q8_layout_gen() : int {
    return q8q8_repack_type(GEMM_REFERENCE_MR).interleave
}

//! The generated tile: mr interleaved rows x 4 tokens (the q8q8_repack_type(mr) layout — see
//! dasllama_gemm_schema; the stamped mr is what q8q8_layout_gen reports). The reference body —
//! 4 single-token laneq4 dots with the same per-block fold order as the tile — runs on interp,
//! AOT, non-arm64 JIT, and whenever the generator declines; the last three grid rows decline
//! by design (q-reg budget, sdot lane structure, no per-ISA dot emitter) and pin that rail in
//! test mode. Not `private`: called from inside the lifted parallel_for worker lambda below.
[tune_perm(kstep = 1), tune_perm(kstep = 2), tune_perm(kstep = 4), tune_perm(kstep = 2, nrsplit = 2),
 tune_perm(kstep = 1, nrsplit = 2), tune_perm(kstep = 4, nrsplit = 2),
 tune_perm(kstep = 1, nrsplit = 2, mr = 8), tune_perm(kstep = 2, nrsplit = 2, mr = 8), tune_perm(kstep = 4, nrsplit = 2, mr = 8),
 tune_perm(suffix = "mr8_budget", mr = 8), tune_perm(suffix = "mr2_lanes", mr = 2), tune_perm(dot = "vpdpbusd"),
 tune_companion(fn = "q8q8_layout_gen", gen = "dasllama_gemm_gen::q8q8_layout"),
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

//! mr-generalized Q8 interleave repack — the q8q8_repack_type(mr) layout for any mr
//! (repack_q8q8_neon is the mr=4 instance: same loops, byte-identical output there). mr-row
//! groups, dword-group interleave (4 k-bytes per row per group), f32 scales interleaved per
//! block; tail rows (d % mr) stay row-major. Runs once per weight tensor at load, on the main
//! context. Public: the probes repack per-variant copies with an explicit mr.
def repack_q8q8_grp(var wp : int8?; var sp : float?; n, d, mr : int64) {
    let nb = n / 32l
    let ng = d / mr
    let ncg = n / 4l
    var tw : array<int8>
    var ts : array<float>
    tw |> resize(int(d * n))
    ts |> resize(int(d * nb))
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
            let gbase = g * mr * n
            for (kg in range64(ncg)) {
                let dst = gbase + kg * 4l * mr
                for (r in range64(mr)) {
                    let src = (g * mr + r) * n + kg * 4l
                    wp[dst + r * 4l + 0l] = twp[src + 0l]
                    wp[dst + r * 4l + 1l] = twp[src + 1l]
                    wp[dst + r * 4l + 2l] = twp[src + 2l]
                    wp[dst + r * 4l + 3l] = twp[src + 3l]
                }
            }
            let sgbase = g * mr * nb
            for (bi in range64(nb)) {
                for (r in range64(mr)) {
                    sp[sgbase + bi * mr + r] = tsp[(g * mr + r) * nb + bi]
                }
            }
        }
    }
    delete tw
    delete ts
}

// the backend repack slot: the layout companion decides the interleave, so a stamped mr=8
// tile gets grp8 weights from the same load path that gave the grp4 pair its grp4 weights
def private repack_q8q8_gen(var wp : int8?; var sp : float?; n, d : int64) {
    repack_q8q8_grp(wp, sp, n, d, int64(q8q8_layout_gen()))
}

//! Generic grp<mr> single-token dot for the mr != 4 slots and tails: scalar, correct
//! anywhere, same per-block fold order as the tile (acc int-exact, then f += float(acc) * s *
//! q per block in bi order). Writes the group's mr outputs for token trow at column col.
//! Public: the parity probe uses it as the grp<mr> reference when the stamped mr isn't 4.
def q8q8_token_grp_generic(var yp : float?; wg : int8 const?; sg : float const?; xq : int8 const?; xs : float const?; n, d, col, trow, mr : int64) {
    let nb = n / 32l
    var f : float[8]
    for (r in range(int(mr))) {
        f[r] = 0.0
    }
    unsafe {
        for (bi in range64(nb)) {
            let wb = bi * mr * 32l
            let xb = bi * 32l
            let xsb = xs[bi]
            for (r in range64(mr)) {
                var acc = 0
                for (kg in range64(8l)) {
                    let wo = wb + kg * 4l * mr + r * 4l
                    let xo = xb + kg * 4l
                    acc += int(wg[wo + 0l]) * int(xq[xo + 0l])
                    acc += int(wg[wo + 1l]) * int(xq[xo + 1l])
                    acc += int(wg[wo + 2l]) * int(xq[xo + 2l])
                    acc += int(wg[wo + 3l]) * int(xq[xo + 3l])
                }
                f[int(r)] += float(acc) * sg[bi * mr + r] * xsb
            }
        }
        for (r in range64(mr)) {
            yp[trow * d + col + r] = f[int(r)]
        }
    }
}

// q8q8_batch_kernel_neon_laneq with the hand tile swapped for the generated one — traversal,
// token-blocking, chunking and tails identical (see the original for the design notes), except
// strides come off the layout companion: at mr=4 this is the original byte-for-byte, any other
// stamped mr walks grp<mr> groups and runs its token tail through the generic dot
def private q8q8_batch_kernel_neon_laneq_gen(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d, ntok : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    let TB = effective_token_block(g_q8_token_block, n)
    maybe_parallel_for(n * d * ntok >= g_matmul_par_threshold, 0, int(ng), matmul_chunks(int(ng * mr), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        unsafe {
            var tb = 0l
            while (tb < ntok) {
                let tbe = min(tb + TB, ntok)
                let tb4 = tb + ((tbe - tb) / 4l) * 4l
                for (gi in range(rb, re)) {
                    let g = int64(gi)
                    let wgp = wp + g * mr * n
                    let sgp = sp + g * mr * nb
                    var tk = tb
                    while (tk < tb4) {
                        q8q8_tile_gen(myp, wgp, sgp, xqp, xsp, n, d, g, tk)
                        tk += 4l
                    }
                    if (mr == 4l) {
                        while (tk < tbe) {
                            let f = dot_q8q8_laneq4(wgp, sgp, xqp + tk * n, xsp + tk * nb, n)
                            myp[tk * d + g * 4l + 0l] = f.x
                            myp[tk * d + g * 4l + 1l] = f.y
                            myp[tk * d + g * 4l + 2l] = f.z
                            myp[tk * d + g * 4l + 3l] = f.w
                            tk++
                        }
                    } else {
                        while (tk < tbe) {
                            q8q8_token_grp_generic(myp, wgp, sgp, xqp + tk * n, xsp + tk * nb, n, d, g * mr, tk, mr)
                            tk++
                        }
                    }
                }
                tb += TB
            }
        }
    }
    unsafe {
        for (i in range64(ng * mr, d)) {
            let wrow = wp + i * n
            let srow = sp + i * nb
            for (tk in range64(ntok)) {
                myp[tk * d + i] = dot_q8q8_sdot4x4(wrow, srow, xqp + tk * n, xsp + tk * nb, n)
            }
        }
    }
}

// grp<mr> GEMV for mr != 4 (the hand laneq mm reads grp4 only): generic dot per group, same
// dispatch shape as q8q8_kernel_neon_laneq. Correct-anywhere, not fast — the GEMV regime gets
// its own perm sub-family later; batch is what the mr axis is swept for.
def private q8q8_kernel_grp_generic(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(ng), matmul_chunks_gemv(int(ng * mr), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        unsafe {
            for (gi in range(rb, re)) {
                let g = int64(gi)
                q8q8_token_grp_generic(myp, wp + g * mr * n, sp + g * mr * nb, xqp, xsp, n, d, g * mr, 0l, mr)
            }
        }
    }
    unsafe {
        for (i in range64(ng * mr, d)) {
            myp[i] = dot_q8q8_sdot4x4(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

// grp<mr> group3 for mr != 4: three generic GEMVs — same per-row dots as a fused walk, one
// dispatch each (probe-only backend; fusion stays a hand-tier property until the scoreboard
// says otherwise)
def private q8q8_group3_grp_generic(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                                    woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    unsafe {
        q8q8_kernel_grp_generic(y0p, wp + woff0, sp + woff0 / 32l, xqp, xsp, n, d0)
        q8q8_kernel_grp_generic(y1p, wp + woff1, sp + woff1 / 32l, xqp, xsp, n, d1)
        q8q8_kernel_grp_generic(y2p, wp + woff2, sp + woff2 / 32l, xqp, xsp, n, d2)
    }
}

// grp<mr> region-list GEMV for mr != 4: per-region generic GEMV + a bias post-add — one
// dispatch per region instead of laneq's fused walk (correct-anywhere stopgap; the GEMV perm
// sub-family is where mr != 4 decode perf comes from)
def private q8q8_groupn_grp_generic(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    var myp = yp
    unsafe {
        for (r in range64(nregions)) {
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            q8q8_kernel_grp_generic(myp + r * d, wp + woff, sp + woff / 32l, xqp + xoff, xsp + xoff / 32l, n, d)
            if (bp != null) {
                for (i in range64(d)) {
                    myp[r * d + i] += bp[boffs[r] + i]
                }
            }
        }
    }
}

[init]
def dasllama_math_gen_register() {
    // Same gate as the laneq backend whose slots it borrows. needs_repack keeps it out of
    // auto-select (direct callers stay on arm64-sdot); priority 25 makes
    // select_matmul_backend_for_load pick it OVER arm64-laneq (20) — since slice C the generated
    // tile is the arm64 load-select batch tier. The layout companion decides which slots are
    // layout-coherent: on the grp4 fallback/winner the hand laneq mm/group3/rows/mx4 read the
    // same bytes; any other stamped mr gets the generic grp<mr> Q8 forms, a row-major mx4 family
    // (interleaved planes + a grp<mr> Q8 scratch can't share the laneq expand map), and the
    // per-op decode path (rows core stays the unset default).
    if (get_architecture_name() == "arm64" && jit_enabled()) {
        var be = KernelBackend(name = "arm64-laneq-gen", mm = @@q8q8_kernel_neon_laneq,
            batch = @@q8q8_batch_kernel_neon_laneq_gen, group3 = @@q8q8_group3_kernel_neon_laneq,
            repack = @@repack_q8q8_gen,
            mm_mx4 = @@mx4q8_kernel_neon, repack_mx4 = @@repack_mx4_identity,
            groupn = @@q8q8_groupn_grp_generic, groupn_mx4 = @@mx4q8_groupn_kernel_neon,
            needs_repack = true, priority = 25)
        if (q8q8_layout_gen() == 4) {
            be.mm_mx4 = @@mx4q8_kernel_neon_laneq
            be.repack_mx4 = @@repack_mx4_neon
            be.groupn = @@q8q8_groupn_kernel_neon_laneq
            be.groupn_mx4 = @@mx4q8_groupn_kernel_neon_laneq
            be.mm_rows = @@q8q8_rows_kernel_neon_laneq
            be.mx4_expand_interleaved = true
        } else {
            be.mm = @@q8q8_kernel_grp_generic
            be.group3 = @@q8q8_group3_grp_generic
        }
        register_kernel_backend(be)
    }
}
