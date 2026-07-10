# ASR CPU scoreboard (living doc — CURRENT numbers only; history in git + Changelog)

Method: best-of-reps per side, CPU-only everywhere (`-ng`), greedy, transcribe time excludes
model load. Matched threads per box. das = parakeet/whisper q8 encoder default (word-exact vs
fp32, see Correctness). cli = whisper.cpp `whisper-cli`/`parakeet-cli` (macOS links
Accelerate → its f32 GEMMs ride **AMX**; zen2 is plain AVX2). onnx = onnx-asr + ONNX-Runtime
int8 (engine-level `onnx_bench.py`, no HTTP). Rows marked with the date+rev they were measured;
a das-only re-sweep compares against the stored cli/onnx TSV baselines (never re-benched
without cause — noise policy: >2-3% run-to-run swings mean other software, not thermals).

## Parakeet-TDT 0.6B v2 — das vs parakeet-cli vs ONNX-Runtime int8

### Apple M1 Max, 8 threads

<!-- GEN:asr Parakeet-TDT v2 m1 -->
_Apple M1 Max, 8 threads — daslang 0.6.3, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | parakeet-cli ms | onnx ms | das/parakeet-cli |  das/onnx | das xRT |
| :-------- | ------: | -----: | --------------: | ------: | ---------------: | --------: | ------: |
| jfk.wav   |      11 |    198 |             336 |     483 |        **0.59x** | **0.41x** |    55.6 |
| jfk3.wav  |      33 |    605 |             749 |     874 |        **0.81x** | **0.69x** |    54.5 |
| gb1.wav   |     199 |   5681 |            6662 |    7188 |        **0.85x** | **0.79x** |    35.0 |
| hp0.wav   |     273 |   9126 |           10955 |   11552 |        **0.83x** | **0.79x** |    29.9 |
| hp0x2.wav |     547 |  28277 |           37610 |       - |        **0.75x** |         - |    19.3 |
<!-- /GEN:asr Parakeet-TDT v2 m1 -->

Source: `performance/profile_asr_m1.json` (das) + `performance/baseline_asr_m1.tsv` (references).

### AMD Ryzen Threadripper 3990X, 16 threads

<!-- GEN:asr Parakeet-TDT v2 zen2 -->
_AMD Ryzen Threadripper 3990X 64-Core Processor, 16 threads — daslang unknown, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | parakeet-cli ms | onnx ms | das/parakeet-cli | das/onnx | das xRT |
| :-------- | ------: | -----: | --------------: | ------: | ---------------: | -------: | ------: |
| jfk.wav   |      11 |    380 |             679 |       - |        **0.56x** |        - |    28.9 |
| jfk3.wav  |      33 |   1130 |            1781 |       - |        **0.63x** |        - |    29.2 |
| gb1.wav   |     199 |   9180 |           16753 |       - |        **0.55x** |        - |    21.6 |
| hp0.wav   |     273 |  14288 |           27991 |       - |        **0.51x** |        - |    19.1 |
| hp0x2.wav |     547 |  41048 |           92567 |       - |        **0.44x** |        - |    13.3 |
<!-- /GEN:asr Parakeet-TDT v2 zen2 -->

Source: `performance/profile_asr_zen2.json` (das) + `performance/baseline_asr_zen2.tsv` (references).

## Parakeet-TDT 0.6B v3 — das vs parakeet-cli vs ONNX-Runtime int8

onnx's exported graph bakes a max input length: hp0x2 overflows its rel-pos table → skipped
(das/cli handle it).

### Apple M1 Max, 8 threads

