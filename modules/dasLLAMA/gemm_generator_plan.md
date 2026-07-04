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

## M4 slice C (2026-07-04, M1 Max) — arm64-laneq-gen is the load-select tier

**The generated family stops being probe-only.** `dasllama_common` requires `dasllama_math_gen`
behind a new **PATH guard** — `require ?llvm/daslib/llvm_tune dasllama/dasllama_math_gen` — and
the backend registers at **priority 25** with full slots, so `select_matmul_backend_for_load`
picks it over arm64-laneq (20) on arm64+jit: every Q8 model load runs the generated batch tile.
No manifest → the kstep2 fallback stamp = the M2 perm, machine-code-identical to the hand tile
(289/289), with the laneq mm/group3/rows/mx4 slots byte-shared — promotion is numerically
invisible until a manifest says otherwise. arm64-laneq stays registered for by-name pins/A-B.

**`require ?` grew a path-guard form** (core parser, both walkers): a guard containing `/` is
resolved as a FILE and there is NO target-resolvability fallback — the witness for a target
living in an always-present package (dasLLAMA's own mount) while depending on an optional one
(dasLLVM). Plain-name guards keep the registered-module-else-target-file semantics. Pinned by
two new optional_require rows (path-guard present → loaded; absent → skipped even though the
target file resolves).

**Slot coverage follows the stamped layout — decided at SELECTION time, not [init] (the
slice C bug, and the load-bearing lesson).** The first cut branched on `q8q8_layout_gen()`
inside the registration `[init]` — and `[init]`s run BEFORE the JIT installs generated code,
so the companion answered with its reference grp4 there while the load-time repack (a
runtime call) used the stamped mr8: laneq grp4 readers on grp8 weights. Every kernel-level
gate passed (they sit below the slot wiring); the model run generated fluent-looking garbage
that even benched "fast" — caught only by a token-print (`parity.das` GEN_IDS) and pinned by
the new `harness/gen_slot_parity_probe.das` (portable reference vs the gen backend through
the REAL rail: pin → backend repack → mm/batch/group3 wrappers; batch passed, mm/group3
failed exactly as grp4-readers-on-grp8 predicts). This is the same lifecycle wrinkle the
dastest-jit reference-tier note flagged — generalized: **nothing may consume a JIT-stamped
value at [init]-time.**

The fix: `KernelBackend.available : function<():bool>` — evaluated by
`select_matmul_backend_for_load` / `pin_kernel_backend` at runtime (registration-time
auto-activate deliberately does NOT evaluate it) — and TWO statically-correct flavors:
- **arm64-laneq-gen** (priority 25, `available` = stamped layout == 4): generated batch tile
  + the byte-identical laneq mm/group3/groupn/rows + interleaved mx4 family +
  `mx4_expand_interleaved` (six neon kernels flipped public for the cross-module borrow).
- **arm64-grp-gen** (priority 24, `available` = stamped layout != 4): generated batch tile +
  generic grp<mr> mm/group3 + NEW `q8q8_groupn_grp_generic` (per-region generic GEMV + bias
  post-add), NO rows core (fused chains fall back to per-op), and a **row-major mx4 family**
  (identity plane repack + sdot-tier kernels): interleaved planes + a grp<mr> Q8 scratch
  can't share the laneq expand map, so the expand goes row-major and repacks the scratch
  through the backend's own Q8 repack. mr≠4 decode rides the generic scalar GEMV — the GEMV
  perm sub-family is exactly the next coverage item, so an mr8 manifest today is a
  prefill-experiment config, not a daily driver.

Pinned by: gen_slot_parity_probe green at BOTH layouts (mr8 row tail within tolerance,
everything else maxdiff 0), parity.das mr8 GEN_IDS **token-for-token identical** to the
default stream (40 greedy tokens), and a portable unit test
(`test_backend_availability_predicate`: priority-99 unavailable backend skipped by for-load
select, refused by pin).

`emission_bench` gained the `DASLLAMA_PIN_BACKEND` rail its siblings had plus a
`backend:` log line (the sweep evidence). Batch-pin note: the donor layout guard compares
repack function POINTERS, so laneq⇄gen cross-pins are rejected even at byte-identical mr=4 —
no current config needs them; revisit if a real pin does.

**Gates:** language 1087/1087 (+2 path-guard rows), jit 305/305, dasLLAMA suite 179/179 (under
the promoted backend — the whole suite now loads models through the gen tile), gen_parity_probe
exact, grid test 13/13, gen_slot_parity_probe both layouts, parity.das token checks both
stamps.

### Slice C fleet re-sweep (M1 Max, 8 lanes, emission_bench -p 512 -n 64 --nprompts 3)

A = `DASLLAMA_PIN_BACKEND=arm64-laneq` (pre-slice hand tier), B = default (arm64-laneq-gen,
kstep2 fallback), back-to-back per model + ABBA anchors (1B/8B — run-to-run drift ±6%, so
±5% is noise). C = mr8 manifest (arm64-grp-gen, `kstep4_nrsplit2_mr8`), `-n 16 --nprompts 2`,
POST-fix (the pre-fix C numbers were garbage-but-fast and are not reported). pp = 512000/ttft.

| model | A pp | B pp | B/A | C pp | C/A | A emit | B emit | B/A | C emit | C/A |
|---|--:|--:|:--:|--:|:--:|--:|--:|:--:|--:|:--:|
| SmolLM2-135M | 4535 | 4553 | 1.00 | 4457 | 0.98 | 214.4 | 214.4 | 1.00 | 136.3 | 0.64 |
| Qwen2.5-0.5B | 2014 | 2005 | 1.00 | 1427 | 0.71 | 145.7 | 146.0 | 1.00 | 78.2 | 0.54 |
| Qwen3-0.6B | 1496 | 1471 | 0.98 | 1242 | 0.83 | 100.7 | 98.9 | 0.98 | 59.4 | 0.59 |
| gemma-3-1b | 1047 | 1044 | 1.00 | 1025 | 0.98 | 80.4 | 78.7 | 0.98 | 67.6 | 0.84 |
| TinyLlama-1.1B | 817 | 825 | 1.01 | 850 | 1.04 | 79.9 | 80.7 | 1.01 | 73.1 | 0.92 |
| Llama-3.2-1B | 801 | 809 | 1.01 | 866 | 1.08 | 68.8 | 69.9 | 1.02 | 60.7 | 0.88 |
| Qwen2.5-1.5B | 580 | 573 | 0.99 | 626 | 1.08 | 56.5 | 56.7 | 1.01 | 53.6 | 0.95 |
| SmolLM2-1.7B | 473 | 474 | 1.00 | 528 | 1.12 | 45.3 | 44.5 | 0.98 | 44.6 | 0.98 |
| gemma-2-2b | 380 | 384 | 1.01 | 429 | 1.13 | 29.9 | 29.8 | 1.00 | 31.3 | 1.05 |
| Phi-3.5-mini | 212 | 218 | 1.03 | 245 | 1.16 | 19.6 | 19.8 | 1.01 | 19.2 | 0.98 |
| gemma-3-4b | 220 | 245 | 1.11 | 276 | 1.25 | 20.5 | 21.1 | 1.03 | 21.0 | 1.02 |
| Qwen3-4B | 188 | 198 | 1.05 | 234 | 1.25 | 20.5 | 19.8 | 0.96 | 21.3 | 1.04 |
| Qwen1.5-MoE | 312 | 323 | 1.04 | 314 | 1.01 | 31.9 | 31.8 | 1.00 | 33.0 | 1.04 |
| Mistral-7B | 123 | 120 | 0.97 | 123 | 1.00 | 12.8 | 12.8 | 1.00 | 12.8 | 1.00 |
| Llama-3.1-8B | 119 | 117 | 0.98 | 118 | 1.00 | 12.2 | 12.0 | 0.99 | 12.7 | 1.05 |
| gemma-4-12B | 74 | 75 | 1.01 | 75 | 1.01 | 7.2 | 7.2 | 0.99 | 7.3 | 1.01 |
| gpt-oss-20b (mx4) | 155 | 158 | 1.01 | 77 | 0.49 | 35.1 | 36.3 | 1.03 | 33.1 | 0.94 |

Ratios: **B/A pp median 1.01 (0.97–1.11), B/A emit median 1.00 (0.96–1.03)** —
**the promotion is perf-neutral; the gen backend supersedes arm64-laneq as the load-select
tier at zero cost.** C/A pp median 1.01 (0.49–1.25), C/A emit median 0.98 (0.54–1.05).

What the honest C column says:
- **The mr8 prefill win is real and fleet-visible in the 1.5B–4B dense band:** Qwen3-4B and
  gemma-3-4b +25%, Phi-3.5 +16%, gemma-2-2b +13%, SmolLM2-1.7B +12%, the 1B–1.5B cluster
  +4–8%. Large dense (7B/8B/12B) sits at 1.00 — DRAM-bound, tile shape can't matter.
- **Decode at mr8 (generic grp<mr> GEMV, LLVM-auto-vectorized) is far better than "scalar
  stopgap" suggests:** ≥1.5B models run 0.88–1.05 of the hand laneq GEMV — bandwidth-bound
  decode forgives compute inefficiency. Small models pay hard (135M 0.64, 0.5–0.6B ~0.55).
- **The two mr8 losers are GEMV-shaped, not batch-shaped:** vocab-heavy small models lose
  ttft to the cls GEMV (Qwen2.5-0.5B 0.71 pp, 152k-row cls at scalar), and gpt-oss loses
  half its prefill (0.49) to the row-major mx4 family + row-major-expand-then-repack path.
- **Verdict: mr8 stays a per-app manifest experiment** — the GEMV perm sub-family (grp8-
  reading generated GEMV, next coverage item) and a generated mx4 family are exactly what
  gates flipping it on; the batch-side win it buys is already measured and waiting.

## M4 slice D (2026-07-04, M1 Max) — the GEMV sub-family: the three-function stamp

**The nr=1 perm sub-family lands as a THIRD companion in the same [tune] bracket.**
`q8q8_gemv_gen` is a rows-range core with the mm_rows slot signature (rows [rb, re) of one
region, no internal dispatch, rb/re multiples of the stamped mr), stamped from the SAME
manifest entry as the tile and layout — one entry, one coherent layout+tile+gemv decision;
desync structurally impossible. The generator wraps `emit_slice(tokCount=1)` in an outer
group loop (g-phi, per-group wg/sg GEPs — the group walk lives INSIDE the generated
function, one call per dispatch chunk), reference body = the hand laneq rows walk (grp4).
New knob `gkstep` (1|2|4, GEMV blocks per K-iteration — emit_block's fresh int accumulators
per block are the independent sdot chains a serial single-token laneq chain lacks); the ONE
shared `perm_declines` grows the gkstep rail, so all three generators decline in lockstep.
Grid rows carrying gkstep spell their tile knobs explicitly ("kstep2_gkstep2"), which is
what lets the tune probe key rows back to their tile family (`tile_key` strips the gkstep
piece).

**Every Q8 slot on both backend flavors is now the generated family.** mm/group3/groupn
became das traversals over the rows core (chunk-splitting at region boundaries, bias
post-add das-side), `mm_rows = q8q8_gemv_gen` directly (signature-identical), and the three
grp<mr> generic stopgaps are DELETED — the first hand-kernel deletion the mandate called
for. arm64-grp-gen thereby GAINS a rows core: fused decode chains now work at mr != 4. The
flavors differ only in the mx4 family (laneq interleaved vs row-major — the next coverage
item). The hand laneq mm/group3/groupn/rows borrow is gone from the gen backends;
arm64-laneq stays registered for by-name pins/A-B.

**The sweep grew a GEMV axis and the bench-shape lesson.** The streamed decode shape
(2048x8192, 16MB per call) is DRAM-bound and CANNOT tell kernels apart — even the scalar
reference body matches the vector tiers there (~54 GMAC/s single-thread). Differentiation
needs the cache-resident shape (2048x512 x16 reps): there **mr8 GEMV beats the mr4 hand
walk 67.4-69.0 vs 62.1-63.6 GMAC/s (~+8%)** — grp8 halves activation reloads per row — and
gkstep2 adds ~2%. Tune mode benches tile on the batch shape and gemv on both decode shapes,
then writes the MERGED winner: batch bench picks the tile knobs (and the layout), hot
decode bench picks gkstep among rows sharing those tile knobs. This box writes
`kstep4_nrsplit2_mr8_gkstep2`.

**Gates:** grid test 17/17 rows (tile AND gemv vs the grp4-laneq oracle, both layouts;
mr8 rows show the legal ~2e-6 fast-math regroup drift, mr4 exact); gen_parity_probe tile +
gemv exact at both stamps; gen_slot_parity_probe green at BOTH layouts through the real
rail (mm now rides the generated core — maxdiff 0 at mr4, 1.2e-7 worst at mr8);
parity.das GEN_IDS token-for-token identical default-vs-mr8 on Llama-3.2-1B and
Qwen2.5-0.5B (40 greedy tokens each); dasLLAMA suite under the promoted backend; fleet
C-column re-run on the mr8 loser models (table below). No LLVM_JIT_CODEGEN_VERSION bump:
emit_block/emit_slice untouched (tile emission byte-identical), and the new/changed stamped
functions self-invalidate via their AST hashes.

### Slice D fleet re-check (M1 Max, 8 lanes, emission_bench -p 512 -n 64 --nprompts 2)

B = default (arm64-laneq-gen, kstep2 fallback), C = mr8 manifest (kstep4_nrsplit2_mr8_gkstep2,
arm64-grp-gen), back-to-back per model on an idle box. The slice C C-column for these models
was the generic-scalar GEMV penalty this slice was built to remove.

| model | B pp | C pp | C/B | B emit | C emit | C/B (was, slice C) |
|---|--:|--:|:--:|--:|--:|:--:|
| SmolLM2-135M | 4555 | 4518 | 0.99 | 220.4 | 221.1 | 1.00 (was 0.64) |
| Qwen2.5-0.5B | 1992 | 1986 | 1.00 | 145.4 | 146.0 | 1.00 (was 0.54; pp was 0.71 — the 152k cls GEMV) |
| Qwen3-0.6B | 1497 | 1494 | 1.00 | 96.9 | 96.4 | 1.00 (was 0.59) |

**mr8's fleet story after slice D:** wins +12–25% prefill on 1.5B–4B dense (slice C table,
tile unchanged — gkstep is invisible to the tile), neutral on small AND large dense in both
regimes, loses only gpt-oss (0.49 pp — the row-major mx4 family, exactly the next coverage
item). The mr8 manifest is no longer a prefill-experiment config on Q8 models; a generated
mx4 family is what's left before it's the unconditional daily driver.

