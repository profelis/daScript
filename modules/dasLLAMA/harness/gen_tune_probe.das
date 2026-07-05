options gen2
options persistent_heap
options _jit_fast_math = true   // match gemm_1core_probe / the end-to-end config

// M3/M4 grid gates (gemm_generator_plan.md): run with DAS_TUNE_MODE=test or =tune, -jit.
// Layout is per-variant: each variant's mr comes off its q8q8_layout_gen__<suffix>
// companion (declined perms report the reference grp4 — the lockstep rail), and the probe
// repacks a fresh copy of the row-major master into that variant's grp<mr> before running it.
// Since slice D the grid stamps a THIRD function — the q8q8_gemv_gen rows core — and both
// modes cover it alongside the tile.
//   test: every [tune_perm] variant of q8q8_tile_gen AND q8q8_gemv_gen (dasllama_math_gen)
//         must match the hand laneq oracle (computed once, from a grp4 copy — the fold order
//         is layout-independent; the gemv compares the token-0 row) within
//         CLOSE_REL/CLOSE_ABS on nb-even, nb-odd and a production-ish slice. Tolerance, not
//         equality: variants run under full fast-math, so the backend may legally regroup a
//         fold per loop shape (~1e-6 relative; llama.cpp holds no cross-kernel bit-parity
//         either) — real generator bugs (wrong stride/lane/scale) are orders louder and
//         still die here. Declining perms (mr8_budget / mr2_lanes / dot_vpdpbusd) run the
//         reference bodies.
//   tune: iso-bench every variant (interleaved best-of) on its own repacked buffers — the
//         tile on a batch shape, the gemv core on a single-token decode shape — print both
//         tables, and tune_manifest_set the merged winner: the row whose TILE knobs win the
//         batch bench and whose gkstep wins the decode bench among rows with those tile
//         knobs (one manifest entry = one coherent layout+tile+gemv decision). A following
//         normal run stamps it (the round-trip; point DAS_TUNE_MANIFEST somewhere writable
//         first).

require dasllama/dasllama_math
require dasllama/dasllama_math_default
require dasllama/dasllama_math_aarch64_neon
require dasllama/dasllama_math_gen
require dasllama/dasllama_gemm_schema
require dasllama/dasllama_quant
require llvm/daslib/llvm_tune
require daslib/random
require daslib/fio   // has_env_variable: the compile-only mint gate (slice J recipe)
require math
require strings

let ROUNDS = 6

struct Fixture {
    n, d, ntok, nb : int64
    q : array<int8>       // row-major master — repacked per variant into a copy
    s : array<float>
    xq : array<int8>
    xs : array<float>
    xbs : array<int>      // −128·Σx per (token, block) — the bias128 tile's bsums plane
    yref : array<float>
}

def build_fixture(n, d, ntok : int64) : Fixture {
    var fx = Fixture(n = n, d = d, ntok = ntok, nb = n / 32l)
    var w : array<float>
    w |> resize(int(n * d))
    for (i in range64(n * d)) {
        w[i] = float(i % 17l) * 0.13 - 1.1
    }
    let qt <- quantize_q8_0(w, n * d)
    fx.q |> resize(int(n * d))
    fx.s |> resize(int(d * fx.nb))
    for (i in range64(n * d)) {
        fx.q[i] = qt.q[i]
    }
    for (i in range64(d * fx.nb)) {
        fx.s[i] = qt.scales[i]
    }

    var xrow : array<float>
    xrow |> resize(int(n))
    fx.xq |> resize(int(ntok * n))
    fx.xs |> resize(int(ntok * fx.nb))
    for (tk in range64(ntok)) {
        for (i in range64(n)) {
            xrow[i] = float((i + tk * 7l) % 23l) * 0.07 - 0.8
        }
        quantize_q8_0_into(xrow, n, fx.xq, fx.xs, tk * n, tk * fx.nb)
    }
    fx.xbs |> resize(int(ntok * fx.nb))
    for (tk in range64(ntok)) {
        for (bi in range64(fx.nb)) {
            var bsum = 0
            for (j in range64(32l)) {
                bsum += int(fx.xq[tk * n + bi * 32l + j])
            }
            fx.xbs[tk * fx.nb + bi] = -128 * bsum
        }
    }

    // the oracle: hand laneq semantics off a grp4 copy — the per-block fold order is the same
    // in every variant, so one oracle serves all layouts
    fx.yref |> resize(int(ntok * d))
    var q4 := fx.q
    var s4 := fx.s
    unsafe {
        repack_q8q8_grp(addr(q4[0]), addr(s4[0]), n, d, 4l)
        let wp = addr(q4[0])
        let sp = addr(s4[0])
        let xqp = addr(fx.xq[0])
        let xsp = addr(fx.xs[0])
        var yrp = addr(fx.yref[0])
        for (g in range64(d / 4l)) {
            let wgp = wp + g * 4l * n
            let sgp = sp + g * 4l * fx.nb
            for (tk in range64(ntok)) {
                let f = dot_q8q8_laneq4(wgp, sgp, xqp + tk * n, xsp + tk * fx.nb, n)
                yrp[tk * d + g * 4l + 0l] = f.x
                yrp[tk * d + g * 4l + 1l] = f.y
                yrp[tk * d + g * 4l + 2l] = f.z
                yrp[tk * d + g * 4l + 3l] = f.w
            }
        }
    }
    delete q4
    delete s4
    return <- fx
}

