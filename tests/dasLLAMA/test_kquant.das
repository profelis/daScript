options gen2
options stack = 65536   // dasLLAMA program-root convention (options stack does not unify up from libs)
options persistent_heap   // the layout arm loads a multi-GB model; explicit delete below

require dastest/testing_boost public
require _model_tier
require dasllama/dasllama_gguf
require dasllama/dasllama_quant
require dasllama/dasllama_math_default   // dot_k4q8/k5/k6 — the kernel arms gate them vs the plane dequant
require dasllama/dasllama_transformer   // nolint:STYLE029 — umbrella fires each arch [init] registration for load_gguf
require math

// K-quant (Q4_K / Q6_K) superblock dequant gates. The synthetic arms hand-pack one superblock
// with the ggml bit layout written in the PACK direction (independent of the reader's unpack),
// so a layout misread fails loudly with no model files needed. The dequant arithmetic itself is
// proven bit-exact against gguf-py's dequantize (harness/q4k_dequant_probe.das); the real-file
// arm cross-checks against the Q8_0 twin of the same weights at known quantization-error levels.

// synthetic quant patterns: every nibble/5-bit/6-bit value, position-dependent so swaps can't cancel
def private q4_pat(k : int) : int => (k * 7 + 3) % 16
def private q5_pat(k : int) : int => (k * 3 + 7) % 32
def private q6_pat(k : int) : int => (k * 5 + 11) % 64

// The shared synthetic scale/min sets: 6-bit values > 15 exercise the split high-bit arms of
// get_scale_min_k4 (j >= 4); d/dmin are f16-exact so expected-value math uses the f32 value.
let SYNTH_SC <- [63, 21, 37, 5, 48, 17, 60, 33]
let SYNTH_MN <- [1, 62, 19, 44, 7, 58, 25, 36]
let SYNTH_D = 0.5
let SYNTH_DMIN = 0.25
let SYNTH_SCQ <- [3, -5, 60, -60, 17, 127, -128, 1, 0, 33, -77, 90, -2, 45, -101, 7]

// Pack the 4-byte header + 12 scale/min bytes shared by the Q4_K/Q5_K synthetic superblocks.
def private pack_kq_header(var blkb : array<uint8>) {
    let dbits = f32_to_f16(SYNTH_D)
    let mbits = f32_to_f16(SYNTH_DMIN)
    blkb[0] = uint8(dbits & 0xFF)
    blkb[1] = uint8(dbits >> 8u)
    blkb[2] = uint8(mbits & 0xFF)
    blkb[3] = uint8(mbits >> 8u)
    for (j in range(4)) {
        blkb[4 + j] = uint8((SYNTH_SC[j] & 63) | (((SYNTH_SC[j + 4] >> 4) & 3) << 6))
        blkb[8 + j] = uint8((SYNTH_MN[j] & 63) | (((SYNTH_MN[j + 4] >> 4) & 3) << 6))
        blkb[12 + j] = uint8((SYNTH_SC[j + 4] & 15) | ((SYNTH_MN[j + 4] & 15) << 4))
    }
}

def private build_q4k_block() : array<uint8> {
    var blkb : array<uint8>
    blkb |> resize(144)
    pack_kq_header(blkb)
    // chunk js: 32 bytes carry weights 64js..+31 in low nibbles, 64js+32..+31 in high
    for (js in range(4)) {
        for (l in range(32)) {
            blkb[16 + 32 * js + l] = uint8(q4_pat(64 * js + l) | (q4_pat(64 * js + 32 + l) << 4))
        }
    }
    return <- blkb
}

def private build_q5k_block() : array<uint8> {
    var blkb : array<uint8>
    blkb |> resize(176)
    pack_kq_header(blkb)
    // qh[l] bit 2js = high bit of weight 64js+l, bit 2js+1 = high bit of weight 64js+32+l
    for (js in range(4)) {
        for (l in range(32)) {
            blkb[48 + 32 * js + l] = uint8((q5_pat(64 * js + l) & 15) | ((q5_pat(64 * js + 32 + l) & 15) << 4))
            var h = int(blkb[16 + l])
            h |= (q5_pat(64 * js + l) >> 4) << (2 * js)
            h |= (q5_pat(64 * js + 32 + l) >> 4) << (2 * js + 1)
            blkb[16 + l] = uint8(h)
        }
    }
    return <- blkb
}

