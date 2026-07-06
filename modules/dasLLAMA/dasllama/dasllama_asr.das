options gen2

module dasllama_asr shared public

require math
require daslib/fio
require strings
require daslib/strings_boost
require dasllama/dasllama_gguf   // rd_u32 for the magic sniff
require dasllama/dasllama_audio  // EncoderState (the qwen3a tower's scratch)
require dasllama/dasllama_whisper public
require dasllama/dasllama_qwen3a public
require dasllama/dasllama_parakeet public
require dasllama/dasllama_transformer   // nolint:STYLE029 — the qwen3a decoder is a full LLM; umbrella fires arch [init]s

// The uniform ASR surface: one loader that sniffs the file format, one verb set that
// dispatches internally — NO family names in the public API. Backends: whisper (ggml bin)
// and Qwen3-ASR (GGUF decoder + qwen3a mmproj); Parakeet lands behind the same sniff.

//! Timestamp granularity an ASR backend can produce.
enum AsrTimestamps {
    none
    segment
    word
}

enum private AsrKind {
    whisper
    qwen3a
    parakeet
}

//! What a loaded ASR model honestly supports — advisory (invalid options still panic loudly
//! at the call site, never silently ignore). Query via ``caps``.
struct AsrCaps {
    languages : array<string>    // codes accepted by create_session (sans "auto"); empty = the model detects and reports the language itself
    translate : bool             // speech-to-English translation task
    timestamps : AsrTimestamps
    streaming : bool             // native incremental decode (whisper: false — 30 s windows)
    prompt : bool                // context/prompt conditioning (qwen3a: AsrSession.context)
}

//! A loaded ASR model of whatever family the files turned out to be.
struct AsrModel {
    kind : AsrKind = AsrKind.whisper
    whisper : WhisperModel = WhisperModel()
    dec : Model = Model()              // qwen3a: the qwen3 decoder LLM
    q3t : Qwen3aTower = Qwen3aTower()  // qwen3a: the chunked audio encoder
    pk : ParakeetModel = ParakeetModel()
}

//! One transcription stream over an AsrModel: per-backend scratch plus the shared options.
//! ``translate``/``no_timestamps`` apply where the backend supports them (see caps);
//! ``context`` is qwen3a's context-biasing text; ``detected_lang`` is filled after
//! transcription (whisper: the resolved/auto-detected code; qwen3a: the model's own report).
struct AsrSession {
    w : WhisperSession = WhisperSession()
    qctx : Session = Session()
    qenc : EncoderState = EncoderState()
    qcs : Qwen3aConvState = Qwen3aConvState()
    translate : bool = false
    no_timestamps : bool = false
    context : string = ""
    detected_lang : string = ""
}

// exact-fp32 knob for oracle rails: flip BEFORE load_asr_model to skip the Q8 fast path
var private g_asr_force_fp32 = false

//! Force the fp32 (bit-exact-with-oracle) path for models loaded AFTER this call — the
//! default load quantizes the encoder GEMMs to Q8_0 (~4x on CPU, tolerance-gated).
def set_asr_fp32(on : bool) {
    g_asr_force_fp32 = on
}

