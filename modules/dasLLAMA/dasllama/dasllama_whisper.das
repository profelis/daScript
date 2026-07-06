options gen2

module dasllama_whisper shared public

require math
require daslib/fio
require daslib/array_boost // nolint:STYLE030 — temp_array is [template]; STYLE030 misses template-fn refs
require strings
require dasllama/dasllama_math
require dasllama/dasllama_par
require dasllama/dasllama_gguf
require dasllama/dasllama_audio

// Whisper-proper ASR: reads ggerganov/whisper.cpp ggml-*.bin models directly (drop-in HF
// models, no converter), reuses the validated encoder tower from dasllama_audio, adds the
// text decoder with cross-attention and the greedy transcription driver. Oracle =
// whisper.cpp CPU greedy — see whisper_plan.md for the container layout and driver rules.

// ===== model =====

//! A loaded whisper.cpp model: encoder tower (dasllama_audio's AudioTower, gelu_tanh flavor),
//! decoder weight blob + offsets, byte-level vocab, mel filterbank from the file, and the
//! special-token protocol ids (multilingual-shifted per whisper.cpp's vocab math).
struct WhisperModel {
    n_vocab : int64
    n_text_ctx : int64
    n_text_state : int64
    n_text_head : int64
    n_text_layer : int64
    eps : float = 1e-5
    multilingual : bool
    n_lang : int64
    tok_eot : int
    tok_sot : int
    tok_translate : int
    tok_transcribe : int
    tok_solm : int
    tok_prev : int
    tok_nosp : int
    tok_not : int
    tok_beg : int
    tok_space : int    // id of " " (suppress_blank's second victim)
    vocab : array<string>    // id -> raw bytes; synthesized tail ids (specials/timestamps) are ""
    filters : array<float>   // mel filterbank [n_mel][201], loaded from the file
    enc : AudioTower = AudioTower()
    dblob : array<float>
    d_pe_off : int64
    d_te_off : int64
    d_ln_w_off : int64
    d_ln_b_off : int64
    dlayers_off : int64
    dlayer_stride : int64
}

// Per-layer decoder tensor offsets inside dblob, in layout order (24 tensors: self-attn
// block, cross-attn block, mlp block; both k projections have no bias).
struct DecLayerOffs {
    ln1_w : int64
    ln1_b : int64
    q_w : int64
    q_b : int64
    k_w : int64
    v_w : int64
    v_b : int64
    o_w : int64
    o_b : int64
    cln_w : int64
    cln_b : int64
    cq_w : int64
    cq_b : int64
    ck_w : int64
    cv_w : int64
    cv_b : int64
    co_w : int64
    co_b : int64
    ln2_w : int64
    ln2_b : int64
    fc1_w : int64
    fc1_b : int64
    fc2_w : int64
    fc2_b : int64
}

def dec_layer_offsets(w : WhisperModel; l : int64) : DecLayerOffs {
    let d = w.n_text_state
    let ff = 4l * d
    var o = w.dlayers_off + l * w.dlayer_stride
    var r = DecLayerOffs()
    r.ln1_w = o; o += d
    r.ln1_b = o; o += d
    r.q_w = o; o += d * d
    r.q_b = o; o += d
    r.k_w = o; o += d * d
    r.v_w = o; o += d * d
    r.v_b = o; o += d
    r.o_w = o; o += d * d
    r.o_b = o; o += d
    r.cln_w = o; o += d
    r.cln_b = o; o += d
    r.cq_w = o; o += d * d
    r.cq_b = o; o += d
    r.ck_w = o; o += d * d
    r.cv_w = o; o += d * d
    r.cv_b = o; o += d
    r.co_w = o; o += d * d
    r.co_b = o; o += d
    r.ln2_w = o; o += d
    r.ln2_b = o; o += d
    r.fc1_w = o; o += ff * d
    r.fc1_b = o; o += ff
    r.fc2_w = o; o += d * ff
    r.fc2_b = o; o += d
    return r
}

// 8 square mats + 2 mlp mats (4d·d each) + 13 d-vectors + fc1 bias (4d)
def dec_layer_stride(d : int64) : int64 => 16l * d * d + 17l * d

// ===== ggml bin container parsing =====

// One tensor's location in the bin: ggml ttype (0=f32, 1=f16), element count, absolute
// byte offset of the raw data (which follows the name with NO alignment padding).
struct private WTensorRec {
    ttype : int
    n_elem : int64
    off : int64
}

def private bytes_str(b : array<uint8> | #; o, n : int64) : string {
    if (n <= 0l) {
        return ""
    }
    var s = ""
    unsafe {
        s = string(temp_array(reinterpret<uint8?>(addr(b[o])), n, type<uint8>))
    }
    return s
}

// Read a tensor's raw data (f32 or f16) into dst[dst_off..) as fp32. Byte-wise reads — the
// bin stores tensor data unaligned.
def private wt_read(recs : table<string; WTensorRec>; b : array<uint8> | #; name : string;
                    var dst : array<float>; dst_off, n : int64) {
    if (!key_exists(recs, name)) {
        panic("dasLLAMA whisper: missing tensor '{name}' in model file")
    }
    let r = recs?[name] ?? default<WTensorRec>
    if (r.n_elem != n) {
        panic("dasLLAMA whisper: tensor '{name}' has {r.n_elem} elements, want {n}")
    }
    if (r.ttype == GGML_TYPE_F32) {
        for (i in range64(n)) {
            dst[dst_off + i] = rd_f32(b, r.off + i * 4l)
        }
    } else {
        for (i in range64(n)) {
            dst[dst_off + i] = f16_to_f32(rd_u16(b, r.off + i * 2l))
        }
    }
}

// Conv1d weight (flat [c_out][c_in][k=3], k contiguous — torch layout) permuted to the
// im2col column order W'[o][dk·C + c] the encoder's frontend expects.
def private wt_read_conv_permuted(recs : table<string; WTensorRec>; b : array<uint8> | #; name : string;
                                  var blob : array<float>; off : int64; c_out, c_in : int64) {
    var raw : array<float>
    raw |> resize(int(c_out * c_in * 3l))
    wt_read(recs, b, name, raw, 0l, c_out * c_in * 3l)
    for (o in range64(c_out)) {
        for (c in range64(c_in)) {
            for (k in range64(3l)) {
                blob[off + o * c_in * 3l + k * c_in + c] = raw[o * c_in * 3l + c * 3l + k]
            }
        }
    }
}