// suffix -> repack interleave, off the layout companion's variants registry (lockstep with
// the tile variants by construction — same suffixes, same decline predicate)
def variant_mrs() : table<string; int> {
    var mrs : table<string; int>
    var lvs <- q8q8_layout_gen_variants()
    for (v in lvs) {
        mrs[v._0] = invoke(v._1)
    }
    delete lvs
    return <- mrs
}

// suffix -> weight-plane bias, off the wbias companion's variants registry (same lockstep)
def variant_wbias() : table<string; int> {
    var wbs : table<string; int>
    var bvs <- q8q8_wbias_gen_variants()
    for (v in bvs) {
        wbs[v._0] = invoke(v._1)
    }
    delete bvs
    return <- wbs
}

// suffix -> plane kgroup, off the kgroup companion's variants registry (same lockstep; 8 on
// the smmla rows — the repack below must write the row-pair plane those tiles read)
def variant_kgroups() : table<string; int> {
    var kgs : table<string; int>
    var kvs <- q8q8_kgroup_gen_variants()
    for (v in kvs) {
        kgs[v._0] = invoke(v._1)
    }
    delete kvs
    return <- kgs
}

// suffix -> tokens per tile call, off the tokstep companion's variants registry (same
// lockstep; 16/32 on the amx rows, whose macro also spans ts/16 row-groups — the walk below
// must match the stamped shape)
def variant_toksteps() : table<string; int> {
    var tss : table<string; int>
    var tvs <- q8q8_tokstep_gen_variants()
    for (v in tvs) {
        tss[v._0] = invoke(v._1)
    }
    delete tvs
    return <- tss
}

// one full tile sweep: every (ts-token, gs-group) unit through `tile`, on the variant's own
// repacked buffers (q/s); the fixture's bsums plane rides along (biased variants read it,
// everything else ignores the parameter). Fixtures divide evenly (ntok % ts == 0, groups %
// gs == 0) — production tails are the batch wrapper's job, not the tile's.
def run_tile(tile; fx : Fixture; q : array<int8>; s : array<float>; mr, ts, gs : int64; var y : array<float>) {
    let ng = fx.d / mr
    verify(fx.ntok % ts == 0l && ng % gs == 0l)
    unsafe {
        let wp = addr(q[0])
        let sp = addr(s[0])
        let xqp = addr(fx.xq[0])
        let xsp = addr(fx.xs[0])
        let xbsp = addr(fx.xbs[0])
        var yp = addr(y[0])
        for (u in range64(ng / gs)) {
            let g = u * gs
            let wgp = wp + g * mr * fx.n
            let sgp = sp + g * mr * fx.nb
            var t0 = 0l
            while (t0 < fx.ntok) {
                invoke(tile, yp, wgp, sgp, xqp, xsp, xbsp, fx.n, fx.d, g, t0)
                t0 += ts
            }
        }
    }
}