## M4 slice E (2026-07-04, M1 Max) — the mx4 family: one backend, one layout, four functions

**MXFP4 joins the stamp (the second quant family) and the two backend flavors merge into ONE
`arm64-gen`.** `mx4q8_gemv_gen` is the fourth companion in the same bracket — the mx4 twin of
the Q8 rows core over grp<mr>-interleaved nibble/exponent planes (`repack_mx4_grp`, the SAME
mr as the Q8 layout: one layout companion drives both repacks). The generator reuses the
whole slice-D loop machinery: `emit_block_mx4` swaps the weight-load stage for `tbl`
LUT-dequant (the doubled-e2m1 LUT baked as a constant vector — no table pointer at runtime;
one v16i8 nibble load per quad per dword-group feeds tbl-lo/tbl-hi + the same indexed-sdot
lattice) and the scale loads for an in-register vectorized `e8m0_half` (zext + the
denormal-select bit trick). `perm_declines` grew the tbl rail — four generators, still ONE
lockstep predicate. mm_mx4/groupn_mx4 are das traversals over the core (region-splitting,
bias post-add, row-major row tails); the mx4 expand's byte-for-byte positional map
generalized to any mr (nibble byte `off` of block-group bg -> q8[bg*32*mr + off] low /
+16*mr high; scale bytes 1:1), reading a new activation-time layout cache
(`KernelBackend.q8_layout` -> `active_q8_layout_mr()`, evaluated at selection time per the
slice C rule). The x64-style expand-row-major-then-repack double pass is arm64-history: the
expand writes the stamped layout directly at every mr.

