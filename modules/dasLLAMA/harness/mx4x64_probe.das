options gen2
options persistent_heap

// Correctness probe for the x64 MXFP4/groupn tier (dot32_mx4 + the groupn dispatch-fuse kernels).
// Gates, per the tier's design:
//   - dot32_mx4 / mx4_dequant32 intrinsics vs lane-wise references -> EQUAL (run with AND without
//     -jit: -jit proves the ymm PSHUFB path, plain proves the fallback body — same ref both ways)
//   - mm_mx4 / groupn_mx4 x64 vs portable                 -> tolerance (dot_mx4q8_x64's 4-way float
//     partitioning; block sums stay exact — was maxdiff-0 before the 4-accumulator row dot)
//   - groupn Q8 x64 vs a per-region mm loop, SAME backend -> maxdiff == 0.0 (the groupn contract)
//   - groupn Q8 x64 / grp4 vs portable                    -> tolerance (dot4x4/grp4 float order differs)
//   - mx4 BATCH: portable vs ntok x GEMV                  -> bit-exact (same row dot per token)
//   - mx4 batch x64 vs Q8 batch on an exact expansion,
//     SAME backend (row-major and grp4/repack forms)      -> bit-exact (the strip-dequant contract)
//   - mx4 batch grp4 vs ntok x row-major mx4 GEMV         -> tolerance (the GEMV's 4-acc partitioning)
// Run: daslang -jit modules/dasLLAMA/harness/mx4x64_probe.das   (and once without -jit)

require dasllama/dasllama_math
require dasllama/dasllama_math_default
require dasllama/dasllama_math_x64_avx
require dasllama/dasllama_quant
require llvm/daslib/x64_avx
require daslib/jobque_boost
require math

def fillw(var a : array<float>; cnt : int64; seed : float) {
    a |> resize(cnt)
    for (i in range64(cnt)) {
        a[i] = sin(float(i) * 0.37 + seed) * 0.9
    }
}

def maxdiff(a, b : array<float>) : float {
    var m = 0.0
    for (i in range(length(a))) {
        m = max(m, abs(a[i] - b[i]))
    }
    return m
}

// Relative maxdiff — the mx4 gates need it: the synthetic E8M0 bytes reach 2^25, so row values
// run ~1e8 and an absolute gate has no meaningful scale. Order-noise (4-acc partitioning) lands
// ~1e-6 relative; a real kernel bug is O(1) relative.
def rel_maxdiff(a, b : array<float>) : float {
    var scale = 1.0
    for (v in a) {
        scale = max(scale, abs(v))
    }
    var m = 0.0
    for (i in range(length(a))) {
        m = max(m, abs(a[i] - b[i]))
    }
    return m / scale
}

// Deterministic synthetic MXFP4 planes: nibble bytes roll through all 256 values; E8M0 scale
// bytes stay in a sane range (plus the denormal-path extremes 0/1/2) so block products never inf.
def fill_mx4(var wn : array<uint8>; var we : array<uint8>; n, d : int64; seed : int) {
    wn |> resize(d * (n / 2l))
    we |> resize(d * (n / 32l))
    for (i in range64(d * (n / 2l))) {
        wn[i] = uint8((int(i) * 131 + seed * 7 + 13) & 255)
    }
    for (i in range64(d * (n / 32l))) {
        let r = (int(i) * 37 + seed) % 44
        we[i] = uint8(r < 3 ? r : 110 + r)   // 0,1,2 (denormal path) then 113..151
    }
}

// Lane-wise reference for one dot32_mx4 call — the documented contract, written independently.
def ref_dot32_mx4(acc : int4; lut : int8[16]; wn : array<uint8>; wb : int64; xq : array<int8>; xb : int64) : int4 {
    var s = int4(0, 0, 0, 0)
    for (j in range(4)) {
        var t = 0
        for (e in range(4)) {
            let k = int64(j * 4 + e)
            let b = int(wn[wb + k])
            t += int(lut[b & 15]) * int(xq[xb + k])
            t += int(lut[b >> 4]) * int(xq[xb + 16l + k])
        }
        if (j == 0) { s.x = t } elif (j == 1) { s.y = t } elif (j == 2) { s.z = t } else { s.w = t }
    }
    return acc + s
}

