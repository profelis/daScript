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
require strings
require llvm/daslib/llvm_code public

//! Generalized tune framework (gemm_generator_plan.md part 2). `[tune_perm(...), ...,
//! tune(gen="key", fallback="suffix")]` — perm rows first, `tune` last — turns one reference
//! function into a tuned `[llvm_code]` kernel family. `DAS_TUNE_MODE` selects the compile-time
//! mode:
//!  - normal (default): stamp exactly one winner onto the function itself — the manifest entry
//!    when a manifest exists (authoritative: no entry means reference body), else the
//!    `fallback=` perm, else the reference body. No variant stubs are emitted; the
//!    `<name>_variants()` registry still exists (reference row only) so harness code
//!    compiles in every mode.
//!  - tune / test: stamp the full grid as `<name>__<suffix>` clones plus a `<name>_variants()`
//!    registry; a harness benches them (tune, then `tune_manifest_set` the winner) or
//!    bit-exact-gates every variant against the reference row (test).

// ===== manifest + mode =====

//! Compile-time tune mode from the `DAS_TUNE_MODE` env var: "normal" (default), "tune", "test".
def tune_mode() : string {
    let m = get_env_variable("DAS_TUNE_MODE")
    return empty(m) ? "normal" : m
}

// runtime copy of the app's [tune_manifest] declaration, set by the injected [init]
var private g_runtime_manifest = ""

//! Runtime hook the `[tune_manifest]`-injected [init] calls; harnesses that manage their own
//! manifest location can also call it directly before using the get/set APIs.
def set_tune_manifest_runtime_path(p : string) {
    g_runtime_manifest = p
}

//! The tune manifest location: `DAS_TUNE_MANIFEST` env override, else the app's
//! `[tune_manifest]` declaration, else "" — no manifest. Per-app opt-in by design: a shared
//! default file would let unrelated apps stomp each other's winners.
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

// ===== the perm grid =====

struct private TunePerm {
    suffix : string
    args : array<tuple<argname : string; argvalue : RttiValue>>
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
        row.args |> emplace((argname = string(aa.name), argvalue = v))
    }
    if (empty(row.suffix)) {
        var pieces <- [for (a in row.args); suffix_piece(a.argname, a.argvalue)]
        row.suffix = join(pieces, "_")
        delete pieces
    }
    return <- row
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
def private stamp_llvm_code(var fn : FunctionPtr; genKey : string; perm : TunePerm) {
    var aargs : array<tuple<argname : string; argvalue : RttiValue>>
    aargs |> reserve(length(perm.args) + 1)
    aargs |> push((argname = "name", argvalue = RttiValue(tString = genKey)))
    for (a in perm.args) {
        aargs |> push((argname = a.argname, argvalue = a.argvalue))
    }
    fn |> append_annotation("llvm_code", "llvm_code", aargs)
    fn.sideEffectFlags.userScenario = true
    delete aargs
}

// tune/test modes: one `<base>__<suffix>` clone per perm, each carrying its [llvm_code] stamp,
// plus the `<base>_variants()` registry. The base function keeps its reference body — it is
// the oracle row. (Clones are annotation-free: the parsed declarations attach to the base
// only after every apply has run, which is after the clones are made.)
def private stamp_grid(var func : FunctionPtr; genKey : string; perms : array<TunePerm>; var errors : das_string) : bool {
    var mod = compiling_module()
    for (p in perms) {
        var fclone = clone_function(func)
        fclone.name := "{func.name}__{p.suffix}"
        stamp_llvm_code(fclone, genKey, p)
        fclone.flags.generated = true
        if (!(mod |> add_function(fclone))) {
            errors := "[tune] on {func.name}: failed to add variant {fclone.name}"
            return false
        }
    }
    return emit_registry(mod, func, perms, errors)
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
        if (!empty(errors)) {
            delete perms
            return false
        }
        if (func.result.baseType == Type.autoinfer) {
            // function_to_type runs pre-infer: an implicit result type reaches the
            // variants registry as `auto` and its rows fail to unify
            errors := "[tune] on {func.name}: an explicit return type is required (add ': void' or the real type)"
            delete perms
            return false
        }
        let mode = tune_mode()
        if (mode == "tune" || mode == "test") {
            let ok = stamp_grid(func, genKey, perms, errors)
            delete perms
            return ok
        }
        if (mode != "normal") {
            errors := "[tune] on {func.name}: unknown DAS_TUNE_MODE '{mode}' (normal | tune | test)"
            delete perms
            return false
        }
        // normal: an env-pinned manifest is authoritative when present; else fallback=.
        // An app's [tune_manifest] declaration lives in the root module, which compiles after
        // every library [tune] — its apply re-stamps the tuned functions from the declared
        // manifest (see TuneManifestAnnotation below).
        let fname = "{func.name}"
        var manifestFound = false
        var manifest <- read_manifest(get_env_variable("DAS_TUNE_MANIFEST"), manifestFound)
        var suffix = ""
        if (manifestFound) {
            suffix = manifest?[fname] ?? ""
        } else {
            let fv = find_arg(args, "fallback")
            if (fv is tString) { suffix = fv as tString }
        }
        delete manifest
        var ok = true
        if (!empty(suffix) && suffix != "reference") {
            ok = false
            for (p in perms) {
                if (p.suffix == suffix) {
                    stamp_llvm_code(func, genKey, p)
                    print("llvm_tune: {fname} <- {suffix} ({manifestFound ? tune_manifest_path() : "fallback"})\n")
                    ok = true
                    break
                }
            }
            if (!ok) {
                errors := "[tune] on {func.name}: perm '{suffix}' is not in the [tune_perm] grid"
            }
        }
        // reference-row-only registry, so harness code referencing <name>_variants() compiles
        // (and lints) in every mode — the perm stubs themselves exist only in tune/test runs
        if (ok) {
            let noPerms : array<TunePerm>
            ok = emit_registry(compiling_module(), func, noPerms, errors)
        }
        delete perms
        return ok
    }
}

