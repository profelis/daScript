options gen2
options indenting = 4

// Shared foundation for the dasLLAMA profiling suite: the model catalog, the small/large tier gate,
// the per-box platform block, and the baseline-TSV I/O that the reference establisher writes and the
// das-side generator reads. The suite is deliberately self-contained (it does not cross-require the
// tests/ tier helper) so it lives entirely under modules/dasLLAMA/performance/.

module profile_common shared public

require daslib/fio public
require strings public
require daslib/strings_boost public
require dasllama/dasllama_common public   // QuantMode

// ===== Box + model roots =====

// Machine-local model root; override with DASLLAMA_MODELS_DIR (the x64/handoff boxes).
def models_dir() : string {
    let env = get_env_variable("DASLLAMA_MODELS_DIR")
    return empty(env) ? "/Users/borisbatkin/Work/llama.cpp/models/" : env
}

// Short box tag baked into the JSON/TSV filenames (profile_llm_<box>.json). Override with DASLLAMA_BOX.
def box_name() : string {
    let env = get_env_variable("DASLLAMA_BOX")
    return empty(env) ? "m1" : env
}

// Models at or above this are large-tier (deferred unless --tier large|all). 6 GiB splits the
// ~5GB-and-under carriers (incl. gemma-4-E2B at 4.63GB) from the 7GB+ heavies.
let LARGE_TIER_BYTES = 6ul * 1024ul * 1024ul * 1024ul

// ===== The text-LLM catalog =====

//! One profiled text model: its GGUF basename under [[models_dir]], a scoreboard display name, the
//! quant to load das-side, and the prefill / emission context sizes to measure at.
struct LlmModel {
    file : string
    display : string
    quant : QuantMode
    prefill_ctx : int
    emission_ctx : int
}

// The text LLMs the suite profiles. Absent files are skipped at run time, so this can list every box's
// models; each box measures the subset it actually has. Audio models live in the ASR path, not here.
def llm_catalog() : array<LlmModel> {
    return <- [
        LlmModel(file="SmolLM2-135M-Instruct-Q8_0.gguf", display="SmolLM2-135M", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Qwen2.5-0.5B-Instruct-Q8_0.gguf", display="Qwen2.5-0.5B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Qwen3-0.6B-Q8_0.gguf", display="Qwen3-0.6B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="gemma-3-1b-it-Q8_0.gguf", display="gemma-3-1B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="tinyllama-1.1b-chat-v1.0.Q8_0.gguf", display="TinyLlama-1.1B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Llama-3.2-1B-Instruct-Q8_0.gguf", display="Llama-3.2-1B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Qwen2.5-1.5B-Instruct-Q8_0.gguf", display="Qwen2.5-1.5B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="SmolLM2-1.7B-Instruct-Q8_0.gguf", display="SmolLM2-1.7B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="gemma-2-2b-it-Q8_0.gguf", display="gemma-2-2B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Phi-3.5-mini-instruct-Q8_0.gguf", display="Phi-3.5-mini", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="gemma-3-4b-it-Q8_0.gguf", display="gemma-3-4B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Qwen3-4B-Instruct-2507-Q8_0.gguf", display="Qwen3-4B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="gemma-4-E2B-it-Q8_0.gguf", display="gemma-4-E2B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Mistral-7B-Instruct-v0.3-Q8_0.gguf", display="Mistral-7B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="gemma-4-E4B-it-Q8_0.gguf", display="gemma-4-E4B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128),
        LlmModel(file="Meta-Llama-3.1-8B-Instruct-Q8_0.gguf", display="Llama-3.1-8B", quant=QuantMode.q8, prefill_ctx=512, emission_ctx=128)
    ]
}

//! Tier selector matching the --tier flag.
enum Tier {
    small
    large
    all
}

def parse_tier(s : string) : Tier {
    if (s == "large") {
        return Tier.large
    }
    if (s == "all") {
        return Tier.all
    }
    return Tier.small
}

// Full path to a catalog entry's GGUF.
def model_path(m : LlmModel) : string {
    return "{models_dir()}{m.file}"
}

//! True when `m` is present on disk AND in the requested tier. `sz` receives the file size (0 if absent).
def model_selected(m : LlmModel; tier : Tier; var sz : uint64&) : bool {
    let st = stat(model_path(m))
    sz = st.is_valid ? st.size : 0ul
    if (!st.is_valid) {
        return false
    }
    let is_large = st.size >= LARGE_TIER_BYTES
    if (tier == Tier.all) {
        return true
    }
    return tier == Tier.large ? is_large : !is_large
}

// ===== Platform block =====

//! The per-box platform header stored at the top of every profile JSON.
struct PlatformInfo {
    cpu : string
    os : string
    threads : int
    daslang : string
    llama_cpp : string
    date : string
    box_profile : string
    parsec_off : bool
}

// Run `cmd`, return its trimmed stdout (first line only when `first_line`). Uses fread_to_eof (fio's
// pipe-safe reader) — fread(f) whole-file sizes via seek and returns empty on a non-seekable pipe.
def run_capture(cmd : string; first_line : bool) : string {
    var out = ""
    unsafe {
        popen(cmd) $(f) {
            out = fread_to_eof(f)
        }
    }
    out = strip(out)
    if (first_line) {
        let nl = find(out, "\n")
        if (nl >= 0) {
            out = slice(out, 0, nl)
        }
    }
    return out
}