//! Load an ASR model, sniffing the format: ggml-bin magic = whisper vs parakeet
//! (disambiguated on vocab size: whisper >= 51864, parakeet ~1k); GGUF needs the model's
//! mmproj too — use the two-argument overload. One loader, no family names.
def load_asr_model(path : string) : AsrModel {
    let f = fopen(path, "rb")
    if (f == null) {
        panic("dasLLAMA asr: cannot open model '{path}'")
    }
    // stat, not length(bytes): the fmap array's length() wraps int32 on >2GB files (whisper
    // large-v3 / parakeet f32 bins), which would reject valid models here
    if (stat(path).size < 8ul) {
        panic("dasLLAMA asr: '{path}' is too short to be a model file ({stat(path).size} bytes)")
    }
    var magic = 0u
    var vocab = 0
    fmap(f) $(var bytes : array<uint8>#) {
        magic = rd_u32(bytes, 0l)
        vocab = int(rd_u32(bytes, 4l))   // ggml-bin: first hparam after the magic is n_vocab
    }
    fclose(f)
    if (magic == 0x46554747u) {   // "GGUF"
        panic("dasLLAMA asr: '{path}' is a GGUF decoder — pass its mmproj too: load_asr_model(path, mmproj_path)")
    }
    if (magic != 0x67676d6cu) {
        panic("dasLLAMA asr: '{path}' is neither a GGUF nor a ggml bin")
    }
    if (vocab < 8192) {   // parakeet bins carry a ~1k SPM vocab
        var pm = AsrModel(kind = AsrKind.parakeet)
        pm.pk <- load_parakeet_model(path)
        if (!g_asr_force_fp32) {
            parakeet_quantize(pm.pk)
        }
        return <- pm
    }
    // whisper vocabs: 51864 (.en) / 51865 (multilingual) / 51866 (large-v3 family); anything
    // else with the ggml magic (e.g. a legacy GPT-2 bin, 50257) fails HERE, not deep in the loader
    if (vocab < 51864 || vocab > 51999) {
        panic("dasLLAMA asr: '{path}' has n_vocab {vocab} — matches neither whisper (51864-51866) nor parakeet (~1k)")
    }
    var m = AsrModel(kind = AsrKind.whisper)
    m.whisper <- load_whisper_model(path)
    return <- m
}

def load_asr_model(path : string; mmproj : string) : AsrModel {
    //! The GGUF route (Qwen3-ASR): ``path`` is the decoder GGUF (arch qwen3vl), ``mmproj``
    //! its qwen3a audio encoder. Decoder weights load Q8; context is capped at 8192.
    var m = AsrModel(kind = AsrKind.qwen3a)
    m.dec <- load_model_(path, QuantMode.q8)
    if (m.dec.arch != "qwen3vl" && m.dec.arch != "qwen3") {
        panic("dasLLAMA asr: '{path}' is arch '{m.dec.arch}' — the GGUF ASR route expects a Qwen3-ASR decoder")
    }
    m.dec.config.seq_len = min(m.dec.config.seq_len, 8192l)
    m.q3t <- load_qwen3a_tower(mmproj)
    if (m.q3t.proj_dim != m.dec.config.dim) {
        panic("dasLLAMA asr: mmproj projects to {m.q3t.proj_dim} but the decoder is {m.dec.config.dim}-wide — mismatched pair")
    }
    return <- m
}

//! What this model supports. Whisper: the model's own language set (99, or 100 on the
//! large-v3 family which adds Cantonese; English-only for *.en models), translation on
//! multilingual models, segment timestamps. Qwen3-ASR: the model detects and reports the
//! language itself (``detected_lang``), no timestamps, context biasing via
//! ``AsrSession.context``.
def caps(m : AsrModel) : AsrCaps {
    if (m.kind == AsrKind.qwen3a) {
        return <- AsrCaps(translate = false, timestamps = AsrTimestamps.none,
                          streaming = false, prompt = true)
    }
    if (m.kind == AsrKind.parakeet) {
        var pc = AsrCaps(translate = false, timestamps = AsrTimestamps.segment,
                         streaming = false, prompt = false)
        pc.languages <- ["en"]
        return <- pc
    }
    var c = AsrCaps(translate = m.whisper.multilingual,
                    timestamps = AsrTimestamps.segment,
                    streaming = false,
                    prompt = false)
    if (m.whisper.multilingual) {
        c.languages <- whisper_lang_list()
        if (int64(length(c.languages)) > m.whisper.n_lang) {   // 99-lang models predate "yue"
            c.languages |> resize(int(m.whisper.n_lang))
        }
    } else {
        c.languages <- ["en"]
    }
    return <- c
}

def create_session(m : AsrModel; lang : string = "en") : AsrSession {
    //! Create a transcription session. ``lang`` is a language code from ``caps().languages``,
    //! or "auto" to detect (whisper multilingual models; Qwen3-ASR always detects — it only
    //! accepts "auto").
    var s = AsrSession()
    if (m.kind == AsrKind.parakeet) {
        if (lang != "en" && lang != "auto") {
            panic("dasLLAMA asr: this Parakeet model is English-only")
        }
        return <- s
    }
    if (m.kind == AsrKind.qwen3a) {
        if (lang != "auto") {
            panic("dasLLAMA asr: Qwen3-ASR detects the language itself — create the session with lang=\"auto\"")
        }
        s.qctx <- create_session_(m.dec)
        s.qenc <- make_encoder_state(m.q3t.core)
    } else {
        s.w <- create_session(m.whisper, lang)
    }
    return <- s
}

