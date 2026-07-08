# Model-expansion plan — LLM + audio, post-audio-perf arc

Scoped 2026-07-07 (discussion during PR #3401 babysit). Goal: bring the supported-model
matrix back to "current" on both sides — LLM ("up to date" = the full Gemma-4 family) and
audio (the 2026 crop of audio-embedded and leaderboard ASR models) — every model to the
standing dasLLAMA bar: **token-for-token vs its reference implementation**, README matrix
row + parity fixture per model, one branch per wave.

Landscape facts referenced below were checked 2026-07-07 (Gemma-4 family/licensing per
Google's docs; ASR leaderboard per the Open ASR snapshot). Anything marked **VERIFY** is a
wave-start check, not a settled fact — do not build on it before probing.

## CPU speed reality (measured 2026-07-07, M1 8T, run.das)

Decode is bandwidth-bound: tok/s ≈ effective GEMV rate (~90-95 GB/s measured on M1) ÷
active bytes per token. Measured anchors: **gpt-oss-20b (MoE, ~3.6B active) 30 t/s gen**;
**Llama-3.1-8B dense Q8 11 t/s gen** — both sit exactly on that rail.

Implications for this plan:
- **Qwen3-30B-A3B ≈ 25-30 t/s** (q8) — fully interactive; the A3B shape is the point.
- **Gemma-4-26B-A4B ≈ 20 t/s** — interactive.
- **Gemma-4-31B dense ≈ 3 t/s q8 / ~6-7 q4** — NOT interactive on our boxes; it is a
  coverage/verification row and a prefill workhorse, not a chat target.
- **Gemma-4-E2B/E4B** — small active sets, fastest chat models in the plan; they pair
  with the audio stack for the edge/dictation story.
- Dense interactive ceiling on M1 ≈ 8B q8 (11 t/s) / ~14B q4. Memory-RESIDENT size is
  almost irrelevant to speed; active-streamed bytes are everything.
- K-quants note: at these sizes q4-class weights are also a straight ~2x decode speedup
  over q8, not just a disk saving — one more pull-forward argument.

## Standing rules (inherited, non-negotiable)

- Token-for-token oracle per model; frozen fixture in `test_parity.das` (LLM) or the
  audio suite; README matrix row lands in the same wave as the model.
- New arch features go through the arch registry / std_blocks seams — the core forward
  pass does not grow per-model branches.
- Perf ideas spotted mid-wave go to the API_REWORK.md performance ledger, never chased
  mid-wave.
- Correctness waves run fp32 first; q8 is a follow-up knob with its own gate class.
- Models live in `~/Work/llama.cpp/models` (gitignored), self-conversion recipes recorded
  in the plan of the wave that introduced them.

## Wave G — Gemma-4 family completion (the named target)

We have gemma-4-12B-it verified (arch: heterogeneous sliding/global geometry, p-RoPE,
V-from-K global layers, per-layer output scale, final softcap). The family is five models;
four remain. Order inside the wave = cheapest first, each gated before the next starts.

1. **gemma-4-31B dense — ✅ DONE 2026-07-07 (verify-only, zero code).** Header confirmed
   the same gemma4 arch as the 12B, scaled: 60 layers, embd 5376, 32Q / [16×5,4]KV heads;
   PLE off, shared_kv 0, softcap 30, 5-local:1-global SWA. Ran the existing gemma4 forward
   unchanged → **40/40 token-for-token** vs simple_ids (harness/parity.sh). Fixture
   `test_parity_gemma4_31b` (reuses GEMMA4_12B_GEN — identical counting continuation) +
   README matrix row. Committed on `bbatkin/model-expansion` (`19d7712cd`). Source:
   `ggml-org/gemma-4-31B-it-GGUF` (Q8 + bf16 mmproj), direct GGUF.
2. **gemma-4-26B-A4B MoE — ✅ DONE 2026-07-07. Real MoE slice; ~17 tok/s decode (M1 Max, 4B active).**
   Shipped: config `moe_optional`/`moe_dense_shexp` (arch is MoE only when the file ships experts) +
   5 new fblob regions (router scale, per-expert down scale, `pre/post_ffw_norm_1/2`); loader splits
   the fused `ffn_gate_up_exps` into the existing we1(gate)/we3(up) stacks at load (block-aligned Q8
   slices) + allocates/loads the dense shared expert (`ffn_gate/up/down` → w1/w3/w2 even with
   n_expert>0); forward `gemma4_moe_ffn` (custom router → select → per-expert down scale folded into
   the routed weights → `moe_experts_apply` → sandwich norms → dense-shared-expert sum), reusing the
   extracted `moe_experts_apply` (from `moe_ffn_core`) + `dense_ffn_inplace` (from `ffn_dense_decode`)
   so qwen2moe/gpt-oss/dense are byte-unchanged (full sweep 33/34 confirms). `gemma4_blocks()`
   dispatches dense (12B/31B) vs MoE (26B) by expert count.
   **KEY LESSON — MoE routing is near-tie-brittle.** The router RMS feeds a DISCRETE top-8-of-128
   pick; ggml accumulates it in `ggml_float` (double). With float, dasLLAMA flips experts at router
   near-ties even where the reference is *confident* → real O(1) miscounts. Fix = double-accumulate
   ONLY the router sum-of-squares (2816 adds/layer, non-hot — matches ggml; every GEMM + the residual
   stream stay float; approved by Boris: "double in a hot loop would be a problem, this isn't"). That
   removed the systematic flips (counting 3→1 miss). The survivor is a GENUINE near-tie: verified vs
   llama.cpp's per-step logit margins, the 26B's own top-1/top-2 gap is ~0.5–2.2 at counting steps
   12/26/32/38 — a coin-flip no float engine can pin. So NO 40-token prompt holds token-for-token
   (counting 34/40, days 16, prose/repetition worse — the "long" matches are repetition loops).
   Fixture = the counting prompt capped at its confident 11-token head (`GEMMA4_26B_GEN`); correctness
   proven separately via the margin analysis, not the fixture length. Diagnostic tooling:
   `harness/oracle` `simple_ids_margin`/`simple_ids_multi` (per-step logit margins + multi-prompt).
   ~~PROBED 2026-07-07; a real MoE slice (medium).~~
   Header: gemma4 arch, 30 layers, embd 2816, ff 2112, 16Q / [8×5,2]KV heads, **128 experts
   top-8**, expert_ff 704, softcap 30, SWA 1024, PLE off, shared_kv 0. The gemma4 MoE
   (`src/models/gemma4.cpp` `is_moe_layer` branch, lines ~291-344) is **two parallel branches
   SUMMED** (`cur = shared + routed`):
   - **Shared expert** — dense GeGLU FFN: `ffn_norm` → build_ffn(GELU, PAR) → `ffn_post_norm_1`. Always on.
   - **Routed experts** — `ffn_pre_norm_2` → MoE → `ffn_post_norm_2`. Router is *custom-normalized*:
     `RMS_norm(attn_out) × 1/√n_embd × learned ffn_gate_inp_s`, then `ffn_gate_inp` matmul → logits.
     **Softmax top-8-of-128 WITH renorm** (`norm_w=true`). Experts are **fused gate_up**
     (`ffn_gate_up_exps`, dim n_ff_exp·2) GeGLU + per-expert output scales
     (`ffn_up_exps_s`/`gate_exps_s`/`down_exps_s`).
   **Already in dasLLAMA** (proven by 12B/31B 40/40): attn geometry, dense GeGLU, per-tensor
   `_s` scale machinery. **NEW code** (in `dasllama_arch_gemma4.das`, a MoE-layer branch): the
   router normalization + softmax/renorm top-8, fused-gate_up experts w/ scales, the parallel
   dense-shared-expert sum, and the extra sandwich norms (`ffn_pre_norm_2`,
   `ffn_post_norm_1/2`). Rides the existing routed-expert GEMM seam (qwen2moe/gpt-oss).
   **vs qwen2moe** (the closest): gemma4 renormalizes top-k (qwen2moe doesn't), has a learned
   router input-scale + RMS/√d normalization (qwen2moe's router is a plain matmul), fuses
   gate_up (qwen2moe separate), and its shared expert is a **dense parallel** FFN (qwen2moe's
   is sigmoid-gated). Then 26B parity 40/40 (harness/parity.sh) + `test_parity_gemma4_26b`
   fixture (large-tier) + README row. Source: `ggml-org/gemma-4-26B-A4B-it-GGUF` (Q8 + bf16
   mmproj), on disk 2026-07-07. 4B active = strong CPU target, likely the family's perf sweet spot.
   **PREFILL grouped-batched (✅ 2026-07-07).** The 26B prefill was naive per-token (each position
   looped through `gemma4_moe_ffn`) → **35 t/s, 0.23× lcpp**. New `gemma4_moe_prefill_grouped` +
   `gemma4_router_batch` route every position, bucket (position, slot) by expert (CSR), run one Q8
   batch GEMM chain per touched expert (reusing `moe_gather_rows` + the qwen2moe grouped machinery),
   and batch the dense parallel shared expert over all positions — summed under the shared
   post_ffw_norm. Bit-identical per row to the naive path (same quants/dots, slot-order reduce, router
   SoS in double), gated by the existing `g_moe_grouped_prefill` A/B toggle; no new Session buffers.
   Measured (M1 Max, prefill-512, interleaved A/B): **grouped 217 t/s vs naive 39 = 5.5×**, and **217
   vs lcpp 151.1 = 1.44× — das now LEADS lcpp on 26B prefill.** Correctness held: the counting-prompt
   1492-token prefill still produces `GEMMA4_26B_GEN` token-for-token, grouped==naive==fixture.
3. **gemma-4-E2B / E4B — the edge models. PROBED 2026-07-07; slice RE-SIZED DOWN to
   "PLE + KV-sharing," best case.** Read of `src/models/gemma4.cpp` vs `gemma3n.cpp`
   plus E2B/E4B header dumps settled every VERIFY below:
   - **PLE — ON & confirmed.** `embedding_length_per_layer_input = 256` on both E2B and
     E4B (the 12B has it 0 → PLE is an E-series-only feature). Tables: `per_layer_tok_embd`
     {256·n_layer, n_vocab}, `per_layer_model_proj`, `per_layer_proj_norm`, plus per-layer
     `per_layer_inp_gate`/`per_layer_proj`/`per_layer_post_norm`. One lookup+project+add
     per layer per token. Loader region + one std_block addition; token-indexed reads suit
     the fmap discipline (tables never need to be resident).
   - **AltUp / LAuReL / MatFormer / activation-sparsity — ALL GONE.** grep count 0 in
     gemma4.cpp; gemma3n.cpp still carries the full bag (7 AltUp + 3 LAuReL tensors/layer).
     No new sub-blocks, no new forward-pass math — the biggest cost items in the pre-probe
     estimate all evaporated. This is the "PLE only" best case.
   - **Cross-layer KV sharing — PRESENT & USED.** `shared_kv_layers` = 20/35 (E2B),
     18/42 (E4B); 12B = 0. Local layers reuse a global layer's KV — real change to the
     per-layer KV-cache indexing; moderate, and a decode-bandwidth win.
   - Geometry: SWA `sliding_window` 512 with per-layer `sliding_window_pattern`;
     `final_logit_softcapping` 30.0; heads 8, kv 1 (E2B) / 2 (E4B); embd 1536 (E2B) /
     2560 (E4B); ctx 131072; blocks 35 (E2B) / 42 (E4B).
   - **Chat template — reasoning model.** gemma-4 emits `<|channel>thought …` blocks
     (harmony/gpt-oss-style channels); the template + stop handling must parse channels,
     not plain turns. Register a gemma-4 template variant; `--jinja` is required in the
     oracle recipe.
   Net slice = PLE loader+block + KV-sharing indexing + channel-aware template. No
   AltUp/LAuReL work. Text path first; audio deferred to Wave A2 — same models, two waves,
   so the text parity fixture exists before tower work starts. Payoff: the E-models are the
   audio carriers AND the fastest chat models in the plan (small active set on the
   bandwidth rail). Models: direct GGUF from `ggml-org/gemma-4-E{2,4}B-it-GGUF` (Q8 text +
   bf16 audio/vision mmproj), downloaded 2026-07-07 — no conversion.

Oracle throughout: llama.cpp `simple_ids` / `harness/parity.sh` (gemma4 support already
proven by the 12B row). Chat template: gemma family template already registered; E-series
**VERIFY** for deltas.

## Wave Q — Qwen3-MoE (best value/cost on the LLM side)

**Qwen3-30B-A3B** (+ optionally the 235B-A22B for header-tolerance only — it does not fit
either box; no parity run, just a clean "too big" load error). Arch delta over what we
run: qwen2moe wiring + qwen3's QK-norm, **renormalized** top-k router, **no shared
expert** (**VERIFY** against llama.cpp's `qwen3moe` build fn). Small slice; 3B-active on
our threaded engine probably becomes the best chat model per CPU-second we ship.
Unlocks the Wave A3 Omni thinker. Oracle: `simple_ids`, standard.

## Wave A1 — Canary-Qwen 2.5B (the ASR leaderboard crown)

Tops Open ASR (5.63 % WER English). Architecturally two pillars we already own:
FastConformer encoder (= parakeet's, **VERIFY** the canary variant's deltas — subsampling
factor, rel-pos flavor, d_model) + **unmodified Qwen3-1.7B** decoder in SALM arrangement
(**VERIFY** the adapter: how encoder frames project/splice into the LLM — likely a linear
projector + prompt wrapping, i.e. our soft-token splice rail).

- Conversion: `.nemo` → ggml bin, extend the parakeet converter (precedent in-tree).
- Oracle: NO cli oracle exists — NeMo python greedy transcribe is the reference. New
  oracle rail: a pinned-venv driver like `onnx_bench.py` (engine-level, no HTTP), plus
  frozen transcript fixtures. This is the wave's main risk/cost — budget a session for
  the rig before the model work.
- Lands as an `AsrModel` family behind the uniform ASR surface (`load_asr_model` sniff:
  nemo-converted bin + qwen3 vocab present).

## Wave A2 — Gemma-4 E-series audio input

The E2B/E4B carry native audio. Depends on Wave G step 3 (text path verified). **PROBED
2026-07-07 — both VERIFYs resolved GREEN; oracle proven end-to-end** (E2B transcribed
`tools/mtmd/test-2.mp3` verbatim at `--temp 0 --jinja`; conformer encode 302 ms):
- (a) Encoder = **`gemma4a` conformer** (`clip.audio.projector_type='gemma4a'` on both
  E2B and E4B mmprojs). 12 blocks, audio d_model 1024, FFN 4096, 8 heads, 128 mel bins
  (FFT filterbank), LN eps 1e-5, projects into text embd (1536/2560). Structure
  (`tools/mtmd/models/gemma4a.cpp`): subsample Conv2D ×2 (stride 2) → per block { dual
  half-step macaron FFN (SiLU) · full self-attn w/ sinusoidal RPE (Transformer-XL blocked
  shift) · conv module: pointwise 1024→2048 → GLU → causal depthwise conv1d k=5
  (`ggml_ssm_conv`) → norm → SiLU → pointwise 1024→1024 }. = parakeet's block
  neighborhood — parakeet blocks are the starting point.
- (b) llama.cpp mtmd support = **YES** (runs today; the qwen2audio `llama-mtmd-cli
  --temp 0 --jinja` recipe applies verbatim). Wave does NOT stall; priority holds.
- **Gotcha:** the gemma4a conv ops ship per-op activation-quant calibration ranges
  (`input_max/min`, `output_max/min` tensors) — the encoder must honor them, not just
  weight-dequant.
- Note: llama.cpp also has a second audio flavor `gemma4ua` (encoder-free, raw-waveform
  640-frame, no FFT/filterbank) used by OTHER gemma-4 checkpoints — irrelevant to E2B/E4B
  but on the map for later.
Projector + soft-token splice ride the existing audio-chat rails.

## Wave A3 — Qwen3-Omni-30B-A3B, audio-in/text-out

Depends on Wave Q (thinker = qwen3moe). Audio tower is **AuT** — a new encoder family,
NOT whisper-based (**VERIFY** exact blocks from the tech report / llama.cpp mtmd). We take
audio understanding + ASR only; the Talker (speech generation) is explicitly out of scope.
Oracle: **VERIFY** llama.cpp mtmd support; without it this waits. Size: q8 ≈ 30 GB — fits.
Claimed SOTA ASR (beats Voxtral-Small) — if it verifies, it enters the ASR bench
scoreboard next to whisper/parakeet/canary.

## Cross-cutting: K-quant READ support (pull-forward candidate)

We read F32/F16/Q8_0/Q4_0/MXFP4. The 2026 GGUF ecosystem defaults to K-quants
(Q4_K_M/Q5_K/Q6_K) — several waves above otherwise start with "self-convert the HF
original" (already true for Voxtral). Read-side support = dequant K-blocks → our Q8_0 at
load (the parakeet fblob→qblob transcode pattern); NO native K-kernels unless profiling
ever says otherwise. This multiplies every other row (and community usability) more than
any single model. **ASK BORIS: pull forward before Wave G's big downloads, or slot after
Wave Q?**

## The next ENGINE arc — decision, not a wave

Two candidate directions after the waves above; each is flash-decode-sized:

- **Hybrid SSM lane** (Granite-4 micro/tiny, Qwen3-Next, LFM2): new kernel family — SSM
  scan + conv state next to attention in hybrid stacks. CPU-friendly (linear in context),
  clearly where small-model architecture is heading, small CPU-sized carriers exist.
- **MLA lane** (DeepSeek V3/R1, Kimi): only CPU-sized carrier is DeepSeek-V2-Lite
  (16B-A2.4B). The models people want from this family are 671B+ — never fitting our
  boxes; the R1-distills everyone runs locally are llama/qwen archs we already support.

Recommendation: **SSM > MLA** for our CPU story; MLA only if arch-coverage completeness
becomes a goal in itself. **ASK BORIS** when the waves above near completion.

## Quick-win shelf (fill idle moments, no wave ceremony)

- New **Ultravox checkpoints** (v0.6/v0.7): if the projector shape is unchanged, cost ≈
  download + parity run + matrix row.
- **Phi-4 / Phi-4-mini**: phi3-adjacent (**VERIFY**: full-attention + partial rotary
  deltas); likely a small arch tweak + parity.
- **Mistral Small 3.x / Ministral**: llama-arch by reputation (**VERIFY**) — parity-only.
- **Moonshine** (27M/61M streaming ASR): would make live dictation latency absurd;
  ONNX-only reference — needs the A1 python-oracle rail first.
- **GLM-4 dense (9B/32B)**: llama-ish with deltas (**VERIFY** bias/rope details).

## Explicit no-gos (this plan)

- Kimi K2.x, DeepSeek V3/R1 proper, GLM-4.7 flagship, Qwen3-235B parity runs — do not
  fit the boxes; header-tolerance + honest errors only.
- TTS (Voxtral-TTS, CosyVoice3, …) — a different capability arc (speech OUT); not model
  support. Gets its own plan if/when wanted.
- Vision input anywhere — unchanged standing exclusion.
- Talker/speech-generation side of Omni models.

## Sequencing summary (proposed)

G1 (31B verify) → G2 (26B MoE) → Q (qwen3moe 30B-A3B) → G3 (E2B/E4B text) → A1
(Canary-Qwen + python-oracle rail) → A2 (E-series audio) → A3 (Omni audio) → engine-arc
decision. K-quants placement per Boris. Quick-win shelf interleaves freely.