//! Load a whisper.cpp ggml-*.bin model (f32/f16 tensor types; quantized whisper bins are not
//! supported). Verified against whisper.cpp's whisper_model_load, byte for byte.
def load_whisper_model(path : string) : WhisperModel {
    var w = WhisperModel()
    // the record walk runs until EOF, so it needs the true byte count — length(bytes) is
    // int32 and wraps negative on >2 GB bins (large-v3); stat's st_size is 64-bit
    let n_bytes = int64(stat(path).size)
    let f = fopen(path, "rb")
    if (f == null) {
        panic("dasLLAMA whisper: cannot open model '{path}'")
    }
    fmap(f) $(var bytes : array<uint8>#) {
        var o = 0l
        if (rd_u32(bytes, o) != 0x67676d6cu) {
            panic("dasLLAMA whisper: bad magic in '{path}' (want ggml 0x67676d6c)")
        }
        o += 4l

        // 11 i32 hparams
        w.n_vocab = int64(rd_i32(bytes, o)); o += 4l
        let n_audio_ctx = int64(rd_i32(bytes, o)); o += 4l
        let n_audio_state = int64(rd_i32(bytes, o)); o += 4l
        let n_audio_head = int64(rd_i32(bytes, o)); o += 4l
        let n_audio_layer = int64(rd_i32(bytes, o)); o += 4l
        w.n_text_ctx = int64(rd_i32(bytes, o)); o += 4l
        w.n_text_state = int64(rd_i32(bytes, o)); o += 4l
        w.n_text_head = int64(rd_i32(bytes, o)); o += 4l
        w.n_text_layer = int64(rd_i32(bytes, o)); o += 4l
        let n_mels = int64(rd_i32(bytes, o)); o += 4l
        let ftype = rd_i32(bytes, o) % 1000; o += 4l
        if (ftype != GGML_TYPE_F32 && ftype != GGML_TYPE_F16) {
            panic("dasLLAMA whisper: unsupported ftype {ftype} (only f32/f16 bins)")
        }

        // mel filterbank
        let filt_mel = int64(rd_i32(bytes, o)); o += 4l
        let filt_fft = int64(rd_i32(bytes, o)); o += 4l
        if (filt_mel != n_mels || filt_fft != AUDIO_N_FFT / 2l + 1l) {
            panic("dasLLAMA whisper: filterbank is {filt_mel}x{filt_fft}, want {n_mels}x{AUDIO_N_FFT / 2l + 1l}")
        }
        w.filters |> resize(int(filt_mel * filt_fft))
        for (i in range64(filt_mel * filt_fft)) {
            w.filters[i] = rd_f32(bytes, o + i * 4l)
        }
        o += filt_mel * filt_fft * 4l

        // vocab: raw byte tokens; hparams tail ids (specials/timestamps) have no bytes
        let n_vocab_file = int64(rd_i32(bytes, o)); o += 4l
        w.vocab |> resize(int(w.n_vocab))
        for (i in range64(n_vocab_file)) {
            let len = int64(rd_u32(bytes, o)); o += 4l
            w.vocab[i] = bytes_str(bytes, o, len)
            o += len
        }

        // special-token id math (whisper_vocab defaults + multilingual shift)
        w.multilingual = w.n_vocab >= 51865l
        w.n_lang = w.n_vocab - 51765l - (w.multilingual ? 1l : 0l)
        w.tok_eot = 50256
        w.tok_sot = 50257
        w.tok_translate = 50357
        w.tok_transcribe = 50358
        w.tok_solm = 50359
        w.tok_prev = 50360
        w.tok_nosp = 50361
        w.tok_not = 50362
        w.tok_beg = 50363
        if (w.multilingual) {
            w.tok_eot++
            w.tok_sot++
            let dt = int(w.n_lang) - 98
            w.tok_translate += dt
            w.tok_transcribe += dt
            w.tok_solm += dt
            w.tok_prev += dt
            w.tok_nosp += dt
            w.tok_not += dt
            w.tok_beg += dt
        }
        w.tok_space = -1
        for (i in range64(n_vocab_file)) {
            if (w.vocab[i] == " ") {
                w.tok_space = int(i)
                break
            }
        }

        // tensor directory: records until EOF, data immediately after each name
        var recs : table<string; WTensorRec>
        while (o + 12l <= n_bytes) {
            let nd = rd_i32(bytes, o)
            let nl = int64(rd_i32(bytes, o + 4l))
            let tt = rd_i32(bytes, o + 8l)
            o += 12l
            if (tt != GGML_TYPE_F32 && tt != GGML_TYPE_F16) {
                panic("dasLLAMA whisper: unsupported tensor type {tt} (only f32/f16 bins)")
            }
            var ne = 1l
            for (_i in range(nd)) {
                ne *= int64(rd_i32(bytes, o))
                o += 4l
            }
            let name = bytes_str(bytes, o, nl)
            o += nl
            recs[name] = WTensorRec(ttype = tt, n_elem = ne, off = o)
            o += ne * (tt == GGML_TYPE_F32 ? 4l : 2l)
        }

        // encoder tower -> AudioTower blob (same layout the qwen2a loader builds)
        var t = AudioTower()
        t.n_mel = n_mels
        t.d_model = n_audio_state
        t.n_head = n_audio_head
        t.n_layer = n_audio_layer
        t.n_ff = 4l * n_audio_state
        t.n_ctx = n_audio_ctx
        t.proj_dim = 0l
        t.gelu_tanh = true
        let d = t.d_model
        let ff = t.n_ff
        var oe = 0l
        t.conv1_w_off = oe; oe += d * 3l * t.n_mel
        t.conv1_b_off = oe; oe += d
        t.conv2_w_off = oe; oe += d * 3l * d
        t.conv2_b_off = oe; oe += d
        t.pos_off = oe; oe += t.n_ctx * d
        t.layers_off = oe
        t.layer_stride = enc_layer_stride(d, ff)
        oe += t.n_layer * t.layer_stride
        t.lnp_w_off = oe; oe += d
        t.lnp_b_off = oe; oe += d
        t.proj_w_off = oe
        t.proj_b_off = oe
        t.fblob |> resize(int(oe))

        wt_read_conv_permuted(recs, bytes, "encoder.conv1.weight", t.fblob, t.conv1_w_off, d, t.n_mel)
        wt_read(recs, bytes, "encoder.conv1.bias", t.fblob, t.conv1_b_off, d)
        wt_read_conv_permuted(recs, bytes, "encoder.conv2.weight", t.fblob, t.conv2_w_off, d, d)
        wt_read(recs, bytes, "encoder.conv2.bias", t.fblob, t.conv2_b_off, d)
        wt_read(recs, bytes, "encoder.positional_embedding", t.fblob, t.pos_off, t.n_ctx * d)
        for (l in range64(t.n_layer)) {
            let lo = enc_layer_offsets(t, l)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn_ln.weight", t.fblob, lo.ln1_w, d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn_ln.bias", t.fblob, lo.ln1_b, d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn.query.weight", t.fblob, lo.q_w, d * d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn.query.bias", t.fblob, lo.q_b, d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn.key.weight", t.fblob, lo.k_w, d * d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn.value.weight", t.fblob, lo.v_w, d * d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn.value.bias", t.fblob, lo.v_b, d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn.out.weight", t.fblob, lo.o_w, d * d)
            wt_read(recs, bytes, "encoder.blocks.{l}.attn.out.bias", t.fblob, lo.o_b, d)
            wt_read(recs, bytes, "encoder.blocks.{l}.mlp_ln.weight", t.fblob, lo.ln2_w, d)
            wt_read(recs, bytes, "encoder.blocks.{l}.mlp_ln.bias", t.fblob, lo.ln2_b, d)
            wt_read(recs, bytes, "encoder.blocks.{l}.mlp.0.weight", t.fblob, lo.fc1_w, ff * d)
            wt_read(recs, bytes, "encoder.blocks.{l}.mlp.0.bias", t.fblob, lo.fc1_b, ff)
            wt_read(recs, bytes, "encoder.blocks.{l}.mlp.2.weight", t.fblob, lo.fc2_w, d * ff)
            wt_read(recs, bytes, "encoder.blocks.{l}.mlp.2.bias", t.fblob, lo.fc2_b, d)
        }
        wt_read(recs, bytes, "encoder.ln_post.weight", t.fblob, t.lnp_w_off, d)
        wt_read(recs, bytes, "encoder.ln_post.bias", t.fblob, t.lnp_b_off, d)
        w.enc <- t

        // decoder blob
        let dd = w.n_text_state
        var od = 0l
        w.d_pe_off = od; od += w.n_text_ctx * dd
        w.d_te_off = od; od += w.n_vocab * dd
        w.dlayers_off = od
        w.dlayer_stride = dec_layer_stride(dd)
        od += w.n_text_layer * w.dlayer_stride
        w.d_ln_w_off = od; od += dd
        w.d_ln_b_off = od; od += dd
        w.dblob |> resize(int(od))

        wt_read(recs, bytes, "decoder.positional_embedding", w.dblob, w.d_pe_off, w.n_text_ctx * dd)
        wt_read(recs, bytes, "decoder.token_embedding.weight", w.dblob, w.d_te_off, w.n_vocab * dd)
        for (l in range64(w.n_text_layer)) {
            let lo = dec_layer_offsets(w, l)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn_ln.weight", w.dblob, lo.ln1_w, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn_ln.bias", w.dblob, lo.ln1_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn.query.weight", w.dblob, lo.q_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn.query.bias", w.dblob, lo.q_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn.key.weight", w.dblob, lo.k_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn.value.weight", w.dblob, lo.v_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn.value.bias", w.dblob, lo.v_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn.out.weight", w.dblob, lo.o_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.attn.out.bias", w.dblob, lo.o_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn_ln.weight", w.dblob, lo.cln_w, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn_ln.bias", w.dblob, lo.cln_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn.query.weight", w.dblob, lo.cq_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn.query.bias", w.dblob, lo.cq_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn.key.weight", w.dblob, lo.ck_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn.value.weight", w.dblob, lo.cv_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn.value.bias", w.dblob, lo.cv_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn.out.weight", w.dblob, lo.co_w, dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.cross_attn.out.bias", w.dblob, lo.co_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.mlp_ln.weight", w.dblob, lo.ln2_w, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.mlp_ln.bias", w.dblob, lo.ln2_b, dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.mlp.0.weight", w.dblob, lo.fc1_w, 4l * dd * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.mlp.0.bias", w.dblob, lo.fc1_b, 4l * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.mlp.2.weight", w.dblob, lo.fc2_w, dd * 4l * dd)
            wt_read(recs, bytes, "decoder.blocks.{l}.mlp.2.bias", w.dblob, lo.fc2_b, dd)
        }
        wt_read(recs, bytes, "decoder.ln.weight", w.dblob, w.d_ln_w_off, dd)
        wt_read(recs, bytes, "decoder.ln.bias", w.dblob, w.d_ln_b_off, dd)
    }
    fclose(f)
    return <- w
}

