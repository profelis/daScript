options gen2

module dasllama_parakeet shared public

require math
require daslib/fio
require strings
require daslib/strings_boost
require daslib/array_boost
require dasllama/dasllama_math
require dasllama/dasllama_gguf
require dasllama/dasllama_audio
require dasllama/dasllama_quant
require dasllama/dasllama_par

// Parakeet-TDT (NVIDIA FastConformer + LSTM predictor + Token-and-Duration Transducer),
// read from whisper.cpp's converted ggml bin. Oracle = whisper.cpp's in-tree parakeet-cli
// (CPU, -ng); the container/graph/decode rules are transcribed from src/parakeet.cpp —
// see parakeet_plan.md for the full spec and line references.

let PARAKEET_HOP = 160l
let private LOCAL_ATTN_THRESHOLD = 8192l   // beyond this the oracle switches to local attention

//! One decoded TDT token: vocab id, chosen duration (index + frames), the encoder frame it
//! was emitted at, and its (log-)probability under the joint's full-row log-softmax.
struct ParakeetToken {
    id : int
    dur_idx : int
    dur : int
    frame : int64
    p : float
    plog : float
}

struct private PkLayerOffs {
    nf1_w : int64
    nf1_b : int64
    ff1a_w : int64   // 1024 -> 4096
    ff1b_w : int64   // 4096 -> 1024
    nat_w : int64
    nat_b : int64
    bias_u : int64   // [d_head × n_head]
    bias_v : int64
    q_w : int64
    k_w : int64
    v_w : int64
    o_w : int64
    pos_w : int64
    ncv_w : int64
    ncv_b : int64
    pw1_w : int64    // 1024 -> 2048
    dw_w : int64     // [9 × 1024]
    bn_w : int64
    bn_b : int64
    bn_mean : int64
    bn_var : int64
    pw2_w : int64
    nf2_w : int64
    nf2_b : int64
    ff2a_w : int64
    ff2b_w : int64
    nout_w : int64
    nout_b : int64
}

//! A loaded Parakeet-TDT model: hparams, mel filterbank + STFT window from the file, TDT
//! durations, SPM vocab, and every weight fp32 in one blob.
struct ParakeetModel {
    n_vocab : int64
    n_state : int64
    n_head : int64
    n_layer : int64
    n_mel : int64
    n_fft : int64
    subsampling : int64
    n_sub_ch : int64
    n_conv_kernel : int64
    n_pred_dim : int64
    n_pred_layers : int64
    n_durations : int64
    n_max_tokens : int64
    eps : float = 1e-5
    blank_id : int
    durations : array<int>
    filters : array<float>     // [n_mel][n_fb]
    window : array<float>      // STFT window from the file
    vocab : array<string>
    blob : array<float>
    // pre-encode conv stack
    c0_w : int64
    c0_b : int64
    c2_w : int64
    c2_b : int64
    c3_w : int64
    c3_b : int64
    c5_w : int64
    c5_b : int64
    c6_w : int64
    c6_b : int64
    pre_w : int64
    pre_b : int64
    layers_off : int64
    layer_stride : int64
    // prediction network + joint
    embed_off : int64          // [n_vocab+1][pred_dim]
    lstm_ih : array<int64>     // per layer
    lstm_hh : array<int64>
    lstm_b : array<int64>
    joint_enc_w : int64
    joint_enc_b : int64
    joint_pred_w : int64
    joint_pred_b : int64
    joint_net_w : int64
    joint_net_b : int64
    // Q8 fast path (parakeet_quantize): whole-blob Q8_0 image; GEMM regions repacked for the
    // active backend. blob stays resident for the fp32-only reads (norms/biases/convs/LSTM).
    q8 : bool
    qblob : array<int8>
    qscales : array<float>
}

def private pk_layer_offsets(m : ParakeetModel; l : int64) : PkLayerOffs {
    let d = m.n_state
    let ff = 4l * d
    let dh = d / m.n_head
    var o = m.layers_off + l * m.layer_stride
    var r = PkLayerOffs()
    r.nf1_w = o; o += d
    r.nf1_b = o; o += d
    r.ff1a_w = o; o += ff * d
    r.ff1b_w = o; o += d * ff
    r.nat_w = o; o += d
    r.nat_b = o; o += d
    r.bias_u = o; o += dh * m.n_head
    r.bias_v = o; o += dh * m.n_head
    r.q_w = o; o += d * d
    r.k_w = o; o += d * d
    r.v_w = o; o += d * d
    r.o_w = o; o += d * d
    r.pos_w = o; o += d * d
    r.ncv_w = o; o += d
    r.ncv_b = o; o += d
    r.pw1_w = o; o += 2l * d * d
    r.dw_w = o; o += m.n_conv_kernel * d
    r.bn_w = o; o += d
    r.bn_b = o; o += d
    r.bn_mean = o; o += d
    r.bn_var = o; o += d
    r.pw2_w = o; o += d * d
    r.nf2_w = o; o += d
    r.nf2_b = o; o += d
    r.ff2a_w = o; o += ff * d
    r.ff2b_w = o; o += d * ff
    r.nout_w = o; o += d
    r.nout_b = o; o += d
    return r
}

// per-layer blob span: 8 d×d mats (q/k/v/o/pos + pw1(2) + pw2) + 4 ff×d mats + 16
// d-vectors (norms ×8, u/v, bn ×4) + the depthwise kernel
def private pk_layer_stride(d, ff, nk : int64) : int64 => 8l * d * d + 4l * ff * d + 16l * d + nk * d

// repack one GEMM region for the active backend (scales index at woff/32, so woff must be 32-aligned)
def private pk_repack(var m : ParakeetModel; woff, n, d : int64) {
    if (woff % 32l != 0l) {
        panic("parakeet q8: GEMM weight at {woff} is not 32-aligned")
    }
    repack_q8q8_weight(m.qblob, m.qscales, woff, n, d)
}

