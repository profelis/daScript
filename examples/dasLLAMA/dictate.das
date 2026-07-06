options gen2
options stack = 65536
options fast_math = true   // ggml-parity FP laxity (non-bit-exact, ~+10%)
options persistent_heap

require dasllama/dasllama       // the ASR surface: load_asr_model / create_session / transcribe
require audio/audio_record      // microphone capture (sound_record_*)
require daslib/jobque_boost
require daslib/fio
require strings
require math

// Live dictation: microphone -> Parakeet-TDT. The capture device fills a lock-free ring
// buffer from the audio thread; this script drains it on the main thread, re-transcribing
// the growing take every REDECODE_S seconds so the line under your voice keeps extending.
// Parakeet decodes several times faster than realtime, so whole-take re-decodes stay cheap
// for dictation-length audio (the encoder is O(T²) past a few minutes — take a breath).
//
// Any ASR model the uniform loader takes works here; Parakeet is the pick for latency
// (no 30 s window). Whisper bins work too — expect window-sized latency.
//
//   bin/daslang -jit examples/dasLLAMA/dictate.das -- <asr-model> [seconds]
//   e.g. bin/daslang -jit examples/dasLLAMA/dictate.das -- ggml-parakeet-tdt-0.6b-v2-f32.bin 15

let RATE = 16000
let REDECODE_S = 2.0    // re-transcribe cadence while recording
let DEFAULT_SECONDS = 15.0

[export]
def main {
    let cmd <- get_command_line_arguments()
    var model_path = ""
    var seconds = DEFAULT_SECONDS
    for (a in cmd) {
        if (ends_with(a, ".bin") || ends_with(a, ".gguf")) {
            model_path = a
        } elif (!empty(model_path) && to_float(a) > 0.0) {
            seconds = to_float(a)
        }
    }
    if (empty(model_path)) {
        print("usage: daslang -jit examples/dasLLAMA/dictate.das -- <asr-model> [seconds]\n")
        return
    }

    print("loading {model_path}\n")
    var m <- load_asr_model(model_path)
    let c <- caps(m)
    let lang = !empty(c.languages) && length(c.languages) == 1 ? c.languages[0] : "auto"

    if (!sound_record_start(RATE, 1, RATE * 30, -1)) {
        panic("could not open the capture device (no microphone, or access denied)")
    }
    print("recording {seconds} s — speak!\n\n")

    with_job_que() {
        setup_dasllama_jobque()
        var take : array<float>
        take |> reserve(int(seconds * float(RATE)) + RATE)
        var scratch : array<float>
        scratch |> resize(RATE / 4)
        var since_decode = 0
        var line = ""
        while (float(length(take)) < seconds * float(RATE)) {
            let n = sound_record_read(scratch)
            if (n > 0) {
                for (i in range(n)) {
                    take |> push(scratch[i])
                }
                since_decode += n
                if (float(since_decode) >= REDECODE_S * float(RATE)) {
                    since_decode = 0
                    var s <- create_session(m, lang)
                    line = transcribe(m, s, take)
                    print("[{float(length(take)) / float(RATE)} s] {line}\n")
                }
            } else {
                sleep(5u)
            }
        }
        sound_record_stop()
        if (sound_record_overflow_frames() > 0l) {
            print("(dropped {sound_record_overflow_frames()} frames — the decode loop fell behind)\n")
        }

        // the final pass over the full take
        var s <- create_session(m, lang)
        let final_text = transcribe(m, s, take)
        print("\n=== final ===\n{final_text}\n")
    }
}