// one gemv rows-core sweep over all group rows for token 0 (the group loop is inside the
// generated function — one call, like a production dispatch chunk)
def run_gemv(gemv; fx : Fixture; q : array<int8>; s : array<float>; mr : int64; var y : array<float>) {
    unsafe {
        invoke(gemv, addr(y[0]), addr(q[0]), addr(s[0]), addr(fx.xq[0]), addr(fx.xs[0]), fx.n, 0l, (fx.d / mr) * mr)
    }
}

// suffix -> gemv rows-core variant, keyed like the tile registry (same perm rows by
// construction)
def gemv_variants_by_suffix() : table<string; MatmulQ8Q8RowsFn> {
    var tab : table<string; MatmulQ8Q8RowsFn>
    var gvs <- q8q8_gemv_gen_variants()
    for (v in gvs) {
        tab[v._0] = v._1
    }
    delete gvs
    return <- tab
}

// suffix -> witness variant (the five-function stamp's availability bit), keyed like the
// tile registry
def witness_variants_by_suffix() : table<string; function<() : bool>> {
    var tab : table<string; function<() : bool>>
    var wvs <- q8q8_family_live_variants()
    for (v in wvs) {
        tab[v._0] = v._1
    }
    delete wvs
    return <- tab
}

// the row's tile knobs: the suffix minus its gemv piece — rows carrying gkstep spell the
// tile knobs explicitly, so "kstep2_gkstep2" keys with "kstep2"
def tile_key(suffix : string) : string {
    let i = find(suffix, "_gkstep")
    return i < 0 ? suffix : slice(suffix, 0, i)
}

// ===== the mx4 gemv companion (slice E) =====

typedef Mx4RowsFn = function<(var yp : float?; wn : uint8 const?; we : uint8 const?; xqp : int8 const?; xsp : float const?; n : int64; rb : int64; re : int64) : void>

struct Mx4Fixture {
    n, d, nb : int64
    wn : array<uint8>     // row-major nibble plane master — repacked per variant into a copy
    we : array<uint8>     // row-major E8M0 exponent plane master
    xq : array<int8>
    xs : array<float>
    yref : array<float>
}

def build_mx4_fixture(n, d : int64) : Mx4Fixture {
    var fx = Mx4Fixture(n = n, d = d, nb = n / 32l)
    var seed = int4(20260704, 5, 9, 2)
    fx.wn <- [for (_i in range64(d * n / 2l)); uint8(random_int(seed) % 256)]
    fx.we <- [for (_i in range64(d * fx.nb)); uint8(118 + random_int(seed) % 14)]
    var xrow : array<float>
    xrow |> resize(int(n))
    fx.xq |> resize(int(n))
    fx.xs |> resize(int(fx.nb))
    for (i in range64(n)) {
        xrow[i] = float(i % 23l) * 0.07 - 0.8
    }
    quantize_q8_0_into(xrow, n, fx.xq, fx.xs, 0l, 0l)
    // the oracle: hand interleaved-mx4 semantics off a grp4 plane copy (fold order is
    // layout-independent, like the Q8 oracle)
    fx.yref |> resize(int(d))
    var n4 := fx.wn
    var e4 := fx.we
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        repack_mx4_grp(addr(n4[0]), addr(e4[0]), n, d, 4l)
        let lutp = addr(lut[0])
        let np = addr(n4[0])
        let ep = addr(e4[0])
        var yrp = addr(fx.yref[0])
        for (g in range64(d / 4l)) {
            let f = dot_mx4q8_laneq4(lutp, np + g * 4l * (n / 2l), ep + g * 4l * fx.nb, addr(fx.xq[0]), addr(fx.xs[0]), n)
            yrp[g * 4l + 0l] = f.x
            yrp[g * 4l + 1l] = f.y
            yrp[g * 4l + 2l] = f.z
            yrp[g * 4l + 3l] = f.w
        }
    }
    delete n4
    delete e4
    return <- fx
}