def check_intrinsic() {
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    var wn : array<uint8>
    var xq : array<int8>
    wn |> resize(16l * 64l)
    xq |> resize(32l * 64l)
    // roll every nibble byte value through; x sweeps the Q8 range [-127, 127] (the sign trick's
    // exactness precondition — the quantizer never emits -128, and neither may this probe)
    for (i in range64(16l * 64l)) {
        wn[i] = uint8(int(i) & 255)
    }
    for (i in range64(32l * 64l)) {
        let v = (int(i) * 89 + 41) % 255 - 127
        xq[i] = int8(v)
    }
    // extreme block: x pinned to ±127 alternating (largest legal Q8 magnitudes)
    for (i in range64(32l)) {
        xq[i] = int8((i & 1l) == 0l ? 127 : -127)
    }
    unsafe {
        var bad = 0
        for (bi in range64(64l)) {
            let hw = dot32_mx4(int4(1, -2, 3, -4), addr(lut[0]), addr(wn[bi * 16l]), addr(xq[bi * 32l]))
            let rf = ref_dot32_mx4(int4(1, -2, 3, -4), lut, wn, bi * 16l, xq, bi * 32l)
            if (hw.x != rf.x || hw.y != rf.y || hw.z != rf.z || hw.w != rf.w) {
                print("dot32_mx4 MISMATCH at block {bi}: hw={hw} ref={rf}\n")
                bad++
            }
        }
        if (bad != 0) {
            panic("dot32_mx4 intrinsic FAILED")
        }
    }
    print("dot32_mx4 intrinsic: 64/64 blocks equal ({jit_enabled() ? "hardware path" : "fallback body"})\n")
    // mx4_dequant32: the stored bytes must equal the independent scalar LUT expansion, per block
    var dq : array<int8>
    dq |> resize(32l * 64l)
    unsafe {
        var bad2 = 0
        for (bi in range64(64l)) {
            mx4_dequant32(addr(lut[0]), addr(wn[bi * 16l]), addr(dq[bi * 32l]))
            for (j in range64(16l)) {
                let b = int(wn[bi * 16l + j])
                if (dq[bi * 32l + j] != lut[b & 15] || dq[bi * 32l + 16l + j] != lut[b >> 4]) {
                    print("mx4_dequant32 MISMATCH at block {bi} byte {j}\n")
                    bad2++
                }
            }
        }
        if (bad2 != 0) {
            panic("mx4_dequant32 intrinsic FAILED")
        }
    }
    print("mx4_dequant32 intrinsic: 64/64 blocks equal ({jit_enabled() ? "hardware path" : "fallback body"})\n")
    delete dq
    delete wn
    delete xq
}

def quant_x(n, ntok : int64; var xq : array<int8>; var xs : array<float>; seed : float) {
    let nb = n / 32l
    var x : array<float>
    fillw(x, n * ntok, seed)
    xq |> resize(ntok * n)
    xs |> resize(ntok * nb)
    for (tk in range64(ntok)) {
        quantize_q8_0_into(x, n, xq, xs, tk * n, tk * nb)
    }
    delete x
}

def check_mm_mx4(n, d : int64) {
    var wn : array<uint8>
    var we : array<uint8>
    fill_mx4(wn, we, n, d, 3)
    var xq : array<int8>
    var xs : array<float>
    quant_x(n, 1l, xq, xs, 4.567)
    var y_ref : array<float>
    var y_x64 : array<float>
    y_ref |> resize(d)
    y_x64 |> resize(d)
    select_kernel_backend("portable")
    matmul_mx4q8(y_ref, wn, we, xq, xs, n, d)
    select_kernel_backend("x64-avx2")
    matmul_mx4q8(y_x64, wn, we, xq, xs, n, d)
    let md = rel_maxdiff(y_ref, y_x64)
    print("mm_mx4 n={n} d={d}: rel maxdiff={md}  {md < 1.0e-5 ? "OK" : "FAIL <<<<"}\n")
    if (md >= 1.0e-5) {
        panic("mm_mx4 probe FAILED (rel tolerance 1e-5 — the x64 row dot is 4-acc partitioned)")
    }
    delete wn
    delete we
    delete xq
    delete xs
    delete y_ref
    delete y_x64
}