**The two-flavor split dissolves.** After slice D (Q8 slots layout-driven) + this slice
(mx4 slots layout-driven), arm64-laneq-gen and arm64-grp-gen differed in nothing — merged
into `arm64-gen` (priority 25, no `available` predicate needed), the laneq mx4 borrow and
`repack_mx4_identity` wiring gone. Probes updated to the one name.

**Gates:** grid test 17/17 x THREE kernels (tile, Q8 gemv, mx4 gemv — mx4 bit-exact vs the
hand interleaved walk at mr4, ~6e-5 fast-math drift at mr8, within tolerance);
gen_slot_parity_probe grew mm_mx4 + groupn_mx4 legs (portable reference vs the real rail:
plane repack -> traversals over the generated core) — ALL slots maxdiff 0 at mr4 and mx4
maxdiff 0 at mr8; parity.das gpt-oss GEN_IDS **token-for-token identical default-vs-mr8**
(24 greedy tokens through the full rail: grp8 plane repack -> positional expand -> generated
grp8 mx4 GEMVs -> MoE decode groupn); dasLLAMA suite 179/179.

**gpt-oss fleet check (emission_bench -p 512 -n 64 --nprompts 2, back-to-back):** B (default
grp4) pp 137 t/s / emit 33.0; C (mr8 manifest) pp 145 / emit 35.7 — **the slice C mr8
gpt-oss loss (pp 0.49, the expand double pass + row-major mx4 family) is GONE; mr8 now
matches-or-beats grp4 on gpt-oss too.** With slice D's Q8 GEMV recovery, NO model loses at
mr8 anymore: the mr8 manifest is a legitimate daily driver on this box (+12–25% prefill in
the 1.5B–4B dense band, neutral-or-better everywhere else).

