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
4. **The authoring surface IS dasSpirv's.** Same `@ssbo`/`@binding` field annotations, same
   builtin globals — `msl_shader` does `require spirv/spirv_builtins public` (dasSpirv is
   unconditional in-tree pure das, present on every platform, so this dependency always
   resolves). dasMetal adds only the `[metal_kernel]` annotation + the MSL emitter. One
   source function can stack `[compute_shader, metal_kernel]` → the cross-backend parity
   gate. **Zero edits to shipped dasSpirv/dasGlsl.**
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
8. **Parity compiles with fast-math OFF.** Metal's runtime compiler defaults fast-math ON,
   which breaks CPU↔GPU float comparison. All test/parity pipelines compile with safe math;
   a boost-level knob re-enables fast-math for perf kernels.

## Architecture

`modules/dasMetal` = one APPLE-gated Obj-C++ shim + pure-daslang emitter files:

| File | Gen/Hand | Purpose |
|---|---|---|
| `src/dasMetal.mm` | hand | `Module("das_metal")` — Obj-C++ shim over Metal.framework. Opaque annotated handles (device, queue, command buffer, compute encoder, pipeline state, library, function, buffer) + the extern surface below. Compiled with ARC; handles cross to das as `__bridge_retained void*`; `metal_release` = `__bridge_transfer`. Shim-side live-object counter for the leak gate. APPLE-only; links `-framework Metal -framework Foundation`. |
| `metal/msl_types.das` | hand | daslang `TypeDecl` → MSL type name (uint/int/float/bool, 2/3/4-vectors; later the 16/8-bit lattice — MSL has native `half`). |
| `metal/msl_emit.das` | hand | The text emitter: `[macro_function] generate_msl(fn, var errors, cfg, var census) : string`. Manual recursion (`emit_value`/`emit_stmt`, mirroring `spirv_emit`). Kernel-signature synthesis from `@ssbo` globals (the one structural novelty — below). Records the construct census at every emit site. |
| `metal/msl_shader.das` | hand | `[metal_kernel]` function-macro (`MetalKernel : AstFunctionAnnotation`, modeled on `SpirvShader`). `apply` declares the public ``{name}`msl : string`` global; **`fixup` fills `glob.init = new ExprConstString(...)`** — string capture is call-free, so fixup suffices (dasGlsl precedent; the patch/astChanged dance dasSpirv needed for `array<uint>` does not apply). Does `require spirv/spirv_builtins public`. |
| `metal/das_metal_boost.das` | hand | Host sugar over `das_metal`: `with_metal_device`, `pipeline_from_kernel` (compile + error surfacing), unified-memory buffer helpers, `run_compute_1d` one-liner, live-object leak assert. `require das_metal` → usable only where the C++ module exists. |
| `CMakeLists.txt` | hand | `ADD_MODULE_DAS(metal metal …)` unconditional (emitter everywhere); `IF(APPLE)`: `ADD_MODULE_CPP(DasMetal)` + `ADD_MODULE_LIB` + frameworks. Install rule mirrors dasSpirv's. |

**Extern surface (PoC-complete).** `metal_create_system_default_device`; device name +
unified-memory query; `metal_new_command_queue`; `metal_new_library_from_source(dev, src,
safe_math; var error)`; `metal_new_function(lib, name)`; `metal_new_compute_pipeline(dev,
fn; var error)`; `metal_new_buffer(dev, bytes)` (storageModeShared);
`metal_buffer_contents(buf) : void?` (the unified-memory pointer — host reads/writes it
directly, no map/unmap); `metal_new_command_buffer(q)`; `metal_new_compute_encoder(cb)`;
`metal_set_pipeline`; `metal_set_buffer(enc, buf, offset, index)`;
`metal_dispatch_threadgroups(enc, groups, threads_per_group)` (+`metal_dispatch_threads`
as the Apple-silicon exact-grid fast path); `metal_end_encoding`; `metal_commit`;
`metal_wait_until_completed`; `metal_command_buffer_error`; `metal_release`;
`metal_live_object_count`.

**Kernel-signature lowering (the one structural novelty).** SPIR-V keeps `@ssbo` globals as
module-scope `OpVariable`s; MSL has no module-scope device globals — each `@ssbo` global
lowers to a kernel parameter `device T* name [[buffer(N)]]` (`device const T*` when the
body never writes it; write-set collected in a pre-scan), and each referenced builtin
lowers to a builtin-attributed parameter (`gl_GlobalInvocationID` →
`uint3 gl_GlobalInvocationID [[thread_position_in_grid]]`). The parameter keeps the
global's name and MSL is lexically scoped, so body references need **no rewriting**.
`@binding` = the flat `[[buffer(N)]]` index; `@set` must be absent or 0 (clean error —
Metal has no descriptor sets); duplicate bindings are a clean error. Identifiers colliding
with MSL keywords (`kernel`, `device`, `constant`, `thread`, `half`, …) are mangled.

**Capture + cache.** Capture mirrors dasGlsl exactly (`ExprConstString` in fixup). A
companion reflection global is deferred until the boost needs auto-binding (mirror
`spirv_reflect` then). Text emission is fast enough to run every compile; if pipeline
compilation latency ever matters, an `MTLBinaryArchive` cache keyed by
`MSL_CODEGEN_VERSION` + `get_function_aot_hash(fn)` is the llvm_jit-pattern answer.

## PoC feature set (Phase-1 milestone)

The a*b kernel, authored:

```das
require metal/msl_shader

var @ssbo @binding = 0 a : array<float>
var @ssbo @binding = 1 b : array<float>
var @ssbo @binding = 2 c : array<float>

[metal_kernel]
def mul_ab { let i = gl_GlobalInvocationID.x; c[i] = a[i] * b[i] }
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
3. **Real-GPU behavioral gate — as early as Phase 1** (`tests/metal/`, Apple-only).
   `run_compute_1d`, `c[i]==a[i]*b[i]`, exact float compare (products of small ints;
   fast-math off). Files are `require ?das_metal` + `static_if builtin_module_exists`
   guarded, so they compile and no-op cleanly on non-Apple lanes. Primary gate = **local
   M-boxes**; CI = the macOS lane's paravirtual device (Phase-0 probe decides behavioral
   vs compile-only).

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
  (`if (i >= n) return` for non-exact grids) lands here. **First cross-backend parity
  fixtures land here** (stacked `[compute_shader, metal_kernel]`).
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

## Cross-backend parity gate (Phase 2+)

One source function, both annotations stacked → two globals (``{name}`spirv`` words +
``{name}`msl`` text). zen2 runs the SPIR-V via dasVulkan (lavapipe + real GPU); the M-box
runs the MSL via `das_metal`. Integer fixtures compare bit-exact; float fixtures exact
where arithmetic is exactly representable, ULP-bounded otherwise (fast-math off on both
sides; lattice fixtures reuse `_lattice_gpu_parity`'s dual-reference discipline). Requires
the two annotations not to fight in apply/patch (each adds its own global; both set
exports) — verified by the first stacked fixture.

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
4. **Float parity vs fast-math.** Settled decision 8; forgetting it produces
   Heisenberg parity failures. The parity harness sets safe math unconditionally.
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

*(Phase 0 not started — 2026-07-11: masterplan authored.)*
