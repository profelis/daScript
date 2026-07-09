options gen2
options persistent_heap   // the f16 model A/B holds two Sessions (see test_forward.das)
options stack = 65536

require dastest/testing_boost public
require dasllama/dasllama_transformer   // nolint:STYLE029 — umbrella fires each arch [init] registration
require dasllama/dasllama_math   // setup_dasllama_jobque_ + target_chunk_work + fused knob
require llvm/daslib/f16_cvt
require daslib/jobque_boost
require daslib/fio
require math

// KV-cache codec layout invariants — synthetic Configs only (no model files, never skips):
// the per-session row-byte prefixes built by make_run_state must mirror layout_offsets' shared-
// skipping walk, agree with the definitional kv_cache_off on uniform models, alias shared-KV
// layers to their source slab, and size the blobs exactly. Plus the kv_store_row round-trip.
// The f16 codec cases at the bottom need stories15M (env-gated, skip contract as test_forward).

def private mk_config(layers, heads, kv_heads, hs, ctx : int64) : Config {
    return Config(dim = heads * hs, hidden_dim = 32l, n_layers = layers, n_heads = heads,
        n_kv_heads = kv_heads, vocab_size = 8l, seq_len = ctx, head_size = hs,
        kv_dim = kv_heads * hs, shared_weights = true, rope_freq_base = 10000.0)
}

// independent reference: layout_offsets' prefix walk (elements), shared layers aliasing the source
def private ref_prefix_elems(c : Config) : array<int64> {
    var pref : array<int64>
    var row = 0l
    for (l in range64(c.n_layers)) {
        let src = layer_kv_source(c, l)
        if (src != l) {
            pref |> push(pref[src])
        } else {
            pref |> push(row)
            row += layer_kv_dim(c, l)
        }
    }
    return <- pref
}

def private own_row_elems(c : Config) : int64 {
    var total = 0l
    for (l in range64(c.n_layers)) {
        if (layer_kv_source(c, l) == l) {
            total += layer_kv_dim(c, l)
        }
    }
    return total
}

def private check_layout(t : T?; c : Config; tag : string) {
    var s <- make_run_state(c)
    let ref <- ref_prefix_elems(c)
    for (l in range64(c.n_layers)) {
        t |> equal(s.kv_bprefix_k[l], ref[l] * 4l)   // f32 codec: byte prefix = 4 x element prefix
        t |> equal(s.kv_bprefix_v[l], s.kv_bprefix_k[l])   // same dtype -> same walk
        t |> equal(s.kv_bprefix_k[l], s.kv_bprefix_k[layer_kv_source(c, l)])   // shared-KV aliasing
    }
    let want = c.seq_len * own_row_elems(c) * 4l
    t |> success(int64(length(s.key_cache)) == want, "{tag}: key cache sized exactly (bytes)")
    t |> success(int64(length(s.value_cache)) == want, "{tag}: value cache sized exactly (bytes)")
    delete s
}

[test]
def test_kv_layout(t : T?) {
    t |> run("uniform model: prefixes match the definitional kv_cache_off") @(t : T?) {
        let c = mk_config(4l, 4l, 2l, 64l, 8l)
        var s <- make_run_state(c)
        for (l in range64(c.n_layers)) {
            // no shared layers -> the walking Config form and the skipping walk agree
            t |> equal(s.kv_bprefix_k[l] * c.seq_len, kv_cache_off(c, l) * 4l)
        }
        delete s
        check_layout(t, c, "uniform")
    }
    t |> run("gemma4-like ragged layers (SWA class differs in head size AND kv heads)") @(t : T?) {
        var c = mk_config(6l, 4l, 2l, 64l, 8l)
        c.sliding_window = 4l
        c.swa_pattern = 2l        // even layers slide
        c.head_size_swa = 32l
        c.n_kv_heads_swa = 4l
        check_layout(t, c, "ragged")
    }
    t |> run("E-series shared KV: post-boundary layers alias their source slab") @(t : T?) {
        var c = mk_config(6l, 4l, 2l, 64l, 8l)
        c.sliding_window = 4l
        c.swa_pattern = 2l
        c.n_layer_kv_from_start = 4l   // layers 4 (sliding -> src 2) and 5 (global -> src 3) share
        t |> equal(layer_kv_source(c, 4l), 2l)
        t |> equal(layer_kv_source(c, 5l), 3l)
        check_layout(t, c, "shared")
    }
}