//! Quantize the encoder/joint GEMM weights to Q8_0 and switch parakeet_encode onto the generated
//! q8q8 kernels (~the decoder's quantize_weights). The conv im2col stack (k=9 taps), depthwise
//! kernels, LSTM, and joint_net stay fp32 — they are a few % of encode and off the q8 shapes.
def parakeet_quantize(var m : ParakeetModel) {
    var qt <- quantize_q8_0(m.blob, int64(length(m.blob)))
    m.qblob <- qt.q
    m.qscales <- qt.scales
    m.q8 = true
    if (select_matmul_backend_for_load()) {
        let d = m.n_state
        let ff = 4l * d
        let nch = m.n_sub_ch
        let w1 = (m.n_mel - 1l) / 2l + 1l
        let w2 = (w1 - 1l) / 2l + 1l
        let w3 = (w2 - 1l) / 2l + 1l
        let feat = w3 * nch                       // pre_w input dim (encode's xf row width)
        pk_repack(m, m.c3_w, nch, nch)
        pk_repack(m, m.c6_w, nch, nch)
        pk_repack(m, m.pre_w, feat, d)
        for (l in range64(m.n_layer)) {
            let lo = pk_layer_offsets(m, l)
            pk_repack(m, lo.ff1a_w, d, ff)
            pk_repack(m, lo.ff1b_w, ff, d)
            pk_repack(m, lo.q_w, d, d)
            pk_repack(m, lo.k_w, d, d)
            pk_repack(m, lo.v_w, d, d)
            pk_repack(m, lo.o_w, d, d)
            pk_repack(m, lo.pos_w, d, d)
            pk_repack(m, lo.pw1_w, d, 2l * d)
            pk_repack(m, lo.pw2_w, d, d)
            pk_repack(m, lo.ff2a_w, d, ff)
            pk_repack(m, lo.ff2b_w, ff, d)
        }
        pk_repack(m, m.joint_enc_w, d, m.n_pred_dim)
    }
}

// mm_blob_b with the q8 route: activation image (xq, xs) pre-quantized by the caller
// (asr_requant_rows_q8) so q/k/v and repeat consumers share one requant.
def private pk_mm(m : ParakeetModel; var y : array<float>; woff : int64; x : array<float>;
                  xq : array<int8>; xs : array<float>; n, d, npos : int64) {
    if (m.q8) {
        array_view(m.qblob, woff, n * d) $(wq : array<int8>#) {
            array_view(m.qscales, woff / 32l, n * d / 32l) $(ws : array<float>#) {
                matmul_q8q8_batch(y, wq, ws, xq, xs, n, d, npos)
            }
        }
    } else {
        mm_blob_b(y, m.blob, woff, x, n, d, npos)
    }
}

// requant-and-multiply for single-consumer activations (scratch grows lazily)
def private pk_mm_rq(m : ParakeetModel; var y : array<float>; woff : int64; x : array<float>;
                     var xq : array<int8>; var xs : array<float>; n, d, npos : int64) {
    if (m.q8) {
        pk_requant(x, n, npos, xq, xs)
    }
    pk_mm(m, y, woff, x, xq, xs, n, d, npos)
}

def private pk_requant(x : array<float>; n, npos : int64; var xq : array<int8>; var xs : array<float>) {
    let need = npos * n
    if (int64(length(xq)) < need) {
        xq |> resize(int(need))
        xs |> resize(int(need / 32l))
    }
    asr_requant_rows_q8(x, n, npos, xq, xs)
}

// ===== bin container =====

// whisper-bin-style tensor records: i32 n_dims, i32 name_len, i32 ftype; i32 dims (ne
// order); name bytes; raw data (f32/f16), unaligned.
struct private PkTensorRec {
    ttype : int
    n_elem : int64
    off : int64
}

def private pk_bytes_str(b : array<uint8> | #; o, n : int64) : string {
    if (n <= 0l) {
        return ""
    }
    var s = ""
    unsafe {
        s = string(temp_array(reinterpret<uint8?>(addr(b[o])), n, type<uint8>))
    }
    return s
}

