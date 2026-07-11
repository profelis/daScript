options gen2
options stack = 65536   // dasLLAMA program-root convention (options stack does not unify up from libs)

require dastest/testing_boost public
require _model_tier
require dasllama/dasllama_gguf
require dasllama/dasllama_quant
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

[test]
def test_q4k_synthetic(t : T?) {
    t |> run("Q4_K superblock unpacks the 6-bit scale/min packing") @(t : T?) {
        // 6-bit values > 15 exercise the split high-bit arms of get_scale_min_k4 (j >= 4)
        let sc <- [63, 21, 37, 5, 48, 17, 60, 33]
        let mn <- [1, 62, 19, 44, 7, 58, 25, 36]
        let d = 0.5      // f16-exact, so expected-value math can use the f32 value directly
        let dmin = 0.25
        var blkb : array<uint8>
        blkb |> resize(144)
        let dbits = f32_to_f16(d)
        let mbits = f32_to_f16(dmin)
        blkb[0] = uint8(dbits & 0xFF)
        blkb[1] = uint8(dbits >> 8u)
        blkb[2] = uint8(mbits & 0xFF)
        blkb[3] = uint8(mbits >> 8u)
        for (j in range(4)) {
            blkb[4 + j] = uint8((sc[j] & 63) | (((sc[j + 4] >> 4) & 3) << 6))
            blkb[8 + j] = uint8((mn[j] & 63) | (((mn[j + 4] >> 4) & 3) << 6))
            blkb[12 + j] = uint8((sc[j + 4] & 15) | ((mn[j + 4] & 15) << 4))
        }
        // chunk js: 32 bytes carry weights 64js..+31 in low nibbles, 64js+32..+31 in high
        for (js in range(4)) {
            for (l in range(32)) {
                blkb[16 + 32 * js + l] = uint8(q4_pat(64 * js + l) | (q4_pat(64 * js + 32 + l) << 4))
            }
        }
        var dst : array<float>
        dst |> resize(256)
        dequant_q4k_superblock(blkb, 0l, dst, 0l)
        for (k in range(256)) {
            let sub = k / 32
            let expected = d * float(sc[sub]) * float(q4_pat(k)) - dmin * float(mn[sub])
            t |> success(dst[k] == expected, "Q4_K element must match hand-packed value exactly")
        }
    }
    t |> run("Q5_K superblock unpacks the split high-bit plane") @(t : T?) {
        // reuse the Q4_K scale/min values (same 12-byte packing) — the new surface is qh
        let sc <- [63, 21, 37, 5, 48, 17, 60, 33]
        let mn <- [1, 62, 19, 44, 7, 58, 25, 36]
        let d = 0.5
        let dmin = 0.25
        var blkb : array<uint8>
        blkb |> resize(176)
        let dbits = f32_to_f16(d)
        let mbits = f32_to_f16(dmin)
        blkb[0] = uint8(dbits & 0xFF)
        blkb[1] = uint8(dbits >> 8u)
        blkb[2] = uint8(mbits & 0xFF)
        blkb[3] = uint8(mbits >> 8u)
        for (j in range(4)) {
            blkb[4 + j] = uint8((sc[j] & 63) | (((sc[j + 4] >> 4) & 3) << 6))
            blkb[8 + j] = uint8((mn[j] & 63) | (((mn[j + 4] >> 4) & 3) << 6))
            blkb[12 + j] = uint8((sc[j + 4] & 15) | ((mn[j + 4] & 15) << 4))
        }
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
        var dst : array<float>
        dst |> resize(256)
        dequant_q5k_superblock(blkb, 0l, dst, 0l)
        for (k in range(256)) {
            let sub = k / 32
            let expected = d * float(sc[sub]) * float(q5_pat(k)) - dmin * float(mn[sub])
            t |> success(dst[k] == expected, "Q5_K element must match hand-packed value exactly")
        }
    }
    t |> run("Q6_K superblock unpacks the ql/qh split and signed sub-scales") @(t : T?) {
        let scq <- [3, -5, 60, -60, 17, 127, -128, 1, 0, 33, -77, 90, -2, 45, -101, 7]
        let d = 0.25
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
            blkb[192 + i] = uint8(scq[i] & 255)
        }
        let dbits = f32_to_f16(d)
        blkb[208] = uint8(dbits & 0xFF)
        blkb[209] = uint8(dbits >> 8u)
        var dst : array<float>
        dst |> resize(256)
        dequant_q6k_superblock(blkb, 0l, dst, 0l)
        for (k in range(256)) {
            let expected = d * float(scq[k / 16]) * float(q6_pat(k) - 32)
            t |> success(dst[k] == expected, "Q6_K element must match hand-packed value exactly")
        }
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
