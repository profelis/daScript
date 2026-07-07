# ASR side-by-side results (living doc)

Method: interleaved das/cli(/onnx) reps, best-of-reps, CPU-only every side (`-ng`), greedy,
per-transcribe time excludes model load everywhere. das runs WITHOUT `options fast_math`
(x64-JIT miscompile under the flag — fixed on this branch; on M1 the flag was worth nothing
on this path anyway). **Matched thread caps on every side**: M1 = 8 (the P-core count —
also parakeet-cli's calibrated best; `-t 10` regresses on E-core stragglers), zen2 = 16.
das lanes via `DAS_THREADS`/`DAS_JOBQUE_THREADS`, cli `-t`, onnx ORT `intra_op` (engine-level
`onnx_bench.py` driving onnx-asr directly — no HTTP; the mil-ad server hardcodes intra_op=4,
so the server itself is slower than this column). Corpus: `make` (+ `make librispeech`).
das = `bbatkin/audio-perf` @ `52cf2e741`, parakeet q8 encoder default.

Correctness on these rows: das fp32 is token-for-token with parakeet-cli (v2 jfk 33/33 +
gb1 786/786; v3 jfk 38/38 + gb1 655/655 — ids, frames, dur idx+val). das q8 (the path
benched here) is id/text-exact vs fp32 on both models; gb1 shows a handful of duration-pick
flips (v2 12 / v3 14 tuple lines, ≤4-frame transient timestamp drift, ids/text exact).
onnx-int8 changes TEXT vs fp32 (e.g. jfk "for you, ask" → "for you. Ask") — its int8 is
not output-preserving.

Note: whisper.cpp links ggml-blas → on macOS the "CPU" oracle's f32 GEMMs ride
**Accelerate/AMX**; on zen2 it's plain AVX2. That coprocessor is why the M1 story below
differs from zen2. (Earlier M1 tables in this doc's history ran cli at its as-shipped
`-t 4` default — that handicapped cli ~20-30%; superseded by the matched-8T tables.)

## M1 (8P+2E), all sides 8 threads, Parsec OFF — 2026-07-07 (STANDING; das re-sweep @ `52cf2e741`)

das side re-run only, per the method: cli/onnx numbers come from the 2026-07-06 standing
TSVs (results_pk_m1_t8_p0.tsv / results_pk_ls_m1_t8_p0.tsv); new das rows in
results_pk_m1_t8_jo.tsv / results_pk_ls_m1_t8_jo.tsv. What changed since the previous
round: `asr_bench` had been running BARE `with_job_que()` — no `setup_dasllama_jobque()` —
so every prior das row measured the ~10us/job fifo fork/join instead of the shipped team
dispatch (2.2x end-to-end on jfk; ALL pre-2026-07-07 das rows carry that handicap, cli/onnx
rows are unaffected). On top of the fix: silu4_batch (threaded FFN silu) and gemm_f32_jo
(jj-outer attention tile walk, gb1 attn blocks −20%). Output-parity unchanged — pk_gate
4-way F32-vs-cli EXACT.

parakeet-tdt-0.6b-**v2** (f32 bin), das (3 reps) vs parakeet-cli (stored):

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 207 | 339 | **0.61x** | 53.0 | 32.5 |
| jfk3.wav | 33 | 638 | 749 | **0.85x** | 51.7 | 44.1 |
| gb1.wav | 199 | 5928 | 6635 | **0.89x** | 33.5 | 30.0 |
| hp0.wav | 273 | 9455 | 11041 | **0.86x** | 28.9 | 24.8 |
| hp0x2.wav | 547 | 28874 | 38021 | **0.76x** | 18.9 | 14.4 |

parakeet-tdt-0.6b-**v3** (f32 bin), das (3 reps) vs parakeet-cli vs ONNX-Runtime int8 (stored):

| file | audio s | das ms | cli ms | onnx ms | das/cli | das/onnx | das xRT | cli xRT | onnx xRT |
|---|---|---|---|---|---|---|---|---|---|
| jfk.wav | 11 | 218 | 344 | 468 | **0.63x** | **0.47x** | 50.5 | 32.0 | 23.5 |
| jfk3.wav | 33 | 678 | 773 | 931 | **0.88x** | **0.73x** | 48.7 | 42.7 | 35.5 |
| gb1.wav | 199 | 6046 | 6725 | 7215 | **0.90x** | **0.84x** | 32.9 | 29.6 | 27.5 |
| hp0.wav | 273 | 9706 | 11123 | 11563 | **0.87x** | **0.84x** | 28.2 | 24.6 | 23.6 |
| hp0x2.wav | 547 | 29455 | 38078 | - | **0.77x** | - | 18.6 | 14.4 | - |

LibriSpeech test-clean, 25 short clips (best-of-2, per-clip latency — the dictation case):

| side | mean ms | p50 | p95 |
|---|---|---|---|
| das v2 | **182** | **183** | **304** |
| cli v2 | 314 | 310 | 446 |
| das v3 | **191** | **194** | **321** |
| cli v3 | 320 | 319 | 453 |
| onnx-int8 v3 | 396 | 398 | 529 |

M1 shape: das now leads every row on both models — short-clip dictation included (p50
1.7x faster than AMX cli, 2.1x faster than onnx-int8). Stage profile per rep (v2 jfk |
v2 gb1, `asr_stage_probe` post-fix): ffn 82|1373, attn_heads 34|3071 (blocks 17|2706,
pack+pos 17|365), attn_proj 23|370, conv_module 26|308, decode 23|511, conv_sub 10|128,
attn_out 8|123, mel 2.7|34, pos_emb 1.6|36. Next levers: gb1 = attn_heads blocks (fp32
GEMM+softmax, ~224 GMAC/s aggregate ≈ 90% of the 8-lane scaling ceiling) and decode
(f4-lse, v3-weighted); jfk = the attn pack/pos hoist (~17ms of 34).

## M1 — 2026-07-06 (SUPERSEDED das rows; cli/onnx STANDING BASELINE source)

das = phase-0 zero-alloc + mel-FFT (`f09bd8bdc`), PRE-dispatch-fix — the das rows below
measured the degraded fifo dispatch and are kept only as the session-history record. The
cli/onnx rows remain the standing baseline TSVs (results_pk_m1_t8_p0.tsv /
results_pk_ls_m1_t8_p0.tsv) that later das-only rounds compare against. Parsec residency
was worth up to ~15% noise on the earlier same-day round (cli jfk spread v2-vs-v3 407/352
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

M1 shape then: cli (AMX-backed GEMMs) led until ~9 min, where das reached parity — the
gap was the dispatch handicap, not the kernels (see the 2026-07-07 section).

## zen2 EPYC, both sides 16 threads, 3 reps — 2026-07-07 (STANDING; das re-sweep @ `17abcd32d`)

das side re-run only (cli rows = the 2026-07-06 standing TSV results_parakeet_zen2_t16.tsv;
new das rows in results_pk_zen2_t16_jo.tsv). Same dispatch-fix + silu4_batch + gemm_f32_jo
stack as the M1 round; `tune_kernels` run on the box first (box_profile.json refreshed —
winners matched the shipped per-ISA fallback defaults, deltas within box noise).

parakeet-tdt-0.6b-v2 (f32 bin), das vs parakeet-cli (plain AVX2, no AMX):

| file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |
|---|---|---|---|---|---|---|
| jfk.wav | 11 | 419 | 666 | **0.63x** | 26.2 | 16.5 |
| jfk3.wav | 33 | 1133 | 1782 | **0.64x** | 29.1 | 18.5 |
| gb1.wav | 199 | 10277 | 17052 | **0.60x** | 19.3 | 11.7 |
| hp0.wav | 273 | 15339 | 29698 | **0.52x** | 17.8 | 9.2 |
| hp0x2.wav | 547 | 44789 | 95549 | **0.47x** | 12.2 | 5.7 |

zen2 shape: das now leads every row — the old "crossover ≈ 2.5-3 min" died with the
dispatch fix (jfk was 3.02x, now 0.63x: the fifo cost scaled with 16 lanes and hit short
clips hardest). v3 + onnx columns on zen2 still pending (box needs the v3 bin + an
onnxruntime venv).

## zen2 EPYC — 2026-07-06 (SUPERSEDED das rows; cli STANDING BASELINE source)

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
