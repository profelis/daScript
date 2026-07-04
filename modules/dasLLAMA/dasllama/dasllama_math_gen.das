options gen2

module dasllama_math_gen shared public

require dasllama/dasllama_math
require dasllama/dasllama_math_aarch64_neon
require llvm/daslib/llvm_tune  // [tune]/[tune_perm]/[tune_companion] + the [llvm_code] annotation it re-exports
require dasllama/dasllama_gemm_schema
require daslib/jobque_boost public
require dasllama/dasllama_par
require math

// The GEMM family as a [tune] client (gemm_generator_plan.md part 3; promoted from the M2
// GO/NO-GO experiment): the perm grid below stamps dasllama_gemm_gen::q8q8_tile perms through
// [llvm_code], and the [tune_companion] rows stamp q8q8_layout_gen + q8q8_gemv_gen +
// mx4q8_gemv_gen from the same entry — the four-function stamp: the runtime repacks (Q8 AND
// mx4 planes) ask the layout companion which interleave the stamped cores read, and all four
// generators share one decline predicate, so kernels and repacks cannot desync on any tier.
// Normal runs stamp exactly one winner (manifest > fallback kstep2 = the M2 perm);
// DAS_TUNE_MODE=tune/test stamps the grid + the *_variants() registries for the harness
// (gen_parity_probe / gen_tune_probe). This module registers ONE backend — "arm64-gen"
// (priority 25, the arm64 load-select tier since slice C): every slot, Q8 and mx4, is the
// generated family or a das traversal over it, reading the stamped layout at runtime.
// dasllama_common pulls it in behind a path guard (`require ?llvm/daslib/llvm_tune`), so any
// Q8/mx4 model load on arm64+jit runs the generated family. The generators live in
// dasllama/dasllama_gemm_gen.das (llvm-jit context, wired via llvm/daslib/llvm_user_modules.das).

//! The layout companion (the four-function stamp): the repack interleave (mr) the stamped tile
//! reads. Reference body = the reference tile's grp4; the generator emits the perm's mr and
//! declines in lockstep with the tile generator (shared perm_declines), so a perm the tile
//! can't emit keeps the grp4 reference pair on both sides — on every tier, JIT-time declines
//! included.
def q8q8_layout_gen() : int {
    return q8q8_repack_type(GEMM_REFERENCE_MR).interleave
}

//! The GEMV companion (the nr=1 perm sub-family, slice D): a rows-range core with the mm_rows
//! slot signature — rows [rb, re) of one region, no internal dispatch, rb/re multiples of the
//! stamped mr (the mm/group3/groupn wrappers chunk by groups; the mm_rows slot contract is
//! multiples of 32). The generator emits the grp<mr> single-token k-loop with the group walk
//! inside (gkstep blocks per iteration — independent sdot chains); the reference body is the
//! hand laneq rows walk over the grp4 reference layout, declining in lockstep with the tile
//! and layout via the shared predicate. Not `private`: it IS the mm_rows slot and is called
//! from inside lifted parallel_for worker lambdas.
[hint(unsafe_range_check, noalias = wp, noalias = sp, noalias = xqp, noalias = xsp)]
def q8q8_gemv_gen(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, rb, re : int64) : void {
    let nb = n / 32l
    unsafe {
        for (g in range64(rb / 4l, re / 4l)) {
            let f = dot_q8q8_laneq4(wp + g * 4l * n, sp + g * 4l * nb, xqp, xsp, n)
            yp[g * 4l + 0l] = f.x
            yp[g * 4l + 1l] = f.y
            yp[g * 4l + 2l] = f.z
            yp[g * 4l + 3l] = f.w
        }
    }
}

