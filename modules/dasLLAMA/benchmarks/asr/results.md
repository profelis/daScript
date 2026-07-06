# ASR side-by-side results (living doc)

Method: `side_by_side.sh` — interleaved A/B reps, CPU-only both sides (`-ng`; note
whisper.cpp links ggml-blas → **Accelerate/AMX on macOS**, so the "CPU" oracle rides the
AMX units there), greedy (`-bs 1 -bo 1 -nf` on whisper-cli), per-transcribe time excludes
model load on both sides, best-of-reps. Corpus: `make` (+ `make librispeech`).

⚠️ Bench and examples must NOT set `options fast_math` until the x64-JIT fast-math
miscompile is fixed: on zen2 (AVX2) the parakeet encoder output goes NaN under the flag
(mel is fine; fp32 and q8 identically broken; the `v != v` NaN check itself folds away
under nnan). aarch64 is unaffected. Stage repro: `scratchpad pk_stages_fm.das` (2026-07-06).

## M1 (MacBook Air, 8c) — parakeet-tdt-0.6b-v2 f32, das q8 encoder (token-for-token with cli)

3 reps, 2026-07-06, das = `bbatkin/audio-perf` @ `4ed4e8182` (fast_math ON — aarch64-valid;
re-sweep planned with the flag off for cross-box comparability):

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 686 | 357 | 1.92x | 16.0 | 30.8 |
| jfk3.wav | 33 | 1296 | 887 | 1.46x | 25.5 | 37.2 |
| gb1.wav | 199 | 9788 | 9529 | 1.03x | 20.3 | 20.9 |
| hp0.wav | 273 | 15154 | 16668 | **0.91x** | 18.0 | 16.4 |
| hp0x2.wav | 547 | 44908 | 59188 | **0.76x** | 12.2 | 9.2 |

Crossover ≈ 3 min: beyond it our threaded row-blocked attention + q8 GEMMs scale better
than ggml's parakeet graph. Short clips are bounded by per-layer q8q8 GEMM shapes at small
tt + fixed mel/decode (~60 ms).

LibriSpeech test-clean, 25 short clips (best-of-2, per-clip transcribe latency —
the dictation case): das mean 621 ms / p50 628 / p95 797; cli mean 339 / p50 346 / p95 491.

Whisper-family (fp32 tower, pre-q8): tiny jfk 541 ms vs cli 165 ms (3.3x) — tower q8 next.

## zen2 (EPYC, 16-core cap) — pending

Rig ready (E:\whisper.cpp built, models byte-identical, corpus at E:\asr_corpus, branch
via bundle). Sweep blocked on the fast_math strip (numbers with the flag are invalid on
x64); cap plan: affinity mask + `-t 16` + `DAS_JOBQUE_THREADS=16`.
