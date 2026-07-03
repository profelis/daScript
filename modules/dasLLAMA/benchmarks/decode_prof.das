options gen2
options _jit_fast_math = true   // ggml-parity FP laxity (non-bit-exact, ~+10%); tests stay bit-exact

require dasllama/dasllama_transformer   // nolint:STYLE029 — umbrella fires each arch [init] registration; requiring dasllama_common directly would drop them
require dasllama/dasllama_math   // setup_dasllama_jobque_ (the engine-standard jobque config)
require daslib/jobque_boost
require daslib/clargs
require math

// Per-op DECODE profile: prefill a synthetic prompt to depth P, then greedily decode N tokens with
// the forward-section profiler windowed to just the decode loop. Prints the measured per-bucket
// time split next to a config-derived per-token weight/KV traffic table, so the time share of each
// section can be checked against its theoretical bandwidth share (the traffic table is what says
// whether a weight-format change — e.g. native MXFP4 experts — can pay).
//   bin/daslang -jit modules/dasLLAMA/benchmarks/decode_prof.das -- -m <model.gguf> [-p 256] [-n 64]

[CommandLineArgs]
struct Args {
    @clarg_required
    @clarg_short = "m"
    @clarg_doc = "Model GGUF path"
    model : string

    @clarg_short = "p"
    @clarg_doc = "Prefill depth before the decode window (default: 8)"
    prefill : int = 8

    @clarg_doc = "Second, deeper window in the same process — 0 to skip (default: 512)"
    prefill2 : int = 512

    @clarg_short = "n"
    @clarg_doc = "Decode tokens profiled (default: 64)"
    ngen : int = 64

    @clarg_short = "q"
    @clarg_doc = "Weight quant mode (default: q8)"
    quant : QuantMode = QuantMode.q8

    @clarg_doc = "Override the decode-attention threading threshold (work units; 0 = always thread, -1 = keep default)"
    attn_par : int = -1

