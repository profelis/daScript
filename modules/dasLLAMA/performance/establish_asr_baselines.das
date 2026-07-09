options gen2
options indenting = 4

// Batch ASR reference-baseline establisher — the audio sibling of establish_baselines.das (which is
// llama-bench-only). Runs each audio model's REFERENCE engine(s) once per box and writes their
// best-of-reps transcribe ms to a machine-readable per-box baseline that gen_asr_profile then merges
// with the freshly-measured das side. The das side is uniform (asr_bench rig); the heterogeneity is
// all here — four reference families, each with its own binary + output shape:
//   parakeet-cli / whisper-cli  (whisper.cpp; transcribe = total - load from *_print_timings)
//   onnx                        (onnx_bench.py; ORT-CPU int8; BENCH tsv lines, single-window whisper)
//   nemo                        (canary_qwen_bench.py; NeMo SALM greedy; BENCH tsv lines)
//   mtmd                        (patched llama-mtmd-cli; MTMD_TIMING encode/decode/total split)
//
// Parsec MUST be off — every tool here is a measurement.
//   bin/daslang modules/dasLLAMA/performance/establish_asr_baselines.das -- -o Parakeet
//   bin/daslang modules/dasLLAMA/performance/establish_asr_baselines.das -- --libri

require profile_common
require daslib/clargs
require strings
require daslib/strings_boost
require daslib/fio

[CommandLineArgs]
struct Args {
    @clarg_short = "o"
    @clarg_doc = "Only models whose display name contains this substring (default: all)"
    only : string = ""

    @clarg_doc = "Threads passed to every reference tool (default 8 — the box perf-core count)"
    threads : int = 8

    @clarg_short = "r"
    @clarg_doc = "Timed repetitions per clip; the baseline keeps the best (default 2)"
    reps : int = 2

    @clarg_doc = "Also run the 25-clip LibriSpeech dictation set (heavy; default off)"
    libri : bool

    @clarg_short = "?"
    @clarg_doc = "Show this help and exit"
    help : bool
}

// ===== Reference-tool binaries / interpreters (all env-overridable) =====

def env_or(name, dflt : string) : string {
    let v = get_env_variable(name)
    return empty(v) ? dflt : v
}

def whisper_cpp_bin(cli : string) : string {
    let root = env_or("WHISPER_CPP", "/Users/borisbatkin/Work/whisper.cpp")
    return "{root}/build/bin/{cli}"
}

def onnx_py() : string {
    return env_or("ONNX_PY", "/Users/borisbatkin/Work/parakeet-tdt-0.6b-v3-fastapi-openai/.venv/bin/python")
}

def nemo_py() : string {
    return env_or("NEMO_PY", "/Users/borisbatkin/Work/canary-nemo-oracle/.venv/bin/python")
}

def mtmd_bin() : string {
    return env_or("MTMD_BIN", "/Users/borisbatkin/Work/llama.cpp/build/bin/llama-mtmd-cli")
}

// The python bench scripts live beside the corpus (asr/); this tool runs from the repo-root cwd.
def asr_dir() : string {
    return "modules/dasLLAMA/benchmarks/asr"
}

// ===== Output parsers =====

// The numeric token immediately before an "ms" token on a whitespace line (whisper.cpp timing lines:
// "whisper_print_timings:  total time =  1234.56 ms"). -1 if none.
def ms_before_ms_token(line : string) : double {
    let toks <- [for (t in split(line, " ")); t; where !empty(t)]
    for (i in range(length(toks))) {
        if (toks[i] == "ms" && i > 0) {
            return to_double(toks[i - 1])
        }
    }
    return -1.0lf
}

// whisper.cpp transcribe ms = total time - load time, from the *_print_timings lines. -1 on failure.
def parse_cli_ms(out : string) : double {
    var load = -1.0lf
    var total = -1.0lf
    for (line in split(out, "\n")) {
        if (find(line, "_print_timings") < 0) {
            continue
        }
        if (find(line, "load time") >= 0) {
            load = ms_before_ms_token(line)
        }
        if (find(line, "total time") >= 0) {
            total = ms_before_ms_token(line)
        }
    }
    return (load >= 0.0lf && total >= 0.0lf) ? total - load : -1.0lf
}