**Found compiler bug (repro'd, not fixed here):** a TERNARY string result passed directly to
an extern's `string implicit` parameter SIGSEGVs the compiler (plain interpolation is fine,
das-wrapper callees are fine, hoisting to a `let` is the dodge). Minimal 10-line repro
against llvm_boost's raw `LLVMBuildBitCast` binding; hit inside emit_block_mx4's s4 naming.

## M4 slice F (2026-07-04, M1 Max) — the x64 dot emitters: one grid, every ISA (emission-proven)

**The x64 legs land in the SAME generator and the SAME grid — `dot` and `width` become real
knobs.** The M1 design conclusion held exactly: the loop nest, interleaved loads, accumulator
tiles, scale folds, lane splats and stores were already generic IR, so the x64 legs are a
`TileEmit` width generalization (`rv` = rows per vector = i32 acc lanes: 4/8/16 at
width 128/256/512; `rq` becomes weight VECTORS per group = mr/rv) plus per-ISA dot chains in
ONE `dot_lane` dispatch:

- `dot=vpdpbusd` (VNNI, u8·s8): the proven dot32/dot64 emitter chain — `llvm.abs` (VPABSB,
  hoisted per weight vector) + VPSIGNB per dot at 256 / compare+negate+select at 512 (no
  512-bit VPSIGNB) + ONE `vpdpbusd.256/.512`. Exactness precondition unchanged from dot32
  (x in [-127,127], w may be -128 — |w| goes on the unsigned side).
