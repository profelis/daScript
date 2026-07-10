options gen2
options persistent_heap

require bench_gemm_iso

// Direct-run wrapper for bench_gemm_iso — REQUIRED for real kernel numbers. dastest compiles
// every test with policies.aot_module=true, which trips tune_aot_gate() and stamps reference
// bodies for every [tune] kernel: the dastest rail silently benches the slow tier (measured
// 82 vs 1600 GMAC/s on SPR). Same env contract as the dastest rail (DASLLAMA_BENCH_MODEL,
// DASLLAMA_BENCH_NTOK, DASLLAMA_BENCH_SKIP_ROWMAJOR, DAS_TUNE_MANIFEST, DAS_JOBQUE_THREADS):
//   DAS_JOBQUE_THREADS=24 bin/daslang -jit modules/dasLLAMA/benchmarks/matmul/run_gemm_iso.das

[export]
def main {
    bench_gemm_iso(null)
}
