options gen2
options persistent_heap

// Correctness probe for the AVX kernel matrix (VNNI / AVX-512 tiers — see the section comment in
// dasllama_math_x64_avx.das). Gates, per the tiers' design:
//   - every matrix intrinsic vs its established twin -> EXACT (dot32_vnni == dot32 and
//     dot64_acc16_vnni == dot64_acc16 are integer/lane identities; dot64_acc16 == two dot32_acc8
//     calls and mx4_dequant64 == two mx4_dequant32 calls are the documented contracts). Run with
//     AND without -jit; on a box WITH the tiers -jit proves the hardware sequences against the
//     ymm/scalar references, elsewhere it proves the delegating fallbacks.
//   - x64-vnni256 / -acc8 / -repack backends vs their donors (x64-avx2 / -acc8 / -repack)
//     -> BIT-EXACT on every facade (the VNNI dot is an integer identity; kernels differ only in
//     the dot call, so any mismatch is matrix-kernel plumbing)
//   - x64-avx512vnni vs x64-avx512bw -> BIT-EXACT (same z16 shape, same identity)
//   - x64-avx512bw vs portable -> rel tolerance 1e-5 (the z16 float[16] partitioning, the
//     acc8/ps gate class)
// Backends register only under DASLLAMA_AVX_MATRIX=1 && cpu_supports(tier); on a box without the
// tiers add DASLLAMA_AVX_MATRIX_FORCE=1 — forced backends run the delegating fallbacks, which is
// exactly what the plumbing gates need. Without registration the backend section SKIPs.
// Run: DASLLAMA_AVX_MATRIX=1 DASLLAMA_AVX_MATRIX_FORCE=1 daslang [-jit] modules/dasLLAMA/harness/avx_matrix_probe.das

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

// Deterministic operands: w rolls all 256 byte values (including -128 — legal for weights), x
// sweeps the Q8 range [-127, 127] (the sign trick's exactness precondition), block 0 pinned to
// the extreme +-127 alternation.
def fill_wx(var w : array<int8>; var x : array<int8>; cnt : int64) {
    w |> resize(cnt)
    x |> resize(cnt)
    for (i in range64(cnt)) {
        w[i] = int8(int(i) * 73 + 5)
        x[i] = int8((int(i) * 89 + 41) % 255 - 127)
    }
    for (i in range64(32l)) {
        x[i] = int8((i & 1l) == 0l ? 127 : -127)
    }
}

