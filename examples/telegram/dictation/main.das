options gen2
options rtti                  // dasTelegram's JSON (sscan_json/sprint_json) needs rtti
options persistent_heap       // dasLLAMA's big weight arrays + the GC below
options gc                    // periodic heap_collect between messages (long-running bot)
options stack = 262144        // dasLLAMA's forward chain runs deep
options _jit_fast_math = true // inference tool, not the bit-exact test suite

// dictation — a Telegram bot that transcribes voice/audio messages into clean, easy-to-read text.
// It watches direct messages and groups; for every voice note or audio file it downloads the audio,
// transcodes it to 16 kHz mono WAV with ffmpeg, transcribes it with a local whisper model
// (auto-detecting the language), then rewrites the raw transcript into paragraph-split prose with a
// local instruct LLM (dasLLAMA) — all offline. Model paths and options come from a TOML/JSON config
// (see dictation.toml / README.md). Requires the JIT — run under `daslang -jit` or a released -exe.

require telegram/tbot                 // dasTelegram (daspkg): getUpdates / getFile / download / sendMessage
require dasllama/dasllama             // load_model / load_asr_model / transcribe / create_chat / respond
require dasllama/dasllama_audio_io    // load_audio_16k_mono
require llvm/daslib/llvm_tune         // [tune_policy] + log_tune_status
require daslib/jobque_boost           // with_job_que + set_jobque_threads_cap
require daslib/toml                   // read_toml (re-exports daslib/json: read_json + JsonValue)
require daslib/json_boost             // operator ?? over JsonValue
require daslib/clargs                 // --config
require daslib/module_path            // get_this_module_dir (config next to the exe in a release bundle)
require daslib/fio                    // fopen / fwrite / popen_argv / temp_directory / remove / path_join / sleep
require strings
require daslib/strings_boost          // join / strip
require daslib/logger                 // proper file logging (levels + dotted categories)

// ===== command line =====

[CommandLineArgs]
struct DictationArgs {
    @clarg_short = "c"
    @clarg_doc = "Path to the config file (.toml or .json; default: dictation.toml next to the exe)"
    config : string

    @clarg_short = "?"
    @clarg_name = "show-help"
    @clarg_doc = "Show this help and exit"
    help : bool
}

// ===== config =====

struct DictationConfig {
    whisper_model : string            // path to the whisper ggml .bin (ASR)
    llm_model : string                // path to the instruct LLM GGUF (cleanup/reformat)
    bot_token : string                // Telegram bot token (TELEGRAM_BOT_TOKEN env overrides)
    threads : int = 7                 // dasLLAMA worker cap; 7 workers + main = 8 compute lanes
    language : string = "auto"        // whisper language hint ("auto" detects per message)
    max_tokens : int = 2048           // reply-token budget for the LLM cleanup
    temp : float = 0.0                // LLM sampling temperature (0 = greedy, faithful)
    ffmpeg : string = "ffmpeg"        // ffmpeg executable (on PATH or an absolute path)
    poll_timeout : int = 30           // getUpdates long-poll timeout, seconds
    log_file : string = ""            // log file path ("" = dictation.log next to the exe)
    log_level : string = "info"       // trace | debug | info | warning | error | critical
    min_chars : int = 0               // skip the LLM if the stripped transcript is <= this many bytes
    keep_audio_dir : string = ""      // if set, archive each received audio here ("" = don't keep)
}

// Persistent state lives in GLOBALS, never on the poll loop's stack. Under the JIT the heap
// collector cannot see JIT-stack locals, so a local holding the models/config across a
// heap_collect would be swept out from under us (segfault). As globals they are GC roots, so
// heap_collect(true, true) between messages is safe. Everything the loop touches is either a
// global (here) or an ephemeral local inside process_message that is gone before the collect.
var g_cfg = DictationConfig()
var g_asr = AsrModel()
var g_llm = Model()

