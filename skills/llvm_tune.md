# llvm_tune — the `[tune]` kernel-tuning framework

Read before touching `modules/dasLLVM/daslib/llvm_tune.das`, adding a `[tune]` kernel family,
wiring a library into a per-box tune scope, or giving an app a tune policy. Full user-facing
reference: `doc/source/reference/tune.rst`. Worked application: `modules/dasLLAMA/tune_for_this_box.md`.

## What it is

Turns one reference function into a tuned `[llvm_code]` kernel family: a grid of generator
permutations, a per-box manifest recording which one wins, and a policy rail. Winners are
**compile-time stamps** — the front end reads the manifest and stamps the winning perm onto the
function before codegen. The generator only fires under the LLVM JIT (`-jit`); every other tier
runs the reference body.

## The annotation set

- `[tune_perm(<gen args>)]` — one grid row; args pass to the generator + fold into the JIT DLL key. `suffix=` renames; `requires=` is a fallback-eligibility hint.
- `[tune(gen="key", fallback="suffix;chain")]` — closes the perm bracket (applies run in declaration order). Needs an explicit return type. `fallback=` is a `;`-chain, first `requires=`-passing perm wins; `reference` forces the original body.
- `[tune_companion(fn="sibling", gen="key")]` — between the perms and `tune()`; stamps a sibling with the SAME perm from the same entry (two-function coherence).
- `[tune_scope(name="lib", tuner="rel/path.das")]` — on a dummy struct in the **library** module owning the kernels; manifest at `<das_root>/<name>.tune.json`, shared by every app requiring the lib, no app declaration needed. `tuner=` resolves against the declaring file.
- `[tune_policy(missing = fallback|warn|error|auto|restart)]` — on the app's `main`. `error` = dev mode (fail compile, print tuner cmd). `auto` = tune at runtime + re-exec. `DAS_TUNE_POLICY` env overrides.
- `[tune_manifest(name=, dir=)]` — per-app manifest override (isolation escape hatch).
- `tune_status()` — runtime rows (fname, suffix, source manifest/fallback/reference, scope, path); populated when `[tune_policy]` is present. Log at startup.

## The load-bearing facts (learned the hard way)

- **Tuning cannot run mid-compile.** The tuner is a separate daslang process; you cannot spawn it during a macro apply and adopt its winners in the same compile. `auto`/`--tune` therefore tune at **runtime** (a guard prepended to `main`) then **re-exec** the process — the fresh compile stamps the winners at `[tune]` time. This is why `auto` needs `main` to return void or int and re-launches via `popen_argv`.
- **Cross-module restamp is broken.** Mutating a *required* library's already-compiled `[tune]` function from the root apply (strip+restamp `[llvm_code]`) trips the re-infer pass (`Function::visit` AV). So `restamp_program` (the `[tune_manifest]` rail) is proven only **same-module**. Library kernels must take winners at `[tune]` time via `[tune_scope]`/`DAS_TUNE_MANIFEST`, NOT via a post-hoc restamp. The re-exec model exists precisely to avoid this.
- **`find_module(name)` resolves against `this_program()`** — the *runtime* program, NULL in macro context → null-`Program` AV. In a macro use `compiling_program()` (walk it) or `find_compiling_module(name)`, never `find_module(name)`.
- **`get_command_line_arguments()` aliases a process-global locked Array** — never `delete` it.
- **`--tune` is read at macro time** from the compiler argv (after `--`), and stripped from the re-exec so the child converges instead of looping.
- **Gates:** cross-box artifacts (`policies.tune_frozen` — set by the `-aot` driver and dastest's AST serializer) are fully tune-free, and AOT-consuming runs (`policies.aot`) only when the JIT is off (a stamp changes the semantic hash → AOT link fails; under `-jit` the JIT supersedes AOT bodies, stamps stay live). `aot_module` is NOT a tune signal (it means "module-shaped compile" — dastest sets it on every test compile and the serializer needs it). `-exe` (`jit_exe_mode`) still STAMPS (an exe next to a manifest ships those winners; else the generic fallback) but the policy rail is dead. Split as `tune_aot_gate()` vs `tune_exe_gate()`. **Emission half (fixed 2026-07-12):** a native `-exe` carrying any `[llvm_code]` kernel computes the target flags WITH host features and targets the host machine — decided ONCE before the flag pass in `run_jit` (`exe_host_cpu`) and used at `init_jit_target_flags`/`init_jit`/`write_exe` alike; generic flags would make every feature-gated generator decline to its reference body (the 11-15× dasLLAMA release regression), and flags/machine must never diverge (host-F16C flags on a generic machine lower fp16 to libcalls msvcrt never links). Kernel-free exes stay generic/redistributable. Artifact witness: `g_target_host_features` + the `llvm_code_selftest::host_features` probe (tests/jit_tests/exe_host_cpu.das).
- **`stamp_llvm_code` records `tune_suffix`/`tune_from`** as extra `[llvm_code]` args — generators ignore unknown args by contract, and `tune_status` reads that stamped truth back off the AST (no macro-state bank).

## Adding a kernel family to a scope

1. Write the reference `def` with an explicit return type; register the generator key under `[llvm_code]` (see `llvm/daslib/llvm_jit_code.das` + `llvm_user_modules.das`).
2. Add the `[tune_perm]` grid + `tune(gen=, fallback=)`; companions between them.
3. If the library owns a scope already (`[tune_scope]`), the new family joins it automatically (same manifest). Otherwise declare one on a dummy struct in that module.
4. The harness benches `<name>_variants()` (the grid registry, present under `DAS_TUNE_MODE=tune`) and calls `tune_manifest_set("<name>", winner)`.

## Testing

`tests/jit_tests/llvm_tune_scope.das` is the end-to-end pattern: spawn the app as child daslang
processes across the policy flavors, use the `llvm_code_selftest::add_plus_k` generator (emits
`a+b+k`) so the RESULT is a fingerprint of the stamped perm. The tuner is a seconds-fast fake that
just `fwrite`s the manifest. Two scopes with a poisoned cross-scope entry prove isolation. Runs
with `-jit`; the `[test]` short-circuits to pass when `!jit_enabled()`.