def private build_q6k_block() : array<uint8> {
    var blkb : array<uint8>
    blkb |> resize(210)
    for (half in range(2)) {
        let base = 128 * half
        for (l in range(32)) {
            blkb[64 * half + l] = uint8((q6_pat(base + l) & 15) | ((q6_pat(base + 64 + l) & 15) << 4))
            blkb[64 * half + 32 + l] = uint8((q6_pat(base + 32 + l) & 15) | ((q6_pat(base + 96 + l) & 15) << 4))
            blkb[128 + 32 * half + l] = uint8((q6_pat(base + l) >> 4) | ((q6_pat(base + 32 + l) >> 4) << 2)
                | ((q6_pat(base + 64 + l) >> 4) << 4) | ((q6_pat(base + 96 + l) >> 4) << 6))
        }
    }
    for (i in range(16)) {
        blkb[192 + i] = uint8(SYNTH_SCQ[i] & 255)
    }
    let dbits = f32_to_f16(0.25)
    blkb[208] = uint8(dbits & 0xFF)
    blkb[209] = uint8(dbits >> 8u)
    return <- blkb
}

// f16 round-trip: the rounding the transcoded (s, o) pairs carry
def private f16r(x : float) : float => f16_to_f32(f32_to_f16(x))

[test]
def test_q4k_synthetic(t : T?) {
    t |> run("Q4_K superblock unpacks the 6-bit scale/min packing") @(t : T?) {
        let blkb <- build_q4k_block()
        var dst : array<float>
        dst |> resize(256)
        dequant_q4k_superblock(blkb, 0l, dst, 0l)
        for (k in range(256)) {
            let sub = k / 32
            let expected = SYNTH_D * float(SYNTH_SC[sub]) * float(q4_pat(k)) - SYNTH_DMIN * float(SYNTH_MN[sub])
            t |> success(dst[k] == expected, "Q4_K element must match hand-packed value exactly")
        }
    }
    t |> run("Q5_K superblock unpacks the split high-bit plane") @(t : T?) {
        let blkb <- build_q5k_block()
        var dst : array<float>
        dst |> resize(256)
        dequant_q5k_superblock(blkb, 0l, dst, 0l)
        for (k in range(256)) {
            let sub = k / 32
            let expected = SYNTH_D * float(SYNTH_SC[sub]) * float(q5_pat(k)) - SYNTH_DMIN * float(SYNTH_MN[sub])
            t |> success(dst[k] == expected, "Q5_K element must match hand-packed value exactly")
        }
    }
    t |> run("Q6_K superblock unpacks the ql/qh split and signed sub-scales") @(t : T?) {
        let blkb <- build_q6k_block()
        var dst : array<float>
        dst |> resize(256)
        dequant_q6k_superblock(blkb, 0l, dst, 0l)
        for (k in range(256)) {
            let expected = 0.25 * float(SYNTH_SCQ[k / 16]) * float(q6_pat(k) - 32)
            t |> success(dst[k] == expected, "Q6_K element must match hand-packed value exactly")
        }
    }
}

[test]
def test_kq_transcode_planes(t : T?) {
    // The transcoded planes ARE the kernel-facing format: k4/k5 dequant must equal the file
    // dequant with the (s, o) pairs' f16 rounding applied; k6 planes are verbatim, so exact.
    t |> run("k4 planes reproduce the f16-rounded Q4_K dequant") @(t : T?) {
        let blkb <- build_q4k_block()
        var kq : array<uint8>
        var ks : array<uint8>
        kq |> resize(128)
        ks |> resize(32)
        transcode_q4k_superblock(blkb, 0l, kq, 0l, ks, 0l)
        var dst : array<float>
        dst |> resize(256)
        dequant_k4_plane_superblock(kq, 0l, ks, 0l, dst, 0l)
        for (k in range(256)) {
            let sub = k / 32
            let expected = f16r(SYNTH_D * float(SYNTH_SC[sub])) * float(q4_pat(k)) - f16r(SYNTH_DMIN * float(SYNTH_MN[sub]))
            t |> success(dst[k] == expected, "k4 plane element must match the f16-rounded value exactly")
        }
    }
    t |> run("k5 planes reproduce the f16-rounded Q5_K dequant") @(t : T?) {
        let blkb <- build_q5k_block()
        var kq : array<uint8>
        var ks : array<uint8>
        kq |> resize(160)
        ks |> resize(32)
        transcode_q5k_superblock(blkb, 0l, kq, 0l, ks, 0l)
        var dst : array<float>
        dst |> resize(256)
        dequant_k5_plane_superblock(kq, 0l, ks, 0l, dst, 0l)
        for (k in range(256)) {
            let sub = k / 32
            let expected = f16r(SYNTH_D * float(SYNTH_SC[sub])) * float(q5_pat(k)) - f16r(SYNTH_DMIN * float(SYNTH_MN[sub]))
            t |> success(dst[k] == expected, "k5 plane element must match the f16-rounded value exactly")
        }
    }
    t |> run("k6 planes reproduce the Q6_K dequant bit-exactly") @(t : T?) {
        let blkb <- build_q6k_block()
        var kq : array<uint8>
        var ks : array<uint8>
        kq |> resize(192)
        ks |> resize(18)
        transcode_q6k_superblock(blkb, 0l, kq, 0l, ks, 0l)
        var want : array<float>
        want |> resize(256)
        dequant_q6k_superblock(blkb, 0l, want, 0l)
        var dst : array<float>
        dst |> resize(256)
        dequant_k6_plane_superblock(kq, 0l, ks, 0l, dst, 0l)
        for (k in range(256)) {
            t |> success(dst[k] == want[k], "k6 plane element must equal the file dequant bit-exactly")
        }
    }
}

