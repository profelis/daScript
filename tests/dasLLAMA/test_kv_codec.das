options gen2

require dastest/testing_boost public
require dasllama/dasllama_transformer   // nolint:STYLE029 — umbrella fires each arch [init] registration

// KV-cache codec layout invariants — synthetic Configs only (no model files, never skips):
// the per-session row-byte prefixes built by make_run_state must mirror layout_offsets' shared-
// skipping walk, agree with the definitional kv_cache_off on uniform models, alias shared-KV
// layers to their source slab, and size the blobs exactly. Plus the kv_store_row round-trip.

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