// ===== encoder =====

//! Whisper encoder over one 30 s mel window: the shared tower core (conv frontend + pos +
//! pre-LN blocks) + ln_post. Output lands in ``s.xb``: ``n_ctx × d_model`` — the memory the
//! decoder's cross-attention reads (via whisper_cross_kv).
def whisper_encode(t : AudioTower; var s : EncoderState; mel : MelChunk) {
    audio_encode_blocks(t, s, mel)
    layernorm_batch(s.xb, s.x, t.fblob, t.lnp_w_off, t.lnp_b_off, t.d_model, t.n_ctx, t.eps)
}

// ===== decoder =====

//! Decoder scratch + caches, sized once per model and reused across windows. Self-attn K/V
//! caches and the per-window cross-attention memory are head-major; K is stored TRANSPOSED
//! (``[hs][T]``) and pre-scaled by hs^-0.25 so attention scores are one gemm per head.
struct DecoderState {
    n_past : int64
    kcache : array<float>   // [L][H][hs][Tmax]
    vcache : array<float>   // [L][H][Tmax][hs]
    kx : array<float>       // [L][H][hs][Ta] cross keys (from the encoder output, per window)
    vx : array<float>       // [L][H][Ta][hs]
    ckv_tmp : array<float>  // [Ta × d] cross k/v staging (token-major projection out)
    x : array<float>        // residual [ncap × d]
    xb : array<float>       // norm out [ncap × d]
    xb2 : array<float>      // attention scatter out [ncap × d]
    qq : array<float>       // [ncap × d]
    kk : array<float>
    vv : array<float>
    h : array<float>        // mlp hidden [ncap × 4d]
    hp : array<float>       // per-head q/out packs: [H × 2 × ncap × hs]
    att : array<float>      // per-head scores [H × ncap × max(Tmax, Ta)]
    x1 : array<float>       // [d] last-row staging for the tied-logits GEMV
    logits : array<float>   // [n_vocab]
}

def make_decoder_state(w : WhisperModel) : DecoderState {
    let d = w.n_text_state
    let hh = w.n_text_head
    let hs = d / hh
    let tmax = w.n_text_ctx
    let ta = w.enc.n_ctx
    let ncap = tmax
    var ds = DecoderState()
    ds.kcache |> resize(int(w.n_text_layer * d * tmax))
    ds.vcache |> resize(int(w.n_text_layer * d * tmax))
    ds.kx |> resize(int(w.n_text_layer * d * ta))
    ds.vx |> resize(int(w.n_text_layer * d * ta))
    ds.ckv_tmp |> resize(int(ta * d))
    ds.x |> resize(int(ncap * d))
    ds.xb |> resize(int(ncap * d))
    ds.xb2 |> resize(int(ncap * d))
    ds.qq |> resize(int(ncap * d))
    ds.kk |> resize(int(ncap * d))
    ds.vv |> resize(int(ncap * d))
    ds.h |> resize(int(ncap * 4l * d))
    ds.hp |> resize(int(hh * 2l * ncap * hs))
    ds.att |> resize(int(hh * ncap * max(tmax, ta)))
    ds.x1 |> resize(int(d))
    ds.logits |> resize(int(w.n_vocab))
    return <- ds
}

