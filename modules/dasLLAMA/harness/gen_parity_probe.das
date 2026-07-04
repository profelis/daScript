options gen2
options persistent_heap
options _jit_fast_math = true   // match gemm_1core_probe / the end-to-end config

// M2 bit-exact gate (gemm_generator_plan.md): the [llvm_code]-generated 4x4 tile
// (q8q8_tile_gen) vs the hand laneq semantics (dot_q8q8_laneq4) on the same repacked
// buffers. The generated tile mirrors the hand fold order exactly, so the comparison is EXACT
// float equality, not a tolerance. Shapes cover the paired-block loop (nb even), the odd-block
// tail (nb odd), and a production-ish slice. Run: daslang -jit gen_parity_probe.das
// (--jit-dump to eyeball the generated IR — look for the "sdot" calls + "wv0".."wv7" loads)

require dasllama/dasllama_math
require dasllama/dasllama_math_default
require dasllama/dasllama_math_aarch64_neon
require dasllama/dasllama_math_gen
require dasllama/dasllama_quant
require math

def test_shape(n, d, ntok : int64) : bool {
    let nb = n / 32l
    let ng = d / 4l
    var w : array<float>
    w |> resize(int(n * d))
    for (i in range64(n * d)) {
        w[i] = float(i % 17l) * 0.13 - 1.1
    }
    let qt <- quantize_q8_0(w, n * d)
    var q : array<int8>
    var s : array<float>
    q |> resize(int(n * d))
    s |> resize(int(d * nb))
    for (i in range64(n * d)) {
        q[i] = qt.q[i]
    }
    for (i in range64(d * nb)) {
        s[i] = qt.scales[i]
    }
    select_kernel_backend("arm64-laneq-gen")
    repack_q8q8_weight(q, s, 0l, n, d)

    // distinct per-token activations
    var xrow : array<float>
    xrow |> resize(int(n))
    var xq : array<int8>
    var xs : array<float>
    xq |> resize(int(ntok * n))
    xs |> resize(int(ntok * nb))
    for (tk in range64(ntok)) {
        for (i in range64(n)) {
            xrow[i] = float((i + tk * 7l) % 23l) * 0.07 - 0.8
        }
        quantize_q8_0_into(xrow, n, xq, xs, tk * n, tk * nb)
    }

    var ygen : array<float>
    var yref : array<float>
    ygen |> resize(int(ntok * d))
    yref |> resize(int(ntok * d))
    unsafe {
        let wp = addr(q[0])
        let sp = addr(s[0])
        let xqp = addr(xq[0])
        let xsp = addr(xs[0])
        var ygp = addr(ygen[0])
        var yrp = addr(yref[0])
        for (g in range64(ng)) {
            let wgp = wp + g * 4l * n
            let sgp = sp + g * 4l * nb
            var t0 = 0l
            while (t0 < ntok) {
                q8q8_tile_gen(ygp, wgp, sgp, xqp, xsp, n, d, g, t0)
                t0 += 4l
            }
            for (tk in range64(ntok)) {
                let f = dot_q8q8_laneq4(wgp, sgp, xqp + tk * n, xsp + tk * nb, n)
                yrp[tk * d + g * 4l + 0l] = f.x
                yrp[tk * d + g * 4l + 1l] = f.y
                yrp[tk * d + g * 4l + 2l] = f.z
                yrp[tk * d + g * 4l + 3l] = f.w
            }
        }
    }
    var exact = 0
    var md = 0.0
    for (i in range(length(ygen))) {
        if (ygen[i] == yref[i]) {
            exact++
        }
        md = max(md, abs(ygen[i] - yref[i]))
    }
    let ok = exact == length(ygen)
    print("n={n} d={d} ntok={ntok}: {exact}/{length(ygen)} exact, maxdiff {md} — {ok ? "OK" : "MISMATCH"}\n")
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
    var ok = test_shape(64l, 8l, 4l)      // nb=2: paired-block loop only
    ok = test_shape(96l, 8l, 4l) && ok    // nb=3: odd tail
    ok = test_shape(2048l, 64l, 8l) && ok // production-ish slice
    print(ok ? "GEN PARITY OK\n" : "GEN PARITY FAIL\n")
}
