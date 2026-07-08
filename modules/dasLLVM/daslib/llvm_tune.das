options gen2
options indenting = 4
options no_aot = true

module llvm_tune shared public

require daslib/ast
require daslib/rtti
require daslib/ast_boost
require daslib/templates_boost
require daslib/fio
require daslib/strings_boost
require daslib/command_line
require strings
require llvm/daslib/llvm_code public

//! Generalized tune framework (gemm_generator_plan.md part 2). `[tune_perm(...), ...,
//! tune(gen="key", fallback="suffix")]` — perm rows first, `tune` last — turns one reference
//! function into a tuned `[llvm_code]` kernel family. `[tune_companion(fn=, gen=)]` rows
//! (between the perm rows and `tune`) stamp sibling functions with the SAME perm from the same
//! manifest entry — the two-function stamp (a kernel and its repack-layout query can never
//! desync). `DAS_TUNE_MODE` selects the compile-time mode:
//!  - normal (default): stamp exactly one winner onto the function itself — the manifest
//!    entry when one exists, else the `fallback=` perm, else the reference body (a manifest
//!    with no entry for a function falls through to its fallback — new kernel families must
//!    not be dropped to the reference tier by a stale manifest; an explicit "reference"
//!    entry forces the original body). No variant stubs are emitted; the `<name>_variants()`
//!    registry still exists (reference row only) so harness code compiles in every mode.
//!  - tune / test: stamp the full grid as `<name>__<suffix>` clones plus a `<name>_variants()`
//!    registry; a harness benches them (tune, then `tune_manifest_set` the winner) or
//!    bit-exact-gates every variant against the reference row (test).
//!
//! Per-box sharing + UX rail: a library declares `[tune_scope(name=, tuner=)]` (manifest at
//! `<das_root>/<name>.tune.json`, shared by every app that requires it); an app declares
//! `[tune_policy(missing = fallback|warn|error|auto|restart)]`; `--tune` after `--` on the
//! app's command line forces a fresh tuner run. AOT builds are fully tune-free
//! (`tune_aot_gate`); `-exe` builds stamp normally but run no policy (`tune_exe_gate`) — an
//! exe built WITH a manifest is a local-use artifact shipping those winners, one built
//! without ships the generic per-ISA `fallback=` stamps.

// ===== manifest + mode =====

//! Compile-time tune mode from the `DAS_TUNE_MODE` env var: "normal" (default), "tune", "test".
def tune_mode() : string {
    let m = get_env_variable("DAS_TUNE_MODE")
    return empty(m) ? "normal" : m
}

//! True when this compile is AOT — C++ generation (`policies.aot_module`) or an AOT-consuming
//! run (`policies.aot`). Under AOT every tune annotation is fully inert: no manifest/scope
//! reads, no stamps (`fallback=` included), no policy, no injected checks — only the
//! reference-row `<name>_variants()` registries are emitted so harness code still compiles.
//! AOT soundness depends on the gate covering BOTH the generating and the consuming compile:
//! per-box stamps would desync their AOT hashes.
def tune_aot_gate() : bool {
    return compiling_program().policies.aot || compiling_program().policies.aot_module
}

//! True when this compile produces a standalone exe (`llvm-jit -exe`). Stamping still runs:
//! an exe built on a box WITH a manifest ships those winners (a local-use artifact by
//! definition), and without one it ships the generic per-ISA `fallback=` stamps. Only the
//! policy rail (`[tune_policy]`, `--tune`) is dead — a frozen artifact must not demand or
//! run tuning.
def tune_exe_gate() : bool {
    return compiling_program().policies.jit_exe_mode
}

// runtime copy of the program's manifest declaration, set by the injected [init]s — a
// library [tune_scope] first, then (root module inits run last) an app [tune_manifest]
var private g_runtime_manifest = ""

//! Runtime hook the `[tune_manifest]`/`[tune_scope]`-injected [init]s call; harnesses that
//! manage their own manifest location can also call it directly before using the get/set APIs.
def set_tune_manifest_runtime_path(p : string) {
    g_runtime_manifest = p
}

//! The tune manifest location: `DAS_TUNE_MANIFEST` env override, else the app's
//! `[tune_manifest]` declaration, else the library's `[tune_scope]` per-box file, else "" —
//! no manifest.
def tune_manifest_path() : string {
    let env = get_env_variable("DAS_TUNE_MANIFEST")
    if (!empty(env)) return env
    return g_runtime_manifest
}

// flat { "function name" : "perm suffix" } map; found = the file existed and parsed
def private read_manifest(path : string; var found : bool&) : table<string; string> {
    found = false
    var tab : table<string; string>
    if (!empty(path)) {
        let text = fread(path)
        if (!empty(text)) {
            found = sscan_json(text, tab)
        }
    }
    return <- tab
}

//! The winning perm suffix recorded for `fname`, or "" when the manifest is absent or has no
//! entry — the read-your-own-tune-value API.
def tune_manifest_get(fname : string) : string {
    var found = false
    var tab <- read_manifest(tune_manifest_path(), found)
    let r = tab?[fname] ?? ""
    delete tab
    return r
}

//! Upsert `fname -> suffix` into the manifest and save it — the set-a-value API the tune
//! harness calls after picking a winner. Returns false when no manifest location is
//! configured (env or `[tune_manifest]`) or the file can't be written.
def tune_manifest_set(fname : string; suffix : string) : bool {
    let path = tune_manifest_path()
    if (empty(path)) {
        return false
    }
    var found = false
    var tab <- read_manifest(path, found)
    tab[fname] = suffix
    let ok = fwrite(path, sprint_json(tab, true))
    delete tab
    return ok
}

// ===== tune status (runtime) =====

//! One tuned function's final compile-time decision, as reported by `tune_status()`.
struct TuneStatus {
    fname : string
    scope : string          // [tune_scope] name, "" when env/app-manifest driven
    suffix : string         // winning perm suffix, "" for the reference body
    source : string         // "manifest" | "fallback" | "reference"
    manifestPath : string   // the manifest the winner came from (or would come from)
}

var private g_tune_status : array<TuneStatus>

//! Hook the `[tune_policy]`-injected [init] calls once per tuned function.
def tune_status_add(fname, scope, suffix, source, manifestPath : string) {
    g_tune_status |> push(TuneStatus(fname = fname, scope = scope, suffix = suffix,
        source = source, manifestPath = manifestPath))
}

