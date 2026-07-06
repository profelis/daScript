# dasLLAMA

daslang-native **CPU** LLM inference (Llama / Qwen / Phi / Gemma dense + MoE transformers, gpt-oss). Loads GGUF
(or llama2.c `.bin`), runs the forward pass + KV cache, tokenizes, and decodes —
all in daslang, JIT tier. Verified token-for-token against `llama.cpp` / `llama2.c`.

Run a model: `bin/daslang -jit examples/dasLLAMA/run.das -- <model.gguf>`
Chat: `bin/daslang -jit examples/dasLLAMA/chat.das -- <model.gguf>`

---

## Module layout & usage

dasLLAMA is a pure-daslang module under the `dasllama/` namespace. The core library
lives in `modules/dasLLAMA/dasllama/`; perf benchmarks and verification harnesses sit
beside it under `modules/dasLLAMA/benchmarks/` and `modules/dasLLAMA/harness/`; runnable
demos are in `examples/dasLLAMA/` and tests in `tests/dasLLAMA/`.

```
modules/dasLLAMA/
  .das_module                 # registers the dasllama/ namespace (dynamic binary)
  CMakeLists.txt              # ADD_MODULE_DAS registration (static binary + install)
  API_REWORK.md               # API + backend-seam design record (the plan of record)
  x64_arch.md                 # x64 port docs — seam map; get_x64_going.md = runbook,
  get_x64_going.md            #   tune_for_this_box.md = per-box tuning + measurement discipline
  tune_for_this_box.md
  dasllama/                   # the module — require dasllama/<name>
    dasllama_math.das         #   numeric primitives + matmul/dot kernels (fp32, Q8, Q4) + Q8·Q8 kernel-backend registry
    dasllama_math_default.das #   the portable Q8·Q8 kernel backend (the fallback; platform backends out-rank it)
    dasllama_math_aarch64_neon.das # arm64 SDOT row-major Q8·Q8 backend + the laneq dot leaves the gen tier composes ([init]-registered; no-op off-ARM)
    dasllama_math_gen.das     #   the generated GEMM tier — registers "arm64-gen"/"x64-gen" (load-select repack backends; traversals read the stamped layout)
    dasllama_gemm_schema.das  #   tune_perm grid + layout schema shared by the generator and the runtime
    dasllama_gemm_gen.das     #   the GEMM tile generator (emits per-perm kernels under llvm_tune)
    dasllama_gemm_register.das #  [tune] family registration — manifest > per-ISA fallback chain
    dasllama_par.das          #   maybe_parallel_for threading macro
    dasllama_tune.das         #   per-box kernel loop-hint tuner — [tuned] / [dasllama_grid] (see tune_for_this_box.md)
    dasllama_quant.das        #   Q8_0 / Q4_0 (de)quantization
    dasllama_gguf.das         #   GGUF container parser + tensor transcode
    dasllama_unicode.das      #   Unicode classification + UTF-8 codec
    dasllama_tokenizer.das    #   SentencePiece tokenizer (Llama-2 family, Phi-3, Gemma)
    dasllama_bpe.das          #   byte-level BPE / tiktoken tokenizer (Llama-3 + Qwen2 pre-tokenizers)
    dasllama_common.das       #   engine core — Config / Model / Session, load + forward + generate + sample
    dasllama_audio.das        #   audio tower — whisper mel frontends + encoder core + qwen2a projector (soft-token splice)
    dasllama_whisper.das      #   whisper-proper ASR — ggml-bin loader, cross-attn decoder, greedy driver, transcribe API
    dasllama_qwen3a.das       #   Qwen3-ASR audio encoder — conv2d chunk frontend, windowed transformer, MLP projector
    dasllama_asr.das          #   uniform ASR surface — load_asr_model (format-sniffed), caps(), family-free verbs
    dasllama_arch_llama.das   #   Llama / Llama-2 / Llama-3 / TinyLlama arch (config + chat template)
    dasllama_arch_qwen2.das   #   Qwen2 arch  (per-arch: config setter + [init] registration)
    dasllama_arch_qwen3.das   #   Qwen3 arch (QK-norm)
    dasllama_arch_phi3.das    #   Phi-3 arch
    dasllama_arch_gemma2.das  #   Gemma-2 arch
    dasllama_arch_gemma3.das  #   Gemma-3 arch (SWA pattern + dual rope θ)
    dasllama_arch_gemma4.das  #   Gemma-4 arch (heterogeneous sliding/global geometry + p-RoPE)
    dasllama_arch_qwen2moe.das #  Qwen-MoE arch (routed top-k + shared expert)
    dasllama_arch_gptoss.das  #   gpt-oss arch (MoE + sinks + YaRN + swiglu_oai + biases)
    dasllama_transformer.das  #   umbrella — re-exports dasllama_common + registers every arch
    dasllama_chat.das         #   layer-2 chat engine — Role/Message/ChatSession, template renderer, respond()
    dasllama.das              #   THE public facade — documented API over engine + chat (require this)
  benchmarks/                 # perf harnesses (gen tok/s, prefill TTFT)
    matmul/                   #   matmul kernel micro-bench ledger
  harness/                    # verification / eval test beds, per-box tuners, GGUF inspection tools
tests/dasLLAMA/               # dastest [test] suites (model-gated ones self-skip)
examples/dasLLAMA/            # runnable demos only — run.das (completion + stats), chat.das (REPL), audio.das (audio chat), transcribe.das (speech-to-text), dictate.das (live mic -> text)
tutorials/dasLLAMA/           # the guided series — 01 generate ... 06 add an arch, 07 speech-to-text, 08 audio chat
```

