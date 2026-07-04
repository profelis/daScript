options gen2
options persistent_heap
options _jit_fast_math = true   // match gemm_1core_probe / the end-to-end config

// M3/M4 grid gates (gemm_generator_plan.md): run with DAS_TUNE_MODE=test or =tune, -jit.
// Layout is per-variant: each tile variant's mr comes off its q8q8_layout_gen__<suffix>
// companion (declined perms report the reference grp4 — the lockstep rail), and the probe
// repacks a fresh copy of the row-major master into that variant's grp<mr> before running it.
//   test: every [tune_perm] variant of q8q8_tile_gen (dasllama_math_gen) must match the hand
//         laneq oracle (computed once, from a grp4 copy — the fold order is layout-
//         independent) within CLOSE_REL/CLOSE_ABS on nb-even, nb-odd and a production-ish
//         slice. Tolerance, not equality: variants run under full fast-math, so the backend
//         may legally regroup a fold per loop shape (~1e-6 relative; llama.cpp holds no
//         cross-kernel bit-parity either) — real generator bugs (wrong stride/lane/scale)
//         are orders louder and still die here. Declining perms (mr8_budget / mr2_lanes /
//         dot_vpdpbusd) run the reference body.
//   tune: iso-bench every variant (interleaved best-of) on its own repacked buffers, print
//         the table, and tune_manifest_set the winner — a following normal run stamps it
//         (the round-trip; point DAS_TUNE_MANIFEST somewhere writable first).

require dasllama/dasllama_math
require dasllama/dasllama_math_default
require dasllama/dasllama_math_aarch64_neon
require dasllama/dasllama_math_gen
require dasllama/dasllama_quant
require llvm/daslib/llvm_tune
require math

let ROUNDS = 6

struct Fixture {
    n, d, ntok, nb : int64
    q : array<int8>       // row-major master — repacked per variant into a copy
    s : array<float>
    xq : array<int8>
    xs : array<float>
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

// one full tile sweep: every group x every 4-token block through `tile`, on the variant's
// own repacked buffers (q/s), walking mr-row groups
def run_tile(tile; fx : Fixture; q : array<int8>; s : array<float>; mr : int64; var y : array<float>) {
    let ng = fx.d / mr
    unsafe {
        let wp = addr(q[0])
        let sp = addr(s[0])
        let xqp = addr(fx.xq[0])
        let xsp = addr(fx.xs[0])
        var yp = addr(y[0])
        for (g in range64(ng)) {
            let wgp = wp + g * mr * fx.n
            let sgp = sp + g * mr * fx.nb
            var t0 = 0l
            while (t0 < fx.ntok) {
                invoke(tile, yp, wgp, sgp, xqp, xsp, fx.n, fx.d, g, t0)
                t0 += 4l
            }
        }
    }
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
    // grid mr (4 and 8)
    var fxs <- [ <- build_fixture(64l, 8l, 4l), <- build_fixture(96l, 8l, 4l), <- build_fixture(2048l, 64l, 8l)]
    var vs <- q8q8_tile_gen_variants()
    var mrs <- variant_mrs()
    var allok = true
    for (v in vs) {
        let mr = int64(mrs?[v._0] ?? 4)
        var ok = true
        var maxdiff = 0.0
        for (fx in fxs) {
            var qv := fx.q
            var sv := fx.s
            unsafe {
                repack_q8q8_grp(addr(qv[0]), addr(sv[0]), fx.n, fx.d, mr)
            }
            var y : array<float>
            y |> resize(int(fx.ntok * fx.d))
            run_tile(v._1, fx, qv, sv, mr, y)
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
            delete y
            delete qv
            delete sv
        }
        print("{v._0} (mr={mr}): {ok ? "ok" : "MISMATCH"} (maxdiff {maxdiff})\n")
        allok = allok && ok
    }
    delete mrs
    delete vs
    delete fxs
    return allok
}

struct VBuf {
    q : array<int8>
    s : array<float>
}

def tune_mode_run : bool {
    var fx <- build_fixture(2048l, 512l, 64l)
    var vs <- q8q8_tile_gen_variants()
    var mrs <- variant_mrs()
    let nv = length(vs)
    // per-variant repacked buffers, built once outside the timing loop
    var bufs : array<VBuf>
    bufs |> resize(nv)
    var vmr : array<int64>
    vmr |> resize(nv)
    for (vi in range(nv)) {
        vmr[vi] = int64(mrs?[vs[vi]._0] ?? 4)
        bufs[vi].q := fx.q
        bufs[vi].s := fx.s
        unsafe {
            repack_q8q8_grp(addr(bufs[vi].q[0]), addr(bufs[vi].s[0]), fx.n, fx.d, vmr[vi])
        }
    }
    var best : array<double>
    best |> resize(nv)
    for (i in range(nv)) {
        best[i] = 1.0e30lf
    }
    var y : array<float>
    y |> resize(int(fx.ntok * fx.d))
    // correctness first — a tune run must never crown a broken variant
    for (vi in range(nv)) {
        run_tile(vs[vi]._1, fx, bufs[vi].q, bufs[vi].s, vmr[vi], y)
        var maxdiff = 0.0
        if (!close_to_ref(fx, y, maxdiff)) {
            print("{vs[vi]._0}: MISMATCH (maxdiff {maxdiff}) — aborting tune\n")
            return false
        }
    }
    for (_r in range(ROUNDS)) {   // interleaved best-of: variant order inside each round
        for (vi in range(nv)) {
            let t0 = ref_time_ticks()
            run_tile(vs[vi]._1, fx, bufs[vi].q, bufs[vi].s, vmr[vi], y)
            let us = double(get_time_usec(t0))
            if (us < best[vi]) {
                best[vi] = us
            }
        }
    }
    let macs = double(fx.n * fx.d * fx.ntok)
    var winner = 0
    for (vi in range(nv)) {
        if (best[vi] < best[winner]) {
            winner = vi
        }
        print("{vs[vi]._0} (mr={vmr[vi]}): {macs / best[vi] / 1000.0lf} GMAC/s (best of {ROUNDS})\n")
    }
    let ok = tune_manifest_set("q8q8_tile_gen", vs[winner]._0)
    print("winner: {vs[winner]._0} {ok ? "->" : "-> FAILED TO WRITE"} {tune_manifest_path()}\n")
    delete y
    delete bufs
    delete vmr
    delete best
    delete mrs
    delete vs
    delete fx
    return ok
}

[export]
def main {
    if (!jit_enabled()) {
        print("run with -jit — the generator only fires under the LLVM JIT\n")
        return
    }
    var found = false
    for (nm in kernel_backend_names()) {
        found ||= nm == "arm64-laneq-gen"
    }
    if (!found) {
        print("arm64-laneq-gen not registered (non-arm64 host?) — nothing to test\n")
        return
    }
    select_kernel_backend("arm64-laneq-gen")
    let mode = tune_mode()
    if (mode == "test") {
        print(test_mode() ? "GEN TUNE TEST OK\n" : "GEN TUNE TEST FAIL\n")
    } elif (mode == "tune") {
        print(tune_mode_run() ? "GEN TUNE RUN OK\n" : "GEN TUNE RUN FAIL\n")
    } else {
        print("set DAS_TUNE_MODE=test or =tune (compile-time env: it stamps the variant grid)\n")
    }
}