//! Precompute the cross-attention memory for one encoded window (``enc_out`` =
//! whisper_encode's ``s.xb``, ``n_ctx × d``): per layer K = W_k·enc (no bias, pre-scaled
//! hs^-0.25), V = W_v·enc + b — whisper.cpp's build_graph_cross. Resets the sequence.
def whisper_cross_kv(w : WhisperModel; var ds : DecoderState; enc_out : array<float>) {
    let d = w.n_text_state
    let hh = w.n_text_head
    let hs = d / hh
    let ta = w.enc.n_ctx
    let kscale = 1.0 / sqrt(sqrt(float(hs)))
    for (l in range64(w.n_text_layer)) {
        let lo = dec_layer_offsets(w, l)
        mm_blob_b(ds.ckv_tmp, w.dblob, lo.ck_w, enc_out, d, d, ta)
        for (h in range64(hh)) {
            let base = ((l * hh + h) * hs) * ta
            for (t in range64(ta)) {
                for (j in range64(hs)) {
                    ds.kx[base + j * ta + t] = ds.ckv_tmp[t * d + h * hs + j] * kscale
                }
            }
        }
        mm_blob_b(ds.ckv_tmp, w.dblob, lo.cv_w, enc_out, d, d, ta)
        add_bias_rows(ds.ckv_tmp, w.dblob, lo.cv_b, d, ta)
        for (h in range64(hh)) {
            let base = ((l * hh + h) * ta) * hs
            for (t in range64(ta)) {
                for (j in range64(hs)) {
                    ds.vx[base + t * hs + j] = ds.ckv_tmp[t * d + h * hs + j]
                }
            }
        }
    }
    ds.n_past = 0l
}

def private scale_inplace(var x : array<float>; n : int64; s : float) {
    for (i in range64(n)) {
        x[i] *= s
    }
}

// Self-attention over the K/V caches, causal (row r sees positions 0..p0+r), parallel over
// heads. Scores need no extra scale — q and k rows were pre-scaled hs^-0.25 (whisper.cpp
// order). The caches are gemm'd at full Tmax width; softmax is row-length-limited and the
// tail probabilities are zeroed, so stale columns never contribute.
def private dec_self_attn(w : WhisperModel; var ds : DecoderState; l, n, p0 : int64) {
    let d = w.n_text_state
    let hh = w.n_text_head
    let hs = d / hh
    let tmax = w.n_text_ctx
    let tbig = max(tmax, w.enc.n_ctx)
    unsafe {
        let qp = reinterpret<float const?>(addr(ds.qq[0]))
        let kcp = reinterpret<float const?>(addr(ds.kcache[0]))
        let vcp = reinterpret<float const?>(addr(ds.vcache[0]))
        var hpp = addr(ds.hp[0])
        var attp = addr(ds.att[0])
        var aop = addr(ds.xb2[0])
        let ncap = w.n_text_ctx
        maybe_parallel_for(0, int(hh), get_dispatch_lanes()) $(hb, he) {
            unsafe {
                for (h in range(hb, he)) {
                    let hoff = int64(h) * hs
                    var qh = hpp + int64(h) * 2l * ncap * hs
                    var oh = qh + ncap * hs
                    for (r in range64(n)) {
                        for (j in range64(hs)) {
                            qh[r * hs + j] = qp[r * d + hoff + j]
                        }
                    }
                    let kt = kcp + (l * hh + int64(h)) * hs * tmax
                    let vh = vcp + (l * hh + int64(h)) * tmax * hs
                    var ah = attp + int64(h) * ncap * tbig
                    for (i in range64(n * tmax)) {
                        ah[i] = 0.0
                    }
                    gemm_f32(ah, qh, kt, n, hs, tmax)
                    for (r in range64(n)) {
                        var row = ah + r * tmax
                        let len = p0 + r + 1l
                        softmax(row, len)
                        for (i in range64(len, tmax)) {
                            row[i] = 0.0
                        }
                    }
                    for (i in range64(n * hs)) {
                        oh[i] = 0.0
                    }
                    gemm_f32(oh, ah, vh, n, tmax, hs)
                    for (r in range64(n)) {
                        for (j in range64(hs)) {
                            aop[r * d + hoff + j] = oh[r * hs + j]
                        }
                    }
                }
            }
        }
    }
}

// Cross-attention against the per-window kx/vx memory: non-causal over all Ta positions,
// scores scaled hs^-0.25 before softmax (the other hs^-0.25 half lives in the pre-scaled
// keys — whisper.cpp's soft_max_ext(KQ, scale) split).
def private dec_cross_attn(w : WhisperModel; var ds : DecoderState; l, n : int64) {
    let d = w.n_text_state
    let hh = w.n_text_head
    let hs = d / hh
    let ta = w.enc.n_ctx
    let tbig = max(w.n_text_ctx, ta)
    let sm_scale = 1.0 / sqrt(sqrt(float(hs)))
    unsafe {
        let qp = reinterpret<float const?>(addr(ds.qq[0]))
        let kxp = reinterpret<float const?>(addr(ds.kx[0]))
        let vxp = reinterpret<float const?>(addr(ds.vx[0]))
        var hpp = addr(ds.hp[0])
        var attp = addr(ds.att[0])
        var aop = addr(ds.xb2[0])
        let ncap = w.n_text_ctx
        maybe_parallel_for(0, int(hh), get_dispatch_lanes()) $(hb, he) {
            unsafe {
                for (h in range(hb, he)) {
                    let hoff = int64(h) * hs
                    var qh = hpp + int64(h) * 2l * ncap * hs
                    var oh = qh + ncap * hs
                    for (r in range64(n)) {
                        for (j in range64(hs)) {
                            qh[r * hs + j] = qp[r * d + hoff + j]
                        }
                    }
                    let kt = kxp + (l * hh + int64(h)) * hs * ta
                    let vh = vxp + (l * hh + int64(h)) * ta * hs
                    var ah = attp + int64(h) * ncap * tbig
                    for (i in range64(n * ta)) {
                        ah[i] = 0.0
                    }
                    gemm_f32(ah, qh, kt, n, hs, ta)
                    for (r in range64(n)) {
                        var row = ah + r * ta
                        for (i in range64(ta)) {
                            row[i] *= sm_scale
                        }
                        softmax(row, ta)
                    }
                    for (i in range64(n * hs)) {
                        oh[i] = 0.0
                    }
                    gemm_f32(oh, ah, vh, n, ta, hs)
                    for (r in range64(n)) {
                        for (j in range64(hs)) {
                            aop[r * d + hoff + j] = oh[r * hs + j]
                        }
                    }
                }
            }
        }
    }
}