// The qwen3a transcription turn: chatml with the audio span in <|audio_start|>/<|audio_end|>,
// the context text after it, greedy decode, and the model's `language {L}<asr_text>{text}`
// response parsed into (detected_lang, text).
def private transcribe_qwen3a(m : AsrModel; var s : AsrSession; samples : array<float> | #;
                              blk : block<(seg : TranscribeSegment)>) : int {
    let mel <- log_mel_qwen3a(samples, m.q3t.core.n_mel)
    var rows : array<float>
    let n_audio = qwen3a_encode_all(m.q3t, s.qenc, s.qcs, mel, rows)

    let dim = m.dec.config.dim
    let im_start = special_id(m.dec, "<|im_start|>")
    let im_end = special_id(m.dec, "<|im_end|>")
    var head : array<int64>
    head |> push(im_start)
    head |> push_from(encode_(m.dec, "user\n", false, false))
    head |> push(special_id(m.dec, "<|audio_start|>"))
    var tail : array<int64>
    tail |> push(special_id(m.dec, "<|audio_end|>"))
    if (!empty(s.context)) {
        tail |> push_from(encode_(m.dec, s.context, false, false))
    }
    tail |> push(im_end)
    tail |> push_from(encode_(m.dec, "\n", false, false))
    tail |> push(im_start)
    tail |> push_from(encode_(m.dec, "assistant\n", false, false))

    let n_head = int64(length(head))
    let n_tail = int64(length(tail))
    let npos = n_head + n_audio + n_tail
    var embd : array<float>
    embd |> resize(int(npos * dim))
    embed_text_rows(m.dec, head, embd, 0l)
    for (i in range64(n_audio * dim)) {
        embd[n_head * dim + i] = rows[i]
    }
    embed_text_rows(m.dec, tail, embd, n_head + n_audio)

    s.qctx.n_past = 0l   // each transcribe is a fresh sequence; the KV rewinds to position 0
    eval_embd_(m.dec, s.qctx, embd, npos)

    let eot = special_id(m.dec, "<|endoftext|>")
    let max_new = m.dec.config.seq_len - npos - 1l
    var one : array<int64>
    one |> resize(1)
    var toks : array<int>
    var plog_sum = 0.0lf
    var raw : array<string>
    for (_i in range64(max_new)) {
        // greedy argmax + its logprob (logit − logsumexp) for the confidence signal
        var best = 0
        for (i in range(1, length(s.qctx.logits))) {
            if (s.qctx.logits[i] > s.qctx.logits[best]) {
                best = i
            }
        }
        let mx = s.qctx.logits[best]
        var lse = 0.0lf
        for (v in s.qctx.logits) {
            lse += double(exp(v - mx))
        }
        plog_sum += double(s.qctx.logits[best]) - (log(lse) + double(mx))
        if (int64(best) == im_end || int64(best) == eot) {
            break
        }
        toks |> push(best)
        raw |> push(piece_(m.dec, int64(best)))
        one[0] = int64(best)
        eval_(m.dec, s.qctx, one)
    }

    // parse `language {L}<asr_text>{text}` (the marker may detokenize as text or be muted)
    let full = join(raw, "")
    var text = full
    s.detected_lang = ""
    let mark = find(full, "<asr_text>")
    if (mark >= 0) {
        let pre = slice(full, 0, mark)
        if (starts_with(pre, "language ")) {
            s.detected_lang = strip(slice(pre, length("language "), length(pre)))
        }
        text = slice(full, mark + length("<asr_text>"), length(full))
    }
    var seg = TranscribeSegment(t0 = 0l, t1 = int64(length(samples)) * 100l / AUDIO_SAMPLE_RATE, text = text)
    seg.tokens := toks
    if (!empty(toks)) {
        seg.avg_logprob = float(plog_sum / double(length(toks) + 1))   // + the stop token's plog
    }
    blk |> invoke(seg)
    return 1
}

