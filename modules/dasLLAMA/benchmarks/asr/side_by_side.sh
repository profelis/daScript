#!/bin/bash
# Interleaved A/B ASR speed bench: dasLLAMA vs whisper-cli / parakeet-cli.
# Both sides CPU-only, greedy; per-transcribe time excludes model load on both
# sides (cli: total - load from *_print_timings; ours: BENCH line from asr_bench.das).
# Interleaved rep order (A B A B ...) so thermals hit both sides equally.
#
#   ./side_by_side.sh                     # default matrix
#   MODELS="parakeet tiny" REPS=2 ./side_by_side.sh
#   CORPUS="corpus/librispeech/*.wav" MODELS=parakeet ./side_by_side.sh   # latency batch
set -euo pipefail
cd "$(dirname "$0")"

DAS_ROOT=${DAS_ROOT:-$(cd ../../../.. && pwd)}
WHISPER_CPP=${WHISPER_CPP:-$HOME/Work/whisper.cpp}
REPS=${REPS:-3}
THREADS=${THREADS:-4}                       # oracle -t (calibrate once per box)
MODELS=${MODELS:-"parakeet tiny large-v3-turbo"}
CORPUS=${CORPUS:-"corpus/jfk.wav corpus/jfk3.wav corpus/gb1.wav corpus/hp0.wav corpus/hp0x2.wav"}
RAW=${RAW:-results_raw.tsv}

model_path() {
    case "$1" in
        parakeet) echo "$WHISPER_CPP/models/ggml-parakeet-tdt-0.6b-v2-f32.bin" ;;
        *)        echo "$WHISPER_CPP/models/ggml-$1.bin" ;;
    esac
}

# one oracle run -> transcribe ms (total - load, from *_print_timings)
cli_run_ms() {
    local model=$1 wav=$2 out
    if [ "$model" = "parakeet" ]; then
        out=$("$WHISPER_CPP/build/bin/parakeet-cli" -m "$(model_path "$model")" \
              -f "$wav" -t "$THREADS" -ng 2>&1)
    else
        out=$("$WHISPER_CPP/build/bin/whisper-cli" -m "$(model_path "$model")" \
              -f "$wav" -t "$THREADS" -bs 1 -bo 1 -nf -ng 2>&1)
    fi
    echo "$out" | awk '
        /_print_timings:.*load time/  { load = $(NF-1) }
        /_print_timings:.*total time/ { total = $(NF-1) }
        END { printf "%.3f", total - load }'
}

: > "$RAW"
for model in $MODELS; do
    mpath=$(model_path "$model")
    [ -f "$mpath" ] || { echo "skip $model (no $mpath)"; continue; }
    wavs=""
    files=""
    for w in $CORPUS; do
        [ -f "$w" ] || { echo "skip $w (missing — run make)"; continue; }
        wavs="$wavs --wav $w"; files="$files $w"
    done
    for rep in $(seq "$REPS"); do
        echo "== $model rep $rep: das =="
        das_out=$("$DAS_ROOT/bin/daslang" -jit asr_bench.das -- --model "$mpath" $wavs --reps 1 2>&1) ||
            { echo "$das_out" | tail -5; echo "DAS RUN FAILED for $model"; exit 1; }
        echo "$das_out" |
            awk -v rep="$rep" -F'\t' '$1=="BENCH" { printf "das\t%s\t%s\t%s\t%s\t%s\n", $2, $3, $4, rep, $6 }' |
            tee -a "$RAW"
        echo "== $model rep $rep: cli =="
        for w in $files; do
            dur=$(afinfo "$w" 2>/dev/null | awk '/estimated duration/ { printf "%s", $3 }')
            ms=$(cli_run_ms "$model" "$w")
            printf "cli\tggml-%s.bin\t%s\t%s\t%s\t%s\n" "$model" "$(basename "$w")" "$dur" "$rep" "$ms" |
                tee -a "$RAW"
        done
    done
done

# aggregate: best-of-reps per (side, model, file) -> markdown table
echo
echo "| model | file | audio s | das ms | cli ms | das/cli | das xRT | cli xRT |"
echo "|---|---|---|---|---|---|---|---|"
awk -F'\t' '
    {
        key = $2 "\t" $3; dur[key] = $4
        if ($1 == "das") { if (!(key in a) || $6 < a[key]) a[key] = $6 }
        else             { if (!(key in b) || $6 < b[key]) b[key] = $6 }
        if (!(key in seen)) { order[++n] = key; seen[key] = 1 }
    }
    END {
        for (i = 1; i <= n; i++) {
            k = order[i]; split(k, p, "\t")
            if (k in a && k in b)
                printf "| %s | %s | %.0f | %.0f | %.0f | %.2fx | %.2f | %.2f |\n",
                    p[1], p[2], dur[k], a[k], b[k], a[k] / b[k],
                    dur[k] * 1000 / a[k], dur[k] * 1000 / b[k]
        }
    }' "$RAW"