[test]
def test_kv_layout_f16(t : T?) {
    t |> run("f16 sessions: byte prefixes halve, mixed K/V dtypes walk independently") @(t : T?) {
        let c = mk_config(4l, 4l, 2l, 64l, 8l)
        let ref <- ref_prefix_elems(c)
        var s16 <- make_run_state(c, KVDtype.f16, KVDtype.f16)
        for (l in range64(c.n_layers)) {
            t |> equal(s16.kv_bprefix_k[l], ref[l] * 2l)   // f16 codec: byte prefix = 2 x element prefix
            t |> equal(s16.kv_bprefix_v[l], s16.kv_bprefix_k[l])
        }
        let want16 = c.seq_len * own_row_elems(c) * 2l
        t |> success(int64(length(s16.key_cache)) == want16, "f16 key cache is half the f32 bytes")
        t |> success(int64(length(s16.value_cache)) == want16, "f16 value cache is half the f32 bytes")
        delete s16
        var smix <- make_run_state(c, KVDtype.f16, KVDtype.f32)   // K/V dtypes are independent
        for (l in range64(c.n_layers)) {
            t |> equal(smix.kv_bprefix_k[l], ref[l] * 2l)
            t |> equal(smix.kv_bprefix_v[l], ref[l] * 4l)
        }
        t |> success(int64(length(smix.key_cache)) * 2l == int64(length(smix.value_cache)),
            "mixed session: K blob is half the V blob")
        delete smix
    }
}

[test]
def test_kv_runs_flat(t : T?) {
    t |> run("flat sessions: every window is exactly one identity run; kv_phys_row is identity") @(t : T?) {
        let c = mk_config(2l, 4l, 2l, 64l, 16l)
        var s <- make_run_state(c)
        t |> equal(1, length(s.kv_runs))   // make_run_state sizes the flat scratch to one entry
        // whole-window, offset-window, single-row — all one run with row0 == j0
        var nrun = kv_runs(s, 0l, 16l, s.kv_runs)
        t |> equal(1l, nrun)
        t |> equal(0l, s.kv_runs[0].j0)
        t |> equal(16l, s.kv_runs[0].j1)
        t |> equal(0l, s.kv_runs[0].row0)
        nrun = kv_runs(s, 5l, 12l, s.kv_runs)   // sliding-window shape
        t |> equal(1l, nrun)
        t |> equal(5l, s.kv_runs[0].j0)
        t |> equal(12l, s.kv_runs[0].j1)
        t |> equal(5l, s.kv_runs[0].row0)       // flat: physical row == absolute position
        nrun = kv_runs(s, 7l, 8l, s.kv_runs)    // one row
        t |> equal(1l, nrun)
        t |> equal(7l, s.kv_runs[0].row0)
        t |> equal(0l, kv_runs(s, 9l, 9l, s.kv_runs))   // empty window: no runs
        t |> equal(0l, kv_runs(s, 9l, 3l, s.kv_runs))   // inverted window: no runs
        for (pos in range64(16l)) {
            t |> equal(pos, kv_phys_row(s, pos))
        }
        delete s
    }
}

[test]
def test_kv_store_row_f16(t : T?) {
    t |> run("f16 kv_store_row: RNE convert on store, clamp to ±65504, exact read-back") @(t : T?) {
        let c = mk_config(3l, 4l, 2l, 16l, 4l)
        let kv_dim = layer_kv_dim(c, 1l)
        var s <- make_run_state(c, KVDtype.f16, KVDtype.f16)
        var src : array<float>
        src |> resize(int(kv_dim))
        for (i in range(length(src))) {
            src[i] = float(i) * 0.5 - 3.0   // exactly representable in f16
        }
        src[0] = 0.1                        // not representable: pins the RNE rounding
        src[1] = 1.0e6                      // past f16 max: pins the +clamp
        src[2] = -1.0e6                     // pins the -clamp
        unsafe {
            let kbase = kv_base_k(s, 1l, c.seq_len)
            kv_store_row(addr(s.key_cache[0]) + kbase, s.kv_dtype_k, kv_dim, 3l, 0l, kv_dim,
                reinterpret<float const?>(addr(src[0])))
            let kcp = reinterpret<uint16 const?>(addr(s.key_cache[0]) + kbase)
            var ok = true
            for (i in range64(kv_dim)) {
                let want = f32_to_f16(clamp(src[i], -65504.0, 65504.0))
                ok &&= uint(kcp[3l * kv_dim + i]) == want
            }
            t |> success(ok, "every stored half == RNE(clamp(src))")
            t |> equal(f16_to_f32(uint(kcp[3l * kv_dim + 1l])), 65504.0)    // clamped, finite
            t |> equal(f16_to_f32(uint(kcp[3l * kv_dim + 2l])), -65504.0)
        }
        delete src
        delete s
    }
}

