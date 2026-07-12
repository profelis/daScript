options gen2
options stack = 262144   // the forward chain runs deep under the HTTP tick + C++->das handler bridge

// dasllama-server — an OpenAI-compatible HTTP server over the dasLLAMA facade.
//
//   bin/daslang -jit utils/dasllama-server/main.das -- --model <model.gguf> [--port 8080] [--quant q8]
//                                                       [--kv-dtype f16] [--asr <asr.bin>] [--mmproj <mmproj.gguf>]
//                                                       [--config server.toml] [--tune]
//
// --config points at a TOML file whose keys mirror the long flag names (model = "...", port = 8080,
// kv_dtype = "tq4", ...); explicit CLI flags override it.
//
// Then point any OpenAI client at http://127.0.0.1:<port>/v1 (opencode, Open WebUI, the `llm` CLI, …).
//
// Per-box tuning: the first start on an untuned box runs the dasLLAMA kernel tuner and relaunches
// itself with the winners (missing = "auto"); `--tune` forces a re-tune. Set DAS_TUNE_POLICY=error
// while developing to skip per-start tuning (it prints the tuner command instead). The winners live
// at <das_root>/dasllama.tune.json, shared by every dasLLAMA app on this box.

require openai_server           // the server + route handlers (this directory)
require dasllama/dasllama       // load_model / QuantMode / load_asr_model
require llvm/daslib/llvm_tune   // [tune_policy] + tune_status (the injected guard resolves here)
require daslib/clargs
require daslib/toml
require daslib/json_boost
require daslib/fio
require math

[CommandLineArgs]
struct ServerArgs {
    @clarg_short = "c"
    @clarg_doc = "TOML config file; keys mirror the long flag names (explicit CLI flags override)"
    config : string

    @clarg_short = "m"
    @clarg_doc = "Path to the GGUF model to serve (or model = in --config)"
    model : string

    @clarg_short = "p"
    @clarg_doc = "Port to listen on (default 8080)"
    port : int

    @clarg_short = "q"
    @clarg_doc = "Weight quantization: fp32 | q8 | q4 (default q8)"
    quant : string

    @clarg_doc = "KV cache codec: f32 | f16 | q8_0 | tq4 (default f16)"
    kv_dtype : string

    @clarg_short = "a"
    @clarg_doc = "Path to an ASR model — enables /v1/audio/transcriptions"
    asr : string

    @clarg_doc = "mmproj for the GGUF Qwen3-ASR route (paired with --asr)"
    mmproj : string

    @clarg_doc = "Context-length cap in tokens (default 4096)"
    ctx : int

    @clarg_short = "s"
    @clarg_doc = "Max concurrent generation streams (default 4)"
    streams : int

    @clarg_doc = "Prefill chunk in tokens: decode stalls at most this many per tick (default 64)"
    chunk : int

    @clarg_doc = "KV page size in positions for paged serving (default 64)"
    page_rows : int

    @clarg_doc = "Prefix-cache retention cap in pages (default: one full context per stream; -1 = unbounded)"
    prefix : int

    @clarg_doc = "Flat preallocated KV sessions — disables paged serving and the prefix cache"
    flat : bool

    @clarg_doc = "Re-tune this box's dasLLAMA kernels, then relaunch (handled before arg parsing)"
    tune : bool

    @clarg_short = "?"
    @clarg_name = "show-help"
    @clarg_doc = "Show this help and exit"
    help : bool
}

def pick_kv_dtype(s : string) : KVDtype {
    if (s == "f32") {
        return KVDtype.f32
    } elif (s == "q8_0") {
        return KVDtype.q8_0
    } elif (s == "tq4") {
        return KVDtype.tq4
    } elif (!empty(s) && s != "f16") {
        to_log(LOG_WARNING, "dasllama-server: unknown --kv-dtype '{s}', using f16 (valid: f32 | f16 | q8_0 | tq4)\n")
    }
    return KVDtype.f16
}

