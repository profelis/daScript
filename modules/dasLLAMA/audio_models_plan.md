# Audio-models expansion wave — audit action items

Extends the audio arc (qwen2_audio_plan.md + whisper_plan.md) per the 2026-07-06 audit:
add Ultravox, Voxtral, Qwen2.5-Omni (audio), Qwen3-ASR, and Parakeet-TDT, each to the same
bar as everything else in dasLLAMA — **token-for-token vs its reference implementation** —
with README model-matrix rows as each lands. Same branch, same one big PR.

The structural shortcut (from the audit): llama.cpp mtmd serves Ultravox, Voxtral, and
Qwen2-Audio from ONE whisper-encoder graph — the tower we already validated. For those,
"support" = a projector tail + chat wiring, not a new encoder.

## Session A — audio-LLM wave (Ultravox + Voxtral + Qwen2.5-Omni audio)

All three ride existing rails: whisper tower (validated) + decoders we already run.

- **Ultravox v0.5** (llama-3.2-1b dev, llama-3.1-8b validate): the decoder is STOCK
  Llama-3.2-1B / 3.1-8B-Instruct — the Q8 GGUFs are already in models/; only the mmprojs
  download (~1.2 GB each, whisper tower inside). New work: the `ultravox` projector tail —
  stack(proj_stack_factor) frame-concat → mm_1 → swiglu_swapped → mm_2 (mtmd
  whisper-enc.cpp:51-73) — plus loader keys and llama-3 chat splice.
- **Voxtral-Mini-3B** (Mistral): same whisper tower, same stack+SwiGLU tail family
  (`voxtral` projector), llama-arch decoder, [INST] template splice. ggml-org publishes
  only Q4_K_M (K-quants — we don't read them): **self-convert** the HF original with the
  qwen2audio venv recipe (convert_hf_to_gguf.py → decoder Q8_0 + mmproj).
- **Qwen2.5-Omni 3B** (7B validate): audio side is the QWEN2A projector VERBATIM (mtmd
  aliases it); decoder is qwen2. Work ≈ conversion-free download + loader tolerance for the
  omni mmproj (it also carries v.* vision tensors — name-driven loader skips them) + the
  omni chat template + parity runs. Vision input explicitly out of scope.
- Gates: `llama-mtmd-cli --temp 0` token-for-token per model on jfk.wav + test-2.mp3
  (the qwen2audio harness recipe); suite tests model-gated like test_audio.das.
- Possible follow-on freebies to check while here: SeaLLM-Audio (qwen2a family),
  MERaLiON (gemma2 + whisper tower) — audit says small; only if the wave goes smoothly.

## Session B — user-facing API (Boris discussion first)

Shape the transcribe/audio-chat surface knowing all backends: whisper (30 s windows,
timestamps), Qwen3-ASR (LLM-style ASR), Parakeet (streaming transducer), and the
audio-chat family (soft-token splice into chat sessions). Facade placement, segment/result
shapes, naming. Then implement. Tutorials + mic example follow this.

**ALL DECISIONS SETTLED (Boris, 2026-07-06) — session B is now pure implementation:**
- Uniform `load_asr_model(path[, mmproj])` — format sniffed (GGUF magic vs ggml-bin;
  whisper-vs-parakeet bins share the magic, disambiguate on n_vocab ≥ 51864 vs ~1k),
  per-family loaders demote to plumbing, one verb set with internal dispatch. NO family
  names in the public API.
- `caps(m : AsrModel) : AsrCaps` (languages / translate / timestamps none-segment-word /
  streaming / prompt) — advisory; invalid options still panic loudly, never silently ignore.
- Chat-audio verbs live on the facade (`dasllama.das`): `create_chat(m, tower)` (tower
  attached at creation), `add_user_audio(chat, samples)` composing with `add_user(text)`
  in one turn; splice inside render/respond, per-model wiring in the arch registry.
- `WhisperSegment` → shared `TranscribeSegment` + `avg_logprob : float`.
- `lang = "auto"` (whisper language detect, one extra prompt decode) implemented here.
- `create_whisper_session` → `create_session` overload.

**Also in this session: `caps` for LLMs** (Boris: "it's on us regardless — buck stops
here"). The known silent gap: gemma has no system role and the chat layer absorbs the
system prompt without telling anyone. `caps(m : Model) : LlmCaps` declared by each arch
registration (the registry already owns templates/stop tokens — caps live beside them):
system_prompt support at minimum; grow honestly as gaps surface (audio-tower attach,
thinking variants) rather than speculatively.

## Session C — Qwen3-ASR (0.6B dev, 1.7B validate)

qwen3 decoder (registered) + a NEW audio encoder: mtmd's `qwen3a` graph — 128-mel input
processed in 100-frame chunks (chunked windowed attention; ref modeling_qwen3_asr.py).
GGUFs from ggml-org. Oracle = mtmd-cli. Hooks into the session-B API surface.

## Session D — Parakeet-TDT (0.6b-v2)

FastConformer encoder (24L, d=1024, 8h): conv subsampling, macaron dual half-FFN,
depthwise-conv module w/ inference batch-norm, Transformer-XL-style rel-pos attention
(pos_bias u/v — the one genuinely new attention piece); tiny LSTM prediction network +
joint net + TDT greedy loop (token+duration, frame-skipping). Oracle: whisper.cpp checkout
has `parakeet-cli` BUILT in-tree (+ convert-parakeet-to-ggml.py, .nemo downloaded,
test-parakeet-full-jfk as reference). Streaming-native — the natural mic-example backend.

## Session E — mic example + tutorials

**Mic demo runs on Parakeet** (Boris's call — streaming-native, no 30 s window latency),
so E depends on D, plus dasAudio capture (PR #3388) and the session-B API. Tutorials
document the settled surface across ASR + audio-chat.

## Status

- [ ] A. Ultravox (1b + 8b) — mmprojs downloaded
- [ ] A. Voxtral-Mini-3B — HF original downloading; self-convert pending
- [ ] A. Qwen2.5-Omni 3B/7B — GGUFs downloading
- [ ] B. API discussion + implementation
- [ ] C. Qwen3-ASR 0.6B/1.7B
- [ ] D. Parakeet-TDT 0.6b-v2 — .nemo downloading
- [ ] E. mic example + tutorials

## Findings

(collect as sessions land)