// XOR the quant payload of a synthetic superblock with an LCG byte stream — every quant bit
// pattern is valid, so the second superblock of a kernel test carries different data (an
// inter-superblock offset bug can't cancel).
def private perturb_quants(var blkb : array<uint8>; qoff, qlen : int) {
    var st = 0x12345u
    for (i in range(qlen)) {
        st = st * 1664525u + 1013904223u
        blkb[qoff + i] = uint8(uint(blkb[qoff + i]) ^ (st >> 16u))
    }
}

// Kernel-vs-reference gate core: transcode two distinct superblocks of `fmt`, quantize a smooth
// activation with the bs quantizer, and compare the integer-domain kernel dot against the fp64
// elementwise dot over the plane dequant (the kernels' declared oracle).
def private kq_dot_gate(t : T?; fmt : int) {
    let n = 512l
    let blk1 <- fmt == 4 ? build_q4k_block() : (fmt == 5 ? build_q5k_block() : build_q6k_block())
    var blk2 <- fmt == 4 ? build_q4k_block() : (fmt == 5 ? build_q5k_block() : build_q6k_block())
    if (fmt == 4) {
        perturb_quants(blk2, 16, 128)
    } elif (fmt == 5) {
        perturb_quants(blk2, 16, 160)   // qh + qs
    } else {
        perturb_quants(blk2, 0, 192)    // ql + qh
    }
    let qsb = fmt == 4 ? 128l : (fmt == 5 ? 160l : 192l)
    let ssb = fmt == 6 ? 18l : 32l
    var kq : array<uint8>
    var ks : array<uint8>
    kq |> resize(2l * qsb)
    ks |> resize(2l * ssb)
    if (fmt == 4) {
        transcode_q4k_superblock(blk1, 0l, kq, 0l, ks, 0l)
        transcode_q4k_superblock(blk2, 0l, kq, qsb, ks, ssb)
    } elif (fmt == 5) {
        transcode_q5k_superblock(blk1, 0l, kq, 0l, ks, 0l)
        transcode_q5k_superblock(blk2, 0l, kq, qsb, ks, ssb)
    } else {
        transcode_q6k_superblock(blk1, 0l, kq, 0l, ks, 0l)
        transcode_q6k_superblock(blk2, 0l, kq, qsb, ks, ssb)
    }
    // plane dequant = the reference weights
    var w : array<float>
    w |> resize(n)
    for (s in range64(2l)) {
        if (fmt == 4) {
            dequant_k4_plane_superblock(kq, s * qsb, ks, s * ssb, w, s * 256l)
        } elif (fmt == 5) {
            dequant_k5_plane_superblock(kq, s * qsb, ks, s * ssb, w, s * 256l)
        } else {
            dequant_k6_plane_superblock(kq, s * qsb, ks, s * ssb, w, s * 256l)
        }
    }
    // activation: smooth signal -> bs quantizer (quants + scales + per-16 sums)
    var src : array<float>
    src |> resize(n)
    for (i in range64(n)) {
        src[i] = 1.7 * sin(float(i) * 0.23) + 0.3 * cos(float(i) * 0.071)
    }
    var xq : array<int8>
    var xs : array<float>
    var xbs : array<int>
    xq |> resize(n)
    xs |> resize(n / 32l)
    xbs |> resize(n / 16l)
    quantize_q8_0_bs_into(src, n, xq, xs, xbs, 0l, 0l, 0l)
    // fp64 elementwise reference over the SAME quantized activation
    var ref = 0.0lf
    for (i in range64(n)) {
        ref += double(w[i]) * double(xq[i]) * double(xs[i / 32l])
    }
    var got = 0.0
    unsafe {
        if (fmt == 4) {
            got = dot_k4q8(addr(kq[0]), addr(ks[0]), addr(xq[0]), addr(xs[0]), addr(xbs[0]), n)
        } elif (fmt == 5) {
            got = dot_k5q8(addr(kq[0]), addr(ks[0]), addr(xq[0]), addr(xs[0]), addr(xbs[0]), n)
        } else {
            got = dot_k6q8(addr(kq[0]), addr(ks[0]), addr(xq[0]), addr(xs[0]), addr(xbs[0]), n)
        }
    }
    let denom = max(abs(float(ref)), 1.0e-6)
    t |> success(abs(got - float(ref)) / denom < 1.0e-4, "kernel dot must match the fp64 plane-dequant reference")
}