def check_intrinsics() {
    let mode = jit_enabled() ? "jit" : "fallback"
    var w : array<int8>
    var x : array<int8>
    fill_wx(w, x, 64l * 64l)
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    unsafe {
        // dot32_vnni == dot32, dot32_mx4_vnni == dot32_mx4 (integer identities)
        for (bi in range64(64l)) {
            let a = dot32(int4(1, -2, 3, -4), addr(w[bi * 32l]), addr(x[bi * 32l]))
            let b = dot32_vnni(int4(1, -2, 3, -4), addr(w[bi * 32l]), addr(x[bi * 32l]))
            if (a.x != b.x || a.y != b.y || a.z != b.z || a.w != b.w) {
                panic("dot32_vnni != dot32 at block {bi}: {b} vs {a}")
            }
            let ma = dot32_mx4(int4(2, 0, -1, 5), addr(lut[0]), reinterpret<uint8 const?>(addr(w[bi * 16l])), addr(x[bi * 32l]))
            let mb = dot32_mx4_vnni(int4(2, 0, -1, 5), addr(lut[0]), reinterpret<uint8 const?>(addr(w[bi * 16l])), addr(x[bi * 32l]))
            if (ma.x != mb.x || ma.y != mb.y || ma.z != mb.z || ma.w != mb.w) {
                panic("dot32_mx4_vnni != dot32_mx4 at block {bi}: {mb} vs {ma}")
            }
        }
        print("dot32_vnni / dot32_mx4_vnni: 64/64 blocks equal ({mode})\n")
        // dot32_acc8_vnni == dot32_acc8 (same float tail on identical quads)
        var accA : float[8]
        var accB : float[8]
        for (bi in range64(64l)) {
            let s = 0.75 + float(bi) * 0.03
            dot32_acc8(addr(accA[0]), addr(w[bi * 32l]), addr(x[bi * 32l]), s)
            dot32_acc8_vnni(addr(accB[0]), addr(w[bi * 32l]), addr(x[bi * 32l]), s)
        }
        for (j in range(8)) {
            if (accA[j] != accB[j]) {
                panic("dot32_acc8_vnni != dot32_acc8 at lane {j}: {accB[j]} vs {accA[j]}")
            }
        }
        print("dot32_acc8_vnni: 8/8 lanes equal after 64 blocks ({mode})\n")
        // dot64_acc16 == two dot32_acc8 calls (the documented contract); _vnni == dot64_acc16
        var z0 : float[16]
        var z1 : float[16]
        var y8 : float[16]
        for (bi in range64(32l)) {
            let bb = bi * 64l
            let s0 = 0.5 + float(bi) * 0.02
            let s1 = -0.25 + float(bi) * 0.01
            dot64_acc16(addr(z0[0]), addr(w[bb]), addr(x[bb]), s0, s1)
            dot64_acc16_vnni(addr(z1[0]), addr(w[bb]), addr(x[bb]), s0, s1)
            dot32_acc8(addr(y8[0]), addr(w[bb]), addr(x[bb]), s0)
            dot32_acc8(addr(y8[0]) + 8, addr(w[bb]) + 32, addr(x[bb]) + 32, s1)
        }
        for (j in range(16)) {
            if (z0[j] != y8[j]) {
                panic("dot64_acc16 != 2x dot32_acc8 at lane {j}: {z0[j]} vs {y8[j]}")
            }
            if (z1[j] != z0[j]) {
                panic("dot64_acc16_vnni != dot64_acc16 at lane {j}: {z1[j]} vs {z0[j]}")
            }
        }
        print("dot64_acc16 / dot64_acc16_vnni: 16/16 lanes equal after 32 block pairs ({mode})\n")
        // mx4_dequant64 == two mx4_dequant32 calls, byte for byte
        var dqA : array<int8>
        var dqB : array<int8>
        dqA |> resize(64l * 32l)
        dqB |> resize(64l * 32l)
        var bi2 = 0l
        while (bi2 + 2l <= 64l) {
            mx4_dequant64(addr(lut[0]), reinterpret<uint8 const?>(addr(w[bi2 * 16l])), addr(dqA[bi2 * 32l]))
            mx4_dequant32(addr(lut[0]), reinterpret<uint8 const?>(addr(w[bi2 * 16l])), addr(dqB[bi2 * 32l]))
            mx4_dequant32(addr(lut[0]), reinterpret<uint8 const?>(addr(w[bi2 * 16l + 16l])), addr(dqB[bi2 * 32l + 32l]))
            bi2 += 2l
        }
        for (i in range64(64l * 32l)) {
            if (dqA[i] != dqB[i]) {
                panic("mx4_dequant64 != 2x mx4_dequant32 at byte {i}: {int(dqA[i])} vs {int(dqB[i])}")
            }
        }
        print("mx4_dequant64: 64 blocks byte-equal ({mode})\n")
        delete dqA
        delete dqB
    }
    delete w
    delete x
}