def private pk_read(recs : table<string; PkTensorRec>; b : array<uint8> | #; name : string;
                    var dst : array<float>; dst_off, n : int64) {
    if (!key_exists(recs, name)) {
        panic("dasLLAMA parakeet: missing tensor '{name}' in model file")
    }
    let r = recs?[name] ?? default<PkTensorRec>
    if (r.n_elem != n) {
        panic("dasLLAMA parakeet: tensor '{name}' has {r.n_elem} elements, want {n}")
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

//! Load a converted Parakeet-TDT ggml bin (convert-parakeet-to-ggml.py output; f32 or f16).
def load_parakeet_model(path : string) : ParakeetModel {
    var m = ParakeetModel()
    let n_bytes = int64(stat(path).size)
    let f = fopen(path, "rb")
    if (f == null) {
        panic("dasLLAMA parakeet: cannot open model '{path}'")
    }
    fmap(f) $(var bytes : array<uint8>#) {
        var o = 0l
        if (rd_u32(bytes, o) != 0x67676d6cu) {
            panic("dasLLAMA parakeet: bad magic in '{path}'")
        }
        o += 4l
        m.n_vocab = int64(rd_i32(bytes, o)); o += 4l
        o += 4l   // n_audio_ctx (unused: full-clip encode)
        m.n_state = int64(rd_i32(bytes, o)); o += 4l
        m.n_head = int64(rd_i32(bytes, o)); o += 4l
        m.n_layer = int64(rd_i32(bytes, o)); o += 4l
        m.n_mel = int64(rd_i32(bytes, o)); o += 4l
        o += 4l   // ftype (per-record types below)
        m.n_fft = int64(rd_i32(bytes, o)); o += 4l
        m.subsampling = int64(rd_i32(bytes, o)); o += 4l
        m.n_sub_ch = int64(rd_i32(bytes, o)); o += 4l
        m.n_conv_kernel = int64(rd_i32(bytes, o)); o += 4l
        m.n_pred_dim = int64(rd_i32(bytes, o)); o += 4l
        m.n_pred_layers = int64(rd_i32(bytes, o)); o += 4l
        m.n_durations = int64(rd_i32(bytes, o)); o += 4l
        m.n_max_tokens = int64(rd_i32(bytes, o)); o += 4l
        m.blank_id = int(m.n_vocab)

        // mel filterbank
        let fb_mel = int64(rd_i32(bytes, o)); o += 4l
        let fb_n = int64(rd_i32(bytes, o)); o += 4l
        if (fb_mel != m.n_mel || fb_n != m.n_fft / 2l + 1l) {
            panic("dasLLAMA parakeet: filterbank is {fb_mel}x{fb_n}, want {m.n_mel}x{m.n_fft / 2l + 1l}")
        }
        m.filters |> resize(int(fb_mel * fb_n))
        for (i in range64(fb_mel * fb_n)) {
            m.filters[i] = rd_f32(bytes, o + i * 4l)
        }
        o += fb_mel * fb_n * 4l

        // STFT window
        let n_window = int64(rd_i32(bytes, o)); o += 4l
        m.window |> resize(int(n_window))
        for (i in range64(n_window)) {
            m.window[i] = rd_f32(bytes, o + i * 4l)
        }
        o += n_window * 4l

        // TDT durations
        m.durations |> resize(int(m.n_durations))
        for (i in range64(m.n_durations)) {
            m.durations[i] = int(rd_u32(bytes, o + i * 4l))
        }
        o += m.n_durations * 4l

        // vocab (SPM pieces; blank = id n_vocab lives outside the table)
        let nv = int64(rd_i32(bytes, o)); o += 4l
        m.vocab |> resize(int(nv))
        for (i in range64(nv)) {
            let len = int64(rd_u32(bytes, o)); o += 4l
            m.vocab[i] = pk_bytes_str(bytes, o, len)
            o += len
        }

        // tensor records
        var recs : table<string; PkTensorRec>
        while (o + 12l <= n_bytes) {
            let n_dims = int64(rd_i32(bytes, o)); o += 4l
            let name_len = int64(rd_i32(bytes, o)); o += 4l
            let ttype = rd_i32(bytes, o); o += 4l
            var n_elem = 1l
            for (_d in range64(n_dims)) {
                n_elem *= int64(rd_i32(bytes, o)); o += 4l
            }
            let name = pk_bytes_str(bytes, o, name_len)
            o += name_len
            recs[name] = PkTensorRec(ttype = ttype, n_elem = n_elem, off = o)
            o += n_elem * (ttype == GGML_TYPE_F32 ? 4l : 2l)
        }

        // blob layout
        let d = m.n_state
        let ff = 4l * d
        let dh = d / m.n_head
        let nch = m.n_sub_ch
        var bo = 0l
        m.c0_w = bo; bo += nch * 9l
        m.c0_b = bo; bo += nch
        m.c2_w = bo; bo += nch * 9l          // depthwise: per-channel 3x3
        m.c2_b = bo; bo += nch
        m.c3_w = bo; bo += nch * nch
        m.c3_b = bo; bo += nch
        m.c5_w = bo; bo += nch * 9l
        m.c5_b = bo; bo += nch
        m.c6_w = bo; bo += nch * nch
        m.c6_b = bo; bo += nch
        let feat = (m.n_mel / m.subsampling) * nch
        m.pre_w = bo; bo += d * feat
        m.pre_b = bo; bo += d
        m.layers_off = bo
        m.layer_stride = pk_layer_stride(d, ff, m.n_conv_kernel)
        bo += m.n_layer * m.layer_stride
        m.embed_off = bo; bo += (m.n_vocab + 1l) * m.n_pred_dim
        let pd = m.n_pred_dim
        for (_l in range64(m.n_pred_layers)) {
            m.lstm_ih |> push(bo); bo += 4l * pd * pd
            m.lstm_hh |> push(bo); bo += 4l * pd * pd
            m.lstm_b |> push(bo); bo += 4l * pd
        }
        m.joint_enc_w = bo; bo += pd * d
        m.joint_enc_b = bo; bo += pd
        m.joint_pred_w = bo; bo += pd * pd
        m.joint_pred_b = bo; bo += pd
        let n_logits = m.n_vocab + 1l + m.n_durations
        m.joint_net_w = bo; bo += n_logits * pd
        m.joint_net_b = bo; bo += n_logits
        m.blob |> resize(int(bo))

        pk_read(recs, bytes, "encoder.pre_encode.conv.0.weight", m.blob, m.c0_w, nch * 9l)
        pk_read(recs, bytes, "encoder.pre_encode.conv.0.bias", m.blob, m.c0_b, nch)
        pk_read(recs, bytes, "encoder.pre_encode.conv.2.weight", m.blob, m.c2_w, nch * 9l)
        pk_read(recs, bytes, "encoder.pre_encode.conv.2.bias", m.blob, m.c2_b, nch)
        pk_read(recs, bytes, "encoder.pre_encode.conv.3.weight", m.blob, m.c3_w, nch * nch)
        pk_read(recs, bytes, "encoder.pre_encode.conv.3.bias", m.blob, m.c3_b, nch)
        pk_read(recs, bytes, "encoder.pre_encode.conv.5.weight", m.blob, m.c5_w, nch * 9l)
        pk_read(recs, bytes, "encoder.pre_encode.conv.5.bias", m.blob, m.c5_b, nch)
        pk_read(recs, bytes, "encoder.pre_encode.conv.6.weight", m.blob, m.c6_w, nch * nch)
        pk_read(recs, bytes, "encoder.pre_encode.conv.6.bias", m.blob, m.c6_b, nch)
        pk_read(recs, bytes, "encoder.pre_encode.out.weight", m.blob, m.pre_w, d * feat)
        pk_read(recs, bytes, "encoder.pre_encode.out.bias", m.blob, m.pre_b, d)
        for (l in range64(m.n_layer)) {
            let lo = pk_layer_offsets(m, l)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_feed_forward1.weight", m.blob, lo.nf1_w, d)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_feed_forward1.bias", m.blob, lo.nf1_b, d)
            pk_read(recs, bytes, "encoder.layers.{l}.feed_forward1.linear1.weight", m.blob, lo.ff1a_w, ff * d)
            pk_read(recs, bytes, "encoder.layers.{l}.feed_forward1.linear2.weight", m.blob, lo.ff1b_w, d * ff)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_self_att.weight", m.blob, lo.nat_w, d)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_self_att.bias", m.blob, lo.nat_b, d)
            pk_read(recs, bytes, "encoder.layers.{l}.self_attn.pos_bias_u", m.blob, lo.bias_u, dh * m.n_head)
            pk_read(recs, bytes, "encoder.layers.{l}.self_attn.pos_bias_v", m.blob, lo.bias_v, dh * m.n_head)
            pk_read(recs, bytes, "encoder.layers.{l}.self_attn.linear_q.weight", m.blob, lo.q_w, d * d)
            pk_read(recs, bytes, "encoder.layers.{l}.self_attn.linear_k.weight", m.blob, lo.k_w, d * d)
            pk_read(recs, bytes, "encoder.layers.{l}.self_attn.linear_v.weight", m.blob, lo.v_w, d * d)
            pk_read(recs, bytes, "encoder.layers.{l}.self_attn.linear_out.weight", m.blob, lo.o_w, d * d)
            pk_read(recs, bytes, "encoder.layers.{l}.self_attn.linear_pos.weight", m.blob, lo.pos_w, d * d)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_conv.weight", m.blob, lo.ncv_w, d)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_conv.bias", m.blob, lo.ncv_b, d)
            pk_read(recs, bytes, "encoder.layers.{l}.conv.pointwise_conv1.weight", m.blob, lo.pw1_w, 2l * d * d)
            pk_read(recs, bytes, "encoder.layers.{l}.conv.depthwise_conv.weight", m.blob, lo.dw_w, m.n_conv_kernel * d)
            pk_read(recs, bytes, "encoder.layers.{l}.conv.batch_norm.weight", m.blob, lo.bn_w, d)
            pk_read(recs, bytes, "encoder.layers.{l}.conv.batch_norm.bias", m.blob, lo.bn_b, d)
            pk_read(recs, bytes, "encoder.layers.{l}.conv.batch_norm.running_mean", m.blob, lo.bn_mean, d)
            pk_read(recs, bytes, "encoder.layers.{l}.conv.batch_norm.running_var", m.blob, lo.bn_var, d)
            pk_read(recs, bytes, "encoder.layers.{l}.conv.pointwise_conv2.weight", m.blob, lo.pw2_w, d * d)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_feed_forward2.weight", m.blob, lo.nf2_w, d)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_feed_forward2.bias", m.blob, lo.nf2_b, d)
            pk_read(recs, bytes, "encoder.layers.{l}.feed_forward2.linear1.weight", m.blob, lo.ff2a_w, ff * d)
            pk_read(recs, bytes, "encoder.layers.{l}.feed_forward2.linear2.weight", m.blob, lo.ff2b_w, d * ff)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_out.weight", m.blob, lo.nout_w, d)
            pk_read(recs, bytes, "encoder.layers.{l}.norm_out.bias", m.blob, lo.nout_b, d)
        }
        pk_read(recs, bytes, "decoder.prediction.embed.weight", m.blob, m.embed_off, (m.n_vocab + 1l) * m.n_pred_dim)
        for (l in range64(m.n_pred_layers)) {
            pk_read(recs, bytes, "decoder.prediction.dec_rnn.lstm.weight_ih_l{l}", m.blob, m.lstm_ih[l], 4l * m.n_pred_dim * m.n_pred_dim)
            pk_read(recs, bytes, "decoder.prediction.dec_rnn.lstm.weight_hh_l{l}", m.blob, m.lstm_hh[l], 4l * m.n_pred_dim * m.n_pred_dim)
            pk_read(recs, bytes, "decoder.prediction.dec_rnn.lstm.bias_h_l{l}", m.blob, m.lstm_b[l], 4l * m.n_pred_dim)
        }
        pk_read(recs, bytes, "joint.enc.weight", m.blob, m.joint_enc_w, m.n_pred_dim * d)
        pk_read(recs, bytes, "joint.enc.bias", m.blob, m.joint_enc_b, m.n_pred_dim)
        pk_read(recs, bytes, "joint.pred.weight", m.blob, m.joint_pred_w, m.n_pred_dim * m.n_pred_dim)
        pk_read(recs, bytes, "joint.pred.bias", m.blob, m.joint_pred_b, m.n_pred_dim)
        pk_read(recs, bytes, "joint.joint_net.2.weight", m.blob, m.joint_net_w, (m.n_vocab + 1l + m.n_durations) * m.n_pred_dim)
        pk_read(recs, bytes, "joint.joint_net.2.bias", m.blob, m.joint_net_b, m.n_vocab + 1l + m.n_durations)
    }
    fclose(f)
    return <- m
}