// The dictation system prompt (proven on the sample voice notes): rewrite the raw transcript into a
// clean, easy-to-read message split into short paragraphs, in the source language. Not a verbatim
// transcript — filler / false-starts / mumbling are dropped, obvious ASR mishearings fixed, and the
// speaker's meaning, tone and register (including strong language) are preserved.
def dictation_system_prompt(lang : string) : string {
    return ("You are a dictation editor. You receive a raw speech-to-text transcript of a voice message. " +
            "It is full of filler words, false starts, repetitions, mumbling and recognition errors. Its " +
            "main language is \"{lang}\", but the speaker may switch languages mid-message. Write in the " +
            "SAME language(s) the speaker used — keep every part in its original language and NEVER translate " +
            "any part into another language.\n\n" +
            "Clean it up into an easy-to-read message. Rules:\n" +
            "- Keep the speaker's OWN words and phrasing. Only rewrite parts that are garbled, disfluent or " +
            "genuinely hard to read; leave clear sentences as they are, just fixing punctuation and casing.\n" +
            "- Do NOT paraphrase, rephrase or restate sentences that are already understandable, and do NOT " +
            "summarize or shorten the content.\n" +
            "- Break the text into several short paragraphs, roughly one per topic or thought, separated by " +
            "a blank line. Never return one long block of text.\n" +
            "- Drop filler words, false starts, repetitions and mumbling. If a fragment is unintelligible, " +
            "leave it out rather than guessing.\n" +
            "- Fix obvious speech-recognition errors when the intended word is clear from context.\n" +
            "- Keep the speaker's meaning, tone and register — including slang and strong language.\n" +
            "- Do not add a summary, a title, opinions, or facts the speaker did not express. Output only " +
            "the cleaned message text.")
}

def private resolve_config_path(cli_config : string) : string {
    if (!empty(cli_config)) {
        return cli_config
    }
    // default: dictation.toml next to the exe (release bundle) or next to main.das (dev)
    return path_join(get_this_module_dir(), "dictation.toml")
}

def private read_whole_file(path : string) : string {
    var content = ""
    fopen(path, "rb") $(f) {
        if (f != null) {
            content = fread(f)
        }
    }
    return content
}

def load_config(path : string; var err : string&) : DictationConfig {
    var cfg = DictationConfig()
    let content = read_whole_file(path)
    if (empty(content)) {
        err = "config not found or empty: {path}"
        return cfg
    }
    var perr = ""
    var js = ends_with(path, ".json") ? read_json(content, perr) : read_toml(content, perr)
    if (js == null) {
        err = "could not parse {path}: {perr}"
        return cfg
    }
    cfg.whisper_model = js?["whisper_model"] ?? cfg.whisper_model
    cfg.llm_model     = js?["llm_model"] ?? cfg.llm_model
    cfg.bot_token     = js?["bot_token"] ?? cfg.bot_token
    cfg.threads       = js?["threads"] ?? cfg.threads
    cfg.language      = js?["language"] ?? cfg.language
    cfg.max_tokens    = js?["max_tokens"] ?? cfg.max_tokens
    cfg.temp          = js?["temp"] ?? cfg.temp
    cfg.ffmpeg        = js?["ffmpeg"] ?? cfg.ffmpeg
    cfg.poll_timeout  = js?["poll_timeout"] ?? cfg.poll_timeout
    cfg.log_file      = js?["log_file"] ?? cfg.log_file
    cfg.log_level     = js?["log_level"] ?? cfg.log_level
    cfg.min_chars     = js?["min_chars"] ?? cfg.min_chars
    cfg.keep_audio_dir = js?["keep_audio_dir"] ?? cfg.keep_audio_dir
    unsafe {
        delete js
    }
    // TELEGRAM_BOT_TOKEN env overrides the config field (keep the secret out of the file if preferred)
    let envtok = get_env_variable("TELEGRAM_BOT_TOKEN")
    if (!empty(envtok)) {
        cfg.bot_token = envtok
    }
    return cfg
}

def private parse_log_level(s : string) : int {
    return LOG_TRACE if (s == "trace")
    return LOG_DEBUG if (s == "debug")
    return LOG_WARNING if (s == "warning" || s == "warn")
    return LOG_ERROR if (s == "error")
    return LOG_CRITICAL if (s == "critical")
    return LOG_INFO
}

// Report a fatal startup error to BOTH the console and the log file, then the caller returns
// false so main() exits non-zero. A bare panic() in a standalone -exe aborts the process
// silently (panic in a jitted frame), turning a bad model path into a mysterious exit with no
// message — so startup failures are reported explicitly here. Call after logger_set_path().
def private fatal(msg : string) {
    to_log(LOG_ERROR, "dictation: {msg}\n")   // console (stdout, level-tagged)
    logger_error("dictation", msg)            // log file
    logger_flush()
}

