options gen2

module dasllama_audio shared public

require math
require daslib/fio
require daslib/array_boost
require dasllama/dasllama_math
require dasllama/dasllama_par
require dasllama/dasllama_gguf

// Whisper-family audio frontend: 16 kHz mono PCM -> log-mel chunks, in two oracle-exact
// flavors: log_mel_chunks mirrors llama.cpp mtmd (tools/mtmd/mtmd-audio.cpp, qwen2a tower),
// log_mel_whisper mirrors whisper.cpp's log_mel_spectrogram (different padding/floor/fill
// rules — see whisper_plan.md). The 400-point DFT is two GEMM columns of a precomputed
// twiddle matrix (minfft is pow2-only, and 400 = 2^4*25 is not) — see qwen2_audio_plan.md.

let AUDIO_SAMPLE_RATE = 16000l
let AUDIO_N_FFT = 400l
let AUDIO_HOP = 160l
let AUDIO_CHUNK_FRAMES = 3000l  // 30 s of hops per encoder chunk

//! One 30 s log-mel chunk, mel-major ``[n_mel][n_len]`` (mtmd layout, conv-ready).
struct MelChunk {
    n_mel : int64
    n_len : int64
    data : array<float>
}

// erfc rational approximation (Numerical Recipes 6.2), |fractional error| < 1.2e-7 —
// float-level agreement with ggml's erff. Double internally.
def private erf_nr(x : double) : double {
    let z = abs(x)
    let t = 1.0lf / (1.0lf + 0.5lf * z)
    let erfc = t * exp(-z * z - 1.26551223lf + t * (1.00002368lf + t * (0.37409196lf + t * (0.09678418lf +
        t * (-0.18628806lf + t * (0.27886807lf + t * (-1.13520398lf + t * (1.48851587lf +
        t * (-0.82215223lf + t * 0.17087277lf)))))))))
    return x >= 0.0lf ? 1.0lf - erfc : erfc - 1.0lf
}

//! gelu_erf(x) = 0.5·x·(1 + erf(x/√2)) — the EXACT erf form (ggml's ggml_vec_gelu_erf_f32),
//! not the tanh approximation ``gelu`` uses. Whisper's conv frontend and encoder FFN both
//! use this flavor. In place over the first ``size`` elements.
def gelu_erf(var x : float?; size : int64) {
    let inv_sqrt2 = 0.7071067811865476lf
    unsafe {
        for (i in range64(size)) {
            let v = double(x[i])
            x[i] = float(0.5lf * v * (1.0lf + erf_nr(v * inv_sqrt2)))
        }
    }
}

def gelu_erf(var x : array<float> | #; size : int64) {
    if (size <= 0l) return
    gelu_erf(unsafe(addr(x[0])), size)
}

//! whisper.cpp's ggml_gelu flavor (GGML_GELU_FP16): tanh approximation evaluated through an
//! fp16 lookup table — input and output both round-trip through binary16, with ±10 clamps
//! applied BEFORE the conversion. Bit-exact vs ggml's CPU path. In place over ``size``.
def gelu_tanh_lut(var x : float?; size : int64) {
    unsafe {
        for (i in range64(size)) {
            let v = x[i]
            if (v <= -10.0) {
                x[i] = 0.0
            } elif (v < 10.0) {  // v >= 10 passes through unchanged
                let xr = f16_to_f32(f32_to_f16(v))
                let g = 0.5 * xr * (1.0 + tanh(0.79788456080286535587989211986876 * xr * (1.0 + 0.044715 * xr * xr)))
                x[i] = f16_to_f32(f32_to_f16(g))
            }
        }
    }
}

def gelu_tanh_lut(var x : array<float> | #; size : int64) {
    if (size <= 0l) return
    gelu_tanh_lut(unsafe(addr(x[0])), size)
}

//! Hann window of length ``n`` (periodic when ``periodic``), float-exact vs mtmd's
//! ``fill_hann_window``: 0.5·(1 − cos(2πi/denom)) with denom = n (periodic) / n−1.
def build_hann_window(n : int64; periodic : bool = true) : array<float> {
    let denom = double(periodic ? n : n - 1l)
    return <- [for (i in range64(n)); float(0.5lf * (1.0lf - double(cos(float(2.0lf * DBL_PI * double(i) / denom)))))]
}

//! Slaney-scale triangular mel filterbank ``[n_mel][n_fft/2+1]`` (librosa default, area-
//! normalized) — a direct port of mtmd's ``fill_mel_filterbank_matrix`` with fmin=0,
//! fmax=sample_rate/2. Double internally, float out.
def build_mel_filterbank(n_mel, n_fft, sample_rate : int64) : array<float> {
    let n_bins = n_fft / 2l + 1l
    // slaney hz<->mel: linear below 1 kHz, log above
    let min_log_hz = 1000.0lf
    let lin_slope = 3.0lf / 200.0lf
    let min_log_mel = min_log_hz * lin_slope
    let log_step = log(6.4lf) / 27.0lf
    let fmax = 0.5lf * double(sample_rate)
    let m_hi = fmax < min_log_hz ? fmax * lin_slope : min_log_mel + log(fmax / min_log_hz) / log_step
    // mel grid edges back to hz (m_lo = hz_to_mel(0) = 0)
    var hz_pts : array<double>
    hz_pts |> resize(int(n_mel + 2l))
    for (i in range64(n_mel + 2l)) {
        let m = m_hi * double(i) / double(n_mel + 1l)
        hz_pts[i] = m < min_log_mel ? m / lin_slope : min_log_hz * exp((m - min_log_mel) * log_step)
    }
    let bin_hz_step = double(sample_rate) / double(n_fft)
    var out : array<float>
    out |> resize(int(n_mel * n_bins))
    for (m in range64(n_mel)) {
        let f_left = hz_pts[m]
        let f_center = hz_pts[m + 1l]
        let f_right = hz_pts[m + 2l]
        let denom_l = max(1e-30lf, f_center - f_left)
        let denom_r = max(1e-30lf, f_right - f_center)
        let enorm = 2.0lf / max(1e-30lf, f_right - f_left)  // slaney area norm
        for (k in range64(n_bins)) {
            let f = double(k) * bin_hz_step
            var w = 0.0lf
            if (f >= f_left && f <= f_center) {
                w = (f - f_left) / denom_l
            } elif (f > f_center && f <= f_right) {
                w = (f_right - f) / denom_r
            }
            out[m * n_bins + k] = float(w * enorm)
        }
    }
    return <- out
}