<!-- GEN:asr Parakeet-TDT v3 m1 -->
_Apple M1 Max, 8 threads — daslang 0.6.3, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | parakeet-cli ms | onnx ms | das/parakeet-cli |  das/onnx | das xRT |
| :-------- | ------: | -----: | --------------: | ------: | ---------------: | --------: | ------: |
| jfk.wav   |      11 |    203 |             343 |     472 |        **0.59x** | **0.43x** |    54.3 |
| jfk3.wav  |      33 |    631 |             770 |     906 |        **0.82x** | **0.70x** |    52.3 |
| gb1.wav   |     199 |   5559 |            6784 |    7212 |        **0.82x** | **0.77x** |    35.7 |
| hp0.wav   |     273 |   9019 |           11101 |   11535 |        **0.81x** | **0.78x** |    30.3 |
| hp0x2.wav |     547 |  27901 |           38062 |       - |        **0.73x** |         - |    19.6 |
<!-- /GEN:asr Parakeet-TDT v3 m1 -->

Source: `performance/profile_asr_m1.json` (das) + `performance/baseline_asr_m1.tsv` (references).

### AMD Ryzen Threadripper 3990X, 16 threads

<!-- GEN:asr Parakeet-TDT v3 zen2 -->
_AMD Ryzen Threadripper 3990X 64-Core Processor, 16 threads — daslang unknown, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | parakeet-cli ms | onnx ms | das/parakeet-cli | das/onnx | das xRT |
| :-------- | ------: | -----: | --------------: | ------: | ---------------: | -------: | ------: |
| jfk.wav   |      11 |    426 |             692 |       - |        **0.62x** |        - |    25.8 |
| jfk3.wav  |      33 |   1153 |            1799 |       - |        **0.64x** |        - |    28.6 |
| gb1.wav   |     199 |   9178 |           17054 |       - |        **0.54x** |        - |    21.7 |
| hp0.wav   |     273 |  14203 |           28987 |       - |        **0.49x** |        - |    19.2 |
| hp0x2.wav |     547 |  41213 |           94314 |       - |        **0.44x** |        - |    13.3 |
<!-- /GEN:asr Parakeet-TDT v3 zen2 -->

Source: `performance/profile_asr_zen2.json` (das) + `performance/baseline_asr_zen2.tsv` (references).

## LibriSpeech test-clean, 25 short clips — per-clip latency (dictation case)

### Apple M1 Max, 8 threads

<!-- GEN:asr librispeech m1 -->
| side             | mean ms |     p50 |     p95 |
| :--------------- | ------: | ------: | ------: |
| das v2           | **175** | **182** | **287** |
| parakeet-cli v2  |     310 |     306 |     437 |
| onnx v2          |     381 |     396 |     542 |
| das v3           | **180** | **186** | **294** |
| parakeet-cli v3  |     316 |     317 |     456 |
| onnx v3          |     401 |     383 |     572 |
| das tiny         | **121** | **122** | **147** |
| whisper-cli tiny |     127 |     126 |     163 |
| onnx tiny        |     422 |     418 |     510 |
<!-- /GEN:asr librispeech m1 -->

Source: `performance/profile_asr_m1.json` (das rows bold). das leads AMX cli on every side —
parakeet v2/v3 and whisper tiny — and runs 2–3.6× faster than onnx-int8. whisper-tiny is the
quicker dictation model (p50 ~115 ms), parakeet v2/v3 the stronger.

## Whisper — das vs whisper-cli (`-bs 1 -bo 1 -nf -ng`)

das = tower q8 + threaded gelu table (`d25a46542`) + decoder q8 (`cb20e2954`) + the
parakeet-parity opt pass (`8c10b930e`: per-frame threaded mel, threaded f4 cross_kv
scatters, zero-alloc sessions, hmax+exp4 decode passes) + threaded bias/residual row
passes (`cb26a05d0`) + flattened tower attention (`cab95ee9c`: (head × query-block)
units over the slot-indexed team dispatch — killed the head-unit raggedness that
dominated encode; bit-exact, fingerprints byte-identical).

### Apple M1 Max, 8 threads

_tiny:_