// Best (min) ms over the BENCH lines whose clip basename == `wav_base` (onnx_bench / canary_qwen_bench
// emit "BENCH\t<model>\t<base>\t<audio_s>\t<rep>\t<ms>\t<speed>"). Also reports the audio seconds. -1 if none.
def parse_bench_best(out, wav_base : string; var audio_s : double&) : double {
    var best = -1.0lf
    audio_s = -1.0lf
    for (line in split(out, "\n")) {
        let c <- split(line, "\t")
        if (length(c) < 6 || c[0] != "BENCH" || c[2] != wav_base) {
            continue
        }
        audio_s = to_double(c[3])
        let ms = to_double(c[5])
        if (ms > 0.0lf && (best < 0.0lf || ms < best)) {
            best = ms
        }
    }
    return best
}

// The patched llama-mtmd-cli emits "MTMD_TIMING encode_prefill_ms E decode_ms D total_ms T". Returns
// (total, encode) ms; (-1, -1) if the line is absent.
def parse_mtmd_ms(out : string) : tuple<total : double; encode : double> {
    for (line in split(out, "\n")) {
        if (find(line, "MTMD_TIMING") < 0) {
            continue
        }
        let toks <- [for (t in split(line, " ")); t; where !empty(t)]
        var enc = -1.0lf
        var tot = -1.0lf
        for (i in range(length(toks))) {
            if (toks[i] == "encode_prefill_ms" && i + 1 < length(toks)) {
                enc = to_double(toks[i + 1])
            }
            if (toks[i] == "total_ms" && i + 1 < length(toks)) {
                tot = to_double(toks[i + 1])
            }
        }
        return (total = tot, encode = enc)
    }
    return (total = -1.0lf, encode = -1.0lf)
}

// ===== Per-tool runners (each returns best-of-reps ms for one clip; mtmd also the encode split) =====

// whisper.cpp parakeet-cli / whisper-cli — one process per clip (load is ~ms). Best over `reps`.
def run_cli(cli, model_path, wav_path : string; threads, reps : int) : double {
    let flags = cli == "whisper-cli" ? "-bs 1 -bo 1 -nf -ng" : "-ng"
    var best = -1.0lf
    for (_rep in range(reps)) {
        let cmd = "{whisper_cpp_bin(cli)} -m {model_path} -f {wav_path} -t {threads} {flags} 2>&1"
        let ms = parse_cli_ms(run_capture(cmd, false))
        if (ms > 0.0lf && (best < 0.0lf || ms < best)) {
            best = ms
        }
    }
    return best
}

// patched llama-mtmd-cli — one process per clip (30B load is heavy). Best total over `reps`, plus the
// encode+prefill split from the winning-total run's own line (encode tracks total closely rep-to-rep).
def run_mtmd(model_path, mmproj_path, wav_path : string; threads, reps : int; var encode_ms : double&) : double {
    encode_ms = -1.0lf
    var best = -1.0lf
    for (_rep in range(reps)) {
        let cmd = ("{mtmd_bin()} -m {model_path} --mmproj {mmproj_path} --audio {wav_path} " +
            "-p \"Transcribe the audio.\" --temp 0 --jinja -ngl 0 -t {threads} 2>&1")
        let r = parse_mtmd_ms(run_capture(cmd, false))
        if (r.total > 0.0lf && (best < 0.0lf || r.total < best)) {
            best = r.total
            encode_ms = r.encode
        }
    }
    return best
}

// ===== Baseline assembly =====

// The full corpus paths for a model's declared buckets (relative to the repo-root cwd — the reference
// tools inherit it).
def bucket_paths(spec : AsrModelSpec) : array<tuple<name : string; path : string>> {
    return <- [for (b in spec.buckets); (name = b, path = "{asr_corpus_dir()}{b}")]
}

// The 25 LibriSpeech dictation clips (sorted NN_* order), full paths.
def libri_clips() : array<tuple<name : string; path : string>> {
    var out : array<tuple<name : string; path : string>>
    let d = "{asr_corpus_dir()}librispeech/"
    dir(d) $(fn) {
        if (ends_with(fn, ".wav")) {
            out |> push((name = fn, path = "{d}{fn}"))
        }
    }
    sort(out) $(a, b) => a.name < b.name
    return <- out
}