//! DFT twiddle matrix [n_fft][2·n_bins]: column 2k = cos(2πjk/n), column 2k+1 = −sin(2πjk/n).
//! XW[frames×n_fft] · B -> interleaved re/im rows, same table values as mtmd's sin/cos cache
//! (double theta, float trig). Shared by every mel flavor (whisper/mtmd here, qwen3a's module).
def build_dft_twiddles(n_fft : int64) : array<float> {
    let n_bins = n_fft / 2l + 1l
    var cos_tab : array<float>
    var sin_tab : array<float>
    cos_tab |> resize(int(n_fft))
    sin_tab |> resize(int(n_fft))
    for (i in range64(n_fft)) {
        let theta = 2.0lf * DBL_PI * double(i) / double(n_fft)
        cos_tab[i] = cos(float(theta))
        sin_tab[i] = sin(float(theta))
    }
    var b : array<float>
    b |> resize(int(n_fft * n_bins * 2l))
    for (j in range64(n_fft)) {
        for (k in range64(n_bins)) {
            let idx = (j * k) % n_fft
            b[j * n_bins * 2l + k * 2l] = cos_tab[idx]
            b[j * n_bins * 2l + k * 2l + 1l] = -sin_tab[idx]
        }
    }
    return <- b
}

//! Whisper log-mel spectrogram over the full (padded) input, then split into full 3000-frame
//! chunks — the mtmd whisper preprocessor end-to-end: pad to ≥31 s, reflect-200 head pad,
//! 30 s zero tail (+200), Hann-400/hop-160 power spectra, slaney mel (double accumulate,
//! floor 2⁻²⁴), log10, global max−8 clamp, (x+4)/4. Audio ≤30 s yields exactly one chunk.
def log_mel_chunks(samples : array<float> | #; n_mel : int64) : array<MelChunk> {
    let n_in = length(samples)
    // mtmd zero-extends short input to chunk+1 seconds BEFORE the stage pads — the head
    // reflect below must read from the extended buffer, not the raw input
    let min_samples = int(AUDIO_SAMPLE_RATE * 31l)
    let n_base = max(n_in, min_samples)
    let head = int(AUDIO_N_FFT / 2l)                       // reflect pad
    let tail = int(AUDIO_SAMPLE_RATE * 30l) + head         // 30 s zeros + 200
    let n_padded = head + n_base + tail
    var padded : array<float>
    padded |> resize(n_padded)                             // resize zero-fills
    for (i in range(n_in)) {
        padded[head + i] = samples[i]
    }
    for (i in range(head)) {                               // reflect: padded[199-i] = base[1+i]
        padded[head - 1 - i] = padded[head + 1 + i]
    }

    let n_fft = AUDIO_N_FFT
    let n_bins = n_fft / 2l + 1l
    let n_len = (int64(n_padded) - n_fft) / AUDIO_HOP + 1l
    let hann <- build_hann_window(n_fft)
    let twiddles <- build_dft_twiddles(n_fft)
    let filters <- build_mel_filterbank(n_mel, n_fft, AUDIO_SAMPLE_RATE)

    // windowed frames [n_len × n_fft]
    var xw : array<float>
    xw |> resize(int(n_len * n_fft))
    for (i in range64(n_len)) {
        let off = i * AUDIO_HOP
        for (j in range64(n_fft)) {
            xw[i * n_fft + j] = hann[j] * padded[off + j]
        }
    }

    // DFT as one GEMM: [n_len × n_fft] · [n_fft × 2·n_bins] -> interleaved re/im
    var reim : array<float>
    reim |> resize(int(n_len * n_bins * 2l))               // gemm accumulates: starts zeroed
    gemm_f32(unsafe(addr(reim[0])), unsafe(addr(xw[0])), unsafe(addr(twiddles[0])),
             n_len, n_fft, n_bins * 2l)

    // power spectra -> mel (float products, double sum — mtmd's exact accumulation), log10
    let mel_floor = 5.960464477539063e-08lf                // 2^-24, mtmd filter_params default
    let log10_e = 0.43429448190325176lf
    var mel : array<float>
    mel |> resize(int(n_mel * n_len))                      // mel-major [n_mel][n_len]
    var power : array<float>
    power |> resize(int(n_bins))
    for (i in range64(n_len)) {
        for (k in range64(n_bins)) {
            let re = reim[i * n_bins * 2l + k * 2l]
            let im = reim[i * n_bins * 2l + k * 2l + 1l]
            power[k] = re * re + im * im
        }
        for (m in range64(n_mel)) {
            var sum = 0.0lf
            for (k in range64(n_bins)) {
                sum += double(power[k] * filters[m * n_bins + k])
            }
            mel[m * n_len + i] = float(log(max(sum, mel_floor)) * log10_e)
        }
    }

    // whisper-style dynamic clamp + scale, GLOBAL over the padded spectrogram; mtmd's exact
    // rounding — the clamp value round-trips through float before the (x+4)/4 double math
    var mmax = -1e20lf
    for (v in mel) {
        mmax = max(mmax, double(v))
    }
    mmax -= 8.0lf
    for (v in mel) {
        let clamped = double(v) < mmax ? float(mmax) : v
        v = float((double(clamped) + 4.0lf) / 4.0lf)
    }

    // full 3000-frame chunks only; the padded tail chunk is dropped (mtmd: "safe to ignore")
    var chunks : array<MelChunk>
    var off = 0l
    while (off + AUDIO_CHUNK_FRAMES <= n_len) {
        var c = MelChunk(n_mel = n_mel, n_len = AUDIO_CHUNK_FRAMES)
        c.data |> resize(int(n_mel * AUDIO_CHUNK_FRAMES))
        for (m in range64(n_mel)) {
            for (i in range64(AUDIO_CHUNK_FRAMES)) {
                c.data[m * AUDIO_CHUNK_FRAMES + i] = mel[m * n_len + off + i]
            }
        }
        chunks |> emplace(c)
        off += AUDIO_CHUNK_FRAMES
    }
    return <- chunks
}

//! Full-length whisper.cpp-style log-mel spectrogram: total frame count (audio + the 30 s
//! zero tail), the real-audio frame count (``n_len_org`` = the driver's seek_end), and
//! mel-major ``[n_mel][n_len]`` data.
struct WhisperMel {
    n_mel : int64
    n_len : int64
    n_len_org : int64
    data : array<float>
}