- `dot=maddubs` (pre-VNNI, the Zen2 leg): same sign chain, dot = VPMADDUBSW + VPMADDWD(ones)
  + VPADDD (`avx2.pmadd.*` at 256, `avx512.pmaddubs.w.512`/`pmaddw.d.512` at 512).
- `dot=vpdpbssd` (AVX-VNNI-INT8, native s8·s8): ONE `llvm.x86.avx2.vpdpbssd.256`, NO sign
  trick at all (new cpuid tier `avxvnniint8`, leaf-7-subleaf-1 EDX bit 4, added to
  das_cpu_supports + `g_target_x64_vnniint8`; no fleet silicon — emission-only for now;
  the 512-bit form is AVX10-only and declines).
- mx4: `tbl1` -> `pshuf.b` ymm / `pshuf.b.512` (LUT constant broadcast per 16-byte lane;
  indices 0..15 keep bit 7 clear so the zeroing path never fires) — the e8m0 scale fold was
  already generic IR. The x64 rows' mx4/gemv companions come free through the shared slice
  machinery and decline in lockstep (one `perm_declines`, now ISA-aware: tier truth via
  `g_target_x64_*`, geometry mr % rv == 0, vq <= 2, nrsplit*vq <= 8, vreg budget
  2*nrsplit*vq + 6 <= 16 ymm / 32 zmm).

