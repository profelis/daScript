options gen2
options stack = 65536   // the forward/prefill chain + generated kernels need more than the 16K default on arm64
options fast_math = true   // ggml-parity FP laxity (non-bit-exact); inference tool, not the test suite

module openai_server

require dasllama/dasllama       // the public facade — the main dasLLAMA surface this tool touches
require llm_scheduler           // continuous-batching scheduler (sibling — bare require, hyphenated dir)
require dashv/dashv_boost public
require daslib/json_boost
require daslib/defer            // defer() { delete js } — free the parsed request JSON on every exit path
require daslib/jobque_boost
require daslib/strings_boost    // join()
require daslib/fio              // sleep(), path_join, base_name, remove, get_env_variable
require strings
require math
require dasllama/dasllama_audio_io   // load_audio_16k_mono: any uploaded audio format -> 16 kHz mono f32

// An OpenAI-compatible HTTP server over the dasLLAMA facade. It reaches only public facade verbs —
// no engine internals — which is the acceptance test for the API: if a full OpenAI surface builds
// without reaching into the engine, the facade is complete.
// Chat and completion requests batch continuously: handlers parse + render + register and return;
// run_server's loop drives llm_scheduler (one eval_batch decode step over every live stream + one
// bounded prefill chunk per tick) and routes SchedEvents back to each request's writer. Streaming
// and buffered responses both ride the deferred writer ops, so N streams generate concurrently.
// The buffered holdouts (/v1/models, /v1/embeddings, /v1/audio/*, /shutdown, /v1/stats) still run
// to completion in-handler and stall generation for their duration.

// ===== Served state (set once at startup; handlers run serially on the tick thread) =====

var g_model = Model()
var g_model_name = ""
var g_asr = AsrModel()
var g_has_asr = false
var g_should_stop = false
var g_req_counter = 0l
var g_sched = Scheduler()       // live from run_server on; handlers submit into it
var g_events : array<SchedEvent>

// One registered request's HTTP side: where this stream id's SchedEvents go. The writer is owned by
// dasHV's active_writers (respond/close_writer/release_writer drop it) — never deleted from here.
struct private StreamWire {
    @do_not_delete writer : HttpResponseWriter?
    streaming : bool
    is_chat : bool                  // chat.completion.chunk vs text_completion framing
    id : string                     // "chatcmpl-N" / "cmpl-N"
    created : int64
    reply_parts : array<string>     // non-streaming: pieces accumulate until the finished event
}

var g_wires : table<int64; StreamWire>

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

// request shape — text fields only. Multimodal content arrays and the request's `stop` field are NOT
// read: content is parsed as a plain string, and stop sequences are not honored.
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