// fill CLI-unset fields (zero / empty / false — the same sentinels the guards below use) from the
// TOML config, so precedence is defaults < config file < explicit flags
def apply_config(var cfg : ServerArgs) : bool {
    let body = fread(cfg.config)
    if (empty(body)) {
        to_log(LOG_ERROR, "dasllama-server: cannot read config '{cfg.config}'\n")
        return false
    }
    var terr = ""
    var root = read_toml(body, terr)
    if (root == null) {
        to_log(LOG_ERROR, "dasllama-server: bad TOML in '{cfg.config}': {terr}\n")
        return false
    }
    if (empty(cfg.model)) {
        cfg.model = root?["model"] ?? ""
    }
    if (cfg.port <= 0) {
        cfg.port = int(root?["port"] ?? 0l)
    }
    if (empty(cfg.quant)) {
        cfg.quant = root?["quant"] ?? ""
    }
    if (empty(cfg.kv_dtype)) {
        cfg.kv_dtype = root?["kv_dtype"] ?? ""
    }
    if (empty(cfg.asr)) {
        cfg.asr = root?["asr"] ?? ""
    }
    if (empty(cfg.mmproj)) {
        cfg.mmproj = root?["mmproj"] ?? ""
    }
    if (cfg.ctx <= 0) {
        cfg.ctx = int(root?["ctx"] ?? 0l)
    }
    if (cfg.streams <= 0) {
        cfg.streams = int(root?["streams"] ?? 0l)
    }
    if (cfg.chunk <= 0) {
        cfg.chunk = int(root?["chunk"] ?? 0l)
    }
    if (cfg.page_rows <= 0) {
        cfg.page_rows = int(root?["page_rows"] ?? 0l)
    }
    if (cfg.prefix == 0) {
        cfg.prefix = int(root?["prefix"] ?? 0l)
    }
    if (!cfg.flat) {
        cfg.flat = root?["flat"] ?? false
    }
    unsafe {
        delete root
    }
    return true
}

def pick_quant(s : string) : QuantMode {
    if (s == "fp32") {
        return QuantMode.fp32
    } elif (s == "q4") {
        return QuantMode.q4
    } elif (!empty(s) && s != "q8") {
        to_log(LOG_WARNING, "dasllama-server: unknown --quant '{s}', using q8 (valid: fp32 | q8 | q4)\n")
    }
    return QuantMode.q8
}

// missing = "auto": on the first start of an untuned box the injected guard runs the dasLLAMA
// tuner and relaunches; thereafter it serves directly. DAS_TUNE_POLICY=error (or =fallback)
// overrides while developing — no per-start tuning. --tune forces a re-tune + relaunch.
[export, tune_policy(missing = "auto")]
def main : int {
    // inference on the interpreter is uselessly slow — require the JIT (or a jit -exe build)
    if (!jit_enabled() && !is_standalone_exe()) {
        to_log(LOG_ERROR, "dasllama-server: run under the JIT — bin/daslang -jit utils/dasllama-server/main.das -- ...\n")
        return 1
    }
    var r <- parse_args(type<ServerArgs>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<ServerArgs>), "dasllama-server")
        return 1
    }
    var cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<ServerArgs>), "dasllama-server")
        return 0
    }
    if (!empty(cfg.config) && !apply_config(cfg)) {
        return 1
    }
    if (empty(cfg.model)) {
        print("error: no model — pass --model or set model = in --config\n\n")
        print_help(get_command_info(type<ServerArgs>), "dasllama-server")
        return 1
    }

    let port = cfg.port > 0 ? cfg.port : 8080     // non-positive (incl. a stray negative) -> default
    let ctx = cfg.ctx > 0 ? int64(cfg.ctx) : 4096l   // guard: a negative ctx would make seq_len < 0
    let streams = cfg.streams > 0 ? int64(cfg.streams) : 4l
    let chunk = cfg.chunk > 0 ? int64(cfg.chunk) : 64l
    let page_rows = cfg.flat ? 0l : (cfg.page_rows > 0 ? int64(cfg.page_rows) : 64l)
    let prefix = int64(cfg.prefix)   // 0 = auto (run_server sizes it), < 0 = unbounded

    log_tune_status("dasllama-server")
    print("loading {cfg.model} ...\n")
    var m <- load_model(cfg.model, pick_quant(cfg.quant))
    m.config.seq_len = min(m.config.seq_len, ctx)
    set_model(m, base_name(cfg.model))

    if (!empty(cfg.asr)) {
        print("loading ASR {cfg.asr} ...\n")
        var a <- empty(cfg.mmproj) ? load_asr_model(cfg.asr) : load_asr_model(cfg.asr, cfg.mmproj)
        set_asr(a)
    }

    run_server(port, streams, chunk_tokens = chunk, page_rows = page_rows, prefix_groups = prefix,
        kv_dtype = pick_kv_dtype(cfg.kv_dtype))
    return 0
}
