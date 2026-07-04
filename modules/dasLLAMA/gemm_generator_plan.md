# GEMM kernel generator — plan

**Status: plan, pre-implementation.** This is the design + session runbook for generating
Q8·Q8 (and later MXFP4) GEMM microkernels at the LLVM-IR layer instead of hand-writing them
in das. Written at the close of the EPYC 9654 campaign (`epyc9654_measurements.md`); the
campaign's fleet sweep is the motivating evidence. Companion docs: `x64_arch.md` (the two
seams this plugs into), `avx_kernel_matrix.md` (the hand-written tier matrix this replaces),
`tune_for_this_box.md` (the tuner rail this extends).

**Hardware prereq:** execution measurements need real VNNI/AVX-512 silicon — the rented EPYC
is parked/off; either rent again (Cherry Servers hourly, setup recipe in
`epyc9654_measurements.md`) or note that Boris's Zen2 desktop only exercises the avx2 tiers.
M0/M1 emission-only work runs fine on the arm64 box via `DAS_JIT_X64_FORCE_FEATURES` + `llc`
disasm (never execute forced artifacts).

---

## The frame

Hand-writing kernels doesn't scale and never will: llama.cpp carries ~390 hand-written
kernels (~1000 ISA paths across 7 architectures, `arch/*/repack.cpp` + `ggml-cpu-quants.c`),
and every one of them is the same loop nest with different constants — tile shape, vector
width, dot primitive, repack layout, scale fold. That's not 390 kernels; it's **one
parametric family** and a maintenance moat. We stop digging our own copy of that moat:

- **Generate** the microkernel loop nest as LLVM IR, parameterized by a perm vector,
  via the JIT-intrinsic emitter rail that already exists in dasLLVM.
- **Tune** by sweeping the perm space with the existing tuner machinery — `[tuned]` one
  level down: instead of permuting loop *hints* on a das body, permute the *kernel itself*.
- Per-ISA support becomes a per-ISA **dot-primitive emitter** (vpdpbusd / maddubs pair /
  sdot / …), and NEON/SVE/RVV fall out of the same generator instead of new hand files.

**The gap it chases:** fleet prefill is uniformly ~0.73–0.86× of llama.cpp (gpt-oss 0.61×)
after the zvnni batch pin; on Genoa their engine is the AVX512-VNNI **zmm repack GEMM**
(pp512 T=32: 1072 vs our 565 before the pin). Decode at ≥1B is already near-parity — this
is a **batch-GEMM (prefill) program** first.

**Method rule (standing):** profile hand-coded before building the macro. The generator gets
built only after ONE hand-emitted perm proves the ceiling is reachable (M2 gate below).

---

## The rail that exists (what we build on, not build)

- **Emitter surface** (`modules/dasLLVM/daslib/llvm_jit_intrin.das`): name-keyed tables
  (`g_intrin_lookup`, `g_aarch64_intrin_lookup`, `g_x64_intrin_lookup`) mapping a qualified
  das call name to an emitter `(var ctx : JitCtx; expr : ExprCallFunc?; arguments :
  array<LLVMOpaqueValue?>) : LLVMOpaqueValue?` that builds IR with `LLVMBuild*` /
  `LLVMGetIntrinsicDeclaration`. `x64_avx.das` / `aarch64_neon.das` are the worked examples:
  das function with a portable scalar fallback body, emitter fires only on the matching
  target. The vector-expf emitter (`build_vector_expf`) is the existing proof that a
  *multi-instruction computation* (not just one intrinsic) can be composed this way.
- **Cross-context reality (why the schema is an annotation):** the JIT is a das program in
  its own context compiling the *user* program's AST. A user-module `[init]` cannot reach
  the JIT's lookup tables — the only channels the JIT already reads are the AST itself and
  **annotations on user functions** (`fold_loop_hints` reads loop hints; the DLL cache key
  folds them). So the generator lives in dasLLVM's daslib, and the perm travels as
  annotation arguments (ints/strings/bools) on a user-side stub.