// Stream ids are the request counter: the scheduler keys on the int64, the wire keys the JSON id.
def private next_id() : int64 {
    g_req_counter ++
    return g_req_counter
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
    var err = ""
    let d = temp_directory(err)   // fio: platform temp dir (Windows GetTempPath, POSIX $TMPDIR/tmp)
    return empty(d) ? "/tmp" : d
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
    var js = read_json(string(req.body), perr)
    if (js == null) {
        return resp_error(resp, http_status.BAD_REQUEST, "invalid JSON: {perr}")
    }
    defer() { unsafe { delete js } }
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

// Validate the rendered prompt, submit it to the scheduler, and register the wire that routes its
// SchedEvents back to `writer`. Owns the mandatory 400 (prompt does not fit the context — submit
// would panic) and the 503 (queue full). Moves prompt/stop_ids/close_toks into the request.
def private register_request(srv : WebSocketServer; var writer : HttpResponseWriter?;
                             var prompt, stop_ids, close_toks : array<int64>;
                             params : SamplingParams; max_new : int64;
                             streaming, is_chat : bool; prefix : string) {
    let np = int64(length(prompt))
    if (np + 1l > g_model.config.seq_len) {
        bad_request(srv, writer, "the rendered prompt is {np} tokens; the model context is {g_model.config.seq_len} — shorten the conversation or raise --ctx")
        return
    }
    let rid = next_id()
    let cid = "{prefix}-{rid}"
    let created = created_ts()
    var preq <- PendingReq(id = rid, params = params, max_new = max_new)
    preq.prompt <- prompt
    preq.stop_ids <- stop_ids
    preq.close_toks <- close_toks
    if (!submit(g_model, g_sched, preq)) {
        delete preq
        respond(srv, writer, int(http_status.SERVICE_UNAVAILABLE), "application/json",
                error_body("the server is at capacity ({g_sched.max_queue} requests queued) — retry shortly", "server_error"))
        return
    }
    var wire <- StreamWire(writer = writer, streaming = streaming, is_chat = is_chat,
                           id = cid, created = created)
    g_wires[rid] <- wire
    if (streaming && is_chat) {
        send_chat_chunk(srv, writer, cid, created, "assistant", "", "")   // opening role delta
    }
}

// Parse + validate + render + register, then return — no generation in the handler. The prompt is
// rendered through the S1 render seam (tokens only, no KV), so a queued request holds no cache
// memory; the session exists only once the scheduler admits the stream.
def private handle_chat(srv : WebSocketServer; var req : HttpRequest?; var writer : HttpResponseWriter?) {
    var perr = ""
    var js = read_json(string(req.body), perr)
    if (js == null) {
        bad_request(srv, writer, "invalid JSON: {perr}")
        return
    }
    defer() { unsafe { delete js } }
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
    // user/assistant pairs through the renderer, then render the trailing user turn + generation prompt.
    var system = ""
    for (msg in messages) {
        if (msg.role == "system") {
            system = empty(system) ? msg.content : "{system}\n{msg.content}"
        }
    }
    var chat <- create_chat_renderer(g_model, system, max_new)
    defer() { delete chat }
    var prompt : array<int64>
    defer() { delete prompt }
    var pending_user = false
    for (msg in messages) {
        if (msg.role == "user") {
            add_user(chat, msg.content)
            pending_user = true
        } elif (msg.role == "assistant" && pending_user) {
            render_assistant(g_model, chat, msg.content, prompt)
            pending_user = false
        }
    }
    if (!pending_user) {
        bad_request(srv, writer, "the last message must be from the user")
        return
    }
    var turn <- render_turn(g_model, chat)
    prompt |> push_from(turn)
    delete turn
    var close <- render_close(g_model, chat)
    defer() { delete close }   // register_request moves it on success; the 400/503 paths leave it here
    register_request(srv, writer, prompt, chat.stop_ids, close, params, max_new, streaming, true, "chatcmpl")
}

def private handle_completion(srv : WebSocketServer; var req : HttpRequest?; var writer : HttpResponseWriter?) {
    var perr = ""
    var js = read_json(string(req.body), perr)
    if (js == null) {
        bad_request(srv, writer, "invalid JSON: {perr}")
        return
    }
    defer() { unsafe { delete js } }
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
    var toks <- encode(g_model, prompt, true, false)
    defer() { delete toks }
    // no stop ids and no close: raw completions run to the budget, matching bare generate()
    var none_stop : array<int64>
    var none_close : array<int64>
    register_request(srv, writer, toks, none_stop, none_close, params, max_new, streaming, false, "cmpl")
}

// Evict streams whose client vanished: is_writer_connected reads false once the connection is
// gone (the async writer ops themselves never report a dead peer). The scheduler appends the
// "evicted" finished event; flush_events below releases the writer and drops the wire.
def private reap_disconnected(srv : WebSocketServer) {
    for (id, w in keys(g_wires), values(g_wires)) {
        if (!is_writer_connected(srv, w.writer)) {
            evict(g_sched, id, g_events)
        }
    }
}

// Route drained SchedEvents to their writers: streaming wires emit SSE chunks, buffered wires
// accumulate pieces and respond once at finish. "evicted" releases the writer with no bytes —
// the client is gone (reap_disconnected produced it). Finished wires unregister.
def private flush_events(srv : WebSocketServer) {
    for (e in g_events) {
        // interior pointer into g_wires — nothing inserts into the table between here and the erase
        var w = unsafe(g_wires?[e.stream])
        if (w == null) {
            continue
        }
        if (e.kind == SchedEventKind.piece) {
            if (!w.streaming) {
                w.reply_parts |> push(e.text)
            } elif (w.is_chat) {
                send_chat_chunk(srv, w.writer, w.id, w.created, "", e.text, "")
            } else {
                send_compl_chunk(srv, w.writer, w.id, w.created, e.text, "")
            }
            continue
        }
        if (e.finish == "evicted") {
            release_writer(srv, w.writer)
        } elif (w.streaming) {
            if (w.is_chat) {
                send_chat_chunk(srv, w.writer, w.id, w.created, "", "", e.finish)
            } else {
                send_compl_chunk(srv, w.writer, w.id, w.created, "", e.finish)
            }
            sse_event(srv, w.writer, "[DONE]", "")
            close_writer(srv, w.writer)
        } elif (w.is_chat) {
            var out = OaiChatResponse(id = w.id, _object = "chat.completion", created = w.created, model = g_model_name)
            out.choices |> push(OaiChoice(index = 0,
                                          message = OaiMessage(role = "assistant", content = join(w.reply_parts, "")),
                                          finish_reason = e.finish))
            out.usage = OaiUsage(prompt_tokens = e.n_prompt, completion_tokens = e.n_gen,
                                 total_tokens = e.n_prompt + e.n_gen)
            respond(srv, w.writer, int(http_status.OK), "application/json", sprint_json(out, false))
            delete out
        } else {
            var out = OaiComplResponse(id = w.id, _object = "text_completion", created = w.created, model = g_model_name)
            out.choices |> push(OaiComplChoice(index = 0, text = join(w.reply_parts, ""), finish_reason = e.finish))
            out.usage = OaiUsage(prompt_tokens = e.n_prompt, completion_tokens = e.n_gen,
                                 total_tokens = e.n_prompt + e.n_gen)
            respond(srv, w.writer, int(http_status.OK), "application/json", sprint_json(out, false))
            delete out
        }
        delete g_wires[e.stream]   // finalize the wire in place (erase is a raw remove)
        g_wires |> erase(e.stream)
    }
    g_events |> clear()
}

// /v1/stats: the scheduler's counters as JSON (buffered — cheap enough to run in-handler).
struct private OaiStatsResponse {
    active : int64
    queued : int64
    peak_active : int64
    admitted : int64
    finished : int64
    evicted : int64
    decode_steps : int64
    gen_tokens : int64
    avg_batch : float
    cached_tokens : int64
    prefix_pages : int64
    max_streams : int64
    chunk_tokens : int64
}

def private handle_stats(var resp : HttpResponse?) : http_status {
    let out = OaiStatsResponse(
        active = n_active(g_sched), queued = n_queued(g_sched), peak_active = g_sched.peak_active,
        admitted = g_sched.n_admitted, finished = g_sched.n_finished, evicted = g_sched.n_evicted,
        decode_steps = g_sched.decode_steps, gen_tokens = g_sched.gen_tokens,
        avg_batch = float(g_sched.sum_batch) / float(max(g_sched.decode_steps, 1l)),
        cached_tokens = g_sched.cached_tokens, prefix_pages = prefix_held_groups(g_sched.prefix),
        max_streams = g_sched.max_streams, chunk_tokens = g_sched.chunk_tokens)
    return resp |> JSON(sprint_json(out, false), http_status.OK)
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
        GET("/v1/stats") <| @(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
            return handle_stats(resp)
        }
        POST("/shutdown") <| @(var req : HttpRequest?; var resp : HttpResponse?) : http_status {
            g_should_stop = true
            return resp |> JSON("\{\"ok\":true}", http_status.OK)
        }
    }
}

