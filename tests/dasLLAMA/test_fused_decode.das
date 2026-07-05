options gen2
options persistent_heap   // + explicit deletes below (see test_forward.das)
options stack = 65536   // dastest harness + forward chain + by-value Session (test_forward does the same)

require dastest/testing_boost public
require dasllama/dasllama_transformer   // nolint:STYLE029 — umbrella fires each arch [init] registration; load_checkpoint resolves "llama" from the registry
require daslib/jobque_boost
require daslib/fio
require dasllama/dasllama_math  // setup_dasllama_jobque_ + target_chunk_work + fused knob

// Fused decode chains (team_parallel_stages: qkv→attn→wo and w1/w3→w2 as ONE dispatch each) vs
// the per-op dispatch path: bit-exact equivalence. The fused path claims bit-identical arithmetic
// — same backend row dots, same per-head norm/rope/store order, same act/quant/add per element —
// so greedy ids AND final logits must match EXACTLY, not within tolerance. stories15M sits below
// the fused size gate, so both sides run with target_chunk_work forced to 1 (identical
// dispatch decisions per-op path included).

def private llama2c_dir() : string {
    let env = get_env_variable("DASLLAMA_LLAMA2C_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama2.c" : env
}
let MODEL_PATH = path_join(llama2c_dir(), "stories15M.bin")
// override the machine-local model root with DASLLAMA_MODELS_DIR (same rail as test_parity)
def private models_dir() : string {
    let env = get_env_variable("DASLLAMA_MODELS_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama.cpp/models/" : env
}
let N_STEPS = 24

def private argmax_of(s : Session; vocab : int64) : int64 {
    var best = 0l
    for (i in range64(1l, vocab)) {
        if (s.logits[i] > s.logits[best]) {
            best = i
        }
    }
    return best
}

def private greedy_ids(tr : Model; var s : Session; var ids : array<int64>; var logits : array<float>) {
    ids |> reserve(N_STEPS)
    var token = 1l   // BOS
    var pos = 0l
    for (_i in range(N_STEPS)) {
        forward(tr, s, token, pos)
        pos++
        token = argmax_of(s, tr.config.vocab_size)
        ids |> push(token)
    }
    logits := s.logits
}

[test]
def test_fused_decode_bit_exact(t : T?) {
    t |> run("fused stage chains == per-op dispatches, ids + logits bit-exact (needs stories15M.bin)") @(t : T?) {
        if (!jit_enabled()) {
            t |> success(true, "skipped: interpreted (dasLLAMA model tests are JIT-only)")
            return
        }
        if (!stat(MODEL_PATH).is_valid) {
            t |> success(true, "skipped: stories15M.bin not present")
            return
        }
        var tr <- load_checkpoint(MODEL_PATH)
        let c = tr.config
        quantize_weights(tr)  // fused chains are Q8-only
        let prev_thresh = get_target_chunk_work()
        with_job_que() {
            setup_dasllama_jobque_()   // team mode on — the fused gate requires it
            set_target_chunk_work(1l)
            var ids_std : array<int64>
            var ids_fused : array<int64>
            var lg_std : array<float>
            var lg_fused : array<float>
            set_fused_decode(false)
            var s1 <- make_run_state(c)
            greedy_ids(tr, s1, ids_std, lg_std)
            delete s1
            set_fused_decode(true)
            var s2 <- make_run_state(c)
            greedy_ids(tr, s2, ids_fused, lg_fused)
            delete s2
            var id_bad = 0
            for (i in range(N_STEPS)) {
                if (ids_std[i] != ids_fused[i]) {
                    id_bad++
                }
            }
            t |> equal(0, id_bad)
            var lg_bad = 0
            for (i in range64(c.vocab_size)) {
                if (lg_std[i] != lg_fused[i]) {
                    lg_bad++
                }
            }
            t |> equal(0, lg_bad)
            delete ids_std
            delete ids_fused
            delete lg_std
            delete lg_fused
        }
        set_target_chunk_work(prev_thresh)
        delete tr
    }
}

def private fused_vs_std_bit_exact(t : T?; tr : Model) {
    let c = tr.config
    var ids_std : array<int64>
    var ids_fused : array<int64>
    var lg_std : array<float>
    var lg_fused : array<float>
    set_fused_decode(false)
    var s1 <- make_run_state(c)
    greedy_ids(tr, s1, ids_std, lg_std)
    delete s1
    set_fused_decode(true)
    var s2 <- make_run_state(c)
    greedy_ids(tr, s2, ids_fused, lg_fused)
    delete s2
    var id_bad = 0
    for (i in range(N_STEPS)) {
        if (ids_std[i] != ids_fused[i]) {
            id_bad++
        }
    }
    t |> equal(0, id_bad)
    var lg_bad = 0
    for (i in range64(c.vocab_size)) {
        if (lg_std[i] != lg_fused[i]) {
            lg_bad++
        }
    }
    t |> equal(0, lg_bad)
    delete ids_std
    delete ids_fused
    delete lg_std
    delete lg_fused
}

// stories15M's head_size (48) gates the ATTENTION chain off — this twin runs a real GGUF with
// head_size 64, so both chains (qkv→attn→wo AND w1/w3→w2) take the fused path. Two passes: the
// auto-selected backend (arm64-gen on an M1 — the interleaved rows core), then a fresh load
// under a "portable" pin — the rows core every host shares, and the EPYC box's profile-pinned
// decode config; without the pin an x64 auto-select picks an intrinsic tier with no rows core
// and the fused gate silently falls back (the A/B would compare std vs std).
[test]
def test_fused_decode_attn_chain(t : T?) {
    t |> run("fused attention chain bit-exact on SmolLM2-135M (needs the gguf)") @(t : T?) {
        if (!jit_enabled()) {
            t |> success(true, "skipped: interpreted (dasLLAMA model tests are JIT-only)")
            return
        }
        let path = path_join(models_dir(), "SmolLM2-135M-Instruct-Q8_0.gguf")
        if (!stat(path).is_valid) {
            t |> success(true, "skipped: {path} not present")
            return
        }
        let prev_backend = active_kernel_backend()
        let prev_thresh = get_target_chunk_work()
        with_job_que() {
            setup_dasllama_jobque_()
            set_target_chunk_work(1l)
            if (kernel_backend_has_rows()) {   // auto backend pass (skipped where auto has no rows core)
                var tr <- load_gguf(path, QuantMode.q8)
                fused_vs_std_bit_exact(t, tr)
                delete tr
            }
            pin_kernel_backend("portable")     // fresh row-major load under the shared rows core
            var tr2 <- load_gguf(path, QuantMode.q8)
            fused_vs_std_bit_exact(t, tr2)
            delete tr2
            clear_kernel_backend_pin()
        }
        set_target_chunk_work(prev_thresh)
        select_kernel_backend(prev_backend)
    }
}