**The emission-only rail on a non-x64 box is now first-class.** `--jit-compile-only` (new JIT
CLI flag): build + verify + optimize (+`--jit-dump`), write/load/install nothing, program runs
interpreted — with `--jit-target=x86_64-unknown-linux-gnu`, cross x64 tier gates read
`DAS_JIT_X64_FORCE_FEATURES` as the ONLY tier truth (host cpuid never leaks into a cross
target; no env = no AVX emission, the pre-slice behavior). The TargetMachine feature string on
explicit x64 cross triples now folds the forced features too, and `jit_dll_basename` folds the
target triple (a latent cross-DLL cache-poison fix — a `--jit-target` artifact could
previously cache-hit a host run of the same program).

**Gates (this box):**

- **arm64 UNCHANGED, machine-code-proven:** full-DLL neutralized instruction streams of the
  kstep2-fallback stamp AND the mr8 manifest stamp are byte-identical pre/post refactor
  (64975 + 69681 instruction lines diffed) — no `LLVM_JIT_CODEGEN_VERSION` bump needed.
- **Grid 29/29 on arm64** (13 sdot rows + 12 x64 rows + 3 decline-by-design + reference):
  every x64 row declines to reference semantics, maxdiff 0.
- **Emission proof, 21/21 instruction-count gates green on the FIRST full run**
  (`harness/gen_x64_emission_check.sh`: cross dump -> llc 22.1.5, same major as the dasLLVM
  pin, `-mattr=+avx2,...,+avxvnniint8` -> llvm-objdump): busd256 tile = 96 vpdpbusd / 96
  vpsignb / 24 vpabsb / 0 pair ops; maddubs256 = 96+96 pair / 0 VNNI; bssd256 = 96 vpdpbssd /
  0 sign ops; busd512 = 96 vpdpbusd on zmm, 0 vpsignb; gemv gkstep2 = 24; mx4 = 8 vpshufb + 8
  dots per block. Histogram: 96 single `vpbroadcastd` lane splats (the generic shuffle lowers
  to memory-adjacent broadcasts — the x64 twin of the indexed-sdot zero-dup result), no
  scalarization, no spill storm.
- Slot parity + dasLLAMA/jit suites re-green on arm64; lint/format clean.

**What is deliberately NOT proven here (needs x64 silicon):** semantics of the live x64 stamps
(`DAS_TUNE_MODE=test` gen_tune_probe on Zen2/EPYC — zero extra wiring, the grid + oracle run
as-is; small test fixtures bumped d 8 -> 32 so mr16/mr32 rows have groups to cover), perf
(tune mode sweep -> manifest), and runtime selection (no `x64-gen` backend is registered yet —
see below).

