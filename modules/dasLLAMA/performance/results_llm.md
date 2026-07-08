# LLM CPU scoreboard (living doc — CURRENT numbers only; history in git)

GENERATED from `profile_llm_<box>.json` by `gen_results.das` — do not hand-edit. das = dasLLAMA (JIT, Q8); llama.cpp = `llama-bench` CPU (`-ngl 0`, no Accelerate/AMX BLAS). pp*N* = prefill throughput over *N* prompt tokens; tg*N* = greedy generation of *N* tokens. Ratio = das / llama.cpp (>1 = das faster); winners bold.

## Apple M1 Max, 8 threads — daslang 0.6.3, llama.cpp ebd048f, 2026-07-08 (Parsec off)

macOS 26.4.1; box profile `default`.

| model          | active B | quant | pp512 das | pp512 lcpp |  das/lcpp | tg128 das | tg128 lcpp | das/lcpp |
| :------------- | -------: | :---- | --------: | ---------: | --------: | --------: | ---------: | -------: |
| SmolLM2-135M   |     0.13 | q8    |    4163.6 |     3905.3 | **1.07x** |     329.6 |      409.6 |    0.80x |
| Qwen2.5-0.5B   |     0.49 | q8    |    2031.7 |     1814.0 | **1.12x** |     150.7 |      173.7 |    0.87x |
| Qwen3-0.6B     |     0.60 | q8    |    1441.6 |     1364.3 | **1.06x** |     120.8 |      138.9 |    0.87x |
| gemma-3-1B     |     1.00 | q8    |    1055.8 |     1027.8 | **1.03x** |      82.4 |       90.4 |    0.91x |
| TinyLlama-1.1B |     1.10 | q8    |     829.7 |      784.9 | **1.06x** |      84.3 |       93.7 |    0.90x |
| Llama-3.2-1B   |     1.24 | q8    |     889.6 |      857.2 | **1.04x** |      73.9 |       81.4 |    0.91x |
| Qwen2.5-1.5B   |     1.54 | q8    |     620.8 |      607.3 | **1.02x** |      55.0 |       64.1 |    0.86x |
| SmolLM2-1.7B   |     1.71 | q8    |     543.7 |      497.7 | **1.09x** |      53.5 |       58.8 |    0.91x |
| gemma-4-E2B    |     2.25 | q8    |     408.4 |      233.2 | **1.75x** |      35.6 |       37.6 |    0.95x |
| gemma-2-2B     |     2.61 | q8    |     419.8 |      393.0 | **1.07x** |      32.8 |       36.5 |    0.90x |
| Phi-3.5-mini   |     3.82 | q8    |     231.9 |      224.2 | **1.03x** |      24.8 |       27.5 |    0.90x |
| gemma-3-4B     |     3.88 | q8    |     269.1 |      252.9 | **1.06x** |      23.3 |       25.5 |    0.92x |
| Qwen3-4B       |     4.02 | q8    |     216.0 |      218.8 |     0.99x |      23.3 |       25.7 |    0.91x |
| gemma-4-E4B    |     4.59 | q8    |     206.8 |      119.8 | **1.73x** |      18.5 |       19.4 |    0.95x |
| Mistral-7B     |     7.25 | q8    |     127.2 |      114.3 | **1.11x** |      13.4 |       14.8 |    0.90x |
| Llama-3.1-8B   |     8.03 | q8    |     132.0 |      119.1 | **1.11x** |      12.7 |       14.2 |    0.89x |

