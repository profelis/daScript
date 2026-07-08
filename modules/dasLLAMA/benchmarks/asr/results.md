# ASR CPU scoreboard (living doc — CURRENT numbers only; history in git + Changelog)

Method: best-of-reps per side, CPU-only everywhere (`-ng`), greedy, transcribe time excludes
model load. Matched threads per box. das = parakeet/whisper q8 encoder default (word-exact vs
fp32, see Correctness). cli = whisper.cpp `whisper-cli`/`parakeet-cli` (macOS links
Accelerate → its f32 GEMMs ride **AMX**; zen2 is plain AVX2). onnx = onnx-asr + ONNX-Runtime
int8 (engine-level `onnx_bench.py`, no HTTP). Rows marked with the date+rev they were measured;
a das-only re-sweep compares against the stored cli/onnx TSV baselines (never re-benched
without cause — noise policy: >2-3% run-to-run swings mean other software, not thermals).

## Parakeet-TDT 0.6B v2 — das vs parakeet-cli

### Apple M1 Max, 8 threads — das 2026-07-07 @ `52cf2e741`; cli TSV 2026-07-06 (Parsec off)

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 207 | 339 | **0.61x** | 53.0 | 32.5 |
| jfk3.wav | 33 | 638 | 749 | **0.85x** | 51.7 | 44.1 |
| gb1.wav | 199 | 5928 | 6635 | **0.89x** | 33.5 | 30.0 |
| hp0.wav | 273 | 9455 | 11041 | **0.86x** | 28.9 | 24.8 |
| hp0x2.wav | 547 | 28874 | 38021 | **0.76x** | 18.9 | 14.4 |

TSVs: das `results_pk_m1_t8_jo.tsv`, cli `results_pk_m1_t8_p0.tsv`.

### AMD EPYC Zen 2, 16 threads — das 2026-07-07 @ `17abcd32d` (post-TUNE); cli TSV 2026-07-06

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 419 | 666 | **0.63x** | 26.2 | 16.5 |
| jfk3.wav | 33 | 1133 | 1782 | **0.64x** | 29.1 | 18.5 |
| gb1.wav | 199 | 10277 | 17052 | **0.60x** | 19.3 | 11.7 |
| hp0.wav | 273 | 15339 | 29698 | **0.52x** | 17.8 | 9.2 |
| hp0x2.wav | 547 | 44789 | 95549 | **0.47x** | 12.2 | 5.7 |

TSVs: das `results_pk_zen2_t16_jo.tsv`, cli `results_parakeet_zen2_t16.tsv`.

## Parakeet-TDT 0.6B v3 — das vs parakeet-cli vs ONNX-Runtime int8

onnx's exported graph bakes a max input length: hp0x2 overflows its rel-pos table → skipped
(das/cli handle it).

### Apple M1 Max, 8 threads — das 2026-07-07 @ `52cf2e741`; cli/onnx TSV 2026-07-06 (Parsec off)

| file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 218 | 344 | 468 | **0.63x** | **0.47x** |
| jfk3.wav | 33 | 678 | 773 | 931 | **0.88x** | **0.73x** |
| gb1.wav | 199 | 6046 | 6725 | 7215 | **0.90x** | **0.84x** |
| hp0.wav | 273 | 9706 | 11123 | 11563 | **0.87x** | **0.84x** |
| hp0x2.wav | 547 | 29455 | 38078 | - | **0.77x** | - |

TSVs: das `results_pk_m1_t8_jo.tsv`, cli/onnx `results_pk_m1_t8_p0.tsv`.

### AMD EPYC Zen 2, 16 threads — ALL THREE sides 2026-07-07 @ `17abcd32d`, interleaved A/B/C

| file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 414 | 673 | 570 | **0.61x** | **0.73x** |
| jfk3.wav | 33 | 1171 | 1757 | 1776 | **0.67x** | **0.66x** |
| gb1.wav | 199 | 9654 | 16670 | 17286 | **0.58x** | **0.56x** |
| hp0.wav | 273 | 14902 | 27775 | 26868 | **0.54x** | **0.55x** |
| hp0x2.wav | 547 | 41436 | 88198 | - | **0.47x** | - |

TSV (all sides): `results_pk_zen2_t16_v3.tsv`. onnx = ORT `intra_op=16`.