// ===== mel (frame-major!) =====

//! Parakeet's log-mel: preemphasis 0.97, zero center-pad n_fft/2, the file's STFT window
//! (centered inside the 512 frame), power spectra, mel dot (float4-group double-acc),
//! NATURAL log(sum + 2⁻²⁴), then per-feature mean/std normalization computed over the
//! valid frames only (Bessel n−1, std + 1e-5) and applied to all. FRAME-major
//! ``[n_len][n_mel]``.
def parakeet_log_mel(samples : array<float> | #; m : ParakeetModel) : WhisperMel {
    let n_in = int64(length(samples))
    var pre : array<float>
    pre |> resize(int(n_in))
    for (i in range(int(n_in))) {
        pre[i] = samples[i]
    }
    var pi = n_in - 1l
    while (pi > 0l) {   // backward in place: x[i] -= 0.97·x[i−1]
        pre[pi] -= 0.97 * pre[pi - 1l]
        pi--
    }
    let pad = m.n_fft / 2l
    let n_padded = n_in + 2l * pad
    var padded : array<float>
    padded |> resize(int(n_padded))
    for (i in range(int(n_in))) {
        padded[int(pad) + i] = pre[i]
    }

    var mel = WhisperMel(n_mel = m.n_mel)
    mel.n_len = (n_padded - m.n_fft) / PARAKEET_HOP + 1l
    mel.n_len_org = mel.n_len
    mel.data |> resize(int(mel.n_len * m.n_mel))

    let n_fft = m.n_fft
    let n_bins = n_fft / 2l + 1l
    let wsz = int64(length(m.window))
    let wpad = (n_fft - wsz) / 2l
    let twiddles <- build_dft_twiddles(n_fft)

    var xw : array<float>
    xw |> resize(int(mel.n_len * n_fft))
    for (i in range64(mel.n_len)) {
        let off = i * PARAKEET_HOP
        let n_do = min(wsz, n_padded - off)   // window applied at [wpad, wpad+wsz)
        for (j in range64(n_do)) {
            if (off + wpad + j < n_padded) {
                xw[i * n_fft + wpad + j] = m.window[j] * padded[off + wpad + j]
            }
        }
    }
    var reim : array<float>
    reim |> resize(int(mel.n_len * n_bins * 2l))
    gemm_f32(unsafe(addr(reim[0])), unsafe(addr(xw[0])), unsafe(addr(twiddles[0])),
             mel.n_len, n_fft, n_bins * 2l)

    let mel_eps = 5.960464477539063e-08lf
    var power : array<float>
    power |> resize(int(n_bins))
    for (i in range64(mel.n_len)) {
        for (k in range64(n_bins)) {
            let re = reim[i * n_bins * 2l + k * 2l]
            let im = reim[i * n_bins * 2l + k * 2l + 1l]
            power[k] = re * re + im * im
        }
        for (j in range64(m.n_mel)) {
            var sum = 0.0lf
            var k = 0l
            while (k + 3l < n_bins) {
                sum += double(power[k] * m.filters[j * n_bins + k]
                    + power[k + 1l] * m.filters[j * n_bins + k + 1l]
                    + power[k + 2l] * m.filters[j * n_bins + k + 2l]
                    + power[k + 3l] * m.filters[j * n_bins + k + 3l])
                k += 4l
            }
            while (k < n_bins) {
                sum += double(power[k] * m.filters[j * n_bins + k])
                k++
            }
            mel.data[i * m.n_mel + j] = float(log(sum + mel_eps))
        }
    }

    // per-feature normalization over the valid frames, applied to all
    let valid = n_in / PARAKEET_HOP
    for (j in range64(m.n_mel)) {
        var sum = 0.0lf
        for (i in range64(valid)) {
            sum += double(mel.data[i * m.n_mel + j])
        }
        let mean = sum / double(valid)
        var sq = 0.0lf
        for (i in range64(valid)) {
            let dv = double(mel.data[i * m.n_mel + j]) - mean
            sq += dv * dv
        }
        let denom = sqrt(sq / (double(valid) - 1.0lf)) + 1e-5lf
        for (i in range64(mel.n_len)) {
            mel.data[i * m.n_mel + j] = float((double(mel.data[i * m.n_mel + j]) - mean) / denom)
        }
    }
    return <- mel
}

