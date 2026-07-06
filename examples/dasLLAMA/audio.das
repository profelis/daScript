options gen2
options _jit_fast_math = true   // ggml-parity FP laxity (non-bit-exact, ~+10%); tests stay bit-exact

require dasllama/dasllama       // the public facade: engine + arch registration + chat layer
require dasllama/dasllama_audio // whisper-encoder tower + mel frontend
require audio                   // miniaudio decode (any format) resampled to 16 kHz mono
require daslib/jobque_boost
require daslib/fio
require strings
require math

// Audio chat over Qwen2-Audio: mel frontend -> whisper encoder tower -> soft tokens spliced
// into the EXISTING qwen2 decoder at the audio placeholder (no cross-attention). The prompt
// layout mirrors llama.cpp's mtmd-cli exactly (no system message, audio before the text):
//   <|im_start|>user\n<|audio_bos|>[soft tokens]<|audio_eos|>{prompt}<|im_end|>\n<|im_start|>assistant\n
//
//   bin/daslang -jit examples/dasLLAMA/audio.das -- <decoder.gguf> <mmproj.gguf> <audio-file> [prompt]

let DEFAULT_PROMPT = "What is being said in this audio?"
let N_GEN = 128
let CTX = 4096l

// Decode any audio file miniaudio understands (WAV/MP3/FLAC/Vorbis) to 16 kHz mono f32 —
// the decoder converts rate/channels on the fly, same rail mtmd-helper uses.
def load_audio_16k_mono(path : string) : array<float> {
    var decoder = new ma_decoder
    var config <- ma_decoder_config_init(ma_format.ma_format_f32, 1u, uint(AUDIO_SAMPLE_RATE))
    if (ma_decoder_init_file(path, unsafe(addr(config)), decoder) != ma_result.MA_SUCCESS) {
        panic("cannot open audio file '{path}'")
    }
    var out : array<float>
    let chunk = 65536
    var buf : array<float>
    buf |> resize(chunk)
    while (true) {
        let got = int(ma_decoder_read_pcm_frames(decoder, unsafe(addr(buf[0])), uint64(chunk)))
        if (got <= 0) {
            break
        }
        out |> reserve(length(out) + got)
        for (i in range(got)) {
            out |> push(buf[i])
        }
        if (got < chunk) {
            break
        }
    }
    ma_decoder_uninit(decoder)
    unsafe {
        delete decoder
    }
    return <- out
}

[export]
def main {
    let cmd <- get_command_line_arguments()
    var gguf_at = -1
    for (i in range(length(cmd))) {
        if (ends_with(cmd[i], ".gguf")) {
            gguf_at = i
            break
        }
    }
    if (gguf_at < 0 || gguf_at + 2 >= length(cmd)) {
        print("usage: daslang -jit examples/dasLLAMA/audio.das -- <decoder.gguf> <mmproj.gguf> <audio-file> [prompt]\n")
        return
    }
    let model_path = cmd[gguf_at]
    let mmproj_path = cmd[gguf_at + 1]
    let audio_path = cmd[gguf_at + 2]
    let prompt = gguf_at + 3 < length(cmd) ? cmd[gguf_at + 3] : DEFAULT_PROMPT

    print("loading {model_path}\n")
    var m <- load_model(model_path, QuantMode.q8)
    m.config.seq_len = min(m.config.seq_len, CTX)
    print("loading {mmproj_path}\n")
    var tower <- load_audio_tower(mmproj_path)
    let samples <- load_audio_16k_mono(audio_path)
    print("audio: {length(samples)} samples ({float(length(samples)) / float(int(AUDIO_SAMPLE_RATE))} s)\n")
    let chunks <- log_mel_chunks(samples, tower.n_mel)

    let dim = m.config.dim
    if (tower.proj_dim != dim) {
        panic("mmproj projects to {tower.proj_dim} but the decoder is {dim}-wide — mismatched pair")
    }
    let n_audio_tok = tower.n_ctx / 2l

    with_job_que() {
        setup_dasllama_jobque()
        // encode every 30 s chunk to soft tokens
        var enc <- make_encoder_state(tower)
        var audio_rows : array<float>
        audio_rows |> resize(int(int64(length(chunks)) * n_audio_tok * dim))
        let t_enc = ref_time_ticks()
        for (ci in range(length(chunks))) {
            audio_encode(tower, enc, chunks[ci])
            for (i in range64(n_audio_tok * dim)) {
                audio_rows[int64(ci) * n_audio_tok * dim + i] = enc.out[i]
            }
        }
        print("encoded {length(chunks)} chunk(s) x {n_audio_tok} soft tokens in {get_time_usec(t_enc) / 1000} ms\n")

        // the mtmd-cli prompt shape, split around the audio span; specials by id + text runs
        // encoded per segment (the chat layer's pattern — BPE merges never cross specials)
        let im_start = special_id(m, "<|im_start|>")
        let im_end = special_id(m, "<|im_end|>")
        var prefix : array<int64>
        prefix |> push(im_start)
        prefix |> push_from(encode(m, "user\n", false, false))
        prefix |> push(special_id(m, "<|audio_bos|>"))
        var suffix : array<int64>
        suffix |> push(special_id(m, "<|audio_eos|>"))
        suffix |> push_from(encode(m, prompt, false, false))
        suffix |> push(im_end)
        suffix |> push_from(encode(m, "\n", false, false))
        suffix |> push(im_start)
        suffix |> push_from(encode(m, "assistant\n", false, false))
        let n_prefix = int64(length(prefix))
        let n_suffix = int64(length(suffix))
        let n_audio = int64(length(chunks)) * n_audio_tok
        let npos = n_prefix + n_audio + n_suffix
        var embd : array<float>
        embd |> resize(int(npos * dim))
        embed_text_rows(m, prefix, embd, 0l)
        for (i in range64(n_audio * dim)) {
            embd[(n_prefix * dim) + i] = audio_rows[i]
        }
        embed_text_rows(m, suffix, embd, n_prefix + n_audio)

        var s = create_session(m)
        let t_pre = ref_time_ticks()
        eval_embd(m, s, embd, npos)
        print("prefill {npos} pos ({n_audio} audio) in {get_time_usec(t_pre) / 1000} ms\n---\n")

        let eot = special_id(m, "<|endoftext|>")
        var one : array<int64>
        one |> resize(1)
        for (_i in range(N_GEN)) {
            let tok = sample(s, SamplingParams())
            if (tok == im_end || tok == eot) {
                break
            }
            fprint(fstdout(), piece(m, tok))
            fflush(fstdout())
            one[0] = tok
            eval(m, s, one)
        }
        print("\n")
    }
}
