#!/usr/bin/env bash
# pure_gemm_ladder.sh — the pure-GEMM ladder: das (benchmarks/matmul/bench_gemm_iso.das, both
# row-major and repack tiers) vs llama.cpp (test-backend-ops perf MUL_MAT, fleet cases added by
# harness/backend_ops_shapes.patch) on IDENTICAL shapes at the SAME thread count. This is the
# SPR-session opener: it attributes prefill deltas to the GEMM kernels alone — no attention,
# no KV cache, no model, no tokenizer. (das reports GMAC/s; lcpp GFLOPS = 2*GMAC/s — converted.)
#
# Usage: pure_gemm_ladder.sh [threads] [model|all] [ntok]
#   LCPP_TBO   path to test-backend-ops (default ~/Work/llama.cpp/build/bin/test-backend-ops;
#              SPR: the box tree's build — apply backend_ops_shapes.patch + rebuild first)
#   DAS_ROOT   daScript root (default: two levels up from this script)
# Output: TSV rows on stdout —  engine  model  shape  n  d  ntok  threads  gmacs
set -e
T=${1:-8}
MODEL=${2:-all}
NTOK=${3:-512}
ROOT=${DAS_ROOT:-$(cd "$(dirname "$0")/../../.." && pwd)}
TBO=${LCPP_TBO:-$HOME/Work/llama.cpp/build/bin/test-backend-ops}
MODELS="smol135m qwen06b gemma1b llama1b qwen4b llama8b tinyllama"
[ "$MODEL" != "all" ] && MODELS="$MODEL"

echo "# pure-GEMM ladder  threads=$T ntok=$NTOK  $(date +%F)" >&2
echo -e "engine\tmodel\tshape\tn\td\tntok\tthreads\tgmacs"

# ---- das leg: one bench_gemm_iso run per model; rows carry shape + n x d already ----
# Direct-run wrapper, NOT dastest: dastest compiles with aot_module=true which trips
# tune_aot_gate() — [tune] kernels silently bench their reference bodies there.
for m in $MODELS; do
    DASLLAMA_BENCH_MODEL=$m DASLLAMA_BENCH_NTOK=$NTOK DAS_JOBQUE_THREADS=$T \
        "$ROOT/bin/daslang" -jit "$ROOT/modules/dasLLAMA/benchmarks/matmul/run_gemm_iso.das" 2>&1 |
    awk -v m=$m -v nt=$NTOK '
        /GMAC\/s total/ {
            eng = ($2 == "laneq") ? "das-gen" : "das-rowmajor"
            split($5, wh, "x")
            split($6, th, "=")
            printf "%s\t%s\t%s\t%s\t%s\t%d\t%d\t%.1f\n", eng, m, $3, wh[1], wh[2], nt, th[2], $7
        }'
done

# ---- lcpp legs: one filtered perf run per rung; map (k=n, m=d) back to model/shape names.
# The lcpp-amx rung sets GGML_PERF_WEIGHT_BUFT=AMX (backend_ops_shapes.patch places quantized
# weights into the matching CPU extra buffer type — stock test-backend-ops NEVER exercises the
# AMX mmq path). Env must be UNSET for the plain rung (an empty value strstr-matches any buft).
# On non-AMX silicon the AMX rung finds no buft and just repeats the plain path — ignore it there.
for LENG in lcpp lcpp-amx; do
    if [ "$LENG" = lcpp-amx ]; then
        GGML_PERF_WEIGHT_BUFT=AMX GGML_BENCH_THREADS=$T "$TBO" perf -o MUL_MAT -b CPU -p "type_a=q8_0,type_b=f32" 2>/dev/null
    else
        GGML_BENCH_THREADS=$T "$TBO" perf -o MUL_MAT -b CPU -p "type_a=q8_0,type_b=f32" 2>/dev/null
    fi |
awk -v nt=$NTOK -v t=$T -v ENG=$LENG '
    BEGIN {
        # n(reduction/k) "x" d(out/m) -> "model shape"  — MUST match shapes_for() in bench_gemm_iso.das
        s["576x192"]="smol135m kv"; s["576x576"]="smol135m q"; s["576x1536"]="smol135m w13"; s["1536x576"]="smol135m w2"; s["576x49152"]="smol135m cls"
        s["1024x1024"]="qwen06b kv"; s["1024x2048"]="qwen06b q"; s["2048x1024"]="qwen06b wo"; s["1024x3072"]="qwen06b w13"; s["3072x1024"]="qwen06b w2"; s["1024x151936"]="qwen06b cls"
        s["1152x256"]="gemma1b kv"; s["1152x1024"]="gemma1b q"; s["1024x1152"]="gemma1b wo"; s["1152x6912"]="gemma1b w13"; s["6912x1152"]="gemma1b w2"; s["1152x262144"]="gemma1b cls"
        s["2048x512"]="llama1b kv"; s["2048x2048"]="llama1b q"; s["2048x8192"]="llama1b w13"; s["8192x2048"]="llama1b w2"; s["2048x128256"]="llama1b cls"
        s["2560x1024"]="qwen4b kv"; s["2560x4096"]="qwen4b q"; s["4096x2560"]="qwen4b wo"; s["2560x9728"]="qwen4b w13"; s["9728x2560"]="qwen4b w2"; s["2560x151936"]="qwen4b cls"
        s["4096x1024"]="llama8b kv"; s["4096x4096"]="llama8b q"; s["4096x14336"]="llama8b w13"; s["14336x4096"]="llama8b w2"; s["4096x128256"]="llama8b cls"
        s["2048x5632"]="tinyllama w13"; s["5632x2048"]="tinyllama w2"; s["2048x32000"]="tinyllama cls"
    }
    # portable field extraction (BSD awk / mawk have no 3-arg match())
    function getnum(str, key,   v) { v = str; sub(".*" key, "", v); sub(/[^0-9].*/, "", v); return v + 0 }
    /MUL_MAT\(type_a=q8_0/ {
        gm = getnum($0, ",m="); gn = getnum($0, ",n="); gk = getnum($0, ",k=")
        if (gn != nt) next
        key = gk "x" gm
        if (!(key in s) || (key in seen)) next
        seen[key] = 1
        split(s[key], ms, " ")
        gf = ""; unit = ""
        for (i = 1; i <= NF; i++) if ($i ~ /[GT]FLOPS/) { gf = $(i - 1); unit = $i }   # >=1 TFLOPS switches units; reset code may glue to the token
        sub(/.*m/, "", gf)   # strip a glued ANSI color code (ends in m); no-op when plain
        gmacs = (unit ~ /TFLOPS/) ? gf * 500.0 : gf / 2.0
        printf "%s\t%s\t%s\t%d\t%d\t%d\t%d\t%.1f\n", ENG, ms[1], ms[2], gk, gm, nt, t, gmacs
    }'
done