// ===== conv subsampling =====

// regular conv2d k3 s2 p1 over [iw × ih × cin] (rows [ih][iw][c], c fastest) via im2col+GEMM
def private pk_conv2d_s2(var out : array<float>; var col : array<float>;
                         x : array<float>; blob : array<float>; w_off, b_off : int64;
                         iw, ih, cin, cout : int64) {
    let ow = (iw - 1l) / 2l + 1l
    let oh = (ih - 1l) / 2l + 1l
    let kdim = cin * 9l
    let rows = oh * ow
    col |> resize(int(rows * kdim))
    for (oy in range64(oh)) {
        for (ox in range64(ow)) {
            let r = (oy * ow + ox) * kdim
            for (ic in range64(cin)) {
                for (kh in range64(3l)) {
                    let iy = oy * 2l - 1l + kh
                    for (kw in range64(3l)) {
                        let ix = ox * 2l - 1l + kw
                        col[r + (ic * 3l + kh) * 3l + kw] = (iy >= 0l && iy < ih && ix >= 0l && ix < iw
                            ? x[(iy * iw + ix) * cin + ic]
                            : 0.0)
                    }
                }
            }
        }
    }
    out |> resize(int(rows * cout))
    mm_blob_b(out, blob, w_off, col, kdim, cout, rows)
    add_bias_rows(out, blob, b_off, cout, rows)
}

// depthwise conv2d k3 s2 p1: per-channel 3x3 kernel (w flat [c][kh][kw])
def private pk_conv2d_dw_s2(var out : array<float>; x : array<float>; blob : array<float>;
                            w_off, b_off : int64; iw, ih, ch : int64) {
    let ow = (iw - 1l) / 2l + 1l
    let oh = (ih - 1l) / 2l + 1l
    out |> resize(int(oh * ow * ch))
    for (oy in range64(oh)) {
        for (ox in range64(ow)) {
            let r = (oy * ow + ox) * ch
            for (c in range64(ch)) {
                var acc = 0.0
                for (kh in range64(3l)) {
                    let iy = oy * 2l - 1l + kh
                    if (iy >= 0l && iy < ih) {
                        for (kw in range64(3l)) {
                            let ix = ox * 2l - 1l + kw
                            if (ix >= 0l && ix < iw) {
                                acc += blob[w_off + (c * 3l + kh) * 3l + kw] * x[(iy * iw + ix) * ch + c]
                            }
                        }
                    }
                }
                out[r + c] = acc + blob[b_off + c]
            }
        }
    }
}

def private pk_relu(var x : array<float>) {
    for (v in x) {
        v = max(v, 0.0)
    }
}

// ===== encoder =====