## LibriSpeech test-clean, 25 short clips — per-clip latency (dictation case)

### Apple M1 Max, 8 threads — das 2026-07-07 @ `52cf2e741`; cli/onnx TSV 2026-07-06 (best-of-2)

| side | mean ms | p50 | p95 |
|---|---|---|---|
| das v2 | **182** | **183** | **304** |
| cli v2 | 314 | 310 | 446 |
| das v3 | **191** | **194** | **321** |
| cli v3 | 320 | 319 | 453 |
| onnx-int8 v3 | 396 | 398 | 529 |

TSVs: das `results_pk_ls_m1_t8_jo.tsv`, cli/onnx `results_pk_ls_m1_t8_p0.tsv`.

### Apple M1 Max, 8 threads, whisper tiny — das 2026-07-08 @ `cab95ee9c`; cli/onnx TSV 2026-07-08

| side | mean ms | p50 | p95 |
|---|---|---|---|
| das tiny | **117** | **117** | **139** |
| cli tiny | 129 | 129 | 167 |
| onnx tiny-int8 | 431 | 421 | 528 |

TSVs: das `results_wh_ls_m1_t8_attnidx.tsv` (best-of-2), cli/onnx sides of
`results_wh_ls_m1_t8.tsv`. das now leads AMX whisper-cli on short-clip latency (p50 0.91x,
p95 0.83x), 3.6x faster than onnx-int8. (whisper-tiny p50 117 vs parakeet v2 183 — tiny is
the quicker dictation model, parakeet the stronger one.)

## Whisper — das vs whisper-cli (`-bs 1 -bo 1 -nf -ng`)

das = tower q8 + threaded gelu table (`d25a46542`) + decoder q8 (`cb20e2954`) + the
parakeet-parity opt pass (`8c10b930e`: per-frame threaded mel, threaded f4 cross_kv
scatters, zero-alloc sessions, hmax+exp4 decode passes) + threaded bias/residual row
passes (`cb26a05d0`) + flattened tower attention (`cab95ee9c`: (head × query-block)
units over the slot-indexed team dispatch — killed the head-unit raggedness that
dominated encode; bit-exact, fingerprints byte-identical).

### Apple M1 Max, 8 threads — das 2026-07-08 @ `cab95ee9c` (flattened tower attention, Parsec off); cli TSV 2026-07-07

| model | file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx |
|---|---|---|---|---|---|---|---|
| tiny | jfk.wav | 11 | 112 | 122 | 463 | **0.92x** | **0.24x** |
| tiny | jfk3.wav | 33 | 246 | 298 | - | **0.82x** | - |
| tiny | gb1.wav | 199 | 1173 | 1672 | - | **0.70x** | - |
| tiny | hp0.wav | 273 | 1523 | 2102 | - | **0.72x** | - |
| tiny | hp0x2.wav | 547 | 3001 | 4836 | - | **0.62x** | - |
| large-v3-turbo | jfk.wav | 11 | 2629 | 2150 | 2406 | 1.22x | 1.09x |
| large-v3-turbo | jfk3.wav | 33 | 5331 | 4494 | - | 1.19x | - |
| large-v3-turbo | gb1.wav | 199 | 21891 | 25415 | - | **0.86x** | - |
| large-v3-turbo | hp0.wav | 273 | 32420 | 32878 | - | **0.99x** | - |
| large-v3-turbo | hp0x2.wav | 547 | 62128 | 64621 | - | **0.96x** | - |