//! Run the server on the calling thread until ``request_stop`` (or ``POST /shutdown``). Sets up the
//! job queue, then drives the serve loop: pump HTTP (handlers parse + render + submit), evict
//! streams whose client disconnected, one scheduler step (continuous batching over every live
//! stream), flush events to the writers.
//! ``max_streams`` concurrent generation streams, ``max_queue`` waiting requests (503 beyond),
//! ``chunk_tokens`` the prefill quantum (decode stalls at most this many tokens per tick).
//! ``page_rows`` > 0 (the default) serves PAGED: KV memory tracks actual context and a prefix
//! cache reuses completed streams' pages, so repeated prompts (system prompts, multi-turn chats)
//! skip their prefill; ``prefix_groups`` caps the cache (0 = auto: one full context per stream
//! slot, < 0 = unbounded). ``page_rows`` = 0 restores flat preallocated sessions (each the full
//! ``--ctx`` slab). Call after ``set_model``.
def run_server(port : int; max_streams : int64 = 4l; max_queue : int64 = 32l; chunk_tokens : int64 = 64l;
               page_rows : int64 = 64l; prefix_groups : int64 = 0l) {
    g_should_stop = false   // reset so a restart in the same context after /shutdown doesn't exit at once
    with_job_que() {
        setup_dasllama_jobque()
        var pfx = prefix_groups
        if (page_rows > 0l && pfx == 0l) {   // auto: retain up to one full context per stream slot
            pfx = max_streams * ((g_model.config.seq_len + page_rows - 1l) / page_rows)
        }
        if (pfx < 0l) {
            pfx = 0l   // explicit unbounded
        }
        g_sched <- create_scheduler(g_model, max_streams, max_queue, chunk_tokens, page_rows, pfx)
        var server = new OpenAiServer()
        server->init(port)
        let rc = server->start()   // 0 on success; non-zero = bind/listen failed (e.g. port in use)
        if (rc != 0) {
            to_log(LOG_ERROR, "dasllama-server: could not start on port {port} (start rc {rc}; is the port already in use?)\n")
        } else {
            let pfx_desc = pfx > 0l ? "{pfx}" : "unbounded"
            let kv_mode = page_rows > 0l ? "paged P={page_rows}, prefix cache {pfx_desc} pages" : "flat"
            to_log(LOG_INFO, "dasllama-server listening on http://127.0.0.1:{port}/v1  (model: {g_model_name}, streams: {max_streams}, prefill chunk: {chunk_tokens}, kv: {kv_mode})\n")
            while (!g_should_stop) {
                server->tick()   // drains queued handlers: requests parse + render + submit here
                reap_disconnected(server.server)
                let busy = scheduler_step(g_model, g_sched, g_events)
                flush_events(server.server)
                if (!busy) {
                    sleep(2u)
                }
            }
            server->stop()
        }
        server->cleanup()
        unsafe {
            delete server
        }
        unsafe {
            delete g_sched   // live sessions + workspace go with it (writers already died with the server)
        }
        delete g_events
        delete g_wires
    }
}