//! whisper.cpp's ``log_mel_spectrogram`` — DIVERGES from the mtmd flavor above: reflect-200
//! head from the RAW input (no 31 s pre-extend), 30 s zeros + 200 tail, n_len drops the last
//! frame, frames past the real audio skip the FFT (every bin = log10(1e-10)), floor 1e-10,
//! filterbank comes from the model file. Same global max−8 clamp + (x+4)/4.
def log_mel_whisper(samples : array<float> | #; filters : array<float>; n_mel : int64) : WhisperMel {
    let n_in = int64(length(samples))
    let head = AUDIO_N_FFT / 2l                            // 200
    let n_padded = n_in + AUDIO_SAMPLE_RATE * 30l + 2l * head
    var padded : array<float>
    padded |> resize(int(n_padded))                        // resize zero-fills (the whole tail)
    for (i in range(int(n_in))) {
        padded[int(head) + i] = samples[i]
    }
    let nref = clamp(n_in - 1l, 0l, head)                  // whisper.cpp reads samples[1..200] unguarded
    for (i in range64(nref)) {
        padded[head - 1l - i] = samples[i + 1l]
    }

    var m = WhisperMel(n_mel = n_mel)
    m.n_len = (n_padded - AUDIO_N_FFT) / AUDIO_HOP         // "remove the last frame"
    m.n_len_org = 1l + (n_in + head - AUDIO_N_FFT) / AUDIO_HOP
    m.data |> resize(int(n_mel * m.n_len))

    // frames whose window starts inside the real (head-padded) audio get the FFT; the rest
    // are pure zero-tail and fill with log10(1e-10) directly
    let n_fft = AUDIO_N_FFT
    let n_bins = n_fft / 2l + 1l
    let n_compute = min((n_in + head) / AUDIO_HOP + 1l, m.n_len)
    let hann <- build_hann_window(n_fft)
    let twiddles <- build_dft_twiddles(n_fft)

    var xw : array<float>
    xw |> resize(int(n_compute * n_fft))
    for (i in range64(n_compute)) {
        let off = i * AUDIO_HOP
        for (j in range64(n_fft)) {
            xw[i * n_fft + j] = hann[j] * padded[off + j]
        }
    }
    var reim : array<float>
    reim |> resize(int(n_compute * n_bins * 2l))
    gemm_f32(unsafe(addr(reim[0])), unsafe(addr(xw[0])), unsafe(addr(twiddles[0])),
             n_compute, n_fft, n_bins * 2l)

    // power -> mel: float products in groups of 4 summed in float, each group added to a
    // double accumulator — whisper.cpp's exact unrolled accumulation
    let log10_e = 0.43429448190325176lf
    let fill = float(log(1e-10lf) * log10_e)
    var power : array<float>
    power |> resize(int(n_bins))
    for (i in range64(n_compute)) {
        for (k in range64(n_bins)) {
            let re = reim[i * n_bins * 2l + k * 2l]
            let im = reim[i * n_bins * 2l + k * 2l + 1l]
            power[k] = re * re + im * im
        }
        for (j in range64(n_mel)) {
            var sum = 0.0lf
            var k = 0l
            while (k + 3l < n_bins) {
                sum += double(power[k] * filters[j * n_bins + k]
                    + power[k + 1l] * filters[j * n_bins + k + 1l]
                    + power[k + 2l] * filters[j * n_bins + k + 2l]
                    + power[k + 3l] * filters[j * n_bins + k + 3l])
                k += 4l
            }
            while (k < n_bins) {
                sum += double(power[k] * filters[j * n_bins + k])
                k++
            }
            m.data[j * m.n_len + i] = float(log(max(sum, 1e-10lf)) * log10_e)
        }
    }
    for (i in range64(n_compute, m.n_len)) {
        for (j in range64(n_mel)) {
            m.data[j * m.n_len + i] = fill
        }
    }

    // global max−8 clamp + (x+4)/4, double math over float storage (same as the mtmd flavor)
    var mmax = -1e20lf
    for (v in m.data) {
        mmax = max(mmax, double(v))
    }
    mmax -= 8.0lf
    for (v in m.data) {
        let clamped = double(v) < mmax ? float(mmax) : v
        v = float((double(clamped) + 4.0lf) / 4.0lf)
    }
    return <- m
}

//! Slice one 3000-frame encoder window starting at mel frame ``seek``; frames past
//! ``m.n_len`` zero-fill (whisper.cpp's conv-input copy).
def whisper_mel_window(m : WhisperMel; seek : int64) : MelChunk {
    var c = MelChunk(n_mel = m.n_mel, n_len = AUDIO_CHUNK_FRAMES)
    c.data |> resize(int(m.n_mel * AUDIO_CHUNK_FRAMES))
    let i0 = min(seek, m.n_len)
    let i1 = min(seek + AUDIO_CHUNK_FRAMES, m.n_len)
    for (j in range64(m.n_mel)) {
        for (i in range64(i1 - i0)) {
            c.data[j * AUDIO_CHUNK_FRAMES + i] = m.data[j * m.n_len + i0 + i]
        }
    }
    return <- c
}

// ===== Whisper encoder tower (fp32 bring-up; q8 fast path is ledgered) =====

//! Which projector tail maps encoder positions to decoder soft tokens (mtmd family names).
enum AudioProjKind {
    qwen2a      // avg-pool -> post-LN -> linear w+b (Qwen2-Audio; Qwen2.5-Omni audio is identical)
    ultravox    // post-LN -> stack(8) -> RMS-pre -> mm1 -> swiglu_swapped -> RMS-mid -> mm2 (no biases)
    voxtral     // avg-pool -> post-LN -> stack(4) -> mm1 -> gelu_erf -> mm2 (no biases)
}

