options gen2
options stack = 65536   // dasLLAMA program-root convention (options stack does not unify up from libs)
options _jit_fast_math = true   // ggml-parity FP laxity — same rail as decode_prof / perf

require dasllama/dasllama_transformer   // nolint:STYLE029 — umbrella fires each arch [init] registration
require dasllama/dasllama_math   // setup_dasllama_jobque_ + pin_kernel_backend (engine-level, not re-exported)
require daslib/jobque_boost
require daslib/clargs
require daslib/fio
require math

// Batched-decode throughput: B independent sessions stepped together through eval_batch vs the
// same B streams decoded one after another with forward() (fused chain ON — the honest baseline).
// The weight GEMVs amortize into B-row GEMMs; attention stays per-row by physics, so the win
// shrinks as context deepens and the KV read dominates.
//   bin/daslang -jit modules/dasLLAMA/benchmarks/batch_decode_perf.das -- -m <model.gguf> [-p 64] [-n 64] [-b 8]

[CommandLineArgs]
struct Args {
    @clarg_required
    @clarg_short = "m"
    @clarg_doc = "Model GGUF path"
    model : string

    @clarg_short = "p"
    @clarg_doc = "Prefill depth before the timed decode (default: 64)"
    prefill : int = 64

    @clarg_short = "n"
    @clarg_doc = "Decode steps timed per stream (default: 64)"
    ngen : int = 64

    @clarg_short = "b"
    @clarg_doc = "Largest batch size — sweeps 1,2,4,... up to this (default: 8)"
    bmax : int = 8

    @clarg_short = "q"
    @clarg_doc = "Weight quant mode (default: q8)"
    quant : QuantMode = QuantMode.q8

    @clarg_doc = "KV cache dtype (default: f32)"
    kv : KVDtype = KVDtype.f32

    @clarg_short = "?"
    @clarg_doc = "Show this help and exit"
    help : bool
}

def private build_prompt(n, salt : int64) : array<int64> {
    return <- [for (i in range64(n)); 1000l + ((i * 7l + salt * 131l) % 5000l)]
}

def private greedy_top(lg : array<float>; vocab : int64) : int64 {
    var best = 0l
    var bestv = lg[0]
    for (i in range64(vocab)) {
        if (lg[i] > bestv) {
            bestv = lg[i]
            best = i
        }
    }
    return best
}

// nb fresh sessions, each prefilled to depth p with its own (salted) prompt
def private make_streams(t : Model; kvdt : KVDtype; nb, p : int64) : array<Session> {
    var ss : array<Session>
    ss |> reserve(int(nb))
    for (i in range64(nb)) {
        ss |> emplace <| make_run_state(t.config, kvdt, kvdt)
        var prompt <- build_prompt(p, i)
        eval_(t, ss[i], prompt)
        delete prompt
    }
    return <- ss
}

// today's throughput for nb conversations: each stream decoded to completion, one after another
def private run_sequential(t : Model; kvdt : KVDtype; nb, p, n : int64) : double {
    var ss <- make_streams(t, kvdt, nb, p)
    let vocab = t.config.vocab_size
    let t0 = ref_time_ticks()
    for (i in range64(nb)) {
        var tok = greedy_top(ss[i].logits, vocab)
        for (_st in range64(n)) {
            forward(t, ss[i], tok, ss[i].n_past)
            ss[i].n_past++
            tok = greedy_top(ss[i].logits, vocab)
        }
    }
    let us = get_time_usec(t0)
    delete ss
    return double(nb * n) / (double(us) * 1.0e-6lf)
}

// the same nb streams stepped together, one eval_batch per token
def private run_batched(t : Model; kvdt : KVDtype; nb, p, n : int64) : double {
    var ss <- make_streams(t, kvdt, nb, p)
    let vocab = t.config.vocab_size
    var ws <- create_batch_workspace_(t)
    var sess : array<Session?>
    sess |> reserve(int(nb))
    var cur : array<int64>
    cur |> reserve(int(nb))
    for (i in range64(nb)) {
        unsafe {
            sess |> push(addr(ss[i]))
        }
        cur |> push(greedy_top(ss[i].logits, vocab))
    }
    let t0 = ref_time_ticks()
    for (_st in range64(n)) {
        eval_batch_(t, ws, sess, cur)
        for (i in range64(nb)) {
            cur[i] = greedy_top(ss[i].logits, vocab)
        }
    }
    let us = get_time_usec(t0)
    sess |> clear()   // drop the borrowed handles: delete of array<T?> cascades to the pointees
    unsafe {
        delete ws
        delete sess
    }
    delete cur
    delete ss
    return double(nb * n) / (double(us) * 1.0e-6lf)
}

[export]
def main() {
    if (!jit_enabled()) {
        print("This benchmark is JIT-only — run with: daslang -jit <file>\n")
        return
    }
    var r <- parse_args(type<Args>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<Args>), "batch_decode_perf")
        return
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<Args>), "batch_decode_perf")
        return
    }
    let p = max(int64(cfg.prefill), 8l)
    let n = max(int64(cfg.ngen), 1l)
    let bmax = clamp(int64(cfg.bmax), 1l, 64l)
    if (has_env_variable("DASLLAMA_PIN_BACKEND")) {
        pin_kernel_backend(get_env_variable("DASLLAMA_PIN_BACKEND"))
    }
    print("loading {cfg.model}\n")
    var t <- load_gguf(cfg.model, cfg.quant)
    t.config.seq_len = min(t.config.seq_len, p + n + 8l)   // cap the per-session KV allocation
    let c = t.config
    print("config: dim={c.dim} layers={c.n_layers} heads={c.n_heads}/{c.n_kv_heads} vocab={c.vocab_size} moe={c.moe}\n")
    print("active backend: {active_kernel_backend()}\n")
    print("kv cache dtype: {cfg.kv}\n")
    print("prefill {p}, {n} decode steps per stream\n\n")
    with_job_que() {
        setup_dasllama_jobque_()
        // warm both code paths (JIT + kernel dispatch) before any timed window
        let _w1 = run_sequential(t, cfg.kv, 1l, 8l, 2l)
        let _w2 = run_batched(t, cfg.kv, 2l, 8l, 2l)
        var nb = 1l
        while (nb <= bmax) {
            let seq_tps = run_sequential(t, cfg.kv, nb, p, n)
            let bat_tps = run_batched(t, cfg.kv, nb, p, n)
            let speedup = bat_tps / seq_tps
            let stream_tps = bat_tps / double(nb)
            print("B={nb}: sequential {seq_tps} tok/s | batched {bat_tps} tok/s ({speedup}x) | per-stream {stream_tps} tok/s\n")
            nb *= 2l
        }
    }
    delete t
}