- **Correctness tiers for free:** the stub carries a reference das body — interpreter, AOT,
  and non-matching JIT targets compile it verbatim. That is the AOT gate and the bit-exact
  oracle in one move (same rule as every intrinsic today: correct everywhere, fast where the
  emitter fires).
- **Cache keying:** the JIT DLL cache key folds per-function AOT hashes + loop-hint
  annotations. The perm annotation must fold the same way (extend `fold_loop_hints`'s
  pattern in `llvm_jit_run.das`) so a re-tune re-keys the DLL automatically; bump
  `LLVM_JIT_CODEGEN_VERSION` when the generator's emission changes for a fixed perm.
- **Backend registry** (`dasllama_math.das`): generated kernels register as ordinary
  pin-only `KernelBackend` tiers (exactly like the AVX matrix — priorities below shipped,
  `cpu_supports` gates). The whole existing selection/pin/hybrid/profile/A-B rail then
  applies to generated kernels **unchanged**.

## The unit of generation

A das stub function per (kernel-shape × perm):

```
[gemm_kernel(mr = 8, nr = 4, width = 512, dot = "vpdpbusd", kstep = 2, repack = "grp8",
             acc = "i32reg", scale = "block_fold", prefetch = 256)]
def q8q8_batch_gen_8x4_z(w : uint8 const?; ws : float const?; x : uint8 const?;
                         xs : float const?; var y : float?; n, d, ntok : int) {
    // reference body: the portable batch kernel — bit-exact semantics, runs on
    // interp/AOT/off-target JIT; the emitter replaces it wholesale on-target
}
```

The JIT recognizes the annotation, ignores the body, and emits the whole loop nest from the
perm. (Alternative considered: a callmacro generating das *source* — rejected as the primary
path: source-level permutation is what `[tuned]` already does, and the loop-hint ceiling is
measured; the wins left are instruction-selection-level — exact dot ops, register-tile
layout, fold points — which das source cannot express.) `[tuned]` stays for float
elementwise kernels; the generator owns the integer GEMM/GEMV family.

## The perm vector (the knobs)

The parameter space the generator must span — write the M2 kernel against these names so
the schema is validated by use:

| Knob | Values (initial) | Notes |
|---|---|---|
| `dot` | `vpdpbusd` (u8·s8 + sign trick), `maddubs` (VPMADDUBSW+VPMADDWD pair), `vpdpbssd` (VNNI-INT8, s8·s8 native), `sdot` (NEON), `mx4` (VPSHUFB dequant + dot) | per-ISA emitter; the sign-trick identity and its `|a|`-on-unsigned rule are in `x64_arch.md` |
| `width` | 256 (ymm), 512 (zmm) | zmm halves instruction count but watch frequency/port behavior per box — a *tuned* knob, not a derived one |
| `mr × nr` | e.g. 4×4, 8×4, 8×8, 16×4 (rows × tokens) | register-tile shape. Hard constraint: `mr·nr` accumulators + row loads + broadcast ≤ 32 vregs (16 for ymm) — generator rejects illegal perms at emit time |
| `kstep` | 1, 2, 4 blocks (32 int8 = 1 block) per K-iteration | interacts with `acc` promotion; full unroll when K is baked (per-model) |
| `repack` | `none` (row-major), `grp<mr>` (mr-row block interleave, scales float<mr>-interleaved) | **interleave factor is derived from `mr`** — repack is *generated from the same schema* so layout and kernel can never desync; `needs_repack` flows to the registry as today |
| `acc` | `i32reg` (mr·nr i32 vreg tile, scale-fold at block boundary), `f32mem` (acc8-style memory accumulator, LICM-promoted) | acc8's low-thread win vs wash-at-32T says this is box-dependent — keep both |
| `scale` | `block_fold` (float(blocksum)·ws·xs per block), `late` (accumulate i32 across kstep, fold once) | `late` is only exact within the no-overflow window — generator computes the window from kstep and refuses invalid combos |
| `load` | `bcast_x` (broadcast activation dword-group × row-vector loads — the repack shape), `bcast_w` | M0 disasm decides which family ggml's winner actually is — don't cargo-cult |
| `prefetch` | off, N bytes ahead (weights) | NT/streaming loads for fat w13/w2 streams is a candidate value here (mm_ffn 1.42× is fat-stream territory) |
| `epilogue` | store, `+bias`, `+residual`, `+requant` | fused-chain epilogues (see `a8aee5c4b`) become perm values instead of hand variants |
| `tail` | masked (zmm k-masks), padded, scalar | d-tail and ntok-tail handling |
| `bake` | none, `k` (n and nblocks become IR constants) | the per-model axis — see below |