//! The program's tune decisions — one row per `[tune]` function. Populated when the app
//! declares `[tune_policy]` (its injected [init] fills the table); empty otherwise.
def tune_status() : array<TuneStatus> {
    return clone_to_move(g_tune_status)
}

//! Log the tune status table at `LOG_INFO` — the shared "am I tuned?" surface for any app.
//! `appName` prefixes the lines. No-op when the table is empty (no `[tune_policy]`, or a
//! standalone build). Prints `<n>/<total> kernels tuned for this box`, one line per function,
//! and a `--tune` hint when any kernel is on a fallback/reference tier.
def log_tune_status(appName : string) {
    var st <- tune_status()
    if (empty(st)) {
        delete st
        return
    }
    var tuned = 0
    for (s in st) {
        tuned += s.source == "manifest" ? 1 : 0
    }
    to_log(LOG_INFO, "{appName}: tune status ({tuned}/{length(st)} kernels tuned for this box):\n")
    for (s in st) {
        to_log(LOG_INFO, "  {s.fname}: {empty(s.suffix) ? "reference" : s.suffix} ({s.source})\n")
    }
    if (tuned < length(st)) {
        to_log(LOG_INFO, "{appName}: run with --tune to tune the remaining kernels for this box\n")
    }
    delete st
}

// ===== [tune_scope] data — library-owned per-box scope =====

// one registered scope: a per-box manifest at <das_root>/<name>.tune.json plus the harness
// that produces it
struct private TuneScope {
    scopeName : string
    manifestPath : string
    tunerPath : string   // resolved against the declaring file; "" = no tuner declared
}

// declaring module name -> scope. [tune] applies in that module resolve their manifest here
// when no DAS_TUNE_MANIFEST env is set; [tune_policy] drives tuner runs off the same bank.
var private g_scopes : table<string; TuneScope>

def private scope_manifest_for(modName : string) : string {
    if (g_scopes |> key_exists(modName)) {
        return g_scopes[modName].manifestPath
    }
    return ""
}

// ===== the perm grid =====

struct private TunePerm {
    suffix : string
    requires : string   // fallback-eligibility hint: "a,b" = AND, "a|b" = OR per element; "" = everywhere
    args : array<tuple<argname : string; argvalue : RttiValue>>
}

// fallback tier truth: host cpuid OR'd with the DAS_JIT_X64_FORCE_FEATURES emission-only
// override — same names and semantics as llvm_jit_common's x64_target_feature (keep in
// lockstep; that module lives outside this macro context). requires= is an ELIGIBILITY
// hint for fallback selection only — the generator's own decline predicate remains the
// emission truth (a stamped-but-declining row still lands on the reference body).
// arm64 feature names (e.g. "i8mm") ride DAS_JIT_ARM64_FORCE_FEATURES: cpu_supports is
// x64-cpuid-only (fail-closed on arm), and this is macro context — no LLVM host-features
// query here — so on aarch64 the env IS the eligibility truth (the same env the emission
// rail and the DLL cache key read; a native-i8mm box without it still runs smmla via the
// manifest, which bypasses requires=).
def private fallback_feature_ok(name : string) : bool {
    if (cpu_supports(name)) return true
    for (part in split(get_env_variable("DAS_JIT_X64_FORCE_FEATURES"), ",")) {
        if (part == name) return true
    }
    for (part in split(get_env_variable("DAS_JIT_ARM64_FORCE_FEATURES"), ",")) {
        if (part == name) return true
    }
    return false
}

def private perm_requires_ok(p : TunePerm) : bool {
    if (empty(p.requires)) return true
    for (conj in split(p.requires, ",")) {
        continue if (empty(conj))
        var anyOk = false
        for (alt in split(conj, "|")) {
            anyOk ||= !empty(alt) && fallback_feature_ok(alt)
        }
        if (!anyOk) return false
    }
    return true
}

def private suffix_piece(name : string; v : RttiValue) : string {
    if (v is tBool) return (v as tBool) ? name : "no{name}"
    if (v is tInt) return "{name}{v as tInt}"
    if (v is tString) return "{name}_{v as tString}"
    if (v is tFloat) return replace("{name}{v as tFloat}", ".", "d")
    return name
}

// Annotation applies run in declaration order, and a function's annotations only attach to
// the Function AFTER every apply has run — so [tune] cannot read its [tune_perm] siblings off
// func.annotations. Instead each [tune_perm] apply banks its row here (all tune annotations
// share llvm_tune's macro context), and the trailing [tune] apply consumes them.
var private g_perm_rows : table<string; array<TunePerm>>

def private perm_key(func : FunctionPtr) : string => "{compiling_module().name}::{func.name}"

// one TunePerm from one [tune_perm(...)] declaration's args; suffix= overrides the
// auto-derived name
def private build_perm_row(args : AnnotationArgumentList) : TunePerm {
    var row : TunePerm
    for (aa in args) {
        let v = get_annotation_argument_value(aa)
        if (aa.name == "suffix") {
            if (v is tString) { row.suffix = v as tString }
            continue
        }
        if (aa.name == "requires") {
            // eligibility hint, consumed here — must not leak into the stamp args or the
            // auto-derived suffix
            if (v is tString) { row.requires = v as tString }
            continue
        }
        row.args |> emplace((argname = string(aa.name), argvalue = v))
    }
    if (empty(row.suffix)) {
        var pieces <- [for (a in row.args); suffix_piece(a.argname, a.argvalue)]
        row.suffix = join(pieces, "_")
        delete pieces
    }
    return <- row
}

// one companion row: a sibling function stamped with the same perm as the tuned function
struct private TuneCompanion {
    fnname : string
    genkey : string
    @do_not_delete fn : FunctionPtr   // gc_node-owned by the module, not this row
}

var private g_companion_rows : table<string; array<TuneCompanion>>

