#!/bin/bash
# pk parity gate for one (model, wav): das pk_parity_probe vs parakeet-cli -ng -ps
# tuples compared: (i, id, frame, dur_idx, dur_val)
MODEL=$1
WAV=$2
TAG=$3
SP=$(dirname "$0")
CLI=~/Work/whisper.cpp/build/bin/parakeet-cli

"$CLI" -m "$MODEL" -f "$WAV" -ng -ps > "$SP/cli_$TAG.out" 2>&1
bin/daslang -jit modules/dasLLAMA/harness/pk_parity_probe.das -- "$MODEL" "$WAV" > "$SP/probe_$TAG.out" 2>&1

grep -E '^ *\[ *[0-9]+\] id=' "$SP/cli_$TAG.out" \
  | sed -E 's/^ *\[ *([0-9]+)\] id= *([0-9]+) frame= *([0-9]+) dur_idx= *([0-9]+) dur_val= *([0-9]+).*/\1 \2 \3 \4 \5/' \
  > "$SP/cli_$TAG.tuples"

for SIDE in F32 Q8 F32R F32SAME Q8R Q8SAME; do
    grep -E "^$SIDE	" "$SP/probe_$TAG.out" | awk -F'\t' '{print $2, $3, $4, $5, $6}' > "$SP/${SIDE}_$TAG.tuples"
done

report() {
    local name=$1 a=$2 b=$3
    if cmp -s "$a" "$b"; then
        echo "$TAG $name: EXACT ($(wc -l < "$a" | tr -d ' ') tokens)"
    else
        echo "$TAG $name: DIFF ($(diff "$a" "$b" | grep -c '^<') lines)"
        diff "$a" "$b" | head -8
    fi
}

report "F32-vs-CLI " "$SP/cli_$TAG.tuples" "$SP/F32_$TAG.tuples"
report "Q8-vs-CLI  " "$SP/cli_$TAG.tuples" "$SP/Q8_$TAG.tuples"
report "F32R-vs-F32" "$SP/F32_$TAG.tuples" "$SP/F32R_$TAG.tuples"
report "F32S-vs-F32" "$SP/F32_$TAG.tuples" "$SP/F32SAME_$TAG.tuples"
report "Q8R-vs-Q8  " "$SP/Q8_$TAG.tuples" "$SP/Q8R_$TAG.tuples"
report "Q8S-vs-Q8  " "$SP/Q8_$TAG.tuples" "$SP/Q8SAME_$TAG.tuples"