//! The mx4 GEMV companion (slice E — the second quant family): the MXFP4·Q8 twin of
//! q8q8_gemv_gen, rows [rb, re) of one region off the grp<mr>-interleaved nibble/exponent
//! planes (repack_mx4_grp — the SAME mr as the Q8 layout, one companion for both). The
//! generator emits the tbl-dequant laneq shape (per block: 4 nibble loads per row quad feed
//! tbl lo/hi + indexed sdot, e8m0 scale fold in-register); reference body = the hand laneq
//! mx4 rows walk over the grp4 reference planes, declining in lockstep via the shared
//! predicate. Not `private`: called from inside lifted parallel_for worker lambdas.
[hint(unsafe_range_check, noalias = wn, noalias = we, noalias = xqp, noalias = xsp)]
def mx4q8_gemv_gen(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, rb, re : int64) : void {
    let nrow = n / 2l
    let nbb = n / 32l
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])
        for (g in range64(rb / 4l, re / 4l)) {
            let f = dot_mx4q8_laneq4(lutp, wn + g * 4l * nrow, we + g * 4l * nbb, xqp, xsp, n)
            yp[g * 4l + 0l] = f.x
            yp[g * 4l + 1l] = f.y
            yp[g * 4l + 2l] = f.z
            yp[g * 4l + 3l] = f.w
        }
    }
}

//! The generated tile: mr interleaved rows x 4 tokens (the q8q8_repack_type(mr) layout — see
//! dasllama_gemm_schema; the stamped mr is what q8q8_layout_gen reports). The reference body —
//! 4 single-token laneq4 dots with the same per-block fold order as the tile — runs on interp,
//! AOT, non-arm64 JIT, and whenever the generator declines. The dot=/width= rows are the x64
//! legs (slice F): they decline on arm64 and light per cpuid tier on x86-64 (avx2 / vnni256 /
//! avx512bw / avx512vnni / avxvnniint8), so ONE grid serves every ISA. The three trailing
//! suffix rows decline by design everywhere (q-reg budget, lane structure, a dot with no
//! 128-bit leg) and pin the decline rail in test mode. Not `private`: called from inside the
//! lifted parallel_for worker lambda below.
[tune_perm(kstep = 1), tune_perm(kstep = 2), tune_perm(kstep = 4), tune_perm(kstep = 2, nrsplit = 2),
 tune_perm(kstep = 1, nrsplit = 2), tune_perm(kstep = 4, nrsplit = 2),
 tune_perm(kstep = 1, nrsplit = 2, mr = 8), tune_perm(kstep = 2, nrsplit = 2, mr = 8), tune_perm(kstep = 4, nrsplit = 2, mr = 8),
 tune_perm(kstep = 2, gkstep = 2), tune_perm(kstep = 2, gkstep = 4),
 tune_perm(kstep = 4, nrsplit = 2, mr = 8, gkstep = 2), tune_perm(kstep = 4, nrsplit = 2, mr = 8, gkstep = 4),
 tune_perm(dot = "maddubs", width = 256, mr = 8, kstep = 2), tune_perm(dot = "maddubs", width = 256, mr = 8, kstep = 4, nrsplit = 2),
 tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 2), tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 4, nrsplit = 2),
 tune_perm(dot = "vpdpbusd", width = 256, mr = 16, kstep = 2, nrsplit = 2), tune_perm(dot = "vpdpbssd", width = 256, mr = 8, kstep = 2),
 tune_perm(dot = "maddubs", width = 512, mr = 16, kstep = 2), tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 2),
 tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 4, nrsplit = 2), tune_perm(dot = "vpdpbusd", width = 512, mr = 32, kstep = 2, nrsplit = 2),
 tune_perm(dot = "vpdpbusd", width = 256, mr = 8, kstep = 2, gkstep = 2), tune_perm(dot = "vpdpbusd", width = 512, mr = 16, kstep = 2, gkstep = 2),
 tune_perm(suffix = "mr8_budget", mr = 8), tune_perm(suffix = "mr2_lanes", mr = 2), tune_perm(dot = "vpdpbusd"),
 tune_companion(fn = "q8q8_layout_gen", gen = "dasllama_gemm_gen::q8q8_layout"),
 tune_companion(fn = "q8q8_gemv_gen", gen = "dasllama_gemm_gen::q8q8_gemv"),
 tune_companion(fn = "mx4q8_gemv_gen", gen = "dasllama_gemm_gen::mx4_gemv"),
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