def mx4_variants_by_suffix() : table<string; Mx4RowsFn> {
    var tab : table<string; Mx4RowsFn>
    var gvs <- mx4q8_gemv_gen_variants()
    for (v in gvs) {
        tab[v._0] = v._1
    }
    delete gvs
    return <- tab
}

def run_mx4_gemv(gemv; fx : Mx4Fixture; wn : array<uint8>; we : array<uint8>; mr : int64; var y : array<float>) {
    unsafe {
        invoke(gemv, addr(y[0]), addr(wn[0]), addr(we[0]), addr(fx.xq[0]), addr(fx.xs[0]), fx.n, 0l, (fx.d / mr) * mr)
    }
}

def close_to_mx4_ref(fx : Mx4Fixture; y : array<float>; var maxdiff : float&) : bool {
    var ok = true
    for (i in range(length(y))) {
        let d = abs(y[i] - fx.yref[i])
        maxdiff = max(maxdiff, d)
        ok &&= d <= max(CLOSE_ABS, CLOSE_REL * abs(fx.yref[i]))
    }
    return ok
}

let CLOSE_REL = 1e-4
let CLOSE_ABS = 1e-5

def close_to_ref(fx : Fixture; y : array<float>; var maxdiff : float&) : bool {
    var ok = true
    for (i in range(length(y))) {
        let d = abs(y[i] - fx.yref[i])
        maxdiff = max(maxdiff, d)
        ok &&= d <= max(CLOSE_ABS, CLOSE_REL * abs(fx.yref[i]))
    }
    return ok
}

