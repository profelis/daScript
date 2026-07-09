options gen2
options stack = 65536   // the forward/prefill chain + generated kernels need more than the 16K default on arm64
options _jit_fast_math = true   // ggml-parity FP laxity (non-bit-exact, ~+10%); the profile is a speed measurement

// The das-side half of the profiling suite: for each tier-selected model it measures prefill (one
// batched forward_prefill) and emission (a greedy decode loop) tok/s under the tuned per-box runtime,
// pulls the matching llama.cpp reference from the committed baseline TSV (never re-run here — see
// establish_baselines.das), and MERGES the row into the persistent per-box profile JSON. Partial runs
// (small now, large later) merge into the same file. JIT-only, Parsec off.
//   bin/daslang -jit modules/dasLLAMA/performance/gen_profile.das -- -t small

require dasllama/dasllama_transformer   // nolint:STYLE029 — umbrella fires each arch [init] registration; requiring dasllama_common directly would drop them
require dasllama/dasllama_math          // setup_dasllama_jobque_ + apply_box_profile_runtime knobs (engine-level, not re-exported)
require dasllama/dasllama_tune          // box_profile_path (the applied per-box manifest, recorded in the platform block)
require daslib/jobque_boost
require profile_common
require daslib/clargs
require daslib/fio
require math

[CommandLineArgs]
struct Args {
    @clarg_short = "t"
    @clarg_doc = "Tier: small | large | all (default small)"
    tier : string = "small"

    @clarg_doc = "Threads recorded in the platform block (default 8 — the perf-core count on both boxes)"
    threads : int = 8

    @clarg_doc = "Parsec was off for this run — recorded in the platform block (default true)"
    parsec_off : bool = true

    @clarg_short = "o"
    @clarg_doc = "Only models whose display name contains this substring (default: whole tier)"
    only : string = ""

    @clarg_short = "?"
    @clarg_doc = "Show this help and exit"
    help : bool
}

def private build_prompt(n : int64) : array<int64> {
    return <- [for (i in range64(n)); 1000l + (i % 5000l)]
}

def private greedy_top(s : Session; vocab : int64) : int64 {
    var best = 0l
    var bestv = s.logits[0]
    for (i in range64(vocab)) {
        if (s.logits[i] > bestv) {
            bestv = s.logits[i]
            best = i
        }
    }
    return best
}

// Measure prefill (one batched forward over `prefill_ctx` synthetic tokens) and emission (a greedy
// decode of `emission_ctx` tokens from position 0) tok/s for one loaded model, both from a warmed
// JIT + live jobque. Token content doesn't affect speed, so synthetic ids are fine.
def private measure(var t : Model; prefill_ctx, emission_ctx : int) : tuple<prefill : double; emission : double> {
    var s <- make_run_state(t.config)
    var pf = 0.0lf
    var em = 0.0lf
    with_job_que() {
        setup_dasllama_jobque_()
        var warm <- build_prompt(8l)
        for (p in range64(8l)) {
            forward(t, s, warm[p], p)
        }
        forward_prefill(t, s, warm, 8l, 0l)
        delete warm
        // PREFILL — one batched forward_prefill (matches llama-bench pp<N>)
        let np = int64(prefill_ctx)
        var prompt <- build_prompt(np)
        let t0 = ref_time_ticks()
        forward_prefill(t, s, prompt, np, 0l)
        let us_pf = get_time_usec(t0)
        pf = double(np) / (double(us_pf) * 1.0e-6lf)
        delete prompt
        // EMISSION — greedy decode from position 0 (matches llama-bench tg<N>)
        let ng = int64(emission_ctx)
        var tok = 1l
        let t1 = ref_time_ticks()
        for (i in range64(ng)) {
            forward(t, s, tok, i)
            tok = greedy_top(s, t.config.vocab_size)
        }
        let us_em = get_time_usec(t1)
        em = double(ng) / (double(us_em) * 1.0e-6lf)
    }
    delete s   // free the run-state (KV cache) — measure() runs once per model
    return (prefill = pf, emission = em)
}

// The applied per-box profile filename (or "default" when none is on disk) for the platform block.
def private box_profile_tag() : string {
    let bp = box_profile_path()
    return stat(bp).is_valid ? base_name(bp) : "default"
}

// Pull the reference tok/s for `display` from the established baselines. Non-positive (unmeasured)
// stays 0.0 — @optional in the JSON means the reference cell is then simply absent.
def private ref_for(baselines : array<LlmBaseline>; display : string; var prefill, emission : double&) {
    prefill = 0.0lf
    emission = 0.0lf
    for (b in baselines) {
        if (b.model == display) {
            prefill = max(b.prefill_tok_s, 0.0lf)    // unmeasured (-1) collapses to 0 => absent in JSON
            emission = max(b.emission_tok_s, 0.0lf)
            return
        }
    }
}