//! mr-generalized MXFP4 plane repack — repack_mx4_neon is the mr=4 instance (same loops,
//! byte-identical output there). Nibble bytes interleave [dword-group j][row r][4 bytes]
//! per block (16*mr bytes per block-group — the layout whose nibble order maps byte-for-byte
//! onto the grp<mr> Q8 order, see expand_mx4_region_q8), E8M0 scale bytes mr-per-block; tail
//! rows (d % mr) stay row-major. Public: the probes repack per-variant copies with an
//! explicit mr.
def repack_mx4_grp(var np : uint8?; var ep : uint8?; n, d, mr : int64) {
    let nrow = n / 2l    // nibble bytes per row
    let nbb = n / 32l    // blocks per row
    let ng = d / mr
    var tn : array<uint8>
    var te : array<uint8>
    tn |> resize(int(d * nrow))
    te |> resize(int(d * nbb))
    unsafe {
        var tnp = addr(tn[0])
        var tep = addr(te[0])
        for (i in range64(d * nrow)) {
            tnp[i] = np[i]
        }
        for (i in range64(d * nbb)) {
            tep[i] = ep[i]
        }
        for (g in range64(ng)) {
            let gnb = g * mr * nrow
            for (bi in range64(nbb)) {
                let dst = gnb + bi * 16l * mr
                for (j in range64(4l)) {
                    for (r in range64(mr)) {
                        let src = (g * mr + r) * nrow + bi * 16l + j * 4l
                        let dj = dst + j * 4l * mr + r * 4l
                        np[dj + 0l] = tnp[src + 0l]
                        np[dj + 1l] = tnp[src + 1l]
                        np[dj + 2l] = tnp[src + 2l]
                        np[dj + 3l] = tnp[src + 3l]
                    }
                }
            }
            let geb = g * mr * nbb
            for (bi in range64(nbb)) {
                for (r in range64(mr)) {
                    ep[geb + bi * mr + r] = tep[(g * mr + r) * nbb + bi]
                }
            }
        }
    }
    delete tn
    delete te
}