//! The audio tower: Whisper encoder weights + a model-specific projector tail, all fp32 in
//! one blob. Per-layer tensors sit at ``layers_off + l·layer_stride`` in the fixed order
//! ``enc_layer_offsets`` computes — the loader lays them out, forward never touches names.
struct AudioTower {
    n_mel : int64
    d_model : int64
    n_head : int64
    n_layer : int64
    n_ff : int64
    n_ctx : int64      // encoder positions per chunk (1500 = 3000 mel frames / conv stride 2)
    proj_dim : int64   // decoder embedding width the projector maps into (0 = no projector)
    gelu_tanh : bool = false  // whisper.cpp oracle uses the tanh-fp16-LUT gelu; mtmd uses erf
    eps : float = 1e-5
    proj_kind : AudioProjKind = AudioProjKind.qwen2a
    stack_factor : int64 = 1  // frame-concat width before the projector (ultravox 8, voxtral 4)
    mm1_out : int64 = 0l      // projector hidden width (ultravox: pre-swiglu, voxtral: pre-gelu)
    has_k_bias : bool = false // qwen3a attention carries a k bias; whisper towers don't
    fblob : array<float>
    conv1_w_off : int64
    conv1_b_off : int64
    conv2_w_off : int64
    conv2_b_off : int64
    pos_off : int64
    layers_off : int64
    layer_stride : int64
    lnp_w_off : int64
    lnp_b_off : int64
    proj_w_off : int64        // qwen2a: fc weight; ultravox/voxtral: mm1 weight
    proj_b_off : int64        // qwen2a: fc bias
    normpre_off : int64       // ultravox RMS-pre weight [d·stack]
    normmid_off : int64       // ultravox RMS-mid weight [mm1_out/2]
    mm2_w_off : int64         // ultravox/voxtral second projector matrix
}

def audio_has_avgpool(t : AudioTower) : bool => (
    t.proj_kind == AudioProjKind.qwen2a || t.proj_kind == AudioProjKind.voxtral)

//! Soft tokens one 30 s (3000-frame) mel chunk becomes after the projector — matches mtmd's
//! clip_n_output_tokens: conv halves, avg-pool halves, stacking divides (floor: the ragged
//! tail positions are DROPPED, mirroring ggml's build_stack view math — no zero-pad row).
def audio_tokens_per_chunk(t : AudioTower) : int64 {
    var n = t.n_ctx
    if (audio_has_avgpool(t)) {
        n /= 2l
    }
    if (t.stack_factor > 1l) {
        n /= t.stack_factor
    }
    return n
}

// Per-layer tensor offsets inside fblob, in layout order. conv weights are stored PERMUTED
// for the im2col column order (dk-major, then channel): W'[o][dk·C + c] = torch_w[o][c][dk].
struct LayerOffs {
    ln1_w : int64
    ln1_b : int64
    q_w : int64
    q_b : int64
    k_w : int64
    k_b : int64   // whisper towers have no k bias — the slot stays zeroed and is skipped
    v_w : int64
    v_b : int64
    o_w : int64
    o_b : int64
    ln2_w : int64
    ln2_b : int64
    fc1_w : int64
    fc1_b : int64
    fc2_w : int64
    fc2_b : int64
}

def enc_layer_offsets(t : AudioTower; l : int64) : LayerOffs {
    let d = t.d_model
    let ff = t.n_ff
    var o = t.layers_off + l * t.layer_stride
    var r = LayerOffs()
    r.ln1_w = o; o += d
    r.ln1_b = o; o += d
    r.q_w = o; o += d * d
    r.q_b = o; o += d
    r.k_w = o; o += d * d
    r.k_b = o; o += d
    r.v_w = o; o += d * d
    r.v_b = o; o += d
    r.o_w = o; o += d * d
    r.o_b = o; o += d
    r.ln2_w = o; o += d
    r.ln2_b = o; o += d
    r.fc1_w = o; o += ff * d
    r.fc1_b = o; o += ff
    r.fc2_w = o; o += d * ff
    r.fc2_b = o; o += d
    return r
}

// 4 square attn mats + 2 ffn mats + 9 d-vectors (ln1 w/b, q/k/v/o bias, ln2 w/b, fc2 bias) + fc1 bias
def enc_layer_stride(d, ff : int64) : int64 => 4l * d * d + 2l * ff * d + 9l * d + ff

//! LayerNorm row: o = (x − mean)/√(var + eps)·w + b, mean/var double-accumulated over the
//! row (ggml_norm's exact shape; the decoder only has RMS so this is new). Population var.
def layernorm(var o : float?; x, w, b : float const?; size : int64; eps : float) {
    unsafe {
        var mean = 0.0lf
        for (i in range64(size)) {
            mean += double(x[i])
        }
        mean /= double(size)
        var variance = 0.0lf
        for (i in range64(size)) {
            let dv = double(x[i]) - mean
            variance += dv * dv
        }
        variance /= double(size)
        let scale = 1.0 / sqrt(float(variance) + eps)
        let fmean = float(mean)
        for (i in range64(size)) {
            o[i] = (x[i] - fmean) * scale * w[i] + b[i]
        }
    }
}

//! Threaded per-position layernorm over token-major rows (rms_batch's shape, LN math),
//! weight/bias read from ``blob`` at the given offsets.
def layernorm_batch(var out : array<float>; src : array<float>; blob : array<float>; w_off, b_off, dim, npos : int64; eps : float) {
    unsafe {
        var op = addr(out[0])
        let ip = reinterpret<float const?>(addr(src[0]))
        let wp = reinterpret<float const?>(addr(blob[w_off]))
        let bp = reinterpret<float const?>(addr(blob[b_off]))
        maybe_parallel_for(0, int(npos), get_dispatch_lanes()) $(rb, re) {
            unsafe {
                for (p in range(rb, re)) {
                    let off = int64(p) * dim
                    layernorm(op + off, ip + off, wp, bp, dim, eps)
                }
            }
        }
    }
}

//! y[p] += blob[b_off .. b_off+d) for every row (projection bias)
def add_bias_rows(var y : array<float>; blob : array<float>; b_off, d, npos : int64) {
    for (p in range64(npos)) {
        for (i in range64(d)) {
            y[p * d + i] += blob[b_off + i]
        }
    }
}

//! x += r, elementwise (residual)
def add_inplace_rows(var x : array<float>; r : array<float>; n : int64) {
    for (i in range64(n)) {
        x[i] += r[i]
    }
}

//! fp32 matmul against a blob region: Y [npos×d] = W[d×n]·X[npos×n] (threaded matmul_batch)
def mm_blob_b(var y : array<float>; blob : array<float>; woff : int64; x : array<float>; n, d, npos : int64) {
    array_view(blob, woff, n * d) $(w : array<float>#) {
        matmul_batch(y, w, x, n, d, npos)
    }
}

