options gen2
options stack = 262144   // the forward chain runs deep under the HTTP tick + C++->das handler bridge

// dasllama-server — an OpenAI-compatible HTTP server over the dasLLAMA facade.
//
//   bin/daslang -jit utils/dasllama-server/main.das -- --model <model.gguf> [--port 8080] [--quant q8]
//                                                       [--asr <asr.bin>] [--mmproj <mmproj.gguf>] [--tune]
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
require daslib/fio
require math

[CommandLineArgs]
struct ServerArgs {
    @clarg_required
    @clarg_short = "m"
    @clarg_doc = "Path to the GGUF model to serve"
    model : string

    @clarg_short = "p"
    @clarg_doc = "Port to listen on (default 8080)"
    port : int

    @clarg_short = "q"
    @clarg_doc = "Weight quantization: fp32 | q8 | q4 (default q8)"
    quant : string

    @clarg_short = "a"
    @clarg_doc = "Path to an ASR model — enables /v1/audio/transcriptions"
    asr : string

    @clarg_doc = "mmproj for the GGUF Qwen3-ASR route (paired with --asr)"
    mmproj : string

    @clarg_doc = "Context-length cap in tokens (default 4096)"
    ctx : int

    @clarg_doc = "Re-tune this box's dasLLAMA kernels, then relaunch (handled before arg parsing)"
    tune : bool

    @clarg_short = "?"
    @clarg_name = "show-help"
    @clarg_doc = "Show this help and exit"
    help : bool
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
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<ServerArgs>), "dasllama-server")
        return 0
    }

    let port = cfg.port > 0 ? cfg.port : 8080     // non-positive (incl. a stray negative) -> default
    let ctx = cfg.ctx > 0 ? int64(cfg.ctx) : 4096l   // guard: a negative ctx would make seq_len < 0

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

    run_server(port)
    return 0
}