TSVs: das `results_wh_m1_t8_attnidx.tsv` (best-of-2), cli side of `results_wh_m1_t8.tsv`,
onnx `results_wh_m1_t8_onnx.tsv` (jfk-only — single-window adapter). The flattened tower
attention took the das side another ~9-10% on every row: **tiny now beats AMX cli on ALL
FIVE rows** (jfk was the last holdout at 1.03x) and turbo wins every row past jfk3
(hp0 0.99x, hp0x2 0.96x — both were cli's). Clean-window stage (per rep, jfk): tiny
encode 81.7 (attn_heads 40.4 — the 6-units-on-8-lanes floor is gone; 1.30x on the bucket
vs the 1.33x theoretical), decode 23.3, cross_kv 5.6; turbo encode 2540 (attn_heads 1048,
1.22x on the bucket), decode 107, cross_kv 41.

### AMD EPYC Zen 2, 16 threads — das 2026-07-08 @ `cab95ee9c` (flattened tower attention); cli TSV 2026-07-07

| model | file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx |
|---|---|---|---|---|---|---|---|
| tiny | jfk.wav | 11 | 216 | 213 | 643 | 1.01x | **0.34x** |
| tiny | jfk3.wav | 33 | 520 | 500 | - | 1.04x | - |
| tiny | gb1.wav | 199 | 2782 | 2845 | - | **0.98x** | - |
| tiny | hp0.wav | 273 | 3398 | 3546 | - | **0.96x** | - |
| tiny | hp0x2.wav | 547 | 6841 | 7327 | - | **0.93x** | - |
| large-v3-turbo | jfk.wav | 11 | 3693 | 6728 | 3730 | **0.55x** | **0.99x** |
| large-v3-turbo | jfk3.wav | 33 | 7908 | 13657 | - | **0.58x** | - |
| large-v3-turbo | gb1.wav | 199 | 34182 | 76720 | - | **0.45x** | - |
| large-v3-turbo | hp0.wav | 273 | 48737 | 100852 | - | **0.48x** | - |
| large-v3-turbo | hp0x2.wav | 547 | 93820 | 189313 | - | **0.50x** | - |

TSVs: das `results_wh_zen2_t16_attnidx.tsv` (best-of-2), cli side of `results_wh_zen2_t16.tsv`,
onnx `results_wh_zen2_t16_onnx.tsv` (2026-07-08). onnx = onnx-community exports, int8, ORT
`intra_op=16` — the adapter is a SINGLE 30 s window (no long-form chunking; >30 s clips
return truncated/empty text — skipped, `63e2ac191`), so jfk is its only valid row. The
flattened tower attention (`cab95ee9c` — (head × query-block) units, slot-indexed score
scratch, chunk-per-unit team self-serve) took the das side another 12-24% on this box:
stage probe attn_heads tiny 151 → 66 ms/rep (2.3x; encode 200 → 114) and turbo
2495 → 1492 ms/rep (1.67x; encode 4361 → 3297). tiny now sits at cli parity short and
LEADS long (0.93-0.98x, was 1.09-1.33x); turbo's lead widens to 0.45-0.58x and its jfk
row now edges onnx-int8 (0.99x). das beats onnx-int8 3.0x on the comparable tiny row.
tiny's next wall is decode (~59 ms/rep vs encode 114); decoder q8 stays net-neutral here
(logits/cross_kv wins vs cache-hot per-layer GEMV losses — no VNNI).

## Canary-Qwen 2.5B — das vs the NeMo SALM reference engine

llama.cpp has **zero** canary/SALM/FastConformer support and onnx-asr ships no canary export,
so the only reference is **NeMo SALM greedy** (`canary_qwen_bench.py`, engine-level python, CPU,
timed transcribe excludes model load — same shape as `asr_bench.das`'s BENCH line). das runs
**fp32** here (the token-for-token parity load: LoRA-merged Qwen3-1.7B decoder + f32 FastConformer
encoder); a q8 decoder + q8 encoder is the obvious perf follow-up (not chased — the parity gate is
fp32). Correctness is token-for-token on every clip (model matrix + `test_canary_qwen_oracle`).

### Apple M1 Max, 8 threads — both sides 2026-07-08 @ `daf12e7b7` (Parsec off)

| file | audio s | das ms | nemo ms | das/nemo | das xRT | nemo xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 5433 | 8952 | **0.61x** | 2.0 | 1.2 |
| jfk3.wav | 33 | 17488 | 24098 | **0.73x** | 1.9 | 1.4 |
| 05_1089-134686-0004.wav | 5.2 | 2817 | 5693 | **0.49x** | 1.9 | 0.9 |
| 09_1089-134686-0008.wav | 6.7 | 3664 | 7947 | **0.46x** | 1.8 | 0.8 |
| 15_1089-134686-0014.wav | 2.2 | 1461 | 4317 | **0.34x** | 1.5 | 0.5 |
| gb1.wav | 199 | 131609 | 35466 | 3.71x | 1.5 | 5.6 |

das **leads on every short/dictation clip (1.4–3x — the Canary-Qwen use case)**: NeMo carries a
heavy fixed per-`generate` overhead that dominates a few-second clip (its xRT stays < 1 on the
LibriSpeech clips). It **trails 3.7x on the 3-minute gb1** — the fp32 1.7B decoder is
bandwidth-bound prefilling gb1's ~2500 audio soft tokens (exactly the knob a q8 decoder would
halve), where NeMo's batched-BLAS decode scales better. das xRT holds ~1.5–2.0 across the board.

TSVs: das `results_cq_m1_t8.tsv`, nemo `results_cq_m1_nemo.tsv`.

## Gemma-4 E2B audio — das vs llama-mtmd-cli

The gemma4a Conformer audio path benched vs the CLI oracle `llama-mtmd-cli` (`--temp 0 --jinja`,
no-think turn — a bare user turn; the reasoning channel is near-tie-brittle, disabled both sides).
das runs the encoder **fp32** (correctness-first; the mmproj is bf16 and the Conformer is a scalar
fp32 forward — encode runs once per clip and is explicitly not the perf gate), the Gemma-4 decoder
q8 (matching mtmd). Transcribe time excludes model load; both sides greedy, one 17.4 s clip.

### Apple M1 Max, 8 threads — das 2026-07-08 (Parsec off); mtmd-cli same box/build

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT | das encode ms | cli encode ms |
|---|---|---|---|---|---|---|---|---|
| gemma4a_test2.wav | 17.4 | 6028 | 1547 | 3.90x | 2.89 | 11.3 | 1888 | 117 |

das **trails 3.9x** — the gap is the fp32 **scalar** Conformer encoder (1888 ms vs mtmd's 117 ms
= 16x; ggml runs the audio tower as bf16-weight SIMD GEMMs, das as a plain fp32 forward) plus a
long-context decode gap (~495 audio+prompt positions: das 21.7 tok/s vs cli 78). Both are the
obvious perf follow-ups (a gemm-gen tuned Q8 audio-tower kernel + the long-context decode path);
neither is chased — the A2 gate is fp32 encoder correctness. Ledger note in `model_expansion_plan.md`.

TSVs: das `results_g4a_m1_t8.tsv`, cli `results_g4a_m1_mtmd.tsv`.

## Qwen3-Omni-30B audio — das vs llama-mtmd-cli

Qwen3-Omni-30B-A3B (audio-in/text-out; Talker out of scope) transcription benched vs the CLI oracle
`llama-mtmd-cli` (`--temp 0 --jinja`, a bare user turn on the non-thinking Instruct thinker:
"Transcribe the audio."). das runs the SHARED qwen3a AuT tower **fp32** (correctness-first; the
mmproj is bf16, the tower a scalar fp32 forward — not the perf gate) + the qwen3vlmoe (30B-A3B)
thinker q8 (matching mtmd). Transcribe time excludes model load; both sides greedy, transcribe-only
timers (mtmd measured with an in-`main` `std::chrono` wrap of encode+prefill+generate).

### Apple M1 Max, 8 threads — das 2026-07-08 (Parsec host daemon idle, no active session); mtmd-cli same box/build

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT | das encode ms | cli encode ms |
|---|---|---|---|---|---|---|---|---|
| jfk.wav | 11 | 3625 | 1173 | 3.09x | 3.03 | 9.4 | 1665 | 349 |
| jfk3.wav | 33 | 8263 | 2079 | 3.97x | 3.99 | 15.9 | 4760 | 1191 |

das **trails 3.1x (jfk) → 4.0x (jfk3)** — the gap is the fp32 **scalar** qwen3a AuT tower (d_model
1280 × ff 5120, 32 blocks: 1665/4760 ms vs mtmd's bf16-SIMD 349/1191 ms = ~4.8x/4.0x). The output is
a fixed ~27-token transcription both clips, so the gap widens with clip length as the linear-in-audio
encode dominates. The thinker side is das's grouped q8 MoE prefill (~207 tok/s — the Wave-Q path,
engaged for the audio-embd prefill) + q8 decode, and it too trails ggml here. Both are perf-ledger
items (a gemm-gen tuned Q8 audio-tower kernel for the 1280/5120 dims + the MoE prefill/decode path);
neither chased — the A3 gate is fp32 encoder correctness + token-for-token parity. Ledger note in
`model_expansion_plan.md`.

TSVs: das `results_q3o_m1_t8.tsv`, cli `results_q3o_m1_mtmd.tsv`.

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