// Read a conv1d weight (GGUF flat [c_out][c_in][k], k contiguous — torch layout) permuted to
// the im2col order W'[o][dk·C + c].
def private load_conv_permuted(m : GGUFMeta; bytes : array<uint8> | #; name : string;
                               var blob : array<float>; off : int64; c_out, c_in : int64) {
    var raw : array<float>
    raw |> resize(int(c_out * c_in * 3l))
    gguf_read_tensor_f32(m, bytes, name, raw, 0l, c_out * c_in * 3l)
    for (o in range64(c_out)) {
        for (c in range64(c_in)) {
            for (k in range64(3l)) {
                blob[off + o * c_in * 3l + k * c_in + c] = raw[o * c_in * 3l + c * 3l + k]
            }
        }
    }
}

//! Load an audio mmproj GGUF (projector ``qwen2a`` / ``qwen2.5o`` / ``ultravox`` / ``voxtral``)
//! into an AudioTower: hparams from the ``clip.audio.*`` keys, every tensor fp32 into the blob
//! in ``enc_layer_offsets`` order, conv weights permuted for im2col. Vision tensors in a
//! combined omni mmproj are skipped (the loader only reads ``a.*`` / ``mm.a.*`` names).
def load_audio_tower(path : string) : AudioTower {
    var t = AudioTower()
    let f = fopen(path, "rb")
    if (f == null) {
        panic("dasLLAMA: cannot open mmproj gguf '{path}'")
    }
    fmap(f) $(var bytes : array<uint8>#) {
        let m <- parse_gguf_meta(bytes)
        let proj = gguf_str(m, bytes, "clip.projector_type")
        if (proj == "qwen2a" || proj == "qwen2.5o") {   // omni's audio side is qwen2a verbatim
            t.proj_kind = AudioProjKind.qwen2a
        } elif (proj == "ultravox") {
            t.proj_kind = AudioProjKind.ultravox
        } elif (proj == "voxtral") {
            t.proj_kind = AudioProjKind.voxtral
        } else {
            panic("dasLLAMA: audio tower supports qwen2a/qwen2.5o/ultravox/voxtral projectors, got '{proj}'")
        }
        t.n_mel = gguf_int(m, bytes, "clip.audio.num_mel_bins")
        t.d_model = gguf_int(m, bytes, "clip.audio.embedding_length")
        t.n_head = gguf_int(m, bytes, "clip.audio.attention.head_count")
        t.n_layer = gguf_int(m, bytes, "clip.audio.block_count")
        t.n_ff = gguf_int(m, bytes, "clip.audio.feed_forward_length")
        t.proj_dim = gguf_int(m, bytes, "clip.audio.projection_dim")
        if (gguf_has(m, "clip.audio.attention.layer_norm_epsilon")) {
            t.eps = gguf_f32(m, bytes, "clip.audio.attention.layer_norm_epsilon")
        }
        if (gguf_has(m, "clip.audio.projector.stack_factor")) {
            t.stack_factor = gguf_int(m, bytes, "clip.audio.projector.stack_factor")
        }
        let d = t.d_model
        let ff = t.n_ff
        let nm = t.n_mel
        // encoder positions from the position-embedding tensor (1500 for whisper-large-v3)
        let pi = gguf_find_tensor(m, "a.position_embd.weight")
        if (pi < 0) {
            panic("dasLLAMA: a.position_embd.weight missing from mmproj")
        }
        t.n_ctx = m.tensors[pi].n_elem / d

        // projector shapes from the tensors themselves — clip.audio.projection_dim lies for
        // ultravox-1b (the GGUF says 4096; mm2 actually projects into the 2048-wide decoder)
        var mm1_in = 0l
        if (t.proj_kind != AudioProjKind.qwen2a) {
            mm1_in = d * t.stack_factor
            let i1 = gguf_find_tensor(m, "mm.a.mlp.1.weight")
            let i2 = gguf_find_tensor(m, "mm.a.mlp.2.weight")
            if (i1 < 0 || i2 < 0) {
                panic("dasLLAMA: mm.a.mlp.1/2.weight missing from '{proj}' mmproj")
            }
            t.mm1_out = m.tensors[i1].n_elem / mm1_in
            let mm2_in = t.proj_kind == AudioProjKind.ultravox ? t.mm1_out / 2l : t.mm1_out
            t.proj_dim = m.tensors[i2].n_elem / mm2_in
        }

        // fixed blob layout: convs, pos, per-layer region, post-ln, projector
        var o = 0l
        t.conv1_w_off = o; o += d * 3l * nm
        t.conv1_b_off = o; o += d
        t.conv2_w_off = o; o += d * 3l * d
        t.conv2_b_off = o; o += d
        t.pos_off = o; o += t.n_ctx * d
        t.layers_off = o
        t.layer_stride = enc_layer_stride(d, ff)
        o += t.n_layer * t.layer_stride
        t.lnp_w_off = o; o += d
        t.lnp_b_off = o; o += d
        if (t.proj_kind == AudioProjKind.qwen2a) {
            t.proj_w_off = o; o += t.proj_dim * d
            t.proj_b_off = o; o += t.proj_dim
        } elif (t.proj_kind == AudioProjKind.ultravox) {
            t.normpre_off = o; o += mm1_in
            t.proj_w_off = o; o += t.mm1_out * mm1_in
            t.normmid_off = o; o += t.mm1_out / 2l
            t.mm2_w_off = o; o += t.proj_dim * (t.mm1_out / 2l)
        } else {   // voxtral
            t.proj_w_off = o; o += t.mm1_out * mm1_in
            t.mm2_w_off = o; o += t.proj_dim * t.mm1_out
        }
        t.fblob |> resize(int(o))

        load_conv_permuted(m, bytes, "a.conv1d.1.weight", t.fblob, t.conv1_w_off, d, nm)
        gguf_read_tensor_f32(m, bytes, "a.conv1d.1.bias", t.fblob, t.conv1_b_off, d)
        load_conv_permuted(m, bytes, "a.conv1d.2.weight", t.fblob, t.conv2_w_off, d, d)
        gguf_read_tensor_f32(m, bytes, "a.conv1d.2.bias", t.fblob, t.conv2_b_off, d)
        gguf_read_tensor_f32(m, bytes, "a.position_embd.weight", t.fblob, t.pos_off, t.n_ctx * d)
        for (l in range64(t.n_layer)) {
            let lo = enc_layer_offsets(t, l)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ln1.weight", t.fblob, lo.ln1_w, d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ln1.bias", t.fblob, lo.ln1_b, d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.attn_q.weight", t.fblob, lo.q_w, d * d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.attn_q.bias", t.fblob, lo.q_b, d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.attn_k.weight", t.fblob, lo.k_w, d * d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.attn_v.weight", t.fblob, lo.v_w, d * d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.attn_v.bias", t.fblob, lo.v_b, d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.attn_out.weight", t.fblob, lo.o_w, d * d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.attn_out.bias", t.fblob, lo.o_b, d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ln2.weight", t.fblob, lo.ln2_w, d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ln2.bias", t.fblob, lo.ln2_b, d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ffn_up.weight", t.fblob, lo.fc1_w, ff * d)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ffn_up.bias", t.fblob, lo.fc1_b, ff)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ffn_down.weight", t.fblob, lo.fc2_w, d * ff)
            gguf_read_tensor_f32(m, bytes, "a.blk.{l}.ffn_down.bias", t.fblob, lo.fc2_b, d)
        }
        gguf_read_tensor_f32(m, bytes, "a.post_ln.weight", t.fblob, t.lnp_w_off, d)
        gguf_read_tensor_f32(m, bytes, "a.post_ln.bias", t.fblob, t.lnp_b_off, d)
        if (t.proj_kind == AudioProjKind.qwen2a) {
            gguf_read_tensor_f32(m, bytes, "mm.a.fc.weight", t.fblob, t.proj_w_off, t.proj_dim * d)
            gguf_read_tensor_f32(m, bytes, "mm.a.fc.bias", t.fblob, t.proj_b_off, t.proj_dim)
        } elif (t.proj_kind == AudioProjKind.ultravox) {
            let m1in = d * t.stack_factor
            gguf_read_tensor_f32(m, bytes, "mm.a.norm_pre.weight", t.fblob, t.normpre_off, m1in)
            gguf_read_tensor_f32(m, bytes, "mm.a.mlp.1.weight", t.fblob, t.proj_w_off, t.mm1_out * m1in)
            gguf_read_tensor_f32(m, bytes, "mm.a.norm_mid.weight", t.fblob, t.normmid_off, t.mm1_out / 2l)
            gguf_read_tensor_f32(m, bytes, "mm.a.mlp.2.weight", t.fblob, t.mm2_w_off, t.proj_dim * (t.mm1_out / 2l))
        } else {   // voxtral
            let m1in = d * t.stack_factor
            gguf_read_tensor_f32(m, bytes, "mm.a.mlp.1.weight", t.fblob, t.proj_w_off, t.mm1_out * m1in)
            gguf_read_tensor_f32(m, bytes, "mm.a.mlp.2.weight", t.fblob, t.mm2_w_off, t.proj_dim * t.mm1_out)
        }
    }
    fclose(f)
    return <- t
}

