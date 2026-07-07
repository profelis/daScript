options gen2
options stack = 262144   // the forward chain runs deep

// ask — a one-shot dasLLAMA completion CLI, a sibling of dasllama-server.
//
//   bin/daslang -jit utils/dasllama-server/ask.das -- --model <model.gguf> --prompt "..." [--max-tokens 256]
//
// It shares this box's tune winners with the server and every other dasLLAMA app: NO scope
// declaration of its own — requiring dasLLAMA pulls in the [tune_scope], so ask reads the same
// <das_root>/dasllama.tune.json. The policy is "auto" (like the server): the first run on an
// untuned box tunes and relaunches, then completes; --tune forces a re-tune. Tune once (any of
// the three tools), and every sibling is tuned.

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

[export, tune_policy(missing = "auto")]
def main : int {
    // inference on the interpreter is uselessly slow — require the JIT (or a jit -exe build)
    if (!jit_enabled() && !is_standalone_exe()) {
        to_log(LOG_ERROR, "ask: run under the JIT — bin/daslang -jit utils/dasllama-server/ask.das -- ...\n")
        return 1
    }
    var r <- parse_args(type<AskArgs>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<AskArgs>), "ask")
        return 1
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<AskArgs>), "ask")
        return 0
    }

    log_tune_status("ask")

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
        // throughput: prompt/gen token counts, time-to-first-token, prefill and decode t/s
        let st = stats(s)
        print("\n[prompt {st.n_prompt} tok | gen {st.n_gen} tok | ttft {int(st.ttft_s * 1000.0lf)}ms | ")
        print("prefill {int(st.prefill_tps)} t/s | gen {int(st.gen_tps)} t/s]\n")
    }
    return 0
}
