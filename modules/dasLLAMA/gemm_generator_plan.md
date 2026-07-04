# Kernel generation — `[llvm_code]`, the tune framework, and GEMM — plan

**Status: architecture settled (2026-07-04 discussion), pre-implementation.** This supersedes
the GEMM-only first draft of this document. The GEMM generator is now the flagship *client*
of two generic dasLLVM capabilities — an external-codegen hook (`[llvm_code]`, part 1) and a
generalized tune framework (part 2) — with GEMM as part 3. Work order: **part 1 minimal →
M0–M2 evidence on the M1 Mac → parts 2–3 built on that evidence.** Companion docs:
`x64_arch.md` (the two x64 seams), `avx_kernel_matrix.md` (the hand-written tier matrix this
eventually deletes), `tune_for_this_box.md` (the tuner rail being generalized),
`epyc9654_measurements.md` (the motivating fleet evidence).

**Hardware plan (settled):** the M1 Mac first — this box's **sdot kernels** are the M0–M2
vehicle. Zen2 desktop after (avx2/maddubs perms; no VNNI). The EPYC 9654 is parked but
configured — wake it up only when everything is a win and there's a reason (zvnni perms,
fleet re-score). x64 emission work runs on the Mac via `DAS_JIT_X64_FORCE_FEATURES` + `llc`
disasm (never execute forced artifacts).

---

## The frame

Hand-writing kernels doesn't scale and never will: llama.cpp carries ~390 hand-written
kernels (~1000 ISA paths across 7 architectures, `arch/*/repack.cpp` + `ggml-cpu-quants.c`),
and every one of them is the same loop nest with different constants — tile shape, vector
width, dot primitive, repack layout, scale fold. That's not 390 kernels; it's **one
parametric family** and a maintenance moat. We stop digging our own copy of that moat:
generate the loop nest as LLVM IR, tune by sweeping the parameter space, and let per-ISA
support collapse to a per-ISA dot-primitive emitter.

**The gap it chases:** fleet prefill is uniformly ~0.73–0.86× of llama.cpp on Genoa
(gpt-oss 0.61×) after the zvnni batch pin; on M1 prefill median is 0.92× (their engine
there is Accelerate/AMX). Decode at ≥1B is already near-parity — this is a **batch-GEMM
(prefill) program** first.