<!-- GEN:asr Whisper tiny m1 -->
_Apple M1 Max, 8 threads — daslang 0.6.3, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | whisper-cli ms | onnx ms | das/whisper-cli |  das/onnx | das xRT |
| :-------- | ------: | -----: | -------------: | ------: | --------------: | --------: | ------: |
| jfk.wav   |      11 |    117 |            124 |     416 |       **0.94x** | **0.28x** |    94.1 |
| jfk3.wav  |      33 |    264 |            314 |       - |       **0.84x** |         - |   125.0 |
| gb1.wav   |     199 |   1302 |           1955 |       - |       **0.67x** |         - |   152.6 |
| hp0.wav   |     273 |   1647 |           2121 |       - |       **0.78x** |         - |   165.9 |
| hp0x2.wav |     547 |   3397 |           4701 |       - |       **0.72x** |         - |   160.9 |
<!-- /GEN:asr Whisper tiny m1 -->

_large-v3-turbo:_

<!-- GEN:asr Whisper large-v3-turbo m1 -->
_Apple M1 Max, 8 threads — daslang 0.6.3, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | whisper-cli ms | onnx ms | das/whisper-cli | das/onnx | das xRT |
| :-------- | ------: | -----: | -------------: | ------: | --------------: | -------: | ------: |
| jfk.wav   |      11 |   2490 |           2144 |    2318 |           1.16x |    1.07x |     4.4 |
| jfk3.wav  |      33 |   5147 |           4447 |       - |           1.16x |        - |     6.4 |
| gb1.wav   |     199 |  21589 |          25355 |       - |       **0.85x** |        - |     9.2 |
| hp0.wav   |     273 |  31634 |          32876 |       - |       **0.96x** |        - |     8.6 |
| hp0x2.wav |     547 |  60608 |          64500 |       - |       **0.94x** |        - |     9.0 |
<!-- /GEN:asr Whisper large-v3-turbo m1 -->