// pull the banked companion rows for `func` and resolve each sibling function
def private take_companions(func : FunctionPtr; var errors : das_string) : array<TuneCompanion> {
    var comps : array<TuneCompanion>
    let key = perm_key(func)
    if (g_companion_rows |> key_exists(key)) {
        comps <- g_companion_rows[key]
        g_companion_rows |> erase(key)
    }
    var seen : table<string>
    for (c in comps) {
        if (seen |> key_exists(c.fnname)) {
            errors := "[tune] on {func.name}: duplicate companion '{c.fnname}'"
        } elif (c.fnname == func.name) {
            errors := "[tune] on {func.name}: a companion can't be the tuned function itself"
        } else {
            c.fn = compiling_module() |> find_unique_function(c.fnname, true)
            if (c.fn == null) {
                errors := "[tune] on {func.name}: companion function '{c.fnname}' not found — declare exactly one, before the tuned function, in the same module"
            } elif (c.fn.result.baseType == Type.autoinfer) {
                errors := "[tune] on {func.name}: companion {c.fnname} needs an explicit return type"
            } else {
                // even when this compile leaves the companion unstamped (no fallback, no env
                // manifest), a root-module [tune_manifest] may re-stamp it later — a pure
                // zero-arg companion const-folded at ITS module's compile would leave stale
                // reference values at call sites while the main function moves to the
                // manifest perm. Force the side effect up front, not just at stamp time.
                c.fn.sideEffectFlags.userScenario = true
            }
        }
        if (!empty(errors)) {
            break
        }
        seen |> insert(c.fnname)
    }
    delete seen
    return <- comps
}

// pull the banked rows for `func` (moving them out of the registry) and validate the set
def private take_perms(func : FunctionPtr; var errors : das_string) : array<TunePerm> {
    var perms : array<TunePerm>
    let key = perm_key(func)
    if (g_perm_rows |> key_exists(key)) {
        perms <- g_perm_rows[key]
        g_perm_rows |> erase(key)
    }
    var seen : table<string>
    for (p in perms) {
        if (empty(p.suffix)) {
            errors := "[tune] on {func.name}: a [tune_perm] with no args needs an explicit suffix=\"...\""
        } elif (p.suffix == "reference") {
            errors := "[tune] on {func.name}: perm suffix 'reference' is reserved for the unstamped body"
        } elif (seen |> key_exists(p.suffix)) {
            errors := "[tune] on {func.name}: duplicate perm suffix '{p.suffix}'"
        }
        if (!empty(errors)) {
            break
        }
        seen |> insert(p.suffix)
    }
    delete seen
    return <- perms
}

// ===== stamping =====

// [llvm_code(name=<generator>, <perm args>)] onto `fn`. The appended declaration's own apply
// does not run for macro-added annotations, so force the side effects here too — without
// userScenario the front-end const-folds constant-arg calls before they reach the JIT.
// tune_suffix/tune_from ride along as extra args (generators ignore unknown args by
// contract): they are the stamped-truth record `collect_status` reads back off the AST —
// `from` is the manifest the winner came from, "" for a fallback= stamp.
def private stamp_llvm_code(var fn : FunctionPtr; genKey : string; perm : TunePerm; from : string) {
    var aargs : array<tuple<argname : string; argvalue : RttiValue>>
    aargs |> reserve(length(perm.args) + 3)
    aargs |> push((argname = "name", argvalue = RttiValue(tString = genKey)))
    for (a in perm.args) {
        aargs |> push((argname = a.argname, argvalue = a.argvalue))
    }
    aargs |> push((argname = "tune_suffix", argvalue = RttiValue(tString = perm.suffix)))
    aargs |> push((argname = "tune_from", argvalue = RttiValue(tString = from)))
    fn |> append_annotation("llvm_code", "llvm_code", aargs)
    fn.sideEffectFlags.userScenario = true
    delete aargs
}

// tune/test modes: one `<base>__<suffix>` clone per perm, each carrying its [llvm_code] stamp,
// plus the `<base>_variants()` registry — and the same treatment for every companion (its
// clones carry the companion's generator key with the same perm args/suffixes). The base
// functions keep their reference bodies — they are the oracle rows. (Clones are
// annotation-free: the parsed declarations attach to the base only after every apply has run,
// which is after the clones are made.)
def private stamp_grid(var func : FunctionPtr; genKey : string; perms : array<TunePerm>; comps : array<TuneCompanion>; var errors : das_string) : bool {
    var mod = compiling_module()
    for (p in perms) {
        var fclone = clone_function(func)
        fclone.name := "{func.name}__{p.suffix}"
        stamp_llvm_code(fclone, genKey, p, "")
        fclone.flags.generated = true
        if (!(mod |> add_function(fclone))) {
            errors := "[tune] on {func.name}: failed to add variant {fclone.name}"
            return false
        }
    }
    if (!emit_registry(mod, func, perms, errors)) {
        return false
    }
    for (c in comps) {
        for (p in perms) {
            var cclone = clone_function(c.fn)
            cclone.name := "{c.fnname}__{p.suffix}"
            stamp_llvm_code(cclone, c.genkey, p, "")
            cclone.flags.generated = true
            if (!(mod |> add_function(cclone))) {
                errors := "[tune] on {func.name}: failed to add companion variant {cclone.name}"
                return false
            }
        }
        if (!emit_registry(mod, c.fn, perms, errors)) {
            return false
        }
    }
    return true
}

// `<base>_variants() : array<tuple<string; <sig>>>` — ("reference", @@base) first, then one row
// per perm. `<sig>` is the base function's own type, so the registry is generic across kernels.
def private emit_registry(var mod : Module?; base : FunctionPtr; perms : array<TunePerm>; var errors : das_string) : bool {
    let sig = function_to_type(base)
    var body : array<ExpressionPtr>
    body |> reserve(length(perms) + 3)
    body |> push <| qmacro_expr() {
        var result : array<tuple<string; $t(sig)>>
    }
    var baseAddr = new ExprAddr(at = base.at, target := "{base.name}")
    body |> push <| qmacro_expr() {
        result |> push(("reference", $e(baseAddr)))
    }
    for (p in perms) {
        var fnAddr = new ExprAddr(at = base.at, target := "{base.name}__{p.suffix}")
        body |> push <| qmacro_expr() {
            result |> push(($v(p.suffix), $e(fnAddr)))
        }
    }
    body |> push <| qmacro_expr() {
        return <- result
    }
    var fn = qmacro_function("{base.name}_variants") $() : array<tuple<string; $t(sig)>> {
        $b(body)
    }
    fn.flags.generated = true
    if (!(mod |> add_function(fn))) {
        errors := "[tune] on {base.name}: failed to add {base.name}_variants"
        return false
    }
    return true
}

// ===== the annotations =====

//! `[tune_perm(<generator args>)]` — one grid row for the `tune(...)` annotation that must
//! follow it in the same bracket. The args are passed to the generator verbatim (they become
//! `[llvm_code]` annotation args, and fold into the JIT DLL cache key); `suffix="..."`
//! overrides the auto-derived variant name.
[function_macro(name = "tune_perm")]
class private TunePermAnnotation : AstFunctionAnnotation {
    def override apply(var func : FunctionPtr; var group : ModuleGroup;
                       args : AnnotationArgumentList; var errors : das_string) : bool {
        g_perm_rows[perm_key(func)] |> emplace(build_perm_row(args))
        return true
    }
}

