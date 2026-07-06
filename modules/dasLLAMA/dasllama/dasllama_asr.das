options gen2

module dasllama_asr shared public

require daslib/fio
require dasllama/dasllama_gguf   // rd_u32 for the magic sniff
require dasllama/dasllama_whisper public

// The uniform ASR surface: one loader that sniffs the file format, one verb set that
// dispatches internally — NO family names in the public API. Whisper is the first backend;
// Parakeet (ggml-bin, tiny vocab) and Qwen3-ASR (GGUF) land behind the same sniff.

//! Timestamp granularity an ASR backend can produce.
enum AsrTimestamps {
    none
    segment
    word
}

//! What a loaded ASR model honestly supports — advisory (invalid options still panic loudly
//! at the call site, never silently ignore). Query via ``caps``.
struct AsrCaps {
    languages : array<string>    // language codes accepted by create_session (sans "auto")
    translate : bool             // speech-to-English translation task
    timestamps : AsrTimestamps
    streaming : bool             // native incremental decode (whisper: false — 30 s windows)
    prompt : bool                // initial-prompt conditioning
}

//! A loaded ASR model of whatever family the file turned out to be.
struct AsrModel {
    whisper : WhisperModel = WhisperModel()
}

//! Load an ASR model, sniffing the format: GGUF magic = the GGUF-based families (Qwen3-ASR,
//! session C), ggml-bin magic = whisper vs parakeet disambiguated on vocab size (whisper
//! >= 51864, parakeet ~1k). One loader, no family names.
def load_asr_model(path : string) : AsrModel {
    let f = fopen(path, "rb")
    if (f == null) {
        panic("dasLLAMA asr: cannot open model '{path}'")
    }
    var magic = 0u
    var vocab = 0
    fmap(f) $(var bytes : array<uint8>#) {
        magic = rd_u32(bytes, 0l)
        vocab = int(rd_u32(bytes, 4l))   // ggml-bin: first hparam after the magic is n_vocab
    }
    fclose(f)
    if (magic == 0x46554747u) {   // "GGUF"
        panic("dasLLAMA asr: GGUF-based ASR (Qwen3-ASR) is not supported yet")
    }
    if (magic != 0x67676d6cu) {
        panic("dasLLAMA asr: '{path}' is neither a GGUF nor a ggml bin")
    }
    if (vocab < 32768) {
        panic("dasLLAMA asr: ggml bin with a {vocab}-token vocab looks like Parakeet — not supported yet")
    }
    var m = AsrModel()
    m.whisper <- load_whisper_model(path)
    return <- m
}

//! What this model supports. Whisper: 100 languages (or English-only for *.en models),
//! translation on multilingual models, segment timestamps, no native streaming (30 s
//! windows — feed/drain works but latency is a window), no prompt conditioning yet.
def caps(m : AsrModel) : AsrCaps {
    var c = AsrCaps(translate = m.whisper.multilingual,
                    timestamps = AsrTimestamps.segment,
                    streaming = false,
                    prompt = false)
    if (m.whisper.multilingual) {
        c.languages <- whisper_lang_list()
    } else {
        c.languages <- ["en"]
    }
    return <- c
}

def create_session(m : AsrModel; lang : string = "en") : WhisperSession {
    //! Create a transcription session. ``lang`` is a language code from ``caps().languages``,
    //! or "auto" to detect from the first audio (multilingual models only).
    return <- create_session(m.whisper, lang)
}

def transcribe(m : AsrModel; var s : WhisperSession; samples : array<float> | #;
               blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe ``samples`` (16 kHz mono f32 PCM), one ``TranscribeSegment`` per trailing-block
    //! call. Returns the segment count.
    return transcribe(m.whisper, s, samples, blk)
}

def transcribe(m : AsrModel; var s : WhisperSession; samples : array<float> | #) : string {
    //! One-shot: transcribe ``samples`` and return the full text.
    return transcribe(m.whisper, s, samples)
}

def feed(m : AsrModel; var s : WhisperSession; samples : array<float> | #) {
    //! Push a chunk of 16 kHz mono PCM onto the session's stream (pair with drain/flush).
    feed(s, samples)
}

def drain(m : AsrModel; var s : WhisperSession; blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe every complete 30 s window of the fed stream; sub-window audio stays pending.
    return drain(m.whisper, s, blk)
}

def flush(m : AsrModel; var s : WhisperSession; blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe everything left on the fed stream (including the tail) and clear it.
    return flush(m.whisper, s, blk)
}
