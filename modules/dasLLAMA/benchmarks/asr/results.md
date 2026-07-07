# ASR side-by-side results (living doc)

Method: interleaved das/cli(/onnx) reps, best-of-reps, CPU-only every side (`-ng`), greedy,
per-transcribe time excludes model load everywhere. das runs WITHOUT `options fast_math`
(x64-JIT miscompile under the flag — fixed on this branch; on M1 the flag was worth nothing
on this path anyway). **Matched thread caps on every side**: M1 = 8 (the P-core count —
also parakeet-cli's calibrated best; `-t 10` regresses on E-core stragglers), zen2 = 16.
das lanes via `DAS_THREADS`/`DAS_JOBQUE_THREADS`, cli `-t`, onnx ORT `intra_op` (engine-level
`onnx_bench.py` driving onnx-asr directly — no HTTP; the mil-ad server hardcodes intra_op=4,
so the server itself is slower than this column). Corpus: `make` (+ `make librispeech`).
das = `bbatkin/audio-perf` @ `c7f1c9c8a`, parakeet q8 encoder default.

Correctness on these rows: das fp32 is token-for-token with parakeet-cli (v2 jfk 33/33 +
gb1 786/786; v3 jfk 38/38 + gb1 655/655 — ids, frames, dur idx+val). das q8 (the path
benched here) is id/text-exact vs fp32 on both models; v3 gb1 flips 16/655 duration picks
(≤4-frame transient timestamp drift). onnx-int8 changes TEXT vs fp32 (e.g. jfk "for you,
ask" → "for you. Ask") — its int8 is not output-preserving.

Note: whisper.cpp links ggml-blas → on macOS the "CPU" oracle's f32 GEMMs ride
**Accelerate/AMX**; on zen2 it's plain AVX2. That coprocessor is why the M1 story below
differs from zen2. (Earlier M1 tables in this doc's history ran cli at its as-shipped
`-t 4` default — that handicapped cli ~20-30%; superseded by the matched-8T tables.)

## M1 (8P+2E), all sides 8 threads, Parsec OFF — 2026-07-06 (STANDING BASELINE)

das = phase-0 zero-alloc + mel-FFT (`f09bd8bdc`). This round re-ran cli/onnx with Parsec
off and is the standing baseline for those sides — later rounds re-bench das ONLY against
these TSVs (results_pk_m1_t8_p0.tsv / results_pk_ls_m1_t8_p0.tsv). Parsec residency was
worth up to ~15% noise on the earlier same-day round (cli jfk spread v2-vs-v3 407/352
then, 339/344 now); >2-3% run-to-run swings mean other software, not thermals.

parakeet-tdt-0.6b-**v2** (f32 bin), das vs parakeet-cli, 3 reps:

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 642 | 339 | 1.89x | 17.1 | 32.5 |
| jfk3.wav | 33 | 1217 | 749 | 1.62x | 27.1 | 44.1 |
| gb1.wav | 199 | 8859 | 6635 | 1.34x | 22.4 | 30.0 |
| hp0.wav | 273 | 13580 | 11041 | 1.23x | 20.1 | 24.8 |
| hp0x2.wav | 547 | 38764 | 38021 | 1.02x | 14.1 | 14.4 |

parakeet-tdt-0.6b-**v3** (f32 bin), das vs parakeet-cli vs ONNX-Runtime int8, 3 reps
(onnx = istupakov v3 export via onnx-asr; its graph bakes a max input length — hp0x2
overflows the rel-pos table and is skipped, das/cli handle it fine):

| file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx | das xRT | cli xRT | onnx xRT |
|---|---|---|---|---|---|---|---|---|---|
| jfk.wav | 11 | 656 | 344 | 468 | 1.91x | 1.40x | 16.8 | 32.0 | 23.5 |
| jfk3.wav | 33 | 1300 | 773 | 931 | 1.68x | 1.40x | 25.4 | 42.7 | 35.5 |
| gb1.wav | 199 | 8774 | 6725 | 7215 | 1.30x | 1.22x | 22.7 | 29.6 | 27.5 |
| hp0.wav | 273 | 14666 | 11123 | 11563 | 1.32x | 1.27x | 18.6 | 24.6 | 23.6 |
| hp0x2.wav | 547 | 37701 | 38078 | - | **0.99x** | - | 14.5 | 14.4 | - |

LibriSpeech test-clean, 25 short clips (best-of-2, per-clip latency — the dictation case):

| side | mean ms | p50 | p95 |
|---|---|---|---|
| das v2 | 585 | 599 | 762 |
| cli v2 | 314 | 310 | 446 |
| das v3 | 597 | 610 | 782 |
| cli v3 | 320 | 319 | 453 |
| onnx-int8 v3 | 396 | 398 | 529 |

M1 shape: cli (AMX-backed GEMMs) leads until ~9 min, where das reaches parity (v2 1.02x)
and takes its first M1 win (v3 0.99x). Short clips remain ~1.9x. Stage profile per rep
(v2 jfk | v2 gb1, `asr_stage_probe`): ffn 206|2271, conv_module 127|494, attn_proj
113|463, attn_heads 77|3967, conv_sub 61|1021 (single-threaded), attn_out 33|144,
decode 25|548 (v3 45|807 — 8198-row joint), mel 4.8|60 (post-FFT; was 33|181),
pos_emb 1.7|36. Next levers in order: conv_subsample, decode, pos_emb; attn_heads is
the quadratic bulk (23% on gb1) — ledger, not a quick pass.

## zen2 EPYC, both sides 16 threads (`DAS_JOBQUE_THREADS=16` / `-t 16`), 3 reps — 2026-07-06

parakeet-tdt-0.6b-v2 (f32 bin), das vs parakeet-cli (plain AVX2, no AMX):

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 2012 | 666 | 3.02x | 5.5 | 16.5 |
| jfk3.wav | 33 | 3138 | 1782 | 1.76x | 10.5 | 18.5 |
| gb1.wav | 199 | 15599 | 17052 | **0.91x** | 12.7 | 11.7 |
| hp0.wav | 273 | 23702 | 29698 | **0.80x** | 11.5 | 9.2 |
| hp0x2.wav | 547 | 66271 | 95549 | **0.69x** | 8.2 | 5.7 |

zen2 shape: crossover ≈ 2.5-3 min, das wins grow with length (threaded row-blocked
attention + q8 GEMMs scale better than ggml's parakeet graph); short clips lose on
per-layer GEMM shapes at small tt + fixed mel/decode — zen2 jfk (3x) is the worst case
and the next short-clip target. v3 + onnx columns on zen2 pending (box needs the v3 bin
+ an onnxruntime venv).

Whisper-family (fp32 tower, pre-q8): M1 tiny jfk 541 ms vs cli 165 ms (3.3x) — tower q8 queued.
