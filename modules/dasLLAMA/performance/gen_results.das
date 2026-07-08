options gen2
options indenting = 4

// The renderer half of the profiling suite: reads every committed profile_llm_<box>.json and emits the
// LLM CPU scoreboard (results_llm.md) via daslib/md_boost. One section per box (platform header + a
// per-model table of das vs llama.cpp prefill/emission tok/s, winners bolded). results_llm.md is
// GENERATED — never hand-edited; the JSON is the single source of truth.
//   bin/daslang modules/dasLLAMA/performance/gen_results.das

require profile_common
require daslib/md_boost
require daslib/fio
require strings

let PERF_DIR = "modules/dasLLAMA/performance"
let RESULTS_PATH = "modules/dasLLAMA/performance/results_llm.md"

// All committed per-box LLM profiles, sorted so the .md ordering is stable across runs.
def list_llm_profiles() : array<string> {
    var out : array<string>
    dir(PERF_DIR) $(fn) {
        if (starts_with(fn, "profile_llm_") && ends_with(fn, ".json")) {
            out |> push("{PERF_DIR}/{fn}")
        }
    }
    sort(out)
    return <- out
}

// tok/s cell (1 decimal), or "-" when the value is absent (0 = unmeasured reference). ASCII, not an
// em dash, so the raw .md stays byte-aligned (render_md_table sizes columns by byte length).
def cell_tps(v : double) : string {
    return v > 0.0lf ? "{v:.1f}" : "-"
}

// das / lcpp ratio cell (higher das = faster => >1 wins), bolded on a das win. "-" if no reference.
def cell_ratio(das, lcpp : double) : string {
    if (lcpp <= 0.0lf || das <= 0.0lf) {
        return "-"
    }
    let r = das / lcpp
    let s = "{r:.2f}x"
    return r >= 1.0lf ? md_bold(s) : s
}

// One box's section: the platform header line + the per-model table.
def render_section(p : LlmProfile) : string {
    let pl = p.platform
    var rows : array<array<string>>
    // stable: ascending by active size
    var tests := p.tests
    sort(tests) $(a, b) => a.active_b < b.active_b
    var pctx = 512
    var ectx = 128
    if (!empty(tests)) {
        pctx = tests[0].prefill.context
        ectx = tests[0].emission.context
    }
    rows |> reserve(length(tests))
    for (t in tests) {
        rows |> emplace([
            t.model,
            "{t.active_b:.2f}",
            t.quant,
            cell_tps(t.prefill.das_tok_s),
            cell_tps(t.prefill.llama_cpp_tok_s),
            cell_ratio(t.prefill.das_tok_s, t.prefill.llama_cpp_tok_s),
            cell_tps(t.emission.das_tok_s),
            cell_tps(t.emission.llama_cpp_tok_s),
            cell_ratio(t.emission.das_tok_s, t.emission.llama_cpp_tok_s)
        ])
    }
    let headers <- [
        "model", "active B", "quant",
        "pp{pctx} das", "pp{pctx} lcpp", "das/lcpp",
        "tg{ectx} das", "tg{ectx} lcpp", "das/lcpp"
    ]
    let aligns <- [
        ColAlign.left, ColAlign.right, ColAlign.left,
        ColAlign.right, ColAlign.right, ColAlign.right,
        ColAlign.right, ColAlign.right, ColAlign.right
    ]
    let parsec = pl.parsec_off ? "Parsec off" : "Parsec ON"
    return build_string() $(w) {
        w |> write("## {pl.cpu}, {pl.threads} threads — daslang {pl.daslang}, llama.cpp {pl.llama_cpp}, {pl.date} ({parsec})\n\n")
        w |> write("{pl.os}; box profile `{pl.box_profile}`.\n\n")
        w |> write(render_md_table(headers, aligns, rows))
        w |> write("\n")
    }
}

def render_doc(profiles : array<LlmProfile>) : string {
    return build_string() $(w) {
        w |> write("# LLM CPU scoreboard (living doc — CURRENT numbers only; history in git)\n\n")
        w |> write("GENERATED from `profile_llm_<box>.json` by `gen_results.das` — do not hand-edit. ")
        w |> write("das = dasLLAMA (JIT, Q8); llama.cpp = `llama-bench` CPU (`-ngl 0`, no Accelerate/AMX BLAS). ")
        w |> write("pp*N* = prefill throughput over *N* prompt tokens; tg*N* = greedy generation of *N* tokens. ")
        w |> write("Ratio = das / llama.cpp (>1 = das faster); winners bold.\n\n")
        for (p in profiles) {
            w |> write(render_section(p))
            w |> write("\n")
        }
    }
}

[export]
def main() {
    var profiles : array<LlmProfile>
    for (path in list_llm_profiles()) {
        var p : LlmProfile
        if (sscan_json(fread(path), p)) {
            profiles |> emplace(p)
        } else {
            print("skip: {path} did not parse as an LlmProfile\n")
        }
    }
    if (empty(profiles)) {
        print("no profile_llm_*.json under {PERF_DIR} — run gen_profile.das first\n")
        return
    }
    let doc = render_doc(profiles)
    fopen(RESULTS_PATH, "wb") $(f) {
        if (f != null) {
            fwrite(f, doc)
        }
    }
    print("wrote {length(profiles)} box section(s) -> {RESULTS_PATH}\n")
}