// ===== audio helpers =====

def private tmpdir() : string {
    var err = ""
    let d = temp_directory(err)
    return empty(d) ? "." : d
}

// Run ffmpeg to transcode any Telegram audio (OGG/Opus voice notes, mp3, m4a, …) to 16 kHz mono WAV.
// popen_argv is shell-free (no Windows quoting trap); the block drains ffmpeg's output to avoid a
// full-pipe stall. Returns true on a clean exit.
def private transcode_to_wav(cfg : DictationConfig; src, dst : string) : bool {
    let argv = [cfg.ffmpeg, "-y", "-hide_banner", "-loglevel", "error",
                "-i", src, "-ar", "16000", "-ac", "1", dst]
    let rc = unsafe(popen_argv(argv, 120.0) $(f) {
        if (f != null) {
            unsafe(fread_to_eof(f))   // drain the pipe so a chatty ffmpeg build can't stall
        }
    })
    return rc == 0
}

def private is_audio_mime(mime : string) : bool {
    return starts_with(mime, "audio/")
}

// The file_id of the audio in this message, and a short kind label — "" if the message has no audio.
def private audio_of(msg : message; var kind : string&) : string {
    let v = msg.voice
    if (v != null) {
        kind = "voice"
        return v.file_id
    }
    let a = msg.audio
    if (a != null) {
        kind = "audio"
        return a.file_id
    }
    let d = msg.document
    if (d != null && is_audio_mime(d.mime_type)) {
        kind = "document"
        return d.file_id
    }
    kind = ""
    return ""
}

// Reply to the user on a soft failure — but only in private chats, so groups don't get spammed.
def private notify(msg : message; text : string) {
    if (msg.chat._type == "private") {
        telegram_sendMessage(send_message(chat_id = "{msg.chat.id}", text = text))
    } else {
        logger_info("dictation.msg", "{text} (chat {msg.chat.id})")
    }
}

// ===== sender identity =====

// "First Last (@username)" — used to attribute the reply in group chats.
def private sender_display(msg : message) : string {
    let u = msg._from
    if (u == null) {
        return "Unknown"
    }
    let name = empty(u.last_name) ? u.first_name : "{u.first_name} {u.last_name}"
    return empty(u.username) ? name : "{name} (@{u.username})"
}

// "First Last @username [id N]" — the full identity written to the log.
def private sender_ident(msg : message) : string {
    let u = msg._from
    if (u == null) {
        return "chat {msg.chat.id}"
    }
    let name = empty(u.last_name) ? u.first_name : "{u.first_name} {u.last_name}"
    let uname = empty(u.username) ? "" : " @{u.username}"
    return "{name}{uname} [id {u.id}]"
}

// Send the reply, threaded to the original voice message so it's clearly attributed. Telegram caps a
// message at 4096 chars; short replies go as a single reply, longer ones split (unthreaded) via
// sendLongMessage — the name header still attributes them.
def private send_reply(msg : message; text : string) {
    let chat_id = "{msg.chat.id}"
    if (length(text) <= 4096) {
        var sm = send_message(chat_id = chat_id, text = text)
        // thread to the voice note, but still send (unthreaded) if it was deleted meanwhile
        sm.reply_parameters = new reply_parameters(message_id = msg.message_id, allow_sending_without_reply = true)
        telegram_sendMessage(sm)
    } else {
        telegram_sendLongMessage(send_message(chat_id = chat_id, text = text))
    }
}

// ===== pipeline =====