**Risk framing (Boris):** generation-via-LLVM on the box you're sitting at is expected to
just work — IR is IR. The *cross-platform* portion (emitting for targets you can't execute)
is where the annoyance lives. So the GO/NO-GO is less "can it work" and more "does one
generated perm beat our best hand kernel on real silicon" (M2 below).

---

## The architecture — three parts

### Part 1 — `[llvm_code(...)]`: external codegen hook (dasLLVM core)

The generic extension point. An annotation on an ordinary das function:

```
[llvm_code(name = "module_name::generator_function", anyarg = anyvalue, other = whatever)]
def q8q8_batch_8x4(w : uint8 const?; ws : float const?; ...) {
    // reference body — bit-exact semantics; interp, AOT, and non-matching
    // JIT targets compile this verbatim
}
```

- **At JIT time**, instead of compiling the body, the JIT calls the named das **generator
  function**, passing the annotation arguments, the name of the function to generate, and
  the AST (the generator gets the `Function` — signature, types, everything it needs).
- **The generator lives in the llvm-jit context** (the JIT is a das program in its own
  context; a user-module `[init]` can't reach it — the annotation IS the channel). Module
  wiring for now: **`llvm_user_modules.das`** — a user-edited extra-require list in dasLLVM
  daslib. End state: `require ?gemm_kernels` optional-require, the linq-adapter pattern.
  No stronger machinery for now; fine as-is.
- **ABI via helper function**: the generator calls a helper to create the LLVM function
  declaration with the das JIT calling convention (lean: helper the generator opts into,
  not JIT-pre-created). This also gives the **decline path** — the generator returns false
  (wrong ISA, illegal perm) and the JIT compiles the reference body normally.
- **Correctness tiers for free:** the reference body is the AOT gate and the bit-exact
  oracle in one move — same rule as every intrinsic today (correct everywhere, fast where
  the emitter fires).
- **Cache keying: MANUAL for now** (`LLVM_JIT_CODEGEN_VERSION` bump discipline). Folding
  the generator function's hash + its dependency closure into the DLL key gets too big;
  revisit when it bites.
- Known-missing mechanics are accepted: make it work first; the shapes of the missing
  pieces become obvious in the process.

### Part 2 — the tune framework moves into dasLLVM (and generalizes)

The tune machinery (`dasllama_tune.das` — `[tuned]`/`[dasllama_grid]`) migrates to dasLLVM
and becomes the stub factory. Example: given `add(a?, b?, count)`, a **tune macro**
generates a family of named stubs — `add_vector`, `add_unroll`, `add_vec4_unroll2`, … —
each carrying `[llvm_code(name = "addunroller", ...)]` with different arguments.

**Three modes:**

| Mode | Stamping | What runs |
|---|---|---|
| **normal run** | manifest read; **exactly the winner** is stamped — one body per function, no runtime variant dispatch at all | the app |
| **tune run** | full grid stamped | profile all stubs (interleaved ABBA is native — all variants in one process beats the env-var A/B rail), write winners to the manifest |
| **test run** | full grid stamped | **bit-exact gate**: every stub vs the reference body, no timing — generator bugs die here, never in production |

**The manifest:**

- JSON, sits **next to the app**. Resolution per function: manifest entry > the annotation's
  `fallback=` perm > reference body — a manifest with no entry for a function falls through
  to its fallback (M4, Boris: a stale manifest written before a kernel family landed must not
  silently drop it to the reference tier); an explicit `"reference"` entry forces the
  original body.
- Keys are **function names** — the best persistent ID the language has (no GUIDs
  embeddable; "function's loop N" by index is fragile under edits but accepted).
- Values are stamping instructions: *"stamp this function with this macro with these
  arguments"* and *"stamp this function's loop N with these values"* — the second kind
  **subsumes today's `[tuned]` loop-hint rail**.
- APIs: set-a-value-to-manifest (used during tuning) and read-your-own-tune-value (used by
  the macro at stamp time).

**Client contract per kernel family:** the reference function, the perm grid, the generator
name, and a probe (representative shapes to bench and compare against the reference).

### Part 3 — GEMM kernels become tune-macro clients

The original plan's kernels, re-expressed: the GEMM family is a tune macro whose stubs
carry `[llvm_code]` perms. Per perm the generator targets **two functions** — the kernel
itself and **`get_repack_type`** — stamped from the same schema, so layout and kernel can
never desync (`needs_repack`/interleave factor derive from `mr`). Load-time repack just
calls the generated `get_repack_type`.

**End state:** delete every hand-written platform-specific kernel we've built so far (the
x64 AVX matrix tiers, the arm64 laneq/sdot tiers), `[tune]` the **big GEMM** and the
**small GEMM**, and live happily ever after. The `KernelBackend` registry shrinks to
slot-shaped call-site selection — decode-vs-batch per-slot hybrid still means distinct stub
functions per regime, but that's plain das call sites, not a runtime tier registry.

---

## Settled / deferred (the first draft's open questions)

1. **Schema surface — settled:** annotation-on-stub via the generic `[llvm_code]`; the
   *tune macro* stamps stubs (the callmacro idea landed at the tune layer, not the
   generator layer — the annotation stays the JIT surface).
2. **Sweep mechanics — settled:** all-stubs-in-one-tune-binary (one JIT compile sweeps the
   family); winners live in the JSON manifest; DLL cache keying manual for now.
3. **Per-model winners — DEFERRED.** Per-model may not make the cut at all; `bake = k` and
   per-slot perm pins get decided only after M2 numbers say whether baking shapes matters.
4. **Registration locality — settled:** `llvm_user_modules.das` user-edited require list
   now, `require ?module` optional-require later. Generators run in the llvm-jit context.
5. **Hardware — settled:** M1 first (sdot), Zen2 after (avx2/maddubs), EPYC wake-up when
   everything wins.

---

## The perm vector (the knobs)

The parameter space the generator must span — the M2 kernel is written against these names
so the schema is validated by use. The generator rejects illegal perms at emit time (vreg
budget AND per-ISA legality), which in tune terms means those stubs decline and are skipped.

| Knob | Values (initial) | Notes |
|---|---|---|
| `dot` | `sdot` (NEON — **first**, the M1 leg), `vpdpbusd` (u8·s8 + sign trick), `maddubs` (VPMADDUBSW+VPMADDWD pair), `vpdpbssd` (VNNI-INT8, s8·s8 native), `mx4` (shuffle-dequant + dot) | per-ISA emitter; the sign-trick identity and its `|a|`-on-unsigned rule are in `x64_arch.md` |
| `width` | 128 (NEON q-regs), 256 (ymm), 512 (zmm) | zmm halves instruction count but watch frequency/port behavior per box — a *tuned* knob, not a derived one |
| `mr × nr` | e.g. 4×4, 8×4, 8×8, 16×4 (rows × tokens) | register-tile shape. Hard constraint: `mr·nr` accumulators + row loads + broadcast ≤ 32 vregs (16 for ymm) |
| `kstep` | 1, 2, 4 blocks (32 int8 = 1 block) per K-iteration | interacts with `acc` promotion; full unroll when K is baked (per-model — deferred) |
| `repack` | `none` (row-major), `grp<mr>` (mr-row block interleave, scales interleaved) | **interleave factor derives from `mr`** — `get_repack_type` is generated from the same perm |
| `acc` | `i32reg` (mr·nr i32 vreg tile, scale-fold at block boundary), `f32mem` (acc8-style memory accumulator) | acc8's low-thread win vs wash-at-32T says this is box-dependent — keep both |
| `scale` | `block_fold` (float(blocksum)·ws·xs per block), `late` (accumulate i32 across kstep, fold once) | `late` is only exact within the no-overflow window — generator computes the window from kstep and refuses invalid combos |
| `load` | `bcast_x` (broadcast activation dword-group × row-vector loads — the repack shape), `bcast_w` | M0 disasm decides which family the winners actually use — don't cargo-cult |
| `prefetch` | off, N bytes ahead (weights) | NT/streaming loads for fat w13/w2 streams is a candidate value (mm_ffn 1.42× is fat-stream territory) |
| `epilogue` | store, `+bias`, `+residual`, `+requant` | fused-chain epilogues become perm values instead of hand variants |
| `tail` | masked (zmm k-masks only), padded, scalar | d-tail and ntok-tail handling; per-ISA legality applies |
| `bake` | none, `k` (n and nblocks become IR constants) | the per-model axis — **deferred** |

## Tuning axes

- **Per-ISA:** which dot primitives exist at all — `cpu_supports` gating, as today.
- **Per-box:** the manifest. Tune run on the box writes it; normal runs stamp from it.
- **Per-model:** deferred (see settled/deferred #3).
- **Per-regime:** decode GEMV vs batch GEMM — GEMV perms are a sub-family (`nr = 1`,
  latency-shaped) swept separately; regime selection is distinct stub functions at the
  call site.

Sweep cost stays sane because the sweep unit is a kernel-level iso bench (the
`bench_gemm_iso.das` / `gemm_1core_probe.das` pattern) on real slot shapes, not end-to-end
decode — the tune_kernels sweep is ~1 min today; the perm sweep targets the same order.

## Milestones

**P1 — `[llvm_code]` minimal (the vehicle — START HERE).**
Annotation recognized by the JIT; generator-call machinery; ABI helper; decline path;
`llvm_user_modules.das` wiring. Hard-coded toy generator (e.g. a vector `add`) to prove the
loop: **gate — generated function bit-exact vs its reference body on this Mac, IR visible
via `--jit-dump`, decline falls back to the body cleanly.**

**M0 — reference ceiling (Mac edition; position 0: build the instrument first).**
Extend `harness/oracle/kernel_bench.cpp` to call llama.cpp's arm repack GEMM family
(`arch/arm/repack.cpp` q8_0 path) and disasm their winning NEON kernel: actual tile shape,
dot sequence, scale-fold point, load family. Dump OUR laneq tier (`--jit-dump` rail) for
the same shapes. **Note:** lcpp's Mac *prefill* number rides Accelerate/AMX (`-ngl 0` still
uses BLAS for pp) — so the honest M2 comparator on this box is **our arm64-laneq tier**
(approach validation: can generated IR beat our best hand kernel), with lcpp CPU columns as
reference. The absolute lcpp-parity chase stays x64 territory. **Gate: ceiling table per
slot shape + target IR shape on paper.**

**M1 — raw primitive emitters.**
The primitives one level down from today's whole-dot intrinsics: sdot-accumulate on given
vreg values, dword-group/lane broadcast, interleaved q-reg loads (NEON leg first); then
vpdpbusd-accumulate, sign-apply, k-masked loads, NT loads (x64 leg, emission-only via
`DAS_JIT_X64_FORCE_FEATURES` + `llc`). Plain emitter helpers inside dasLLVM — they compose
IR values, no das-side fallback of their own. **Gate: disasm of each helper matches the
hand-expected instruction, no verifier errors.**

**M2 — ONE hand-composed perm (the GO/NO-GO).**
Hand-emit one sdot register tile (M0-informed shape) as a single `[llvm_code]` stub +
hard-coded generator — no tune framework yet; the generator IS what the real generator
would produce for that one perm. Bit-exact vs the reference body; iso ABBA on kv/qo/w13/w2/cls
shapes at 1-core and multi-thread vs the laneq batch baseline. **Gate: the hand perm beats
or matches laneq on ≥1 slot shape. If it can't even match a hand kernel, stop and rethink —
we've spent one kernel, not a framework.**

**M3 — parts 2 + 3 proper.**
Tune-framework migration to dasLLVM (tune macro, three modes, manifest + its two APIs);
promote the M2 generator into the perm-parameterized family; `get_repack_type` generation;
2–3 neighbor perms bit-exact (a laneq-equivalent perm as self-check); vreg-budget/ISA
rejection tested; test-run mode gates everything. **Gate: generated == hand-emitted for the
M2 perm (same disasm); neighbors bit-exact; manifest round-trip (tune → write → normal run
stamps the winner).**

**M4 — tune + fleet + the deletion.**
Perm sweep on the Mac → manifest; Mac fleet re-sweep (`emission_bench` pp512 method);
Zen2 leg (avx2/maddubs perms); wake the EPYC for the zvnni leg + Genoa fleet re-score of
the 0.73–0.86× column. Hand-written kernel tiers get deleted only when the scoreboard says
the generated family covers them. Repack generation lands here (needed as soon as a
`grp<mr>` perm wins somewhere).

## M0/M1 results (2026-07-04, M1 Max, LLVM 22.1.5)

**M0 ceiling table** — single-thread, best-of-6, ntok=128, GMAC/s. lcpp = `kernel_bench`
(direct `ggml_gemm_q8_0_4x4_q8_0` / `ggml_gemv_q8_0_4x4_q8_0` calls, repacked, dotprod tier —
what the repack traits select on M1); ours = `gemm_1core_probe` (now platform-aware: enumerates
registered backends, per-backend repack copies, gemv column).

| shape | lcpp gemm 4x4 | **ours laneq batch** | ratio | lcpp gemv | ours laneq gemv |
|---|---|---|---|---|---|
| kv 2048×512 | 122.4 | **131.0** | 1.07× | 65.1 | 62.5 |
| qo 2048×2048 | 120.8 | **128.1** | 1.06× | 64.2 | 61.2 |
| w13 2048×5632 | 118.3 | **128.9** | 1.09× | 55.9 | 53.3 |
| w2 5632×2048 | 119.1 | **132.2** | 1.11× | 56.1 | 53.4 |

**Our hand laneq tier already beats lcpp's arm repack GEMM kernel-to-kernel on every shape.**
Disasm (their dylib vs our cached JIT DLL): identical 32-sdot lane-indexed core + 16 q-reg
loads per 32-k block on both sides; our edge = f32 scales pre-converted at repack (no
per-block `fcvtl`, one `ldp q` per 2 blocks), token-scale folded into lane-indexed `fmla`,
u2 block unroll. Their traversal re-streams weights ntok/4 times (4-token groups outer);
ours streams weights once per token-block (TB=128). row-major vec_dot 37 / portable 33 /
row-major sdot4x4 44 — repack tier ≈ 3× row-major on both engines. **M2 bar: ≥ ~130 GMAC/s.**

**M1 platform-independent-reduce experiment** (`harness/oracle/reduce_experiment.ll`,
`opt -O3 | llc -mcpu=apple-m1`, same LLVM 22.1.5 the JIT pins):

| generic IR form | arm64 | x64 znver4 |
|---|---|---|
| `vecreduce.add(mul(sext,sext))` → scalar | `sdot` + `addv` ✓ | `vpmovsxbw`+`vpmaddwd`+hadd (sane, no VNNI) |
| `partial.reduce.add(v4i32, mul(sext,sext))` | **single `sdot`** ✓ | zmm widening + `vpmulld` + extracts — garbage |
| lane-splat shuffle + partial.reduce | `dup` + plain sdot (lane NOT folded) | — |
| full block loop, generic IR only | tight hand-shaped loop, 8 dup + 8 sdot, zero spills ✓ | — |
| `@llvm.aarch64.neon.sdot` + shuffle | **indexed `sdot v,v,v[lane]`, zero dups** | n/a |

**Design conclusion:** the generator emits platform-independent IR for everything structural
(loop nest, interleaved loads, accumulators, scale folds, epilogues — all proven to lower
hand-shaped on arm64), and keeps a per-ISA emitter ONLY for the dot primitive — on arm64 a
~3-op emitter (`shufflevector` + `aarch64.neon.sdot`) that buys the indexed form (generic
partial.reduce leaves one `dup` per sdot: +100% vector µops on the 4×4 tile's dot core); on
x64 per-ISA dot emitters were already mandatory (no generic form selects a dot). An ISA with
no dot emitter = generator declines = reference body — the decline path IS the fallback tier.
This validates the perm vector: `dot` is the only per-ISA knob; everything else is generic IR.

## M2 result (2026-07-04, M1 Max) — GO

The hand-composed perm shipped as `[llvm_code]` end to end: `dasllama/dasllama_gemm_gen.das`
(the generator — emits the laneq 4×4 tile as IR: byte-GEP loads, phi loop with kstep=2 paired
blocks + odd-block tail, indexed sdot via intrinsic+shuffle, f32-scale block fold, v4f32
stores; runs in the llvm-jit context, wired via `llvm_user_modules.das`),
`dasllama/dasllama_math_gen.das` (the `[llvm_code]` stub — reference body = 4 single-token
laneq4 dots — plus the `arm64-laneq-gen` backend: arm64-laneq with only the batch tile
swapped), `harness/gen_parity_probe.das` (the exactness gate).

- **Bit-exact:** maxdiff **0** vs the hand laneq semantics on nb-even, nb-odd (tail path) and
  a production slice — identical fold order ⇒ identical bits, not a tolerance pass.
- **Machine code:** 96 sdot / **0 dup** in the tile loop — the indexed-sdot fold held in
  production; firing proven by the generator's named blocks in `--jit-dump`.
- **Iso (gemm_1core_probe, interleaved best-of-6, GMAC/s):** generated vs hand laneq batch —
  kv 130.4 vs 131.2 (−0.6%), qo **129.4 vs 126.8 (+2.1%)**, w13 **129.9 vs 128.8 (+0.9%)**,
  w2 **133.7 vs 131.7 (+1.5%)**. Matches-or-beats on all four shapes; all above lcpp's
  118–122. Gate ("beat or match laneq on ≥1 shape") passed with margin — **M3 is a go.**

Notes for M3: the impl inlines into its public wrapper (and the batch worker) for free; the
das-side const model wants IR-handle helper params spelled `var` (`LLVMOpaqueValue?` non-var
constifies the whole value chain — llvm_boost's `*Aligned` wrappers were fixed to return
non-const for the same reason); LLVM's verifier enforces phi-grouping in merge blocks —
create all phis before any other instruction. The `llvm_user_modules.das` dasllama require was
branch-local wiring at M2; the `require ?` gate landed with M3 (see below) — dasLLVM no longer
hard-depends on dasLLAMA.

## M3 result (2026-07-04, M1 Max) — tune framework + perm-parameterized family shipped

**Part 2 shipped** as `modules/dasLLVM/daslib/llvm_tune.das`: `[tune_perm(...)]` grid rows + a
trailing `[tune(gen = "generator_key", fallback = "suffix")]` on the reference function.
`DAS_TUNE_MODE` picks the mode — normal stamps exactly one winner's `[llvm_code]` onto the
function itself (manifest authoritative when present: no entry ⇒ reference body; else
`fallback=`; else reference); tune/test stamp the full grid as `<name>__<suffix>` clones plus
a `<name>_variants()` registry (emitted reference-row-only in normal mode too, so harnesses
compile/lint everywhere). Manifest = flat `{ "fn name": "perm suffix" }` JSON, **per-app by
opt-in** (Boris: a shared default is a non-starter — two apps stomp): the app declares
`[tune_manifest(name = "myapp", dir = "...")]` on `main`, and the manifest lives at
`<dir>/<name>.tune.json` resolved against the declaring file's directory (the
`get_this_module_dir` pattern — distinct names disambiguate apps sharing a folder).
`DAS_TUNE_MANIFEST` env overrides the declaration; neither ⇒ no manifest (fallback perms).
Because the root module compiles last, the declaration cannot feed the library `[tune]`
applies — instead its own apply **re-stamps** every `[tune]`-annotated function in the
program from the declared manifest (grids re-read from the by-then-attached annotations),
and injects an `[init]` so the runtime write API targets the same file. The two APIs:
`tune_manifest_get` (read-your-own-value) and `tune_manifest_set` (the harness write).
Known edges: constant-arg call sites compiled before a late re-stamp may stay on the
reference tier (bit-exact by contract; pointer-shaped kernels unaffected), and in
multi-program processes a shared library module keeps the stamps of the first program that
compiled it. Round-trip test: `tests/jit_tests/llvm_tune_manifest.das` (temp-copied client,
declaration-driven write → re-stamp → k2 tier observed).
Framework worked example: `llvm_code_selftest::add_plus_k` (emits `a+b+k` from the perm arg +
a `decline=true` rail); suite test `tests/jit_tests/llvm_code`/`llvm_tune`; CLI gates green
(grid rows 5/6/7 with declined→5, set-API → normal-run consume, authoritative-absence).

**Part 3 (M3 slice): the M2 generator is now the perm-parameterized family**
(`dasllama_gemm_gen::q8q8_tile`; stub renamed `q8q8_tile_gen`, a `[tune]` client with grid
kstep 1|2|4, kstep2+nrsplit2, and three deliberate decline rows). Knobs: `kstep` (blocks per
main-loop iteration; remainder emitted as a chain of conditional single blocks so kstep=2 IS
the M2 CFG), `nrsplit` (tokens per accumulator slice — the 4-token call contract is fixed;
nrsplit=2 runs the k-loop twice at half register pressure), `mr` + `dot`. Strides derive from
`q8q8_repack_type(mr)` in `dasllama_gemm_schema.das` — one function read by the generator at
emit time and by the runtime repack side, so layout and kernel cannot desync (`get_repack_type`
delivered as this shared derivation rather than a second generated function; revisit the
two-function form when repack generation lands). Decline rails in order: no per-ISA dot
emitter (`dot != "sdot"` on this leg), illegal perm values, q-reg budget
(`2·mr + nrsplit·mr/4 + 2·nrsplit + 2 > 32`), layout contract (`mr != 4` until M4 — the
reference body's grp4 semantics ARE the stub contract).

**Gates, all green:**
- *Generated == hand-emitted for the M2 perm:* disasm of the kstep2 tile vs the M2 baseline —
  291/291 instructions identical (only objdump symbol-name annotations differ, from the stub
  rename); 96 sdot / 0 dup preserved.
- *Neighbors bit-exact + genuinely generated:* test mode = all 8 rows exact vs the hand-laneq
  oracle on nb-even, nb-odd, production slice; per-variant disasm proves distinct shapes —
  kstep1/2/4 = 32/96/224 sdots, nrsplit2 = 96 sdots across two loop skeletons, and all three
  decline rows instruction-identical to the reference body (the rejection rail, machine-code
  proven).
- *Manifest round-trip:* tune run (2048×512×64 iso, interleaved best-of-6) — kstep2 **133.9**
  GMAC/s > kstep4 133.4 > kstep1 126.9 > kstep2_nrsplit2 119.6 > declined/reference ~85; the
  M2 perm wins on this box, consistent with the hand tier's shipped u2. Winner written via
  `tune_manifest_set`; the normal run stamps kstep2 *from the manifest* (log rail) and parity
  stays exact. Probes: `harness/gen_parity_probe.das` (normal mode), `gen_tune_probe.das`
  (DAS_TUNE_MODE=test|tune).

**Framework mechanics learned (load-bearing):** a function's annotations attach only AFTER
every apply runs — `[tune]` cannot read `[tune_perm]` siblings off `func.annotations`, so rows
route through a macro-context registry and *must be listed before* `tune(...)` in the bracket
(loud error otherwise); grid clones are annotation-free for the same reason. `generator` and
`default` are grammar keywords — annotation args are `gen=` / `fallback=`. Tuned functions
need an explicit return type (`function_to_type` runs pre-infer; an implicit result reaches
the registry as `auto`). Stamped declarations don't get their own `apply`, so `[tune]` forces
`sideEffectFlags.userScenario` itself (the P1 const-fold lesson).

**Generator wiring decoupled (post-M3 follow-up, same day):** `llvm_user_modules` now does
`require ?dasllama_gemm_gen dasllama/dasllama_gemm_register` (a new registration shim that
requires the generator implementation). The optional-require guard grew a **target-file
resolvability fallback** (C++: the collector in `ast_parse.cpp` + the parser statement in
`parser_impl.cpp`): a guarded require also loads when the target's own file resolves — i.e.
the das package is mounted — because pure-das packages have no C++ module to guard on. The
original "app requires the implementation first" two-file idea cannot work on the `-jit`
rail: the LLVM chain is injected as an *extra module* and is collected + compiled before the
app root's requires are even scanned. So the opt-in unit is the build/mount, not the app;
registered generators are name-keyed and inert for programs that never `[llvm_code]`-name
them. `typeinfo builtin_module_exists` additionally sees promoted (shared das) modules now,
so the `static_if` guard around the registration call works for das contributors. Tests:
`tests/language/optional_require.das` (+ fixture) pins the resolvability fallback and the
das-module `builtin_module_exists`; `tests/jit_tests/llvm_tune_modes.das` spawns a child
daslang with `DAS_TUNE_MODE=test` and asserts every grid row's runtime value (5/5/6/7/5);
`cant_tune_bad_grids.das` pins all six `[tune]` validation errors.

**Deferred to M4:** loop-hint manifest kind (subsuming `[tuned]`/box_profile — dasllama_tune
stays untouched and shipped this milestone), `grp<mr≠4>` repack generation + the two-function
stamp, per-regime/per-slot perms, Zen2/EPYC legs.

## M4 slice A (2026-07-04, M1 Max) — the two-function stamp + grp<mr> unlock

**Framework: `[tune_companion(fn=, gen=)]`** rows in a `[tune]` bracket (after the perm rows,
before `tune(...)` — the perm bank doubles as the order guard) stamp sibling functions with
the SAME perm from the same manifest entry, in all three modes: normal stamps the winner onto
main + companions; grid modes clone `<companion>__<suffix>` per perm and emit a
`<companion>_variants()` registry; the `[tune_manifest]` re-stamp reaches companions too. One
manifest entry = one perm decision across N functions — manifest-level desync is impossible,
and JIT-time decline coherence comes from the dasllama side sharing ONE decline predicate
between the generators. Selftest generator `llvm_code_selftest::k_value` (emits `return k`
for a `() : int` companion, honors the decline rail); jit_tests assert companion-follows-stamp
on the normal/grid/manifest rails; cant_tune_bad_grids pins 6 new validation branches.

**dasLLAMA: mr is a live axis.** The tile generator is generalized over row quads (rq = mr/4:
weight vectors 2·mr per block at `kg·4·mr + qd·16`, accumulators token×quad, per-quad scale
loads/folds/stores; mr=4 emission is instruction-identical to M2 by construction). The layout
companion `q8q8_layout_gen() : int` (generator emits `ret i32 mr`, reference body returns
grp4's 4) is what the runtime asks: the backend repack slot, the batch traversal strides, and
the mm/group3 slot choice at [init] all read it — `repack_q8q8_grp(mr)` is the one
mr-parameterized executor (byte-identical to repack_q8q8_neon at 4), and mr≠4 token tails /
GEMV / group3 fall to a generic scalar grp<mr> dot (same fold order — the GEMV perm
sub-family stays future work). Grid now: kstep 1|2|4 × nrsplit 4|2 at mr4, kstep 1|2|4 at
nrsplit2+mr8, plus three decline rows (`mr8_budget` = 34 q-regs at nrsplit4, `mr2_lanes` =
mr%4, `dot_vpdpbusd`). Probes are per-variant: the layout variants registry gives each tile
variant its mr, the tune/parity probes repack a fresh copy of the row-major master per
variant, and the oracle is computed ONCE from a grp4 copy (fold order is layout-independent).

**The FMF lesson (load-bearing).** First test run: mr8 × kstep1/kstep4 mismatched by last-ulp
while kstep2 was exact — the AArch64 machine combiner had regrouped the fold's
`(af·s4)·qs` into `af·(s4·qs)` in those loop shapes, licensed by the blanket `fast` flags
(`_jit_fast_math` stamps 0x7f on every FP instruction pre-opt). Fix in two halves:
`apply_fast_math_to_module` now fills ONLY instructions with unset flags (authored FMF wins),
and the generator authors `0x7e` (contract kept, reassoc cleared) on the fold's fmul/fadd —
the fold order is the exactness contract, so it lives in the IR flags, not in optimizer luck.
fmla fusion is untouched (contract), and the shipped kstep2 machine code is bit-identical
before/after (289/289 disasm gate below).

**Gates, all green:**
- *Grid test mode:* 13/13 rows bit-exact vs the hand-laneq oracle (incl. all three mr8 rows on
  their own grp8 repack, and the three decline rows on grp4 — the lockstep rail proven by the
  layout variants reporting 4 for declined perms).
- *Disasm invariance:* normal-mode kstep2 (the M2 perm) — 289/289 instructions identical to
  the pre-slice generator (only absolute DLL base addresses differ).
- *mr8 structure:* kstep2_nrsplit2_mr8 = 192 sdot / 0 dup (2 slices × 3 blocks × 32), all 24
  folds fmul+fmla-fused; kstep1_nrsplit2_mr8 = 64 sdot / 0 dup — genuinely distinct shapes.
- *Parity probe:* bit-exact on all three shapes under BOTH the fallback (mr4) and a manifest
  mr8 stamp — the production two-function round-trip (manifest → layout report → grp8 backend
  repack → generated tile). The oracle is always a grp4-copy laneq4 pass: the fold order is
  layout-independent, and the generic scalar dot must NOT be an oracle — full fast-math may
  reassociate ITS fold (first probe draft tripped exactly that, maxdiff ~5e-7). Corollary
  worth remembering: mr≠4 token tails / generic GEMV are correct but not bit-stable vs the
  vector tiers under fast-math — the exactness gates pin the TILE, which does the bulk.
- `LLVM_JIT_CODEGEN_VERSION` 0x37 → 0x38 (generator emission changed for fixed args).

## M4 slice B (2026-07-04, M1 Max) — the sweep: a perm the hand tier never had wins

**FP-laxity policy (Boris, same day):** bit-exactness across variants is NOT the standard —
llama.cpp holds no cross-kernel bit-parity, and `_jit_fast_math` is already declared
non-bit-exact program-wide. The reassoc pin measured as −2.5% on the kstep4-mr8 shape (the
machine combiner's regroup is a critical-path optimization), so it's dropped: generated folds
get the same blanket fast-math as all das code, and the probes gate on a TOLERANCE vs the
grp4-laneq oracle (CLOSE_REL 1e-4 / CLOSE_ABS 1e-5; legal drift observed ~1e-6 relative,
real generator bugs are orders louder — 11/13 grid rows still land bit-exact, only the
loop shapes where the combiner fires drift). The dasLLVM authored-FMF-wins semantics and the
companion const-fold guard stay — they're correct framework behavior regardless of policy.
`LLVM_JIT_CODEGEN_VERSION` 0x38 → 0x39.

`DAS_TUNE_MODE=tune` gen_tune_probe, kv-shape iso (2048×512×64, interleaved best-of-6,
GMAC/s): **kstep4_nrsplit2_mr8 wins at 137.5** — kstep2_nrsplit2_mr8 135.8 > kstep2 133.2
(the hand-tier-equivalent M2 perm) > kstep4 132.6 > kstep1 126.6 > kstep4_nrsplit2 120.1 >
kstep2_nrsplit2 118.6 > kstep1_nrsplit2_mr8 116.1 > kstep1_nrsplit2 115.3 >
declined/reference ~85. The 8-row × 2-slice × 4-block tile (16 weight vectors per block,
26 q-regs) did not exist in the hand tier — the generator+sweep found a shape hand-writing
never tried, worth **+3.3% over the shipped hand kernel** on this box. Manifest round-trip
green (winner written via tune_manifest_set → normal run stamps tile+layout from it → grp8
repack → parity within tolerance; nb-even/odd small shapes exact — kstep4's remainder chain
is straight-line, the regroup only fires in the 4-block main loop). The kstep2-mr4 fallback's
machine code stays 289/289 identical to the M2 baseline.

**Manifest missing-entry semantics flipped (same day, Boris):** entry > `fallback=` >
reference, on both the env path and the `[tune_manifest]` re-stamp (which now leaves
functions without an entry untouched instead of stripping them to reference). `"reference"`
stays expressible as an explicit entry. Pinned by llvm_tune_manifest's OTHER/REF assertions
and a GEMM-client env-path check (missing entry → `kstep2 (fallback)` in the stamp log).

**Still open in M4:** fleet re-sweep with the mr8 winner (slice C — wire emission_bench to
require dasllama_math_gen + pin_kernel_backend), loop-hint manifest kind, per-regime/per-slot
perms (GEMV sub-family unlocks deleting the hand mm tiers), Zen2/EPYC legs, hand-tier
deletion.

## Pointers

- Rails: `modules/dasLLVM/daslib/llvm_jit_intrin.das` (emitter tables + `build_vector_expf`
  composition example), `x64_avx.das` / `aarch64_neon.das` (stub+emitter pattern),
  `llvm_jit_run.das` (cache key, `fold_loop_hints`, `LLVM_JIT_CODEGEN_VERSION`),
  `dasllama_math.das` (KernelBackend registry, hybrid per-slot pin),
  `dasllama_tune.das` (`[tuned]`/`[dasllama_grid]` — the machinery being generalized),
  linq adapters (the `require ?module` optional-require precedent).
- Benches/probes: `harness/oracle/kernel_bench.cpp` (lcpp kernel iso),
  `benchmarks/matmul/bench_gemm_iso.das`, `harness/gemm_1core_probe.das`,
  `harness/avx_matrix_probe.das` (exactness gates), `benchmarks/emission_bench.das`
  (fleet pp512 method).
- Evidence: `epyc9654_measurements.md` (sessions 3b–5: why portable+pin wins today, the
  0.73–0.86× fleet column, the Genoa zmm-engine finding); `~/Downloads/M1_results.md`
  (M1 baseline: prefill 0.92×, decode 0.84× median — local, not committed).
