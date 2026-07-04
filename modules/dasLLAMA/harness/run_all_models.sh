#!/usr/bin/env bash
# dasLLAMA vs llama.cpp across every local model at a fixed core count.
#
#   run_all_models.sh <cores> [reps]
#
# <cores> maps to BOTH sides apples-to-apples: DAS_JOBQUE_THREADS=<cores> (post-fix = <cores>-1
# workers + the computing main == <cores> lanes) and llama-bench -t <cores>. dasLLAMA's per-N
# single-shot is noisy, so each dasLLAMA number is the BEST of <reps> (default 3); llama-bench
# self-averages. Prints a per-model line as it goes, then a summary table.
#
# Config via env (no box-specific defaults):
#   DASLLAMA_MODELS_DIR  (REQUIRED)  directory holding the .gguf models
#   LLAMA_BENCH          llama-bench binary (default: found on PATH)
#   DASLANG              daslang binary (default: <repo>/bin/Release/daslang.exe)
#   DASLLAMA_ROOT        repo root (default: derived from this script's location)
set -u
CORES="${1:?usage: run_all_models.sh <cores> [reps]}"
REPS="${2:-3}"
ROOT="${DASLLAMA_ROOT:-$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)}"
DAS="${DASLANG:-$ROOT/bin/Release/daslang.exe}"
MODELS="${DASLLAMA_MODELS_DIR:?set DASLLAMA_MODELS_DIR to the directory holding the .gguf models}"
LBENCH="${LLAMA_BENCH:-$(command -v llama-bench 2>/dev/null || echo llama-bench)}"
PREFILL="$ROOT/modules/dasLLAMA/benchmarks/prefill_perf.das"
DECODE="$ROOT/modules/dasLLAMA/benchmarks/llama3_perf.das"

# display-name | gguf filename (Q8_0 dense, mxfp4 for gpt-oss)
MODELS_LIST=(
  "SmolLM2-135M|SmolLM2-135M-Instruct-Q8_0.gguf"
  "Qwen3-0.6B|Qwen3-0.6B-Q8_0.gguf"
  "Llama-3.2-1B|Llama-3.2-1B-Instruct-Q8_0.gguf"
  "gemma-3-1b|gemma-3-1b-it-Q8_0.gguf"
  "gemma-3-4b|gemma-3-4b-it-Q8_0.gguf"
  "Qwen3-4B|Qwen3-4B-Instruct-2507-Q8_0.gguf"
  "Phi-3.5-mini|Phi-3.5-mini-instruct-Q8_0.gguf"
  "Qwen1.5-MoE-A2.7B|Qwen1.5-MoE-A2.7B-Chat.Q8_0.gguf"
  "gpt-oss-20b|gpt-oss-20b-mxfp4.gguf"
)

best() { awk 'BEGIN{m=0}{if($1+0>m)m=$1+0}END{if(m>0)printf "%.1f",m; else printf "ERR"}'; }

das_prefill() { # $1 = model path -> best pp512 t/s over REPS
  for _ in $(seq 1 "$REPS"); do
    DAS_JOBQUE_THREADS="$CORES" "$DAS" -jit "$PREFILL" -- "$1" 2>/dev/null \
      | grep 'N=512:' | grep -oE 'prefill [0-9]+us [0-9.]+ tok/s' | grep -oE '[0-9.]+ tok/s' | grep -oE '^[0-9.]+'
  done | best
}
das_decode() { # $1 = model path -> best gen t/s over REPS
  for _ in $(seq 1 "$REPS"); do
    DAS_JOBQUE_THREADS="$CORES" "$DAS" -jit "$DECODE" -- "$1" 2>/dev/null \
      | grep -oE '\-> [0-9.]+ tok/s' | grep -oE '[0-9.]+'
  done | best
}

echo "=== dasLLAMA vs llama.cpp @ ${CORES} cores (best-of-${REPS} dasLLAMA, llama-bench -t ${CORES}) ==="
ROWS=""
for entry in "${MODELS_LIST[@]}"; do
  name="${entry%%|*}"; file="${entry#*|}"; path="$MODELS/$file"
  if [ ! -f "$path" ]; then echo "  [skip] $name ($file not found)"; continue; fi
  dpp=$(das_prefill "$path"); dtg=$(das_decode "$path")
  lb=$("$LBENCH" -m "$path" -t "$CORES" -p 512 -n 64 2>/dev/null)
  lpp=$(echo "$lb" | awk -F'|' '/pp512/{split($8,a,"±");gsub(/ /,"",a[1]);print a[1]}')
  ltg=$(echo "$lb" | awk -F'|' '/tg64/{split($8,a,"±");gsub(/ /,"",a[1]);print a[1]}')
  [ -z "$lpp" ] && lpp="ERR"; [ -z "$ltg" ] && ltg="ERR"
  echo "  $name:  prefill das=$dpp lcpp=$lpp  |  decode das=$dtg lcpp=$ltg"
  ROWS="$ROWS$name|$dpp|$lpp|$dtg|$ltg"$'\n'
done

echo ""
echo "=== SUMMARY @ ${CORES} cores (t/s; ratio = dasLLAMA / llama.cpp) ==="
printf "%-20s %10s %10s %8s   %10s %10s %8s\n" "model" "das_pp512" "lcpp_pp512" "pp_x" "das_tg" "lcpp_tg" "tg_x"
echo "$ROWS" | grep -E '\|' | while IFS='|' read -r n dpp lpp dtg ltg; do
  ppx=$(awk -v a="$dpp" -v b="$lpp" 'BEGIN{if(b+0>0&&a!="ERR")printf "%.2f",a/b; else printf "-"}')
  tgx=$(awk -v a="$dtg" -v b="$ltg" 'BEGIN{if(b+0>0&&a!="ERR")printf "%.2f",a/b; else printf "-"}')
  printf "%-20s %10s %10s %8s   %10s %10s %8s\n" "$n" "$dpp" "$lpp" "$ppx" "$dtg" "$ltg" "$tgx"
done
echo "=== done ==="
