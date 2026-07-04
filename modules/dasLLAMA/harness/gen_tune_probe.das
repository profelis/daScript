options gen2
options persistent_heap
options _jit_fast_math = true   // match gemm_1core_probe / the end-to-end config

// M3 grid gates (gemm_generator_plan.md): run with DAS_TUNE_MODE=test or =tune, -jit.
//   test: every [tune_perm] variant of q8q8_tile_gen (dasllama_math_gen) must be bit-exact vs
//         the hand laneq semantics on nb-even, nb-odd and a production-ish slice. Declining
//         perms (mr8_budget / mr2_layout / dot_vpdpbusd) run the reference body — also exact,
//         which pins the rejection rail.
//   tune: iso-bench every variant (interleaved best-of), print the table, and
//         tune_manifest_set the winner — a following normal run stamps it (the round-trip;
//         point DAS_TUNE_MANIFEST somewhere writable first).

require dasllama/dasllama_math
require dasllama/dasllama_math_default
require dasllama/dasllama_math_aarch64_neon
require dasllama/dasllama_math_gen
require dasllama/dasllama_quant
require llvm/daslib/llvm_tune
require math

let ROUNDS = 6

struct Fixture {
    n, d, ntok, nb, ng : int64
    q : array<int8>
    s : array<float>
    xq : array<int8>
    xs : array<float>
    yref : array<float>
}

def build_fixture(n, d, ntok : int64) : Fixture {
    var fx = Fixture(n = n, d = d, ntok = ntok, nb = n / 32l, ng = d / 4l)
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
    repack_q8q8_weight(fx.q, fx.s, 0l, n, d)

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

    // the oracle: hand laneq semantics, same fold order as the generated tile
    fx.yref |> resize(int(ntok * d))
    unsafe {
        let wp = addr(fx.q[0])
        let sp = addr(fx.s[0])
        let xqp = addr(fx.xq[0])
        let xsp = addr(fx.xs[0])
        var yrp = addr(fx.yref[0])
        for (g in range64(fx.ng)) {
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
    return <- fx
}

// one full tile sweep: every group x every 4-token block through `tile`
def run_tile(tile; fx : Fixture; var y : array<float>) {
    unsafe {
        let wp = addr(fx.q[0])
        let sp = addr(fx.s[0])
        let xqp = addr(fx.xq[0])
        let xsp = addr(fx.xs[0])
        var yp = addr(y[0])
        for (g in range64(fx.ng)) {
            let wgp = wp + g * 4l * fx.n
            let sgp = sp + g * 4l * fx.nb
            var t0 = 0l
            while (t0 < fx.ntok) {
                invoke(tile, yp, wgp, sgp, xqp, xsp, fx.n, fx.d, g, t0)
                t0 += 4l
            }
        }
    }
}

def exact_vs_ref(fx : Fixture; y : array<float>) : bool {
    for (i in range(length(y))) {
        if (y[i] != fx.yref[i]) return false
    }
    return true
}

def test_mode : bool {
    // nb=2 (even main loop), nb=3 (remainder path), production-ish slice
    var fxs <- [ <- build_fixture(64l, 8l, 4l), <- build_fixture(96l, 8l, 4l), <- build_fixture(2048l, 64l, 8l)]
    var vs <- q8q8_tile_gen_variants()
    var allok = true
    for (v in vs) {
        var ok = true
        for (fx in fxs) {
            var y : array<float>
            y |> resize(int(fx.ntok * fx.d))
            run_tile(v._1, fx, y)
            ok = ok && exact_vs_ref(fx, y)
            delete y
        }
        print("{v._0}: {ok ? "bit-exact" : "MISMATCH"}\n")
        allok = allok && ok
    }
    delete vs
    delete fxs
    return allok
}

def tune_mode_run : bool {
    var fx <- build_fixture(2048l, 512l, 64l)
    var vs <- q8q8_tile_gen_variants()
    let nv = length(vs)
    var best : array<double>
    best |> resize(nv)
    for (i in range(nv)) {
        best[i] = 1.0e30lf
    }
    var y : array<float>
    y |> resize(int(fx.ntok * fx.d))
    // correctness first — a tune run must never crown a broken variant
    for (v in vs) {
        run_tile(v._1, fx, y)
        if (!exact_vs_ref(fx, y)) {
            print("{v._0}: MISMATCH — aborting tune\n")
            return false
        }
    }
    for (_r in range(ROUNDS)) {   // interleaved best-of: variant order inside each round
        for (vi in range(nv)) {
            let t0 = ref_time_ticks()
            run_tile(vs[vi]._1, fx, y)
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
        print("{vs[vi]._0}: {macs / best[vi] / 1000.0lf} GMAC/s (best of {ROUNDS})\n")
    }
    let ok = tune_manifest_set("q8q8_tile_gen", vs[winner]._0)
    print("winner: {vs[winner]._0} {ok ? "->" : "-> FAILED TO WRITE"} {tune_manifest_path()}\n")
    delete y
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