//! FastConformer encoder over the whole mel: conv subsampling to ``[T × n_state]``, then
//! 24 conformer blocks (macaron FFN halves, rel-pos attention with u/v biases, GLU +
//! depthwise-conv + inference-BN module, per-layer post norm). Global attention only —
//! clips past the oracle's 8192-frame local-attention switch panic (see parakeet_plan.md).
//! Returns the encoder output rows (token-major ``[T × n_state]``) and sets ``n_frames``.
def parakeet_encode(m : ParakeetModel; mel : WhisperMel; var enc_out : array<float>) : int64 {
    let d = m.n_state
    let nch = m.n_sub_ch
    let n_head = m.n_head
    let dh = d / n_head

    // q8 activation scratch (one image reused across sites; q/k/v share one requant)
    var xqi : array<int8>
    var xsi : array<float>

    // conv subsampling ([time][mel] rows are already the [ih][iw][c=1] layout)
    var tp = ref_time_ticks()
    var col : array<float>
    var y0 : array<float>
    var y2 : array<float>
    var y3 : array<float>
    var y5 : array<float>
    var y6 : array<float>
    pk_conv2d_s2(y0, col, mel.data, m.blob, m.c0_w, m.c0_b, m.n_mel, mel.n_len, 1l, nch)
    pk_relu(y0)
    let w1 = (m.n_mel - 1l) / 2l + 1l          // 64
    let t1 = (mel.n_len - 1l) / 2l + 1l
    pk_conv2d_dw_s2(y2, y0, m.blob, m.c2_w, m.c2_b, w1, t1, nch)
    let w2 = (w1 - 1l) / 2l + 1l               // 32
    let t2 = (t1 - 1l) / 2l + 1l
    y3 |> resize(int(t2 * w2 * nch))
    pk_mm_rq(m, y3, m.c3_w, y2, xqi, xsi, nch, nch, t2 * w2)   // 1x1 conv = per-position channel mix
    add_bias_rows(y3, m.blob, m.c3_b, nch, t2 * w2)
    pk_relu(y3)
    pk_conv2d_dw_s2(y5, y3, m.blob, m.c5_w, m.c5_b, w2, t2, nch)
    let w3 = (w2 - 1l) / 2l + 1l               // 16
    let t3 = (t2 - 1l) / 2l + 1l
    y6 |> resize(int(t3 * w3 * nch))
    pk_mm_rq(m, y6, m.c6_w, y5, xqi, xsi, nch, nch, t3 * w3)
    add_bias_rows(y6, m.blob, m.c6_b, nch, t3 * w3)
    pk_relu(y6)

    // features per time row: v[f + w3·c] = y6[t][f][c]; then pre_out into the residual stream
    let tt = t3
    if (tt > LOCAL_ATTN_THRESHOLD) {
        panic("dasLLAMA parakeet: {tt} encoder frames crosses the local-attention switch — clip audio to under ~10.9 minutes")
    }
    let feat = w3 * nch
    var xf : array<float>
    xf |> resize(int(tt * feat))
    for (t in range64(tt)) {
        for (fr in range64(w3)) {
            for (c in range64(nch)) {
                xf[t * feat + fr + w3 * c] = y6[(t * w3 + fr) * nch + c]
            }
        }
    }
    var x : array<float>
    x |> resize(int(tt * d))
    pk_mm_rq(m, x, m.pre_w, xf, xqi, xsi, feat, d, tt)
    add_bias_rows(x, m.blob, m.pre_b, d, tt)
    asr_prof_add("pk.conv_subsample", tp)
    tp = ref_time_ticks()

    // masked tail (padded mel frames past the real audio): none for full-clip encode when
    // ceil-per-stage == ceil(n/8); the oracle masks keys >= ceil(n_len_org/8)
    let n_real = (mel.n_len_org + m.subsampling - 1l) / m.subsampling

    // rel-pos embedding table [W × d], interleaved (sin,cos) pairs; W = 2T−1
    let ww = 2l * tt - 1l
    var pos_emb : array<float>
    pos_emb |> resize(int(ww * d))
    for (w in range64(ww)) {
        let rel = double(tt - 1l - w)
        for (k in range64(d / 2l)) {
            let freq = exp(-(double(k * 2l) * log(10000.0lf) / double(d)))
            let theta = float(freq * rel)
            pos_emb[w * d + 2l * k] = sin(theta)
            pos_emb[w * d + 2l * k + 1l] = cos(theta)
        }
    }
    // the rel-pos image is layer-invariant: one requant serves every layer's pos projection
    var posq : array<int8>
    var poss : array<float>
    if (m.q8) {
        pk_requant(pos_emb, d, ww, posq, poss)
    }
    asr_prof_add("pk.pos_emb", tp)

    // scratch
    var xb : array<float>
    xb |> resize(int(tt * d))
    var h : array<float>
    h |> resize(int(tt * 4l * d))
    var qq : array<float>
    qq |> resize(int(tt * d))
    var kk : array<float>
    kk |> resize(int(tt * d))
    var vv : array<float>
    vv |> resize(int(tt * d))
    var posl : array<float>
    posl |> resize(int(ww * d))
    var quh : array<float>
    quh |> resize(int(tt * dh))
    var quh2 : array<float>
    quh2 |> resize(int(tt * dh))
    var vh : array<float>
    vh |> resize(int(tt * dh))
    var kth : array<float>
    kth |> resize(int(dh * tt))
    var scores : array<float>
    scores |> resize(int(tt * tt))
    var relm : array<float>
    relm |> resize(int(tt * ww))
    var post : array<float>
    post |> resize(int(dh * ww))
    var oh : array<float>
    oh |> resize(int(tt * dh))
    var ao : array<float>
    ao |> resize(int(tt * d))
    let scale = 1.0 / sqrt(float(dh))

    for (l in range64(m.n_layer)) {
        let lo = pk_layer_offsets(m, l)

        // FFN1 (macaron half)
        tp = ref_time_ticks()
        layernorm_batch(xb, x, m.blob, lo.nf1_w, lo.nf1_b, d, tt, m.eps)
        pk_mm_rq(m, h, lo.ff1a_w, xb, xqi, xsi, d, 4l * d, tt)
        silu(h, tt * 4l * d)
        pk_mm_rq(m, xb, lo.ff1b_w, h, xqi, xsi, 4l * d, d, tt)
        for (i in range64(tt * d)) {
            x[i] += 0.5 * xb[i]
        }
        asr_prof_add("pk.ffn", tp)

        // rel-pos attention
        tp = ref_time_ticks()
        layernorm_batch(xb, x, m.blob, lo.nat_w, lo.nat_b, d, tt, m.eps)
        if (m.q8) {   // q/k/v share the post-LN activation: one requant, three GEMMs
            pk_requant(xb, d, tt, xqi, xsi)
        }
        pk_mm(m, qq, lo.q_w, xb, xqi, xsi, d, d, tt)
        pk_mm(m, kk, lo.k_w, xb, xqi, xsi, d, d, tt)
        pk_mm(m, vv, lo.v_w, xb, xqi, xsi, d, d, tt)
        // pos projection for this layer: [W × d], against the hoisted layer-invariant image
        pk_mm(m, posl, lo.pos_w, pos_emb, posq, poss, d, d, ww)
        asr_prof_add("pk.attn_proj", tp)
        tp = ref_time_ticks()
        for (hi in range64(n_head)) {
            let hoff = hi * dh
            unsafe {
                var qup = addr(quh[0])
                var qvp = addr(quh2[0])
                var ktp = addr(kth[0])
                var vhp = addr(vh[0])
                var pop = addr(post[0])
                var scp = addr(scores[0])
                var rlp = addr(relm[0])
                var ohp = addr(oh[0])
                var aop = addr(ao[0])
                let qqp = reinterpret<float const?>(addr(qq[0]))
                let kkp = reinterpret<float const?>(addr(kk[0]))
                let vvp = reinterpret<float const?>(addr(vv[0]))
                let plp = reinterpret<float const?>(addr(posl[0]))
                let bup = reinterpret<float const?>(addr(m.blob[lo.bias_u + hi * dh]))
                let bvp = reinterpret<float const?>(addr(m.blob[lo.bias_v + hi * dh]))
                // transposed head views ((Q+u), (Q+v), Kᵀ, V_h, pos_hᵀ) — the row GEMMs read
                // these in full, so they build before the compute dispatch
                maybe_parallel_for(0, int(tt), lanes_for_work(tt * dh * 4l, 0)) $(rb, re) {
                    unsafe {
                        for (t in range64(int64(rb), int64(re))) {
                            for (j in range64(dh)) {
                                let qv = qqp[t * d + hoff + j]
                                qup[t * dh + j] = qv + bup[j]
                                qvp[t * dh + j] = qv + bvp[j]
                                ktp[j * tt + t] = kkp[t * d + hoff + j]
                                vhp[t * dh + j] = vvp[t * d + hoff + j]
                            }
                        }
                    }
                }
                maybe_parallel_for(0, int(ww), lanes_for_work(ww * dh, 0)) $(rb, re) {
                    unsafe {
                        for (w in range64(int64(rb), int64(re))) {
                            for (j in range64(dh)) {
                                pop[j * ww + w] = plp[w * d + hoff + j]
                            }
                        }
                    }
                }
                // content scores (Q+u)·Kᵀ + rel scores (Q+v)·pos_hᵀ (gathered at (T−1)−q+k) +
                // softmax + P·V_h, threaded over query rows in 4-ROW BLOCKS: gemm_f32's 4×16
                // tile / scalar-remainder split is row-position-dependent, so 4-aligned chunk
                // starts keep every row's FMA order identical to the whole-matrix call —
                // bit-exact at any lane count
                let nblk4 = (tt + 3l) / 4l
                maybe_parallel_for(0, int(nblk4), lanes_for_work(tt * dh * (2l * tt + ww), 0)) $(bb, be) {
                    unsafe {
                        let r0 = int64(bb) * 4l
                        let r1 = min(int64(be) * 4l, tt)
                        let nr = r1 - r0
                        for (i in range64(r0 * tt, r1 * tt)) {
                            scp[i] = 0.0
                        }
                        for (i in range64(r0 * ww, r1 * ww)) {
                            rlp[i] = 0.0
                        }
                        gemm_f32(scp + r0 * tt, qup + r0 * dh, ktp, nr, dh, tt)
                        gemm_f32(rlp + r0 * ww, qvp + r0 * dh, pop, nr, dh, ww)
                        for (q in range64(r0, r1)) {
                            let base = tt - 1l - q
                            for (k in range64(tt)) {
                                var s = (scp[q * tt + k] + rlp[q * ww + base + k]) * scale
                                if (k >= n_real) {
                                    s = -1e30
                                }
                                scp[q * tt + k] = s
                            }
                            softmax(scp + q * tt, tt)
                        }
                        for (i in range64(r0 * dh, r1 * dh)) {
                            ohp[i] = 0.0
                        }
                        gemm_f32(ohp + r0 * dh, scp + r0 * tt, vhp, nr, tt, dh)
                        for (t in range64(r0, r1)) {
                            for (j in range64(dh)) {
                                aop[t * d + hoff + j] = ohp[t * dh + j]
                            }
                        }
                    }
                }
            }
        }
        asr_prof_add("pk.attn_heads", tp)
        tp = ref_time_ticks()
        pk_mm_rq(m, xb, lo.o_w, ao, xqi, xsi, d, d, tt)
        add_inplace_rows(x, xb, tt * d)
        asr_prof_add("pk.attn_out", tp)

        // conv module
        tp = ref_time_ticks()
        layernorm_batch(xb, x, m.blob, lo.ncv_w, lo.ncv_b, d, tt, m.eps)
        pk_mm_rq(m, h, lo.pw1_w, xb, xqi, xsi, d, 2l * d, tt)
        unsafe {
            let hp = reinterpret<float const?>(addr(h[0]))
            var xbp = addr(xb[0])
            var aop = addr(ao[0])
            let dwp = reinterpret<float const?>(addr(m.blob[lo.dw_w]))
            let bmp = reinterpret<float const?>(addr(m.blob[lo.bn_mean]))
            let bvp2 = reinterpret<float const?>(addr(m.blob[lo.bn_var]))
            let bwp = reinterpret<float const?>(addr(m.blob[lo.bn_w]))
            let bbp = reinterpret<float const?>(addr(m.blob[lo.bn_b]))
            let nk = m.n_conv_kernel
            let kpad = (nk - 1l) / 2l   // depthwise pad (k−1)/2 both sides
            maybe_parallel_for(0, int(tt), lanes_for_work(tt * d * 4l, 0)) $(rb, re) {
                unsafe {
                    for (t in range64(int64(rb), int64(re))) {   // GLU: signal · σ(gate)
                        for (j in range64(d)) {
                            let sg = hp[t * 2l * d + j]
                            let gt = hp[t * 2l * d + d + j]
                            xbp[t * d + j] = sg * (1.0 / (1.0 + exp(-gt)))
                        }
                    }
                }
            }
            // depthwise conv1d k9 over time (reads xb rows t±kpad — barrier from the GLU
            // dispatch above), then inference BN + silu
            maybe_parallel_for(0, int(tt), lanes_for_work(tt * d * (nk + 4l), 0)) $(rb, re) {
                unsafe {
                    for (t in range64(int64(rb), int64(re))) {
                        for (j in range64(d)) {
                            var acc = 0.0
                            for (k in range64(nk)) {
                                let src = t + k - kpad
                                if (src >= 0l && src < tt) {
                                    acc += dwp[j * nk + k] * xbp[src * d + j]
                                }
                            }
                            let bn = (acc - bmp[j]) / sqrt(bvp2[j])
                            let bv = bn * bwp[j] + bbp[j]
                            aop[t * d + j] = bv * (1.0 / (1.0 + exp(-bv)))   // silu
                        }
                    }
                }
            }
        }
        pk_mm_rq(m, xb, lo.pw2_w, ao, xqi, xsi, d, d, tt)
        add_inplace_rows(x, xb, tt * d)
        asr_prof_add("pk.conv_module", tp)

        // FFN2 (second macaron half)
        tp = ref_time_ticks()
        layernorm_batch(xb, x, m.blob, lo.nf2_w, lo.nf2_b, d, tt, m.eps)
        pk_mm_rq(m, h, lo.ff2a_w, xb, xqi, xsi, d, 4l * d, tt)
        silu(h, tt * 4l * d)
        pk_mm_rq(m, xb, lo.ff2b_w, h, xqi, xsi, 4l * d, d, tt)
        for (i in range64(tt * d)) {
            x[i] += 0.5 * xb[i]
        }

        // per-layer post norm
        layernorm_batch(x, x, m.blob, lo.nout_w, lo.nout_b, d, tt, m.eps)
        asr_prof_add("pk.ffn", tp)
    }

    enc_out <- x
    return tt
}

