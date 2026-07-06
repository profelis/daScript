options gen2
options _jit_fast_math = true   // ggml-parity FP laxity (non-bit-exact); inference tool, not the test suite

module openai_server

require dasllama/dasllama       // the public facade — the ONLY dasLLAMA surface this tool touches
require dashv/dashv_boost public
require daslib/json_boost
require daslib/jobque_boost
require daslib/strings_boost    // join()
require daslib/fio              // sleep(), path_join, base_name, remove, get_env_variable
require strings
require math
require audio                   // miniaudio decoder: any uploaded audio format -> 16 kHz mono f32

// An OpenAI-compatible HTTP server over the dasLLAMA facade. It reaches only public verbs
// (load_model / create_chat / add_user / add_assistant / respond / transcribe) — the acceptance
// test for the API: if it builds with no reach into the engine internals, the facade is complete.
// One process, one context, one in-flight request (serialized on the tick thread).

// ===== Served state (set once at startup; handlers run serially on the tick thread) =====

var g_model = Model()
var g_model_name = ""
var g_asr = AsrModel()
var g_has_asr = false
var g_should_stop = false
var g_req_counter = 0l

//! Move a loaded model into the server (call once, before run_server). ``name`` is the id reported
//! by ``/v1/models`` and echoed back in responses.
def set_model(var m : Model; name : string) {
    g_model <- m
    g_model_name = name
}

//! Move a loaded ASR model in, enabling ``/v1/audio/transcriptions`` (call once, before run_server).
def set_asr(var a : AsrModel) {
    g_asr <- a
    g_has_asr = true
}

//! Ask the tick loop to exit at the next iteration (also wired to ``POST /shutdown``).
def request_stop() {
    g_should_stop = true
}

// ===== OpenAI wire shapes (response) =====

struct private OaiMessage {
    role : string
    content : string
}

struct private OaiChoice {
    index : int
    message : OaiMessage
    finish_reason : string
}

struct private OaiUsage {
    prompt_tokens : int64
    completion_tokens : int64
    total_tokens : int64
}

struct private OaiChatResponse {
    id : string
    @rename = "object" _object : string
    created : int64
    model : string
    choices : array<OaiChoice>
    usage : OaiUsage
}

// Streaming (stream=true) chunk shapes. @optional so an empty delta emits `{}` and an absent
// finish_reason is dropped (clients read absent as null) — matching OpenAI's chunk framing.
struct private OaiDelta {
    @optional role : string
    @optional content : string
}

struct private OaiStreamChoice {
    index : int
    delta : OaiDelta
    @optional finish_reason : string
}

struct private OaiStreamChunk {
    id : string
    @rename = "object" _object : string
    created : int64
    model : string
    choices : array<OaiStreamChoice>
}

struct private OaiComplStreamChoice {
    index : int
    text : string
    @optional finish_reason : string
}

struct private OaiComplStreamChunk {
    id : string
    @rename = "object" _object : string
    created : int64
    model : string
    choices : array<OaiComplStreamChoice>
}

struct private OaiComplChoice {
    index : int
    text : string
    finish_reason : string
}

struct private OaiComplResponse {
    id : string
    @rename = "object" _object : string
    created : int64
    model : string
    choices : array<OaiComplChoice>
    usage : OaiUsage
}

struct private OaiModel {
    id : string
    @rename = "object" _object : string
    created : int64
    owned_by : string
}

struct private OaiModelList {
    @rename = "object" _object : string
    data : array<OaiModel>
}

struct private OaiErrDetail {
    message : string
    @rename = "type" _type : string
}

struct private OaiErr {
    error : OaiErrDetail
}

// request shape — only the text fields; content-as-array (multimodal) and union `stop` are handled
// off the raw JsonValue tree in the handler.
struct private OaiReqMessage {
    role : string
    content : string
}

// /v1/audio/transcriptions response shapes.
struct private OaiTranscription {
    text : string
}

struct private OaiVerboseSegment {
    id : int
    start : float
    end : float
    text : string
}

struct private OaiVerboseTranscription {
    task : string
    language : string
    duration : float
    text : string
    segments : array<OaiVerboseSegment>
}

// /v1/embeddings response shapes.
struct private OaiEmbedding {
    @rename = "object" _object : string
    embedding : array<float>
    index : int
}

struct private OaiEmbUsage {
    prompt_tokens : int64
    total_tokens : int64
}

struct private OaiEmbeddingList {
    @rename = "object" _object : string
    data : array<OaiEmbedding>
    model : string
    usage : OaiEmbUsage
}

// ===== Helpers =====

def private next_id(prefix : string) : string {
    g_req_counter ++
    return "{prefix}-{g_req_counter}"
}