## Tuning axes — per-ISA × per-box × per-model × per-regime

The perm space factors cleanly, and each factor already has a rail:

- **Per-ISA:** registration gates (`cpu_supports`, `g_target_x64_*`) pick which dot
  primitives exist at all. Same as the AVX matrix today.
- **Per-box:** cache sizes, bandwidth, SMT behavior, zmm frequency response → tuner sweeps
  the perm grid on the box, winners land in `box_profile.json` (the grain knobs already ride
  this rail; `tune_for_this_box.md` step 2's with-profile rule applies).
- **Per-model (the new axis):** a model is a fixed set of GEMM shapes — one per slot
  (kv/qo/w13/w2/cls), known at load time, plus its quant mix (q8/q4/mx4 per tensor) and
  dense-vs-MoE structure. The generator makes per-model kernels *cheap*: `bake = k` turns
  n/nblocks into IR constants (full K-unroll, no tail code, exact tiling for d=2048 vs
  3072), and per-slot perm pins reuse the hybrid-backend machinery (`select_batch_backend`
  precedent — extend the pin from "backend per slot-shape" to "perm per slot"). The tune
  artifact becomes `(box, model) → per-slot perm table`; where it lives (a `models` section
  in `box_profile.json` keyed by shape-signature vs a sidecar per-model file) is an open Q.
- **Per-regime:** decode GEMV vs batch GEMM already diverge (hybrid pin) — GEMV perms are a
  sub-family (nr = 1, latency-shaped) swept separately.

Sweep cost stays sane because the sweep unit is a **kernel-level iso bench** (the
`bench_gemm_iso.das` / `gemm_1core_probe.das` pattern) on the model's actual slot shapes,
not end-to-end decode — the tune_kernels sweep is ~1 min today; a per-model perm sweep
should target the same order.

## Session plan (milestones, each with a gate)

**M0 — reference ceiling (position 0: build the instrument first).**
Extend `harness/oracle/kernel_bench.cpp` to call llama.cpp's *repack GEMM family* (the
`arch/x86/repack.cpp` q8_0 8×8 path that wins on Genoa), not just `vec_dot`; wiring note in
the file header (examples/kernel-bench, same as simple-ids). Disassemble their winning
kernel (objdump on the built lcpp, or perf-annotate during a pp512 run) and write down: the
actual tile shape, dot sequence, scale-fold point, load family, prefetch pattern. Dump OUR
current best (`--jit-dump` rail) for the same shape as the baseline IR. **Gate: a table —
their GMAC/s ceiling per slot shape vs our zvnni-batch numbers — plus the target IR shape
on paper.** Runs partly on arm64 (disasm/IR reading); GMAC/s numbers need the x64 box.

**M1 — raw primitive emitters.**
The current intrinsics (`dot32_vnni`, `dot64_acc16` …) wrap *whole dots*; the generator
needs the primitives one level down: vpdpbusd-accumulate on given vreg values, dword-group
broadcast, sign-apply (compare+negate or VPSIGNB by width), k-masked loads, NT loads. Add
them as plain emitter helpers inside dasLLVM (they compose IR values — they need no das-side
fallback of their own). Emission-only validation via `DAS_JIT_X64_FORCE_FEATURES` + `llc`
disasm on arm64. **Gate: disasm of each helper's output matches the hand-expected
instruction, no verifier errors.**