def private llama2c_dir() : string {
    let env = get_env_variable("DASLLAMA_LLAMA2C_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama2.c" : env
}
let MODEL_PATH = path_join(llama2c_dir(), "stories15M.bin")
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
def test_kv_f16_decode(t : T?) {
    t |> run("f16 KV: greedy trajectory matches f32, fused==std bit-exact under f16 (needs stories15M.bin)") @(t : T?) {
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
        quantize_weights(tr)
        let prev_thresh = get_target_chunk_work()
        with_job_que() {
            setup_dasllama_jobque_()
            set_target_chunk_work(1l)
            var ids32 : array<int64>
            var ids16 : array<int64>
            var ids16f : array<int64>
            var lg32 : array<float>
            var lg16 : array<float>
            var lg16f : array<float>
            set_fused_decode(false)
            var s32 <- make_run_state(c)
            greedy_ids(tr, s32, ids32, lg32)
            delete s32
            var s16 <- make_run_state(c, KVDtype.f16, KVDtype.f16)
            greedy_ids(tr, s16, ids16, lg16)
            delete s16
            set_fused_decode(true)
            var s16f <- make_run_state(c, KVDtype.f16, KVDtype.f16)
            greedy_ids(tr, s16f, ids16f, lg16f)
            delete s16f
            // f16 vs f32: same greedy trajectory (the real gate) + a structural logit backstop —
            // on a Q8 model a ~1e-3 attention diff can cross int8 requant boundaries and amplify
            // (~0.3 observed at step 24), so the bound only catches gross corruption (O(10))
            var id_bad = 0
            for (i in range(N_STEPS)) {
                if (ids32[i] != ids16[i]) {
                    id_bad++
                }
            }
            t |> equal(0, id_bad)
            var worst = 0.0
            for (i in range64(c.vocab_size)) {
                worst = max(worst, abs(lg32[i] - lg16[i]))
            }
            t |> success(worst < 1.0, "f16-vs-f32 final logits within the structural bound (worst |diff| = {worst})")
            // fused vs std, BOTH under f16: identical rounding both sides -> bit-exact
            var f_bad = 0
            for (i in range(N_STEPS)) {
                if (ids16[i] != ids16f[i]) {
                    f_bad++
                }
            }
            t |> equal(0, f_bad)
            var lg_bad = 0
            for (i in range64(c.vocab_size)) {
                if (lg16[i] != lg16f[i]) {
                    lg_bad++
                }
            }
            t |> equal(0, lg_bad)
            delete ids32
            delete ids16
            delete ids16f
            delete lg32
            delete lg16
            delete lg16f
        }
        set_target_chunk_work(prev_thresh)
        delete tr
    }
}

[test]
def test_kv_f16_prefill_vs_decode(t : T?) {
    t |> run("f16 KV: prefill == per-token decode, logits bit-exact (needs stories15M.bin)") @(t : T?) {
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
        quantize_weights(tr)
        let prev_thresh = get_target_chunk_work()
        let prev_mode = get_prefill_attn_mode()
        with_job_que() {
            setup_dasllama_jobque_()
            set_target_chunk_work(1l)
            set_prefill_attn_mode(AttnPrefillMode.blocked)   // blocked/classic are the bit-exact modes (flash reorders)
            var prompt : array<int64>
            for (i in range(16)) {
                prompt |> push(int64(i % 50 + 2))
            }
            let n = int64(length(prompt))
            var sp <- make_run_state(c, KVDtype.f16, KVDtype.f16)
            forward_batch(tr, sp, prompt, n, 0l)
            var sd <- make_run_state(c, KVDtype.f16, KVDtype.f16)
            var pos = 0l
            for (tok in prompt) {
                forward(tr, sd, tok, pos)
                pos++
            }
            var lg_bad = 0
            for (i in range64(c.vocab_size)) {
                if (sp.logits[i] != sd.logits[i]) {
                    lg_bad++
                }
            }
            t |> equal(0, lg_bad)
            var kv_bad = 0
            for (i in range(length(sd.key_cache))) {
                if (sp.key_cache[i] != sd.key_cache[i]) {
                    kv_bad++
                }
            }
            for (i in range(length(sd.value_cache))) {
                if (sp.value_cache[i] != sd.value_cache[i]) {
                    kv_bad++
                }
            }
            t |> equal(0, kv_bad)
            delete sp
            delete sd
            delete prompt
        }
        set_prefill_attn_mode(prev_mode)
        set_target_chunk_work(prev_thresh)
        delete tr
    }
}

[test]
def test_kv_store_row_roundtrip(t : T?) {
    t |> run("f32 kv_store_row: whole row + partial row land at the layer/row/sub address") @(t : T?) {
        let c = mk_config(3l, 4l, 2l, 16l, 4l)
        let kv_dim = layer_kv_dim(c, 1l)
        var s <- make_run_state(c)
        var src : array<float>
        src |> resize(int(kv_dim))
        for (i in range(length(src))) {
            src[i] = float(i) * 0.5 - 3.0
        }
        unsafe {
            let kbase = kv_base_k(s, 1l, c.seq_len)
            kv_store_row(addr(s.key_cache[0]) + kbase, s.kv_dtype_k, kv_dim, 3l, 0l, kv_dim,
                reinterpret<float const?>(addr(src[0])))   // whole row at row 3
            kv_store_row(addr(s.key_cache[0]) + kbase, s.kv_dtype_k, kv_dim, 1l, 16l, 16l,
                reinterpret<float const?>(addr(src[0])))   // one head slot at row 1, sub 16
            let kcp = reinterpret<float const?>(addr(s.key_cache[0]) + kbase)
            var ok_row = true
            for (i in range64(kv_dim)) {
                ok_row &&= kcp[3l * kv_dim + i] == src[i]
            }
            t |> success(ok_row, "whole-row store reads back exactly")
            var ok_sub = true
            for (i in range64(16l)) {
                ok_sub &&= kcp[1l * kv_dim + 16l + i] == src[i]
            }
            t |> success(ok_sub, "partial-row (head slot) store reads back exactly")
        }
        delete src
        delete s
    }
}