**Queued for the Zen2/EPYC bring-up session (in order):**

1. **The witness companion + `x64-gen` registration.** A fifth `() : bool` companion (reference
   body returns false, generated body returns true, same lockstep predicate) gives the runtime
   the "did the stamp actually fire" bit at SELECTION time (slice C rule) — on x64 a declined
   stamp must not load-select the gen backend (its reference bodies are the scalar NEON
   fallbacks there, ~3x slower than portable). Registration mirrors arm64-gen: the das
   traversals are already ISA-agnostic.
2. Semantics + tune sweep on silicon (test mode, then tune mode -> per-box manifest; Zen2 =
   maddubs family, EPYC = vpdpbusd zmm — the session-5 lcpp zmm-engine fight).
3. gen_parity_probe's small shapes assume mr <= 8 (d=8 fixtures) — bump like gen_tune_probe
   when an mr16 manifest is actually in play.

**Ledger (perf ideas spotted, not chased):**

- **bias128 repack for vpdpbusd:** bake `w ^ 0x80` into the grp<mr> plane at repack (schema
  field, layout-companion-driven so it can't desync), dot becomes `vpdpbusd(acc, w_biased,
  x)` + one per-(block,token) correction `128 * blocksum(x)` folded at scale time — kills the
  per-dot VPSIGNB (~28% of the busd dot-stage µops). Exact (u8 = w+128 in [0,255], x s8);
  does NOT work for maddubs (PMADDUBSW pair sums saturate at 255·127·2). Measure against the
  plain sign-trick perm on silicon before adopting.
- Per-ISA `fallback=` in [tune] (the declared fallback "kstep2" is an arm64 perm; on x64 with
  no manifest the family declines to reference — correct because selection is witness-gated,
  but a per-target fallback would give manifest-less x64 boxes a live default).
- NT/streaming weight loads for the fat w13/w2 batch streams (the mm_ffn 1.42x note) — now
  expressible as a perm knob on the x64 legs.

## Direction (Boris, 2026-07-04, post slice B) — the deletion is the mandate, not a maybe

Get rid of the hand-written kernels **apart from the default ones** (the portable /
row-major auto-select tiers stay as the correct-everywhere floor), and work on the tune
kernels **until everything is wonderful on all supported architectures**. The generated
`[tune]` family is THE path — hand tiers don't wait for a per-tier scoreboard verdict; they
get replaced as family coverage lands. What that implies, in order:

1. **Slice C — promote the gen backend on arm64**: the generated family stops being
   probe-only; fleet re-sweep (emission_bench pp512) with the mr8 winner stamped, then the
   gen backend supersedes arm64-laneq as the load-select tier.
2. **Coverage the deletion needs** (each a [tune] family or a layout-driven das traversal
   over generated cores): GEMV sub-family (nr=1, latency-shaped — replaces laneq mm/mm_rows),
   group3/groupN traversals, the mx4 family (MXFP4 kernels — the second quant family), token
   tails.
3. **x64 legs**: vpdpbusd/maddubs/vpdpbssd dot emitters + width/tail perms — replaces the
   whole AVX kernel matrix (avx_kernel_matrix.md). Zen2 desktop first, EPYC for zvnni.
4. **Delete**: arm64-laneq tier, x64 AVX matrix tiers, dasllama_tune's [tuned]/box_profile
   rail (subsumed by the loop-hint manifest kind), keeping portable/default backends only.

**Still open in M4 proper:** loop-hint manifest kind; per-slot perms. (Slices C–F above
delivered the promote, the GEMV/mx4 coverage, and the emission-proven x64 dot emitters; the
x64 runtime bring-up — witness companion, registration, silicon gates — is the queued Zen2/
EPYC session, slice F section above.)

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