// Download → transcode → transcribe → clean → reply. Reads the global models/config; every heavy
// allocation (bytes, samples, ASR session, chat session) is a local here and is `delete`d as soon
// as it's done, to keep GC pressure low. Anything not deleted (on an error path) is out of scope on
// return and reclaimed by main's heap_collect. Call inside with_job_que().
def process_message(msg : message) {
    var kind = ""
    let file_id = audio_of(msg, kind)
    if (empty(file_id)) {
        return   // not an audio message
    }
    let chat_id = "{msg.chat.id}"
    logger_info("dictation.msg", "{kind} from {sender_ident(msg)} in chat {chat_id}")
    let t0 = ref_time_ticks()

    // resolve + download the file
    let finfo <- telegram_getFile(get_file(file_id = file_id))
    if (!empty(telegram_get_last_error())) {
        logger_error("dictation.msg", "getFile failed: {telegram_get_last_error()}")
        notify(msg, "Couldn't fetch the audio, sorry.")
        return
    }
    var bytes <- telegram_download(finfo)
    if (empty(bytes)) {
        logger_error("dictation.msg", "download failed: {telegram_get_last_error()}")
        notify(msg, "Couldn't download the audio, sorry.")
        return
    }

    // stage to temp, transcode to wav, decode to samples
    let base = path_join(tmpdir(), "dictation_{finfo.file_unique_id}")
    let src = "{base}.audio"
    let wav = "{base}.wav"
    fopen(src, "wb") $(f) {
        if (f != null) {
            fwrite(f, bytes)
        }
    }
    // optional archive of the original audio (date + sender id + Telegram's file name, real extension).
    // archived stays in scope so the transcript line below can link to the exact audio file.
    var archived = ""
    if (!empty(g_cfg.keep_audio_dir)) {
        mkdir_rec(g_cfg.keep_audio_dir)
        let sid = msg._from != null ? "{msg._from.id}" : "0"
        archived = path_join(g_cfg.keep_audio_dir, "{msg.date}_{sid}_{base_name(finfo.file_path)}")
        fopen(archived, "wb") $(f) {
            if (f != null) {
                fwrite(f, bytes)
            }
        }
    }
    delete bytes   // heavy download buffer — done once staged to disk
    let ok = transcode_to_wav(g_cfg, src, wav)
    remove(src)
    if (!ok) {
        remove(wav)
        logger_error("dictation.msg", "ffmpeg failed on {kind}")
        notify(msg, "Couldn't decode that audio format.")
        return
    }
    var samples <- load_audio_16k_mono(wav)
    remove(wav)
    if (empty(samples)) {
        notify(msg, "Couldn't read the decoded audio.")
        return
    }

    // transcribe (auto-detect) then rewrite into clean paragraphs, in the source language
    var s <- create_session(g_asr, g_cfg.language)
    let transcript = transcribe(g_asr, s, samples)
    let lang = empty(s.detected_lang) ? g_cfg.language : s.detected_lang
    delete samples   // decoded audio buffer no longer needed
    delete s         // ASR session scratch
    // transcript in the full log, linked to its archived audio file (empty audio if archiving is off)
    logger_info("dictation.msg", "transcript: {transcript}", JV((lang = lang, audio = archived)))

    // no usable speech -> don't waste the LLM. Empty always skips; min_chars also drops Whisper's
    // short silence hallucinations. Stay quiet in groups; only tell the user in a DM.
    let stripped = strip(transcript)
    if (length(stripped) <= g_cfg.min_chars) {
        logger_info("dictation.msg", "no usable speech ({length(stripped)} chars) — skipping LLM")
        notify(msg, "No speech detected.")
        return
    }

    var chat = create_chat(g_llm, dictation_system_prompt(lang), int64(g_cfg.max_tokens))
    add_user(chat, transcript)
    var params = SamplingParams()
    params.temp = g_cfg.temp
    let reply = respond(g_llm, chat, params) $(_piece) {
        return true
    }
    delete chat   // heavy KV-cache / chat session
    logger_info("dictation.msg", "reply: {reply}")

    // attribute the reply: in groups, prefix the sender's name; always thread it to the voice note
    let header = msg.chat._type == "private" ? "" : "🎙 {sender_display(msg)}\n\n"
    send_reply(msg, "{header}{reply}")
    if (!empty(telegram_get_last_error())) {
        logger_error("dictation.msg", "send failed: {telegram_get_last_error()}")
    }
    let dt = double(get_time_usec(t0)) / 1.0e6lf
    logger_info("dictation.msg", "done — {kind}, {lang}, {length(transcript)} -> {length(reply)} chars, {dt}s")
    logger_flush()
}

// One long-poll round: fetch updates, process each message. offset is threaded back so we ack them.
// Reads the global config/models; its own locals (updates + everything under process_message) are
// ephemeral and gone by the time the caller runs heap_collect.
def poll_once(var offset : int64&) {
    let updates <- telegram_getUpdates(get_updates(offset = offset, timeout = int64(g_cfg.poll_timeout), limit = 100l))
    let err = telegram_get_last_error()
    if (!empty(err)) {
        logger_error("dictation", "getUpdates failed: {err}")
        sleep(2000u)   // back off on a transient API/network error
        return
    }
    for (u in updates) {
        offset = u.update_id + 1l
        if (u.message != null) {
            process_message(*u.message)
        }
    }
}

