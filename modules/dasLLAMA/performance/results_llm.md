# LLM CPU scoreboard (living doc — CURRENT numbers only; history in git)

GENERATED from `profile_llm_<box>.json` by `gen_results.das` — do not hand-edit. das = dasLLAMA (JIT, Q8); llama.cpp = `llama-bench` CPU (`-ngl 0`, no Accelerate/AMX BLAS). pp*N* = prefill throughput over *N* prompt tokens; tg*N* = greedy generation of *N* tokens. Ratio = das / llama.cpp (>1 = das faster); winners bold.

## Apple M1 Max, 8 threads — daslang 0.6.3, llama.cpp ebd048f, 2026-07-09 (Parsec off)

macOS 26.4.1; box profile `default`.

| model          | active B | quant | pp512 das | pp512 lcpp |  das/lcpp | tg128 das | tg128 lcpp | das/lcpp |
| :------------- | -------: | :---- | --------: | ---------: | --------: | --------: | ---------: | -------: |
| SmolLM2-135M   |     0.13 | q8    |    4416.9 |     3905.3 | **1.13x** |     346.9 |      409.6 |    0.85x |
| Qwen2.5-0.5B   |     0.49 | q8    |    2025.4 |     1814.0 | **1.12x** |     161.0 |      173.7 |    0.93x |
| Qwen3-0.6B     |     0.60 | q8    |    1532.4 |     1364.3 | **1.12x** |     131.0 |      138.9 |    0.94x |
| gemma-3-1B     |     1.00 | q8    |    1085.7 |     1027.8 | **1.06x** |      83.7 |       90.4 |    0.93x |
| TinyLlama-1.1B |     1.10 | q8    |     866.0 |      784.9 | **1.10x** |      88.9 |       93.7 |    0.95x |
| Llama-3.2-1B   |     1.24 | q8    |     867.0 |      857.2 | **1.01x** |      76.4 |       81.4 |    0.94x |
| Qwen2.5-1.5B   |     1.54 | q8    |     628.9 |      607.3 | **1.04x** |      59.5 |       64.1 |    0.93x |
| SmolLM2-1.7B   |     1.71 | q8    |     545.3 |      497.7 | **1.10x** |      55.5 |       58.8 |    0.94x |
| gemma-4-E2B    |     2.25 | q8    |     391.4 |      233.2 | **1.68x** |      37.1 |       37.6 |    0.99x |
| gemma-2-2B     |     2.61 | q8    |     438.3 |      393.0 | **1.12x** |      35.7 |       36.5 |    0.98x |
| Phi-3.5-mini   |     3.82 | q8    |     250.6 |      224.2 | **1.12x** |      26.4 |       27.5 |    0.96x |
| gemma-3-4B     |     3.88 | q8    |     281.1 |      252.9 | **1.11x** |      24.9 |       25.5 |    0.98x |
| Qwen3-4B       |     4.02 | q8    |     236.3 |      218.8 | **1.08x** |      24.4 |       25.7 |    0.95x |
| gemma-4-E4B    |     4.59 | q8    |     202.7 |      119.8 | **1.69x** |      19.3 |       19.4 |    0.99x |
| Mistral-7B     |     7.25 | q8    |     121.2 |      114.3 | **1.06x** |      14.2 |       14.8 |    0.96x |
| Llama-3.1-8B   |     8.03 | q8    |     119.5 |      119.1 | **1.00x** |      13.6 |       14.2 |    0.96x |

## AMD Ryzen Threadripper 3990X 64-Core Processor, 16 threads — daslang unknown, llama.cpp fdb1db877, 2026-07-09 (Parsec off)

Windows 11; box profile `box_profile.json`.

| model          | active B | quant | pp512 das | pp512 lcpp |  das/lcpp | tg128 das | tg128 lcpp | das/lcpp |
| :------------- | -------: | :---- | --------: | ---------: | --------: | --------: | ---------: | -------: |
| SmolLM2-135M   |     0.13 | q8    |    2423.1 |     2362.0 | **1.03x** |     138.3 |      210.9 |    0.66x |
| Qwen2.5-0.5B   |     0.49 | q8    |    1258.9 |     1023.5 | **1.23x** |      66.5 |       84.6 |    0.79x |
| Qwen3-0.6B     |     0.60 | q8    |     944.9 |      708.2 | **1.33x** |      56.2 |       69.1 |    0.81x |
| gemma-3-1B     |     1.00 | q8    |     664.1 |      521.5 | **1.27x** |      38.2 |       44.0 |    0.87x |
| TinyLlama-1.1B |     1.10 | q8    |     616.3 |      406.3 | **1.52x** |      40.2 |       44.0 |    0.91x |
| Llama-3.2-1B   |     1.24 | q8    |     630.8 |      415.4 | **1.52x** |      37.0 |       39.6 |    0.93x |
| Qwen2.5-1.5B   |     1.54 | q8    |     413.8 |      323.2 | **1.28x** |      28.3 |       30.0 |    0.94x |
| SmolLM2-1.7B   |     1.71 | q8    |     384.1 |      247.8 | **1.55x** |      26.1 |       27.6 |    0.94x |
| gemma-4-E2B    |     2.25 | q8    |     260.9 |      209.9 | **1.24x** |      17.9 |       19.3 |    0.93x |
| gemma-2-2B     |     2.61 | q8    |     299.4 |      201.2 | **1.49x** |      17.1 |       17.4 |    0.98x |
| Phi-3.5-mini   |     3.82 | q8    |     179.2 |      114.0 | **1.57x** |      12.8 |       13.7 |    0.93x |
| gemma-3-4B     |     3.88 | q8    |     190.0 |      130.4 | **1.46x** |      11.9 |       12.4 |    0.95x |
| Qwen3-4B       |     4.02 | q8    |     169.8 |      112.8 | **1.50x** |      11.6 |       12.4 |    0.93x |
| gemma-4-E4B    |     4.59 | q8    |     143.4 |      101.8 | **1.41x** |       9.2 |       10.3 |    0.89x |
| Mistral-7B     |     7.25 | q8    |      97.7 |       67.2 | **1.45x** |       6.9 |        7.5 |    0.92x |
| Llama-3.1-8B   |     8.03 | q8    |      94.8 |       66.9 | **1.42x** |       6.4 |        7.1 |    0.90x |