// the backend mx4 repack slot: same layout companion as the Q8 repack — planes and weights
// interleave at the ONE stamped mr
def private repack_mx4_gen(var np : uint8?; var ep : uint8?; n, d : int64) {
    repack_mx4_grp(np, ep, n, d, int64(q8q8_layout_gen()))
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

// mm slot: the hand laneq dispatch shape with the group walk handed to the generated rows
// core — ONE core call per chunk (the group loop lives inside the generated code). Strides
// come off the layout companion, so the same wrapper serves both stamped layouts; the row
// tail (d % mr) stays row-major in the repack and rides sdot4x4.
def private q8q8_kernel_gen(var yp : float?; wp : int8 const?; sp : float const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(ng), matmul_chunks_gemv(int(ng * mr), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
        q8q8_gemv_gen(myp, wp, sp, xqp, xsp, n, int64(rb) * mr, int64(re) * mr)
    }
    unsafe {
        for (i in range64(ng * mr, d)) {
            myp[i] = dot_q8q8_sdot4x4(wp + i * n, sp + i * nb, xqp, xsp, n)
        }
    }
}

// group3: the hand laneq fused walk (one dispatch over the three regions' combined group
// space), each worker chunk split at region boundaries into at most three rows-core calls
def private q8q8_group3_gen(var y0p : float?; var y1p : float?; var y2p : float?; wp : int8 const?; sp : float const?;
                            woff0, woff1, woff2 : int64; xqp : int8 const?; xsp : float const?; n, d0, d1, d2 : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng0 = d0 / mr
    let ng1 = d1 / mr
    let ng2 = d2 / mr
    let ngtot = ng0 + ng1 + ng2
    var w0 = y0p
    var w1 = y1p
    var w2 = y2p
    // oversplit only under team dispatch — same trade as the hand laneq group3
    maybe_parallel_for(n * (d0 + d1 + d2) >= g_matmul_par_threshold, 0, int(ngtot), matmul_chunks_gemv(int(ngtot * mr), get_dispatch_lanes() * (get_jobque_team_mode() ? get_q8_batch_chunks_per_job() : 1))) $(rb, re) {
        unsafe {
            let b0 = int64(rb)
            let e0 = min(int64(re), ng0)
            if (b0 < e0) {
                q8q8_gemv_gen(w0, wp + woff0, sp + woff0 / 32l, xqp, xsp, n, b0 * mr, e0 * mr)
            }
            let b1 = max(int64(rb) - ng0, 0l)
            let e1 = min(int64(re) - ng0, ng1)
            if (b1 < e1) {
                q8q8_gemv_gen(w1, wp + woff1, sp + woff1 / 32l, xqp, xsp, n, b1 * mr, e1 * mr)
            }
            let b2 = max(int64(rb) - ng0 - ng1, 0l)
            let e2 = min(int64(re) - ng0 - ng1, ng2)
            if (b2 < e2) {
                q8q8_gemv_gen(w2, wp + woff2, sp + woff2 / 32l, xqp, xsp, n, b2 * mr, e2 * mr)
            }
        }
    }
    unsafe {
        for (i in range64(ng0 * mr, d0)) {
            w0[i] = dot_q8q8_sdot4x4(wp + woff0 + i * n, sp + woff0 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng1 * mr, d1)) {
            w1[i] = dot_q8q8_sdot4x4(wp + woff1 + i * n, sp + woff1 / 32l + i * nb, xqp, xsp, n)
        }
        for (i in range64(ng2 * mr, d2)) {
            w2[i] = dot_q8q8_sdot4x4(wp + woff2 + i * n, sp + woff2 / 32l + i * nb, xqp, xsp, n)
        }
    }
}

// groupn: the hand laneq fused walk over the (region x group) space; each worker chunk runs
// region-contiguous rows-core spans + the bias post-add over the same span (an extra y pass,
// trivial next to the dots)
def private q8q8_groupn_gen(var yp : float?; wp : int8 const?; sp : float const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * ng), matmul_chunks_gemv(int(nregions * ng * mr), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(gb, ge) {
        unsafe {
            var gg = int64(gb)
            while (gg < int64(ge)) {
                let r = gg / ng
                let gLocal = gg % ng
                let gEnd = min(int64(ge) - r * ng, ng)
                let woff = offs[r * 2l]
                let xoff = offs[r * 2l + 1l]
                q8q8_gemv_gen(myp + r * d, wp + woff, sp + woff / 32l, xqp + xoff, xsp + xoff / 32l, n, gLocal * mr, gEnd * mr)
                if (bp != null) {
                    for (i in range64(gLocal * mr, gEnd * mr)) {
                        myp[r * d + i] += bp[boffs[r] + i]
                    }
                }
                gg = r * ng + gEnd
            }
        }
    }
    unsafe {
        for (r in range64(nregions)) {   // row tails (d % mr): row-major sdot4x4 per region
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            for (i in range64(ng * mr, d)) {
                var v = dot_q8q8_sdot4x4(wp + woff + i * n, sp + woff / 32l + i * nb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + i]
                }
                myp[r * d + i] = v
            }
        }
    }
}