//! `[tune_companion(fn = "sibling", gen = "generator_key")]` — stamps `sibling` with the SAME
//! perm as the tuned function, from the same manifest entry: the two-function stamp (e.g. a
//! GEMM kernel and its repack-layout query can never desync — including on JIT-time declines,
//! when both generators fall back to their reference bodies together). List companion rows
//! AFTER the [tune_perm] grid and BEFORE tune(...); the sibling is a plain function (no [tune]
//! of its own) declared earlier in the same module, with an explicit return type.
[function_macro(name = "tune_companion")]
class private TuneCompanionAnnotation : AstFunctionAnnotation {
    def override apply(var func : FunctionPtr; var group : ModuleGroup;
                       args : AnnotationArgumentList; var errors : das_string) : bool {
        // the perm bank doubles as the order guard: rows placed after tune(...) (bank already
        // consumed) or before any [tune_perm] would be silently ignored otherwise
        if (!(g_perm_rows |> key_exists(perm_key(func)))) {
            errors := "[tune_companion] on {func.name}: list it AFTER the [tune_perm] rows and BEFORE tune(...) in the same bracket"
            return false
        }
        var row : TuneCompanion
        let fv = find_arg(args, "fn")
        if (fv is tString) { row.fnname = fv as tString }
        let gv = find_arg(args, "gen")
        if (gv is tString) { row.genkey = gv as tString }
        if (empty(row.fnname) || empty(row.genkey)) {
            errors := "[tune_companion] on {func.name}: fn=\"<function>\" and gen=\"<generator key>\" are both required"
            return false
        }
        g_companion_rows[perm_key(func)] |> emplace(row)
        return true
    }
}

//! `[tune(gen="key", fallback="suffix")]` — LAST in a bracket of `[tune_perm]` rows (applies
//! run in declaration order; `tune` consumes the rows banked before it). Normal runs stamp
//! exactly one winner (manifest > fallback > reference); tune/test runs stamp the whole grid
//! as `<name>__<suffix>` stubs plus a `<name>_variants()` registry. See the module docstring
//! for the mode contract.
[function_macro(name = "tune")]
class private TuneAnnotation : AstFunctionAnnotation {
    def override apply(var func : FunctionPtr; var group : ModuleGroup;
                       args : AnnotationArgumentList; var errors : das_string) : bool {
        let gv = find_arg(args, "gen")
        if (!(gv is tString) || empty(gv as tString)) {
            errors := "[tune] on {func.name}: gen=\"<[llvm_code] generator key>\" is required"
            return false
        }
        let genKey = gv as tString
        var perms <- take_perms(func, errors)
        if (empty(errors) && empty(perms)) {
            errors := "[tune] on {func.name}: no [tune_perm(...)] rows — list them BEFORE tune(...) in the same annotation bracket"
        }
        var comps <- take_companions(func, errors)
        if (!empty(errors)) {
            delete perms
            delete comps
            return false
        }
        if (func.result.baseType == Type.autoinfer) {
            // function_to_type runs pre-infer: an implicit result type reaches the
            // variants registry as `auto` and its rows fail to unify
            errors := "[tune] on {func.name}: an explicit return type is required (add ': void' or the real type)"
            delete perms
            delete comps
            return false
        }
        // AOT is tune-free by contract — reference bodies only, registries emitted so harness
        // code compiles. Overrides grid modes too: a stale DAS_TUNE_MODE env must not leak
        // variant stubs into generated C++. (-exe is NOT gated here: an exe ships the box's
        // manifest winners — local-use build — or the generic fallback= stamps without one.)
        if (tune_aot_gate()) {
            let noPerms : array<TunePerm>
            var gok = emit_registry(compiling_module(), func, noPerms, errors)
            for (c in comps) {
                if (gok) {
                    gok = emit_registry(compiling_module(), c.fn, noPerms, errors)
                }
            }
            delete perms
            delete comps
            return gok
        }
        let mode = tune_mode()
        if (mode == "tune" || mode == "test") {
            let ok = stamp_grid(func, genKey, perms, comps, errors)
            delete perms
            delete comps
            return ok
        }
        if (mode != "normal") {
            errors := "[tune] on {func.name}: unknown DAS_TUNE_MODE '{mode}' (normal | tune | test)"
            delete perms
            delete comps
            return false
        }
        // normal: manifest entry > fallback= > reference. The manifest is the env override
        // when set, else the declaring module's [tune_scope] per-box file. A manifest with
        // no entry for this function falls back to the declared fallback= (a manifest written
        // before a kernel family landed must not silently drop that family to the reference
        // tier); an explicit "reference" entry forces the original body. An app's
        // [tune_manifest] declaration lives in the root module, which compiles after every
        // library [tune] — its apply re-stamps the tuned functions from the declared manifest
        // (see TuneManifestAnnotation below).
        let fname = "{func.name}"
        var manifestFound = false
        var mpath = get_env_variable("DAS_TUNE_MANIFEST")
        if (empty(mpath)) {
            mpath = scope_manifest_for("{compiling_module().name}")
        }
        var manifest <- read_manifest(mpath, manifestFound)
        var suffix = ""
        if (manifestFound) {
            suffix = manifest?[fname] ?? ""
        }
        let fromManifest = !empty(suffix)
        var ok = true
        if (empty(suffix)) {
            // fallback= is a ';'-chain tried in declaration order: the first perm whose
            // requires= hint passes on this box (per-ISA defaults — a manifest-less box
            // still lands on its ISA's known-good row instead of the reference tier).
            // Every listed suffix must exist in the grid; none eligible => reference.
            let fv = find_arg(args, "fallback")
            if (fv is tString) {
                for (cand in split(fv as tString, ";")) {
                    continue if (empty(cand))
                    var found = false
                    for (p in perms) {
                        if (p.suffix == cand) {
                            found = true
                            if (perm_requires_ok(p)) {
                                suffix = cand
                            }
                            break
                        }
                    }
                    if (!found) {
                        errors := "[tune] on {func.name}: fallback perm '{cand}' is not in the [tune_perm] grid"
                        ok = false
                    }
                    break if (!ok || !empty(suffix))
                }
            }
        }
        delete manifest
        if (ok && !empty(suffix) && suffix != "reference") {
            ok = false
            for (p in perms) {
                if (p.suffix == suffix) {
                    stamp_llvm_code(func, genKey, p, fromManifest ? mpath : "")
                    for (c in comps) {
                        stamp_llvm_code(c.fn, c.genkey, p, fromManifest ? mpath : "")
                    }
                    print("llvm_tune: {fname} <- {suffix} ({fromManifest ? mpath : "fallback"})\n")
                    ok = true
                    break
                }
            }
            if (!ok) {
                errors := "[tune] on {func.name}: perm '{suffix}' is not in the [tune_perm] grid"
            }
        }
        // reference-row-only registries (base + companions), so harness code referencing
        // <name>_variants() compiles (and lints) in every mode — the perm stubs themselves
        // exist only in tune/test runs
        if (ok) {
            let noPerms : array<TunePerm>
            ok = emit_registry(compiling_module(), func, noPerms, errors)
            for (c in comps) {
                if (ok) {
                    ok = emit_registry(compiling_module(), c.fn, noPerms, errors)
                }
            }
        }
        delete perms
        delete comps
        return ok
    }
}