//! Decode a batch of tokens at positions n_past..n_past+n-1 (prompt prefill and single-step
//! generation share this path). Leaves next-token logits (for the LAST row, tied token
//! embedding) in ``ds.logits`` and advances ``ds.n_past``.
def whisper_decode_batch(w : WhisperModel; var ds : DecoderState; tokens : array<int> | #) {
    let n = int64(length(tokens))
    let d = w.n_text_state
    let hh = w.n_text_head
    let hs = d / hh
    let tmax = w.n_text_ctx
    let p0 = ds.n_past
    if (n <= 0l) {
        panic("whisper_decode_batch: empty batch")
    }
    if (p0 + n > tmax) {
        panic("whisper_decode_batch: {p0}+{n} tokens exceed n_text_ctx {tmax}")
    }

    // token embedding + learned absolute position rows
    for (r in range64(n)) {
        let te = w.d_te_off + int64(tokens[int(r)]) * d
        let pe = w.d_pe_off + (p0 + r) * d
        for (j in range64(d)) {
            ds.x[r * d + j] = w.dblob[te + j] + w.dblob[pe + j]
        }
    }

    let kq_scale = 1.0 / sqrt(sqrt(float(hs)))
    for (l in range64(w.n_text_layer)) {
        let lo = dec_layer_offsets(w, l)

        // self-attention (q and k pre-scaled hs^-0.25, k/v appended to the caches)
        layernorm_batch(ds.xb, ds.x, w.dblob, lo.ln1_w, lo.ln1_b, d, n, w.eps)
        mm_blob_b(ds.qq, w.dblob, lo.q_w, ds.xb, d, d, n)
        add_bias_rows(ds.qq, w.dblob, lo.q_b, d, n)
        scale_inplace(ds.qq, n * d, kq_scale)
        mm_blob_b(ds.kk, w.dblob, lo.k_w, ds.xb, d, d, n)
        scale_inplace(ds.kk, n * d, kq_scale)
        mm_blob_b(ds.vv, w.dblob, lo.v_w, ds.xb, d, d, n)
        add_bias_rows(ds.vv, w.dblob, lo.v_b, d, n)
        for (r in range64(n)) {
            for (h in range64(hh)) {
                for (j in range64(hs)) {
                    ds.kcache[((l * hh + h) * hs + j) * tmax + p0 + r] = ds.kk[r * d + h * hs + j]
                    ds.vcache[((l * hh + h) * tmax + p0 + r) * hs + j] = ds.vv[r * d + h * hs + j]
                }
            }
        }
        dec_self_attn(w, ds, l, n, p0)
        mm_blob_b(ds.xb, w.dblob, lo.o_w, ds.xb2, d, d, n)
        add_bias_rows(ds.xb, w.dblob, lo.o_b, d, n)
        add_inplace_rows(ds.x, ds.xb, n * d)

        // cross-attention (q unscaled; keys pre-scaled; softmax applies the other half)
        layernorm_batch(ds.xb, ds.x, w.dblob, lo.cln_w, lo.cln_b, d, n, w.eps)
        mm_blob_b(ds.qq, w.dblob, lo.cq_w, ds.xb, d, d, n)
        add_bias_rows(ds.qq, w.dblob, lo.cq_b, d, n)
        dec_cross_attn(w, ds, l, n)
        mm_blob_b(ds.xb, w.dblob, lo.co_w, ds.xb2, d, d, n)
        add_bias_rows(ds.xb, w.dblob, lo.co_b, d, n)
        add_inplace_rows(ds.x, ds.xb, n * d)

        // mlp
        layernorm_batch(ds.xb, ds.x, w.dblob, lo.ln2_w, lo.ln2_b, d, n, w.eps)
        mm_blob_b(ds.h, w.dblob, lo.fc1_w, ds.xb, d, 4l * d, n)
        add_bias_rows(ds.h, w.dblob, lo.fc1_b, 4l * d, n)
        gelu_tanh_lut(ds.h, n * 4l * d)
        mm_blob_b(ds.xb, w.dblob, lo.fc2_w, ds.h, 4l * d, d, n)
        add_bias_rows(ds.xb, w.dblob, lo.fc2_b, d, n)
        add_inplace_rows(ds.x, ds.xb, n * d)
    }
    ds.n_past += n

    // final LN, then tied-embedding logits for the last row only (greedy single decoder)
    layernorm_batch(ds.xb, ds.x, w.dblob, w.d_ln_w_off, w.d_ln_b_off, d, n, w.eps)
    for (j in range64(d)) {
        ds.x1[j] = ds.xb[(n - 1l) * d + j]
    }
    mm_blob_b(ds.logits, w.dblob, w.d_te_off, ds.x1, d, w.n_vocab, 1l)
}

// ===== greedy driver (whisper_full's single-decoder temp-0 path, fallback disabled) =====

let private NEG_INF_LOGIT = -1e30
let private MAX_INITIAL_TS = 1.0    // whisper.cpp default: first timestamp can't exceed 1 s

// driver trace (debug rail, set_audio_encode_ref_dir's sibling): per-window seek/no-speech
// state and every sampled (id, tid, plog)
var private g_whisper_trace = false

def set_whisper_trace(on : bool) {
    g_whisper_trace = on
}

//! One transcription segment: [t0, t1] in centiseconds (10 ms mel-frame units), the text,
//! the raw token ids (timestamp tokens and eot included, whisper.cpp's result_all shape), and
//! the mean per-token log-probability (greedy plog under the pre-force-ts normalizer) — a
//! confidence signal, more negative = less certain.
struct TranscribeSegment {
    t0 : int64
    t1 : int64
    text : string
    tokens : array<int>
    avg_logprob : float = 0.0
}

// One sampled token: greedy argmax id + the most probable timestamp token (whisper.cpp's
// token_data.tid — segment boundaries read it even off text tokens).
struct private SampledTok {
    id : int
    tid : int
    plog : float
}