// ===== prediction network + joint + TDT greedy =====

//! LSTM predictor state (h/c per layer) + the projected prediction vector.
struct ParakeetPredState {
    h : array<float>       // [n_layers × pred_dim]
    c : array<float>
    pred : array<float>    // joint.pred projection of the last hidden [pred_dim]
    gates : array<float>   // scratch [4 × pred_dim]: ih part
    gates2 : array<float>  // scratch [4 × pred_dim]: hh part
    xin : array<float>     // scratch [pred_dim]: layer input
    hbuf : array<float>    // scratch [pred_dim]: current layer's h (matmul takes plain arrays)
}

def make_parakeet_pred_state(m : ParakeetModel) : ParakeetPredState {
    var s = ParakeetPredState()
    s.h |> resize(int(m.n_pred_layers * m.n_pred_dim))
    s.c |> resize(int(m.n_pred_layers * m.n_pred_dim))
    s.pred |> resize(int(m.n_pred_dim))
    s.gates |> resize(int(4l * m.n_pred_dim))
    s.gates2 |> resize(int(4l * m.n_pred_dim))
    s.xin |> resize(int(m.n_pred_dim))
    s.hbuf |> resize(int(m.n_pred_dim))
    return <- s
}

// advance the LSTM stack for `token` and refresh s.pred (gates packed [i,f,o,g])
def private pk_predict(m : ParakeetModel; var s : ParakeetPredState; token : int) {
    let pd = m.n_pred_dim
    for (j in range64(pd)) {
        s.xin[j] = m.blob[m.embed_off + int64(token) * pd + j]
    }
    for (l in range64(m.n_pred_layers)) {
        for (j in range64(pd)) {
            s.hbuf[j] = s.h[l * pd + j]
        }
        array_view(m.blob, m.lstm_ih[l], 4l * pd * pd) $(wih : array<float>#) {
            matmul(s.gates, wih, s.xin, pd, 4l * pd)
        }
        array_view(m.blob, m.lstm_hh[l], 4l * pd * pd) $(whh : array<float>#) {
            matmul(s.gates2, whh, s.hbuf, pd, 4l * pd)
        }
        for (j in range64(pd)) {
            let ig = 1.0 / (1.0 + exp(-(s.gates[j] + s.gates2[j] + m.blob[m.lstm_b[l] + j])))
            let fg = 1.0 / (1.0 + exp(-(s.gates[pd + j] + s.gates2[pd + j] + m.blob[m.lstm_b[l] + pd + j])))
            let og = 1.0 / (1.0 + exp(-(s.gates[2l * pd + j] + s.gates2[2l * pd + j] + m.blob[m.lstm_b[l] + 2l * pd + j])))
            let cg = tanh(s.gates[3l * pd + j] + s.gates2[3l * pd + j] + m.blob[m.lstm_b[l] + 3l * pd + j])
            let cn = fg * s.c[l * pd + j] + ig * cg
            s.c[l * pd + j] = cn
            let hn = og * tanh(cn)
            s.h[l * pd + j] = hn
            s.xin[j] = hn
        }
    }
    // joint.pred projection of the top hidden (already in s.xin after the last layer)
    array_view(m.blob, m.joint_pred_w, m.n_pred_dim * m.n_pred_dim) $(w : array<float>#) {
        matmul(s.pred, w, s.xin, pd, pd)
    }
    for (j in range64(pd)) {
        s.pred[j] += m.blob[m.joint_pred_b + j]
    }
}

