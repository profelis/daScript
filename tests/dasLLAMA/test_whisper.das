options gen2
options persistent_heap   // model-scale allocations — freed per test
options stack = 65536

require dastest/testing_boost public
require dasllama/dasllama_whisper
require dasllama/dasllama_asr
require dasllama/dasllama_audio
require dasllama/dasllama_gguf
require dasllama/dasllama_math   // setup_dasllama_jobque_
require daslib/jobque_boost
require daslib/fio
require math
require strings

// Whisper-proper tests. The f16/gelu/mel/id tests are self-contained; the loader and
// transcription tests need a whisper.cpp ggml-tiny.bin (gitignored) and skip without it.
// Oracle constants come from whisper-cli (CPU, greedy: -bs 1 -bo 1 -nf -ng) — the rig and
// the large-v3-turbo parity runs live in modules/dasLLAMA/whisper_plan.md.
def private whisper_models_dir() : string {
    let env = get_env_variable("DASLLAMA_WHISPER_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/whisper.cpp/models/" : env
}

def private samples_dir() : string {
    let env = get_env_variable("DASLLAMA_MODELS_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama.cpp/models/" : env
}

// Minimal RIFF/WAVE reader for the 16-bit PCM mono test fixture (jfk.wav).
def private read_wav_pcm16_mono(path : string) : array<float> {
    var out : array<float>
    let f = fopen(path, "rb")
    if (f == null) {
        return <- out
    }
    fmap(f) $(var bytes : array<uint8>#) {
        let n = int64(length(bytes))
        var o = 12l                       // "RIFF" size "WAVE"
        while (o + 8l <= n) {
            let id = rd_u32(bytes, o)
            let sz = int64(rd_u32(bytes, o + 4l))
            if (id == 0x61746164u) {      // "data"
                let cnt = min(sz, n - o - 8l) / 2l
                out |> resize(int(cnt))
                for (i in range64(cnt)) {
                    var v = int(rd_u16(bytes, o + 8l + i * 2l))
                    if (v >= 32768) {
                        v -= 65536
                    }
                    out[i] = float(v) / 32768.0
                }
                break
            }
            o += 8l + sz + (sz & 1l)
        }
    }
    fclose(f)
    return <- out
}

[test]
def test_f32_to_f16(t : T?) {
    t |> run("round-trips every non-nan f16 pattern") @(t : T?) {
        var bad = 0
        for (h in range(65536)) {
            let hu = uint(h)
            if (((hu >> 10u) & 0x1Fu) == 0x1Fu && (hu & 0x3FFu) != 0u) {
                continue
            }
            if (f32_to_f16(f16_to_f32(hu)) != hu) {
                bad++
            }
        }
        t |> success(bad == 0, "all {65536} patterns round-trip ({bad} failed)")
    }
    t |> run("round-to-nearest-even boundaries match numpy float16") @(t : T?) {
        t |> equal(f32_to_f16(0.1), 0x2e66u)
        t |> equal(f32_to_f16(-1.5), 0xbe00u)
        t |> equal(f32_to_f16(65504.0), 0x7bffu)   // f16 max
        t |> equal(f32_to_f16(65519.9), 0x7bffu)   // just under the overflow tie
        t |> equal(f32_to_f16(65520.0), 0x7c00u)   // IEEE overflow to inf
        t |> equal(f32_to_f16(2.9802322387695312e-8), 0x0u)  // exactly 2^-25: tie to even 0
        t |> equal(f32_to_f16(2.9805302e-8), 0x1u)           // a hair above: min subnormal
        t |> equal(f32_to_f16(10.0), 0x4900u)
    }
}

[test]
def test_gelu_tanh_lut(t : T?) {
    t |> run("matches ggml's GGML_GELU_FP16 table semantics") @(t : T?) {
        var g = [1.0, -1.0, 0.5, 3.0, -0.25, 10.0, -10.0, 9.999, -9.999]
        gelu_tanh_lut(g, 9l)
        // expected = f16(gelu_tanh(f16(x))) via numpy float16, clamps applied pre-conversion
        t |> success(g[0] == 0.84130859375, "gelu(1)")
        t |> success(g[1] == -0.1588134765625, "gelu(-1)")
        t |> success(g[2] == 0.345703125, "gelu(0.5)")
        t |> success(g[3] == 2.99609375, "gelu(3)")
        t |> success(g[4] == -0.100341796875, "gelu(-0.25)")
        t |> success(g[5] == 10.0, "gelu(10) passes through")
        t |> success(g[6] == 0.0, "gelu(-10) clamps to 0")
        t |> success(g[7] == 10.0, "gelu(9.999): f16 rounds up, then passthrough value")
        t |> success(g[8] == 0.0, "gelu(-9.999) -> -0.0")
    }
}

[test]
def test_whisper_mel(t : T?) {
    t |> run("whisper-flavor mel: frame math and silence fill") @(t : T?) {
        // stand-in filterbank (the real one loads from the model file)
        let fb <- build_mel_filterbank(80l, 400l, 16000l)
        var silence : array<float>
        silence |> resize(16000)          // 1 s of zeros
        let m <- log_mel_whisper(silence, fb, 80l)
        t |> equal(m.n_len, (16000l + 480000l) / 160l)                    // no +1: last frame dropped
        t |> equal(m.n_len_org, 1l + (16000l + 200l - 400l) / 160l)       // real-audio frames
        // all-silence spectrogram: every value is ((-10) + 4)/4 = -1.5 after clamp+scale
        var offv = 0
        for (v in m.data) {
            if (abs(v - -1.5) > 1e-6) {
                offv++
            }
        }
        t |> success(offv == 0, "silence normalizes to exactly -1.5 everywhere ({offv} off)")
    }
    t |> run("window slice zero-fills past n_len") @(t : T?) {
        let fb <- build_mel_filterbank(80l, 400l, 16000l)
        var silence : array<float>
        silence |> resize(16000)
        let m <- log_mel_whisper(silence, fb, 80l)
        let win <- whisper_mel_window(m, m.n_len - 10l)
        t |> equal(win.n_len, 3000l)
        t |> success(win.data[0] == -1.5, "first 10 frames real")
        t |> success(win.data[11] == 0.0, "zero-fill past n_len")
    }
}

[test]
def test_whisper_lang_ids(t : T?) {
    t |> run("g_lang order") @(t : T?) {
        t |> equal(whisper_lang_id("en"), 0)
        t |> equal(whisper_lang_id("zh"), 1)
        t |> equal(whisper_lang_id("yue"), 99)
        t |> equal(whisper_lang_id("xx"), -1)
    }
}

[test]
def test_dec_layer_layout(t : T?) {
    t |> run("decoder layer offsets tile by the stride") @(t : T?) {
        var w = WhisperModel()
        w.n_text_state = 384l
        w.dlayers_off = 0l
        w.dlayer_stride = dec_layer_stride(384l)
        let a = dec_layer_offsets(w, 0l)
        let b = dec_layer_offsets(w, 1l)
        t |> equal(b.ln1_w - a.ln1_w, w.dlayer_stride)
        t |> equal(b.fc2_b - a.fc2_b, w.dlayer_stride)
        // the last tensor of layer 0 ends exactly where layer 1 begins
        t |> equal(a.fc2_b + 384l, b.ln1_w)
    }
}

[test]
def test_whisper_loader(t : T?) {
    t |> run("tiny bin: hparams, special ids, vocab (needs ggml-tiny.bin)") @(t : T?) {
        let path = path_join(whisper_models_dir(), "ggml-tiny.bin")
        if (!stat(path).is_valid) {
            t |> success(true, "skipped: ggml-tiny.bin not present")
            return
        }
        let w <- load_whisper_model(path)
        t |> equal(w.n_vocab, 51865l)
        t |> equal(w.enc.n_mel, 80l)
        t |> equal(w.enc.d_model, 384l)
        t |> equal(w.enc.n_layer, 4l)
        t |> equal(w.enc.n_ctx, 1500l)
        t |> equal(w.n_text_ctx, 448l)
        t |> success(w.enc.gelu_tanh, "whisper tower uses the tanh-LUT gelu")
        // multilingual shift: 99 languages
        t |> equal(w.n_lang, 99l)
        t |> equal(w.tok_eot, 50257)
        t |> equal(w.tok_sot, 50258)
        t |> equal(w.tok_transcribe, 50359)
        t |> equal(w.tok_not, 50363)
        t |> equal(w.tok_beg, 50364)
        t |> equal(w.tok_space, 220)
        t |> equal(w.vocab[400], " And")
        t |> equal(w.vocab[50256], "")
    }
}

[test]
def test_asr_surface(t : T?) {
    t |> run("load_asr_model sniffs the bin + caps report whisper honestly") @(t : T?) {
        let model_path = path_join(whisper_models_dir(), "ggml-tiny.bin")
        if (!stat(model_path).is_valid) {
            t |> success(true, "skipped: ggml-tiny.bin not present")
            return
        }
        var m <- load_asr_model(model_path)   // the sniff route: ggml magic + big vocab -> whisper
        t |> equal(m.whisper.n_vocab, 51865l, "loaded through the sniff")
        let c <- caps(m)
        // honest caps: tiny is a 99-language model (n_vocab 51865) — "yue" (id 99) only exists
        // on the large-v3 family; advertising it here would build a colliding language token
        t |> equal(length(c.languages), 99, "trimmed to the model's n_lang")
        t |> equal(c.languages[0], "en")
        t |> equal(c.languages[98], "su", "list ends before yue")
        t |> success(c.translate, "translate")
        t |> success(c.timestamps == AsrTimestamps.segment, "segment timestamps")
        t |> success(!c.streaming, "no native streaming")
        t |> success(!c.prompt, "no prompt conditioning")
        // "auto" on a multilingual model is accepted; a junk code still panics loudly
        let s <- create_session(m, "auto")
        t |> equal(s.w.lang_id, -1, "auto defers detection")
        delete m.whisper.dblob
        delete m.whisper.enc.fblob
    }
}

[test]
def test_qwen3a_tower(t : T?) {
    t |> run("qwen3a tower: conv2d frontend + windowed encode matches mtmd on jfk") @(t : T?) {
        if (!jit_enabled()) {
            t |> success(true, "skipped: interpreted (dasLLAMA model tests are JIT-only)")
            return
        }
        let path = path_join(samples_dir(), "mmproj-Qwen3-ASR-0.6B-bf16.gguf")
        if (!stat(path).is_valid) {
            t |> success(true, "skipped: mmproj-Qwen3-ASR-0.6B-bf16.gguf not present")
            return
        }
        let samples <- read_wav_pcm16_mono(path_join(samples_dir(), "jfk.wav"))
        if (length(samples) == 0) {
            t |> success(true, "skipped: jfk.wav not present")
            return
        }
        var tw <- load_qwen3a_tower(path)
        t |> equal(tw.core.d_model, 896l, "d_model")
        t |> equal(tw.core.n_layer, 18l, "layers")
        t |> equal(tw.core.n_head, 14l, "heads")
        t |> equal(tw.n_ch, 480l, "conv channels")
        t |> equal(tw.proj_dim, 1024l, "proj_dim")
        t |> success(tw.core.has_k_bias, "k bias")
        let mel <- log_mel_qwen3a(samples, tw.core.n_mel)
        t |> equal(mel.n_len, 1101l, "effective mel frames (11 s)")
        var enc <- make_encoder_state(tw.core)
        var cs = Qwen3aConvState()
        with_job_que() {
            setup_dasllama_jobque_()
            let win <- qwen3a_mel_window(mel, 0l)
            t |> equal(win.n_len, 800l, "window 0 padded frames")
            qwen3a_encode(tw, enc, cs, win)
        }
        // llama-mtmd-cli MTMD_DEBUG_EMBEDDINGS (CPU, bf16 mmproj) on jfk window 0: token 0
        // opens 0.043467 -0.015482 -0.032934 0.023813; our fp32 re-orders sit ~1e-4 off.
        t |> success(abs(enc.out[0] - 0.043467) < 5e-3, "tok0[0]")
        t |> success(abs(enc.out[1] + 0.015482) < 5e-3, "tok0[1]")
        t |> success(abs(enc.out[2] + 0.032934) < 5e-3, "tok0[2]")
        t |> success(abs(enc.out[3] - 0.023813) < 5e-3, "tok0[3]")
        delete tw.core.fblob
        delete tw.cblob
    }
}

[test]
def test_parakeet_oracle(t : T?) {
    t |> run("parakeet-TDT greedy on jfk.wav is token-for-token with parakeet-cli") @(t : T?) {
        if (!jit_enabled()) {
            t |> success(true, "skipped: interpreted (dasLLAMA model tests are JIT-only)")
            return
        }
        let path = path_join(whisper_models_dir(), "ggml-parakeet-tdt-0.6b-v2-f32.bin")
        if (!stat(path).is_valid) {
            t |> success(true, "skipped: ggml-parakeet-tdt-0.6b-v2-f32.bin not present")
            return
        }
        let samples <- read_wav_pcm16_mono(path_join(samples_dir(), "jfk.wav"))
        if (length(samples) == 0) {
            t |> success(true, "skipped: jfk.wav not present")
            return
        }
        // through the uniform ASR surface: the sniff routes a small-vocab ggml bin to parakeet
        var m <- load_asr_model(path)
        let c <- caps(m)
        t |> equal(length(c.languages), 1, "English-only")
        t |> success(c.timestamps == AsrTimestamps.segment, "segment timestamps")
        t |> equal(m.pk.n_vocab, 1024l, "vocab")
        t |> equal(m.pk.n_layer, 24l, "layers")
        t |> equal(m.pk.durations[4], 4, "tdt durations")
        with_job_que() {
            setup_dasllama_jobque_()
            var s <- create_session(m)
            var segs : array<TranscribeSegment>
            transcribe(m, s, samples) $(seg) {
                segs |> push_clone(seg)
            }
            // parakeet-cli -ng -ps (CPU, f32 self-convert): 33 tokens, these exact ends
            t |> equal(length(segs), 1)
            t |> equal(length(segs[0].tokens), 33, "token count")
            t |> equal(segs[0].tokens[0], 123, "tok[0] '▁And'")
            t |> equal(segs[0].tokens[1], 96, "tok[1] '▁so'")
            t |> equal(segs[0].tokens[31], 353, "tok[31] 'ry'")
            t |> equal(segs[0].tokens[32], 841, "tok[32] '.'")
            t |> success(segs[0].text == "And so, my fellow Americans, ask not what your country can do for you, ask what you can do for your country.", "text")
            t |> equal(s.detected_lang, "en")

            // the default load above ran the Q8 fast path — pin that set_asr_fp32 gives the
            // bit-exact fp32 route AND that both routes stay token-identical (jfk; gb1 was
            // verified 786/786 at the q8 landing)
            set_asr_fp32(true)
            var mf <- load_asr_model(path)
            set_asr_fp32(false)
            t |> success(!mf.pk.q8, "knob forces fp32")
            t |> success(m.pk.q8, "default load is q8")
            var sf <- create_session(mf)
            var fsegs : array<TranscribeSegment>
            transcribe(mf, sf, samples) $(seg) {
                fsegs |> push_clone(seg)
            }
            t |> equal(length(fsegs), 1)
            t |> equal(length(fsegs[0].tokens), length(segs[0].tokens), "q8/fp32 token count")
            for (a, b in fsegs[0].tokens, segs[0].tokens) {
                t |> equal(a, b, "q8/fp32 token")
            }
            delete mf.pk.blob
        }
        delete m.pk.blob
    }
}

[test]
def test_whisper_transcribe_oracle(t : T?) {
    t |> run("tiny greedy on jfk.wav is token-for-token with whisper-cli") @(t : T?) {
        if (!jit_enabled()) {
            t |> success(true, "skipped: interpreted (dasLLAMA model tests are JIT-only)")
            return
        }
        let model_path = path_join(whisper_models_dir(), "ggml-tiny.bin")
        if (!stat(model_path).is_valid) {
            t |> success(true, "skipped: ggml-tiny.bin not present")
            return
        }
        let samples <- read_wav_pcm16_mono(path_join(samples_dir(), "jfk.wav"))
        if (length(samples) == 0) {
            t |> success(true, "skipped: jfk.wav not present")
            return
        }
        var w <- load_whisper_model(model_path)
        with_job_que() {
            setup_dasllama_jobque_()
            var s <- create_session(w)
            var segs : array<TranscribeSegment>
            transcribe(w, s, samples) $(seg) {
                segs |> push_clone(seg)
            }
            // whisper-cli -bs 1 -bo 1 -nf -ng: one segment [0, 10500ms], these exact tokens
            // (incl. the leading <|0.00|> and closing <|10.50|>)
            let want <- [50364, 400, 370, 452, 7177, 6280, 1029, 406, 437, 428, 1941, 393,
                         360, 337, 291, 11, 1029, 437, 291, 393, 360, 337, 428, 1941, 13, 50889]
            t |> equal(length(segs), 1)
            t |> equal(segs[0].t0, 0l)
            t |> equal(segs[0].t1, 1050l)
            t |> equal(length(segs[0].tokens), length(want))
            var mismatches = 0
            for (a, b in segs[0].tokens, want) {
                if (a != b) {
                    mismatches++
                }
            }
            t |> success(mismatches == 0, "token-for-token ({mismatches} mismatches)")
            t |> success(segs[0].text == " And so my fellow Americans ask not what your country can do for you, ask what you can do for your country.", "text")

            // the push-chunks rail lands on the same result: feed in 2 chunks, flush
            var s2 <- create_session(w)
            let half = length(samples) / 2
            var part : array<float>
            part |> reserve(length(samples))
            for (i in range(half)) {
                part |> push(samples[i])
            }
            s2 |> feed(part)
            part |> clear()
            for (i in range(half, length(samples))) {
                part |> push(samples[i])
            }
            s2 |> feed(part)
            var flushed = ""
            flush(w, s2) $(seg) {
                flushed = "{flushed}{seg.text}"
            }
            t |> success(flushed == segs[0].text, "feed+flush == one-shot")

            // every emitted segment carries a real confidence (greedy plogs are <= 0, and a
            // clean read of jfk stays well above the no-speech −1.0 bar)
            t |> success(segs[0].avg_logprob < 0.0 && segs[0].avg_logprob > -1.0, "avg_logprob in (-1, 0)")

            // lang="auto" detects English on the same clip and lands on the identical text
            var s3 <- create_session(w, "auto")
            t |> equal(s3.lang_id, -1, "auto starts unresolved")
            var auto_text = ""
            transcribe(w, s3, samples) $(seg) {
                auto_text = "{auto_text}{seg.text}"
            }
            t |> equal(s3.lang_id, 0, "detected en")
            t |> success(auto_text == segs[0].text, "auto == en text")
        }
    }
}
