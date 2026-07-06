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

## M1 (8P+2E), all sides 8 threads — 2026-07-06

parakeet-tdt-0.6b-**v2** (f32 bin), das vs parakeet-cli, 3 reps:

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 682 | 407 | 1.67x | 16.1 | 27.0 |
| jfk3.wav | 33 | 1303 | 888 | 1.47x | 25.3 | 37.2 |
| gb1.wav | 199 | 9659 | 7643 | 1.26x | 20.6 | 26.0 |
| hp0.wav | 273 | 14491 | 12130 | 1.19x | 18.9 | 22.5 |
| hp0x2.wav | 547 | 44971 | 42153 | 1.07x | 12.2 | 13.0 |

parakeet-tdt-0.6b-**v3** (f32 bin), das vs parakeet-cli vs ONNX-Runtime int8, 3 reps
(onnx = istupakov v3 export via onnx-asr; its graph bakes a max input length — hp0x2
overflows the rel-pos table and is skipped, das/cli handle it fine):

| file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx | das xRT | cli xRT | onnx xRT |
|---|---|---|---|---|---|---|---|---|---|
| jfk.wav | 11 | 703 | 352 | 491 | 2.00x | 1.43x | 15.7 | 31.3 | 22.4 |
| jfk3.wav | 33 | 1347 | 812 | 936 | 1.66x | 1.44x | 24.5 | 40.6 | 35.3 |
| gb1.wav | 199 | 9425 | 6736 | 7450 | 1.40x | 1.27x | 21.1 | 29.5 | 26.7 |
| hp0.wav | 273 | 14524 | 11166 | 11879 | 1.30x | 1.22x | 18.8 | 24.5 | 23.0 |
| hp0x2.wav | 547 | 42144 | 38408 | - | 1.10x | - | 13.0 | 14.2 | - |

LibriSpeech test-clean, 25 short clips (best-of-2, per-clip latency — the dictation case):

| side | mean ms | p50 | p95 |
|---|---|---|---|
| das v2 | 614 | 629 | 778 |
| cli v2 | 317 | 316 | 446 |
| das v3 | 631 | 651 | 805 |
| cli v3 | 326 | 324 | 467 |
| onnx-int8 v3 | 411 | 425 | 549 |

M1 shape at matched threads: cli (AMX-backed GEMMs) leads every row; our gap closes with
length (2.0x @ 11 s → 1.07-1.10x @ 9 min) but no longer crosses — the earlier M1 "das wins
long" rows were the cli `-t 4` handicap. onnx-int8 sits between (and pays for its speed
with inexact text + the length cap). Short-clip fixed costs (mel + decode ~60 ms + small-tt
GEMM shapes) remain the biggest M1 lever.

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
