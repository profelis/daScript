options gen2
options persistent_heap   // model-scale allocations (2.5 GB mmproj tower) — freed per test
options stack = 65536

require dastest/testing_boost public
require dasllama/dasllama_audio
require dasllama/dasllama_math   // setup_dasllama_jobque_
require daslib/jobque_boost
require daslib/fio
require math

// Audio tower tests. The mel/gelu/filterbank tests are self-contained; the encoder test
// needs the locally-converted Qwen2-Audio mmproj (2.5 GB, gitignored) and skips without it.
// The oracle constants come from llama.cpp's mtmd (llama-mtmd-debug, CPU backend) — the rig
// and end-to-end token parity runs live in modules/dasLLAMA/qwen2_audio_plan.md.
def private models_dir() : string {
    let env = get_env_variable("DASLLAMA_MODELS_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama.cpp/models/" : env
}

[test]
def test_gelu_erf(t : T?) {
    t |> run("gelu_erf matches the exact-erf form") @(t : T?) {
        var g = [1.0, -1.0, 0.0, 3.0, 0.5]
        gelu_erf(g, 5l)
        // 0.5·x·(1+erf(x/√2)) = x·Φ(x): Φ(1)=0.8413447, Φ(3)=0.9986501, Φ(0.5)=0.6914625
        t |> success(abs(g[0] - 0.8413447) < 1e-6, "gelu_erf(1)")
        t |> success(abs(g[1] + 0.1586553) < 1e-6, "gelu_erf(-1)")
        t |> success(g[2] == 0.0, "gelu_erf(0)")
        t |> success(abs(g[3] - 2.9959502) < 1e-5, "gelu_erf(3)")
        t |> success(abs(g[4] - 0.3457312) < 1e-6, "gelu_erf(0.5)")
    }
}

[test]
def test_hann_window(t : T?) {
    t |> run("periodic hann-400 endpoints and center") @(t : T?) {
        let h <- build_hann_window(400l)
        t |> success(h[0] == 0.0, "h[0] = 0")
        t |> success(abs(h[200] - 1.0) < 1e-7, "h[200] = 1 (periodic peak)")
        t |> success(abs(h[100] - 0.5) < 1e-6, "h[100] = 0.5")
        t |> success(abs(h[399] - h[1]) < 1e-6, "periodic symmetry h[399] = h[1]")
    }
}

[test]
def test_mel_filterbank(t : T?) {
    t |> run("slaney filterbank shape invariants") @(t : T?) {
        let fb <- build_mel_filterbank(128l, 400l, 16000l)
        t |> success(length(fb) == 128 * 201, "128 x 201")
        var neg = 0
        var empty_rows = 0
        for (m in range(128)) {
            var row_sum = 0.0
            for (k in range(201)) {
                let v = fb[m * 201 + k]
                if (v < 0.0) {
                    neg++
                }
                row_sum += v
            }
            if (row_sum <= 0.0) {
                empty_rows++
            }
        }
        t |> success(neg == 0, "non-negative weights")
        t |> success(empty_rows == 0, "every mel row has support")
    }
}

[test]
def test_log_mel_chunks(t : T?) {
    t |> run("whisper mel: 440 Hz sine lands on its mel row, silence clamps") @(t : T?) {
        // the mtmd-debug 'preproc 440' fixture: 5 s sine -> exactly 2 full 3000-frame chunks
        var s : array<float>
        s |> resize(80000)
        for (i in range(80000)) {
            s[i] = sin(2.0 * 3.14159265 * 440.0 * float(i) / 16000.0)
        }
        let chunks <- log_mel_chunks(s, 128l)
        t |> success(length(chunks) == 2, "two chunks (audio + padded silence)")
        t |> equal(chunks[0].n_mel, 128l, "n_mel")
        t |> equal(chunks[0].n_len, 3000l, "n_len")
        // 440 Hz sits in the slaney linear region: center(m=18) = 19·(m_hi/129)/lin_slope ≈ 444 Hz
        var best_m = 0
        var best_v = -1e9
        for (m in range(128)) {
            let v = chunks[0].data[m * 3000 + 100]
            if (v > best_v) {
                best_v = v
                best_m = m
            }
        }
        t |> equal(best_m, 18, "peak mel row at 440 Hz")
        // the whisper dynamic clamp bounds the spread to exactly 8 log10 units / 4
        var mn = chunks[0].data[0]
        var mx = chunks[0].data[0]
        for (v in chunks[0].data) {
            mn = min(mn, v)
            mx = max(mx, v)
        }
        t |> success(mx - mn <= 2.0 + 1e-6, "max-min <= 8/4 (global clamp)")
        // the second chunk is all padded silence: every value at the clamp floor
        var uniform = true
        for (v in chunks[1].data) {
            if (v != chunks[1].data[0]) {
                uniform = false
            }
        }
        t |> success(uniform, "silence chunk uniform at the floor")
    }
}

[test]
def test_encoder_oracle(t : T?) {
    t |> run("all-ones mel through the tower matches mtmd (needs qwen2audio mmproj)") @(t : T?) {
        if (!jit_enabled()) {
            t |> success(true, "skipped: interpreted (dasLLAMA model tests are JIT-only)")
            return
        }
        let path = path_join(models_dir(), "qwen2audio-mmproj-f32.gguf")
        if (!stat(path).is_valid) {
            t |> success(true, "skipped: qwen2audio-mmproj-f32.gguf not present")
            return
        }
        var tw <- load_audio_tower(path)
        t |> equal(tw.n_mel, 128l, "n_mel")
        t |> equal(tw.d_model, 1280l, "d_model")
        t |> equal(tw.n_head, 20l, "heads")
        t |> equal(tw.n_layer, 32l, "layers")
        t |> equal(tw.n_ff, 5120l, "ffn")
        t |> equal(tw.n_ctx, 1500l, "positions")
        t |> equal(tw.proj_dim, 4096l, "projection")
        var mel = MelChunk(n_mel = tw.n_mel, n_len = AUDIO_CHUNK_FRAMES)
        mel.data |> resize(int(tw.n_mel * AUDIO_CHUNK_FRAMES))
        for (i in range(length(mel.data))) {
            mel.data[i] = 1.0
        }
        var enc <- make_encoder_state(tw)
        with_job_que() {
            setup_dasllama_jobque_()
            audio_encode(tw, enc, mel)
        }
        // llama-mtmd-debug -p encode --audio one -n 3000 (CPU): token 0 opens
        // 0.251974 0.311756 0.556828 0.005232 -0.838854; stats mean=0.009261 max=7.527778.
        // fp32 CPU re-orders put us ~1e-3 off their flash-attn encoder; gate at 5e-3.
        t |> success(abs(enc.out[0] - 0.251974) < 5e-3, "tok0[0]")
        t |> success(abs(enc.out[1] - 0.311756) < 5e-3, "tok0[1]")
        t |> success(abs(enc.out[2] - 0.556828) < 5e-3, "tok0[2]")
        t |> success(abs(enc.out[4] + 0.838854) < 5e-3, "tok0[4]")
        var sum = 0.0lf
        var mx = enc.out[0]
        for (v in enc.out) {
            sum += double(v)
            mx = max(mx, v)
        }
        let mean = sum / double(750l * tw.proj_dim)
        t |> success(abs(float(mean) - 0.009261) < 5e-4, "mean")
        t |> success(abs(mx - 7.527778) < 5e-2, "max")
        delete tw.fblob
    }
}