// ===== [tune_manifest] — the app's per-app manifest declaration =====

// [init] in the declaring module so the runtime write API targets the declared file; shared
// by [tune_manifest] (root module) and [tune_scope] (library module) — one per module
def private inject_runtime_path_init(mpath : string; var errors : das_string) : bool {
    var fn = qmacro_function("`tune`manifest`runtime`init") $() : void {
        set_tune_manifest_runtime_path($v(mpath))
    }
    fn |> append_annotation("$", "init")
    fn.flags.generated = true
    if (!(compiling_module() |> add_function(fn))) {
        errors := "[tune_manifest]/[tune_scope]: duplicate declaration (one per module)"
        return false
    }
    return true
}

def private strip_llvm_code(var fn : FunctionPtr) {
    var i = length(fn.annotations) - 1
    while (i >= 0) {
        if (fn.annotations[i].annotation.name == "llvm_code") {
            fn.annotations |> erase(i)
        }
        i--
    }
}

// re-stamp one tuned function from the declared manifest: the grid, generator key and
// companions are re-read from its attached [tune]/[tune_perm]/[tune_companion] declarations,
// the fallback [llvm_code] stamps are dropped (companions included), and the manifest entry
// is stamped onto the function and its companions. NO entry keeps the [tune]-time stamps
// (fallback= or reference) untouched — a manifest written before this kernel family landed
// must not silently drop it to the reference tier; an explicit "reference" entry forces the
// original body.
def private restamp_fn(var fn : FunctionPtr; mod : Module?; manifest : table<string; string>; mpath : string; var errors : das_string) {
    let fname = "{fn.name}"
    let suffix = manifest?[fname] ?? ""
    if (empty(suffix)) {
        return
    }
    var genKey = ""
    var rows : array<TunePerm>
    var comps : array<TuneCompanion>
    for (ann in fn.annotations) {
        if (ann.annotation.name == "tune") {
            let gv = find_arg(ann.arguments, "gen")
            if (gv is tString) { genKey = gv as tString }
        } elif (ann.annotation.name == "tune_perm") {
            rows |> emplace(build_perm_row(ann.arguments))
        } elif (ann.annotation.name == "tune_companion") {
            var c : TuneCompanion
            let fv = find_arg(ann.arguments, "fn")
            if (fv is tString) { c.fnname = fv as tString }
            let gv = find_arg(ann.arguments, "gen")
            if (gv is tString) { c.genkey = gv as tString }
            c.fn = mod |> find_unique_function(c.fnname, true)  // validated at the [tune] apply
            if (c.fn != null) {
                comps |> emplace(c)
            }
        }
    }
    strip_llvm_code(fn)
    for (c in comps) {
        strip_llvm_code(c.fn)
    }
    if (suffix != "reference") {
        var stamped = false
        for (p in rows) {
            if (p.suffix == suffix) {
                stamp_llvm_code(fn, genKey, p, mpath)
                for (c in comps) {
                    stamp_llvm_code(c.fn, c.genkey, p, mpath)
                }
                print("llvm_tune: {fname} <- {suffix} ({mpath})\n")
                stamped = true
                break
            }
        }
        if (!stamped) {
            errors := "[tune_manifest]: perm '{suffix}' for {fname} is not in its [tune_perm] grid"
        }
    }
    delete rows
    delete comps
}

def private restamp_module(var mod : Module?; manifest : table<string; string>; mpath : string; var errors : das_string) {
    var tuned : array<FunctionPtr>
    for_each_function(mod, "") $(fn) {
        for (ann in fn.annotations) {
            if (ann.annotation.name == "tune") {
                tuned |> push(fn)
                break
            }
        }
    }
    for (fn in tuned) {
        restamp_fn(fn, mod, manifest, mpath, errors)
    }
}

// The [tune_manifest] re-stamp. Restricted to the DECLARING (root) module ON PURPOSE: mutating
// a REQUIRED module's already-compiled [tune] function is a cross-module mutation that trips the
// re-infer pass (see restamp_fn), so walking the whole program here would let an app-manifest
// entry for a library kernel crash the compile. Library kernels take their manifest winners at
// [tune] time instead (DAS_TUNE_MANIFEST env / [tune_scope]), which is cross-module-safe; policy
// auto/--tune re-exec into a fresh compile for the same reason. So [tune_manifest] overrides
// only the app's OWN [tune] functions; entries naming a required module's kernel are inert.
def private restamp_root_module(manifest : table<string; string>; mpath : string; var errors : das_string) {
    restamp_module(compiling_module(), manifest, mpath, errors)
}

