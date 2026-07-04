options gen2

require dastest/testing_boost
require llvm/daslib/llvm_tune

// Doubles as the child fixture for llvm_tune_modes.das (spawned with DAS_TUNE_MODE=test, -jit:
// main prints every grid variant's result) and as an ordinary suite test (normal mode: the
// [test] below checks the fallback contract). The variants registry exists in every mode —
// reference-row-only under normal — so both faces compile from the same source.

[tune_perm(k = 0), tune_perm(k = 1), tune_perm(k = 2), tune_perm(suffix = "declined", decline = true), tune(gen = "llvm_code_selftest::add_plus_k", fallback = "k1")]
def modes_add(a, b : int) : int {
    return a + b
}

[export]
def main {
    var n = 2  // nolint:LINT003 — var defeats const-fold so the calls survive to codegen
    var vs <- modes_add_variants()
    for (v in vs) {
        print("VARIANT {v._0} -> {invoke(v._1, n, 3)}\n")
    }
    delete vs
}

[test]
def test_modes_client_fallback(t : T?) {
    var n = 2  // nolint:LINT003 — var defeats const-fold so the calls survive to codegen
    let r = modes_add(n, 3)
    t |> success(r == 6 || r == 5)  // stamped fallback k1 tier (jit) or reference tier
    if (!jit_enabled()) {
        t |> equal(r, 5)
    }
}
