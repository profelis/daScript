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
        stamp_llvm_code(fclone, genKey, p)
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
            stamp_llvm_code(cclone, c.genkey, p)
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
        // normal: manifest entry > fallback= > reference. A manifest with no entry for this
        // function falls back to the declared fallback= (a manifest written before a kernel
        // family landed must not silently drop that family to the reference tier); an
        // explicit "reference" entry forces the original body. An app's [tune_manifest]
        // declaration lives in the root module, which compiles after every library [tune] —
        // its apply re-stamps the tuned functions from the declared manifest (see
        // TuneManifestAnnotation below).
        let fname = "{func.name}"
        var manifestFound = false
        var manifest <- read_manifest(get_env_variable("DAS_TUNE_MANIFEST"), manifestFound)
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
                    stamp_llvm_code(func, genKey, p)
                    for (c in comps) {
                        stamp_llvm_code(c.fn, c.genkey, p)
                    }
                    print("llvm_tune: {fname} <- {suffix} ({fromManifest ? tune_manifest_path() : "fallback"})\n")
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
                stamp_llvm_code(fn, genKey, p)
                for (c in comps) {
                    stamp_llvm_code(c.fn, c.genkey, p)
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
            restamp_fn(fn, mod, manifest, mpath, errors)
        }
    }
}

//! `[tune_manifest(name = "myapp", dir = "...")]` on the app's `main` (any function in the
//! root file): opts the app into a tune manifest at `<dir>/<name>.tune.json`. `dir` resolves
//! against the declaring file's directory (absolute dirs pass through; omitted dir = the
//! declaring file's directory), so two apps sharing a folder pick distinct names. The root
//! module compiles after every library `[tune]`, so in normal mode this apply re-stamps the
//! tuned functions from the declared manifest. No entry for a function keeps its
//! `[tune]`-time stamp (fallback= or reference) — a stale manifest must not drop a new
//! kernel family to the reference tier; an explicit "reference" entry forces the original
//! body. Without the file the `fallback=` stamps stand. `DAS_TUNE_MANIFEST` overrides the
//! declaration entirely. Also injects an [init] pointing the runtime write API
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
