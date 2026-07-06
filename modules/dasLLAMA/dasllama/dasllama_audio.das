options gen2

module dasllama_audio shared public

require math
require dasllama/dasllama_math

// Whisper-family audio frontend: 16 kHz mono PCM -> log-mel chunks, exactly mirroring
// llama.cpp's mtmd_audio_preprocessor_whisper (tools/mtmd/mtmd-audio.cpp) so the encoder
// sees oracle-identical input. The 400-point DFT is two GEMM columns of a precomputed
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

// DFT twiddle matrix [n_fft][2·n_bins]: column 2k = cos(2πjk/n), column 2k+1 = −sin(2πjk/n).
// XW[frames×n_fft] · B -> interleaved re/im rows, same table values as mtmd's sin/cos cache
// (double theta, float trig).
def private build_dft_twiddles(n_fft : int64) : array<float> {
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
    for (i in range(length(mel))) {
        let clamped = double(mel[i]) < mmax ? float(mmax) : mel[i]
        mel[i] = float((double(clamped) + 4.0lf) / 4.0lf)
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