//! Encoder scratch, sized once per tower and reused across chunks/calls.
struct EncoderState {
    x1 : array<float>    // conv1 im2col [T_in × 3·n_mel]
    y1 : array<float>    // conv1 out [T_in × d]
    x2 : array<float>    // conv2 im2col [T × 3·d]
    x : array<float>     // residual stream [T × d]
    xb : array<float>    // norm output [T × d]
    xb2 : array<float>   // attn/ffn projection out [T × d]
    qq : array<float>    // q token-major [T × d]
    kk : array<float>    // k token-major [T × d]
    vv : array<float>    // v token-major [T × d]
    hp : array<float>    // per-head packs q,kT,v,out: 4 × [T × d]
    att : array<float>   // per-head blocked scores [n_head × ATTN_ENC_QB × T]
    h : array<float>     // ffn hidden [T × ff]
    pooled : array<float>// [T/2 × d]
    ph : array<float>    // projector hidden [rows × mm1_out] (ultravox/voxtral)
    pg : array<float>    // ultravox swiglu output [rows × mm1_out/2]
    out : array<float>   // projected soft tokens [tokens_per_chunk × proj_dim]
}

let ATTN_ENC_QB = 128l  // query rows per attention score block (15 MB att scratch at T=1500)

def make_encoder_state(t : AudioTower) : EncoderState {
    let tin = AUDIO_CHUNK_FRAMES
    let tt = t.n_ctx
    let d = t.d_model
    var s = EncoderState()
    s.x1 |> resize(int(tin * 3l * t.n_mel))
    s.y1 |> resize(int(tin * d))
    s.x2 |> resize(int(tt * 3l * d))
    s.x |> resize(int(tt * d))
    s.xb |> resize(int(tt * d))
    s.xb2 |> resize(int(tt * d))
    s.qq |> resize(int(tt * d))
    s.kk |> resize(int(tt * d))
    s.vv |> resize(int(tt * d))
    s.hp |> resize(int(4l * tt * d))
    s.att |> resize(int(t.n_head * ATTN_ENC_QB * tt))
    s.h |> resize(int(tt * t.n_ff))
    s.pooled |> resize(int(tt / 2l * d))
    let rows = audio_tokens_per_chunk(t)
    if (t.proj_kind != AudioProjKind.qwen2a) {
        s.ph |> resize(int(rows * t.mm1_out))
        if (t.proj_kind == AudioProjKind.ultravox) {
            s.pg |> resize(int(rows * t.mm1_out / 2l))
        }
    }
    s.out |> resize(int(rows * t.proj_dim))
    return <- s
}