Source: `performance/profile_asr_m1.json` (das) + `performance/baseline_asr_m1.tsv` (references);
onnx is jfk-only (single-window adapter). The flattened tower attention (`cab95ee9c`) had das
**beat AMX cli on all five tiny rows** and win every turbo row past jfk3 (hp0 0.99x, hp0x2 0.96x —
both were cli's). Stage breakdown (per rep, jfk): tiny encode 81.7 / decode 23.3 / cross_kv 5.6;
turbo encode 2540 / decode 107 / cross_kv 41.

### AMD Ryzen Threadripper 3990X, 16 threads

_tiny:_

<!-- GEN:asr Whisper tiny zen2 -->
_AMD Ryzen Threadripper 3990X 64-Core Processor, 16 threads — daslang unknown, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | whisper-cli ms | onnx ms | das/whisper-cli |  das/onnx | das xRT |
| :-------- | ------: | -----: | -------------: | ------: | --------------: | --------: | ------: |
| jfk.wav   |      11 |    210 |            263 |     606 |       **0.80x** | **0.35x** |    52.3 |
| jfk3.wav  |      33 |    503 |            563 |       - |       **0.89x** |         - |    65.6 |
| gb1.wav   |     199 |   2662 |           3090 |       - |       **0.86x** |         - |    74.7 |
| hp0.wav   |     273 |   3288 |           3894 |       - |       **0.84x** |         - |    83.1 |
| hp0x2.wav |     547 |   6587 |           8069 |       - |       **0.82x** |         - |    83.0 |
<!-- /GEN:asr Whisper tiny zen2 -->

_large-v3-turbo:_

<!-- GEN:asr Whisper large-v3-turbo zen2 -->
_AMD Ryzen Threadripper 3990X 64-Core Processor, 16 threads — daslang unknown, 2026-07-09 (Parsec off)._

| file      | audio s | das ms | whisper-cli ms | onnx ms | das/whisper-cli |  das/onnx | das xRT |
| :-------- | ------: | -----: | -------------: | ------: | --------------: | --------: | ------: |
| jfk.wav   |      11 |   3638 |           6972 |    3890 |       **0.52x** | **0.94x** |     3.0 |
| jfk3.wav  |      33 |   7711 |          14234 |       - |       **0.54x** |         - |     4.3 |
| gb1.wav   |     199 |  33630 |          80386 |       - |       **0.42x** |         - |     5.9 |
| hp0.wav   |     273 |  48139 |         103665 |       - |       **0.46x** |         - |     5.7 |
| hp0x2.wav |     547 |  93666 |         199539 |       - |       **0.47x** |         - |     5.8 |
<!-- /GEN:asr Whisper large-v3-turbo zen2 -->

Source: `performance/profile_asr_zen2.json` (das) + `performance/baseline_asr_zen2.tsv` (references);
onnx is jfk-only (single-window adapter, >30 s clips skipped). Same flattened tower attention
(`cab95ee9c`) as on M1: das leads whisper-cli on every turbo row and sits at cli parity / leads long
on tiny; das beats onnx-int8 ~3x on the comparable tiny row. No VNNI on Zen 2 (plain AVX2).

## Canary-Qwen 2.5B — das vs the NeMo SALM reference engine

llama.cpp has **zero** canary/SALM/FastConformer support and onnx-asr ships no canary export, so the
only reference is **NeMo SALM greedy** (`canary_qwen_bench.py`, engine-level python, **CPU** — torch
threads, no MPS). das runs **fp32** (the token-for-token parity load: LoRA-merged Qwen3-1.7B decoder
+ f32 FastConformer encoder; a q8 path is the perf follow-up). Correctness is token-for-token
(`test_canary_qwen_oracle`).

### Apple M1 Max, 8 threads

<!-- GEN:asr Canary-Qwen 2.5B m1 -->
_Apple M1 Max, 8 threads — daslang 0.6.3, 2026-07-09 (Parsec off)._

| file     | audio s | das ms | nemo ms |  das/nemo | das xRT |
| :------- | ------: | -----: | ------: | --------: | ------: |
| jfk.wav  |      11 |   5206 |    7918 | **0.66x** |     2.1 |
| jfk3.wav |      33 |  16981 |   21722 | **0.78x** |     1.9 |
| gb1.wav  |     199 | 127742 |   35319 |     3.62x |     1.6 |
<!-- /GEN:asr Canary-Qwen 2.5B m1 -->

Source: `performance/profile_asr_m1.json` (das) + `performance/baseline_asr_m1.tsv` (references).
das **leads on the short/dictation clips** (jfk/jfk3 ~0.7–0.8x — the Canary-Qwen use case): NeMo
carries a heavy fixed per-`generate` overhead that dominates a few-second clip. It **trails 3.7x on
the 3-minute gb1** — the fp32 1.7B decoder is
bandwidth-bound prefilling gb1's ~2500 audio soft tokens (exactly the knob a q8 decoder would
halve), where NeMo's batched-BLAS decode scales better. das xRT holds ~1.5–2.0 across the board.

## Gemma-4 E2B audio — das vs llama-mtmd-cli (CPU-only)

das = gemma4a Conformer encoder **fp32** (correctness-first — encode is not the perf gate) + Gemma-4
decoder q8 (matching mtmd). Reference = `llama-mtmd-cli --temp 0 --jinja --reasoning off` (no-think),
**CPU-only** (Accelerate/AMX, Metal off). Transcribe excludes model load; both greedy, one 17.4 s clip.

### Apple M1 Max, 8 threads

<!-- GEN:asr Gemma-4 E2B audio m1 -->
_Apple M1 Max, 8 threads — daslang 0.6.3, 2026-07-09 (Parsec off)._

| file              | audio s | das ms | mtmd ms |  das/mtmd | das xRT |
| :---------------- | ------: | -----: | ------: | --------: | ------: |
| gemma4a_test2.wav |      17 |   5966 |   18687 | **0.32x** |     2.9 |
<!-- /GEN:asr Gemma-4 E2B audio m1 -->

