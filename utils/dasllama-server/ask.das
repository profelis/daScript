options gen2
options stack = 262144   // the forward chain runs deep

// ask — a one-shot dasLLAMA completion CLI, a sibling of dasllama-server.
//
//   bin/daslang -jit utils/dasllama-server/ask.das -- --model <model.gguf> --prompt "..." [--max-tokens 256]
//
// It shares this box's tune winners with the server and every other dasLLAMA app: NO tune
// declaration of its own — requiring dasLLAMA pulls in the [tune_scope], so ask reads the same
// <das_root>/dasllama.tune.json. The policy here is "error" (the dev flavor): an untuned box
// refuses to run and prints the exact tuner command, rather than tuning inline — a batch tool
// shouldn't surprise a script with a multi-minute tune. Tune once (e.g. start the server, or
// run ask with --tune), and every sibling is tuned.

require dasllama/dasllama       // load_model / generate / the shared [tune_scope]
require llvm/daslib/llvm_tune   // [tune_policy] + tune_status
require daslib/jobque_boost
require daslib/clargs
require daslib/fio

[CommandLineArgs]
struct AskArgs {
    @clarg_required
    @clarg_short = "m"
    @clarg_doc = "Path to the GGUF model"
    model : string

    @clarg_required
    @clarg_short = "p"
    @clarg_doc = "The prompt to complete"
    prompt : string

    @clarg_short = "n"
    @clarg_name = "max-tokens"
    @clarg_doc = "Max tokens to generate (default 256)"
    max_tokens : int

    @clarg_short = "t"
    @clarg_doc = "Sampling temperature, 0 = greedy (default 0)"
    temp : float

    @clarg_doc = "Weight quantization: fp32 | q8 | q4 (default q8)"
    quant : string

    @clarg_doc = "Re-tune this box's dasLLAMA kernels, then relaunch"
    tune : bool

    @clarg_short = "?"
    @clarg_name = "show-help"
    @clarg_doc = "Show this help and exit"
    help : bool
}

def pick_quant(s : string) : QuantMode {
    if (s == "fp32") return QuantMode.fp32
    if (s == "q4") return QuantMode.q4
    return QuantMode.q8
}

[export, tune_policy(missing = "error")]
def main {
    var r <- parse_args(type<AskArgs>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<AskArgs>), "ask")
        return
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<AskArgs>), "ask")
        return
    }

    let max_new = cfg.max_tokens > 0 ? int64(cfg.max_tokens) : 256l

    var m <- load_model(cfg.model, pick_quant(cfg.quant))
    let toks <- encode(m, cfg.prompt, true, false)
    var params = SamplingParams()
    params.temp = cfg.temp

    with_job_que() {
        setup_dasllama_jobque()
        var s = create_session(m)
        generate(m, s, toks, params, max_new) $(_id, piece) {
            fprint(fstdout(), piece)
            fflush(fstdout())
            return true
        }
    }
    print("\n")
}