// Run one reference tool over `clips`, appending baseline rows (kind = "corpus" | "libri").
def run_ref_over(var rows : array<AsrBaseRow>; spec : AsrModelSpec; ref : AsrRef;
                 clips : array<tuple<name : string; path : string>>; kind : string; threads, reps : int) {
    let model_path = "{spec.root}{spec.das_model}"
    rows |> reserve(length(rows) + length(clips))
    if (ref.tool == "parakeet-cli" || ref.tool == "whisper-cli") {
        for (c in clips) {
            let ms = run_cli(ref.tool, model_path, c.path, threads, reps)
            print("  {ref.tool} {c.name}: {ms} ms\n")
            rows |> emplace(AsrBaseRow(tool = ref.tool, model = spec.display, kind = kind,
                wav = c.name, audio_s = -1.0lf, ms = ms, encode_ms = -1.0lf))
        }
    } elif (ref.tool == "mtmd") {
        let mmproj_path = "{spec.root}{ref.handle}"
        for (c in clips) {
            var enc = -1.0lf
            let ms = run_mtmd(model_path, mmproj_path, c.path, threads, reps, enc)
            print("  mtmd {c.name}: {ms} ms (encode {enc})\n")
            rows |> emplace(AsrBaseRow(tool = ref.tool, model = spec.display, kind = kind,
                wav = c.name, audio_s = -1.0lf, ms = ms, encode_ms = enc))
        }
    } elif (ref.tool == "onnx" || ref.tool == "nemo") {
        // one invocation over every clip — python model load is expensive, amortize it
        let wav_args = build_string() $(w) {
            for (c in clips) {
                w |> write(" --wav {c.path}")
            }
        }
        let cmd = (ref.tool == "onnx"
            ? "{onnx_py()} {asr_dir()}/onnx_bench.py --variant {ref.handle} --threads {threads} --reps {reps}{wav_args} 2>&1"
            : "{nemo_py()} {asr_dir()}/canary_qwen_bench.py --threads {threads} --reps {reps}{wav_args} 2>&1")
        let out = run_capture(cmd, false)
        for (c in clips) {
            var audio_s = -1.0lf
            let ms = parse_bench_best(out, c.name, audio_s)
            print("  {ref.tool} {c.name}: {ms} ms\n")
            rows |> emplace(AsrBaseRow(tool = ref.tool, model = spec.display, kind = kind,
                wav = c.name, audio_s = audio_s, ms = ms, encode_ms = -1.0lf))
        }
    }
}

[export]
def main() {
    var r <- parse_args(type<Args>)
    if (r |> is_err) {
        print("error: {r |> unwrap_err}\n\n")
        print_help(get_command_info(type<Args>), "establish_asr_baselines")
        return
    }
    let cfg <- r |> move_unwrap
    if (cfg.help) {
        print_help(get_command_info(type<Args>), "establish_asr_baselines")
        return
    }
    print("establishing ASR baselines: box={box_name()} threads={cfg.threads} reps={cfg.reps} libri={cfg.libri}\n")
    print("NOTE: this runs the reference engines (a measurement) — Parsec must be off.\n\n")

    var libri : array<tuple<name : string; path : string>>
    if (cfg.libri) {
        libri <- libri_clips()
    }
    var rows : array<AsrBaseRow>
    for (spec in asr_catalog()) {
        if (!empty(cfg.only) && find(spec.display, cfg.only) < 0) {
            continue
        }
        if (!stat("{spec.root}{spec.das_model}").is_valid) {
            print("{spec.display}: model absent — skipped\n")
            continue
        }
        print("{spec.display}\n")
        let corpus <- bucket_paths(spec)
        for (ref in spec.refs) {
            run_ref_over(rows, spec, ref, corpus, "corpus", cfg.threads, cfg.reps)
            if (cfg.libri && !empty(spec.libri_short) && !empty(libri)) {
                run_ref_over(rows, spec, ref, libri, "libri", cfg.threads, cfg.reps)
            }
        }
    }
    write_asr_baselines(rows)
    print("\nwrote {length(rows)} baseline row(s) -> {baseline_asr_path()}\n")
}