// whisper.cpp's whisper_process_logits filter suite, in its exact order. ``n_sampled`` /
// ``last_id`` / ``penult_id`` describe the window's sampled-so-far state (pairs rule),
// ``has_ts``/``seek_delta`` drive the non-decreasing rule.
def private whisper_filter_logits(w : WhisperModel; var logits : array<float>; no_timestamps : bool;
                                  n_sampled : int; last_id, penult_id : int; has_ts : bool; seek_delta : int64) {
    let is_initial = n_sampled == 0
    if (is_initial) {                    // suppress_blank (CLI default true)
        logits[w.tok_eot] = NEG_INF_LOGIT
        if (w.tok_space >= 0) {
            logits[w.tok_space] = NEG_INF_LOGIT
        }
    }
    logits[w.tok_not] = NEG_INF_LOGIT
    if (no_timestamps) {
        for (i in range(w.tok_beg, int(w.n_vocab))) {
            logits[i] = NEG_INF_LOGIT
        }
    }
    logits[w.tok_sot] = NEG_INF_LOGIT
    logits[w.tok_nosp] = NEG_INF_LOGIT
    logits[w.tok_solm] = NEG_INF_LOGIT   // tdrz disabled
    logits[w.tok_translate] = NEG_INF_LOGIT
    logits[w.tok_transcribe] = NEG_INF_LOGIT
    logits[w.tok_prev] = NEG_INF_LOGIT
    for (i in range(100)) {              // g_lang.size() is fixed at 100 in whisper.cpp
        logits[w.tok_sot + 1 + i] = NEG_INF_LOGIT
    }
    if (no_timestamps) {
        return
    }

    // timestamps appear in pairs, except directly before eot
    let last_was_ts = n_sampled > 0 && last_id >= w.tok_beg
    let penult_was_ts = n_sampled < 2 || penult_id >= w.tok_beg
    if (last_was_ts) {
        if (penult_was_ts) {
            for (i in range(w.tok_beg, int(w.n_vocab))) {
                logits[i] = NEG_INF_LOGIT
            }
        } else {
            for (i in range(w.tok_eot)) {
                logits[i] = NEG_INF_LOGIT
            }
        }
    }

    // the initial timestamp can't exceed MAX_INITIAL_TS
    if (is_initial) {
        let precision = 30.0 / float(w.enc.n_ctx)
        let tid0 = int(floor(MAX_INITIAL_TS / precision + 0.5))
        for (i in range(w.tok_beg + tid0 + 1, int(w.n_vocab))) {
            logits[i] = NEG_INF_LOGIT
        }
    }

    // condition timestamps to be non-decreasing within the window
    if (has_ts) {
        let tid0 = int(seek_delta / 2l)
        for (i in range(w.tok_beg, min(w.tok_beg + tid0, int(w.n_vocab)))) {
            logits[i] = NEG_INF_LOGIT
        }
    }

}

// the last process_logits rule, applied AFTER the logprob normalizer is captured: if the
// probability mass over timestamps beats every text token, force a timestamp. logprob
// comparison == raw-logit comparison (log_softmax is a monotone shift).
def private whisper_force_ts_rule(w : WhisperModel; var logits : array<float>) {
    var ts_max = NEG_INF_LOGIT
    for (i in range(w.tok_beg, int(w.n_vocab))) {
        ts_max = max(ts_max, logits[i])
    }
    if (ts_max > NEG_INF_LOGIT * 0.5) {
        var ts_lse = 0.0
        for (i in range(w.tok_beg, int(w.n_vocab))) {
            ts_lse += exp(logits[i] - ts_max)
        }
        let ts_logsumexp = log(ts_lse) + ts_max
        var text_max = NEG_INF_LOGIT
        for (i in range(w.tok_beg)) {
            text_max = max(text_max, logits[i])
        }
        if (ts_logsumexp > text_max) {
            for (i in range(w.tok_beg)) {
                logits[i] = NEG_INF_LOGIT
            }
        }
    }
}

// log-sum-exp over the current logits — the logprob normalizer whisper.cpp captures between
// the main filter suite and the force-timestamp rule (plog = logit − this)
def private logits_lse(logits : array<float>) : float {
    var m = NEG_INF_LOGIT
    for (v in logits) {
        m = max(m, v)
    }
    var sum = 0.0
    for (v in logits) {
        sum += exp(v - m)
    }
    return log(sum) + m
}

// greedy argmax over all filtered logits + argmax over the timestamp region (tid); plog uses
// the pre-force-ts normalizer ``lse`` (the sampled id is unbanned in both phases)
def private sample_greedy(w : WhisperModel; logits : array<float>; lse : float) : SampledTok {
    var r = SampledTok(id = 0, tid = w.tok_beg)
    var bestv = logits[0]
    for (i in range(1, length(logits))) {
        if (logits[i] > bestv) {
            bestv = logits[i]
            r.id = i
        }
    }
    var bestts = logits[w.tok_beg]
    for (i in range(w.tok_beg + 1, length(logits))) {
        if (logits[i] > bestts) {
            bestts = logits[i]
            r.tid = i
        }
    }
    if (r.id >= w.tok_beg) {
        r.tid = r.id
    }
    r.plog = logits[r.id] - lse
    return r
}

// softmax probability of one token id over RAW (pre-filter) logits — the no-speech gate
// reads p[nosp] off the prompt decode before any filtering
def private token_prob(logits : array<float>; id : int) : float {
    var m = NEG_INF_LOGIT
    for (v in logits) {
        m = max(m, v)
    }
    var sum = 0.0
    for (v in logits) {
        sum += exp(v - m)
    }
    return exp(logits[id] - m) / sum
}

// Build and emit one segment off toks[i0..i1) at [t0, t1] — text = concat of the text-range
// token bytes; a segment with no text (bare timestamps) is dropped, whisper.cpp's rule.
def private emit_segment(w : WhisperModel; toks : array<SampledTok>; i0, i1 : int; t0, t1 : int64;
                         blk : block<(seg : TranscribeSegment)>) {
    let text = build_string() $(writer) {
        for (j in range(i0, i1)) {
            if (toks[j].id < w.tok_eot) {
                writer |> write(w.vocab[toks[j].id])
            }
        }
    }
    if (empty(text)) {
        return
    }
    var seg = TranscribeSegment(t0 = t0, t1 = t1, text = text)
    seg.tokens |> reserve(i1 - i0)
    var plog_sum = 0.0
    for (j in range(i0, i1)) {
        seg.tokens |> push(toks[j].id)
        plog_sum += toks[j].plog
    }
    seg.avg_logprob = plog_sum / float(i1 - i0)
    blk |> invoke(seg)
}