//! `[tune_manifest(name = "myapp", dir = "...")]` on the app's `main` (any function in the
//! root file): opts the app into a tune manifest at `<dir>/<name>.tune.json`. `dir` resolves
//! against the declaring file's directory (absolute dirs pass through; omitted dir = the
//! declaring file's directory), so two apps sharing a folder pick distinct names. In normal
//! mode this apply re-stamps the app's OWN `[tune]` functions from the declared manifest — only
//! the root module, since re-stamping a required library's compiled `[tune]` is cross-module
//! and unsafe (see `restamp_root_module`); a manifest entry naming a library kernel is inert
//! (override those via `DAS_TUNE_MANIFEST` env or `[tune_scope]`). No entry for a function keeps
//! its `[tune]`-time stamp (fallback= or reference) — a stale manifest must not drop a new
//! kernel family to the reference tier; an explicit "reference" entry forces the original body.
//! Without the file the `fallback=` stamps stand. `DAS_TUNE_MANIFEST` overrides the declaration
//! entirely. Also injects an [init] pointing the runtime write API (`tune_manifest_set`) at the
//! same file.
[function_macro(name = "tune_manifest")]
class private TuneManifestAnnotation : AstFunctionAnnotation {
    def override apply(var func : FunctionPtr; var group : ModuleGroup;
                       args : AnnotationArgumentList; var errors : das_string) : bool {
        // AOT is tune-free by contract — no init injection, no restamp
        if (tune_aot_gate()) return true
        let nv = find_arg(args, "name")
        if (!(nv is tString) || empty(nv as tString)) {
            errors := "[tune_manifest] on {func.name}: name=\"<app name>\" is required"
            return false
        }
        let declDir = dir_name(string(func.at.fileInfo.name))
        var dir = declDir
        let dv = find_arg(args, "dir")
        if (dv is tString) {
            let d = dv as tString
            dir = is_absolute(d) ? d : path_join(declDir, d)
        }
        let mpath = path_join(dir, "{nv as tString}.tune.json")
        if (!inject_runtime_path_init(mpath, errors)) {
            return false
        }
        // env override: every [tune] already stamped from it; grid modes stamp every perm
        if (!empty(get_env_variable("DAS_TUNE_MANIFEST")) || tune_mode() != "normal") return true
        var found = false
        var manifest <- read_manifest(mpath, found)
        if (found) {
            restamp_root_module(manifest, mpath, errors)
        }
        delete manifest
        return empty(errors)
    }
}

// ===== [tune_scope] / [tune_policy] — the per-box UX rail =====

def private resolve_decl_path(declFile : string; p : string) : string {
    return is_absolute(p) ? p : path_join(dir_name(declFile), p)
}

//! `[tune_scope(name = "mylib", tuner = "harness.das")]` on a (dummy) struct in the library
//! module that owns the `[tune]` functions, declared ABOVE them: opts that module's kernels
//! into a per-box shared manifest at `<das_root>/<name>.tune.json` — every app requiring the
//! library shares the same winners with no app-side declaration. `tuner=` (optional) names
//! the harness that produces the manifest, resolved against the declaring file;
//! `[tune_policy]` and `--tune` run it. `DAS_TUNE_MANIFEST` still overrides everything; an
//! app `[tune_manifest]` still re-stamps on top (its entries win, missing entries keep the
//! scope winners). Also points the runtime write API (`tune_manifest_set`) at the scope file,
//! so a manual `DAS_TUNE_MODE=tune` harness run lands winners in the right place by default.
[structure_macro(name = "tune_scope")]
class private TuneScopeAnnotation : AstStructureAnnotation {
    def override apply(var st : StructurePtr; var group : ModuleGroup;
                       args : AnnotationArgumentList; var errors : das_string) : bool {
        if (tune_aot_gate()) return true
        let nv = find_arg(args, "name")
        if (!(nv is tString) || empty(nv as tString)) {
            errors := "[tune_scope]: name=\"<scope name>\" is required"
            return false
        }
        let sname = nv as tString
        var tuner = ""
        let tv = find_arg(args, "tuner")
        if (tv is tString) {
            tuner = resolve_decl_path(string(st.at.fileInfo.name), tv as tString)
        }
        let mpath = path_join(get_das_root(), "{sname}.tune.json")
        // overwrite, not error: shared-module macro state persists across compiles in one process
        g_scopes["{compiling_module().name}"] = TuneScope(scopeName = sname, manifestPath = mpath, tunerPath = tuner)
        return inject_runtime_path_init(mpath, errors)
    }
}

// `--tune` after `--` on the app's command line — visible at macro time (the compiler argv
// carries the script args)
def private cli_forces_tune() : bool {
    var r = false
    var afterDD = false
    // NO delete: the builtin aliases a process-global Array header (locked), not a copy
    var argv <- get_command_line_arguments()
    for (a in argv) {
        if (afterDD && a == "--tune") {
            r = true
        }
        if (a == "--") {
            afterDD = true
        }
    }
    return r
}

// the exact command a user (or the auto path) runs to tune one scope; the env prefix leads
// so the command never starts with a quote (cmd.exe strips a leading quote)
def private tuner_cmd(scope : TuneScope) : string {
    let win = get_platform_name() == "windows"
    // quote the env values: <das_root> (hence the manifest path) can contain spaces — on POSIX
    // an unquoted VAR=/a b/x.json splits the assignment; Windows `set "VAR=..."` is the safe form.
    let envs = (win ?
        "set \"DAS_TUNE_MODE=tune\"&& set \"DAS_TUNE_MANIFEST={scope.manifestPath}\"&& " :
        "DAS_TUNE_MODE=tune DAS_TUNE_MANIFEST=\"{scope.manifestPath}\" ")
    return "{envs}\"{get_das_exe()}\" -jit \"{scope.tunerPath}\" -dasroot \"{get_das_root()}\""
}

// spawn the scope's tuner to completion, relaying its output — RUNTIME only (the auto and
// restart guards); never from macro context, where a daslang child cannot run mid-compile
def private run_scope_tuner(scope : TuneScope) : bool {
    let tmp = path_join(get_das_root(), "_tune_{scope.scopeName}_out.txt")
    let cmd = "{tuner_cmd(scope)} > \"{tmp}\" 2>&1"
    print("llvm_tune: tuning scope '{scope.scopeName}' -> {scope.manifestPath}\nllvm_tune: {cmd}\n")
    unsafe(popen(cmd) $(_f) {})
    let outp = fread(tmp)
    remove(tmp)
    print("{outp}\n")
    return true
}

// runtime accumulators for the auto/--tune guard: how many scopes just got tuned, and the
// re-exec'd child's exit code
var private g_tuned_scopes = 0
var private g_reexec_code = 0

// "tuned" for the runtime guards means the SAME thing the compile-time [tune] gate means: a
// manifest that exists AND parses (read_manifest's `found`). A stray empty / half-written /
// corrupt file must NOT read as tuned — otherwise the guard no-ops while the compile fell back
// to fallback stamps, and the app can never self-heal.
def private manifest_present(path : string) : bool {
    var found = false
    var m <- read_manifest(path, found)
    delete m
    return found
}