Source: `performance/profile_asr_m1.json` (das) + `performance/baseline_asr_m1.tsv` (references).
**das leads ~3x.** On a genuine CPU-only basis, ggml's Conformer audio ops don't route through
BLAS/AMX, so mtmd's encode is ~16 s (≈99% of its total) — das's optimized fp32 scalar Conformer
(~1.9 s) beats it ~9x on encode. The prior "das trails 3.9x" compared das-CPU against an mtmd whose
audio encode was silently **Metal/GPU**-offloaded (mislabeled CPU-only) — a CPU-vs-GPU mismatch.

### AMD Ryzen Threadripper 3990X, 16 threads

<!-- GEN:asr Gemma-4 E2B audio zen2 -->
_AMD Ryzen Threadripper 3990X 64-Core Processor, 16 threads — daslang unknown, 2026-07-09 (Parsec off)._

| file              | audio s | das ms | mtmd ms | das/mtmd | das xRT |
| :---------------- | ------: | -----: | ------: | -------: | ------: |
| gemma4a_test2.wav |      17 |   9268 |    8252 |    1.12x |     1.9 |
<!-- /GEN:asr Gemma-4 E2B audio zen2 -->

Source: `performance/profile_asr_zen2.json` (das) + `performance/baseline_asr_zen2.tsv` (references).

## Qwen3-Omni-30B audio — das vs llama-mtmd-cli (CPU-only)

Audio-in/text-out (Talker out of scope). das = SHARED qwen3a AuT tower **fp32** (d_model 1280 × ff
5120, 32 blocks — correctness-first, not the perf gate) + qwen3vlmoe (30B-A3B) thinker q8 (matching
mtmd). Reference = `llama-mtmd-cli --temp 0 --jinja --reasoning off` (no-think), **CPU-only** (Metal
off). Transcribe excludes model load; both greedy.

### Apple M1 Max, 8 threads

<!-- GEN:asr Qwen3-Omni-30B audio m1 -->
_Apple M1 Max, 8 threads — daslang 0.6.3, 2026-07-09 (Parsec off)._

| file     | audio s | das ms | mtmd ms |  das/mtmd | das xRT |
| :------- | ------: | -----: | ------: | --------: | ------: |
| jfk.wav  |      11 |   4011 |   21791 | **0.18x** |     2.7 |
| jfk3.wav |      33 |   8222 |   45163 | **0.18x** |     4.0 |
<!-- /GEN:asr Qwen3-Omni-30B audio m1 -->

Source: `performance/profile_asr_m1.json` (das) + `performance/baseline_asr_m1.tsv` (references).
**das leads ~5x.** CPU-only, the AuT tower is entirely encode-bound in ggml (~21 s jfk / ~45 s jfk3,
≈99% of mtmd's total); das's tower does it in ~1.7 / 4.8 s. Same CPU-vs-GPU correction as gemma4a —
the prior "das trails 3-4x" measured mtmd's Metal-offloaded encode, mislabeled CPU-only.

### AMD Ryzen Threadripper 3990X, 16 threads

<!-- GEN:asr Qwen3-Omni-30B audio zen2 -->
_AMD Ryzen Threadripper 3990X 64-Core Processor, 16 threads — daslang unknown, 2026-07-09 (Parsec off)._

| file     | audio s | das ms | mtmd ms |  das/mtmd | das xRT |
| :------- | ------: | -----: | ------: | --------: | ------: |
| jfk.wav  |      11 |   5984 |  318961 | **0.02x** |     1.8 |
| jfk3.wav |      33 |  10139 |   11763 | **0.86x** |     3.3 |
<!-- /GEN:asr Qwen3-Omni-30B audio zen2 -->

Source: `performance/profile_asr_zen2.json` (das) + `performance/baseline_asr_zen2.tsv` (references).

## Correctness

- das fp32 is token-for-token with parakeet-cli (v2 jfk 33 + gb1 786; v3 jfk 38 + gb1 655)
  and with whisper-cli (tiny jfk, suite oracle), and Canary-Qwen with NeMo SALM greedy
  (jfk + 2 LibriSpeech clips, incl. trailing EOS).
- Gemma-4 E2B audio (gemma4a Conformer): the fp32 encoder soft tokens match mtmd's audio
  embeddings at rel ~0.0027 (float-reduction-order noise, not a bug); the no-think greedy
  transcription is token-for-token with mtmd-cli through the 48-token confident prefix and
  diverges only at the Gemma-4 q8 decoder's OWN ~0.6-logit near-tie (llama.cpp's raw logits at
  that step: three tokens within 0.6). `test_gemma4a_audio_oracle` asserts the confident head.