[test]
def test_kq_dots(t : T?) {
    t |> run("dot_k4q8 matches the fp64 plane-dequant reference") @(t : T?) {
        kq_dot_gate(t, 4)
    }
    t |> run("dot_k5q8 matches the fp64 plane-dequant reference") @(t : T?) {
        kq_dot_gate(t, 5)
    }
    t |> run("dot_k6q8 matches the fp64 plane-dequant reference") @(t : T?) {
        kq_dot_gate(t, 6)
    }
}

[test]
def test_quantize_bs(t : T?) {
    t |> run("bs quantizer matches quantize_q8_0 byte-for-byte plus exact per-16 sums") @(t : T?) {
        let n = 4096l
        var src : array<float>
        src |> resize(n)
        for (i in range64(n)) {
            src[i] = 2.0 * sin(float(i) * 0.37) - 0.11 * float(i % 13l)
        }
        let want <- quantize_q8_0(src, n)
        var qdst : array<int8>
        var sdst : array<float>
        var bdst : array<int>
        qdst |> resize(n)
        sdst |> resize(n / 32l)
        bdst |> resize(n / 16l)
        quantize_q8_0_bs_into(src, n, qdst, sdst, bdst, 0l, 0l, 0l)
        var qbad = 0
        var sbad = 0
        var bbad = 0
        for (j in range64(n)) {
            if (qdst[j] != want.q[j]) {
                qbad++
            }
        }
        for (b in range64(n / 32l)) {
            if (sdst[b] != want.scales[b]) {
                sbad++
            }
        }
        for (h in range64(n / 16l)) {
            var bs = 0
            for (i in range64(16l)) {
                bs += int(want.q[h * 16l + i])
            }
            if (bdst[h] != bs) {
                bbad++
            }
        }
        t |> success(qbad == 0, "quants byte-identical to quantize_q8_0")
        t |> success(sbad == 0, "scales bit-identical to quantize_q8_0")
        t |> success(bbad == 0, "per-16 sums exact")
    }
}

// Dequant `n` elements from a Model kq plane starting at plane-local element offset `eloff`.
def private dequant_plane_prefix(tr : Model; fmt : KqFmt; eloff, n : int64; var dst : array<float>) {
    for (blk in range64(n / 256l)) {
        let sb = (eloff + blk * 256l) / 256l
        if (fmt == KqFmt.k4) {
            dequant_k4_plane_superblock(tr.k4q, sb * K4_QSB, tr.k4s, sb * K4_SSB, dst, blk * 256l)
        } elif (fmt == KqFmt.k5) {
            dequant_k5_plane_superblock(tr.k5q, sb * K5_QSB, tr.k5s, sb * K5_SSB, dst, blk * 256l)
        } elif (fmt == KqFmt.k6) {
            dequant_k6_plane_superblock(tr.k6q, sb * K6_QSB, tr.k6s, sb * K6_SSB, dst, blk * 256l)
        } else {
            panic("dequant_plane_prefix: not a kq format")
        }
    }
}