    @clarg_doc = "Override the quantized-matmul oversplit factor (chunks per hw job; -1 = keep default)"
    chunks : int = -1

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

// Bytes read per weight for a quant mode (quants + fp32 block scales at 1 per 32).
def private wbytes(q : QuantMode) : double {
    if (q == QuantMode.q8) {
        return 1.0lf + 4.0lf / 32.0lf
    }
    if (q == QuantMode.q4) {
        return 0.5lf + 4.0lf / 32.0lf
    }
    return 4.0lf
}

def private mb(v : double) : double => v / (1024.0lf * 1024.0lf)

// Config-derived weight + KV bytes READ per decoded token, split by section, evaluated at context
// depth `pos` (attention KV traffic grows with position; everything else is position-free).
def private print_traffic_table(t : Model; pos : int64) {
    let c = t.config
    let wb = wbytes(t.quant)
    let dim = c.dim
    var attn = 0.0lf
    var kv_read = 0.0lf
    for (l in range64(c.n_layers)) {
        let qd = layer_qd(c, l)
        let kvd = layer_kv_dim(c, l)
        let wv = t.wv_offs[l] >= 0l ? double(dim * kvd) : 0.0lf
        attn += (double(dim * qd) + double(dim * kvd) + wv + double(qd * dim)) * wb
        let cnt = layer_is_sliding(c, l) ? min(pos, c.sliding_window) : pos
        kv_read += double(cnt * kvd) * 2.0lf * 4.0lf
    }
    var ffn = 0.0lf
    var moe = 0.0lf
    var router = 0.0lf
    var shexp = 0.0lf
    if (c.moe) {
        router = double(c.n_layers * dim * c.n_expert) * 4.0lf   // router weights stay fp32
        // native-MXFP4 experts read 17 bytes per 32 weights (nibbles + E8M0); else the active quant
        let ewb = t.experts_mx4 ? 17.0lf / 32.0lf : wb
        moe = double(c.n_layers * c.n_expert_used * 3l * dim * c.n_ff_exp) * ewb
        if (c.n_ff_shexp > 0l) {
            shexp = double(c.n_layers * 3l * dim * c.n_ff_shexp) * wb
        }
    } else {
        ffn = double(c.n_layers * 3l * dim * c.hidden_dim) * wb
    }
    let cls_fp32 = c.shared_weights && !t.cls_q8
    let cls = double(dim * c.vocab_size) * (cls_fp32 ? 4.0lf : wb)
    let embed = double(dim) * (t.cls_q8 ? wbytes(QuantMode.q8) : 4.0lf)
    let total = attn + kv_read + ffn + moe + router + shexp + cls + embed
    print("--- per-token traffic at ctx depth {pos} (config-derived, MB read/token) ---\n")
    print("  attn weights: {mb(attn)} ({100.0lf * attn / total}%)\n")
    print("  kv cache:     {mb(kv_read)} ({100.0lf * kv_read / total}%)\n")
    if (c.moe) {
        print("  moe experts:  {mb(moe)} ({100.0lf * moe / total}%)\n")
        print("  moe router:   {mb(router)} ({100.0lf * router / total}%)\n")
        if (shexp > 0.0lf) {
            print("  moe shexp:    {mb(shexp)} ({100.0lf * shexp / total}%)\n")
        }
    } else {
        print("  ffn weights:  {mb(ffn)} ({100.0lf * ffn / total}%)\n")
    }
    print("  classifier:   {mb(cls)} ({100.0lf * cls / total}%)\n")
    print("  TOTAL:        {mb(total)} MB/token -> at 100 GB/s ~= {102400.0lf / mb(total)} tok/s ceiling\n")
}

// One measured window: greedily decode n tokens from context depth p (the cache is already filled
// to p), with the profiler reset to cover exactly this loop. Returns the chained last token.
def private profile_window(t : Model; var s : Session; p, n : int64; tok0 : int64) : int64 {
    var tok = tok0
    forward_profile_reset()
    let t0 = ref_time_ticks()
    for (i in range64(n)) {
        forward(t, s, tok, p + i)
        tok = greedy_top(s, t.config.vocab_size)
    }
    let us = get_time_usec(t0)
    let tps = double(n) / (double(us) * 1.0e-6lf)
    print("decode: {n} tokens from ctx {p} in {us}us = {tps} tok/s\n\n")
    forward_profile_report()
    print("\n")
    print_traffic_table(t, p + n / 2l)
    return tok
}

def private run_profile(var t : Model; p, n, p2 : int64) {
    let c = t.config
    var s <- make_run_state(c)
    with_job_que() {
        setup_dasllama_jobque_()   // pooled forks + batched dispatch + spin window + join poll (the engine standard)
        // warmup — JIT both paths (the real prefill below overwrites these cache positions)
        let warm <- build_prompt(8l)
        for (wp in range64(8l)) {
            forward(t, s, warm[wp], wp)
        }
        forward_prefill(t, s, warm, 8l, 0l)
        // prefill to depth p, then window the profiler to just the decode loop
        let prompt <- build_prompt(p)
        forward_prefill(t, s, prompt, p, 0l)
        var tok = greedy_top(s, c.vocab_size)
        tok = profile_window(t, s, p, n, tok)
        if (p2 > p + n) {   // second window, deeper into the context, off the same load
            let fill = p2 - (p + n)
            let more <- build_prompt(fill)
            forward_prefill(t, s, more, fill, p + n)
            tok = greedy_top(s, c.vocab_size)
            print("\n")
            profile_window(t, s, p2, n, tok)
        }
    }
}

[export]
def main() {
    if (!jit_enabled()) {
        print("This profiler is JIT-only — run with: daslang -jit <file>\n")
        return
    }
    var r <- parse_args(type<Args>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<Args>), "decode_prof")
        return
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<Args>), "decode_prof")
        return
    }
    let p = max(int64(cfg.prefill), 8l)
    let n = max(int64(cfg.ngen), 1l)
    let p2 = int64(cfg.prefill2)
    print("loading {cfg.model}\n")
    var t <- load_gguf(cfg.model, cfg.quant)
    let ctx_cap = max(2048l, max(p, p2) + n + 8l)
    t.config.seq_len = min(t.config.seq_len, ctx_cap)   // cap the KV allocation
    let c = t.config
    print("config: dim={c.dim} layers={c.n_layers} heads={c.n_heads}/{c.n_kv_heads} vocab={c.vocab_size} moe={c.moe}\n")
    if (cfg.attn_par >= 0) {
        set_decode_attn_par_threshold(int64(cfg.attn_par))
        print("decode_attn_par_threshold override: {cfg.attn_par}\n")
    }
    if (cfg.chunks >= 1) {
        set_q8_batch_chunks_per_job(cfg.chunks)
        print("q8_batch_chunks_per_job override: {cfg.chunks}\n")
    }
    run_profile(t, p, n, p2)
}