// Non-causal blocked attention over gemm_f32, parallel across heads: per head, pack Q/Kᵀ/V,
// then per ATTN_ENC_QB query rows score = Q·Kᵀ (scale + full-row softmax) and out = P·V.
// No cache, no mask — every position sees all `tt` positions.
def private enc_attention(t : AudioTower; var s : EncoderState; tt : int64) {
    let d = t.d_model
    let hs = d / t.n_head
    let scale = 1.0 / sqrt(float(hs))
    unsafe {
        let qp = reinterpret<float const?>(addr(s.qq[0]))
        let kp = reinterpret<float const?>(addr(s.kk[0]))
        let vp = reinterpret<float const?>(addr(s.vv[0]))
        var hpp = addr(s.hp[0])
        var attp = addr(s.att[0])
        var aop = addr(s.xb2[0])
        maybe_parallel_for(0, int(t.n_head), get_dispatch_lanes()) $(hb, he) {
            unsafe {
                for (h in range(hb, he)) {
                    let hoff = int64(h) * hs
                    // per-head pack region: q [tt×hs], kT [hs×tt], v [tt×hs], oh [tt×hs]
                    var qh = hpp + int64(h) * 4l * tt * hs
                    var kt = qh + tt * hs
                    var vh = kt + tt * hs
                    var oh = vh + tt * hs
                    for (p in range64(tt)) {
                        for (j in range64(hs)) {
                            qh[p * hs + j] = qp[p * d + hoff + j]
                            kt[j * tt + p] = kp[p * d + hoff + j]
                            vh[p * hs + j] = vp[p * d + hoff + j]
                        }
                    }
                    var ah = attp + int64(h) * ATTN_ENC_QB * tt
                    var qb0 = 0l
                    while (qb0 < tt) {
                        let qbn = min(ATTN_ENC_QB, tt - qb0)
                        for (i in range64(qbn * tt)) {
                            ah[i] = 0.0
                        }
                        gemm_f32(ah, qh + qb0 * hs, kt, qbn, hs, tt)
                        for (r in range64(qbn)) {
                            var row = ah + r * tt
                            for (i in range64(tt)) {
                                row[i] *= scale
                            }
                            softmax(row, tt)
                        }
                        for (i in range64(qbn * hs)) {
                            oh[qb0 * hs + i] = 0.0
                        }
                        gemm_f32(oh + qb0 * hs, ah, vh, qbn, tt, hs)
                        qb0 += qbn
                    }
                    // scatter head output back to token-major xb2
                    for (p in range64(tt)) {
                        for (j in range64(hs)) {
                            aop[p * d + hoff + j] = oh[p * hs + j]
                        }
                    }
                }
            }
        }
    }
}

// Stage-diff witness: when set (debug only), audio_encode maxdiffs each stage against
// <dir>/np_<stage>.f32 raw dumps (the numpy oracle in the arc's scratchpad rig).
var g_audio_ref_dir = ""

def set_audio_encode_ref_dir(dir : string) {
    g_audio_ref_dir = dir
}

def private diff_stage(name : string; x : array<float>; n : int64) {
    if (empty(g_audio_ref_dir)) {
        return
    }
    let f = fopen("{g_audio_ref_dir}/np_{name}.f32", "rb")
    if (f == null) {
        print("stage {name}: no ref file\n")
        return
    }
    fmap(f) $(var bytes : array<uint8>#) {
        var maxd = 0.0
        var maxi = 0
        unsafe {
            let rp = reinterpret<float?>(addr(bytes[0]))
            // int loop: raw-pointer indexing by int64 is AOT-ambiguous (das_index<T*>::at
            // only has int32/uint32 overloads); witness stages are far below 2^31 floats
            for (i in range(int(n))) {
                let d = abs(x[i] - rp[i])
                if (d > maxd) {
                    maxd = d
                    maxi = i
                }
            }
            print("stage {name}: maxdiff {maxd} at {maxi} (das {x[maxi]} ref {rp[maxi]})\n")
        }
    }
    fclose(f)
}

// t.gelu_tanh selects the oracle-exact activation flavor (see gelu_tanh_lut)
def private enc_gelu(t : AudioTower; var x : array<float>; size : int64) {
    if (t.gelu_tanh) {
        gelu_tanh_lut(x, size)
    } else {
        gelu_erf(x, size)
    }
}

//! The shared Whisper-encoder core over one 30 s mel chunk: conv frontend, +pos rows, all
//! pre-LN transformer blocks. Leaves the residual stream in ``s.x`` (``n_ctx × d_model``);
//! the model-specific tail (whisper: ln_post; qwen2a: pool → ln_post → projector) is the
//! caller's.
def audio_encode_blocks(t : AudioTower; var s : EncoderState; mel : MelChunk) {
    if (mel.n_len != AUDIO_CHUNK_FRAMES || mel.n_mel != t.n_mel) {
        panic("audio_encode: mel chunk is {mel.n_mel}x{mel.n_len}, want {t.n_mel}x{AUDIO_CHUNK_FRAMES}")
    }
    let tin = AUDIO_CHUNK_FRAMES
    let tt = t.n_ctx
    let d = t.d_model
    let nm = t.n_mel

    // conv1 k3 s1 same: im2col column (dk, c) — matches the loader's weight permute
    for (i in range64(tin)) {
        for (dk in range64(3l)) {
            let src = i + dk - 1l
            for (c in range64(nm)) {
                s.x1[i * 3l * nm + dk * nm + c] = (src >= 0l && src < tin
                    ? mel.data[c * tin + src]
                    : 0.0)
            }
        }
    }
    mm_blob_b(s.y1, t.fblob, t.conv1_w_off, s.x1, 3l * nm, d, tin)
    add_bias_rows(s.y1, t.fblob, t.conv1_b_off, d, tin)
    enc_gelu(t, s.y1, tin * d)

    // conv2 k3 s2 same -> T = tin/2 positions
    for (i in range64(tt)) {
        for (dk in range64(3l)) {
            let src = 2l * i + dk - 1l
            for (c in range64(d)) {
                s.x2[i * 3l * d + dk * d + c] = (src >= 0l && src < tin
                    ? s.y1[src * d + c]
                    : 0.0)
            }
        }
    }
    mm_blob_b(s.x, t.fblob, t.conv2_w_off, s.x2, 3l * d, d, tt)
    add_bias_rows(s.x, t.fblob, t.conv2_b_off, d, tt)
    enc_gelu(t, s.x, tt * d)

    // + learned/sinusoidal position rows (loaded from the mmproj)
    for (i in range64(tt * d)) {
        s.x[i] += t.fblob[t.pos_off + i]
    }
    diff_stage("after_conv_pos", s.x, tt * d)

    encoder_blocks(t, s, tt)
}