// decode trace (debug rail): per-step duration log-probs alongside the choice
var g_parakeet_trace = false

def set_parakeet_trace(on : bool) {
    g_parakeet_trace = on
}

//! Greedy TDT decode over the encoder output — whisper.cpp's parakeet_decode loop, token
//! for token: joint softmax over the full (vocab+blank+durations) row, argmax token +
//! argmax duration, blank advances time without predicting, non-blank feeds the LSTM,
//! duration 0 caps at n_max_tokens per frame.
def parakeet_tdt_decode(m : ParakeetModel; enc_out : array<float>; n_frames : int64) : array<ParakeetToken> {
    var out : array<ParakeetToken>
    let d = m.n_state
    let pd = m.n_pred_dim
    let n_logits = m.n_vocab + 1l + m.n_durations
    let n_tok_logits = int(m.n_vocab + 1l)

    // precompute the joint's encoder projection for every frame [T × pred_dim]
    var encp : array<float>
    encp |> resize(int(n_frames * pd))
    var xqi : array<int8>
    var xsi : array<float>
    pk_mm_rq(m, encp, m.joint_enc_w, enc_out, xqi, xsi, d, pd, n_frames)
    add_bias_rows(encp, m.blob, m.joint_enc_b, pd, n_frames)

    var s <- make_parakeet_pred_state(m)
    pk_predict(m, s, m.blank_id)

    var joint : array<float>
    joint |> resize(int(pd))
    var logits : array<float>
    logits |> resize(int(n_logits))

    var t = 0l
    var emitted = 0
    while (t < n_frames) {
        for (j in range64(pd)) {
            let v = encp[t * pd + j] + s.pred[j]
            joint[j] = max(v, 0.0)   // relu
        }
        mm_blob_b(logits, m.blob, m.joint_net_w, joint, pd, n_logits, 1l)
        for (i in range64(n_logits)) {
            logits[i] += m.blob[m.joint_net_b + i]
        }
        // log-softmax over the WHOLE row (the oracle's plog normalizer includes durations)
        var mx = logits[0]
        for (v in logits) {
            mx = max(mx, v)
        }
        var lse = 0.0lf
        for (v in logits) {
            lse += double(exp(v - mx))
        }
        let logz = float(log(lse)) + mx

        var best = 0
        for (i in range(1, n_tok_logits)) {
            if (logits[i] > logits[best]) {
                best = i
            }
        }
        // duration argmax over the fp32 SOFTMAX values, not the raw logits: the oracle's
        // probs = softmax(logits) in fp32 flushes the durations' ~e⁻¹¹⁰ relative mass to
        // exactly 0.0 wherever exp(logit − max) underflows, log() turns them into −inf, and
        // its strict-> argmax over five −infs then defaults to index 0. Analytic logit
        // comparison would pick the TRUE argmax and diverge — mirror the underflow.
        var bdur = 0
        var bdp = exp(logits[n_tok_logits] - mx)
        for (i in range(1, int(m.n_durations))) {
            let dp = exp(logits[n_tok_logits + i] - mx)
            if (dp > bdp) {
                bdp = dp
                bdur = i
            }
        }
        var dur = m.durations[bdur]
        if (g_parakeet_trace) {
            print("  t={t} tok={best} durp=[")
            for (i in range(int(m.n_durations))) {
                print("{exp(logits[n_tok_logits + i] - mx)} ")
            }
            print("] -> {bdur}\n")
        }

        if (best == m.blank_id) {
            if (dur == 0) {
                dur = 1
            }
            t += int64(dur)
            emitted = 0
            continue
        }

        // token probability renormalized over the token slice (the oracle's create_token_data)
        let plog = logits[best] - logz
        var tok_sum = 0.0lf
        for (i in range(n_tok_logits)) {
            tok_sum += double(exp(logits[i] - logz))
        }
        out |> push(ParakeetToken(id = best, dur_idx = bdur, dur = dur, frame = t,
            p = float(double(exp(plog)) / tok_sum), plog = plog))

        pk_predict(m, s, best)
        if (dur > 0) {
            t += int64(dur)
            emitted = 0
        } else {
            emitted++
            if (emitted >= int(m.n_max_tokens)) {
                t++
                emitted = 0
            }
        }
    }
    return <- out
}

//! SPM detokenize: ▁ becomes a space, except while the transcript is still empty inside the
//! FIRST piece (the oracle's sentencepiece_piece_to_text rule); `<...>` control pieces
//! render as nothing.
def parakeet_detokenize(m : ParakeetModel; toks : array<ParakeetToken> | #) : string {
    var segs : array<string>
    var idx = 0
    for (t in toks) {
        let piece = m.vocab[t.id]
        if (length(piece) > 2 && starts_with(piece, "<") && ends_with(piece, ">")) {
            idx++
            continue
        }
        var s = replace(piece, "▁", " ")
        if (idx == 0) {   // first piece: strip the leading spaces the ▁ prefix produced
            while (starts_with(s, " ")) {
                s = slice(s, 1, length(s))
            }
        }
        segs |> push(s)
        idx++
    }
    return join(segs, "")
}