// Deterministic synthetic MXFP4 planes (the mx4x64_probe pattern: nibbles roll all values, E8M0
// stays sane + the denormal-path extremes).
def fill_mx4(var wn : array<uint8>; var we : array<uint8>; n, d : int64; seed : int) {
    wn |> resize(d * (n / 2l))
    we |> resize(d * (n / 32l))
    for (i in range64(d * (n / 2l))) {
        wn[i] = uint8((int(i) * 131 + seed * 7 + 13) & 255)
    }
    for (i in range64(d * (n / 32l))) {
        let r = (int(i) * 37 + seed) % 44
        we[i] = uint8(r < 3 ? r : 110 + r)
    }
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

struct ProbeData {
    q : array<int8>
    s : array<float>
    wn : array<uint8>
    we : array<uint8>
    xq : array<int8>
    xs : array<float>
    offs : array<int64>       // groupn pairs [woff, xoff] — per-region activations
    boffs : array<int64>
    bias : array<float>
    toffs : array<int64>      // batch-groupn triples [woff, row0, cnt] (incl. a zero-count region)
    total : int64             // batch-groupn token rows
    nregions : int64
}

def make_probe_data(n, d, ntok, nregions : int64) : ProbeData {
    let nb = n / 32l
    let rows = nregions * d
    var pd : ProbeData
    var w : array<float>
    fillw(w, n * rows, 0.123)
    let qt <- quantize_q8_0(w, n * rows)
    pd.q |> resize(n * rows)
    pd.s |> resize(rows * nb)
    for (i in range64(n * rows)) {
        pd.q[i] = qt.q[i]
    }
    for (i in range64(rows * nb)) {
        pd.s[i] = qt.scales[i]
    }
    delete w
    fill_mx4(pd.wn, pd.we, n, rows, 29)
    pd.nregions = nregions
    pd.bias |> resize(rows)
    for (i in range64(rows)) {
        pd.bias[i] = sin(float(i) * 0.11) * 2.0
    }
    pd.offs |> reserve(nregions * 2l)
    pd.boffs |> reserve(nregions)
    pd.toffs |> reserve(nregions * 3l)
    var row0 = 0l
    for (r in range64(nregions)) {
        pd.offs |> push(r * d * n)   // nolint:STYLE012 — appending per region across iterations
        pd.offs |> push(r * n)
        pd.boffs |> push(r * d)
        let cn = (r % 4l) == 3l ? 0l : 1l + ((r * 5l + 1l) % min(7l, ntok))   // incl. a zero-count region
        pd.toffs |> push(r * d * n)   // nolint:STYLE012 — appending per region across iterations
        pd.toffs |> push(row0)
        pd.toffs |> push(cn)
        row0 += cn
    }
    pd.total = row0
    // token pool covers the widest consumer: batch (ntok), groupn per-region (nregions), batch-groupn (total)
    quant_x(n, max(ntok, max(nregions, pd.total)), pd.xq, pd.xs, 2.71)
    return <- pd
}

def check_pair(y_a, y_b : array<float>; cnt : int64; exact : bool; what : string) {
    // compare only the first cnt entries (buffers are shared across differently-sized facades)
    if (exact) {
        for (i in range64(cnt)) {
            if (y_a[i] != y_b[i]) {
                panic("{what}: mismatch at index {i}: {y_a[i]} != {y_b[i]} (must be bit-exact)")
            }
        }
    } else {
        var scale = 1.0
        var md = 0.0
        for (i in range64(cnt)) {
            scale = max(scale, abs(y_b[i]))
            md = max(md, abs(y_a[i] - y_b[i]))
        }
        if (md / scale >= 1.0e-5) {
            panic("{what}: rel maxdiff {md / scale} exceeds tolerance 1e-5")
        }
    }
}

// One matrix backend against its donor across every facade the pair shares. exact=true gates
// bit-identity (the VNNI tiers); exact=false gates rel tolerance 1e-5 (the z16-vs-portable class).
// repacked=true runs on repacked weight copies (both backends read the same grp4 interleave).
// mx4_batch_exact=false relaxes ONLY the mx4 batch slots to tolerance — the avx512vnni backend's
// z-strip kernels dot with the z16 float[16] shape while its donor's strips dot with the int-flush
// dot4x4 shape; the bit-exact gate for those slots is the expansion contract (check_z16vnni_expansion).
def check_backend(name, donor : string; exact, repacked, mx4_batch_exact : bool; n, d, ntok : int64; pd : ProbeData) {
    let nb = n / 32l
    select_kernel_backend(name)
    if (active_kernel_backend() != name) {
        print("backend {name}: SKIP (not registered — need DASLLAMA_AVX_MATRIX=1 [+ _FORCE=1] and -jit)\n")
        return
    }
    let rows = pd.nregions * d
    var q2 : array<int8>
    var s2 : array<float>
    q2 |> resize(n * rows)
    s2 |> resize(rows * nb)
    for (i in range64(n * rows)) {
        q2[i] = pd.q[i]
    }
    for (i in range64(rows * nb)) {
        s2[i] = pd.s[i]
    }
    if (repacked) {
        for (r in range64(pd.nregions)) {
            repack_q8q8_weight(q2, s2, r * d * n, n, d)
        }
    }
    var y_a : array<float>
    var y_b : array<float>
    y_a |> resize(max(rows, max(ntok, pd.total) * d))
    y_b |> resize(max(rows, max(ntok, pd.total) * d))

    select_kernel_backend(name)
    matmul_q8q8(y_a, q2, s2, pd.xq, pd.xs, n, d)                       // mm (region 0)
    select_kernel_backend(donor)
    matmul_q8q8(y_b, q2, s2, pd.xq, pd.xs, n, d)
    check_pair(y_a, y_b, d, exact, "{name} mm")

    select_kernel_backend(name)
    matmul_q8q8_batch(y_a, q2, s2, pd.xq, pd.xs, n, d, ntok)           // batch (region 0)
    select_kernel_backend(donor)
    matmul_q8q8_batch(y_b, q2, s2, pd.xq, pd.xs, n, d, ntok)
    check_pair(y_a, y_b, ntok * d, exact, "{name} batch")

    select_kernel_backend(name)
    matmul_q8q8_groupn(y_a, q2, s2, pd.offs, pd.nregions, pd.xq, pd.xs, pd.bias, pd.boffs, n, d)
    select_kernel_backend(donor)
    matmul_q8q8_groupn(y_b, q2, s2, pd.offs, pd.nregions, pd.xq, pd.xs, pd.bias, pd.boffs, n, d)
    check_pair(y_a, y_b, rows, exact, "{name} groupn")

    if (!repacked) {   // mx4 planes are row-major on every x64 backend
        select_kernel_backend(name)
        matmul_mx4q8(y_a, pd.wn, pd.we, pd.xq, pd.xs, n, d)            // mm_mx4 (region 0)
        select_kernel_backend(donor)
        matmul_mx4q8(y_b, pd.wn, pd.we, pd.xq, pd.xs, n, d)
        check_pair(y_a, y_b, d, exact, "{name} mm_mx4")

        select_kernel_backend(name)
        matmul_mx4q8_groupn(y_a, pd.wn, pd.we, pd.offs, pd.nregions, pd.xq, pd.xs, pd.bias, pd.boffs, n, d)
        select_kernel_backend(donor)
        matmul_mx4q8_groupn(y_b, pd.wn, pd.we, pd.offs, pd.nregions, pd.xq, pd.xs, pd.bias, pd.boffs, n, d)
        check_pair(y_a, y_b, rows, exact, "{name} groupn_mx4")
    }

    select_kernel_backend(name)
    matmul_mx4q8_batch(y_a, pd.wn, pd.we, pd.xq, pd.xs, n, d, ntok)    // mx4 batch (region 0)
    select_kernel_backend(donor)
    matmul_mx4q8_batch(y_b, pd.wn, pd.we, pd.xq, pd.xs, n, d, ntok)
    check_pair(y_a, y_b, ntok * d, exact && mx4_batch_exact, "{name} mx4_batch")

    if (pd.total > 0l) {
        select_kernel_backend(name)
        matmul_mx4q8_batch_groupn(y_a, pd.wn, pd.we, pd.toffs, pd.nregions, pd.xq, pd.xs, pd.bias, pd.boffs, n, d)
        select_kernel_backend(donor)
        matmul_mx4q8_batch_groupn(y_b, pd.wn, pd.we, pd.toffs, pd.nregions, pd.xq, pd.xs, pd.bias, pd.boffs, n, d)
        check_pair(y_a, y_b, pd.total * d, exact && mx4_batch_exact, "{name} mx4_batch_groupn")
    }
    print("backend {name} vs {donor} n={n} d={d} ntok={ntok} R={pd.nregions}: {exact ? "bit-exact" : "rel<1e-5"}{repacked ? " (repacked)" : ""}  OK\n")
    delete q2
    delete s2
    delete y_a
    delete y_b
}

// The strip-dequant contract for the avx512vnni mx4 batch slots: same-backend mx4 batch vs Q8
// batch on an INDEPENDENT exact expansion of the planes — same bytes, same z16vnni dots, so
// bit-exact (the mx4x64_probe gate, on the z-strip kernels).
def check_z16vnni_expansion(n, d, ntok : int64; pd : ProbeData) {
    select_kernel_backend("x64-avx512vnni")
    if (active_kernel_backend() != "x64-avx512vnni") {
        return
    }
    let nb = n / 32l
    var lut : int8[16]
    mxfp4_fill_lut(lut)
    var q : array<int8>
    var s : array<float>
    q |> resize(d * n)
    s |> resize(d * nb)
    for (bi in range64(d * nb)) {
        for (j in range64(16l)) {
            let b = int(pd.wn[bi * 16l + j])
            q[bi * 32l + j] = lut[b & 15]
            q[bi * 32l + 16l + j] = lut[b >> 4]
        }
        s[bi] = e8m0_half(uint(pd.we[bi]))
    }
    var y_a : array<float>
    var y_b : array<float>
    y_a |> resize(ntok * d)
    y_b |> resize(ntok * d)
    matmul_mx4q8_batch(y_a, pd.wn, pd.we, pd.xq, pd.xs, n, d, ntok)
    matmul_q8q8_batch(y_b, q, s, pd.xq, pd.xs, n, d, ntok)
    check_pair(y_a, y_b, ntok * d, true, "x64-avx512vnni mx4_batch vs expansion")
    print("backend x64-avx512vnni mx4_batch vs own Q8 batch on exact expansion n={n} d={d} ntok={ntok}: bit-exact  OK\n")
    delete q
    delete s
    delete y_a
    delete y_b
}

def check_backends(n, d, ntok, nregions : int64) {
    var pd <- make_probe_data(n, d, ntok, nregions)
    check_backend("x64-vnni256", "x64-avx2", true, false, true, n, d, ntok, pd)
    check_backend("x64-vnni256-acc8", "x64-avx2-acc8", true, false, true, n, d, ntok, pd)
    check_backend("x64-vnni256-repack", "x64-avx2-repack", true, true, true, n, d, ntok, pd)
    check_backend("x64-avx512vnni", "x64-avx512bw", true, false, false, n, d, ntok, pd)
    check_backend("x64-avx512bw", "portable", false, false, false, n, d, ntok, pd)
    check_z16vnni_expansion(n, d, ntok, pd)
    delete pd
}

[export]
def main {
    print("avx matrix: enabled={g_avx_matrix_enabled} force={g_avx_matrix_force} cpu: avxvnni={cpu_supports("avxvnni")} avx512bw={cpu_supports("avx512bw")} avx512vnni={cpu_supports("avx512vnni")}\n")
    print("backends: {kernel_backend_names()}\n")
    if (!jit_enabled()) {
        print("NOTE: no -jit — probing the FALLBACK bodies (valid; run again with -jit)\n")
    }
    with_job_que() {
        setup_dasllama_jobque_()
        check_intrinsics()
        check_backends(64l, 8l, 4l, 5l)      // nb even, d%4 == 0
        check_backends(96l, 10l, 3l, 4l)     // nb ODD (z16/dequant64 odd-block tails), d%4 == 2 (grp4 row tails)
        check_backends(2880l, 20l, 5l, 3l)   // model-width rows, grp4x2 + TB + threaded paths engaged
        print("avx matrix probe: ALL OK\n")
    }
}