// Region-list shapes: R regions of [d x n] contiguous in one blob; gates/ups share activation 0,
// downs bring per-region activations — both offset patterns exercised, with and without bias.
def check_groupn(n, d, nregions : int64) {
    let nb = n / 32l
    let rows = nregions * d

    // Q8 blob with nregions regions
    var w : array<float>
    fillw(w, n * rows, 0.123)
    let qt <- quantize_q8_0(w, n * rows)
    var q : array<int8>
    var s : array<float>
    q |> resize(n * rows)
    s |> resize(rows * nb)
    for (i in range64(n * rows)) {
        q[i] = qt.q[i]
    }
    for (i in range64(rows * nb)) {
        s[i] = qt.scales[i]
    }

    // mx4 planes with nregions regions
    var wn : array<uint8>
    var we : array<uint8>
    fill_mx4(wn, we, n, rows, 11)

    // activations: one per region (downs shape) — region r uses token r's row
    var xq : array<int8>
    var xs : array<float>
    quant_x(n, nregions, xq, xs, 2.71)

    // offsets: shared-x (all regions read activation 0) and per-region-x
    var offs_shared : array<int64>
    var offs_per : array<int64>
    var boffs : array<int64>
    var bias : array<float>
    bias |> resize(rows)
    for (i in range64(rows)) {
        bias[i] = sin(float(i) * 0.11) * 2.0
    }
    offs_shared |> reserve(nregions * 2l)
    offs_per |> reserve(nregions * 2l)
    boffs |> reserve(nregions)
    for (r in range64(nregions)) {
        offs_shared |> push(r * d * n)   // weight-element offset of region r
        offs_shared |> push(0l)          // all share activation 0
        offs_per |> push(r * d * n)
        offs_per |> push(r * n)          // region r reads token r
        boffs |> push(r * d)
    }

    var y_a : array<float>
    var y_b : array<float>
    y_a |> resize(rows)
    y_b |> resize(rows)

    // --- groupn Q8, x64 vs per-region mm loop on the SAME backend (the contract: bit-exact) ---
    select_kernel_backend("x64-avx2")
    matmul_q8q8_groupn(y_a, q, s, offs_per, nregions, xq, xs, n, d)
    for (r in range64(nregions)) {
        var yr : array<float>
        yr |> resize(d)
        var qr : array<int8>
        var sr : array<float>
        qr |> resize(n * d)
        sr |> resize(d * nb)
        for (i in range64(n * d)) {
            qr[i] = q[r * d * n + i]
        }
        for (i in range64(d * nb)) {
            sr[i] = s[r * d * nb + i]
        }
        var xq1 : array<int8>
        var xs1 : array<float>
        xq1 |> resize(n)
        xs1 |> resize(nb)
        for (i in range64(n)) {
            xq1[i] = xq[r * n + i]
        }
        for (i in range64(nb)) {
            xs1[i] = xs[r * nb + i]
        }
        matmul_q8q8(yr, qr, sr, xq1, xs1, n, d)
        for (i in range64(d)) {
            if (y_a[r * d + i] != yr[i]) {
                panic("groupn Q8 vs per-region mm mismatch at region {r} row {i} (must be bit-exact)")
            }
        }
        delete yr
        delete qr
        delete sr
        delete xq1
        delete xs1
    }

    // --- groupn Q8, x64 vs portable (tolerance: dot4x4 float order differs) ---
    select_kernel_backend("portable")
    matmul_q8q8_groupn(y_a, q, s, offs_shared, nregions, xq, xs, bias, boffs, n, d)
    select_kernel_backend("x64-avx2")
    matmul_q8q8_groupn(y_b, q, s, offs_shared, nregions, xq, xs, bias, boffs, n, d)
    let md_q8 = maxdiff(y_a, y_b)

    // --- groupn mx4, x64 vs portable (rel tolerance: 4-acc row dot) — both offset patterns + bias ---
    select_kernel_backend("portable")
    matmul_mx4q8_groupn(y_a, wn, we, offs_shared, nregions, xq, xs, bias, boffs, n, d)
    select_kernel_backend("x64-avx2")
    matmul_mx4q8_groupn(y_b, wn, we, offs_shared, nregions, xq, xs, bias, boffs, n, d)
    let md_mx4s = rel_maxdiff(y_a, y_b)
    select_kernel_backend("portable")
    matmul_mx4q8_groupn(y_a, wn, we, offs_per, nregions, xq, xs, n, d)
    select_kernel_backend("x64-avx2")
    matmul_mx4q8_groupn(y_b, wn, we, offs_per, nregions, xq, xs, n, d)
    let md_mx4p = rel_maxdiff(y_a, y_b)

    // --- groupn Q8 grp4 (repack backend): repack each region in a copy, tolerance vs portable ---
    var q2 : array<int8>
    var s2 : array<float>
    q2 |> resize(n * rows)
    s2 |> resize(rows * nb)
    for (i in range64(n * rows)) {
        q2[i] = q[i]
    }
    for (i in range64(rows * nb)) {
        s2[i] = s[i]
    }
    select_kernel_backend("x64-avx2-repack")
    for (r in range64(nregions)) {
        repack_q8q8_weight(q2, s2, r * d * n, n, d)
    }
    matmul_q8q8_groupn(y_b, q2, s2, offs_shared, nregions, xq, xs, bias, boffs, n, d)
    select_kernel_backend("portable")
    matmul_q8q8_groupn(y_a, q, s, offs_shared, nregions, xq, xs, bias, boffs, n, d)
    let md_grp4 = maxdiff(y_a, y_b)

    let ok = md_q8 < 1.0e-3 && md_mx4s < 1.0e-5 && md_mx4p < 1.0e-5 && md_grp4 < 1.0e-3
    print("groupn n={n} d={d} R={nregions}: q8={md_q8} mx4rel(shared)={md_mx4s} mx4rel(per)={md_mx4p} grp4={md_grp4}  {ok ? "OK" : "FAIL <<<<"}\n")
    if (!ok) {
        panic("groupn probe FAILED")
    }

    delete w
    delete q
    delete s
    delete wn
    delete we
    delete xq
    delete xs
    delete offs_shared
    delete offs_per
    delete boffs
    delete bias
    delete y_a
    delete y_b
    delete q2
    delete s2
}

