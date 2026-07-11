# dasMetal — native Metal compute: platform-gated binding + pure-daslang MSL backend

> **This file is the durable masterplan and implementation history for dasMetal.**
> It is the canonical, reviewable record — not Claude memory, not a scratch plan.
> Each phase appends a dated entry to the **Implementation log** at the bottom as it lands.

## Why

dasVulkan owns graphics on every platform (including macOS via MoltenVK). What it cannot
give on Apple Silicon is the **native compute fast path**: no Vulkan-emulation layer under
every dispatch, unified-memory `MTLBuffer`s that are plain pointers on both CPU and GPU,
and Metal-only features (simdgroup reductions, `simdgroup_matrix`). The target profile is
dasLLAMA-class GPU compute offload on the M-boxes. Scope is **compute only** — graphics
stays dasVulkan's job.

The shader-language facts that shape the design: **LLVM cannot emit MSL** (no backend; AIR,
Metal's binary form, is a private version-unstable LLVM-IR dialect) and **Metal does not
ingest SPIR-V** — its sanctioned inputs are MSL source and DXIL. Translation libraries
exist (SPIRV-Cross is MoltenVK's own shader stage), but vendoring one is a third-party C++
dependency that contradicts this module's thesis: *Metal.framework is just there*.

So dasMetal uses the house pattern, already proven three times: dasGlsl emits **GLSL text**
from the daslang AST (`GlslExport`), dasSpirv emits **SPIR-V words**, and `daslib/aot_cpp.das`
emits **C++ for the entire language**. MSL is a C++14 dialect; a compute-only MSL text
emitter is squarely inside the established pattern. Just as `[compute_shader]` lowers
daslang→SPIR-V→Vulkan, `[metal_kernel]` lowers daslang→MSL→Metal.

What makes it cheap: Metal's in-process runtime compiler (`newLibraryWithSource`) does all
GPU optimization; text is the easiest backend to emit and debug; and the authoring frontend
(module globals + `@ssbo`/`@binding` field annotations + builtin globals) already exists in
dasSpirv and is reused as-is.

## Settled decisions

1. **Lives in the main tree as `modules/dasMetal`.** The C++ binding is APPLE-gated; the
   `metal/` daslang files (emitter + annotation) are **pure das and registered on ALL
   platforms** — emitter/text tests run on every CI lane; only GPU execution is Apple-only.
2. **Compute only.** No render pipelines, no drawables, no CAMetalLayer. Graphics = dasVulkan.
3. **Zero third-party code.** No metal-cpp, no SPIRV-Cross, no MoltenVK, no committed
   `.msl`/`.metallib`, no external SDK. The binding is a hand-written Obj-C++ shim
   (`src/dasMetal.mm`) over the system Metal.framework — ~18 externs for the compute subset.
   (metal-cpp + dasClangBind rejected: vendored headers and binder churn for an ~18-extern
   surface; revisit only if the surface outgrows hand maintenance.)
4. **Class-based authoring: kernels are class methods, resources are class members.** A
   compute pass is a `class` whose `@ssbo @binding = N` members declare the buffers and
   whose `[metal_kernel]` methods are the kernels — no module-scope resource globals (they
   pollute the namespace and don't scale to two kernels with different buffer sets in one
   file), and members→kernel-parameters is exactly MSL's own model. Multiple kernels over
   one buffer set = multiple methods in one class. Builtin globals
   (`gl_GlobalInvocationID`, …) are still reused via `require spirv/spirv_builtins public`
   (dasSpirv is unconditional in-tree pure das — always resolves). Because the body is
   ordinary daslang, the same method also executes on the CPU — the primary correctness
   oracle (Test architecture). **Zero edits to shipped dasSpirv/dasGlsl.**
5. **Naming.** C++ module `das_metal` (`Module("das_metal")`, class `Module_DasMetal`). das
   files under `metal/`: `require metal/msl_shader`, `require metal/das_metal_boost`.
   Consumers guard: `require ?das_metal metal/das_metal_boost` +
   `static_if (typeinfo builtin_module_exists(das_metal))` (the sql_boost provider pattern).
   If a top-level registration proves workable in Phase 0, the spelling may shorten to a
   bare `das_metal_boost`; the two-segment guarded form is the safe default.
6. **Test-per-construct is a hard requirement**, enforced by a construct census (gate B) +
   the real-frontend compile gate. LCOV covers runtime files only — the emitter runs at
   compile time, invisible to line coverage (dasSpirv finding; census is the proxy).
7. **PoC before breadth.** The earliest milestone is `c[i] = a[i]*b[i]` through the REAL
   emitter on a real M-series GPU. The only hand-written MSL ever permitted is the Phase-0
   dev-scaffold **inline string** proving the binding, deleted when Phase 1 lands (the
   `_handbuild_square.das` pattern). **No `.msl` file is ever committed.**
8. **`fastmath` is a `[metal_kernel]` property, ON by default.** daslang's own posture is
   fastmath-on, so we are not chasing bit-exact float parity; Metal's runtime compiler also
   defaults fast-math ON and we keep it. Float oracles compare with tolerance (ints
   bit-exact). `[metal_kernel(fastmath=false)]` per kernel when isolating a divergence
   needs strict IEEE.

## Architecture

`modules/dasMetal` = one APPLE-gated Obj-C++ shim + pure-daslang emitter files:

| File | Gen/Hand | Purpose |
|---|---|---|
| `src/dasMetal.mm` | hand | `Module("das_metal")` — Obj-C++ shim over Metal.framework. Opaque annotated handles (device, queue, command buffer, compute encoder, pipeline state, library, function, buffer) + the extern surface below. Compiled with ARC; handles cross to das as `__bridge_retained void*`; `metal_release` = `__bridge_transfer`. Shim-side live-object counter for the leak gate. APPLE-only; links `-framework Metal -framework Foundation`. |
| `metal/msl_types.das` | hand | daslang `TypeDecl` → MSL type name (uint/int/float/bool, 2/3/4-vectors; later the 16/8-bit lattice — MSL has native `half`). |
| `metal/msl_emit.das` | hand | The text emitter: `[macro_function] generate_msl(fn, var errors, cfg, var census) : string`. Manual recursion (`emit_value`/`emit_stmt`, mirroring `spirv_emit`). Kernel-signature synthesis from `@ssbo` globals (the one structural novelty — below). Records the construct census at every emit site. |
| `metal/msl_shader.das` | hand | `[metal_kernel]` function-macro (`MetalKernel : AstFunctionAnnotation`, modeled on `SpirvShader`), applied to a **class method**; args: `name`, `fastmath` (default **true**, surfaced to the host via a companion ``{name}`msl_fastmath : bool`` global feeding the pipeline-compile options). `apply` declares the public ``{name}`msl : string`` global; **`fixup` fills `glob.init = new ExprConstString(...)`** — string capture is call-free, so fixup suffices (dasGlsl precedent; the patch/astChanged dance dasSpirv needed for `array<uint>` does not apply). Does `require spirv/spirv_builtins public`. |
| `metal/das_metal_boost.das` | hand | Host sugar over `das_metal`: `with_metal_device`, `pipeline_from_kernel` (compile + error surfacing), unified-memory buffer helpers, `run_compute_1d` one-liner, live-object leak assert. `require das_metal` → usable only where the C++ module exists. |
| `CMakeLists.txt` | hand | `ADD_MODULE_DAS(metal metal …)` unconditional (emitter everywhere); `IF(APPLE)`: `ADD_MODULE_CPP(DasMetal)` + `ADD_MODULE_LIB` + frameworks. Install rule mirrors dasSpirv's. |

**Extern surface (PoC-complete).** `metal_create_system_default_device`; device name +
unified-memory query; `metal_new_command_queue`; `metal_new_library_from_source(dev, src,
fastmath; var error)`; `metal_new_function(lib, name)`; `metal_new_compute_pipeline(dev,
fn; var error)`; `metal_new_buffer(dev, bytes)` (storageModeShared);
`metal_buffer_contents(buf) : void?` (the unified-memory pointer — host reads/writes it
directly, no map/unmap); `metal_new_command_buffer(q)`; `metal_new_compute_encoder(cb)`;
`metal_set_pipeline`; `metal_set_buffer(enc, buf, offset, index)`;
`metal_dispatch_threadgroups(enc, groups, threads_per_group)` (+`metal_dispatch_threads`
as the Apple-silicon exact-grid fast path); `metal_end_encoding`; `metal_commit`;
`metal_wait_until_completed`; `metal_command_buffer_error`; `metal_release`;
`metal_live_object_count`.

**Kernel-signature lowering (the one structural novelty).** MSL has no module-scope device
globals — and the authoring class's members map onto its model exactly: each `@ssbo`
member lowers to a kernel parameter `device T* name [[buffer(N)]]` (`device const T*` when
no kernel body writes it; member write-set collected in a pre-scan), and each referenced
builtin global lowers to a builtin-attributed parameter (`gl_GlobalInvocationID` →
`uint3 gl_GlobalInvocationID [[thread_position_in_grid]]`). Member access in the method
body (bare `a` / `self.a`) emits as the bare parameter name, so the body needs no other
rewriting. `@binding` = the flat `[[buffer(N)]]` index; `@set` must be absent or 0 (clean
error — Metal has no descriptor sets); duplicate bindings within one class are a clean
error. Identifiers colliding with MSL keywords (`kernel`, `device`, `constant`, `thread`,
`half`, …) are mangled. The exact AST shape of method-member access (`ExprField` over
`self`, constness, `ExprRef2Value` wrapping at fixup time) is dumped and recorded as the
first Phase-1 step — the same discipline as dasSpirv's square AST dump.

**Capture + cache.** Capture mirrors dasGlsl exactly (`ExprConstString` in fixup). A
companion reflection global is deferred until the boost needs auto-binding (mirror
`spirv_reflect` then). Text emission is fast enough to run every compile; if pipeline
compilation latency ever matters, an `MTLBinaryArchive` cache keyed by
`MSL_CODEGEN_VERSION` + `get_function_aot_hash(fn)` is the llvm_jit-pattern answer.

## PoC feature set (Phase-1 milestone)

The a*b kernel, authored:

```das
require metal/msl_shader

class MulAB {
    @ssbo @binding = 0 a : array<float>
    @ssbo @binding = 1 b : array<float>
    @ssbo @binding = 2 c : array<float>

    [metal_kernel]
    def mul_ab { let i = gl_GlobalInvocationID.x; c[i] = a[i] * b[i] }
}
// host reads mul_ab`msl : string → pipeline_from_kernel → run_compute_1d
```

Expected emission (the construct inventory that seeds the test matrix):

```
#include <metal_stdlib>
using namespace metal;
kernel void mul_ab(device const float* a [[buffer(0)]],
                   device const float* b [[buffer(1)]],
                   device float* c [[buffer(2)]],
                   uint3 gl_GlobalInvocationID [[thread_position_in_grid]]) {
    uint i = gl_GlobalInvocationID.x;
    c[i] = a[i] * b[i];
}
```

Constructs: preamble; kernel signature (device-pointer param, const-ness inference,
`[[buffer(N)]]`, builtin param); value-`let`; single-component swizzle; array index →
pointer index; `ExprOp2 *` (float); `ExprCopy` → assignment.

## Test architecture — "every emitted construct has a test"

Three behavioral layers + enforcement gates:

1. **Text-assertion units** (`tests/msl/`, ALL platforms). Each test compiles a tiny
   `[metal_kernel]` fixture, calls `generate_msl`, asserts structural facts (signature
   shape, attribute per binding, const-ness, statement forms), plus a golden snapshot of
   *our own* emitted text as a forward regression guard (dasSpirv's byte-snapshot amendment).
2. **Compile gate** (the spirv-val analog). Every emitted MSL must compile through the
   **real Metal frontend**: in-process `metal_new_library_from_source` where `das_metal`
   exists (no Xcode required — the OS MTLCompilerService), soft-skip elsewhere,
   hard-required on the macOS CI lane. (`xcrun metal` offline compile is a secondary local
   oracle only — it needs full Xcode, not CLT.)
3. **Real-GPU behavioral gate vs the CPU-reference oracle — as early as Phase 1**
   (`tests/metal/`, Apple-only). The kernel body is ordinary daslang, so the **same method
   runs on the CPU**: a driver loop sets `gl_GlobalInvocationID` and calls the method on a
   class instance whose members are plain arrays — that CPU run (interp/JIT) produces the
   expected buffer contents with zero second-source effort. GPU results compare against
   it: ints bit-exact, floats with tolerance (fastmath on both sides — settled decision 8;
   the PoC's `a[i]*b[i]` on small ints is exact regardless). Files are `require ?das_metal`
   + `static_if builtin_module_exists` guarded, so they compile and no-op cleanly on
   non-Apple lanes. Primary gate = **local M-boxes**; CI = the macOS lane's paravirtual
   device (Phase-0 probe decides behavioral vs compile-only).

- **Gate A — LCOV** on runtime-reached files (`das_metal_boost`, `msl_types` where runtime
  code exists). The emitter is compile-time → census is its coverage proxy.
- **Gate B — construct census.** `generate_msl` records every construct kind it emits
  (`table<string>` set: `"kernel_sig"`, `"param.buffer"`,
  `"param.builtin.thread_position_in_grid"`, `"op.mul.f32"`, …). A meta-test unions the
  census across all fixtures and asserts equality with the declared supported set, both
  directions. Census-record and emit are fused in one helper so they cannot drift; the
  golden-snapshot layer catches emissions that bypass it.
- **Leak gate.** Every `tests/metal/` file asserts `metal_live_object_count() == 0` at
  exit — Metal objects are invisible to all six das leak detectors, so the shim counts.

## Phasing (independently verifiable; no sizing)

- **Phase 0 — binding bring-up + probes.** This file; `src/dasMetal.mm` (module +
  externs); the CMake APPLE gate; `_handrolled_mul.das` dev scaffold with an **inline** MSL
  string (never a committed `.msl`; deleted at Phase 1) proving
  device→queue→pipeline→dispatch→readback + error surfacing on an M-box. Probes:
  (a) **macOS CI lane** — does the paravirtual device execute the scaffold? decides CI
  behavioral vs compile-only; (b) bad MSL surfaces the compiler log as a clean das error;
  (c) live-object counter round-trips to zero.
- **Phase 1 — a*b through the emitter (the PoC milestone).** `msl_types` + `msl_emit` PoC
  subset + `[metal_kernel]` + string capture + `das_metal_boost` v1 + census + compile gate
  + behavioral gate green on an M-box (+CI per the Phase-0 probe). Delete the Phase-0
  scaffold string. Register `tests/msl` in `tests/aot/CMakeLists.txt` (5-site pattern).
- **Phase 2 — arithmetic + control-flow breadth.** Mirror dasSpirv Phase 2's inventory:
  full scalar/vector arithmetic, comparisons, logical ops, mutable locals, if/else, while,
  range-for, break/continue, compound assignment. MSL is C-family — mostly emitter
  table-fill + tests; no structured-CFG hazard. The in-kernel bounds guard
  (`if (i >= n) return` for non-exact grids) lands here. Every fixture regresses against
  its CPU-reference run.
- **Phase 3 — threadgroup memory + barriers + simdgroup ops.** `threadgroup` address
  space, `threadgroup_barrier(mem_flags)`, `simd_sum`/`simd_shuffle*`, the remaining
  builtin attributes (`thread_position_in_threadgroup`, `threadgroup_position_in_grid`,
  `threads_per_threadgroup`). The Metal value-add real kernels need.
- **Phase 4 — 16/8-bit lattice.** `half` (native in MSL), short/ushort/uchar vectors —
  extend `msl_types`, conformance fixtures parity vs the CPU lattice and the
  dasSpirv/dasGlsl shader-lattice rails (`tests/type_lattice` discipline).
- **Phase 5 — `simdgroup_matrix` + host perf plumbing.** `simdgroup_float8x8` et al. (the
  dasLLAMA prize), buffer pooling, `MTLSharedEvent` sync, `MTLBinaryArchive` pipeline
  cache. Sized when we get there; a dasLLAMA offload experiment is the driver.

## Cross-backend parity (deferred — not a gate)

Stacking `[compute_shader, metal_kernel]` on one function was the original parity idea;
class-member authoring defers it — dasSpirv's frontend reads module globals, not class
members. The primary correctness oracle is the CPU-reference run of the same das body
(Test architecture, layer 3), which is cheaper and stricter than a second GPU. Cross-GPU
parity (zen2 Vulkan vs M-box Metal) returns as a nice-to-have if/when dasSpirv gains the
same class-member authoring — an in-tree follow-up, ours to make, not a dasMetal
prerequisite.

## Top risks

1. **macOS CI paravirtual Metal.** GitHub's macOS runners expose an "Apple Paravirtual
   device"; whether it executes our compute reliably is unproven → Phase-0 probe. Fallback:
   CI = compile gate only (still the real Metal frontend), behavioral = local M-boxes with
   a run book (the `tests/opengl_gpu/_lattice_gpu_parity.das` precedent).
2. **Obj-C lifetime discipline.** Retained-handle convention + explicit `metal_release`,
   enforced by the live-object leak gate; the boost's `with_`/finally wrappers are the
   user-facing rail so bare handles rarely cross user code.
3. **Kernel-arg lowering completeness.** Const-ness inference (write-set pre-scan), MSL
   keyword mangling, duplicate `@binding` = clean error, `@set` rejection. Fail-closed rule
   inherited from dasSpirv review hardening: every dispatch validates its input and errors
   cleanly — never a silent bad kernel, never a panic.
4. **Class-method annotation plumbing.** `[metal_kernel]` must fire on a class method
   (function_macro apply/fixup on methods; `@ssbo` field annotations on class members) —
   unproven; probed first thing in Phase 1 before any emitter work. Fallback if it fights:
   the struct-param form (`[metal_kernel] def mul_ab(var k : MulAB)` — free function,
   resources still grouped in one type), same emitter, only the frontend scan differs.
5. **Runtime-compile latency.** Per-pipeline `newLibraryWithSource` at startup is fine for
   tests/PoC; `MTLBinaryArchive` + codegen-version key is the escape hatch (Phase 5).
6. **Census honesty for a text emitter.** No disassembler exists to recount text (dasSpirv
   could re-derive opcodes from the blob). Mitigations in Test architecture (fused
   record+emit helper; golden snapshots).
7. **Dispatch model.** `dispatch_threads` (exact grid) needs Apple-family GPUs — fine on
   M-boxes, unproven on paravirtual. PoC uses exact-multiple sizes +
   `dispatch_threadgroups`; the guarded form arrives with Phase 2's bounds-guard construct.

## Verification (end to end)

- **Phase 0:** scaffold green on an M-box (readback exact, live objects 0, bad-MSL error
  surfaced with the compiler log); CI-probe result recorded in the log below.
- **Per phase (main tree):**
  `daslang dastest/dastest.das -- --test tests/msl --isolated-mode` green on every
  platform; `tests/metal` green on Apple; census == declared set both directions; every
  emitted kernel compile-gate clean; no `GC APP LEAK`; `metal_live_object_count()` 0.
- **M-box run book (behavioral + parity):** `bin/daslang tests/metal/...` on M1/M3 Air;
  the zen2 side runs the same parity fixtures through dasVulkan.
- **Lint/format:** MCP `format_file` + `lint` on every new `.das`; `cpp_format_file` on the
  `.mm`. PR-mode throughout.

---

# Implementation log

**2026-07-11 — masterplan.** Authored; revised same day per review: class-based authoring
(kernels = methods, resources = `@ssbo` members — no module-scope resource globals),
`fastmath` a `[metal_kernel]` property defaulting ON, CPU-reference oracle promoted to the
primary correctness gate, cross-backend GPU parity demoted to a deferred nice-to-have.

**2026-07-11 — Phase 0 landed: binding bring-up + probes.** `src/dasMetal.mm`
(`Module("das_metal")`, class `Module_DasMetal`, ARC-compiled, 8 `DummyTypeAnnotation`
opaque handles, the full PoC extern surface incl. 8 `metal_release` overloads +
`metal_live_object_count`) + `src/dasMetal.h` (pure-C++ decls for `aotRequire`);
`CMakeLists.txt` APPLE-gated (`ADD_MODULE_CPP(DasMetal)` + `ADD_MODULE_LIB`, `-fobjc-arc`
on the `.mm`, Metal+Foundation frameworks); `.das_module` descriptor (silent 2-arg
`register_dynamic_module` — skips cleanly on non-Apple); root `DAS_METAL_DISABLED` option
(default OFF). Scaffold `_handrolled_mul.das` green on M1 Max (macOS 26.4, arm64):
- **Readback exact** — a*b over 256 floats via BOTH `metal_dispatch_threadgroups` and
  `metal_dispatch_threads` (exact-grid fast path confirmed working on Apple-family GPU —
  risk 7 half-resolved; paravirtual still unknown).
- **Bad-MSL probe** — `undeclared_identifier` fixture surfaces the real Metal compiler
  log (with source line + caret) as a clean das error string; no crash, no nil deref.
- **Leak probe** — live-object counter round-trips to 0 after releasing all 12 handles.
- **Fail-closed probe** (beyond plan) — null handle into any extern throws a clean,
  `recover`-able das error via `throw_error_at` (every extern null-guards its handles).
Implementation notes: `char *&` error out-params follow the fio pattern
(`SideEffects::modifyArgumentAndExternal`); handles cross as `__bridge_retained void*`,
`metal_release` = `__bridge_transfer`, counted by a shim-side atomic;
`MTLCompileOptions.mathMode` (macOS 15+ SDK) with `fastMathEnabled` fallback. das-side
gotcha for the Phase-1 emitter: `label` and `expect` are reserved words; literal `{`/`}`
in MSL strings must be escaped `\{`/`\}` (string interpolation).
**Probe (a) — macOS CI paravirtual execute — PENDING:** `build.yml` runs on
PR/master-push/dispatch only and the branch is local; the macOS lanes are `macos-15` /
`macos-26` Apple-Silicon (M2) runners with the Apple Paravirtual device. Resolve when the
arc branch first goes to CI; until then CI posture = compile gate, behavioral = M-boxes.

**2026-07-11 — Phase 1 landed: a*b through the REAL emitter (the PoC milestone).**
`metal/msl_types.das` (32-bit scalar + 2/3/4-vector map), `metal/msl_emit.das`
(`generate_msl` — member scan with duplicate-binding/`@set`/non-`@ssbo` fail-closed errors,
write-set pre-scan for `device` vs `device const`, builtin classifier, manual-recursion
statement/expression emit with fused census recording, MSL keyword mangling),
`metal/msl_shader.das` (`[metal_kernel]` — apply declares 4 companion globals
`N`/`N_entry`/`N_fastmath`/`N_census`, fixup fills all as constant nodes),
`metal/das_metal_boost.das` v1 (`with_metal_device`, `pipeline_from_source`,
`run_compute_1d`, `assert_no_metal_leaks`). Emitted text matches this file's expected
emission byte-for-byte (modulo param-wrap indent + defensive parens). Gates green on M1 Max:
`tests/msl` (shape asserts + golden snapshot + census == declared set both directions, 8/8)
and `tests/metal` (emitted MSL on GPU == CPU-reference run of the same method — the driver
loop feeds `gl_GlobalInvocationID` — plus leak gate, 2/2); both suites pass through the
dynamic AND static binaries. Phase-0 scaffold deleted on schedule. Wiring: unconditional
`ADD_MODULE_DAS` + dasSpirv-style install rule; `.das_module` `register_native_path` for
the four metal files; `tests/msl` + `tests/metal` registered in `tests/aot/CMakeLists.txt`
(fixture `_msl_common` AOT_LIB'd per the `_spirv_common` precedent; macro-only metal
modules deliberately not AOT'd, per the spirv_emit precedent).
Probe results (annotation plumbing — risk 4 CLOSED, no struct-param fallback needed):
`[function_macro]` fires on class methods. The apply/fixup division is dasGlsl's, strictly:
`apply` is pre-infer (types unresolved — aliases still aliases), so it does ONLY the two
type-independent actions: `exports = true` (the method is otherwise culled before `fixup`
runs — probe-verified) and declaring the fixed-type (`tString`/`tBool`) companion globals so
consumers resolve in the first inference pass. ALL type-dependent work — member scan,
write-set, emission — runs in `fixup`, post-infer, where `fld._type` is resolved;
`@ssbo`/`@binding` field annotations read via `field.annotation |> find_arg`; the member
scan skips `__rtti`/`__finalize` + function-typed fields (classes store methods as fields);
by fixup time the `with(self)` wrapper is optimizer-dropped and access is
`ExprAt(ExprField(ExprVar(self), name), index)` — but under `no_optimizations` compiles
(lint/LSP) the wrapper + non-folded shapes survive, so the emitter treats `ExprWith` as
transparent (census-silent, or the gate would depend on optimization level).
Plan deviations, both deliberate: builtins come from `require daslib/shader_lingua_franca
public` (where the compute IDs actually live — `spirv/spirv_builtins` merely re-exports
them and adds VK-specific surface dasMetal doesn't want); the declared census lives in the
test fixture `_msl_common.das`, not the emitter (the emitter modules are macro-only and
never AOT'd — a runtime `declared_msl_census()` there would 50101 under `test_aot`).
das gotcha for kernel authors: emitter-facing das reserved words `label`/`expect` (now in
CLAUDE.md gotchas). CI paravirtual probe still pending first push.

**2026-07-11 — Phase 2 landed: arithmetic + control-flow breadth.** The emitter now covers the
full dasSpirv-Phase-2-equivalent inventory: scalar arithmetic + bitwise + shifts for
uint/int/float (float `%` → `fmod` — MSL `%` is integral-only), componentwise vector arithmetic
incl. `vec*scalar` broadcast and vector negate, comparisons per scalar class, das's scalar-bool
vector `==`/`!=` (→ `all(...)`/`any(...)` — MSL's own vector compare yields `boolN`), logical
`&&`/`||`/`!` (short-circuit matches C on both sides), ternary, pre/post `++`/`--` (statement-level
das postfix arrives as prefix in the AST; value-level postfix survives), compound assignment
(arithmetic + bitwise), mutable locals + das zero-init locals (`var x : T` → `T x = {};`),
if/elif/else chains (emitted flat as `} else if`), `while`, `break`/`continue`, void `return`, and
`for (i in range/urange(...))` — with the das-semantics subtlety that range endpoints evaluate
ONCE: a non-constant end is hoisted into a loop-scoped comma-declared local
(`for (int k = lo, k_end = expr; ...)`), proven behaviorally by a fixture that mutates the end's
source variable inside the body. New frontend surface: **`@uniform @binding = N` scalar/vector
members** → `constant T& name [[buffer(N)]]` (read-only — a written uniform is a clean error;
arrays stay `@ssbo`), which is what the **in-kernel bounds guard** (`if (i >= n) return`) reads.
Literal fixes: das prints integral floats bare ("2" + `f` is invalid MSL → `.0` appended,
non-finite = error) and uints as hex (decimal via int64 detour). Census grew 13 → 106 kinds.
Tests: `tests/msl` 37/37 — per-class shape asserts + goldens (uarith/iarith/farith/vecarith/
control/loops), census union == declared both directions, and a fail-closed suite
(`_fail_closed/` + compile_issues, mirroring tests/spirv): written `@uniform`, array `@uniform`,
value `return`, unsupported call. `tests/metal` 14/14 on M1 Max — every fixture regresses GPU vs
the CPU-reference oracle (ints bit-exact incl. wrap/truncation, floats fastmath-tolerance), with
the loops kernel dispatched on a deliberately NON-exact grid (1000 threads @ 64/tg → 1024
launched) over sentinel-filled buffers compared across the FULL padded range — a broken guard
shows as clobbered sentinels. Shared GPU helpers live in `tests/metal/_metal_common.das` as
GENERIC functions (untyped `dev`/`buf` params): generics only instantiate at call sites inside
`static_if (builtin_module_exists(das_metal))`, so the fixture compiles on every platform;
AOT-wired as `test_aot_metal_modules` (msl-modules pattern; the metal glob gained the `/_` filter).
Green: interp + `-jit` + static binary, MCP lint + CI lint clean. das gotchas hit: `expect` is
reserved (fixture param renamed `want`); `float4 + float` does NOT broadcast in das (only `*`/`/`).

**2026-07-11 — pipeline: fixup-set global inits now infer; dasSpirv blob fill patch→fixup**
(rides this branch — surfaced reviewing dasMetal's apply/fixup model). Boris called dasSpirv's
patch+astChanged blob fill a workaround for a compiler gap; confirmed and fixed. Diagnosis
(both repro'd): `fixupAnnotations()` ran post-optimize and nothing inferred what fixup created —
a call-shaped init (`to_array_move` from the `array<uint>` literal) died with 50607; and a naive
re-infer at that old position re-tripped already-folded unsafe (31013 in daslib generics) because
`foldUnsafe` strips the wrappers — the exact ordering constraint the scope_free comment documents.
Fix (ast_parse.cpp): `fixupAnnotations()` moved to right after infer converges — BEFORE
lint/foldUnsafe/optimize — followed by a dirty re-infer gated on any global init left uninferred;
fixup output now flows through the whole back half like ordinary code. dasSpirv's blob+reflection
fill moved patch→fixup, astChanged dance deleted (also deletes one full-program re-infer restart
per shader-bearing module — those restarts marked EVERY function notInferred). The dasVulkan
backend body-fill hooks stay in patch (function bodies genuinely need the in-loop re-infer).
Consequence for annotation authors: fixup now sees PRE-optimize AST (dasMetal's emitter already
handles both shapes; dasGlsl goldens unchanged — 98/98). Regression test independent of dasSpirv:
`tests/language/test_fixup_global_init.das` + `_fixup_init_macro.das`. Green: tests/spirv 238/238
(generation in fixup), glsl, msl, metal, language — dynamic + static binaries.