// `created` is a unix-seconds field no OpenAI client validates; a monotone stand-in is honest and
// avoids a wall-clock dependency in the hot path.
def private created_ts() : int64 {
    return 1751200000l + g_req_counter
}

def private error_body(msg, kind : string) : string {
    return sprint_json(OaiErr(error = OaiErrDetail(message = msg, _type = kind)), false)
}

// Terminal error on a streaming route's writer (chat/completions run through the writer).
def private bad_request(srv : WebSocketServer; var writer : HttpResponseWriter?; msg : string) {
    respond(srv, writer, int(http_status.BAD_REQUEST), "application/json",
            error_body(msg, "invalid_request_error"))
}

// One chat.completion.chunk SSE event. role-only for the opening delta, content for each token,
// empty delta + finish_reason for the terminating chunk.
def private send_chat_chunk(srv : WebSocketServer; var writer : HttpResponseWriter?;
                            id : string; created : int64; role, content, finish : string) {
    var chunk = OaiStreamChunk(id = id, _object = "chat.completion.chunk", created = created, model = g_model_name)
    chunk.choices |> push(OaiStreamChoice(index = 0, delta = OaiDelta(role = role, content = content),
                                          finish_reason = finish))
    sse_event(srv, writer, sprint_json(chunk, false), "")
}

def private send_compl_chunk(srv : WebSocketServer; var writer : HttpResponseWriter?;
                             id : string; created : int64; text, finish : string) {
    var chunk = OaiComplStreamChunk(id = id, _object = "text_completion", created = created, model = g_model_name)
    chunk.choices |> push(OaiComplStreamChoice(index = 0, text = text, finish_reason = finish))
    sse_event(srv, writer, sprint_json(chunk, false), "")
}

// Clamp a requested reply budget to [1, model context].
def private clamp_max(requested : int64) : int64 {
    return clamp(requested, 1l, g_model.config.seq_len)
}

// Error on a buffered (resp-based) route — /v1/models and the audio endpoints use the response path.
def private resp_error(var resp : HttpResponse?; status : http_status; msg : string) : http_status {
    return resp |> JSON(error_body(msg, "invalid_request_error"), status)
}

def private tmpdir() : string {
    let t = get_env_variable("TMPDIR")
    return empty(t) ? "/tmp" : t
}