// Exact-compare two [ntok x d] result images; panic with the first mismatch position.
def expect_equal(a, b : array<float>; d : int64; what : string) {
    for (i in range(length(a))) {
        if (a[i] != b[i]) {
            panic("{what}: mismatch at token {int64(i) / d} row {int64(i) % d}: {a[i]} != {b[i]} (must be bit-exact)")
        }
    }
}

// The mx4 batch tier. The x64 kernels dequant weight strips into L1 scratch and run the backend's
// own Q8 dots, so each is BIT-IDENTICAL to Q8-batch-on-an-exact-expansion on the same backend —
// that identity is the gate (plus portable batch == ntok x portable GEMV bit-exact, and grp4 batch
// vs ntok x row-major mx4 GEMV within tolerance — the GEMV's 4-acc float partitioning).
def check_mx4_batch(n, d, ntok : int64) {
    let nb = n / 32l
    var wn : array<uint8>
    var we : array<uint8>
    fill_mx4(wn, we, n, d, 17)
    var xq : array<int8>
    var xs : array<float>
    quant_x(n, ntok, xq, xs, 1.618)

    // exact Q8 expansion of the whole region (the documented contract, written independently)
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    var q : array<int8>
    var s : array<float>
    q |> resize(d * n)
    s |> resize(d * nb)
    for (bi in range64(d * nb)) {
        for (j in range64(16l)) {
            let b = int(wn[bi * 16l + j])
            q[bi * 32l + j] = lut[b & 15]
            q[bi * 32l + 16l + j] = lut[b >> 4]
        }
        s[bi] = e8m0_half(uint(we[bi]))
    }

    var y_a : array<float>
    var y_b : array<float>
    y_a |> resize(ntok * d)
    y_b |> resize(ntok * d)

    // --- portable batch vs ntok x portable GEMV (bit-exact: same row dot per token) ---
    select_kernel_backend("portable")
    matmul_mx4q8_batch(y_a, wn, we, xq, xs, n, d, ntok)
    var yr : array<float>
    var xq1 : array<int8>
    var xs1 : array<float>
    yr |> resize(d)
    xq1 |> resize(n)
    xs1 |> resize(nb)
    for (tk in range64(ntok)) {
        for (i in range64(n)) {
            xq1[i] = xq[tk * n + i]
        }
        for (i in range64(nb)) {
            xs1[i] = xs[tk * nb + i]
        }
        matmul_mx4q8(yr, wn, we, xq1, xs1, n, d)
        for (i in range64(d)) {
            if (y_a[tk * d + i] != yr[i]) {
                panic("mx4 batch portable vs GEMV: mismatch at token {tk} row {i} (must be bit-exact)")
            }
        }
    }

    // the x64 gates need the x64 backends registered (JIT on an AVX2 box) — plain mode skips
    select_kernel_backend("x64-avx2")
    if (active_kernel_backend() == "x64-avx2") {
        // --- row-major: native mx4 batch vs Q8 batch on the expansion, same backend ---
        matmul_mx4q8_batch(y_a, wn, we, xq, xs, n, d, ntok)
        matmul_q8q8_batch(y_b, q, s, xq, xs, n, d, ntok)
        expect_equal(y_a, y_b, d, "mx4 batch x64-avx2 vs expansion")

        // --- repack: native grp4 mx4 batch vs expand + repack + grp4 Q8 batch ---
        var q2 : array<int8>
        var s2 : array<float>
        q2 |> resize(n * d)
        s2 |> resize(d * nb)
        for (i in range64(n * d)) {
            q2[i] = q[i]
        }
        for (i in range64(d * nb)) {
            s2[i] = s[i]
        }
        select_kernel_backend("x64-avx2-repack")
        repack_q8q8_weight(q2, s2, 0l, n, d)
        matmul_mx4q8_batch(y_a, wn, we, xq, xs, n, d, ntok)
        matmul_q8q8_batch(y_b, q2, s2, xq, xs, n, d, ntok)
        expect_equal(y_a, y_b, d, "mx4 batch grp4 vs expansion+repack")

        // --- grp4 batch vs ntok x row-major mx4 GEMV (rel tolerance: the GEMV is 4-acc partitioned) ---
        var md_gemv = 0.0
        var sc_gemv = 1.0
        for (tk in range64(ntok)) {
            for (i in range64(n)) {
                xq1[i] = xq[tk * n + i]
            }
            for (i in range64(nb)) {
                xs1[i] = xs[tk * nb + i]
            }
            matmul_mx4q8(yr, wn, we, xq1, xs1, n, d)
            for (i in range64(d)) {
                md_gemv = max(md_gemv, abs(y_a[tk * d + i] - yr[i]))
                sc_gemv = max(sc_gemv, abs(yr[i]))
            }
        }
        if (md_gemv / sc_gemv >= 1.0e-5) {
            panic("mx4 batch grp4 vs mx4 GEMV: rel maxdiff {md_gemv / sc_gemv} exceeds tolerance 1e-5")
        }
        delete q2
        delete s2
        print("mx4 batch n={n} d={d} ntok={ntok}: portable/x64/grp4 all bit-exact  OK\n")
    } else {
        print("mx4 batch n={n} d={d} ntok={ntok}: portable bit-exact OK (x64 backends not registered — plain mode)\n")
    }

    delete wn
    delete we
    delete xq
    delete xs
    delete q
    delete s
    delete y_a
    delete y_b
    delete yr
    delete xq1
    delete xs1
}