[export]
def main() {
    if (!jit_enabled()) {
        print("gen_profile is JIT-only — run with: daslang -jit <file>\n")
        return
    }
    var r <- parse_args(type<Args>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<Args>), "gen_profile")
        return
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<Args>), "gen_profile")
        return
    }
    let tier = parse_tier(cfg.tier)

    // reference baselines (lcpp tok/s + commit) — established once per box, never re-run here
    let baselines <- read_llm_baselines()
    var lcpp_commit = ""
    for (b in baselines) {
        if (!empty(b.lcpp_commit)) {
            lcpp_commit = b.lcpp_commit
            break
        }
    }

    // load-or-start the persistent per-box profile (the merge target)
    var prof : LlmProfile
    read_llm_profile(prof)
    let date = format_time(get_clock(), "%Y-%m-%d")   // portable (no shell) — Windows cmd `date` prompts and hangs
    prof.platform = gather_platform(cfg.threads, lcpp_commit, date, box_profile_tag(), cfg.parsec_off)

    apply_box_profile_runtime()   // the tuned per-box stack (backend pin + dispatch knobs)

    logger_set_name(prof_log_name())
    // The das side runs on the jobque, NOT llama-bench's -t. On a many-core box you MUST set
    // DAS_JOBQUE_THREADS=<threads> or das dispatches wide (~cores lanes) and the comparison is invalid.
    // Probe the ACTUAL lane count, record it (not just the advisory flag), and warn hard on a mismatch.
    var lanes = 0
    with_job_que() {
        setup_dasllama_jobque_()
        lanes = get_dispatch_lanes()
    }
    prof.platform.threads = lanes
    logger_info("profile.llm.gen", "run start", JV({"box" => JV(box_name()), "tier" => JV(cfg.tier),
        "requested_threads" => JV(cfg.threads), "dispatch_lanes" => JV(lanes), "lcpp" => JV(lcpp_commit)}))
    if (lanes != cfg.threads) {
        logger_warning("profile.llm.gen", "dispatch lanes != requested threads — set DAS_JOBQUE_THREADS",
            JV({"dispatch_lanes" => JV(lanes), "requested_threads" => JV(cfg.threads)}))
        print("WARNING: das dispatch lanes = {lanes}, requested {cfg.threads}. Set DAS_JOBQUE_THREADS={cfg.threads} to match.\n")
    }
    print("gen_profile: box={box_name()} tier={cfg.tier} threads={cfg.threads} das_lanes={lanes}\n")
    print("log: {logger_get_path()}  (tail for live, timestamped progress)\n")
    print("baselines: {length(baselines)} row(s) from {baseline_llm_path()} (lcpp {lcpp_commit})\n\n")
    for (m in llm_catalog()) {
        if (!empty(cfg.only) && find(m.display, cfg.only) < 0) {
            continue
        }
        var sz = 0ul
        if (!model_selected(m, tier, sz)) {
            continue
        }
        logger_info("profile.llm.gen", "model start", JV({"model" => JV(m.display), "size_mb" => JV(int(sz / (1024ul * 1024ul)))}))
        let t0 = ref_time_ticks()
        var t <- load_gguf(model_path(m), m.quant)
        t.config.seq_len = min(t.config.seq_len, 2048l)   // cap KV; both phases fit under this
        let meas = measure(t, m.prefill_ctx, m.emission_ctx)
        let ms = double(get_time_usec(t0)) / 1000.0lf
        var pf_ref = 0.0lf
        var em_ref = 0.0lf
        ref_for(baselines, m.display, pf_ref, em_ref)
        let rec = LlmRec(
            model = m.display,
            arch = t.arch,
            quant = quant_str(m.quant),
            active_b = active_params_b(t),
            prefill = PhaseRec(context = m.prefill_ctx, das_tok_s = meas.prefill, llama_cpp_tok_s = pf_ref),
            emission = PhaseRec(context = m.emission_ctx, das_tok_s = meas.emission, llama_cpp_tok_s = em_ref))
        upsert_llm(prof.tests, rec)
        write_llm_profile(prof)   // persist now — a crash on a later model never costs this one
        logger_info("profile.llm.gen", "model done", JV({"model" => JV(m.display), "elapsed_ms" => JV(ms),
            "das_prefill_tok_s" => JV(meas.prefill), "das_emission_tok_s" => JV(meas.emission),
            "lcpp_prefill_tok_s" => JV(pf_ref), "lcpp_emission_tok_s" => JV(em_ref)}))
        delete t   // free the model's weights before the next one (else all models stay resident)
    }
    logger_info("profile.llm.gen", "run done", JV({"profiled" => JV(length(prof.tests)), "path" => JV(profile_llm_path())}))
    print("profiled {length(prof.tests)} model row(s) -> {profile_llm_path()}\n")
}