[test]
def test_kq_load_layout(t : T?) {
    // End-to-end stage-2 oracle: a kquant_native load must place every tagged tensor at its
    // cursor-assigned plane offset. Plane-dequant of tensor prefixes vs the file dequant —
    // exact for k6 (verbatim planes), quant-noise-free but f16-pair-rounded for k4 (rel RMS
    // bound catches any misplaced superblock loudly; the synthetic arms above pin the bit level).
    t |> run("kquant_native load places tensors at their cursor offsets (Qwen3-4B Q4_K_M)") @(t : T?) {
        if (!jit_enabled()) {
            t |> skip("interpreted (dasLLAMA model tests are JIT-only)")
            return
        }
        let path = path_join(models_dir(), "Qwen3-4B-Instruct-2507-Q4_K_M.gguf")
        if (!model_available(t, path)) {
            return
        }
        set_kquant_native(true)
        var tr <- load_gguf(path, QuantMode.q8)
        set_kquant_native(false)
        t |> success(tr.kquant_native, "load detected native K-quant tensors")
        t |> success(cls_kq(tr), "tied Q6_K classifier takes the kq plane path")
        t |> success(tr.wq_fmt[0] == KqFmt.k4, "blk.0.attn_q tagged k4")
        t |> success(tr.wv_fmt[0] == KqFmt.k6, "blk.0.attn_v tagged k6")
        let n = 262144l
        var have : array<float>
        have |> resize(n)
        // deep-layer k4 tensor: catches cursor drift accumulated across every earlier tensor
        let l = tr.config.n_layers - 1l
        dequant_plane_prefix(tr, tr.wq_fmt[l], tr.wq_offs[l], n, have)
        var gt = 0
        var fdq <- read_prefix(path, "blk.{l}.attn_q.weight", n, gt)
        let r4 = rel_rms(have, fdq)
        t |> success(r4 < 1.0e-3, "deep-layer k4 plane matches the file dequant (f16-pair rounding only)")
        delete fdq
        // k6 (verbatim planes): the tied classifier row block — must be bit-exact
        var fdq6 <- read_prefix(path, "token_embd.weight", n, gt)
        dequant_plane_prefix(tr, tr.emb_fmt, tr.wcls_off, n, have)
        var bad = 0
        for (i in range64(n)) {
            if (have[i] != fdq6[i]) {
                bad++
            }
        }
        t |> success(bad == 0, "k6 classifier plane bit-matches the file dequant")
        delete fdq6
        delete have
        delete tr
    }
}

// Dequant the first `n` elements of `name` into fp32; reports the on-disk type via `gt`.
def private read_prefix(path, name : string; n : int64; var gt : int&) : array<float> {
    var dst : array<float>
    dst |> resize(n)
    let f = fopen(path, "rb")
    if (f == null) {
        panic("cannot open {path}")
    }
    fmap(f) $(var bytes : array<uint8>#) {
        var m <- parse_gguf_meta(bytes)
        gt = gguf_tensor_type(m, name)
        gguf_read_tensor_f32(m, bytes, name, dst, 0l, n)
        delete m
    }
    fclose(f)
    return <- dst
}

// Relative RMS of (a - b) against RMS(b), double accumulation.
def private rel_rms(a, b : array<float>) : float {
    var num = 0.0lf
    var den = 0.0lf
    for (x, y in a, b) {
        let dxy = double(x) - double(y)
        num += dxy * dxy
        den += double(y) * double(y)
    }
    return float(sqrt(num / den))
}

[test]
def test_q4k_real_file(t : T?) {
    t |> run("gemma-4-12B Q4_K_M dequant tracks the Q8_0 twin at quant-error level") @(t : T?) {
        let q4path = path_join(models_dir(), "gemma-4-12B-it-Q4_K_M.requant.gguf")
        let q8path = path_join(models_dir(), "gemma-4-12B-it-Q8_0.gguf")
        if (!model_available(t, q4path)) {
            return
        }
        if (!model_available(t, q8path)) {
            return
        }
        // census: the Q4_K_M mix this arc targets — tied cls (token_embd) is Q6_K, bulk is Q4_K
        var gt = 0
        let n = 262144l   // 1024 superblocks — plenty of RMS statistics
        var q4a <- read_prefix(q4path, "blk.0.attn_q.weight", n, gt)
        t |> equal(gt, GGML_TYPE_Q4_K)
        var q8a <- read_prefix(q8path, "blk.0.attn_q.weight", n, gt)
        t |> equal(gt, GGML_TYPE_Q8_0)
        let rq4 = rel_rms(q4a, q8a)
        // measured 0.081 (requantized-from-q8 4.5-bit error); 2x margin, floor guards a same-file mixup
        t |> success(rq4 > 0.005 && rq4 < 0.15, "Q4_K rel RMS vs Q8_0 twin within quant-error band")
        delete q4a
        delete q8a
        var q6a <- read_prefix(q4path, "blk.0.attn_v.weight", n, gt)
        t |> equal(gt, GGML_TYPE_Q6_K)
        var q8b <- read_prefix(q8path, "blk.0.attn_v.weight", n, gt)
        t |> equal(gt, GGML_TYPE_Q8_0)
        let rq6 = rel_rms(q6a, q8b)
        // measured 0.022
        t |> success(rq6 > 0.002 && rq6 < 0.05, "Q6_K rel RMS vs Q8_0 twin within quant-error band")
        delete q6a
        delete q8b
        var gte = 0
        var emb <- read_prefix(q4path, "token_embd.weight", 256l, gte)
        t |> equal(gte, GGML_TYPE_Q6_K)
        delete emb
    }
}