// The region-list batch (mul_mat_id shape): regions with VARYING token counts (including a zero-
// count region the caller normally skips) over one bucket-ordered row image, biased and unbiased,
// against a per-region loop of the SAME backend's mx4 batch kernel (+ manual bias add-after) —
// bit-exact on every backend.
def check_mx4_batch_groupn(n, d, nregions : int64) {
    let nb = n / 32l
    var wn : array<uint8>
    var we : array<uint8>
    fill_mx4(wn, we, n, nregions * d, 23)   // nregions [d x n] regions stacked in one plane pair
    var cnts : array<int64>
    cnts |> reserve(nregions)
    var total = 0l
    for (r in range64(nregions)) {
        let cn = (r % 4l) == 3l ? 0l : 1l + ((r * 5l + 1l) % 7l)
        cnts |> push(cn)
        total += cn
    }
    var xq : array<int8>
    var xs : array<float>
    quant_x(n, total, xq, xs, 0.77)
    var offs : array<int64>
    var boffs : array<int64>
    var row0s : array<int64>
    offs |> reserve(nregions * 3l)
    boffs |> reserve(nregions)
    row0s |> reserve(nregions)
    var row0 = 0l
    for (r in range64(nregions)) {
        offs |> push(r * d * n)
        offs |> push(row0)
        offs |> push(cnts[r])
        boffs |> push(r * d)
        row0s |> push(row0)
        row0 += cnts[r]
    }
    var bias : array<float>
    bias |> resize(nregions * d)
    for (i in range64(nregions * d)) {
        bias[i] = sin(float(i) * 0.17) * 1.5
    }
    var y : array<float>
    y |> resize(total * d)

    var backends <- [""]   // "" = whatever is active (portable off-JIT)
    backends[0] = "portable"
    if (jit_enabled()) {
        backends |> push("x64-avx2")
        backends |> push("x64-avx2-repack")
    }
    for (bk in backends) {
        select_kernel_backend(bk)
        if (active_kernel_backend() != bk) {
            print("mx4 batch groupn n={n} d={d} R={nregions}: SKIP {bk} (not registered)\n")
            continue
        }
        for (biased in [false, true]) {
            if (biased) {
                matmul_mx4q8_batch_groupn(y, wn, we, offs, nregions, xq, xs, bias, boffs, n, d)
            } else {
                matmul_mx4q8_batch_groupn(y, wn, we, offs, nregions, xq, xs, n, d)
            }
            // reference: this backend's own mx4 batch kernel per region (+ manual bias add-after)
            for (r in range64(nregions)) {
                let cnt = cnts[r]
                if (cnt == 0l) {
                    continue
                }
                let r0 = row0s[r]
                var wr : array<uint8>
                var er : array<uint8>
                wr |> resize(d * (n / 2l))
                er |> resize(d * nb)
                for (i in range64(d * (n / 2l))) {
                    wr[i] = wn[r * d * (n / 2l) + i]
                }
                for (i in range64(d * nb)) {
                    er[i] = we[r * d * nb + i]
                }
                var xqr : array<int8>
                var xsr : array<float>
                xqr |> resize(cnt * n)
                xsr |> resize(cnt * nb)
                for (i in range64(cnt * n)) {
                    xqr[i] = xq[r0 * n + i]
                }
                for (i in range64(cnt * nb)) {
                    xsr[i] = xs[r0 * nb + i]
                }
                var yr : array<float>
                yr |> resize(cnt * d)
                matmul_mx4q8_batch(yr, wr, er, xqr, xsr, n, d, cnt)
                for (tk in range64(cnt)) {
                    for (i in range64(d)) {
                        let want = biased ? yr[tk * d + i] + bias[r * d + i] : yr[tk * d + i]
                        if (y[(r0 + tk) * d + i] != want) {
                            panic("mx4 batch groupn [{bk} biased={biased}]: mismatch region {r} token {tk} row {i} (must be bit-exact)")
                        }
                    }
                }
                delete wr
                delete er
                delete xqr
                delete xsr
                delete yr
            }
        }
    }
    print("mx4 batch groupn n={n} d={d} R={nregions}: {jit_enabled() ? "portable/x64/grp4" : "portable"} biased+unbiased bit-exact  OK\n")
    delete wn
    delete we
    delete cnts
    delete xq
    delete xs
    delete offs
    delete boffs
    delete row0s
    delete bias
    delete y
    delete backends
}

