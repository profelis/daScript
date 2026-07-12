# dasLLAMA API Rework — Plan

**Status:** Phases 1-7 done — core API, arch registry + physical arch/kernel seams (6a/6b), chat layer, and the P7 kernel auto-tuner (grid emission + `[tuned]` reconstitution + TB cliff-guard). Design locked 2026-07-01. All seven T1/T2 model-support waves landed (see [Model-support plan](#model-support-plan--the-t1t2-waves-agreed-2026-07-01)), and the [facade + docs wave](#the-facade--dasllamadasllamadas-landed-2026-07-02) landed 2026-07-02, followed by the [tutorials wave](#the-tutorials-wave--tutorialsdasllama-landed-2026-07-02) the same day. **Next: the performance-ledger pass.**

This is the design record for unifying the dasLLAMA user-facing API and making the
backend extensible. It carries the **why**; the code carries the how. Keep it current
as phases land.

## Goal & priorities

In priority order (Boris, 2026-07-01):

1. **A clean user-facing API** — one way to load a model, tokenize (both directions),
   run, and sample. Today every demo re-implements these.
2. **An extensible backend — two seams:**
   - **arch/block seam** — new model architectures (incl. MoE) slot in without editing
     the core forward pass;
   - **kernel/ISA seam** — new platform kernels (x64 AVX/VNNI) slot in behind the same
     registry the ARM NEON backend already uses.
3. **The tune macro** — per-box kernel tuning driven from a config loaded at compile time
   (see [Tune macro](#tune-macro--for-loop-attribute-reification)).

A **minimal unified chat app stays above the line**: bringing up a new architecture means
talking to it to sanity-check. Nothing fancy — roughly what the current per-model REPLs
do, collapsed into one. Tool use / an OpenAI server are *demonstrations*, below the line.

### The invariant

The engine is validated **token-for-token** against 5 oracles (stories15M, TinyLlama
v0.3/v1.0, Llama-3.2-1B, Llama-3.1-8B) plus the per-arch parity fixtures. **Every phase is
a mergeable PR that keeps that green**, and the dense path stays **bit-identical** until
MoE is a genuinely *new* code path. A refactor that changes a single token is a bug.

## Scope — Tier 1 + Tier 2

What varies across transformer architectures, and how deep we cut:

| Tier | What varies | Status |
|---|---|---|
| **1 — scalar knobs** | RoPE variant/scaling, RMS vs LayerNorm, pre/post-norm, SiLU vs GeLU, QKV bias, softcaps, sliding window, embed scale, head_dim≠dim/heads | **Handled today** — `Config` flags. A new dense llama-like = a few flags. |
| **2 — block swaps** | **MoE** (FFN → router + experts), QK-norm, partial/pruned RoPE, per-layer attention patterns (SWA ratios, per-layer θ, NoPE layers), shared KV cache (Gemma-4: last-N layers reuse earlier KV), per-layer embeddings (PLE), attention sinks, parallel attn+FFN | **This rework.** Not flags — they change block dataflow. See the model-support wave plan below. |
| **3 — deep forks** | MLA / compressed KV (DeepSeek-V3), **hybrid linear attention** (Qwen3.5/3.6 Gated DeltaNet, Mamba), multimodal, bespoke sparse attention (e.g. GLM-5.2 "IndexShare") | **Deferred.** Needs a pluggable KV-cache + attention core, not just blocks. |

## Target surface (3 layers)

### Layer 0 — core
```
def load_model(path : string; mode = QuantMode.fp32) : Model     // arch auto-dispatched from GGUF meta
def create_session(model : Model; max_context = 0) : Session     // 0 = model's trained ctx; Model → many Sessions

// unified tokenizer facade on the model (SPM/BPE chosen internally)
def encode(model; text : string; add_special = true; parse_special = false) : array<int64>
def decode(model; ids : array<int64>) : string
def piece (model; id : int64) : string                           // one token — for streaming

def eval(model; var session; tokens : array<int64>)              // THE primitive; session owns n_past
def sample(var session; params : SamplingParams) : int64         // greedy = SamplingParams(temp=0)
def stats(session) : Stats                                       // ttft, prefill tok/s, gen tok/s
```
`Session` owns its own `n_past`, so callers never pass `start_pos`. Prefill and generation
become the **same call** at different batch sizes: prefill = `eval(prompt)`, step = `eval([tok])`.

### Layer 1 — generation
```
def generate(model; var session; prompt : array<int64>; params : SamplingParams; max_tokens : int) ...
```
Streaming is a **trailing callback block** — `respond(...) $(piece : string) : bool { ... }`,
return `false` to stop. Absorbs the ~60-line `sample()` copy-pasted into every demo today.

### Layer 2 — chat (minimal, above the line)  *(built — Phase 5)*
```
struct Message { role : Role; content : string }                 // Role = system | user | assistant | tool
def create_chat(model; system = ""; max_new = 256) : ChatSession
def add_user(var chat; text : string)
def render_turn(model; chat) : array<int64>                      // the turn's prefill ids, no model run — inspect/test
def respond(model; var chat; params : SamplingParams) $(piece : string) : bool { ... } : string
```
The model is threaded through `respond` (like `eval`/`generate`) rather than held by the ChatSession, so
there is no model-pointer lifetime to manage. `respond` renders the turn, prefills it, streams the reply
through the callback block (return `false` to stop), terminates the turn in the KV cache, appends both
turns to `chat.history`, and returns the full reply text; `stats(chat.session)` reports its timing.
**Context cap:** the session's KV cache is sized to `model.config.seq_len`, so a caller loading a
large-context model (Llama-3/Phi = 131072) must cap `model.config.seq_len` first (as every REPL does) —
the full cache would exceed the 4 GB per-array limit.

## The two backend seams

### Arch/block seam  *(built — Phase 4)*
`configure_arch`'s monolithic `switch` is now an **arch registry** — each arch self-registers
via `[init]` (the same pattern `dasllama_math_aarch64_neon.das` uses for its kernels). As built:
```
struct ArchBlocks { attn_decode; ffn_decode; attn_prefill; ffn_prefill }   // copyable fn-ptrs, ride on the Model
struct ArchDesc   { name; configure; blocks : ArchBlocks; chat : ChatTemplate }   // registry-only
register_arch("llama", { configure_llama, std_blocks(), LLAMA3_CHAT })
```
Blocks are **function pointers, one per (attention|ffn) × (decode|prefill)** — decode is the fused
single-token path, prefill the batched path, so the two forward loops call `t.blocks.attn_decode(t, s,
l, pos)` / `t.blocks.ffn_prefill(t, s, l, npos)` etc. `ArchBlocks` (all fn-ptrs, copyable) is copied
onto the `Model` at load; the full `ArchDesc` (non-copyable — holds a `ChatTemplate`) stays in the
registry. All four current arches are dense llama-likes → they share `std_blocks()` and differ only in
config flags, tokenizer backend, and chat template. **Bit-identical**: the block bodies are the old
per-layer code moved verbatim (proven token-for-token via the oracle suite + an A/B source diff across
all 5 GGUF arches). GeGLU-vs-SwiGLU stays a `ffn_act` flag *inside* the shared dense FFN block.

MoE is the one genuinely new block — it registers a different `ffn_*` here without touching the
forward loops. **Build it general — shared experts + routed top-k, gating pluggable (sigmoid |
softmax)** — the GLM / DeepSeek / Qwen2-MoE shape, *not* Mixtral's plain-routed special case, or
GLM/DeepSeek force a re-plumb. First MoE oracle: a small shared-expert MoE (lean Qwen1.5-MoE-A2.7B),
decided when we get there.

**Chat template — data only in Phase 4.** `ChatTemplate` is an ordered part list per turn
(`text` | `special`-token-spelling | `content` slot) + `add_bos` + stop-token spellings; the four
arches' templates live in the registry, validated for well-formedness by `test_arch_registry.das`.
The **renderer** (parts → token ids, resolving special spellings) lands with the Phase-5 chat engine.
One known wrinkle it must handle: GGUF `general.architecture` is `"llama"` for *both* Llama-3 and
Llama-2/TinyLlama, which use different chat formats — so per-model disambiguation (reading the GGUF
`tokenizer.chat_template`, or detecting special tokens) is a Phase-5 concern. The registry's `"llama"`
template carries the Llama-3 instruct format (the flagship).

### Kernel/ISA seam  *(built — Phase 6b)*
A **named `KernelBackend` registry**, symmetric with the arch registry. `dasllama_math.das` owns the
abstraction (the `MatmulQ8Q8*Fn` typedefs, the `g_mm_q8q8*` active pointers, the `matmul_q8q8*` wrappers,
`repack_q8q8_weight`, and `register_kernel_backend` / `select_kernel_backend` / `pin_kernel_backend` /
`select_matmul_backend_for_load`). Each ISA module self-registers its backend(s) at `[init]`:
```
struct KernelBackend { name; mm; batch; group3; repack; needs_repack; priority }   // copyable
register_kernel_backend(KernelBackend("arm64-laneq", …, needs_repack = true, priority = 20))
```
- `dasllama_math_default.das` — the **portable** backend (`dot_q8q8` + the three portable kernels + the
  parallel_for profiler), registered at priority 0. The fallback everywhere; **required by any q8·q8
  consumer** (the `g_mm_q8q8*` pointers panic-stub until a backend registers).
- `dasllama_math_aarch64_neon.das` — `arm64-sdot` (row-major, priority 10) + `arm64-laneq` (interleaved
  repack, priority 20), gated on `jit_enabled() && get_architecture_name() == "arm64"`.
- `dasllama_math_x64_avx.das` — the SESSION-2 mirror: register `x64-vnni` (SDOT → VNNI `vpdpbusd`) exactly
  the same way. **No edit to `dasllama_math` or the wrappers** — it just adds a file + a `[init]`.
  The x64 bring-up is fully documented in `x64_arch.md` (the seam map), `get_x64_going.md`
  (the runbook), and `tune_for_this_box.md` (per-box tuning + measurement discipline).

**Two selection tiers** (mirroring the hardware): `register_kernel_backend` auto-activates the
highest-priority **no-repack** backend so direct callers (tests/benches, row-major weights) get the best
kernel with no load step; `select_matmul_backend_for_load()` (called by the loader on the Q8 path) picks
the best **overall** backend — including a repack one — and returns whether the loader must repack.
`pin_kernel_backend` forces a named backend for A/B benchmarking. Validated token-identical (100/100 JIT +
AOT) + `test_kernel_backend.das`.

## Tune macro — for-loop-attribute reification

**The tune surface is the kernel loops' attributes**, not just the runtime `TB` knob:
```
for [vectorize, vectorize_width = 8, unroll_count = 2] (j in range64(n)) { ... }
```
These live throughout `dasllama_math.das` (dot / axpy / add / mul / scale / copy / silu /
softmax / rope) and `_aarch64_neon.das`, and the `8` / `2` / `4` / `16` are **literal ints
today**. `vectorize` / `vectorize_width` / `unroll_count` are **not** grammar keywords —
they're generic `for [...]` annotation-args recognized semantically.

The tune macro must **load a box config at compile time and emit the right numbers into
these attributes**. Two routes; the deciding question is phase-ordering (are loop
attributes baked before macros run?):

- **(a)** grammar accepts a const-*expr* in the attribute value (`unroll_count = TUNE.unroll`)
  — a parser/AST change; or
- **(b)** a loop/function macro rewrites the literal annotation-args before codegen — no
  grammar change, using the same AST-rewrite machinery `dasllama_par.das` already uses for
  `maybe_parallel_for`.

This is a **daslang-core capability**, broader than dasLLAMA and broader than `TB`.

**Universal vs per-box:** the token-blocking loop-nest structure and repack concept are
universal (stay in the shared path). `TB`, `unroll_count`, `vectorize_width`, thread count,
and the ISA are the **per-box config** — a box-profile the loader reads. See the memory
roadmap + `dasllama_kernel_opt_findings` for the measurement methodology (interleaved A/B,
the ggml per-op-timing patch) — the make-or-break for any tuner is measurement, not codegen.

## Decisions

- **FP32 load default stays.** Do *not* silently reroute the token-exact tests; demos pass
  `q8` explicitly.
- **Tool use is parked** — a curiosity. v1 (later) = OpenAI-style: parse tool-call text out
  of the generation + inject tool definitions into the system turn. No core-engine change.
- **GLM-5.2 is out of scope** — 744B MoE / ~40B active, 1M ctx via bespoke "IndexShare"
  sparse attention (Tier 3); ~370 GB even at 4-bit. Not a CPU target. Its family (GLM-4.5/4.6)
  informs the general MoE-block shape above.

## Phase order

Each phase is a mergeable PR; all oracles stay green; dense path bit-identical until MoE.

1. **Naming + `eval`** ✅ — `Transformer → Model`, `RunState → Session`, `n_past` into
   `Session`, `eval()` / `create_session()`. Pure refactor, token-identical.
2. **Tokenizer facade** ✅ — `SpmTokenizer` / `BpeTokenizer` (renamed) behind a unified
   `Tokenizer` (`kind` + both backends); `load_tokenizer_auto` picks the backend from the GGUF's
   `tokenizer.ggml.model`. `encode` / `decode` / `piece` on both `Tokenizer` and `Model`;
   `load_model` loads weights **and** tokenizer. Existing raw paths unchanged. *(test_facade.das)*
3. **Sampling** ✅ — `SamplingParams` (defaults = greedy: temp 0, penalty 1.0 → the greedy branch
   calls the existing `argmax`, so bit-identical). `Session` owns the RNG (`rng`) + repetition
   window (`recent`) + top-k scratch. `sample(session, params)` lifts the copy-pasted demo
   `sample()`; streaming `generate(model, session, prompt, params, max, blk)` with a callback block
   (`return false` to stop). `set_seed`. *(test_sampling.das)*
4. **Arch registry + block seam** ✅ — `configure_arch` switch → `[init]` self-registering
   registry (`ArchDesc` = configure + `ArchBlocks` fn-ptrs + `ChatTemplate`); attention/FFN are
   function-pointer blocks (decode + prefill) the forward loops dispatch through; chat-template
   descriptor is a registry field (data only — renderer is Phase 5). Blocks resolved onto the Model at
   load (also for the llama2.c `load_checkpoint` path). No new arch; dense path bit-identical, proven
   token-for-token (oracle suite + A/B source diff on all 5 GGUF arches). *(test_arch_registry.das)*
5. **Minimal unified chat app** ✅ — new `dasllama_chat.das` (layer 2): `Role`/`Message`/`ChatSession`
   + `create_chat`/`add_user`/`respond` (streaming callback block) + `render_turn`. The **renderer**
   turns a `ChatTemplate` part list into token ids by *segment accumulation* — each maximal run of
   text/content between special tokens is encoded as ONE segment, which reproduces every old per-model
   REPL's prefill token-for-token (proven in `test_chat.das` for all 5 families). Special tokens
   resolve by spelling: BPE via `special_id`, SPM via the vocab lookup (added `special_id(SpmTokenizer)`
   + the `Tokenizer`/`Model` facades, plus `bos_id` for `add_bos`; SPM `bos_id`/`eos_id` now loaded from
   GGUF). The `"llama"` collision is resolved by **tokenizer backend** — BPE ⇒ Llama-3 instruct
   (registry default), SPM ⇒ Zephyr/TinyLlama (a local `zephyr_chat_template()`); `Model.arch` carries
   the GGUF architecture for this. `stats()` (ttft + prefill/gen tok/s) added, filled by the instrumented
   streaming `generate()`. Examples collapsed: `chat.das` (one REPL, any model) + `run.das` (one
   completion + stats); the 4 other chat REPLs + 2 runners deleted, their oracles migrated into
   `test_parity.das` (TinyLlama-v0.3, Llama-3.2-1B). Full suite 100/100 JIT + AOT.
6. **Arch files + kernel-backend registry** *(done)* —
   - **Arch files (done):** split the `dasllama_transformer.das` monolith so each architecture lives
     in its own `dasllama_arch_*.das` (config setter + `[init]` registration + chat template). The
     shared engine is `dasllama_common.das`; `dasllama_transformer.das` is now a thin umbrella
     (`require dasllama_common public` + one require per arch, firing each arch's `[init]`), so every
     existing `require dasllama/dasllama_transformer` is unchanged — zero consumer churn. `std_blocks()`
     is the only symbol promoted to public (the arch files' one pull from common); block bodies, forward
     loops, and config are byte-for-byte unchanged, so the suite stays **token-identical** (100/100 JIT
     + AOT). Adding an arch = a new file, never touching the core; MoE brings its own blocks in its own
     file. See [What split into files](#what-split-into-files-done--phase-6).
   - **Kernel-backend registry (done):** the `KernelBackend` registry + `dasllama_math_default.das` split
     — each ISA module self-registers at `[init]`, `select_matmul_backend_for_load()` drives the load-time
     repack handshake, `dasllama_math_x64_avx.das` mirrors NEON with no core edit. See
     [Kernel/ISA seam](#kernelisa-seam--built--phase-6b) + [What split into files](#what-split-into-files-done--phase-6).
7. **Tune macro + loop-attribute reification** — depends on 6.

**AOT note (phase 5):** the `Model`↔`ArchBlocks` cycle (Model holds ArchBlocks by value; ArchBlocks's
fn-ptr fields reference Model) tripped the AOT C++ emitter — it emitted `Model` before `ArchBlocks`
(incomplete-type + `sizeof(Model)` mismatch). That emitter bug is **already fixed upstream** (an AOT PR
pending merge). We also declare `ArchBlocks` + its typedefs *before* `Model` in the source — a harmless
defensive ordering (legitimate on its own; emission is source-order for non-recursed structs) that keeps
the AOT green on this branch before that PR lands, and can stay after.

**Below the line (demonstrations):** ✅ an OpenAI-compatible server — `utils/dasllama-server/` (the
acceptance test: it builds reaching **only** public facade verbs, so the API is right). Chat +
completions (SSE + buffered), audio transcriptions/translations, and **`/v1/embeddings`** (mean-pooled,
L2-normalized, over the new facade `embed` → engine `embed_forward` hidden-state path) all ship, with a
model-gated conformance test (`test_openai_server.das`) driving it over the real dashv HTTP client.
**Remaining:** tool / function calling — parked as the next follow-up.

## Model-support plan — the T1/T2 waves *(agreed 2026-07-01)*

Each wave = one engine capability + the smallest popular model that proves it, shipped as a
mergeable PR with a frozen `simple_ids` oracle fixture (`test_parity.das`) + README row. The
local llama.cpp checkout (2026-06-27) implements every target arch — port each one from its
`llm_build_*` in `src/llama-model.cpp` (the definitive spec), never from blog posts. Models
are Q8_0 GGUFs into `~/Work/llama.cpp/models/` unless noted.

| Wave | Engine delta | Oracle model(s) | ~GB |
|---|---|---|---|
| **0** | none — verify + fixtures (incl. backfilling Qwen2.5-1.5B + Phi-3.5), README rows; chat-template *detection* (sniff GGUF `tokenizer.chat_template` → named registry template) | Mistral-7B-Instruct-v0.3 (GGUF arch is `"llama"`), SmolLM2-1.7B-Instruct | 7.7 + 1.8 |
| **1** | QK-norm — Config flag + per-layer `attn_q_norm`/`attn_k_norm` weights, per-head RMSNorm pre-RoPE in the shared attn blocks (a flag like `ffn_act`, not a block swap); `<think>`-stripping in chat history | Qwen3-0.6B (fast iteration), Qwen3-4B-Instruct-2507 (fixture) | 0.7 + 4.3 |
| **2** | per-layer attention patterns — generalize the hardcoded `l % 2` SWA alternation to `sliding_window_pattern` (gemma2 = 2, gemma3 = 6), per-layer RoPE θ (dual rope tables); SmolLM3's NoPE layers = same machinery | gemma-3-1b-it, gemma-3-4b-it (opt: SmolLM3-3B) | 1.1 + 4.5 |
| **3** ✅ | **Gemma 4** — GGUF ground truth revised the plan: the 12B has NO shared KV and NO PLE (`shared_kv_layers = 0`, `embedding_length_per_layer_input = 0` — both are E-series features; the loader now panics honestly on either). What it DOES need, all shipped: heterogeneous per-layer geometry (sliding 16Q/8KV×256 vs global 16Q/1KV×512 — per-layer weight-offset arrays, class-max scratch, per-layer KV-cache packing), explicit bool-array SWA pattern (`swa_mask`), p-RoPE freq factors on global layers only (full rotation, `dimension_count` == head size per class — pruning is a loader panic), weightless V-norm, V-from-K on the no-`attn_v` global layers, unit attention scale, per-layer `layer_output_scale`, final softcap, `suppress_tokens` logit bias, and the new `gemma4` SPM-style-BPE tokenizer (metaspace + newline-only pre-split + byte fallback; 46/46 on the official corpus). Shared-KV + PLE move to a follow-up E-series wave (E2B ~2GB oracle) | gemma-4-12b-it — 40/40 counting + 40/40 window-engaged ~1490-token prompt | 12.7 |
| **4** ✅ | **MoE FFN block** via the ArchBlocks seam (proves Phase 4 — the forward loops were untouched; qwen2moe registers `moe_blocks()`). Shipped: router → top-k over probs-before-selection, pluggable gating (`MoeGate.softmax\|sigmoid` from `{arch}.expert_gating_func`), `norm_topk_prob` + `expert_weights_scale` slots, routed experts + sigmoid-gated **shared expert**; expert-major layout (expert e of layer l = a plain 2D matrix at `we*_off + (l·n_expert+e)·dim·n_ff_exp`) so every existing kernel incl. the arm64 repack applies per expert; 3D `ffn_*_exps` transcode in one contiguous read; honest panics for grouped routing / gating-func 3 / `exp_probs_b` / expert biases. Decode fused; prefill naive per-token (grouped GEMM → ledger). Stretch models not pursued this wave: gemma-4-26B-A4B @ Q4_0, Qwen3-30B-A3B (qwen3moe = QK-norm + `norm_topk_prob`, no shared expert — a thin arch file when wanted) | Qwen1.5-MoE-A2.7B-Chat — 40/40 counting AND 40/40 prose, both prompts token-for-token | 15 |
| **5** ✅ | **gpt-oss** — everything the plan row named plus what the GGUF ground truth added. Shipped: attention sinks (per-head sink logit joins the softmax max + denominator, no V contribution — decode `softmax_sink` + all three prefill cores; flash seeds its online softmax with max = sink, sum = 1); MXFP4 decode (E8M0 half-scale + doubled-e2m1 nibble LUT, one new `gguf_read_tensor_f32` arm → the existing dequant→self-Q8 path covers it); YaRN rope with ZERO engine change — the NTK-by-parts ramp is a per-pair effective position scale, so the loader synthesizes `rope_freqs[j] = 1/(fscale + ramp_j·(1−fscale))` and folds the 1 + 0.1·ln(factor) magnitude into `rope_mscale`; `MoeGate.softmax_weight` (top-k on raw biased logits, softmax over the selected k; knockout sentinel → −FLT_MAX); router + per-expert biases (fblob stacks, expert-major) + attention output-projection bias; `FfnAct.swiglu_oai` (clamped, +1 up branch, scalar + exp4 float4); pre-FFN norm under the `post_attention_norm` name; gpt-4o/o200k pre-tokenizer (llama.cpp's exact case-class approximation: contraction suffixes, upper*/lower+ letter runs, `/` in punct tails, no-BOS default) + Harmony-lite chat template with `<|channel|>` detection sniff | gpt-oss-20b — 40/40 counting + 40/40 window-engaged 449-token prompt (encoded in-test), both FIRST TRY; tokenizer id-for-id vs llama.cpp on counting/contraction/whitespace probes | 12.1 |
| **6** ✅ | *(infra, last)* lifted the linear-allocator 4GB limit — `HeapChunk` `size`/`offset` went `uint64` and `LinearChunkAllocator` dropped every `UINT32_MAX` cap (`allocate`/`free`/`setInitialSize`, the `reset` clamp; virtual `grow` is 64-bit — one override, `DebugInfoAllocator`). Regression tests in `tests-cpp/small/test_heap_64bit.cpp`: an ungated >4GB `setInitialSize` probe plus gated (`DASLANG_HUGE_HEAP_TESTS=1`) >4GB single-chunk and default-context-heap tests. End-to-end on the default heap: Mistral-7B's 7.1GB Q8 blob loads and matches its fixture token-for-token (`harness/parity.das` dropped its `options persistent_heap`), and Llama-3.2-1B at native `seq_len` 131072 allocates two exactly-4GiB single KV arrays and generates. Workaround disposition, re-justified honestly: the tests **keep** `options persistent_heap` — since the explicit-delete discipline landed, it's what makes `delete` really free between fixtures (linear free is a mid-context no-op, so multi-GB weights would accumulate) — and the `seq_len` caps **stay as RAM savers** (native 131072 KV is 8–64GB of fp32); both kinds of comment now state the real reason instead of the vanished cap | none — regression = existing suite + the new tests-cpp cases | — |

Out of scope, and why: Qwen3.5/3.6 (Gated-DeltaNet hybrid linear attention → Tier 3),
Llama-4 (109B+), DeepSeek V3+/GLM-5 (MLA / bespoke sparse → Tier 3), Mixtral (superseded,
too big, plain-routed anyway).

**Chat, long-term (agreed):** stage 1 = the wave-0 template *detection* (string-sniff the
embedded `tokenizer.chat_template` for `[INST]` / `<|im_start|>` / `<start_of_turn>` /
`<|start_header_id|>` … → pick a named registry template — fixes Mistral and the `"llama"`
collision with no template execution). Stage 2 — a Jinja-subset interpreter in daslang (the
llama.cpp "minja" route, executes the embedded template directly) — is deliberately deferred
until the named registry stops scaling; the realistic forcing function is gpt-oss's
channel-based Harmony format at wave 5. Chat remains layer 2 throughout.

## The facade — `dasllama/dasllama.das` *(landed 2026-07-02)*

One require is the public API: `require dasllama/dasllama` re-exports the engine
(`dasllama_transformer public` — which also fires every arch `[init]`) and the chat layer
(`dasllama_chat public`), and defines the **documented, curated surface** — the three layers above
as 14 `//!`-documented stubs (`load_model` / `create_session` / `encode` / `decode` / `piece` /
`eval` / `sample` / `set_seed` / `stats` / `generate` / `create_chat` / `add_user` / `render_turn`
/ `respond`). Everything else stays reachable through the re-export, deliberately undocumented.

- **Naming:** wherever the facade takes the good name, the engine spelling carries a trailing
  underscore (`load_model_`, `eval_`, …) — a same-name stub plus a public re-export would be an
  ambiguous overload at every call site. The raw greedy `generate(t, s, prompt, steps)` keeps its
  name (different arity, no ambiguity — the token-exact oracle path). Public-path consumers
  (examples, `test_parity`/`test_facade`/`test_chat`/`test_sampling`/…) require the facade and use
  the good names; internal/kernel tests and the chat engine's internals use the `_` spellings.
- **Examples are the completeness gate:** `run.das` / `chat.das` require ONLY `dasllama/dasllama`
  from the module — if a demo needs something the facade lacks, the facade grows, not the require
  list. Both verified end-to-end after the switch (TinyLlama completion + chat smoke).
- **Docs:** das2rst registers ONLY the facade module (new stdlib section `sec_ai.rst`,
  `generated/dasllama.rst`; `doc.yml` path filters now include `modules/dasLLAMA/dasllama/**`).
  Engine modules stay undocumented by design — Model's ~40 offset fields are not API. The types the
  facade signatures mention (`Model`, `Session`, `QuantMode`, `SamplingParams`, `Stats`,
  `ChatSession`) get hand-written opaque stanzas emitted by `document_module_dasllama`'s
  `DocsHook.afterEnums` under the exact `:ref:` labels the signature renderer produces, so
  cross-references resolve without documenting internals. The module header
  (`handmade/module-dasllama.rst`) carries the supported-model-family list (and, later, tutorial
  links).
- **🔑 `//!` placement:** the doc extractor (`daslib/rst_comment`) attaches a docstring only when
  the `//!` block is the FIRST thing *inside* the function body — an above-def `//!` is silently
  discarded (this is why no engine docstring ever extracted; the engine's above-def `//!` remain as
  source comments only).
- **Drift detector** (`tests/dasLLAMA/test_facade_docs.das`): every facade def has a body-leading
  `//!` (and no inert above-def `//!` exists); facade stubs ↔ engine `_` spellings stay 1:1 in both
  directions; the examples stay facade-only. Negative-probed: an undocumented extra stub fails it.

## The tutorials wave — `tutorials/dasLLAMA/` *(landed 2026-07-02)*

Six tutorials written strictly against the facade, each a runnable single-file
`main()` (project convention: `tutorials/<area>/`, never `modules/<X>/tutorial/`), with paired
RST pages under `doc/source/reference/tutorials/` and a toctree section, plus tutorial links on
the stdlib module page. The teaching model is SmolLM2-135M-Instruct Q8_0 (~145MB llama-arch
GGUF; models aren't shipped — path via CLI arg or `DASLLAMA_MODEL`):

1. **hello_generate** — load_model / encode / decode / piece / generate / stats.
2. **chat** — create_chat / add_user / respond, multi-turn KV memory, history, render_turn
   (specials are atomic ids, invisible to decode).
3. **sampling** — greedy determinism + the 135M repetition loop, penalty breaking it,
   temp / top-k / set_seed reproducibility.
4. **sessions_and_memory** — KV sizing + the cap-seq_len-BEFORE-create_session rule, session
   independence, manual eval/sample loop, persistent_heap + delete discipline.
5. **performance** — jit_enabled, job-queue requirement + `DAS_JOBQUE_THREADS`, prefill-vs-gen
   physics, fp32/q8/q4 measured table, `_jit_fast_math`.
6. **add_an_arch** — registry walkthrough (arch_names / ArchDesc / std_blocks / chat parts /
   register_arch), no model needed.

Tutorials joined the CMake install + `dry_run_tutorials` compile gate. One durable lesson baked
into 04's structure: a fat `main()` frame plus the forward-pass call chain overflows the default
16KB context stack (das frames are statically sized for all locals) — model-driving mains stay
lean, one function per section.

### Performance ledger (living — address after the model waves)

Standing rule (Boris, 2026-07-01): any performance possibility spotted while doing wave work
gets a note HERE instead of being acted on mid-wave — the model waves optimize for correctness
and coverage; this ledger is the backlog for the perf pass that follows them. Every entry says
what it costs today and what the fix would change.

- **Embeddings path (spotted building `/v1/embeddings`, 2026-07-06).** Two small items, neither
  chased: (1) `embed_forward` takes approach A — reuse `forward_prefill` then re-norm every
  position — which pays **one wasted last-position classifier GEMM** (vocab×dim) per embed call,
  because `forward_prefill` always runs the final norm+classifier on the last token. Fix would be
  to split the transformer stack out of `forward_prefill_body` (a `forward_prefill_stack` helper)
  and call it directly, skipping the classifier; cost is one GEMM against a whole forward, so
  negligible until embeddings are hot. (2) The server's `/v1/embeddings` calls facade `embed`
  per input, which **creates + deletes a full KV-cache session per input** — for a batch of N
  strings that's N session allocations. Fix: a dedicated reused embed session in the server (the
  facade would need a session-taking `embed` overload, or the server reaches the public
  `embed_forward` primitive — but that breaks the facade-only invariant, so the overload is the
  clean path). Both are backlog; the server is serial and embeddings are low-frequency.
- **q8 GEMV loses to fp32 on cache-resident weights without VNNI (zen2 whisper decoder,
  2026-07-08).** Decoder-q8 stage A/B on zen2 tiny/jfk: logits GEMV 3.8x faster (76 MB —
  bandwidth-bound, the q8 win) but per-layer decoder GEMVs +7-21% SLOWER q8 (~2.3 MB mats,
  L2/L3-hot across the serial decode steps; AVX2 int8-dot + per-step requant loses to plain
  FMA when there's no memory traffic to save). Cost today: whisper-tiny zen2 decode leaves
  ~10-15 ms/clip on the table; net end-to-end neutral so nothing urgent. Possible fix: a
  per-region "stay-fp32 when the mat fits cache and the box lacks int8-dot silicon" load
  heuristic (or a box_profile knob like batch_grid_2d) — DON'T build until the M1 decoder-q8
  re-sweep says whether sdot boxes want q8 everywhere (likely yes → knob would be x64-only).
- **Gemma-4 E-series DENSE prefill trails lcpp Accelerate-BLAS on M1 (Wave G3 A/B, 2026-07-07).**
  E4B pp512 das **178.7** vs lcpp **192.9 = 0.93×**; E2B pp512 das **376** vs lcpp **382 = 0.98×**
  (E2B ties, E4B ~7% back). Decode tied both (bandwidth-bound: E4B 18.7/19.2, E2B 36.0/36.9).
  Root: dense prefill has no sparsity/grouping lever (unlike the MoE waves that LED lcpp), so it's
  das NEON-SDOT vs lcpp Accelerate-BLAS (AMX-backed) on the projection/FFN GEMMs — the larger E4B
  dim (2560 × ff 10240) favors AMX more, hence 0.93× vs E2B's 0.98×. Cost today: ~7% E4B prefill
  on M1 only; boxes without AMX exposure (zen2/SPR VNNI) already close it. Possible lever: a
  gemm-gen tuned Q8 kernel for the E-series shapes (the tune framework already exists) — don't
  build until an AMX-less box A/B says the shape actually leaves das-kernel headroom on the table.

- **Canary-Qwen ASR runs fp32 for parity; q8 decoder+encoder is the follow-up (Wave A1,
  2026-07-08).** The token-for-token gate loads the LoRA-merged Qwen3-1.7B decoder + FastConformer
  encoder at fp32. Perf A/B (M1 8T, das vs NeMo SALM greedy, `benchmarks/asr/results.md`): das
  LEADS every short/dictation clip 1.4–3× (jfk das/nemo 0.61×, LibriSpeech 0.34–0.49×) — the
  Canary-Qwen use case — but TRAILS 3.7× on the 3-min gb1, where the fp32 1.7B decoder is
  bandwidth-bound over gb1's ~2500 audio soft tokens. Fix: a q8 decoder (the existing q8 GEMV path,
  ~2× decode on the bandwidth rail) + q8 encoder, both straight ports of the parakeet/whisper q8
  machinery gated behind the fp32 parity default. Don't chase until the ASR-perf pass — but
  gb1-class long-audio is where it pays.

- **Gemma-4 E-series audio (gemma4a) encoder is fp32 SCALAR — big A/B gap (Wave A2, 2026-07-08).**
  The parity gate is fp32 encoder correctness, so the gemma4a Conformer runs a plain fp32 scalar
  forward. A/B (M1 Max 8T, das vs llama-mtmd-cli, `benchmarks/asr/results.md`): das transcribe
  6028 ms / xRT 2.89 vs mtmd-cli 1547 ms / xRT 11.3 → **das TRAILS 3.9×**, dominated by the encoder:
  das encode 1888 ms vs mtmd 117 ms = **16×** (fp32 scalar Conformer vs ggml's bf16-weight SIMD
  GEMMs); long-context decode 21.7 vs 78 tok/s also lags. Unlike A1/parakeet/whisper (which lead or
  tie), this tower has had NO perf pass. Fix: route the gemma4a tower through the gemm-gen Q8 audio
  kernel (the same SIMD/threaded machinery parakeet/whisper towers already use) — likely the single
  biggest audio-side win on the shelf — plus the long-context decode path. Not chased mid-wave.

- **Qwen3-Omni AuT tower is fp32 scalar too; perf numbers are SOFT (Wave A3, 2026-07-08).**
  Same shape as A2: parity gate is fp32, so the shared qwen3a AuT encoder runs scalar. A/B (M1 Max
  8T, das vs llama-mtmd-cli): jfk das 3625 ms / xRT 3.03 vs mtmd 1173 / 9.4 = **das trails 3.09×**;
  jfk3 das 8263 / 3.99 vs mtmd 2079 / 15.9 = **3.97×**. Dominant gap = the fp32 scalar qwen3a tower
  (~4.8× encode), same lever as the gemma4a entry above — SIMD/Q8 the shared AuT/qwen3a encoder
  covers BOTH A2 and A3. The q8 MoE thinker (grouped prefill ~207 t/s + q8 decode) also trails ggml.
  ⚠️ These A/B numbers are SOFT: measured with a dormant Parsec host daemon (1.6% CPU) + Spotlight
  indexing the freshly-downloaded 34 GB — a clean announced Parsec-off re-sweep would firm them (parity
  is unaffected). Not chased mid-wave.

- **ASR short-clip fixed costs (parakeet, M1 — NEXT ROUND, Boris 2026-07-06; whisper tower
  q8 postponed one session behind it).** Cost today at matched 8T: jfk das 703 ms vs cli 352
  (2.0x), LibriSpeech dictation p50 651 vs 324; long clips already 1.07-1.10x, so the short
  end is where the M1 gap lives. jfk stage profile (q8): ffn 215 / conv_module 126 /
  attn_heads 120 / attn_proj 119 / conv_sub 55 / mel 33 / decode 27 ms. Levers: mel is
  single-threaded (thread FFT/mel-dot over frames); conv_sub GEMMs stay fp32 — check their
  threading; audit every `lanes_for_work` gate at jfk-size tt (small clips may run stages
  inline that would profitably thread at 8 lanes); small-tt q8 tile shapes /
  `effective_token_block` at tt≈140; per-layer requant overhead at small tt; v3 decode GEMV
  is 8198×640 per step (8× v2's rows) — q8 the joint if it shows. Gate per lever: token
  parity + jfk best-of-3 + LS p50 before/after, both boxes.

- **✅ SHIPPED + SILICON-ADJUDICATED (zen2, 2026-07-05): 2-D batch chunk space (row-units ×
  token-blocks).** Landed as `batch_grid_2d` (0 = 1-D / 1 = fine grid, ggml's 16-token cells /
  2 = wave-aligned, rc·ntc = whole L-waves); the knob arms a per-dispatch auto-gate (engages only
  when the 1-D grain cap starves the admitted lanes), gen ts=4 walk factored into a shared
  body_cell so the off-path is the old walk verbatim; bit-exact all three ways (op-level test +
  512-tok GEN_IDS on both boxes). zen2 A/B (T=48, 3 interleaved reps): 135M pp512 knob2 +7.9%
  (every rep; +15% in the post-pin interleaved confirm), knob1 only +2.8% — **wave alignment
  beats ggml's amortize-the-tail at one-claim-per-lane granularity, the same physics as the 1-D
  wave invariant**; 1B +3-4% (kv d=512 starves); Qwen3-0.6B null as geometry predicts (nothing
  starves at 48 lanes); T=24 control identical (gate can't engage). zen2 profile pinned
  `batch_grid_2d: 2`; M1 pin stays off (≤11 lanes can never starve — verified no-regress).
  OPEN: the SPR respin should A/B the pin at T≥48 (more shapes starve at higher lane counts;
  fine-vs-aligned may flip where claim overhead differs). Original scoping kept below.
  Our batch dispatch chunks over out-row units only; tokens loop inside each chunk. Shapes
  with few row-units starve high lane counts (135M d=576 → ~5-36 chunks for 48 lanes; the
  Qwen3-0.6B attn_chain "deep-thin" 50% lead is the same geometry). llama.cpp's GENERIC path
  chunks 2-D — (out-rows × tokens) grid, chunk 16, one atomic counter, all architectures
  (ggml-cpu.c:1388-1442) — which is exactly why their mid/high-lane scaling holds on tiny
  models where our gated pool tops out. Our batch walk already loops tokens inside units, so
  the chunk space generalizes mechanically (matmul_chunks gains a token axis; worker chunk =
  (unit range, token-block range)); y-slices stay disjoint by construction. Ordering: linearize
  ROWS-FASTEST (concurrent workers then share the token block's activation slice in LLC and
  stream disjoint weight rows — lcpp's choice; their counter-starts-at-nth first-wave trick is
  the rank gate's natural analog on our side). **Delivery shape (Boris, 2026-07-05): a PIN per
  architecture, not a default rewrite** — the 1-D scheme already wins 2 of 3 ladder rungs
  head-to-head (avx2, vnni) and the M1/zen2 boxes; 2-D lands as a box_profile knob (default
  off, current behavior byte-identical), enabled where the per-box tune/fleet A/B proves it
  (SPR-class high-T tiny models, deep-thin attn shapes). Candidate refinement to discuss at
  implementation: an in-code auto-gate that only engages 2-D when the 1-D unit count starves
  the admitted lanes (units < k·lanes) — the knob then pins the gate rather than the mode.
  Sized: the 135M-class T≥24 residual vs lcpp (their 0.90-1.0 cells) + the attn_chain lead.
  (Spotted reading their amx/generic drivers during SPR session 3, 2026-07-05.)
- **✅ SHIPPED (audio arc, 2026-07-06): the Qwen2-Audio arc (speech→text, Boris 2026-07-05).**
  Landed token-for-token vs mtmd, then grew into the whole audio wave — whisper-proper ASR
  (6-model family sweep), Ultravox/Qwen2.5-Omni/Voxtral, Qwen3-ASR (new qwen3a chunked
  encoder), Parakeet-TDT, live-mic dictation, uniform `load_asr_model`/`transcribe` surface +
  chat-audio verbs on the facade. Arc-local perf ledgers folded in below. Original scoping kept:
  The cheapest audio-input path: Whisper-large-v3 encoder (~640M — mel frontend via the
  ALREADY-BOUND dasMinfft real FFT, the same per-frame-FFT pattern dasAudio's partitioned
  convolution reverb production-tests; 2× conv1d+GELU subsample = kernel-3 neural convs →
  im2col over EXISTING matmuls, no new compute kernel — FFT convolution only pays at long
  kernels; N PLAIN encoder blocks = existing matmul/norm/softmax with non-causal no-cache
  attention) → avg-pool → linear projector → soft tokens spliced at the `<|audio|>`
  placeholder; the decoder is our EXISTING qwen2 arch untouched (no cross-attention anywhere).
  New pieces: im2col gather, encoder forward, embedding-span prefill (driver), mmproj GGUF
  loader; oracle = llama.cpp mtmd (GGUF pairs ship). ~1 modest arc; the encoder is SHARED
  infrastructure — the same implementation unlocks Ultravox (llama-3 decoder ✓ have it) and
  ~80% of a Whisper-proper port later.
- **Fused decode chains regrain for kq v2 (spotted landing k4 v2, 2026-07-12; k5/k6 joined
  with their v2 port).** The chains' mid-chain requants slice at 32-element/per-head grain —
  Q8_K needs whole 256-superblocks — so ALL kq layers are gated OUT of both chains
  (fused_attn_ok/fused_ffn_ok) and take the per-op decode path. tg still improved (v2 gemv
  +15% covered the chain loss) but the chain win is on the table: regrain the w2-input
  requant to 256-row chunks and the wo-input requant to head PAIRS (head_size 128 × 2 = one
  superblock). Sized: a few % tg on kq models.
- **k5/k6 tile unpack gap — the high-bit deposit costs us proportionally more than lcpp
  (spotted racing the k5/k6 v2 port, M1 2026-07-12).** Post-v2 the k5/k6 folds are
  byte-identical to k4's, yet Q5/Q6 pp sit at 0.83×/0.80× lcpp (das 110/111 vs 132/138)
  while Q4 races at parity: our k5/k6 tiles run ~0.69 of our own k4 tile where lcpp's Q5/Q6
  hold ~0.86 of their Q4. The suspect is the per-(blk, j) weight unpack: k5's
  load_row_bytes_x4 byte-gather + or_bit_x10 (cmtst/bsl per half) and k6's two extra qh
  vector loads + shift/and/shl per (j, qd). We OWN the repack layout — candidate fixes:
  pre-expanded k5 high-bit rows (trade plane bytes for ALU), a tbl-based deposit, or k6 qh
  pre-shift at repack. Needs an iso GMAC/s read of the k5/k6 tiles vs k4's 97.7 first.
  Sized: up to +20% Q5/Q6 pp on M1 if the unpack fully amortizes; also lifts the zen2 race.
- **kq v2 on zen2/SPR — the x64 lattice race (k5/k6 v2 landed 2026-07-12 — unblocked).** The v2 emitter folds are
  lattice-generic (maddubs/vpdpbusd kq grid rows emit the same integer scheme, bias128+kq
  dropped as untested); zen2's lcpp lead was its AVX2 Q4_K 8x8 repack GEMM, and lcpp has NO
  x64 repack for Q5_K/Q6_K — post-v2 zen2 should reach Q4_K parity and WIN Q5/Q6. Needs the
  zen2 tune run + per-op race; SPR when a box respins.
- **kq tune bench lacks a MoE-shaped cell row (spotted validating the mr4 crowns, 2026-07-12).**
  The mr4 tile crown gave dense pp +10-26% but gave back ~3% MoE prefill on qwen3moe-30B
  (fused expert cells average ~32 tokens per expert with d=768-class group spans — a regime
  the d=512/ntok=64 batch fixture doesn't represent; mr8's halved group count wins there).
  Adding a MoE-cell-shaped fixture to kq_tune_family and weighting the decision (or a
  per-model-class entry) recovers it. Sized: ~3% MoE pp on M1; re-check on zen2/SPR grids.
- **AMX fold pipelining (double-buffered C spill) — only if amx silicon verdict ever flips.**
  lcpp's tinygemm_kernel_amx interleaves block i−1's AVX-512 scale-fold between block i's
  TMUL ops (double-buffered thread-local C scratch, mmq.cpp:2015-2105) — the fold hides under
  tile latency; our emit_amx_tile serializes them, likely most of the T-independent ~1.6×
  end-to-end amx loss on SPR. Pure emission-order change (second spill alloca + reordered
  fold). NOT worth doing while the amx leg loses on frequency/bandwidth grounds anyway
  (SPR session-3 verdict: grid-resident, biased busd512 keeps the manifest); revisit on
  Granite-Rapids-class silicon or a cache-resident serving regime. Their thread-local
  once-per-thread ldtilecfg (vs our per-call config+release) rides the same follow-up.
  (Spotted reading mmq.cpp during SPR session 3, 2026-07-05.)
- **x64 intrinsic backends lack the `mm_rows` row-range GEMV core (fused-chain fallback).** The
  fused decode chains (team_parallel_stages, 2026-07-03) gate on `kernel_backend_has_rows()`;
  portable + both arm64 backends carry the core, so the EPYC (profile-pinned portable) and M1
  get the fused path — but an x64 box on auto-select (avx2-repack / acc8 / vnni tiers) falls
  back to per-op dispatches. Fix = extract each x64 family's GEMV inner loop into a
  `q8q8_rows_kernel_*` (mechanical, mirrors the arm64 extraction); worth ~the same join-tail
  savings wherever an intrinsic tier ever beats tuned-portable at decode. Cost today: none on
  the campaign boxes (both run backends that carry the core). (Spotted during the fused-dispatch
  work, 2026-07-03.)
- **Fused-chain follow-ups: MoE FFN chain + norm/quantize as a stage.** The 2026-07-03 fused
  decode covers the attention block (all q8 arches, head_size %% 32 == 0) and the DENSE FFN;
  gpt-oss's routed-expert FFN keeps its per-op groupn dispatches (3/layer) — a 2-stage MoE chain
  (router serial, [experts' gate+up + act + requant] -> [downs + weighted reduce]) is the same
  shape one level up. And each chain still has a serial ~3-6us norm+quantize prologue per block;
  folding it in as a tiny stage-0 (chunked scale+quantize after a serial sum-of-squares) or
  fusing norm INTO the quantize pass is the last serial glue. Sized: MoE chain ~= the dense win
  for gpt-oss decode; norm-stage ~1%% at 1B. (Spotted during the fused-dispatch work, 2026-07-03.)
- **DONE (perf pass, 2026-07-02): tied classifier matmuls the Q8 disk quants (`Model.cls_q8`).**
  Tied Q8 loads of a Q8_0 embedding (every tied model we run — probed all 11) transcode
  `token_embd` twice into qblob — a classifier copy at wcls_off (repacked with the other 2D
  weights) and a LINEAR copy at emb_q8_off that embedding rows dequant from on demand (the laneq
  repack interleaves wcls in place, so row reads need their own un-repacked copy; on a no-repack
  box the two could alias — noted x64 follow-up) — and drop the fp32 table: on gemma-4-12B,
  classifier traffic 4.03GB → 1.13GB/token and resident 4.03GB → 2.26GB. Rows are bit-identical
  (same Q8_0 data the fblob decode used; gated by test_parity_tied_cls_q8_rows); the classifier
  quants are exactly what llama.cpp matmuls. 8 of 9 tied-model fixtures held token-for-token
  unchanged; gemma2's "Once upon a time" flipped a near-tie under the PINNED classic+libm test
  kernels only (default kernels still matched the oracle 24/24) → moved to the counting prompt
  like Qwen2.5/Phi, oracle-refrozen. fp32/q4 loads and non-Q8_0 embeddings keep the exact old
  path. (Spotted wave 3.)
- **DONE (perf pass, 2026-07-02): V-from-K layers fuse the K→V copy with the weightless V-norm.**
  Decode (mm_qkv) and prefill both rmsnorm k→v out-of-place when v_norm is on (bit-identical to
  copy + in-place norm; the block's v_norm step skips those layers). (Spotted wave 3.)
- **DONE (perf pass, 2026-07-02): llama.cpp A/Bs run (quiet box, CPU `-ngl 0`, llama-bench
  pp512/tg64 vs our matched driver, ggml-parity fast-math).** gemma-4-12B: prefill us 75-80 t/s
  vs llama.cpp 74.4±0.5 (parity to +5%); decode us ~7.3 vs 8.74 (~84% — the remaining decode gap
  is the next lever). gpt-oss-20b: prefill us ~219 vs 117 (~1.9× FASTER — the grouped MoE GEMM);
  decode us ~19 vs ~39-42 (~0.47× — exactly the MXFP4→Q8 doubled expert-weight-traffic asymmetry
  quantified: the native-MXFP4/Q4_0 entry below is now the headline gpt-oss decode lever).
  POST-JOBQUE (#3361 wake propagation + batch dispatch + worker spin, same-window anchors):
  12B decode 7.3 → 7.9 t/s vs 8.63 (gap 84% → ~92%); gpt-oss decode 19.2 → 22.0 vs 39.9
  (0.47× → 0.55×) — the dispatch-latency share of the decode gap is banked; what remains on
  gpt-oss is the weight-format asymmetry. (Spotted waves 3/5.)
- **DONE (perf pass, 2026-07-02): MoE prefill runs expert-bucketed grouped GEMMs — bit-exact.**
  `ffn_moe_prefill_grouped` routes every position (one batched router GEMM + the shared
  `moe_select`), CSR-buckets the (position, slot) pairs by expert, runs one batched GEMM chain
  per touched expert off a single whole-batch requant, and reduces the parked outputs in exactly
  the decode accumulation order (k slots then shared expert) — so it is bit-identical to the
  per-position path: the batch GEMM/requant/gate kernels are bit-for-bit their single-token
  forms per row. Proven on both MoE models (all logits identical after a 300-token prefill,
  grouped vs reference) and pinned by the qwen2moe fixture running through BOTH paths
  (`set_moe_grouped_prefill` A/B). Decode unchanged (one token = no bucketing win).
  Measured (M1 Max, interleaved in-process A/B): Qwen1.5-MoE 512-tok prefill 31 → ~270 t/s
  (~8.7×); gpt-oss-20b 256-tok prefill 27 → ~186 t/s (~6.8×). (Spotted wave 4.)
- **DONE (perf pass, 2026-07-02): MoE decode re-quantized the same activation per expert.**
  `moe_ffn_core` now quantizes xb once per layer into dedicated `moe_xq/moe_xs` (the
  down-projections quantize s.hb into the shared xq/xs, which would clobber a hoisted image
  there) and routes every gate/up matmul through `mm_at_q8_pre`. Bit-identical (same quants).
  (Spotted wave 4.)
- **DONE (MXFP4 arc, 2026-07-02): native-MXFP4 expert stacks + repacked TBL/SDOT kernels + the
  MoE dispatch fuse.** Was: gpt-oss-20b's 4.25-bit expert stacks ran as Q8 (2× resident, 2×
  decode traffic). Now: the stacks stay as raw nibble + E8M0 planes (mxq/mxs, exact disk bits —
  the old dequant→requant amax error is gone), decoded in-register by new aarch64_neon
  intrinsics (tbl16_lo/tbl16_hi = vqtbl1q_s8 of the doubled-e2m1 LUT; sdot4_w / sdot4_laneq_w
  take the tbl result as a VALUE) through dot_mx4q8 ([tuned], row-major) and dot_mx4q8_laneq4
  (interleaved 4-row repack, the block_mxfp4x4 twin). Grouped prefill expands each touched
  expert to EXACT Q8 (lossless: q = LUT int, scale = e8m0_half), writing the interleaved form
  directly on a repack backend; short prompts route per-position (npos·k ≥ 8·n_expert guard).
  On top, the MoE decode dispatch fuse: region-list groupn/groupn_mx4 kernels run all k
  experts' gates (ups, downs) in ONE fork/join — 288 → ~72 mm dispatches/token, bit-exact.
  Measured (QUIET box, 2026-07-02, same-window anchors): decode 22.0 → **31.8 t/s** @ ctx 8
  (30.7 @ ctx 512) vs llama-bench tg64 41.1 — **0.55× → 0.77×**; per-op profile: mm_moe 50%
  measured vs 47.9% theoretical share (the 66/66 format asymmetry is GONE), MoE mms sustain
  ~77GB/s vs the dense mms' ~99 (the remaining MoE-efficiency gap = the next lever); 12B decode
  7.98 vs anchor 8.67 (92%, unchanged — dense path untouched); resident 26 → 13.2GB; every
  fixture token-for-token unchanged (no refreeze — the counting fixtures absorbed all
  kernel-order changes). Cost paid: gpt-oss pp512 ~186 → ~121-149 t/s (the per-expert
  expansion) vs llama.cpp's 119.9 — still ≥ parity; the native mx4 batch GEMM in the expansion
  entry below reclaims it. (Spotted wave 5; the Q4_0 halfway house was skipped — native landed
  directly.)
- **q4 has no batched prefill kernel — prefill collapses to decode rate.** The q4 path serves
  everything through the scalar fp32-activation `dot_q4`/`matmul_q4` (no q8-style token-blocked
  batch GEMM, no NEON arm, no repack backend), so a q4 prefill runs at generation speed:
  measured on SmolLM2-135M, q8 prefill 1391 t/s vs q4 prefill 70 t/s ≈ its own 69 t/s decode.
  A q4 batch kernel (or the load-time q4→q8 transcode as the cheap fix) closes it.
  (Spotted tutorials wave.) **LOW PRIORITY (2026-07-02):** the path is cold — every model we
  test/ship parity for is Q8_0 on disk (plus gpt-oss MXFP4→Q8); no Q4_0 GGUF anywhere in the
  fixture set. q4 only fires when a user opts into `QuantMode q4` for footprint. Priority rises
  only if the MXFP4→Q4_0 halfway house above lands (q4 becomes the resident format of a real
  20B model).
- **LOW PRIORITY: f32 projection GEMM is untiled — dot-per-token, no token block.**
  `matmul_batch` (dasllama_math.das) is the exact pre-#3315 shape the Q8 path had: weight-
  stationary nest with one horizontal-reduce `dot()` per (row, token), zero register reuse
  across rows/tokens, and no L2 token-blocking (long-prefill X re-streams from DRAM per weight
  row). The SDOT-era fix transfers verbatim since it's dtype-agnostic: a 4-row × 4-token
  register tile with float4 `mad` chains and per-tile reduces (the fp32 twin of
  `dot_q8q8_sdot4x4` — keeps W row-major, no repack, decode GEMV untouched; do NOT reuse the
  broadcast-A `gemm_f32` form, it needs a transposed W copy) plus an `effective_token_block`
  at ~¼ the Q8 block (fp32 activations are 4× fatter). Expected kernel win ~2-3.5× (what the
  attention tile measured), ceiling below Q8 (fmla = 4 MACs/instr vs SDOT 16; 4B/weight vs
  ~1.06B). LOW because the f32 arm only fires for f32 GGUF tensors — in practice the tiny
  teaching models; attention's fp32 GEMMs already have the register tile (`gemm_f32_uk_4x16`).
  (Spotted post-#3354, 2026-07-02.)
- **DONE (perf pass, 2026-07-02): `kv_cache_off` prefix-summed per call.** `Model.kv_row_prefix`
  (filled by layout_offsets, seq_len-independent) × the LIVE seq_len at call time — the O(1)
  Model overload serves both hot call sites; the Config walking form stays as the definitional
  reference. (Spotted post-wave-3 review, per Copilot on #3346.)
- **DONE (perf pass, 2026-07-02): decode attention threads over heads — crossover measured,
  default re-set.** `attention_std_decode` maybe_parallel_fors the head loop (disjoint per-head
  rows ⇒ bit-exact vs inline, gated by test_forward), behind `g_decode_attn_par_threshold`
  (profile `runtime.decode_attn_par_threshold`). Quiet-box sweep (M1 Max, inline-vs-threaded
  interleaved at 32..2048 ctx on Llama-3.2-1B and gemma-4-12B): crossover at ~200-260K work on
  BOTH; below it threading costs ≤2%, above it wins reach +74% (1B) / +89% (12B) at 2048 ctx —
  the derived 4M default was ~15× too conservative (the 12B ran inline below ctx 512). Default
  is now the measured 262144. (Spotted tune audit, 2026-07-02.)
- **LOW PRIORITY: `sample_` top-k is O(top_k × vocab) scalar selection.** Each of the top_k
  rounds rescans the whole vocab (dasllama_common.das sample_) — top_k=40 on gemma-4's 262144
  vocab is ~10M compares per sampled token. Cold today (SamplingParams defaults are greedy /
  top_k=0, and all parity fixtures are greedy), but it's the sampling path the tutorials teach.
  Fix = single-pass partial selection (bounded min-heap of size top_k, or threshold-and-count).
  (Spotted tune audit, 2026-07-02.)
- **DONE (MXFP4 arc follow-up, 2026-07-02): the mm_moe bandwidth-gap profile + the bias fold.**
  Iso-benched the exact decode dispatch shape (4× [2880 x 2880] regions, DRAM-rotating):
  the fused mx4 groupn GEMV sustains **~101 GB/s — bandwidth parity with the q8 dense kernels**
  (the "77 GB/s" in-decode reading was largely single-window wobble: same build re-measured
  90 GB/s an hour later; METHOD: only round-robin interleaved cells within one process are
  trustworthy on this box, single-window absolutes swing ±10-15%). The pre-fuse 4×1 dispatch
  shape measures 63-72 GB/s — the dispatch fuse was worth ~30% and is confirmed load-bearing.
  Follow-up landed: **expert bias vectors fold into the groupn workers' stores** (bp/boffs on the
  groupn contract; bit-identical to the post-pass add_bias, minus its serial ~36us/layer) —
  decode 34.7 → **35.2 t/s @ ctx 8 / 33.8 @ ctx 512** (llama.cpp same-window anchor 41.1 →
  0.86×). Also swept: decode-attn threshold 0-vs-262144 under the spinner at ctx 8/512 —
  a WASH at both depths (the low-ctx attention is memory-latency-bound; threading's dispatch
  cost ≈ its serial cost), so the measured default stands; moe_reduce/rope threading rejected
  (~8us/layer each, below dispatch cost). What remains vs llama.cpp is their continuous-polling
  threadpool (the bus never idles between ops) — picked up by the x64 arc's jobque work, not
  patchable here. (Profiling session, 2026-07-02.)
- **MXFP4 grouped prefill pays a per-touched-expert Q8 expansion (~120MB of traffic each, half of
  it the repack scratch copy).** `expand_mx4_region_q8` writes exact row-major Q8 then runs the
  load-time `repack_q8q8_weight` (temp copy + interleave) so the laneq batch GEMM applies. Levers,
  in effort order: (a) expand DIRECTLY into the interleaved layout (folds the repack's copy away —
  needs a backend-provided expand-repack, not a layout hardcode in common); (b) a native MXFP4
  batch GEMM (mx4 twin of the laneq 4x4 tile — halves the GEMM's weight streaming too, likely wins
  outright); (c) the `npos * k >= 8 * n_expert` tiny-batch guard is an ESTIMATED breakeven
  (4-tok-prompt ttft 1895ms -> 114ms) — sweep it when the mx4 A/B rig exists. (Spotted MXFP4 arc,
  2026-07-02.)
- **Flash-attention tile shape is a frozen compile-time constant — deferred x64 tuning axis.**
  `ATTN_FLASH_QT/KV = 64×64` (dasllama_common.das) was chosen on M1 and never swept; tile shape
  is the classic per-box cache parameter, and x64's small private L2 differs in kind from M1's
  big shared L2. QT is compile-time-coupled to the `float[64]` running max/sum fixed arrays and
  the fa_* scratch sizing, so this is a compile-time axis à la `[tuned]` (profile-keyed), not a
  runtime setter. DEFERRED until an x64 box exists to measure on — do not solve the coupling
  speculatively. (Spotted tune audit, 2026-07-02.)
- **DONE (GEMV hunt, 2026-07-03): the decode "kernel top-end gap" was chunk-count misalignment,
  not the kernel.** A 12-variant GEMV race (`bench_gemv_decode.das` + the matmul_variants decode
  cells: unroll/ILP/fma-flush/dual-group/inline-scale) proved every kernel micro-opt a wash —
  llama.cpp's live M1 kernel (`ggml_gemv_q8_0_4x4_q8_0`; their 4x8 tier needs i8mm) is the same
  shape as `dot_q8q8_laneq4`. The real delta: njobs = `get_total_hw_jobs()*k` sized chunks to the
   7 WORKERS, but 8 lanes serve them (workers + caller — team by design, fifo via main-steal), so
  the last wave ran half-empty (28 chunks / 8 lanes = 87.5% utilization). Fix:
  `get_dispatch_lanes()` (workers + caller; knob `set_dispatch_caller_lane`, decode_prof
  `--legacy-lanes`) at all 54 dispatch sites incl. x64 (same effect there, smaller: ~2-3% at 32+
  workers). Measured: GEMV cls 109 → 118-120 GB/s (their exact rate); decode e2e 74.3 → 77.6 t/s
  @ ctx 8 (+4.4%, ~0.95× lcpp) / 66.3 → 67.8 @ ctx 512; mm_ffn 1.10× → 1.04×, cls 1.19× → 1.12×
  of lcpp per-op. Suite 171/171 token-for-token (chunk splits don't move per-row math). Oversplit
  re-sweep under aligned lanes: decode e2e is a WASH across ×1/×2/×4 (×8 past the knee) — the
  straggler-mitigation rationale dissolved once the split became 8-on-8, ×4 default stands on the
  prefill iso numbers. (GEMV hunt session, 2026-07-03.)
- **Q8 scales stream as a separate fp32 plane — llama.cpp's inline-fp16 layout moves ~6% less
  weight traffic.** Their `block_q8_0x4` packs 4 fp16 scales WITH the 128 quant bytes (136 B per
  4-row block-group, one stream); our laneq layout reads a second fp32-plane stream (144 B total
  per group). At the now-aligned ~118-120 GB/s both sides saturate equally, so the remaining
  cls/ffn per-op gap (1.04-1.12× of lcpp) is almost exactly this byte ratio (144/136 = 5.9%;
  bench: our best cls call 2448us vs their 2307 = 6.1%). The bench's `inline`/`inline_u2m` cells
  already prove the single-stream kernel shape works (fp32 inline = parity, occasionally +1%).
  The win requires fp16: (a) an f16→f32 convert intrinsic in dasLLVM aarch64_neon (vcvt_f32_f16
  via LLVM fpext, x64 twin F16C `vcvtph2ps` — gate on `cpu_supports`); (b) a repack variant
  writing [4×fp16 d | 128 qs] blocks + the GEMV/batch/group3/groupn kernels reading it; (c) the
  element-offset plumbing moves from plane offsets to block strides (loader `w*_off` math, groupn
  offs contracts). Sized: dasLLVM intrinsic + codegen bump, ~4 kernel twins, loader/offset sweep,
  fixture risk LOW (same math, scales exact fp16 round-trip of what the loader already computes —
  but the quantizer would store fp16-rounded scales, so oracle fixtures need a refreeze check).
  Expected: cls 1.12× → ~1.06×, ffn 1.04× → ~parity; decode e2e ~+2-3%. NOT this PR — needs its
  own arc. (Spotted GEMV hunt, 2026-07-03.)
- **Audio arc: the fp32 encoder is the whole ASR cost — q8 the encoder GEMMs.** The whisper-family
  encoder runs fp32 ≈ 18–19 s per 30 s chunk on M1 (~37 s for qwen2a's standard 2 chunks;
  large-v3-turbo transcribe = 0.49× realtime, almost all of it the encoder window). Fast path:
  q8 the 6 encoder GEMM families + projector at load (`quantize_weights` pattern) onto the
  generated q8q8 kernels — expect the usual ~4× (turbo → ~2× realtime) — plus threading the
  im2col/pack loops. Tolerance-gate like flash-decode (stage witness vs fp32), token-parity
  revalidate. (Audio arc, 2026-07-05/06.)
- **Audio arc: the all-silence second chunk's soft tokens are input-independent.** Every ≤30 s
  clip pads to 2 chunks and the second is all mel-floor — its 750 soft tokens are the same for
  every clip, cacheable per tower; halves qwen2a encoder cost for short clips. (Audio arc,
  2026-07-05.)
- **Audio arc: whisper decoder logits GEMV, only if it shows.** The ASR decoders are small
  (tiny ~35 MMAC/token, turbo ~140 incl. the 66 MMAC tied logits) — fp32 is fine; q8 the
  token_embd logits GEMV if profiling ever surfaces it. (Audio arc, 2026-07-06.)
- **Audio arc (correctness follow-up, not perf): honor `encode(parse_special=true)`.** The flag
  is documented-unhonored; every call site assembles specials by id + per-segment text encode
  (the chat-layer pattern). Fix belongs in the tokenizer proper; the workaround callers migrate
  after. (Audio arc, 2026-07-05.)

## What collapsed (done — Phase 5)

- `examples/dasLLAMA/` went from **8 programs to 2**. The 5 chat REPLs (`chat`, `gemma_chat`,
  `llama3_chat`, `phi_chat`, `qwen_chat`) collapsed into one `chat.das` driving the `dasllama_chat`
  engine; the 3 runners (`run`, `gguf_run`, `llama3_run`) collapsed into one `run.das` (completion +
  `stats()`). The deleted runners' token-exact oracles moved into `test_parity.das`.
- The old chat demos hand-rolled a token-by-token `prefill()` that never called the fast
  `forward_prefill`; `respond` prefills the whole rendered turn in one `eval()`, so the collapse also
  sped them up.

## What split into files (done — Phase 6)

The `dasllama` submodule layout, before → after:

| Before | After | Role |
|---|---|---|
| `dasllama_transformer.das` (2024 lines) | `dasllama_common.das` (~1940) | the whole engine: types, loader, kernels, std blocks, forward loops, sampling, registry |
| — | `dasllama_arch_llama.das` | config setter + `[init]` registration + Llama-3 chat template |
| — | `dasllama_arch_qwen2.das` | Qwen2 (QKV bias, NEOX rope) + ChatML template |
| — | `dasllama_arch_phi3.das` | Phi-3 (NEOX rope, fused QKV) + `<|user|>` template |
| — | `dasllama_arch_gemma2.das` | Gemma-2 (GeGLU, softcaps, SWA, 4 norms) + `<start_of_turn>` template |
| `dasllama_transformer.das` (same name) | `dasllama_transformer.das` (11 lines) | thin umbrella — `require dasllama_common public` + one require per arch |

- **The require cycle forces the umbrella.** Arch files `require dasllama_common` (they need
  `ArchDesc`/`Config`/`std_blocks`); common can't require them back (and doesn't — arches self-register
  at `[init]`). daslang forbids require cycles, so a third file requires common (public, re-export) + each
  arch (side-effect require, firing its `[init]`). That third file kept the name `dasllama_transformer.das`
  so no consumer require changed.
- **Only `std_blocks()` went public** — the single symbol the arch files pull from common. Everything else
  they touch (`ArchDesc`, `Config`, `FfnAct`, `ChatTemplate`, `register_arch`, `chat_text/special/content`)
  was already public. `resolve_arch` dispatches through the stored `ArchDesc.configure` fn-ptr, so the
  `configure_*` leaves detach with no dangling refs.
- **Both CMake lists updated** — `modules/dasLLAMA/CMakeLists.txt` (`ADD_MODULE_DAS`) and
  `tests/aot/CMakeLists.txt` (`AOT_DASLLAMA_MODULE_FILES`, leaf-order: common before the arches before the
  umbrella) — plus the `.das_module` `register_native_path` list.
- **Pure refactor** — block bodies / forward loops / config unchanged, so token output is identical
  (100/100 JIT + AOT). Adding a new arch (or MoE, with its own blocks) is now a new file + one require
  line in the umbrella, never an edit to the core.
