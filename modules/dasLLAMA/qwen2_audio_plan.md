# Qwen2-Audio plan — audio input for dasLLAMA

## Direction

Speech/audio→text on the existing engine: a Whisper-large-v3 encoder tower + Qwen2-Audio's
linear projector produce soft tokens that splice into the EXISTING qwen2 decoder at the
`<|AUDIO|>` placeholder. No cross-attention anywhere; the decoder is untouched. The encoder
is shared infrastructure — the same tower unlocks Ultravox (llama decoder, have it) and most
of a Whisper-proper port later.

Oracle = llama.cpp mtmd. ggml-org ships NO pre-quantized GGUF for Qwen2-Audio (their note:
"very poor result", ref PR #13760) — we convert `Qwen/Qwen2-Audio-7B-Instruct` ourselves with
the in-tree `convert_hf_to_gguf.py` (guaranteed tensor-name compat with the checkout's mtmd).
Model quality is the model's problem; parity with mtmd is ours. Perf: `-jit` only, AOT =
compile-gate, same as the rest of dasLLAMA.

Audio input: dasAudio already decodes MP3/WAV/FLAC/Vorbis (`decode_audio`, miniaudio) and
resamples at decode time (`make_decoder(filename, rate, channels)` → 16 kHz mono directly).

## The pipeline (exact ops, from mtmd `models/whisper-enc.cpp` + `clip.cpp build_vit` + `mtmd-audio.cpp`)

0. **Load**: file → 16 kHz mono f32 PCM (dasAudio).
1. **Mel**: STFT n_fft=400, hop=160, Hann; power spectrum → 201 bins; 128-mel filterbank;
   `log10(max(x,1e-10))`; clamp to global `max−8`; `(x+4)/4`. 30 s chunks → `[3000×128]`.
   Exact padding/edge rules + filterbank source = mtmd-audio.cpp (verify at implementation).
   - **dasMinfft is pow2-only; Whisper's DFT is 400-point** → the ledger's "via dasMinfft"
     doesn't hold. Instead the DFT is two GEMMs with precomputed twiddles
     (`Re = frames·cos[400×201]`, `Im = frames·sin`), power = Re²+Im², mel = one more GEMM
     `[201→128]`. The whole frontend is existing matmul kernels; ~0.5 GMAC per 30 s chunk.
2. **Conv frontend**: conv1d k=3 s=1 "same" + bias → gelu_erf; conv1d k=3 s=2 "same" + bias
   → gelu_erf; transpose → `[1500×1280]`. Convs = im2col gather + existing batched GEMM.
3. **+pos-emb**: rows 0..n_pos−1 of `position_embd` — LOADED from the mmproj (no sinusoid
   generation).
4. **32 pre-LN blocks** (d=1280, 20 heads, hs=64, ffn=5120): LayerNorm(w,b) → attention
   (q has bias, k has NO bias, v bias, out bias; non-causal, no cache, scale 1/√64) →
   residual; LayerNorm(w,b) → fc1+b → gelu_erf → fc2+b → residual.
5. **avg_pool1d(k=2,s=2)** over time → `[750×1280]`, THEN post-LN (order matters — pool sits
   between the last block and ln_post, inside mtmd's build_vit).
6. **Projector**: single linear `mm_fc_w [1280→3584] + mm_fc_b` → 750 soft tokens / 30 s.
7. **Splice**: ChatML prompt with the audio segment rendered as
   `<|audio_bos|>` + 750 embeddings + `<|audio_eos|>`; prefill consumes a mixed
   token/embedding stream; generation after prefill is ordinary tokens.

## Integration shape (das side)

- **AudioTower struct** embedding a blob-container `Model` (fblob for conv/norm/bias/pos-emb,
  qblob+qscales for the 7 GEMM weight families: wq/wk/wv/wo, fc1/fc2, projector). All batched
  mm entry points take explicit `(t, woff, n, d, npos)` — the tower stores its own offsets and
  calls the same kernels; zero kernel-signature changes. Q8 repack per-tensor with explicit
  offsets (same primitive `repack_q8_weights` uses).
- **New kernels**: `layernorm_batch` (mean/var — decoder only has RMS), `gelu_erf_batch`
  (erf — bind/verify libm parity with ggml's erff), time-axis avg-pool, im2col gather,
  non-causal batched attention (flash-prefill is causal+cache-coupled; encoder gets its own
  loop over the same `gemm_f32` tiles).
- **forward_prefill split**: today tokens are consumed only in the `embed_row` loop filling
  `s.x_b` (dasllama_common.das:4184). Factor the body into `forward_prefill_x` (assumes
  `s.x_b` pre-filled) + keep `forward_prefill(tokens)` as the filler wrapper + add
  `forward_prefill_embd(embd)`. Audio path requires q8 mode initially (the q4/npos≤0 fallback
  loops per-token `forward()` which embeds internally — panic with a clear message).

## Oracle strategy

- `llama-mtmd-cli -m decoder.gguf --mmproj mmproj.gguf --audio f.wav -p ...` = end-to-end
  token stream (temp 0) → GEN_IDS-style token-for-token parity, the arc's acceptance gate.
- `MTMD_DEBUG_EMBEDDINGS=1` (clip.cpp:4484) dumps the projected soft tokens → stage-level
  gate for mel+conv+encoder+projector before the decoder is even wired.
- Fixtures: `llama.cpp/tools/mtmd/test-2.mp3` (in-tree, what mtmd's own tests use) + jfk.wav
  (the canonical whisper 11 s clip) + one LibriSpeech test-clean utterance + one non-speech
  sound (Qwen2-Audio does general audio understanding, not just ASR).

## Slices

- **A. Oracle rig**: venv convert HF→GGUF (decoder Q8_0 via llama-quantize; mmproj f16),
  mtmd-cli reference runs on the fixtures, MTMD_DEBUG_EMBEDDINGS reference dumps. Verify:
  decoder GGUF arch string (expect plain `qwen2`; alias if `qwen2audio`), audio special-token
  ids, chat template.
- **B. mmproj loader + tower**: GGUFMeta reuse; tensor table → blobs + offsets + q8 repack.
- **C. Mel frontend** + parity vs mtmd's mel (patch-dump or python reference on the fixture).
- **D. Conv + encoder + projector forward** → embedding parity vs MTMD_DEBUG_EMBEDDINGS.
- **E. Splice + prefill + generate** → token-for-token parity; audio-chat demo.
- **F. Tests + docs**: suite tests (model-gated like existing dasLLAMA tests), README, ledger
  sweep.

## Findings / open questions (updated as slices land)

- mel filterbank provenance in mtmd-audio.cpp (generated vs embedded) — pin at slice C.
- exact STFT padding (center/reflect? final-chunk pad-to-30s?) — pin at slice C.
- `<|AUDIO|>` / `<|audio_bos|>` / `<|audio_eos|>` ids in the converted decoder GGUF — slice A.
- whether ggml's gelu_erf is table-driven or erff-exact in this checkout — slice D parity will say.

## Performance ledger

- Encoder GEMMs ride the existing generated-kernel family as-is (n=1280/5120 batch shapes).
  A dedicated tune pass over encoder shapes (1500-token batch, always-prefill regime) only if
  the encoder becomes a measured bottleneck vs mtmd.
- Mel-as-GEMM twiddle matrices are f32 fblob consts (~410 KB) — quantizing them is noise, skip.
- 30 s chunking processes chunks serially; multi-chunk audio could pipeline encoder chunks —
  only relevant for long-audio use, not scoped.