[export]
def main {
    if (!jit_enabled()) {
        print("NOTE: no -jit — probing the FALLBACK bodies (valid; run again with -jit for the ymm path)\n")
    }
    with_job_que() {
        setup_dasllama_jobque_()
        check_intrinsic()
        check_mm_mx4(32l, 1l)         // single block, single row
        check_mm_mx4(64l, 7l)         // 2 blocks, odd rows
        check_mm_mx4(2880l, 32l)      // gpt-oss expert width
        check_mm_mx4(2880l, 2880l)    // gpt-oss expert shape, threaded path engaged
        check_groupn(64l, 8l, 4l)     // tiny, 4 regions (top-k shape)
        check_groupn(96l, 10l, 3l)    // odd rows (grp4 row tails), 3 regions
        check_groupn(2880l, 96l, 4l)  // real-ish width, threaded groupn
        check_mx4_batch(64l, 8l, 4l)      // tiny (2 blocks, 2 groups, token pairs)
        check_mx4_batch(96l, 10l, 3l)     // grp4 row tails (d % 4) + odd-token tail
        check_mx4_batch(2880l, 128l, 1l)  // single token (all-tail path), real width
        check_mx4_batch(2880l, 2880l, 33l)   // gpt-oss expert shape, threaded + TB + chunked scratch
        check_mx4_batch_groupn(96l, 10l, 5l)    // tails + varying counts + a zero-count region
        check_mx4_batch_groupn(2880l, 96l, 6l)  // real width, several regions
        check_mx4_batch_groupn(2880l, 720l, 4l) // threaded chunked path (items span regions)
        print("mx4x64 probe: ALL OK\n")
    }
}