//! Runtime half of `[tune_policy(missing = "auto")]` / `--tune` — injected at the top of the
//! app's `main`, one call per scope, followed by `tune_auto_reexec()`. Runs the scope's tuner
//! when the manifest is missing (unconditionally under `--tune`); tuning happens at RUNTIME
//! because the winners are compile-time stamps — this process compiled without them, and the
//! re-exec that follows picks them up in a fresh compile.
def tune_auto_prepare(scopeName : string; manifestPath : string; tunerPath : string; force : bool) {
    if (!force && manifest_present(manifestPath)) {
        return
    }
    print("llvm_tune: scope '{scopeName}' {force ? "re-tuning (--tune)" : "is untuned on this box — tuning now"}\n")
    run_scope_tuner(TuneScope(scopeName = scopeName, manifestPath = manifestPath, tunerPath = tunerPath))
    if (manifest_present(manifestPath)) {
        g_tuned_scopes++
    } else {
        print("llvm_tune: tuner produced no manifest at {manifestPath}\n")
    }
}

//! Relaunch the current process so a fresh compile stamps the just-written manifests (the
//! winners are compile-time stamps — they cannot be adopted mid-run). Relays the child's
//! output; `--tune` is stripped from the relaunch, so the child converges (its manifests are
//! present) instead of looping. Returns true when the child ran and main must return
//! immediately — `tune_reexec_code()` is its exit code.
def tune_auto_reexec() : bool {
    if (g_tuned_scopes == 0) {
        return false
    }
    // aliases a process-global Array header — do not delete
    var argv <- get_command_line_arguments()
    var args : array<string>
    args |> reserve(length(argv))
    for (a in argv) {
        if (a != "--tune") {
            args |> push("{a}")
        }
    }
    print("llvm_tune: re-launching to apply the fresh manifests\n")
    var rc : int
    unsafe {
        rc = popen_argv(args, 0.0) $(f) {
            if (f != null) {
                while (!feof(f)) {
                    print(fgets(f))
                }
            }
        }
    }
    delete args
    g_reexec_code = rc
    return true
}

//! The re-exec'd child's exit code — what an `int` main returns after `tune_auto_reexec()`.
def tune_reexec_code() : int {
    return g_reexec_code
}

//! Runtime half of `[tune_policy(missing = "restart")]` — injected as a guard at the top of
//! the app's `main`. When the scope manifest is missing: runs the tuner NOW, prints the
//! restart banner, and returns true so main returns immediately (the winners are
//! compile-time stamps — this process compiled without them). False = manifest present,
//! carry on.
def tune_restart_needed(scopeName : string; manifestPath : string; tunerPath : string) : bool {
    if (manifest_present(manifestPath)) {
        return false
    }
    print("llvm_tune: scope '{scopeName}' is untuned on this box\n")
    if (empty(tunerPath)) {
        print("llvm_tune: no tuner declared — produce {manifestPath} with the library's tuner, then restart\n")
        return true
    }
    run_scope_tuner(TuneScope(scopeName = scopeName, manifestPath = manifestPath, tunerPath = tunerPath))
    if (manifest_present(manifestPath)) {
        print("llvm_tune: scope '{scopeName}' tuned -> {manifestPath}\nllvm_tune: restart to apply the winners\n")
    } else {
        print("llvm_tune: tuner produced no manifest at {manifestPath}\n")
    }
    return true
}

// final stamped truth per [tune] function, read off the AST (the tune_suffix/tune_from args
// stamp_llvm_code records) — no macro-state bank, so shared-context reuse across compiles
// can't pollute it
def private collect_status() : array<TuneStatus> {
    var rows : array<TuneStatus>
    let env = get_env_variable("DAS_TUNE_MANIFEST")
    program_for_each_module(compiling_program()) $(mod) {
        let modName = "{mod.name}"
        var scopeName = ""
        var scopePath = ""
        if (g_scopes |> key_exists(modName)) {
            scopeName = g_scopes[modName].scopeName
            scopePath = g_scopes[modName].manifestPath
        }
        for_each_function(mod, "") $(fn) {
            var isTuned = false
            var suffix = ""
            var from = ""
            for (ann in fn.annotations) {
                if (ann.annotation.name == "tune") {
                    isTuned = true
                } elif (ann.annotation.name == "llvm_code") {
                    let sv = find_arg(ann.arguments, "tune_suffix")
                    if (sv is tString) { suffix = sv as tString }
                    let fv = find_arg(ann.arguments, "tune_from")
                    if (fv is tString) { from = fv as tString }
                }
            }
            if (isTuned) {
                let source = empty(suffix) ? "reference" : (empty(from) ? "fallback" : "manifest")
                let mpath = !empty(from) ? from : (!empty(env) ? env : scopePath)
                rows |> push(TuneStatus(fname = "{fn.name}", scope = scopeName,
                    suffix = suffix, source = source, manifestPath = mpath))
            }
        }
    }
    return <- rows
}