//! The pre-LN transformer block loop over ``npos`` positions of the residual stream in ``s.x``
//! (token-major). Shared by the whisper conv frontend above and the qwen3a conv2d frontend —
//! any frontend that leaves ``npos × d_model`` rows in ``s.x`` can run the blocks.
def encoder_blocks(t : AudioTower; var s : EncoderState; npos : int64) {
    let tt = npos
    let d = t.d_model
    for (l in range64(t.n_layer)) {
        let lo = enc_layer_offsets(t, l)
        layernorm_batch(s.xb, s.x, t.fblob, lo.ln1_w, lo.ln1_b, d, tt, t.eps)
        mm_blob_b(s.qq, t.fblob, lo.q_w, s.xb, d, d, tt)
        mm_blob_b(s.kk, t.fblob, lo.k_w, s.xb, d, d, tt)
        mm_blob_b(s.vv, t.fblob, lo.v_w, s.xb, d, d, tt)
        add_bias_rows(s.qq, t.fblob, lo.q_b, d, tt)   // q bias
        if (t.has_k_bias) {
            add_bias_rows(s.kk, t.fblob, lo.k_b, d, tt)
        }
        add_bias_rows(s.vv, t.fblob, lo.v_b, d, tt)   // v bias
        if (l == 0l) {
            diff_stage("b0_ln1", s.xb, tt * d)
            diff_stage("b0_q", s.qq, tt * d)
            diff_stage("b0_k", s.kk, tt * d)
            diff_stage("b0_v", s.vv, tt * d)
        }
        enc_attention(t, s, tt)
        if (l == 0l) {
            diff_stage("b0_attnout", s.xb2, tt * d)
        }
        mm_blob_b(s.xb, t.fblob, lo.o_w, s.xb2, d, d, tt)
        add_bias_rows(s.xb, t.fblob, lo.o_b, d, tt)
        add_inplace_rows(s.x, s.xb, tt * d)

        layernorm_batch(s.xb, s.x, t.fblob, lo.ln2_w, lo.ln2_b, d, tt, t.eps)
        mm_blob_b(s.h, t.fblob, lo.fc1_w, s.xb, d, t.n_ff, tt)
        add_bias_rows(s.h, t.fblob, lo.fc1_b, t.n_ff, tt)
        enc_gelu(t, s.h, tt * t.n_ff)
        mm_blob_b(s.xb2, t.fblob, lo.fc2_w, s.h, t.n_ff, d, tt)
        add_bias_rows(s.xb2, t.fblob, lo.fc2_b, d, tt)
        add_inplace_rows(s.x, s.xb2, tt * d)
        if (l == 0l) {
            diff_stage("after_block0", s.x, tt * d)
        }
    }
    diff_stage("after_blocks", s.x, tt * d)
}

//! Per-row swiglu with ggml's swapped halves: out[r][i] = silu(x[r][half+i]) · x[r][i]
//! (ultravox_model.py's SwiGLU — silu on the SECOND half, passthrough on the first).
def swiglu_swapped_rows(var o : array<float>; x : array<float>; half, rows : int64) {
    for (r in range64(rows)) {
        for (i in range64(half)) {
            o[r * half + i] = x[r * 2l * half + half + i]
        }
    }
    silu(o, rows * half)
    for (r in range64(rows)) {
        for (i in range64(half)) {
            o[r * half + i] *= x[r * 2l * half + i]
        }
    }
}

// RMS-norm each d-wide row in place against a weight vector in the blob (ultravox projector
// norms use eps 1e-6 hardcoded in mtmd's whisper-enc graph, independent of the tower eps)
def private rms_rows_blob(var x : array<float>; blob : array<float>; w_off, dim, rows : int64) {
    unsafe {
        var xp = addr(x[0])
        let wp = reinterpret<float const?>(addr(blob[w_off]))
        for (r in range64(rows)) {
            rmsnorm(xp + r * dim, xp + r * dim, wp, dim, 1e-6)
        }
    }
}

//! Run the Whisper encoder + the model's projector tail over one 30 s mel chunk. Output lands
//! in ``s.out``: ``audio_tokens_per_chunk`` soft tokens × ``proj_dim``. Stacking is a flat
//! reinterpret of the token-major stream as rows of ``d·stack`` — floor rows, ragged tail
//! positions dropped (ggml build_stack's view math; zero-padding never reaches the projector).
def audio_encode(t : AudioTower; var s : EncoderState; mel : MelChunk) {
    audio_encode_blocks(t, s, mel)
    let tt = t.n_ctx
    let d = t.d_model
    let rows = audio_tokens_per_chunk(t)

    if (t.proj_kind == AudioProjKind.qwen2a) {
        // avg-pool pairs over time (BEFORE the post-LN — mtmd build_vit order), then ln_post
        let tp = tt / 2l
        for (p in range64(tp)) {
            for (c in range64(d)) {
                s.pooled[p * d + c] = 0.5 * (s.x[2l * p * d + c] + s.x[(2l * p + 1l) * d + c])
            }
        }
        layernorm_batch(s.pooled, s.pooled, t.fblob, t.lnp_w_off, t.lnp_b_off, d, tp, t.eps)

        // projector: one linear into the decoder's embedding space
        mm_blob_b(s.out, t.fblob, t.proj_w_off, s.pooled, d, t.proj_dim, tp)
        add_bias_rows(s.out, t.fblob, t.proj_b_off, t.proj_dim, tp)
    } elif (t.proj_kind == AudioProjKind.ultravox) {
        // post-LN over all positions (no avg-pool), stacked rows straight off s.xb's memory
        layernorm_batch(s.xb, s.x, t.fblob, t.lnp_w_off, t.lnp_b_off, d, tt, t.eps)
        let m1in = d * t.stack_factor
        rms_rows_blob(s.xb, t.fblob, t.normpre_off, m1in, rows)   // RMS-pre on stacked rows
        mm_blob_b(s.ph, t.fblob, t.proj_w_off, s.xb, m1in, t.mm1_out, rows)
        swiglu_swapped_rows(s.pg, s.ph, t.mm1_out / 2l, rows)
        rms_rows_blob(s.pg, t.fblob, t.normmid_off, t.mm1_out / 2l, rows)
        mm_blob_b(s.out, t.fblob, t.mm2_w_off, s.pg, t.mm1_out / 2l, t.proj_dim, rows)
    } else {   // voxtral: avg-pool -> post-LN -> stack -> mm1 -> gelu_erf -> mm2
        let tp = tt / 2l
        for (p in range64(tp)) {
            for (c in range64(d)) {
                s.pooled[p * d + c] = 0.5 * (s.x[2l * p * d + c] + s.x[(2l * p + 1l) * d + c])
            }
        }
        layernorm_batch(s.pooled, s.pooled, t.fblob, t.lnp_w_off, t.lnp_b_off, d, tp, t.eps)
        let m1in = d * t.stack_factor
        mm_blob_b(s.ph, t.fblob, t.proj_w_off, s.pooled, m1in, t.mm1_out, rows)
        gelu_erf(s.ph, rows * t.mm1_out)
        mm_blob_b(s.out, t.fblob, t.mm2_w_off, s.ph, t.mm1_out, t.proj_dim, rows)
    }
    diff_stage("out", s.out, rows * t.proj_dim)
}
