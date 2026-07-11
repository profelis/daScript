// Shared model-presence + size-tier gate for the dasLLAMA model-loading tests.
//
// The parity/audio fixtures load multi-GB GGUFs; loading every one on every iteration is the
// suite's main time sink. This gate keeps the fast iteration loop to each arch's small carrier
// and defers the large models (Mistral-7B, gemma-4-12B/E4B, gpt-oss-20b, the MoEs) to a pre-PR
// run. The large tier runs only when DASLLAMA_PARITY_FULL is set. CI has no models on disk, so
// every case skips there regardless of tier — the gate only ever bites on a local box.

options gen2

module _model_tier shared public

require dastest/testing_boost public
require daslib/fio public
require strings public

// Models larger than this are large-tier. 6 GiB cleanly splits the ~5GB-and-under carriers
// (incl. gemma-4-E2B at 4.97GB) from the 7.7GB+ heavies.
let LARGE_TIER_BYTES = 6ul * 1024ul * 1024ul * 1024ul

// Machine-local model root; override with DASLLAMA_MODELS_DIR (e.g. the x64 handoff box).
def models_dir() : string {
    let env = get_env_variable("DASLLAMA_MODELS_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama.cpp/models/" : env
}

// True when the large tier is enabled for this run (the pre-PR full sweep).
def parity_full_mode() : bool {
    return !empty(get_env_variable("DASLLAMA_PARITY_FULL"))
}

// Presence + tier gate for a model-loading test. Returns true if the caller should proceed to
// load `path`; otherwise registers a LOUD skip on `t` (model absent, or large-tier without
// DASLLAMA_PARITY_FULL) — the arm lands in the suite's skipped count instead of masquerading
// as a pass (two real x64 failures hid behind the passing form for months). `skip` unwinds,
// so the `return false` is for the signature; every call site is the arm-fatal
// `if (!model_available(t, path)) return` shape.
def model_available(t : T?; path : string) : bool {
    let st = stat(path)
    if (!st.is_valid) {
        t |> skip("{base_name(path)} not present")
        return false
    }
    if (!parity_full_mode() && st.size > LARGE_TIER_BYTES) {
        t |> skip("{base_name(path)} is large-tier ({st.size / (1024ul * 1024ul * 1024ul)} GB) — set DASLLAMA_PARITY_FULL=1 to run")
        return false
    }
    return true
}
