# ASR side-by-side results (living doc)

Method: interleaved das/cli reps, best-of-reps, CPU-only both sides (`-ng`), greedy, per-
transcribe time excludes model load on both sides. das runs WITHOUT `options fast_math`
(x64-JIT miscompile under the flag — parakeet encoder NaNs; fix queued. On M1 the flag was
worth nothing on this path anyway: with/without within noise). Corpus: `make`
(+ `make librispeech`). das = `bbatkin/audio-perf` @ `57a346b4d`, parakeet q8 encoder —
**token-for-token with parakeet-cli on every row of both tables**.

Note: whisper.cpp links ggml-blas → on macOS the "CPU" oracle's f32 GEMMs ride
**Accelerate/AMX**; on zen2 it's plain AVX2.

## parakeet-tdt-0.6b-v2 (f32 bin), das vs parakeet-cli — 2026-07-06

M1 MacBook Air (8c), both sides as-shipped threads, 3 reps:

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 688 | 353 | 1.95x | 16.0 | 31.1 |
| jfk3.wav | 33 | 1350 | 879 | 1.54x | 24.4 | 37.5 |
| gb1.wav | 199 | 10237 | 9615 | 1.06x | 19.4 | 20.7 |
| hp0.wav | 273 | 14976 | 16488 | **0.91x** | 18.2 | 16.6 |
| hp0x2.wav | 547 | 44666 | 59165 | **0.75x** | 12.2 | 9.2 |

LibriSpeech test-clean, 25 short clips (best-of-2, per-clip latency — the dictation case):
das mean 615 ms / p50 631 / p95 826; cli mean 339 / p50 345 / p95 492.

zen2 EPYC, both sides 16 threads (`DAS_JOBQUE_THREADS=16` / `-t 16`), 3 reps:

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 2012 | 666 | 3.02x | 5.5 | 16.5 |
| jfk3.wav | 33 | 3138 | 1782 | 1.76x | 10.5 | 18.5 |
| gb1.wav | 199 | 15599 | 17052 | **0.91x** | 12.7 | 11.7 |
| hp0.wav | 273 | 23702 | 29698 | **0.80x** | 11.5 | 9.2 |
| hp0x2.wav | 547 | 66271 | 95549 | **0.69x** | 8.2 | 5.7 |

Shape on both boxes: crossover ≈ 2.5-3 min, das wins grow with length (threaded row-blocked
attention + q8 GEMMs scale better than ggml's parakeet graph); short clips lose on per-layer
GEMM shapes at small tt + fixed mel/decode (~60 ms) — zen2 jfk (3x) is the worst case and
the next short-clip target.

Whisper-family (fp32 tower, pre-q8): M1 tiny jfk 541 ms vs cli 165 ms (3.3x) — tower q8 queued.