- Qwen3-Omni-30B (audio-in/text-out; SHARED qwen3a AuT tower + qwen3vlmoe MoE thinker): the greedy
  transcription is **FULL token-for-token** with mtmd-cli on jfk + 2 LibriSpeech clips incl. the
  trailing `<|im_end|>` (151645), with NO near-tie divergence. `test_qwen3omni_audio_oracle` (large-tier).
- das q8 (the path benched here): parakeet ids/text exact vs fp32, gb1 shows a handful of
  duration-pick flips (≤4-frame timestamp drift); whisper (tower + decoder q8) word-exact
  on tiny/small/large-v3-turbo, base drops one comma on a 0.018-logit fp32 top-2 near-tie
  (teacher-forced adjudication; `wh_q8_probe`).
- onnx-int8 changes TEXT vs fp32 (e.g. jfk "for you, ask" → "for you. Ask").

## Changelog

- 2026-07-08: M1 Class-2 (Canary, Gemma-4 E2B, Qwen3-Omni-30B) now GENERATED by the suite too — all
  M1 model sections are suite-driven; only zen2 rows stay hand-authored. **Methodology correction:**
  the mtmd (gemma4a/qwen3omni) reference is now genuine **CPU-only** (Accelerate/AMX, Metal off). The
  prior "das trails 3–4x" was a CPU-vs-GPU mismatch — the fast mtmd numbers rode Metal (GPU), since
  ggml's Conformer/AuT audio ops don't hit BLAS/AMX; on CPU-only the encode is 16–45 s and **das
  leads 3–5x** (gemma4a 0.32x, q3o 0.17x/0.19x). Reference no-think via a fresh llama.cpp patch
  (`harness/mtmd_bench.patch`: expose `--reasoning` to mtmd-cli + thread `enable_thinking`; run
  `--reasoning off`), CPU-only build `llama.cpp-clean/build-amx`. Canary das now loads its encoder
  (2-file); NeMo ref is CPU (torch, no MPS); das leads short (0.69x/0.81x), trails gb1 (3.74x).
- 2026-07-08: the M1 Parakeet v2/v3, Whisper tiny/turbo, and LibriSpeech dictation tables are now
  GENERATED by the profiling suite (`performance/gen_asr_profile.das` → `profile_asr_m1.json` →
  `gen_results.das`, spliced between `<!-- GEN:asr … -->` markers; prose hand-maintained). All
  references (parakeet-cli/whisper-cli + onnx) re-established fresh this round (Parsec off) into
  `baseline_asr_m1.tsv` — within noise of the prior stored rows. Parakeet v2 gains onnx columns.
  Class-2 (Canary/Gemma-4/Qwen3-Omni) + zen2 rows remain hand-authored pending their suite run.
- 2026-07-08: NEW Qwen3-Omni-30B audio section (Wave A3) — das (fp32 SHARED qwen3a AuT tower + q8
  qwen3vlmoe MoE thinker) vs `llama-mtmd-cli`. FULL token-for-token (jfk + 2 LibriSpeech, incl.
  trailing `<|im_end|>`). das trails 3.1x→4.0x: fp32 scalar audio tower (~4.8x/4.0x on encode) + the
  MoE thinker path; the A3 gate is fp32 encoder + parity. TSVs `results_q3o_m1_t8.tsv` /
  `results_q3o_m1_mtmd.tsv`.
