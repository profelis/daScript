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
require dasllama/dasllama_math  // set_dispatch_worker_limit (engine-level knob, not re-exported)
require llvm/daslib/llvm_tune   // [tune_policy] + tune_status (the injected guard resolves here)
require daslib/clargs
require daslib/toml
require daslib/json_boost
require daslib/module_path
require daslib/logger
require daslib/fio
require math
require strings                 // to_lower / starts_with (pick_quant's file-quant spellings)

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
    @clarg_doc = "Weight serving mode: fp32 | q8 | q4 (default q8); file-format spellings q4_k | q5_k | q6_k | mxfp4 | f16 | bf16 select q8, where those planes serve natively"
    quant : string

    @clarg_doc = "KV cache codec: f32 | f16 | q8_0 | tq4 (default f16)"
    kv_dtype : string

    @clarg_short = "a"
    @clarg_doc = "Path to an ASR model — enables /v1/audio/transcriptions"
    asr : string

    @clarg_doc = "mmproj for the GGUF Qwen3-ASR route (paired with --asr)"
    mmproj : string

    @clarg_doc = "Long-lived asynchronous ASR worker threads (default 1; 2 permits two parallel transcriptions)"
    asr_workers : int

    @clarg_doc = "Context-length cap in tokens (default: the model's trained context_length)"
    ctx : int

    @clarg_doc = "Default reply token budget when a request omits max_tokens (default 256; clamped to ctx per request)"
    max_tokens : int

    @clarg_short = "s"
    @clarg_doc = "Max concurrent generation streams (default 4)"
    streams : int

    @clarg_short = "t"
    @clarg_doc = "Worker-lane cap for the matmul dispatch (default 16; -1 = all cores)"
    threads : int

    @clarg_doc = "Jobque compute dispatch: hybrid (default; LLM team, ASR inline) | team | inline"
    team_dispatch : string

    @clarg_doc = "Worker CPU affinity: 0 = off (default), 1 = ideal-CPU hint, 2 = hard mask (DAS_JOBQUE_AFFINITY env overrides)"
    affinity : int

    @clarg_doc = "Prefill chunk in tokens: decode stalls at most this many per tick (default 64)"
    chunk : int

    @clarg_doc = "KV page size in positions for paged serving (default 64)"
    page_rows : int

    @clarg_doc = "Prefix-cache retention cap in pages (default: one full context per stream; -1 = unbounded)"
    prefix : int

    @clarg_doc = "Flat preallocated KV sessions — disables paged serving and the prefix cache"
    flat : bool

    @clarg_doc = "MTP/NextN self-speculative decode for greedy requests (needs a model with an in-file NextN head, e.g. the -MTP- GGUFs; pays on the dense qwen35 models)"
    mtp : bool

    @clarg_doc = "Re-tune this box's dasLLAMA kernels, then relaunch (handled before arg parsing)"
    tune : bool

    @clarg_short = "?"
    @clarg_name = "show-help"
    @clarg_doc = "Show this help and exit"
    help : bool
}

def pick_kv_dtype(s : string) : KVDtype {
    let l = to_lower(s)   // same normalization as pick_quant — F16/Q8_0/TQ4 spellings accepted
    if (l == "f32") {
        return KVDtype.f32
    } elif (l == "q8_0") {
        return KVDtype.q8_0
    } elif (l == "tq4") {
        return KVDtype.tq4
    } elif (!empty(l) && l != "f16") {
        to_log(LOG_WARNING, "dasllama-server: unknown --kv-dtype '{s}', using f16 (valid: f32 | f16 | q8_0 | tq4)\n")
    }
    return KVDtype.f16
}