// The running daslang's version, via the box's binary (DASLANG_BIN, default bin/daslang from the
// repo-root cwd these tools run in). Takes the last token of the first --version line ("0.6.3").
def das_version() : string {
    let bin = empty(get_env_variable("DASLANG_BIN")) ? "bin/daslang" : get_env_variable("DASLANG_BIN")
    let line = run_capture("{bin} --version", true)
    let toks <- split(line, " ")
    return empty(toks) ? "unknown" : toks[length(toks) - 1]
}

// Gather the platform block. `llama_cpp` (the reference commit) and `date` are passed in — the caller
// reads them from the freshly-run baseline / the environment so they stay honest per run.
def gather_platform(threads : int; llama_cpp, date, box_profile : string; parsec_off : bool) : PlatformInfo {
    let cpu = run_capture("sysctl -n machdep.cpu.brand_string", true)
    let os_name = run_capture("sw_vers -productName", true)
    let os_ver = run_capture("sw_vers -productVersion", true)
    let das_ver = das_version()
    return PlatformInfo(
        cpu = empty(cpu) ? "unknown" : cpu,
        os = "{os_name} {os_ver}",
        threads = threads,
        daslang = empty(das_ver) ? "unknown" : das_ver,
        llama_cpp = llama_cpp,
        date = date,
        box_profile = box_profile,
        parsec_off = parsec_off)
}

// ===== Baseline TSV I/O (reference tok/s the establisher writes, the generator reads) =====

//! One reference-tool baseline row for a model: llama.cpp prefill / emission tok/s (CPU), the lcpp
//! build commit, and the total parameter count llama-bench reported. -1 means "not measured".
struct LlmBaseline {
    model : string
    prefill_tok_s : double
    emission_tok_s : double
    lcpp_commit : string
    n_params : int64
}

def baseline_llm_path() : string {
    return "modules/dasLLAMA/performance/baseline_llm_{box_name()}.tsv"
}

def write_llm_baselines(rows : array<LlmBaseline>) {
    fopen(baseline_llm_path(), "wb") $(f) {
        if (f == null) {
            return
        }
        fwrite(f, "model\tprefill_tok_s\temission_tok_s\tlcpp_commit\tn_params\n")
        for (r in rows) {
            fwrite(f, "{r.model}\t{r.prefill_tok_s}\t{r.emission_tok_s}\t{r.lcpp_commit}\t{r.n_params}\n")
        }
    }
}

def read_llm_baselines() : array<LlmBaseline> {
    var rows : array<LlmBaseline>
    let text = fread(baseline_llm_path())
    var first = true
    for (line in split(text, "\n")) {
        if (first) {   // header
            first = false
            continue
        }
        if (empty(strip(line))) {
            continue
        }
        let col <- split(line, "\t")
        if (length(col) < 5) {
            continue
        }
        rows |> emplace(LlmBaseline(
            model = col[0],
            prefill_tok_s = to_double(col[1]),
            emission_tok_s = to_double(col[2]),
            lcpp_commit = col[3],
            n_params = to_int64(col[4])))
    }
    return <- rows
}

// ===== Profile JSON (the deliverable — one per box, das + reference tok/s) =====

//! One phase (prefill or emission) of a model's LLM profile. `llama_cpp_tok_s` is @optional: when the
//! reference wasn't measured on this box it stays 0.0 and is omitted from the JSON (absent key = no ref).
struct PhaseRec {
    context : int
    das_tok_s : double
    @optional llama_cpp_tok_s : double
}

//! One text-LLM row in a profile: model + metadata, plus its prefill and emission phases.
struct LlmRec {
    model : string
    arch : string
    quant : string
    active_b : double
    prefill : PhaseRec
    emission : PhaseRec
}

//! A complete per-box LLM profile: the platform block + one row per measured model. Serialized with
//! `sprint_json` and round-tripped with `sscan_json` — the machine-readable handoff for the website.
struct LlmProfile {
    platform : PlatformInfo
    tests : array<LlmRec>
}

def profile_llm_path() : string {
    return "modules/dasLLAMA/performance/profile_llm_{box_name()}.json"
}

def write_llm_profile(p : LlmProfile) {
    let text = sprint_json(p, true)
    fopen(profile_llm_path(), "wb") $(f) {
        if (f != null) {
            fwrite(f, text)
        }
    }
}

// Load the existing per-box profile into `p` for a merge run; false if none exists yet.
def read_llm_profile(var p : LlmProfile) : bool {
    let path = profile_llm_path()
    if (!stat(path).is_valid) {
        return false
    }
    return sscan_json(fread(path), p)
}

// Update-or-insert `rec` into `tests` keyed by model name — lets a small-tier run and a later
// large-tier run merge into one file without clobbering each other's rows.
def upsert_llm(var tests : array<LlmRec>; rec : LlmRec) {
    for (c in tests) {
        if (c.model == rec.model) {
            c = rec
            return
        }
    }
    tests |> push(rec)
}
