#!/bin/bash
# zen2 16-core-capped parakeet sweep, interleaved das/cli, driven over ssh
set -uo pipefail
RAW=/Users/borisbatkin/Work/daScript/modules/dasLLAMA/benchmarks/asr/results_parakeet_zen2_t16.tsv
MODEL='E:\whisper.cpp\models\ggml-parakeet-tdt-0.6b-v2-f32.bin'
CLI='E:\whisper.cpp\build\bin\Release\parakeet-cli.exe'
WAVS="jfk.wav jfk3.wav gb1.wav hp0.wav hp0x2.wav"
: > "$RAW"
for rep in 1 2 3; do
    echo "== rep $rep das =="
    wavargs=""
    for w in $WAVS; do wavargs="$wavargs --wav E:\\asr_corpus\\$w"; done
    ssh zen2 "cd /d E:\\das && set DAS_JOBQUE_THREADS=16&& bin\\Release\\daslang.exe -jit modules\\dasLLAMA\\benchmarks\\asr\\asr_bench.das -- --model $MODEL $wavargs --reps 1 2>&1" 2>/dev/null |
        awk -v rep="$rep" -F'\t' '$1=="BENCH" { printf "das\t%s\t%s\t%s\t%s\t%s\n", $2, $3, $4, rep, $6 }' | tee -a "$RAW"
    echo "== rep $rep cli =="
    for w in $WAVS; do
        out=$(ssh zen2 "$CLI -m $MODEL -f E:\\asr_corpus\\$w -t 16 -ng 2>&1" 2>/dev/null)
        ms=$(echo "$out" | awk '/print_timings:.*load time/ { load = $(NF-1) } /print_timings:.*total time/ { total = $(NF-1) } END { printf "%.3f", total - load }')
        printf "cli\tggml-parakeet-tdt-0.6b-v2-f32.bin\t%s\t0\t%s\t%s\n" "$w" "$rep" "$ms" | tee -a "$RAW"
    done
done
echo ZEN2-SWEEP-DONE
