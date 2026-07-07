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

## Whisper — das vs whisper-cli (`-bs 1 -bo 1 -nf -ng`)

das = tower q8 + threaded gelu table (`d25a46542`) + decoder q8 (`cb20e2954`) + the
parakeet-parity opt pass (`8c10b930e`: per-frame threaded mel, threaded f4 cross_kv
scatters, zero-alloc sessions, hmax+exp4 decode passes) + threaded bias/residual row
passes (`cb26a05d0` — the "fc1/fc2 q8 rate gap" was single-threaded bias/residual
bandwidth, not requant; ffn mm now runs ~84% of the aggregate lane estimate). Remaining
profiled lever: tower attention head-unit raggedness (tiny 6 / turbo 20 units vs lane
count — dominates encode).

### Apple M1 Max, 8 threads — both sides 2026-07-07 @ `da4254be9`, interleaved, best-of-2

das rows predate decoder q8 (`cb20e2954`) and the opt pass (`8c10b930e`) — re-sweep
pending a Parsec-off window.

| model | file | audio s | das ms | cli ms | das/cli |
|---|---|---|---|---|---|
| tiny | jfk.wav | 11 | 193 | 122 | 1.58x |
| tiny | jfk3.wav | 33 | 451 | 298 | 1.52x |
| tiny | gb1.wav | 199 | 2336 | 1672 | 1.40x |
| tiny | hp0.wav | 273 | 2972 | 2102 | 1.41x |
| tiny | hp0x2.wav | 547 | 5932 | 4836 | 1.23x |
| large-v3-turbo | jfk.wav | 11 | 3311 | 2150 | 1.54x |
| large-v3-turbo | jfk3.wav | 33 | 6972 | 4494 | 1.55x |
| large-v3-turbo | gb1.wav | 199 | 29782 | 25415 | 1.17x |
| large-v3-turbo | hp0.wav | 273 | 41934 | 32878 | 1.28x |
| large-v3-turbo | hp0x2.wav | 547 | 80689 | 64621 | 1.25x |

TSV (both sides): `results_wh_m1_t8.tsv`.

### AMD EPYC Zen 2, 16 threads — das 2026-07-08 @ `cb26a05d0` (opt pass + threaded bias); cli TSV 2026-07-07

| model | file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx |
|---|---|---|---|---|---|---|---|
| tiny | jfk.wav | 11 | 283 | 213 | 643 | 1.33x | **0.44x** |
| tiny | jfk3.wav | 33 | 629 | 500 | - | 1.26x | - |
| tiny | gb1.wav | 199 | 3292 | 2845 | - | 1.16x | - |
| tiny | hp0.wav | 273 | 4007 | 3546 | - | 1.13x | - |
| tiny | hp0x2.wav | 547 | 7985 | 7327 | - | 1.09x | - |
| large-v3-turbo | jfk.wav | 11 | 4277 | 6728 | 3730 | **0.64x** | 1.15x |
| large-v3-turbo | jfk3.wav | 33 | 8944 | 13657 | - | **0.65x** | - |
| large-v3-turbo | gb1.wav | 199 | 38832 | 76720 | - | **0.51x** | - |
| large-v3-turbo | hp0.wav | 273 | 55784 | 100852 | - | **0.55x** | - |
| large-v3-turbo | hp0x2.wav | 547 | 107401 | 189313 | - | **0.57x** | - |

TSVs: das `results_wh_zen2_t16_whopt2.tsv` (best-of-2), cli side of `results_wh_zen2_t16.tsv`,
onnx `results_wh_zen2_t16_onnx.tsv` (2026-07-08). onnx = onnx-community exports, int8, ORT
`intra_op=16` — the adapter is a SINGLE 30 s window (no long-form chunking; >30 s clips
return truncated/empty text — skipped, `63e2ac191`), so jfk is its only valid row. The
whisper opt pass (per-frame threaded mel, threaded f4 cross_kv scatters, zero-alloc
sessions, hmax+exp4 decode passes) cut das tiny 22-25% and turbo 6-8% on this box, and
the threaded bias/residual passes (`cb26a05d0`) another 3-5% on turbo: tiny trails AVX2
cli 1.09-1.33x (was 1.47-1.68x), turbo's lead widens to 0.51-0.65x, and das now beats
onnx-int8 2.3x on its one comparable tiny row. tiny's remaining wall is unchanged —
encoder attn head-units (~72% of encode at 6 units on 16 lanes); decoder q8 stays
net-neutral here (logits/cross_kv wins vs cache-hot per-layer GEMV losses — no VNNI).

## Correctness

- das fp32 is token-for-token with parakeet-cli (v2 jfk 33 + gb1 786; v3 jfk 38 + gb1 655)
  and with whisper-cli (tiny jfk, suite oracle).
- das q8 (the path benched here): parakeet ids/text exact vs fp32, gb1 shows a handful of
  duration-pick flips (≤4-frame timestamp drift); whisper (tower + decoder q8) word-exact
  on tiny/small/large-v3-turbo, base drops one comma on a 0.018-logit fp32 top-2 near-tie
  (teacher-forced adjudication; `wh_q8_probe`).
- onnx-int8 changes TEXT vs fp32 (e.g. jfk "for you, ask" → "for you. Ask").

## Changelog

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
