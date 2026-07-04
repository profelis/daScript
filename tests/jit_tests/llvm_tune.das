options gen2

require dastest/testing_boost
require llvm/daslib/llvm_tune

// [tune] framework (llvm/daslib/llvm_tune): normal mode stamps the fallback perm's [llvm_code]
// onto the function itself; the add_plus_k selftest generator emits a+b+k so the stamped perm
// is observable at runtime. Same tolerance contract as llvm_code.das: dastest's in-process
// multi-program execution can serve a reference-tier result with jit instrumentation live, so
// the probe asserts "stamped-perm result or reference tier, never garbage". The grid modes and
// the manifest round-trip are compile-time-env driven (DAS_TUNE_MODE / DAS_TUNE_MANIFEST) and
// are gated by the CLI probes instead — see gemm_generator_plan.md M3.

[tune_perm(k = 0), tune_perm(k = 2), tune_perm(suffix = "declined", decline = true), tune(gen = "llvm_code_selftest::add_plus_k", fallback = "k2")]
def tadd_tuned(a, b : int) : int {
    return a + b
}

[tune_perm(k = 1), tune(gen = "llvm_code_selftest::add_plus_k")]  // no fallback: reference body
def tadd_reference(a, b : int) : int {
    return a + b
}

[test]
def test_llvm_tune(t : T?) {
    var n = 2  // nolint:LINT003 — var defeats const-fold so the calls survive to codegen
    let r = tadd_tuned(n, 3)
    t |> success(r == 7 || r == 5)  // stamped k2 tier (jit) or reference tier — never anything else
    if (!jit_enabled()) {
        t |> equal(r, 5)  // interpreted lane always runs the reference body
    }
    t |> equal(tadd_reference(n, 3), 5)  // no manifest + no fallback = reference body everywhere
}