def test_mode : bool {
    // nb=2 (even main loop), nb=3 (remainder path), production-ish slice — d divides every
    // grid mr (4/8 on arm64, 16/32 on the x64 rows when live); ntok=32 covers one full amx
    // 2×2 macro (and divides the 4/16-token steps of every other row)
    var fxs <- [ <- build_fixture(64l, 32l, 32l), <- build_fixture(96l, 32l, 32l), <- build_fixture(2048l, 64l, 32l)]
    var mfxs <- [ <- build_mx4_fixture(96l, 32l), <- build_mx4_fixture(2048l, 64l)]
    var vs <- q8q8_tile_gen_variants()
    var mrs <- variant_mrs()
    var wbs <- variant_wbias()
    var kgs <- variant_kgroups()
    var tss <- variant_toksteps()
    var gtab <- gemv_variants_by_suffix()
    var mtab <- mx4_variants_by_suffix()
    var wtab <- witness_variants_by_suffix()
    var allok = true
    for (v in vs) {
        let mr = int64(mrs?[v._0] ?? 4)
        let wbias = int64(wbs?[v._0] ?? 0)
        let kgv = int64(kgs?[v._0] ?? 4)
        let tsv = int64(tss?[v._0] ?? 4)
        let gsv = max(tsv / 16l, 1l)
        verify(gtab |> key_exists(v._0))
        verify(mtab |> key_exists(v._0))
        verify(wtab |> key_exists(v._0))
        // witness-lockstep invariants: the reference row is never "live", and a
        // non-reference layout, a biased plane, a kg8 plane or a non-4 tokstep proves the
        // family emitted — the witness must agree
        let live = invoke(wtab[v._0])
        if (v._0 == "reference") {
            verify(!live)
        }
        if (int(mr) != GEMM_REFERENCE_MR && !live) {
            print("  WITNESS DESYNC {v._0}: layout mr={mr} but witness says not live\n")
            allok = false
        }
        if (wbias != 0l && !live) {
            print("  WBIAS DESYNC {v._0}: wbias={wbias} but witness says not live\n")
            allok = false
        }
        if (kgv != 4l && !live) {
            print("  KGROUP DESYNC {v._0}: kgroup={kgv} but witness says not live\n")
            allok = false
        }
        if (tsv != 4l && !live) {
            print("  TOKSTEP DESYNC {v._0}: tokstep={tsv} but witness says not live\n")
            allok = false
        }
        var ok = true
        var gok = true
        var maxdiff = 0.0
        var gmaxdiff = 0.0
        for (fx in fxs) {
            var qv := fx.q
            var sv := fx.s
            unsafe {
                repack_q8q8_grp(addr(qv[0]), addr(sv[0]), fx.n, fx.d, mr, wbias, kgv)
            }
            var y : array<float>
            y |> resize(int(fx.ntok * fx.d))
            run_tile(v._1, fx, qv, sv, mr, tsv, gsv, y)
            let fxok = close_to_ref(fx, y, maxdiff)
            if (!fxok) {
                var shown = 0
                for (i in range(length(y))) {
                    if (abs(y[i] - fx.yref[i]) > max(CLOSE_ABS, CLOSE_REL * abs(fx.yref[i])) && shown < 6) {
                        print("  DBG {v._0} n={fx.n}: y[{i}] (tok {i / int(fx.d)} col {i % int(fx.d)}) = {y[i]} want {fx.yref[i]}\n")
                        shown++
                    }
                }
            }
            ok = ok && fxok
            // the gemv rows core on the same buffers: token 0's row of the oracle
            var yg : array<float>
            yg |> resize(int(fx.d))
            run_gemv(gtab[v._0], fx, qv, sv, mr, yg)
            let gfxok = close_to_ref(fx, yg, gmaxdiff)
            if (!gfxok) {
                var shown = 0
                for (i in range(length(yg))) {
                    if (abs(yg[i] - fx.yref[i]) > max(CLOSE_ABS, CLOSE_REL * abs(fx.yref[i])) && shown < 6) {
                        print("  DBG gemv {v._0} n={fx.n}: y[{i}] = {yg[i]} want {fx.yref[i]}\n")
                        shown++
                    }
                }
            }
            gok = gok && gfxok
            delete y
            delete yg
            delete qv
            delete sv
        }
        // the mx4 gemv companion on its own plane fixtures (repacked per variant)
        var mok = true
        var mmaxdiff = 0.0
        for (mfx in mfxs) {
            var nv := mfx.wn
            var ev := mfx.we
            unsafe {
                repack_mx4_grp(addr(nv[0]), addr(ev[0]), mfx.n, mfx.d, mr)
            }
            var ym : array<float>
            ym |> resize(int(mfx.d))
            run_mx4_gemv(mtab[v._0], mfx, nv, ev, mr, ym)
            let mfxok = close_to_mx4_ref(mfx, ym, mmaxdiff)
            if (!mfxok) {
                var shown = 0
                for (i in range(length(ym))) {
                    if (abs(ym[i] - mfx.yref[i]) > max(CLOSE_ABS, CLOSE_REL * abs(mfx.yref[i])) && shown < 6) {
                        print("  DBG mx4 {v._0} n={mfx.n}: y[{i}] = {ym[i]} want {mfx.yref[i]}\n")
                        shown++
                    }
                }
            }
            mok = mok && mfxok
            delete ym
            delete nv
            delete ev
        }
        let biasTag = wbias != 0l ? " bias{wbias}" : ""
        let kgTag = kgv != 4l ? " kg{kgv}" : ""
        print("{v._0} (mr={mr}{biasTag}{kgTag}, {live ? "live" : "ref"}): tile {ok ? "ok" : "MISMATCH"} (maxdiff {maxdiff}), gemv {gok ? "ok" : "MISMATCH"} (maxdiff {gmaxdiff}), mx4 {mok ? "ok" : "MISMATCH"} (maxdiff {mmaxdiff})\n")
        allok = allok && ok && gok && mok
    }
    delete wtab
    delete mtab
    delete gtab
    delete tss
    delete kgs
    delete wbs
    delete mrs
    delete vs
    delete mfxs
    delete fxs
    return allok
}

struct VBuf {
    q : array<int8>
    s : array<float>
}