// One-time startup: parse args, load config into g_cfg, set up logging, load the models into the
// globals, connect to Telegram. Kept OUT of main so none of its string/model locals ever sit on the
// poll loop's JIT stack (where the collector can't see them). Returns false to exit with *out_rc.
def init(var out_rc : int&) : bool {
    var r <- parse_args(type<DictationArgs>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<DictationArgs>), "dictation")
        out_rc = 1
        return false
    }
    let args <- r |> move_unwrap
    if (args.help) {
        print_help(get_command_info(type<DictationArgs>), "dictation")
        out_rc = 0
        return false
    }

    var cerr = ""
    g_cfg = load_config(resolve_config_path(args.config), cerr)

    // Set up logging FIRST so every fatal startup error below is written to the log file as
    // well as the console — not silently dropped. On a config failure g_cfg is defaulted, so
    // this still resolves to <exe_dir>/dictation.log. Engine (dasLLAMA/JIT) noise stays on stdout.
    let logpath = empty(g_cfg.log_file) ? path_join(get_this_module_dir(), "dictation.log") : g_cfg.log_file
    logger_set_path(logpath)
    logger_set_min_level(parse_log_level(g_cfg.log_level))
    print("dictation: logging to {logpath}\n")

    if (!empty(cerr)) {
        fatal(cerr)
        out_rc = 1
        return false
    }
    if (empty(g_cfg.bot_token)) {
        fatal("no bot token — set TELEGRAM_BOT_TOKEN or bot_token in the config")
        out_rc = 1
        return false
    }
    if (empty(g_cfg.whisper_model) || empty(g_cfg.llm_model)) {
        fatal("whisper_model and llm_model must be set in the config")
        out_rc = 1
        return false
    }
    // The model files must exist before we load them: in a standalone -exe the loader's
    // panic() on a missing file aborts the process SILENTLY (panic in a jitted frame), so
    // check here and report a clear, logged error instead of a mysterious exit code 127.
    if (!fexist(g_cfg.whisper_model)) {
        fatal("whisper model file not found: {g_cfg.whisper_model}")
        out_rc = 1
        return false
    }
    if (!fexist(g_cfg.llm_model)) {
        fatal("LLM model file not found: {g_cfg.llm_model}")
        out_rc = 1
        return false
    }

    log_tune_status("dictation")
    set_jobque_threads_cap(g_cfg.threads)   // cap dasLLAMA to cfg.threads workers (DAS_JOBQUE_THREADS still overrides)

    // The files exist, but a corrupt or unsupported model still panics deep in the loader.
    // Recover it so startup fails with a logged message rather than a silent abort. NOTE: a
    // bare `return` from inside a recover block does not propagate in a jitted -exe (execution
    // falls through) — so set a flag here and return AFTER the try/recover, in normal flow.
    var load_failed = false
    try {
        g_asr <- load_asr_model(g_cfg.whisper_model)
        g_llm <- load_model(g_cfg.llm_model, QuantMode.q8)
    } recover {
        fatal("failed to load models — check whisper_model / llm_model are valid model files: whisper='{g_cfg.whisper_model}' llm='{g_cfg.llm_model}'")
        load_failed = true
    }
    if (load_failed) {
        out_rc = 1
        return false
    }
    telegram_set_configuration(configuration(token = g_cfg.bot_token))
    logger_info("dictation", "bot started (whisper={g_cfg.whisper_model}, llm={g_cfg.llm_model}, threads={g_cfg.threads})")
    logger_flush()
    return true
}

[export, tune_policy(missing = "auto")]
def main : int {
    // dasLLAMA inference on the interpreter is uselessly slow — require the JIT (or a jit -exe build)
    if (!jit_enabled() && !is_standalone_exe()) {
        to_log(LOG_ERROR, "dictation: run under the JIT — daslang -jit main.das -- ...\n")
        return 1
    }
    var rc = 0
    if (!init(rc)) {
        return rc
    }
    // The loop holds NO collectable locals — only `offset` (an int) — so heap_collect is safe.
    with_job_que() {
        setup_dasllama_jobque()
        var offset = 0l
        while (true) {
            poll_once(offset)
            unsafe(heap_collect(true, true))   // reclaim this round's string + object garbage; globals survive
        }
    }
    return 0
}
