options gen2
options stack = 262144

// wav2txt — transcribe an audio file to text with a dasLLAMA ASR model. A third sibling of
// dasllama-server, and the simplest kind of tune consumer: it requires dasLLAMA and so inherits
// the shared [tune_scope] with NO tune declaration AND no [tune_policy] — it silently runs this
// box's tuned kernels when a manifest exists (server/ask having produced it) and the generic
// per-ISA fallback otherwise. Nothing to configure; tuning is entirely the server's/ask's story.
//
//   bin/daslang -jit utils/dasllama-server/wav2txt.das -- --asr <asr.gguf> --file <audio.wav> [--out t.txt]

require dasllama/dasllama       // load_asr_model / transcribe / the shared [tune_scope]
require daslib/jobque_boost
require daslib/clargs
require daslib/fio
require strings
require math
require audio                   // miniaudio: decode any audio file -> 16 kHz mono f32

[CommandLineArgs]
struct Wav2TxtArgs {
    @clarg_required
    @clarg_short = "a"
    @clarg_doc = "Path to the ASR model (GGUF or .bin)"
    asr : string

    @clarg_required
    @clarg_short = "f"
    @clarg_doc = "Path to the audio file to transcribe"
    file : string

    @clarg_short = "o"
    @clarg_doc = "Write the transcript here instead of stdout"
    out : string

    @clarg_short = "l"
    @clarg_doc = "Language hint (default en)"
    lang : string

    @clarg_doc = "mmproj for a GGUF ASR model (paired with --asr)"
    mmproj : string

    @clarg_short = "?"
    @clarg_name = "show-help"
    @clarg_doc = "Show this help and exit"
    help : bool
}

// Decode any format miniaudio handles to 16 kHz mono f32 PCM — the ASR facade takes samples,
// not a path (the same decode rail the server and the dasLLAMA examples use).
def load_audio_16k_mono(path : string) : array<float> {
    var samples : array<float>
    var decoder = new ma_decoder
    var config <- ma_decoder_config_init(ma_format.ma_format_f32, 1u, 16000u)
    if (ma_decoder_init_file(path, unsafe(addr(config)), decoder) != ma_result.MA_SUCCESS) {
        unsafe {
            delete decoder
        }
        return <- samples
    }
    let chunk = 16000
    var total = 0
    while (true) {
        samples |> resize(total + chunk)
        let got = int(ma_decoder_read_pcm_frames(decoder, unsafe(addr(samples[total])), uint64(chunk)))
        total += got
        if (got < chunk) {
            break
        }
    }
    samples |> resize(total)
    ma_decoder_uninit(decoder)
    unsafe {
        delete decoder
    }
    return <- samples
}

[export]
def main {
    var r <- parse_args(type<Wav2TxtArgs>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<Wav2TxtArgs>), "wav2txt")
        return
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<Wav2TxtArgs>), "wav2txt")
        return
    }

    let samples <- load_audio_16k_mono(cfg.file)
    if (empty(samples)) {
        to_log(LOG_ERROR, "wav2txt: could not decode audio: {cfg.file}\n")
        return
    }

    var m <- empty(cfg.mmproj) ? load_asr_model(cfg.asr) : load_asr_model(cfg.asr, cfg.mmproj)
    let lang = empty(cfg.lang) ? "en" : cfg.lang

    var text = ""
    with_job_que() {
        setup_dasllama_jobque()
        var s = create_session(m, lang)
        text = transcribe(m, s, samples)
    }

    if (empty(cfg.out)) {
        print("{text}\n")
    } elif (fwrite(cfg.out, text)) {
        to_log(LOG_INFO, "wav2txt: wrote {cfg.out}\n")
    } else {
        to_log(LOG_ERROR, "wav2txt: could not write {cfg.out}\n")
    }
}