// Decode an uploaded audio file (any format miniaudio handles) to 16 kHz mono f32 PCM — the ASR
// input. Empty on failure. (dasLLAMA's ASR facade takes samples, not a path — this is the decode rail
// its examples roll by hand; the server owns it so the facade stays audio-IO-free.)
def private load_audio_16k_mono(path : string) : array<float> {
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
        samples |> resize(total + chunk)   // grow by a chunk, read straight into the tail
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

// ===== Handlers =====

def private handle_models(var resp : HttpResponse?) : http_status {
    var list = OaiModelList(_object = "list")
    list.data |> push(OaiModel(id = g_model_name, _object = "model", created = created_ts(), owned_by = "dasllama"))
    if (g_has_asr) {
        list.data |> push(OaiModel(id = "{g_model_name}-asr", _object = "model", created = created_ts(), owned_by = "dasllama"))
    }
    return resp |> JSON(sprint_json(list, false), http_status.OK)
}

// /v1/embeddings: mean-pooled, L2-normalized sentence embeddings over the facade `embed` verb.
// `input` is a string or an array of strings; usage is counted via the facade `encode` (cheap
// relative to the forward). Decoder-only-as-embedder — RAG-grade vectors, not a dedicated model.
def private handle_embeddings(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
    var perr = ""
    let js = read_json(string(req.body), perr)
    if (js == null) {
        return resp_error(resp, http_status.BAD_REQUEST, "invalid JSON: {perr}")
    }
    let iv = js?["input"]
    if (iv == null) {
        return resp_error(resp, http_status.BAD_REQUEST, "'input' is required (a string or array of strings)")
    }
    var inputs : array<string>
    if (iv.value is _array) {
        inputs <- from_JV(iv, type<array<string>>)
    } else {
        let single = iv ?? ""
        if (empty(single)) {
            return resp_error(resp, http_status.BAD_REQUEST, "'input' must be a non-empty string or array of strings")
        }
        inputs |> push(single)
    }
    if (empty(inputs)) {
        return resp_error(resp, http_status.BAD_REQUEST, "'input' is empty")
    }

    var out = OaiEmbeddingList(_object = "list", model = g_model_name)
    out.data |> reserve(length(inputs))
    var prompt_tokens = 0l
    var idx = 0
    for (text in inputs) {
        let toks <- encode(g_model, text, true, false)
        prompt_tokens += int64(length(toks))
        var vec = embed(g_model, text)
        out.data |> emplace(OaiEmbedding(_object = "embedding", embedding <- vec, index = idx))
        idx ++
    }
    out.usage = OaiEmbUsage(prompt_tokens = prompt_tokens, total_tokens = prompt_tokens)
    return resp |> JSON(sprint_json(out, false), http_status.OK)
}

def private handle_chat(srv : WebSocketServer; var req : HttpRequest?; var writer : HttpResponseWriter?) {
    var perr = ""
    let js = read_json(string(req.body), perr)
    if (js == null) {
        bad_request(srv, writer, "invalid JSON: {perr}")
        return
    }
    let msgs_v = js?["messages"]
    if (msgs_v == null || !(msgs_v.value is _array)) {
        bad_request(srv, writer, "'messages' must be an array")
        return
    }
    let messages = from_JV(msgs_v, type<array<OaiReqMessage>>)
    let streaming = js?["stream"] ?? false
    var params = SamplingParams()
    params.temp = js?["temperature"] ?? 0.0
    params.top_k = js?["top_k"] ?? 0l
    let max_new = clamp_max(js?["max_tokens"] ?? 256l)

    // OpenAI is stateless — the client resends the whole transcript. Fold system turns, replay prior
    // user/assistant pairs into the KV cache (add_assistant = inject, no generation), then respond to
    // the trailing user turn.
    var system = ""
    for (msg in messages) {
        if (msg.role == "system") {
            system = empty(system) ? msg.content : "{system}\n{msg.content}"
        }
    }
    var chat = create_chat(g_model, system, max_new)
    var pending_user = false
    for (msg in messages) {
        if (msg.role == "user") {
            add_user(chat, msg.content)
            pending_user = true
        } elif (msg.role == "assistant" && pending_user) {
            add_assistant(g_model, chat, msg.content)
            pending_user = false
        }
    }
    if (!pending_user) {
        bad_request(srv, writer, "the last message must be from the user")
        return
    }

    let cid = next_id("chatcmpl")
    let created = created_ts()
    if (streaming) {
        send_chat_chunk(srv, writer, cid, created, "assistant", "", "")   // opening role delta
        respond(g_model, chat, params) $(piece) {
            send_chat_chunk(srv, writer, cid, created, "", piece, "")
            return true
        }
        let st = stats(chat.session)
        send_chat_chunk(srv, writer, cid, created, "", "", st.n_gen >= max_new ? "length" : "stop")
        sse_event(srv, writer, "[DONE]", "")
        close_writer(srv, writer)
        return
    }

    let reply = respond(g_model, chat, params) $(_piece) {
        return true
    }
    let st = stats(chat.session)
    let finish = st.n_gen >= max_new ? "length" : "stop"
    var out = OaiChatResponse(id = cid, _object = "chat.completion", created = created, model = g_model_name)
    out.choices |> push(OaiChoice(index = 0, message = OaiMessage(role = "assistant", content = reply),
                                  finish_reason = finish))
    out.usage = OaiUsage(prompt_tokens = st.n_prompt, completion_tokens = st.n_gen,
                         total_tokens = st.n_prompt + st.n_gen)
    respond(srv, writer, int(http_status.OK), "application/json", sprint_json(out, false))
}

def private handle_completion(srv : WebSocketServer; var req : HttpRequest?; var writer : HttpResponseWriter?) {
    var perr = ""
    let js = read_json(string(req.body), perr)
    if (js == null) {
        bad_request(srv, writer, "invalid JSON: {perr}")
        return
    }
    let prompt = js?["prompt"] ?? ""
    if (empty(prompt)) {
        bad_request(srv, writer, "'prompt' must be a non-empty string")
        return
    }
    let streaming = js?["stream"] ?? false
    var params = SamplingParams()
    params.temp = js?["temperature"] ?? 0.0
    params.top_k = js?["top_k"] ?? 0l
    let max_new = clamp_max(js?["max_tokens"] ?? 256l)

    let cid = next_id("cmpl")
    let created = created_ts()
    var session = create_session(g_model)
    let toks <- encode(g_model, prompt, true, false)
    if (streaming) {
        generate(g_model, session, toks, params, max_new) $(_id, piece) {
            send_compl_chunk(srv, writer, cid, created, piece, "")
            return true
        }
        let st = stats(session)
        send_compl_chunk(srv, writer, cid, created, "", st.n_gen >= max_new ? "length" : "stop")
        sse_event(srv, writer, "[DONE]", "")
        close_writer(srv, writer)
        return
    }

    var reply_parts : array<string>
    generate(g_model, session, toks, params, max_new) $(_id, piece) {
        reply_parts |> push(piece)
        return true
    }
    let st = stats(session)
    let finish = st.n_gen >= max_new ? "length" : "stop"
    var out = OaiComplResponse(id = cid, _object = "text_completion", created = created, model = g_model_name)
    out.choices |> push(OaiComplChoice(index = 0, text = join(reply_parts, ""), finish_reason = finish))
    out.usage = OaiUsage(prompt_tokens = st.n_prompt, completion_tokens = st.n_gen,
                         total_tokens = st.n_prompt + st.n_gen)
    respond(srv, writer, int(http_status.OK), "application/json", sprint_json(out, false))
}

// /v1/audio/transcriptions (translate=false) and /v1/audio/translations (translate=true, to English).
// Multipart upload: save the 'file' part to disk (binary-safe), decode to 16 kHz mono f32, transcribe.
def private handle_transcription(var req : HttpRequest?; var resp : HttpResponse?; translate : bool) : http_status {
    if (!g_has_asr) {
        return resp_error(resp, http_status.NOT_FOUND, "no ASR model loaded — start the server with --asr")
    }
    var fname = ""
    each_form_field(req) $(name, _content, filename) {
        if (name == "file" && !empty(filename)) {
            fname = filename
        }
    }
    if (empty(fname)) {
        return resp_error(resp, http_status.BAD_REQUEST, "multipart form must include a 'file' audio upload")
    }
    let temppath = path_join(tmpdir(), "dasllama_upload_{base_name(fname)}")
    save_form_file(req, "file", temppath)
    let samples <- load_audio_16k_mono(temppath)
    remove(temppath)
    if (empty(samples)) {
        return resp_error(resp, http_status.BAD_REQUEST, "could not decode the uploaded audio")
    }
    let fmt = get_form_data(req, "response_format")
    var lang = get_form_data(req, "language")
    if (empty(lang)) {
        lang = "en"
    }
    var session <- create_session(g_asr, lang)
    session.translate = translate
    if (fmt == "verbose_json") {
        var vt = OaiVerboseTranscription(task = translate ? "translate" : "transcribe",
                                         language = lang, duration = float(length(samples)) / 16000.0)
        var full : array<string>
        var sid = 0
        transcribe(g_asr, session, samples) $(seg) {
            vt.segments |> push(OaiVerboseSegment(id = sid, start = float(seg.t0) / 100.0,
                                                  end = float(seg.t1) / 100.0, text = seg.text))
            full |> push(seg.text)
            sid ++
        }
        vt.text = join(full, "")
        vt.language = session.detected_lang
        return resp |> JSON(sprint_json(vt, false), http_status.OK)
    }
    let text = transcribe(g_asr, session, samples)
    if (fmt == "text") {
        return resp |> TEXT_PLAIN(text)
    }
    return resp |> JSON(sprint_json(OaiTranscription(text = text), false), http_status.OK)
}

// ===== Server =====

class OpenAiServer : HvWebServer {
    def override onInit {
        allow_cors()
        GET("/v1/models") <| @(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
            return handle_models(resp)
        }
        STREAM("/v1/chat/completions") <| @(var req : HttpRequest?; var writer : HttpResponseWriter?) {
            handle_chat(server, req, writer)
        }
        STREAM("/v1/completions") <| @(var req : HttpRequest?; var writer : HttpResponseWriter?) {
            handle_completion(server, req, writer)
        }
        POST("/v1/audio/transcriptions") <| @(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
            return handle_transcription(req, resp, false)
        }
        POST("/v1/audio/translations") <| @(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
            return handle_transcription(req, resp, true)
        }
        POST("/v1/embeddings") <| @(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
            return handle_embeddings(req, resp)
        }
        POST("/shutdown") <| @(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
            g_should_stop = true
            return resp |> JSON("\{\"ok\":true}", http_status.OK)
        }
    }
}

//! Run the server on the calling thread until ``request_stop`` (or ``POST /shutdown``). Sets up the
//! job queue so the facade's kernels thread, then ticks. Call after ``set_model`` (and optionally
//! ``set_asr``).
def run_server(port : int) {
    with_job_que() {
        setup_dasllama_jobque()
        var server = new OpenAiServer()
        server->init(port)
        server->start()
        to_log(LOG_INFO, "dasllama-server listening on http://127.0.0.1:{port}/v1  (model: {g_model_name})\n")
        while (!g_should_stop) {
            server->tick()
            sleep(2u)
        }
        server->stop()
        server->cleanup()
        unsafe {
            delete server
        }
    }
}