// mm_mx4 slot: the mx4 twin of q8q8_kernel_gen — group chunks handed to the generated mx4
// rows core, row tail (d % mr) row-major via dot_mx4q8 (tail planes stay row-major in the
// repack)
def private mx4q8_kernel_gen(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n, d : int64) {
    let nrow = n / 2l
    let nbb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(n * d >= g_matmul_par_threshold, 0, int(ng), matmul_chunks_gemv(int(ng * mr), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(rb, re) {
            mx4q8_gemv_gen(myp, wn, we, xqp, xsp, n, int64(rb) * mr, int64(re) * mr)
        }
        for (i in range64(ng * mr, d)) {
            myp[i] = dot_mx4q8(lutp, wn + i * nrow, we + i * nbb, xqp, xsp, n)
        }
    }
}

// groupn_mx4: the mx4 twin of q8q8_groupn_gen — region-contiguous rows-core spans + bias
// post-add, row tails row-major per region
def private mx4q8_groupn_gen(var yp : float?; wn : uint8 const?; we : uint8 const?; offs : int64 const?; nregions : int64; xqp : int8 const?; xsp : float const?; bp : float const?; boffs : int64 const?; n, d : int64) {
    let nrow = n / 2l
    let nbb = n / 32l
    let mr = int64(q8q8_layout_gen())
    let ng = d / mr
    var myp = yp
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        let lutp = addr(lut[0])   // frame outlives the join, so workers read a live pointer
        maybe_parallel_for(n * d * nregions >= g_matmul_par_threshold, 0, int(nregions * ng), matmul_chunks_gemv(int(nregions * ng * mr), get_dispatch_lanes() * get_q8_batch_chunks_per_job())) $(gb, ge) {
            unsafe {
                var gg = int64(gb)
                while (gg < int64(ge)) {
                    let r = gg / ng
                    let gLocal = gg % ng
                    let gEnd = min(int64(ge) - r * ng, ng)
                    let woff = offs[r * 2l]
                    let xoff = offs[r * 2l + 1l]
                    mx4q8_gemv_gen(myp + r * d, wn + woff / 2l, we + woff / 32l, xqp + xoff, xsp + xoff / 32l, n, gLocal * mr, gEnd * mr)
                    if (bp != null) {
                        for (i in range64(gLocal * mr, gEnd * mr)) {
                            myp[r * d + i] += bp[boffs[r] + i]
                        }
                    }
                    gg = r * ng + gEnd
                }
            }
        }
        for (r in range64(nregions)) {   // row tails (d % mr): row-major dot per region
            let woff = offs[r * 2l]
            let xoff = offs[r * 2l + 1l]
            for (i in range64(ng * mr, d)) {
                var v = dot_mx4q8(lutp, wn + woff / 2l + i * nrow, we + woff / 32l + i * nbb, xqp + xoff, xsp + xoff / 32l, n)
                if (bp != null) {
                    v += bp[boffs[r] + i]
                }
                myp[r * d + i] = v
            }
        }
    }
}

[init]
def dasllama_math_gen_register() {
    // Same gate as the laneq backend it supersedes; needs_repack keeps it out of auto-select
    // (direct callers stay on arm64-sdot). ONE backend since slice E: every slot — Q8 and
    // mx4 — reads the STAMPED layout at runtime (repacks and traversal strides off the
    // layout companion, cores generated for that mr), so the slice C two-flavor split
    // (laneq borrows vs grp stopgaps, selected by an `available` predicate) is gone. The
    // q8_layout field feeds the activation-time cache the mx4 expand's positional map reads;
    // it is evaluated at selection time, never at [init] ([init]s run before the JIT
    // installs generated code — the slice C mr8 bug).
    if (get_architecture_name() == "arm64" && jit_enabled()) {
        register_kernel_backend(KernelBackend(name = "arm64-gen", mm = @@q8q8_kernel_gen,
            batch = @@q8q8_batch_kernel_neon_laneq_gen, group3 = @@q8q8_group3_gen,
            repack = @@repack_q8q8_gen,
            mm_mx4 = @@mx4q8_kernel_gen, repack_mx4 = @@repack_mx4_gen,
            groupn = @@q8q8_groupn_gen, groupn_mx4 = @@mx4q8_groupn_gen,
            mm_rows = @@q8q8_gemv_gen,
            needs_repack = true, mx4_expand_interleaved = true, priority = 25,
            q8_layout = @@q8q8_layout_gen))
    }
}