//! `[tune_policy(missing = "...")]` on the app's `main` (must be `main` for auto/restart —
//! they prepend a guard to its body): what to do about `[tune_scope]`s whose per-box
//! manifest is missing at compile time —
//!   fallback: stamp `fallback=` silently (the default everywhere, also without this annotation)
//!   warn:    loud compile-time banner with the exact tuner command
//!   error:   fail the compile with the same message — the dev mode
//!   auto:    tune at startup (injected guard runs each missing scope's tuner), then RE-EXEC
//!            the process — the fresh compile stamps the winners; one launch, then it serves.
//!            (Tuning cannot happen mid-compile: the tuner is a daslang child, and adopting
//!            its winners means new compile-time stamps anyway.)
//!   restart: like auto but no re-exec — tune at startup, then exit asking for a manual
//!            restart (one missing scope per start)
//! `--tune` after `--` on the app's command line forces the auto path even when the manifests
//! exist (re-tune; the flag is stripped from the re-exec). `DAS_TUNE_POLICY` env overrides
//! the declared value (CI kill switch: `DAS_TUNE_POLICY=fallback`). Grid modes
//! (`DAS_TUNE_MODE=tune`/`test` — also the recursion guard for the spawned tuner), a
//! `DAS_TUNE_MANIFEST` env override, and standalone builds (`-exe`, AOT) skip policy entirely.
[function_macro(name = "tune_policy")]
class private TunePolicyAnnotation : AstFunctionAnnotation {
    def override apply(var func : FunctionPtr; var group : ModuleGroup;
                       args : AnnotationArgumentList; var errors : das_string) : bool {
        // AOT and -exe builds run no policy (a frozen artifact must not demand or run
        // tuning); grid-mode children manage their own manifest (and the spawned tuner
        // compiles in tune mode — the recursion guard); a DAS_TUNE_MANIFEST env override
        // means the user drives manually
        if (tune_aot_gate() || tune_exe_gate() || tune_mode() != "normal"
                || !empty(get_env_variable("DAS_TUNE_MANIFEST"))) {
            return true
        }
        var policy = "warn"
        let mv = find_arg(args, "missing")
        if (mv is tString) {
            policy = mv as tString
        }
        let penv = get_env_variable("DAS_TUNE_POLICY")
        if (!empty(penv)) {
            policy = penv
        }
        if (policy != "fallback" && policy != "warn" && policy != "error" && policy != "auto" && policy != "restart") {
            errors := "[tune_policy] on {func.name}: missing=\"{policy}\" — use fallback | warn | error | auto | restart"
            return false
        }
        let force = cli_forces_tune()
        if (force && empty(g_scopes)) {
            print("llvm_tune: --tune requested but no [tune_scope] is declared by any required library\n")
        }
        // snapshot: values() locks the table for the loop's duration, and the body reads
        // g_scopes indirectly (the [] op is insert-capable — it trips the lock even on hits)
        var scopes <- [for (scope in values(g_scopes)); scope]
        var seen : table<string>
        var autoScopes : array<TuneScope>
        for (scope in scopes) {
            continue if (seen |> key_exists(scope.scopeName))
            seen |> insert(scope.scopeName)
            var found = false
            var manifest <- read_manifest(scope.manifestPath, found)
            delete manifest
            continue if (found && !force)
            if (force || policy == "auto") {
                // NO tuner run and NO restamp at compile time: the tuner is a daslang child
                // (can't run mid-compile), and restamping a REQUIRED module's compiled
                // function is a cross-module mutation the re-infer pass can't survive.
                // Instead a runtime guard tunes and RE-EXECS — the fresh compile stamps the
                // winners at [tune] time, which is cross-module-safe.
                if (empty(scope.tunerPath)) {
                    errors := "[tune_policy]: scope '{scope.scopeName}' declares no tuner= — cannot {force ? "--tune" : "auto-tune"}; produce {scope.manifestPath} manually"
                } else {
                    autoScopes |> push(scope)
                }
            } elif (policy == "error") {
                errors := "[tune_policy]: scope '{scope.scopeName}' is untuned on this box — run: {empty(scope.tunerPath) ? "<no tuner declared>" : tuner_cmd(scope)} (or start with --tune)"
            } elif (policy == "warn") {
                print("llvm_tune: WARNING scope '{scope.scopeName}' is untuned on this box (fallback stamps in effect)\nllvm_tune: run: {empty(scope.tunerPath) ? "<no tuner declared>" : tuner_cmd(scope)} (or start with --tune)\n")
            } elif (policy == "restart") {
                // prepend a graceful guard to the annotated function (main) — a hard exit()
                // from an [init] would skip environment shutdown (g_envTotal FATAL at exit)
                if (!(func.body is ExprBlock)) {
                    errors := "[tune_policy]: restart — {func.name} has no body block"
                } elif (func.result.baseType != Type.tVoid && func.result.baseType != Type.tInt
                        && func.result.baseType != Type.autoinfer) {
                    // autoinfer = undeclared result, void by convention for main
                    errors := "[tune_policy]: restart — {func.name} must return void or int"
                } else {
                    var guard : ExpressionPtr
                    if (func.result.baseType == Type.tInt) {
                        guard = qmacro_expr() {
                            if (tune_restart_needed($v(scope.scopeName), $v(scope.manifestPath), $v(scope.tunerPath))) {
                                return 3
                            }
                        }
                    } else {
                        guard = qmacro_expr() {
                            if (tune_restart_needed($v(scope.scopeName), $v(scope.manifestPath), $v(scope.tunerPath))) {
                                return
                            }
                        }
                    }
                    var blk = unsafe(reinterpret<ExprBlock?>(func.body))
                    blk.list |> push(guard, 0)
                }
            }
            break if (!empty(errors))
        }
        delete seen
        delete scopes
        // the auto/--tune guard: prepend one tune_auto_prepare per scope, then the re-exec —
        // execution order is prepare(s) first, re-exec last, ahead of the original body
        if (empty(errors) && !empty(autoScopes)) {
            if (!(func.body is ExprBlock)) {
                errors := "[tune_policy]: {func.name} has no body block"
            } elif (func.result.baseType != Type.tVoid && func.result.baseType != Type.tInt
                    && func.result.baseType != Type.autoinfer) {
                // autoinfer = undeclared result, void by convention for main
                errors := "[tune_policy]: auto/--tune — {func.name} must return void or int"
            } else {
                var guards : array<ExpressionPtr>
                guards |> reserve(length(autoScopes) + 1)
                for (scope in autoScopes) {
                    guards |> push <| qmacro_expr() {
                        tune_auto_prepare($v(scope.scopeName), $v(scope.manifestPath), $v(scope.tunerPath), $v(force))
                    }
                }
                if (func.result.baseType == Type.tInt) {
                    guards |> push <| qmacro_expr() {
                        if (tune_auto_reexec()) {
                            return tune_reexec_code()
                        }
                    }
                } else {
                    guards |> push <| qmacro_expr() {
                        if (tune_auto_reexec()) {
                            return
                        }
                    }
                }
                var blk = unsafe(reinterpret<ExprBlock?>(func.body))
                var gi = length(guards) - 1
                while (gi >= 0) {
                    blk.list |> push(guards[gi], 0)
                    gi--
                }
            }
        }
        delete autoScopes
        // the runtime status table: one tune_status_add per [tune] function — with auto now
        // tuning at runtime the rows always reflect this compile's [tune]-time stamps
        if (empty(errors)) {
            var rows <- collect_status()
            if (!empty(rows)) {
                var body : array<ExpressionPtr>
                body |> reserve(length(rows))
                for (row in rows) {
                    body |> push <| qmacro_expr() {
                        tune_status_add($v(row.fname), $v(row.scope), $v(row.suffix),
                            $v(row.source), $v(row.manifestPath))
                    }
                }
                var fn = qmacro_function("`tune`status`init") $() : void {
                    $b(body)
                }
                fn |> append_annotation("$", "init")
                fn.flags.generated = true
                if (!(compiling_module() |> add_function(fn))) {
                    errors := "[tune_policy]: duplicate declaration (one per program)"
                }
            }
            delete rows
        }
        return empty(errors)
    }
}