def private cli_has_flag(flag : string) : bool {
    var args <- get_cli_arguments()
    let eqform = "{flag}="
    for (a in args) {
        if (a == flag || a |> starts_with(eqform)) {
            delete args
            return true
        }
    }
    delete args
    return false
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
    if (cfg.asr_workers <= 0) {
        cfg.asr_workers = int(root?["asr_workers"] ?? 0l)
    }
    if (cfg.ctx <= 0) {
        cfg.ctx = int(root?["ctx"] ?? 0l)
    }
    if (cfg.max_tokens <= 0) {
        cfg.max_tokens = int(root?["max_tokens"] ?? 0l)
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
    if (cfg.threads == 0 && !cli_has_flag("--threads")) {
        cfg.threads = int(root?["threads"] ?? 0l)
    }
    if (empty(cfg.team_dispatch)) {
        cfg.team_dispatch = root?["team_dispatch"] ?? ""
    }
    if (cfg.affinity == 0 && !cli_has_flag("--affinity")) {
        cfg.affinity = int(root?["affinity"] ?? 0l)
    }
    // --prefix is the one flag where 0 is a meaningful EXPLICIT value (auto-sizing), so the
    // zero-sentinel isn't enough: only fill from TOML when the flag is truly absent from argv
    if (cfg.prefix == 0 && !cli_has_flag("--prefix")) {
        cfg.prefix = int(root?["prefix"] ?? 0l)
    }
    if (!cfg.flat) {
        cfg.flat = root?["flat"] ?? false
    }
    if (!cfg.mtp) {
        cfg.mtp = root?["mtp"] ?? false
    }
    unsafe {
        delete root
    }
    return true
}

// Besides the serving modes (fp32 | q8 | q4), the FILE formats the gguf loader reads are
// first-class spellings too: q4_k / q5_k / q6_k (any case, _M/_S suffixes fine), mxfp4,
// f16 / bf16, q8_0 — all of those serve under QuantMode.q8 (K-quant and mx4 planes run
// NATIVELY on the kq tier). "q4" stays the legacy q4_0 requant tier — do not use it for
// K-quant files (per-row fallback paths, the 14x prefill stall).
def pick_quant(s : string) : QuantMode {
    let l = to_lower(s)
    if (l == "fp32" || l == "f32") {
        return QuantMode.fp32
    } elif (l == "q4" || l == "q4_0") {
        return QuantMode.q4
    } elif (!empty(l) && l != "q8" && l != "q8_0" && l != "mxfp4" && l != "f16" && l != "bf16"
            && !(starts_with(l, "q4_k") || starts_with(l, "q5_k") || starts_with(l, "q6_k"))) {
        to_log(LOG_WARNING, "dasllama-server: unknown --quant '{s}', using q8 (valid: fp32 | q8 | q4 | q4_k | q5_k | q6_k | mxfp4 | f16 | bf16)\n")
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
    if (empty(cfg.config)) {
        // dictation-bot convention: a same-name config next to the program (or in cwd) loads
        // automatically, so a release bundle configures itself with no flags at all
        let here = "dasllama-server.toml"
        let beside = path_join(get_this_module_dir(), "dasllama-server.toml")
        if (stat(here).is_valid) {
            cfg.config = here
        } elif (stat(beside).is_valid) {
            cfg.config = beside
        }
        if (!empty(cfg.config)) {
            print("using config {cfg.config}\n")
        }
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
    let ctx = cfg.ctx > 0 ? int64(cfg.ctx) : 0l   // 0 = keep the model's trained context_length
    let streams = cfg.streams > 0 ? int64(cfg.streams) : 4l
    let chunk = cfg.chunk > 0 ? int64(cfg.chunk) : 64l
    let page_rows = cfg.flat ? 0l : (cfg.page_rows > 0 ? int64(cfg.page_rows) : 64l)
    let prefix = int64(cfg.prefix)   // 0 = auto (run_server sizes it), < 0 = unbounded
    let dispatch_mode = to_lower(cfg.team_dispatch)
    if (!empty(dispatch_mode) && dispatch_mode != "hybrid"
        && dispatch_mode != "team" && dispatch_mode != "inline") {
        print("error: --team-dispatch must be 'hybrid', 'team', or 'inline'\n")
        return 2
    }
    let team_dispatch = dispatch_mode != "inline"
    let asr_team_dispatch = dispatch_mode == "team"
    // matmul dispatch lane cap: LLM decode saturates memory bandwidth long before big core
    // counts, and an uncapped dispatch fights every other process on the box. -1 = all cores.
    let threads = cfg.threads > 0 ? cfg.threads : (cfg.threads < 0 ? 0 : 16)
    set_dispatch_worker_limit(threads)
    // worker CPU affinity — must land before the jobque exists (applied at worker spawn)
    set_jobque_affinity(cfg.affinity)
    let lanes_desc = threads > 0 ? "{threads}" : "all"
    print("dispatch: {lanes_desc} worker lanes, affinity {cfg.affinity}\n")
    // tee every to_log/print to logs/dasllama-server.log (timestamped ndjson) AND the console
    logger_init_tee("dasllama-server")
    to_log(LOG_INFO, "dasllama-server: logging to {get_das_root()}/logs/dasllama-server.log\n")

    log_tune_status("dasllama-server")
    print("loading {cfg.model} ...\n")
    var m <- load_model(cfg.model, pick_quant(cfg.quant))
    if (ctx > 0l) {
        m.config.seq_len = min(m.config.seq_len, ctx)
    }
    let ctx_note = ctx > 0l ? "" : " (model default)"
    to_log(LOG_INFO, "dasllama-server: ctx {m.config.seq_len}{ctx_note}\n")
    set_model(m, base_name(cfg.model))
    set_default_max_tokens(cfg.max_tokens > 0 ? int64(cfg.max_tokens) : 256l)

    if (!empty(cfg.asr)) {
        configure_asr_workers(cfg.asr, cfg.mmproj, cfg.asr_workers > 0 ? cfg.asr_workers : 1)
    }

    run_server(port, streams, chunk_tokens = chunk, page_rows = page_rows, prefix_groups = prefix,
        kv_dtype = pick_kv_dtype(cfg.kv_dtype), team_dispatch = team_dispatch,
        asr_team_dispatch = asr_team_dispatch, mtp = cfg.mtp)
    return 0
}