// The window loop (whisper_full's single-decoder temp-0 path, no_context): 30 s windows
// advanced by decoded timestamps (or whole windows when no_timestamps), whisper.cpp's
// logit-filter suite and segment-splitting rules. Emits segments through ``blk`` as each
// window completes, offset by ``t_base`` centiseconds; ``complete_only`` stops before a
// window whose 3000 mel frames aren't all real audio (the drain path). Returns the mel
// frames consumed (the final seek, clamped to n_len_org).
def private transcribe_mel_windows(w : WhisperModel; var es : EncoderState; var ds : DecoderState;
                                   mel : WhisperMel; lang_id : int; no_timestamps, translate : bool;
                                   t_base : int64; complete_only : bool;
                                   blk : block<(seg : TranscribeSegment)>) : int64 {
    let seek_end = mel.n_len_org
    let delta_min = 10l                  // ignore anything under 100 ms
    var seek = 0l
    var step : array<int>
    step |> resize(1)
    let n_max = int(w.n_text_ctx / 2l) - 4

    while (seek + delta_min < seek_end && (!complete_only || seek + AUDIO_CHUNK_FRAMES <= mel.n_len_org)) {
        let win <- whisper_mel_window(mel, seek)
        whisper_encode(w.enc, es, win)
        whisper_cross_kv(w, ds, es.xb)

        var prompt : array<int>
        prompt |> reserve(4)
        prompt |> push(w.tok_sot)
        if (w.multilingual) {
            prompt |> push(w.tok_sot + 1 + lang_id)
            prompt |> push(translate ? w.tok_translate : w.tok_transcribe)
        }
        if (no_timestamps) {
            prompt |> push(w.tok_not)
        }
        whisper_decode_batch(w, ds, prompt)
        let no_speech_prob = token_prob(ds.logits, w.tok_nosp)

        var toks : array<SampledTok>
        toks |> reserve(n_max)
        var seek_delta = 100l * 30l      // full window unless a timestamp moves it
        var has_ts = false
        var result_len = 0
        for (i in range(n_max)) {
            let n_sampled = length(toks)
            let last_id = n_sampled > 0 ? toks[n_sampled - 1].id : -1
            let penult_id = n_sampled > 1 ? toks[n_sampled - 2].id : -1
            whisper_filter_logits(w, ds.logits, no_timestamps, n_sampled, last_id, penult_id, has_ts, seek_delta)
            let lse = logits_lse(ds.logits)
            if (!no_timestamps) {
                whisper_force_ts_rule(w, ds.logits)
            }
            let t = sample_greedy(w, ds.logits, lse)
            toks |> push(t)
            if (g_whisper_trace) {
                print("  [{i}] id {t.id} tid {t.tid} plog {t.plog} has_ts {has_ts} seek_delta {seek_delta}\n")
            }

            if (t.id > w.tok_beg) {      // timestamp token (strictly above <|0.00|>) moves the window
                let seek_delta_new = 2l * int64(t.id - w.tok_beg)
                if (has_ts && seek_delta > seek_delta_new && result_len < i) {
                    break                // "do not go back in time" — whisper.cpp fails the decoder here
                }
                seek_delta = seek_delta_new
                result_len = i + 1
                has_ts = true
            }
            if (t.id == w.tok_eot || (has_ts && seek + seek_delta + delta_min >= seek_end)) {
                if (result_len == 0 && !no_timestamps && seek + seek_delta + delta_min >= seek_end) {
                    result_len = i + 1
                }
                if (no_timestamps) {     // single_segment/no_timestamps: keep everything
                    result_len = i + 1
                    seek_delta = 100l * 30l
                }
                break
            }
            step[0] = t.id
            whisper_decode_batch(w, ds, step)
        }

        // the no-speech gate: a confident nosp read on the prompt logits + low avg logprob
        // over the kept tokens drops the window's segments (whisper.cpp defaults 0.6 / −1.0)
        var avg_logprobs = NEG_INF_LOGIT
        if (result_len > 0) {
            var sum = 0.0
            for (i in range(result_len)) {
                sum += toks[i].plog
            }
            avg_logprobs = sum / float(result_len)
        }
        let is_no_speech = no_speech_prob > 0.6 && avg_logprobs < -1.0
        if (g_whisper_trace) {
            print("window seek {seek} seek_end {seek_end}: {length(toks)} sampled, result_len {result_len}, seek_delta {seek_delta}, nosp {no_speech_prob}, avg_lp {avg_logprobs}, no_speech {is_no_speech}\n")
        }

        // split [0, result_len) into segments at timestamp tokens (whisper.cpp's emission loop)
        if (result_len > 0 && !is_no_speech) {
            var i0 = 0
            var t0 = seek + 2l * int64(toks[0].tid - w.tok_beg)
            var i = 0
            while (i < result_len) {
                let t = toks[i]
                if (t.id > w.tok_beg) {
                    let t1 = seek + 2l * int64(t.tid - w.tok_beg)
                    emit_segment(w, toks, i0, i + 1, t_base + t0, t_base + t1, blk)
                    t0 = t1
                    while (i + 1 < result_len && toks[i + 1].id > w.tok_beg) {
                        i++
                        t0 = seek + 2l * int64(toks[i].tid - w.tok_beg)
                    }
                    i0 = i + 1
                }
                i++
            }
            emit_segment(w, toks, i0, result_len, t_base + t0, t_base + seek + seek_delta, blk)
        }

        // a window whose kept tokens end text-then-SINGLE-timestamp (no closing pair) covered
        // everything it could hear — skip the entire remaining chunk (whisper.cpp PR #2629)
        let single_ts_ending = (result_len > 1
            && toks[result_len - 2].id < w.tok_beg
            && toks[result_len - 1].id > w.tok_beg)
        if (single_ts_ending) {
            seek_delta = min(seek_end - seek, 100l * 30l)
        }
        seek += seek_delta
    }
    return min(seek, mel.n_len_org)
}

//! Full greedy transcription into a segment array — the probe/test-facing form; the public
//! ``transcribe``/session API below wraps the same window loop. Times in centiseconds.
def whisper_transcribe_run(w : WhisperModel; var es : EncoderState; var ds : DecoderState;
                           samples : array<float> | #; lang : string;
                           no_timestamps : bool = false; translate : bool = false) : array<TranscribeSegment> {
    var segments : array<TranscribeSegment>
    var lang_id = whisper_lang_id(lang)
    let mel <- log_mel_whisper(samples, w.filters, w.enc.n_mel)
    if (lang == "auto") {
        lang_id = whisper_detect_language(w, es, ds, mel)
    } elif (lang_id < 0) {
        panic("dasLLAMA whisper: unknown language '{lang}'")
    }
    transcribe_mel_windows(w, es, ds, mel, lang_id, no_timestamps, translate, 0l, false) $(seg) {
        segments |> push_clone(seg)
    }
    return <- segments
}

// ===== public API: sessions, one-shot, block, and push-chunks feed/drain =====

//! One transcription stream over a loaded model: encoder/decoder scratch, language/task
//! options, and the fed-but-not-yet-transcribed audio (the push-chunks rail). A model serves
//! many sessions.
struct WhisperSession {
    es : EncoderState = EncoderState()
    ds : DecoderState = DecoderState()
    lang : string = "en"
    lang_id : int = -1       // resolved language id; -1 = not yet detected ("auto")
    translate : bool = false
    no_timestamps : bool = false
    pending : array<float>   // fed 16 kHz mono samples awaiting transcription
    t_base : int64           // centiseconds already consumed off the front of the stream
}

def create_session(w : WhisperModel; lang : string = "en") : WhisperSession {
    //! Create a session (encoder + decoder scratch) for ``w``. ``lang`` is the spoken language
    //! ("en", "zh", ... — whisper's g_lang codes), or "auto" to detect it from the first
    //! transcribed audio (multilingual models only; costs one extra encode + prompt decode,
    //! then sticks for the session's lifetime). Set ``session.translate`` for speech-to-English
    //! translation, ``session.no_timestamps`` to disable timestamp decoding.
    var s = WhisperSession(lang = lang)
    if (lang == "auto") {
        if (!w.multilingual) {
            panic("dasLLAMA whisper: lang=\"auto\" needs a multilingual model (this one is English-only)")
        }
    } else {
        s.lang_id = whisper_lang_id(lang)
        if (s.lang_id < 0) {
            panic("dasLLAMA whisper: unknown language '{lang}'")
        }
    }
    s.es <- make_encoder_state(w.enc)
    s.ds <- make_decoder_state(w)
    return <- s
}