def tune_mode_run : bool {
    var fx <- build_fixture(2048l, 512l, 64l)      // batch shape (the kv projection)
    var gfx <- build_fixture(2048l, 8192l, 1l)     // streamed decode shape (DRAM-bound ffn GEMV)
    var hfx <- build_fixture(2048l, 512l, 1l)      // hot decode shape (cache-resident — the
                                                   // only regime where gemv knobs can show)
    var vs <- q8q8_tile_gen_variants()
    var mrs <- variant_mrs()
    var wbs <- variant_wbias()
    var kgs <- variant_kgroups()
    var tss <- variant_toksteps()
    var gtab <- gemv_variants_by_suffix()
    let nv = length(vs)
    // per-variant repacked buffers, built once outside the timing loop
    var bufs : array<VBuf>
    var gbufs : array<VBuf>
    var hbufs : array<VBuf>
    bufs |> resize(nv)
    gbufs |> resize(nv)
    hbufs |> resize(nv)
    var vmr : array<int64>
    var vts : array<int64>
    var vgs : array<int64>
    vmr |> resize(nv)
    vts |> resize(nv)
    vgs |> resize(nv)
    for (vi in range(nv)) {
        vmr[vi] = int64(mrs?[vs[vi]._0] ?? 4)
        vts[vi] = int64(tss?[vs[vi]._0] ?? 4)
        vgs[vi] = max(vts[vi] / 16l, 1l)
        let wb = int64(wbs?[vs[vi]._0] ?? 0)
        let kgv = int64(kgs?[vs[vi]._0] ?? 4)
        verify(gtab |> key_exists(vs[vi]._0))
        bufs[vi].q := fx.q
        bufs[vi].s := fx.s
        gbufs[vi].q := gfx.q
        gbufs[vi].s := gfx.s
        hbufs[vi].q := hfx.q
        hbufs[vi].s := hfx.s
        unsafe {
            repack_q8q8_grp(addr(bufs[vi].q[0]), addr(bufs[vi].s[0]), fx.n, fx.d, vmr[vi], wb, kgv)
            repack_q8q8_grp(addr(gbufs[vi].q[0]), addr(gbufs[vi].s[0]), gfx.n, gfx.d, vmr[vi], wb, kgv)
            repack_q8q8_grp(addr(hbufs[vi].q[0]), addr(hbufs[vi].s[0]), hfx.n, hfx.d, vmr[vi], wb, kgv)
        }
    }
    var best : array<double>
    var gbest : array<double>
    var hbest : array<double>
    best |> resize(nv)
    gbest |> resize(nv)
    hbest |> resize(nv)
    for (i in range(nv)) {
        best[i] = 1.0e30lf
        gbest[i] = 1.0e30lf
        hbest[i] = 1.0e30lf
    }
    var y : array<float>
    y |> resize(int(fx.ntok * fx.d))
    var yg : array<float>
    yg |> resize(int(gfx.d))
    var yh : array<float>
    yh |> resize(int(hfx.d))
    // correctness first — a tune run must never crown a broken variant
    for (vi in range(nv)) {
        run_tile(vs[vi]._1, fx, bufs[vi].q, bufs[vi].s, vmr[vi], vts[vi], vgs[vi], y)
        var maxdiff = 0.0
        if (!close_to_ref(fx, y, maxdiff)) {
            print("{vs[vi]._0}: tile MISMATCH (maxdiff {maxdiff}) — aborting tune\n")
            return false
        }
        run_gemv(gtab[vs[vi]._0], gfx, gbufs[vi].q, gbufs[vi].s, vmr[vi], yg)
        var gmaxdiff = 0.0
        if (!close_to_ref(gfx, yg, gmaxdiff)) {
            print("{vs[vi]._0}: gemv MISMATCH (maxdiff {gmaxdiff}) — aborting tune\n")
            return false
        }
    }
    // the hot shape runs HOT_REPS back-to-back per timing sample: 1MB of weights stays
    // cache-resident, so the sample measures compute, not the first-touch stream
    let HOT_REPS = 16
    for (_r in range(ROUNDS)) {   // interleaved best-of: variant order inside each round
        for (vi in range(nv)) {
            let t0 = ref_time_ticks()
            run_tile(vs[vi]._1, fx, bufs[vi].q, bufs[vi].s, vmr[vi], vts[vi], vgs[vi], y)
            let us = double(get_time_usec(t0))
            if (us < best[vi]) {
                best[vi] = us
            }
            let g0 = ref_time_ticks()
            run_gemv(gtab[vs[vi]._0], gfx, gbufs[vi].q, gbufs[vi].s, vmr[vi], yg)
            let gus = double(get_time_usec(g0))
            if (gus < gbest[vi]) {
                gbest[vi] = gus
            }
            let h0 = ref_time_ticks()
            for (_h in range(HOT_REPS)) {
                run_gemv(gtab[vs[vi]._0], hfx, hbufs[vi].q, hbufs[vi].s, vmr[vi], yh)
            }
            let hus = double(get_time_usec(h0)) / double(HOT_REPS)
            if (hus < hbest[vi]) {
                hbest[vi] = hus
            }
        }
    }
    let macs = double(fx.n * fx.d * fx.ntok)
    let gmacs = double(gfx.n * gfx.d)
    let hmacs = double(hfx.n * hfx.d)
    var winner = 0
    for (vi in range(nv)) {
        if (best[vi] < best[winner]) {
            winner = vi
        }
        print("{vs[vi]._0} (mr={vmr[vi]}): tile {macs / best[vi] / 1000.0lf} GMAC/s, gemv stream {gmacs / gbest[vi] / 1000.0lf} / hot {hmacs / hbest[vi] / 1000.0lf} GMAC/s (best of {ROUNDS})\n")
    }
    // the merged winner: the batch bench picks the tile knobs (and with them the layout);
    // the HOT decode bench picks gkstep among the rows sharing those tile knobs (the
    // streamed shape is DRAM-bound and cannot tell kernels apart) — one entry, one
    // coherent layout+tile+gemv decision
    let wkey = tile_key(vs[winner]._0)
    var merged = winner
    for (vi in range(nv)) {
        if (tile_key(vs[vi]._0) == wkey && hbest[vi] < hbest[merged]) {
            merged = vi
        }
    }
    if (merged != winner) {
        print("tile winner {vs[winner]._0} + hot decode winner within '{wkey}' -> {vs[merged]._0}\n")
    }
    let ok = tune_manifest_set("q8q8_tile_gen", vs[merged]._0)
    print("winner: {vs[merged]._0} {ok ? "->" : "-> FAILED TO WRITE"} {tune_manifest_path()}\n")
    delete y
    delete yg
    delete yh
    delete bufs
    delete gbufs
    delete hbufs
    delete vmr
    delete vts
    delete vgs
    delete best
    delete gbest
    delete hbest
    delete gtab
    delete tss
    delete kgs
    delete wbs
    delete mrs
    delete vs
    delete fx
    delete gfx
    delete hfx
    return ok
}