One require is the whole public API (docs: the `dasllama` page in the stdlib reference):

```das
require dasllama/dasllama                // load_model / create_session / encode / eval / sample /
                                         // generate (streaming) / decode / piece + chat: create_chat /
                                         // add_user / respond — and it re-exports the engine below
```

Engine internals remain reachable for tools and kernel work:

```das
require dasllama/dasllama_transformer    // engine spellings (load_model_, eval_, ...) + raw load_gguf / forward
require dasllama/dasllama_tokenizer      // SentencePiece
require dasllama/dasllama_bpe            // byte-level BPE (Llama-3 / Qwen2)
require dasllama/dasllama_math           // matmul / rmsnorm / softmax / silu / rope / dot
```

The clean surface is `load_model → create_session → encode → eval → sample / generate
(streaming) → decode / piece`, with chat one layer up (`create_chat → add_user →
respond(model, chat, params) $(piece) { ... }`); design record in `API_REWORK.md`.

---

## Supported models — what runs *for sure*

Legend: ✅ **verified token-for-token** vs the reference · 🚧 in progress · ❌ not supported yet

| Model | Format(s) tested | Arch | Tokenizer | Status | Verified against |
|---|---|---|---|---|---|
| **stories15M** (llama2.c toy) | F32, self-Q8, self-Q4 | Llama-2 | SPM (`.bin`) | ✅ | `llama2.c ./run` greedy, token-for-token (Q8 too; Q4 coherent) |
| **TinyLlama-1.1B-Chat-v0.3** | F16 GGUF | Llama-2 | SPM (GGUF) | ✅ | `llama.cpp`, 40/40 token-for-token (weak model — ChatML) |
| **TinyLlama-1.1B-Chat-v1.0** | Q8_0 GGUF | Llama-2 | SPM (GGUF) | ✅ | `llama.cpp`, 69/69 token-for-token vs fp32; good chat (Zephyr) |
| **Llama-3.2-1B-Instruct** | Q8_0 GGUF | Llama-3 | BPE/tiktoken | ✅ | `llama.cpp` (instrumented `simple_ids`, CPU greedy), 40/40 token-for-token |
| **Llama-3.1-8B-Instruct** | Q8_0 GGUF | Llama-3 | BPE/tiktoken | ✅ | `llama.cpp` (instrumented `simple_ids`, CPU greedy), 40/40 token-for-token (8.5GB, needs the fmap >4GB fix) |
| **SmolLM2-1.7B-Instruct** | Q8_0 GGUF | Llama (arch `llama`) | BPE | ✅ | `llama.cpp` `simple_ids`, 40/40 token-for-token; frozen fixture in `test_parity.das` |
| **Mistral-7B-Instruct-v0.3** | Q8_0 GGUF | Llama (arch `llama`, no SWA) | SPM (GGUF) | ✅ | `llama.cpp` `simple_ids`, 40/40 token-for-token; frozen fixture; chat via the detected `[INST]` template |
| **Qwen2.5-0.5B / 1.5B-Instruct** | Q8_0 GGUF | Qwen2 (QKV bias, NEOX rope, eps 1e-6) | BPE (qwen2 pre) | ✅ | `llama.cpp` `simple_ids` / `harness/parity.sh`: 1.5B 40/40 (frozen fixture); 0.5B matches to ~0.02 logits, flips only genuine near-ties (tiny model) |
| **Qwen3-0.6B / 4B-Instruct-2507** | Q8_0 GGUF | Qwen3 (QK-norm: per-head Q/K RMSNorm pre-RoPE; NEOX rope, no QKV bias) | BPE (qwen2 pre) | ✅ | `llama.cpp` `simple_ids` / `harness/parity.sh`: both 40/40 token-for-token (frozen fixtures in `test_parity.das`) |
| **Qwen1.5-MoE-A2.7B-Chat** | Q8_0 GGUF | Qwen2-MoE (routed experts: softmax router → top-4 of 60, un-renormalized weights; sigmoid-gated shared expert; QKV bias, NEOX rope) | BPE (qwen2 pre) | ✅ | `llama.cpp` `simple_ids` / `harness/parity.sh`: 40/40 token-for-token on the counting AND prose prompts (frozen fixture in `test_parity.das`) |
| **Phi-3.5-mini-instruct** | Q8_0 GGUF | Phi3 (fused QKV + gate_up, NEOX rope, LongRoPE) | SPM | ✅ | `llama.cpp` `simple_ids` / `harness/parity.sh`: 40/40 (frozen fixture); prose matches to ~0.06 logits, flips only genuine near-ties |
| **Gemma-2-2B-it** | Q8_0 GGUF | Gemma2 (GeGLU, dual softcap, sliding window, sandwich norms, embed ×√dim) | SPM (GGUF) | ✅ | `llama.cpp` `simple_ids`, token-for-token; frozen fixture in `tests/dasLLAMA/test_parity.das`; SWA exercised on a 4k+ context |
| **Gemma-3-1B / 4B-it** | Q8_0 GGUF | Gemma3 (Gemma-2 shape minus softcaps + QK-norm; 5:1 sliding:global layer pattern, dual RoPE θ 10k/1M, linear-8 position scale on the 4B's global layers) | SPM (GGUF) | ✅ | `llama.cpp` `simple_ids` / `harness/parity.sh`: both 40/40 token-for-token (frozen fixtures); sliding mask exercised on a ~900-token prompt (40/40) |
| **Gemma-4-12B-it** | Q8_0 GGUF | Gemma4 (heterogeneous geometry: sliding layers 16Q/8KV heads of 256 vs global 16Q/1KV of 512, per-layer bool SWA pattern; p-RoPE freq factors on global layers only; weightless V-norm; V-from-K on global layers; unit attention scale; per-layer output scale; final softcap; suppressed-token logit bias) | SPM-style BPE (`gemma4`) | ✅ | `llama.cpp` `simple_ids` / `harness/parity.sh`: 40/40 token-for-token on the short counting prompt AND on a ~1490-token window-engaged prompt — the latter is the frozen fixture, encoded in-test through the gemma4 tokenizer (the short prompt's continuation drifts into the channel format on a near-tie, so it stays out of the suite); tokenizer 46/46 vs the `ggml-vocab-gemma-4` corpus |
| **Qwen2-Audio-7B-Instruct** (audio input) | self-converted F16→Q8_0 + f32 mmproj (ggml-org publishes no pre-quant — convert with the in-tree `convert_hf_to_gguf.py`, decoder + `--mmproj`) | Qwen2 decoder untouched + whisper-large-v3 encoder tower (fp32: mel→conv×2→32 blocks→avg-pool→linear projector; soft tokens spliced at `<|audio_bos|>…<|audio_eos|>` via `forward_prefill_embd`) | BPE (qwen2 pre) | ✅ | `llama-mtmd-cli --temp 0`: token-for-token on jfk.wav AND tools/mtmd/test-2.mp3; encoder gated vs `llama-mtmd-debug` all-ones mel (test_audio.das); mel gated vs the 440 Hz preproc dump (3.1e-05) — rig + findings in `qwen2_audio_plan.md` |
| **Ultravox v0.5** (audio input): llama-3.2-1b + llama-3.1-8b | STOCK Llama-3 Q8_0 GGUFs (decoders untouched) + ggml-org f16 mmproj (oracle runs use a local f16→f32 re-encode so mtmd computes in fp32; our loader reads either) | whisper-large-v3 tower + `ultravox` projector: post-LN → stack-8 frame concat (floor rows, ragged tail dropped) → RMS-pre → mm1 → swiglu_swapped → RMS-mid → mm2, no biases; 187 soft tokens/chunk spliced INLINE in the llama-3 template (no audio delimiter tokens) | BPE/tiktoken | ✅ | `llama-mtmd-cli --temp 0`: 1b token-for-token on jfk.wav AND tools/mtmd/test-2.mp3; 8b token-for-token on jfk.wav; tower shapes gated in `test_audio.das` |
| **Qwen2.5-Omni 3B / 7B** (audio input) | ggml-org Q8_0 GGUFs + f16 mmproj (same local f32 re-encode for the oracle; the combined mmproj's `v.*` vision tensors are skipped by the name-driven loader) | decoder is arch `qwen2vl` — M-RoPE whose coordinates all equal the linear position for text+audio, so the plain qwen2 forward is bit-identical (registered as a qwen2 alias; vision out of scope); audio side = the QWEN2A tower + projector VERBATIM (750 tokens/chunk at `<|audio_bos|>…<|audio_eos|>`) | BPE (qwen2 pre) | ✅ | `llama-mtmd-cli --temp 0`: 3B token-for-token on jfk.wav AND test-2.mp3; 7B token-for-token on jfk.wav |
| **Voxtral-Mini-3B** (audio input) | self-converted decoder Q8_0 + mmproj f32 (ggml-org publishes only K-quants; `convert_hf_to_gguf.py` needs `mistral-common` + a local missing-`return` fix, see `audio_models_plan.md`) | llama-arch decoder (head_dim 128, rope θ 1e8) + whisper tower + `voxtral` projector: avg-pool → post-LN → stack-4 → mm1 → gelu_erf → mm2, no biases; 187 tokens/chunk after `[BEGIN_AUDIO]` in the `[INST]…[/INST]` v7-tekken template; NEW `tekken` pre-tokenizer (generic-wregex alternation semantics — no contractions, single digits, '/' punct tail) | BPE (`tekken` pre) | ✅ | `llama-mtmd-cli --temp 0`: transcription prompt on jfk.wav byte-identical to natural stop; tokenizer id-for-id vs `llama-tokenize` (incl. 你A / contraction / digit probes); decoder 40/40 text-only (`harness/parity.sh`); encoder ≤5e-4 vs mtmd on real input. The two open-caption prompts each flip ONE step sitting at a 0.079 / 0.195-logit near-tie (p≈0.5 coin-flips; every matched step clears gaps up to 12 logits) — same knife-edge class as whisper tiny/base, not chased |
| **Qwen3-ASR 0.6B / 1.7B** (speech-to-text) | ggml-org Q8_0 decoder + bf16 mmproj GGUFs (read directly — bf16→f32 is exact) | decoder is arch `qwen3vl` (M-RoPE degenerates for text+audio, deepstack inactive without vision — registered as a qwen3 alias) + NEW `qwen3a` encoder: 100-frame mel chunks through 3 stride-2 conv2d blocks (13×16×480), features to d_model, per-chunk position reset, transformer over 800-frame windows (13 tokens/chunk, k-biased attention on the shared tower block loop), GELU MLP projector; LLM-style transcription — the model emits `language {L}<asr_text>{text}`, parsed into `detected_lang` + one segment (no timestamps); context biasing via `AsrSession.context` | BPE (qwen2 pre) | ✅ | `llama-mtmd-cli --temp 0`: 0.6B transcript byte-identical on jfk.wav AND tools/mtmd/test-2.mp3 (88-token read of the NYT clip); 1.7B byte-identical on jfk.wav; encoder gated vs `MTMD_DEBUG_EMBEDDINGS` per-window token-0 (≤1e-4) in `test_whisper.das` |
| **Parakeet-TDT 0.6b-v2** (speech-to-text) | self-converted `.nemo` → ggml bin (whisper.cpp's in-tree `convert-parakeet-to-ggml.py`, `--use-f32`) | NEW family end to end: frame-major mel (preemph 0.97, zero-center-pad, natural log, per-feature Bessel normalization) → conv2d subsampling (regular+depthwise ×2, 8× time) → 24 FastConformer blocks (macaron half-FFNs ×0.5, rel-pos attention with u/v biases + interleaved sin/cos table + scalar rel-shift gather, GLU→depthwise-k9→inference-BN→SiLU conv module, per-layer post-norm) → 2-layer LSTM predictor ([i,f,o,g] packed gates) → TDT joint (relu, full-row log-softmax) + duration-skip greedy | SPM (▁ pieces from the bin) | ✅ | `parakeet-cli -ng -ps` (CPU, f32): **jfk.wav 33/33 and gb1 (3-min Columbia address) 786/786 token-for-token** — ids, frames, duration indices AND values; the duration argmax must run over fp32 softmax values, not raw logits (the oracle's underflow-to-−inf tie-break, see `parakeet_plan.md`); suite gate in `test_whisper.das` |
| **Whisper — full family** (speech-to-text): tiny/base/base.en/small/medium/large-v3/large-v3-turbo | stock whisper.cpp `ggml-*.bin` (f16, read directly — no conversion) | Whisper encoder (the qwen2a tower core, tanh-fp16-LUT gelu, ln_post tail) + NEW text decoder w/ cross-attention (learned abs pos, tied logits, ≤448 ctx) + `whisper_full`'s greedy driver (timestamp rules, no-speech gate, long-form seek) | byte-level vocab from the bin | ✅ | `whisper-cli` CPU greedy (`-bs 1 -bo 1 -nf -ng`), jfk.wav w/ timestamps: **tiny, base.en, small, medium, large-v3, large-v3-turbo all token-for-token** (turbo also on 33 s long-form, 3 windows exact); base flips ONE step where the force-timestamp rule sits at a 2e-4-logit margin (oracle's own p=0.495 — a coin flip; base is exact in `-nt` mode) — rig + findings in `whisper_plan.md`; suite gate in `test_whisper.das` |
| **gpt-oss-20b** | MXFP4 GGUF → self-Q8 | gpt-oss (MoE: 32 experts top-4, softmax over the SELECTED weights, no shared expert; router + per-expert + QKV + output-projection biases; clamped SwiGLU `swiglu_oai`; per-head attention sinks; alternating 128-token SWA; YaRN rope factor 32 over a 4096 original context) | BPE (`gpt-4o` pre) | ✅ | `llama.cpp` `simple_ids` / `harness/parity.sh`: 40/40 token-for-token on the counting prompt AND on a 449-token window-engaged prompt encoded in-test through the gpt-4o pre-tokenizer (both frozen fixtures in `test_parity.das`); tokenizer verified id-for-id vs llama.cpp on counting / mixed-case-contraction / whitespace probes |

Models are **not** checked into the repo — they live in `~/Work/llama.cpp/models/`
(gitignored). Get them with `hf download <repo> <file> --local-dir ~/Work/llama.cpp/models`.

### Reproduce the verified runs

```sh
# Greedy completion + prefill/gen tok/s over any supported GGUF (arch + tokenizer auto-detected)
bin/daslang -jit examples/dasLLAMA/run.das -- ~/Work/llama.cpp/models/tinyllama-1.1b-v0.3-f16.gguf
bin/daslang -jit examples/dasLLAMA/run.das -- ~/Work/llama.cpp/models/Llama-3.2-1B-Instruct-Q8_0.gguf

# Interactive chat — ONE REPL for every model; the arch registry picks the chat template + stop tokens
bin/daslang -jit examples/dasLLAMA/chat.das -- ~/Work/llama.cpp/models/tinyllama-1.1b-chat-v1.0.Q8_0.gguf
bin/daslang -jit examples/dasLLAMA/chat.das -- ~/Work/llama.cpp/models/gemma-2-2b-it-Q8_0.gguf

# Audio chat: whisper-encoder tower + soft-token splice into the decoder. The mmproj's
# projector type picks the prompt shape — the same demo runs Qwen2-Audio, Qwen2.5-Omni,
# Ultravox (stock Llama-3 decoders), and Voxtral pairs:
bin/daslang -jit examples/dasLLAMA/audio.das -- ~/Work/llama.cpp/models/qwen2audio-7b-q8_0.gguf \
    ~/Work/llama.cpp/models/qwen2audio-mmproj-f32.gguf ~/Work/llama.cpp/models/jfk.wav "What is being said in this audio?"
bin/daslang -jit examples/dasLLAMA/audio.das -- ~/Work/llama.cpp/models/Llama-3.2-1B-Instruct-Q8_0.gguf \
    ~/Work/llama.cpp/models/mmproj-ultravox-1b-f32.gguf ~/Work/llama.cpp/models/jfk.wav

# Speech-to-text (Whisper): any audio file -> timestamped segments, stock whisper.cpp models
bin/daslang -jit examples/dasLLAMA/transcribe.das -- ~/Work/whisper.cpp/models/ggml-large-v3-turbo.bin \
    ~/Work/whisper.cpp/samples/jfk.wav

# Token-for-token gates: test_forward (stories15M vs llama2.c) + test_parity (frozen llama.cpp
# simple_ids fixtures: TinyLlama-v0.3, Llama-3.2-1B, gemma-2-2b) — model-gated cases self-skip
bin/daslang -jit dastest/dastest.das -- --test tests/dasLLAMA/

# BPE tokenizer corpus gate (no model needed — uses the in-repo ggml-vocab-llama-bpe fixture)
bin/daslang -jit modules/dasLLAMA/harness/bpe_test.das

# Ad-hoc parity vs llama.cpp for a new model / prompt (wires both sides)
modules/dasLLAMA/harness/parity.sh <model.gguf> [N] [quant] [prompt]
```

---

## Engine capabilities

What a model needs to "just work" today:

| Feature | Supported |
|---|---|
| GGUF weight types (read directly) | **F32, F16, Q8_0, Q4_0, MXFP4** (MXFP4 experts dequant at load and self-quantize to the chosen storage) |
| On-the-fly self-quantization | Q8, Q4 (from an F16/F32 model) |
| Architecture | `llama`, `qwen2`, `qwen3`, `phi3`, `gemma2`, `gemma3`, `gemma4`, `qwen2moe`, `gpt-oss` — a self-registering arch registry (`dasllama_arch_*.das`, `[init]`); the loader dispatches on GGUF `general.architecture`, splits Phi3's fused attn_qkv / gate_up at load, and panics with the registered list on an unknown arch |
| Attention | MHA **and** GQA (grouped-query); sliding-window with a per-layer pattern (Gemma-2 alternating, Gemma-3 5 local : 1 global, Gemma-4 explicit per-layer bool array); heterogeneous per-layer geometry (Gemma-4: sliding vs global layers differ in head size AND kv-head count, incl. V-from-K layers with no attn_v tensor); configurable attention-score scale (Gemma-4: 1.0); per-head attention-sink logits in the softmax denominator (gpt-oss, all three prefill cores + decode); attention + final-logit soft-capping; suppressed-token logit bias |
| Normalization | RMSNorm — eps from GGUF metadata (1e-5 Llama/Phi3, 1e-6 Qwen2/Qwen3/Gemma); Gemma's pre+post sandwich norms; per-head Q/K norms pre-RoPE (QK-norm — Qwen3, Gemma-3/4); weightless per-head V-norm (Gemma-4) |
| Positional encoding | RoPE — **NORM** (Llama, adjacent-pair) and **NEOX** (Qwen2 / Phi3 / Gemma, pairs offset by head_size/2); per-pair freq scaling + θ from metadata (llama3 NTK-by-parts; Phi3 LongRoPE short factors + attn_factor mscale); θ=10000 default, 500000 Llama-3, 1e6 Qwen2.5; per-layer dual θ + linear position scaling (Gemma-3: sliding layers 10k unscaled, global layers 1M ÷8 on the 4B); p-RoPE — proportional freq factors on global layers only, with per-class head sizes (Gemma-4); YaRN (gpt-oss: factor 32 / original context 4096) — the NTK-by-parts ramp folds into the same per-pair factor machinery at load, magnitude correction into mscale |
| FFN | SwiGLU, GeGLU **and** clamped `swiglu_oai` (gpt-oss; incl. Phi3's fused gate_up, split at load); **MoE** — routed top-k experts over a softmax / sigmoid / softmax-after-top-k router (un-renormalized or renormalized weights, optional weight scale, optional router + per-expert biases) + optional sigmoid-gated shared expert, expert-major Q8 so the dense kernels apply per expert (`moe_blocks()`; decode fused, prefill naive per-token — grouped GEMM is a ledger item) |
| Tokenizer | **SentencePiece** (Llama-2 family, Phi-3, Gemma), **byte-level BPE / tiktoken** (Llama-3 + Qwen2 + gpt-4o/o200k pre-tokenizers, exact llama.cpp split incl. its GPT4O case-class approximation), **and SPM-style BPE** (Gemma-4: metaspace escape, newline-only pre-split, raw-UTF-8 ranked merges, `<0xXX>` byte fallback — validated against the `ggml-vocab-gemma-4` corpus) |
| Model size | files >4GB load (needed the fmap >4GB engine fix); single >4GB in-memory arrays (a 7.1GB Q8 weight blob, a 4GiB KV cache at native seq_len) work on the default context heap — no `options persistent_heap` needed (needed the 64-bit linear-chunk engine fix) |
| Attention biases | **Qwen2** — Q/K/V projection biases; **gpt-oss** — Q/K/V + output-projection biases |
| Sampling | greedy, temperature, top-k, repetition penalty (`SamplingParams`; greedy = temp 0, bit-identical to argmax) |
| Chat | per-arch data-driven templates in the registry + one segment-accumulation renderer (`dasllama_chat`) — reproduces the reference prefills token-for-token (`test_chat.das`); the template is auto-detected by sniffing the GGUF's embedded `tokenizer.chat_template` (never executed), falling back to the arch heuristic; Qwen3-style `<think>` blocks are stripped from chat history (`strip_think`); Gemma-4 uses its channel-based turn format (`<|turn>` / `<turn|>`, non-thinking opener closes an empty `thought` channel); gpt-oss uses the Harmony-lite template (`<|start|>role<|message|>...<|end|>`, replies end at `<|return|>` / `<|call|>`, channel markers render in decoded text as in llama.cpp) |
| Performance | KV cache, SIMD + JobQue-threaded matmul, activation-quant Q8·Q8 behind a pluggable kernel-backend registry (ARM SDOT/laneq today — `x64_arch.md` for the x64 mirror), flash-attention batched prefill, per-box kernel tuning (`tune_for_this_box.md`) |

## Known **not** yet supported

So there's no ambiguity about what will fail:

- **MoE beyond the qwen2moe / gpt-oss shapes** — grouped expert routing (DeepSeek-V3
  `expert_group_count`) and the expert-selection bias (`exp_probs_b`) panic honestly at load
  (Tier-3 archs — MLA, Mamba/hybrid, multimodal — remain explicitly deferred in
  `API_REWORK.md`).
- **GGUF weight types beyond F32 / F16 / Q8_0 / Q4_0 / MXFP4** — no K-quants / IQ / BF16.
- `encode(..., parse_special)` is reserved and currently a no-op — the chat renderer injects
  special-token *ids* directly (so templates work); parsing special tokens out of free text
  doesn't.
- The legacy greedy `generate(t, s, prompt, steps)` (kept for the token-exact oracle path)
  stops on **BOS only**; the streaming `generate(..., params, max_tokens, blk)` and chat
  `respond` stop via the callback + the arch's registered stop tokens.

---

## How to verify a new model (oracle method)

Correctness is proven by reproducing a reference **token-for-token** (greedy / `temp 0`),
keeping the tokenizer out of the loop so only the loader + forward pass are under test:

1. **Prompt token IDs** from the reference: `llama-tokenize -m <model> -p "<prompt>" --ids`.
2. **Expected output IDs** from the instrumented reference oracle `harness/oracle/simple_ids.cpp`
   (a copy of llama.cpp `examples/simple` that prints greedy token ids), or `run_ids` for the
   llama2.c toy. Greedy via `llama_sampler_init_greedy`.
3. Feed the same prompt IDs through dasLLAMA's forward pass (`harness/parity.das`) and diff the
   generated IDs — `harness/parity.sh <model> [N] [quant] [prompt]` wires both sides automatically.
   Once verified, freeze the prompt + continuation as a fixture in `tests/dasLLAMA/test_parity.das`
   so it becomes a self-skipping regression gate.
   Note: on tiny models a near-tie argmax can flip from sub-ULP numerical differences vs llama.cpp's
   libm — diagnose by the top-2 logit margin (a ~0.02 gap is a tie, not a bug), and prefer a larger
   model for a clean token-for-token gate.
4. For the tokenizer itself: the `ggml-vocab-*.gguf.inp`/`.out` fixtures in
   `~/Work/llama.cpp/models/` are ready-made round-trip test vectors.

Perf is compared with `llama-bench -m <model> -ngl 0 -t 8` (CPU, generation `tg`).