//! whisper.cpp's whisper_lang_auto_detect: encode the stream's first 30 s window, decode a
//! bare [sot] prompt, and pick the language token with the highest probability. Returns the
//! g_lang language id.
def whisper_detect_language(w : WhisperModel; var es : EncoderState; var ds : DecoderState;
                            mel : WhisperMel) : int {
    let win <- whisper_mel_window(mel, 0l)
    whisper_encode(w.enc, es, win)
    whisper_cross_kv(w, ds, es.xb)
    var prompt : array<int>
    prompt |> push(w.tok_sot)
    whisper_decode_batch(w, ds, prompt)
    var best = 0
    for (i in range(1, int(w.n_lang))) {   // argmax over raw logits == argmax over their softmax
        if (ds.logits[w.tok_sot + 1 + i] > ds.logits[w.tok_sot + 1 + best]) {
            best = i
        }
    }
    return best
}

// Resolve the session's language id, running auto-detect on the first audio that reaches a
// driver. Detection reuses the session scratch; the main loop re-encodes window 0 (matches
// whisper.cpp, which also pays one extra encode for auto).
def private resolve_lang_id(w : WhisperModel; var s : WhisperSession; mel : WhisperMel) : int {
    if (s.lang_id < 0) {
        s.lang_id = whisper_detect_language(w, s.es, s.ds, mel)
    }
    return s.lang_id
}

def transcribe(w : WhisperModel; var s : WhisperSession; samples : array<float> | #;
               blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe ``samples`` (16 kHz mono f32 PCM), invoking the trailing block per segment as
    //! each 30 s window completes. Segment times are centiseconds. Returns the segment count.
    //! Does not touch the session's fed/pending stream — one-shot and push-chunks coexist.
    var count = 0
    let mel <- log_mel_whisper(samples, w.filters, w.enc.n_mel)
    let lang_id = resolve_lang_id(w, s, mel)
    transcribe_mel_windows(w, s.es, s.ds, mel, lang_id, s.no_timestamps, s.translate, 0l, false) $(seg) {
        count++
        blk |> invoke(seg)
    }
    return count
}

def transcribe(w : WhisperModel; var s : WhisperSession; samples : array<float> | #) : string {
    //! One-shot: transcribe ``samples`` and return the full text (concatenated segments).
    return build_string() $(writer) {
        transcribe(w, s, samples) $(seg) {
            writer |> write(seg.text)
        }
    }
}

def feed(var s : WhisperSession; samples : array<float> | #) {
    //! Push a chunk of 16 kHz mono f32 PCM onto the session's stream. Pair with ``drain``
    //! (transcribe complete 30 s windows) and ``flush`` (transcribe the remaining tail).
    s.pending |> push_from(samples)
}

def drain(w : WhisperModel; var s : WhisperSession; blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe every COMPLETE 30 s window of the fed stream, invoking the block per segment
    //! (times are stream-absolute centiseconds). Consumed audio is dropped from the stream;
    //! anything under a full window stays pending. Returns the segment count — 0 until at
    //! least 30 s is buffered.
    var count = 0
    let mel <- log_mel_whisper(s.pending, w.filters, w.enc.n_mel)
    // no complete window yet -> nothing will transcribe; hold auto-detect for real audio too
    if (int64(length(s.pending)) < AUDIO_CHUNK_FRAMES * AUDIO_HOP) {
        return 0
    }
    let lang_id = resolve_lang_id(w, s, mel)
    let consumed = transcribe_mel_windows(w, s.es, s.ds, mel, lang_id,
                                          s.no_timestamps, s.translate, s.t_base, true) $(seg) {
        count++
        blk |> invoke(seg)
    }
    if (consumed > 0l) {
        let keep = int64(length(s.pending)) - consumed * AUDIO_HOP
        var rest : array<float>
        rest |> resize(int(max(keep, 0l)))
        for (i in range(int(max(keep, 0l)))) {
            rest[i] = s.pending[int(consumed * AUDIO_HOP) + i]
        }
        s.pending <- rest
        s.t_base += consumed
    }
    return count
}

def flush(w : WhisperModel; var s : WhisperSession; blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe everything left on the fed stream (including the sub-30 s tail), then clear
    //! it. The session stays usable — subsequent feeds continue the stream timeline.
    var count = 0
    let mel <- log_mel_whisper(s.pending, w.filters, w.enc.n_mel)
    let lang_id = resolve_lang_id(w, s, mel)
    transcribe_mel_windows(w, s.es, s.ds, mel, lang_id,
                           s.no_timestamps, s.translate, s.t_base, false) $(seg) {
        count++
        blk |> invoke(seg)
    }
    s.t_base += mel.n_len_org
    s.pending |> clear()
    return count
}

//! Token ids -> text (raw byte concat; ids at/above eot have no bytes and are skipped).
def whisper_detokenize(w : WhisperModel; toks : array<int> | #) : string {
    return build_string() $(writer) {
        for (t in toks) {
            if (t < w.tok_eot) {
                writer |> write(w.vocab[t])
            }
        }
    }
}

//! The whisper language codes, in g_lang id order (index == language id).
def whisper_lang_list() : array<string> {
    return <- [
        "en", "zh", "de", "es", "ru", "ko", "fr", "ja", "pt", "tr",
        "pl", "ca", "nl", "ar", "sv", "it", "id", "hi", "fi", "vi",
        "he", "uk", "el", "ms", "cs", "ro", "da", "hu", "ta", "no",
        "th", "ur", "hr", "bg", "lt", "la", "mi", "ml", "cy", "sk",
        "te", "fa", "lv", "bn", "sr", "az", "sl", "kn", "et", "mk",
        "br", "eu", "is", "hy", "ne", "mn", "bs", "kk", "sq", "sw",
        "gl", "mr", "pa", "si", "km", "sn", "yo", "so", "af", "oc",
        "ka", "be", "tg", "sd", "gu", "am", "yi", "lo", "uz", "fo",
        "ht", "ps", "tk", "nn", "mt", "sa", "lb", "my", "bo", "tl",
        "mg", "as", "tt", "haw", "ln", "ha", "ba", "jw", "su", "yue"]
}

//! lang string ("en", "zh", ...) -> whisper language id (g_lang order). -1 when unknown.
def whisper_lang_id(lang : string) : int {
    let langs <- whisper_lang_list()
    for (i in range(length(langs))) {
        if (langs[i] == lang) {
            return i
        }
    }
    return -1
}