// ===== [tune_manifest] — the app's per-app manifest declaration =====

// [init] in the declaring module so the runtime write API targets the declared file
def private inject_runtime_path_init(mpath : string; var errors : das_string) : bool {
    var fn = qmacro_function("`tune`manifest`runtime`init") $() : void {
        set_tune_manifest_runtime_path($v(mpath))
    }
    fn |> append_annotation("$", "init")
    fn.flags.generated = true
    if (!(compiling_module() |> add_function(fn))) {
        errors := "[tune_manifest]: duplicate declaration (only one per program)"
        return false
    }
    return true
}

// re-stamp one tuned function from the declared manifest: the grid and generator key are
// re-read from its attached [tune]/[tune_perm] declarations, the fallback [llvm_code] stamp
// is dropped, and the manifest entry — authoritative while the manifest exists — is stamped
def private restamp_fn(var fn : FunctionPtr; manifest : table<string; string>; mpath : string; var errors : das_string) {
    var genKey = ""
    var rows : array<TunePerm>
    for (ann in fn.annotations) {
        if (ann.annotation.name == "tune") {
            let gv = find_arg(ann.arguments, "gen")
            if (gv is tString) { genKey = gv as tString }
        } elif (ann.annotation.name == "tune_perm") {
            rows |> emplace(build_perm_row(ann.arguments))
        }
    }
    var i = length(fn.annotations) - 1
    while (i >= 0) {
        if (fn.annotations[i].annotation.name == "llvm_code") {
            fn.annotations |> erase(i)
        }
        i--
    }
    let fname = "{fn.name}"
    let suffix = manifest?[fname] ?? ""
    if (!empty(suffix) && suffix != "reference") {
        var stamped = false
        for (p in rows) {
            if (p.suffix == suffix) {
                stamp_llvm_code(fn, genKey, p)
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
}

def private restamp_program(manifest : table<string; string>; mpath : string; var errors : das_string) {
    program_for_each_module(compiling_program()) $(mod) {
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
            restamp_fn(fn, manifest, mpath, errors)
        }
    }
}

//! `[tune_manifest(name = "myapp", dir = "...")]` on the app's `main` (any function in the
//! root file): opts the app into a tune manifest at `<dir>/<name>.tune.json`. `dir` resolves
//! against the declaring file's directory (absolute dirs pass through; omitted dir = the
//! declaring file's directory), so two apps sharing a folder pick distinct names. The root
//! module compiles after every library `[tune]`, so in normal mode this apply re-stamps the
//! tuned functions from the declared manifest — authoritative while the file exists (no entry
//! means reference body); without the file the `fallback=` stamps stand. `DAS_TUNE_MANIFEST`
//! overrides the declaration entirely. Also injects an [init] pointing the runtime write API
//! (`tune_manifest_set`) at the same file.
[function_macro(name = "tune_manifest")]
class private TuneManifestAnnotation : AstFunctionAnnotation {
    def override apply(var func : FunctionPtr; var group : ModuleGroup;
                       args : AnnotationArgumentList; var errors : das_string) : bool {
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
            restamp_program(manifest, mpath, errors)
        }
        delete manifest
        return empty(errors)
    }
}