**M2 — ONE hand-composed perm (the GO/NO-GO for the whole idea).**
Hand-emit the 8×4 zmm vpdpbusd tile (the M0-informed guess; adjust to what M0's disasm
says) as a single `[gemm_kernel(...)]` stub + hard-coded emitter — no generator yet, the
emitter IS what the generator would produce for that one perm. Bit-exact vs the reference
body (avx_matrix_probe exactness-gate pattern); iso A/B on kv/qo/w13/w2/cls shapes at
1-core and T=8/32 vs the zvnni-batch baseline (`matmul_variants`/`bench_gemm_iso` probe
pattern, interleaved ABBA only). **Gate: the hand perm closes a meaningful fraction of the
M0 gap on ≥1 slot shape. If it doesn't, stop — the moat isn't where we thought, and we've
spent one kernel, not a generator.**

**M3 — the generator + schema.**
Promote the M2 emitter into the perm-parameterized generator; validate the schema by
re-expressing M2's kernel as its perm vector plus 2–3 neighbors (4×4 ymm maddubs ≈ the
existing avx2 tier as a self-check; an 8×8; a vpdpbssd twin if silicon allows). Bit-exact
gates on every emitted perm; vreg-budget rejection tested. Registry integration: perms
register as pin-only backends. Cache-key folding for the annotation. **Gate: generated
== hand-emitted for the M2 perm (same disasm), neighbors bit-exact.**

**M4 — tune + per-model + fleet.**
Perm sweep on the box (all-perms-in-one-probe à la `tune_kernels` — every perm is just a
differently-annotated stub in one binary, so one probe run sweeps the family); per-slot ×
per-model winners into the profile rail; `bake = k` A/B; then the fleet re-sweep
(`emission_bench` pp512 method from session 5) to re-score the 0.73–0.86× column. Repack
generation from the schema lands here (needed as soon as a `grp<mr>` perm wins somewhere).

## Open questions (Boris)

1. **Schema surface:** annotation-on-stub with reference body (recommended above — free
   AOT/oracle gate, cross-context-correct) vs a callmacro that stamps stubs. Settle before M2.
2. **Sweep mechanics:** all-perms-in-one-probe (one JIT compile of N stubs, tune_kernels
   style) vs recompile-per-perm; how the perm folds into the DLL cache key (annotation-fold
   like loop hints — automatic re-key on re-tune — vs explicit version bump discipline).
3. **Where per-model winners live:** `box_profile.json` `models` section keyed by
   shape-signature, or per-model sidecar next to the GGUF. (Shape-signature keying also
   answers "same shapes, different fine-tune" for free.)
4. **Registration locality:** generator + emitters live in dasLLVM daslib (like x64_avx) —
   fine forever, or do we eventually want a public `register_jit_intrinsic` rail so modules
   outside dasLLVM can contribute emitters? Not needed for M0–M4.
5. **Hardware:** re-rent the EPYC for M2/M4, or is the Zen2 desktop (avx2/maddubs perms
   only, no VNNI) enough to de-risk M2 before renting?

## Pointers

- Rails: `modules/dasLLVM/daslib/llvm_jit_intrin.das` (emitter tables + `build_vector_expf`
  composition example), `x64_avx.das` / `aarch64_neon.das` (stub+emitter pattern),
  `llvm_jit_run.das` (cache key, `fold_loop_hints`, `LLVM_JIT_CODEGEN_VERSION`),
  `dasllama_math.das` (KernelBackend registry, hybrid per-slot pin),
  `dasllama_tune.das` (`[tuned]`/`[dasllama_grid]` — the machinery being generalized).
- Benches/probes: `harness/oracle/kernel_bench.cpp` (lcpp kernel iso),
  `benchmarks/matmul/bench_gemm_iso.das`, `harness/gemm_1core_probe.das`,
  `harness/avx_matrix_probe.das` (exactness gates), `benchmarks/emission_bench.das`
  (fleet pp512 method).
- Evidence: `epyc9654_measurements.md` (sessions 3b–5: why portable+pin wins today, the
  0.73–0.86× fleet column, the Genoa zmm-engine finding).