- 2026-07-08: NEW Gemma-4 E2B audio section — das (fp32 gemma4a Conformer + q8 Gemma-4 decoder)
  vs the CLI oracle `llama-mtmd-cli` (no-think). das trails 3.9x: fp32 scalar encoder (16x on
  encode) + long-context decode gap; the A2 gate is fp32 encoder correctness (rel ~0.0027 vs
  mtmd soft tokens). TSVs `results_g4a_m1_t8.tsv` / `results_g4a_m1_mtmd.tsv`.
- 2026-07-08 `daf12e7b7`: NEW Canary-Qwen 2.5B section — das (fp32) vs the NeMo SALM reference
  engine (`canary_qwen_bench.py`; no llama.cpp/onnx canary support). das leads every short clip
  1.4–3x, trails 3.7x on the fp32-decoder-bound 3-min gb1. TSVs `results_cq_m1_t8.tsv` /
  `results_cq_m1_nemo.tsv`.
- 2026-07-08 `cab95ee9c`: flattened tower attention over (head × query-block) units via the
  new slot-indexed team dispatch (jobque `team_parallel_for_indexed` `9f7b10288` +
  `maybe_parallel_for_indexed` `3800b2aa4`) — bit-exact (pre/post fingerprints
  byte-identical, 6 model×wav combos, q8+fp32). zen2 das re-sweep: tiny -14-24%
  (cli parity short, leads long), turbo -12-14% (0.45-0.58x). M1 re-sweep (Parsec off):
  das -9-10% every row — whisper tiny beats AMX cli on all five corpus rows + LibriSpeech
  (p50 117 vs 129), turbo wins everything past jfk3.
- 2026-07-08 (Parsec-off window): M1 whisper das re-sweep @ `cb26a05d0` (-35-45% vs the
  07-07 rows — tiny beats AMX cli on 4 of 5 rows) + NEW baselines: M1 whisper onnx-int8
  jfk columns, LibriSpeech whisper-tiny 3-way. Parakeet das re-check: within noise of the
  standing 07-07 rows (no table change).
- 2026-07-08 `cb26a05d0`: threaded bias/residual row passes (the "fc1/fc2 q8 rate gap" —
  sub-buckets showed single-threaded bias bandwidth, not requant); zen2 turbo -3-5%.
- 2026-07-08 `8c10b930e`: whisper parakeet-parity opt pass (per-frame threaded mel `a19a9d5ec`,
  threaded f4 cross_kv scatters `dec9f8656`, phase-0 zero-alloc `3c31be3a0`, decode
  hmax+exp4 `8c10b930e`); zen2 das re-sweep — tiny -22-25%, turbo -6-8%. M1 whisper table
  still @ `a97881dfb` pending a Parsec window.
- 2026-07-08 `cb20e2954`: whisper decoder q8; zen2 das re-sweep — end-to-end neutral there
  (logits/cross_kv wins vs cache-hot GEMV losses), M1 re-sweep pending Parsec window.
- 2026-07-08 `63e2ac191`: zen2 onnx whisper columns (jfk-only — the onnx-asr whisper
  adapter is single-window; >30 s rows skipped by the harness).
- 2026-07-07 `c5ad73980`+: doc restructured — current tables only, per-platform sections.
- 2026-07-07 `97e7e7cf6`: zen2 v3 three-side round (first v3/onnx numbers on that box).
- 2026-07-07 `0ee3807ec`: zen2 das re-sweep post dispatch-fix + TUNE — das leads every row.
- 2026-07-07 `17abcd32d`: M1 das re-sweep post dispatch-fix — das leads every row; the
  pre-fix das rows (2026-07-06 tables) measured a bare `with_job_que()` fifo dispatch
  (2.2x handicap) and are superseded; cli/onnx TSVs from that round remain the baselines.
- 2026-07-06 `ee83e59b5`: Parsec-off cli/onnx standing baselines (M1); zen2 v2 cli baseline.