// Parakeet transcription: full-clip FastConformer encode + TDT greedy, one segment.
def private transcribe_parakeet(m : AsrModel; var s : AsrSession; samples : array<float> | #;
                                blk : block<(seg : TranscribeSegment)>) : int {
    var tp = ref_time_ticks()
    let mel <- parakeet_log_mel(samples, m.pk)
    asr_prof_add("pk.mel", tp)
    var enc_out : array<float>
    tp = ref_time_ticks()
    let tt = parakeet_encode(m.pk, mel, enc_out)
    asr_prof_add("pk.encode_total", tp)
    tp = ref_time_ticks()
    let toks <- parakeet_tdt_decode(m.pk, enc_out, tt)
    asr_prof_add("pk.decode_total", tp)
    var seg = TranscribeSegment(t0 = 0l, t1 = int64(length(samples)) * 100l / AUDIO_SAMPLE_RATE,
        text = parakeet_detokenize(m.pk, toks))
    var plog_sum = 0.0lf
    seg.tokens |> reserve(length(toks))
    for (t in toks) {
        seg.tokens |> push(t.id)
        plog_sum += double(t.plog)
    }
    if (!empty(toks)) {
        seg.avg_logprob = float(plog_sum / double(length(toks)))
    }
    s.detected_lang = "en"
    blk |> invoke(seg)
    return 1
}

def transcribe(m : AsrModel; var s : AsrSession; samples : array<float> | #;
               blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe ``samples`` (16 kHz mono f32 PCM), one ``TranscribeSegment`` per trailing-block
    //! call. Returns the segment count. Whisper honors ``translate``/``no_timestamps``; qwen3a
    //! emits ONE segment (no timestamps) and fills ``detected_lang``.
    if (m.kind == AsrKind.qwen3a) {
        return transcribe_qwen3a(m, s, samples, blk)
    }
    if (m.kind == AsrKind.parakeet) {
        return transcribe_parakeet(m, s, samples, blk)
    }
    s.w.translate = s.translate
    s.w.no_timestamps = s.no_timestamps
    let n = transcribe(m.whisper, s.w, samples, blk)
    if (s.w.lang_id >= 0) {
        s.detected_lang = whisper_lang_list()[s.w.lang_id]
    }
    return n
}

def transcribe(m : AsrModel; var s : AsrSession; samples : array<float> | #) : string {
    //! One-shot: transcribe ``samples`` and return the full text.
    return build_string() $(writer) {
        transcribe(m, s, samples) $(seg) {
            writer |> write(seg.text)
        }
    }
}

def feed(m : AsrModel; var s : AsrSession; samples : array<float> | #) {
    //! Push a chunk of 16 kHz mono PCM onto the session's stream (pair with drain/flush).
    //! Whisper only — qwen3a transcribes whole clips (caps().streaming is false there).
    if (m.kind != AsrKind.whisper) {
        panic("dasLLAMA asr: feed/drain/flush are whisper-only — this model transcribes whole clips")
    }
    feed(s.w, samples)
}

def drain(m : AsrModel; var s : AsrSession; blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe every complete 30 s window of the fed stream; sub-window audio stays pending.
    if (m.kind != AsrKind.whisper) {
        panic("dasLLAMA asr: feed/drain/flush are whisper-only — this model transcribes whole clips")
    }
    s.w.translate = s.translate
    s.w.no_timestamps = s.no_timestamps
    return drain(m.whisper, s.w, blk)
}

def flush(m : AsrModel; var s : AsrSession; blk : block<(seg : TranscribeSegment)>) : int {
    //! Transcribe everything left on the fed stream (including the tail) and clear it.
    if (m.kind != AsrKind.whisper) {
        panic("dasLLAMA asr: feed/drain/flush are whisper-only — this model transcribes whole clips")
    }
    s.w.translate = s.translate
    s.w.no_timestamps = s.no_timestamps
    return flush(m.whisper, s.w, blk)
}
