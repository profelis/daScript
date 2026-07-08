options gen2
options indenting = 4

// Batch reference-baseline establisher for the dasLLAMA profiling suite. Runs the REFERENCE tools once
// per box (llama.cpp llama-bench for LLMs here; the ASR CLIs land in a later phase) and writes their
// tok/s to a machine-readable per-box baseline that gen_profile then merges with the freshly-measured
// das side. This exists so establishing on a new box is one command, never a manual llama-bench sweep.
//
// Parsec MUST be off — this runs the reference tool, which is a measurement.
//   bin/daslang modules/dasLLAMA/performance/establish_baselines.das -- -t small

require profile_common
require daslib/clargs
require strings
require daslib/fio

[CommandLineArgs]
struct Args {
    @clarg_short = "t"
    @clarg_doc = "Tier: small | large | all (default small)"
    tier : string = "small"

    @clarg_doc = "Threads (default 8 — the perf-core count on both target boxes)"
    threads : int = 8

    @clarg_doc = "Prompt tokens for the prefill test (default 512)"
    nprompt : int = 512

    @clarg_doc = "Generated tokens for the emission test (default 128)"
    ngen : int = 128

    @clarg_short = "o"
    @clarg_doc = "Only models whose display name contains this substring (default: whole tier)"
    only : string = ""

    @clarg_short = "?"
    @clarg_doc = "Show this help and exit"
    help : bool
}

// llama-bench binary; override with LLAMA_BENCH. Default is the clean CPU build (upstream ebd048f, no
// Accelerate/AMX/BLAS/Metal, no op-profile instrumentation) — the fair kernel-vs-kernel reference.
def llama_bench_bin() : string {
    let env = get_env_variable("LLAMA_BENCH")
    return empty(env) ? "/Users/borisbatkin/Work/llama.cpp-clean/build/bin/llama-bench" : env
}

// The subset of llama-bench's `-o json` result object we consume. sscan_json ignores the rest.
struct LlamaBenchRow {
    n_prompt : int
    n_gen : int
    avg_ts : double
    model_n_params : int64
    build_commit : string
}

// Run llama-bench for one model and fold its two result rows (n_gen=0 prefill, n_prompt=0 decode) into
// an LlmBaseline. prefill/emission stay -1 on a run or parse failure.
def bench_one(display, path : string; threads, nprompt, ngen : int) : LlmBaseline {
    let cmd = "{llama_bench_bin()} -m {path} -ngl 0 -t {threads} -p {nprompt} -n {ngen} -o json"
    var out = ""
    unsafe {
        popen(cmd) $(f) {
            out = fread_to_eof(f)
        }
    }
    var rows : array<LlamaBenchRow>
    if (!sscan_json(out, rows)) {
        return LlmBaseline(model = display, prefill_tok_s = -1.0lf, emission_tok_s = -1.0lf, lcpp_commit = "", n_params = 0l)
    }
    var prefill = -1.0lf
    var emission = -1.0lf
    var commit = ""
    var nparams = 0l
    for (r in rows) {
        commit = r.build_commit
        nparams = r.model_n_params
        if (r.n_gen == 0 && r.n_prompt > 0) {
            prefill = r.avg_ts
        }
        if (r.n_prompt == 0 && r.n_gen > 0) {
            emission = r.avg_ts
        }
    }
    return LlmBaseline(model = display, prefill_tok_s = prefill, emission_tok_s = emission, lcpp_commit = commit, n_params = nparams)
}

[export]
def main() {
    var r <- parse_args(type<Args>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<Args>), "establish_baselines")
        return
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<Args>), "establish_baselines")
        return
    }
    let tier = parse_tier(cfg.tier)
    print("establishing LLM baselines: box={box_name()} tier={cfg.tier} threads={cfg.threads}\n")
    print("bench: {llama_bench_bin()}\n")
    print("NOTE: this runs llama.cpp llama-bench (a measurement) — Parsec must be off.\n\n")
    var rows : array<LlmBaseline>
    for (m in llm_catalog()) {
        if (!empty(cfg.only) && find(m.display, cfg.only) < 0) {
            continue
        }
        var sz = 0ul
        if (!model_selected(m, tier, sz)) {
            continue
        }
        print("{m.display} ({int(sz / (1024ul * 1024ul))} MB) ...\n")
        let b = bench_one(m.display, model_path(m), cfg.threads, cfg.nprompt, cfg.ngen)
        print("  prefill {b.prefill_tok_s} tok/s  emission {b.emission_tok_s} tok/s  (lcpp {b.lcpp_commit})\n")
        rows |> push(b)
    }
    write_llm_baselines(rows)
    print("\nwrote {length(rows)} baseline row(s) -> {baseline_llm_path()}\n")
}