[export]
def main {
    if (!jit_enabled()) {
        print("run with -jit — the generator only fires under the LLVM JIT\n")
        return
    }
    // pre-i8mm mint rail (the slice J no-linker-on-target recipe): the JIT has already
    // linked + installed the full grid DLL by the time main runs — this gate skips
    // EXECUTION only (forced smmla variants would SIGILL on a dotprod-only host). Ship
    // .jitted_scripts to the i8mm box and run there with the same env minus this one —
    // the cache key matches, dlopen, no linker needed on the target.
    if (has_env_variable("GEN_TUNE_COMPILE_ONLY")) {
        var vs <- q8q8_tile_gen_variants()
        print("compile-only: DLL linked, {length(vs)} tile variants, execution skipped\n")
        delete vs
        return
    }
    // select the gen backend where it exists (arm64) — test/tune drive the variant
    // registries directly, so an x64 box runs fine with no gen backend registered
    // (slice F: the x64 grid rows light per cpuid; x64-gen registration is queued)
    for (nm in kernel_backend_names()) {
        if (nm == "arm64-gen") {
            select_kernel_backend("arm64-gen")
        }
    }
    let mode = tune_mode()
    if (mode == "test") {
        print(test_mode() ? "GEN TUNE TEST OK\n" : "GEN TUNE TEST FAIL\n")
    } elif (mode == "tune") {
        print(tune_mode_run() ? "GEN TUNE RUN OK\n" : "GEN TUNE RUN FAIL\n")
    } else {
        print("set DAS_TUNE_MODE=test or =tune (compile-time env: it stamps the variant grid)\n")
    }
}
