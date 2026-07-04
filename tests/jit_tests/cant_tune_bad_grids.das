// [tune] / [tune_perm] validation — covers every grid-shape error branch (llvm_tune.das).
// Each bad function fails its [tune] apply with error 20800 (macro failed to apply).
options gen2
expect 20800:6

require llvm/daslib/llvm_tune

// 1. missing gen=
[tune_perm(k = 1), tune(fallback = "k1")]
def bad_no_gen(a, b : int) : int {
    return a + b
}

// 2. no [tune_perm] rows at all
[tune(gen = "llvm_code_selftest::add_plus_k")]
def bad_no_rows(a, b : int) : int {
    return a + b
}

// 3. rows listed AFTER tune(...) — applies run in declaration order, so tune sees none
[tune(gen = "llvm_code_selftest::add_plus_k"), tune_perm(k = 1)]
def bad_rows_after(a, b : int) : int {
    return a + b
}

// 4. duplicate perm suffix
[tune_perm(k = 1), tune_perm(k = 1), tune(gen = "llvm_code_selftest::add_plus_k")]
def bad_dup_suffix(a, b : int) : int {
    return a + b
}

// 5. 'reference' is reserved for the unstamped body
[tune_perm(suffix = "reference", k = 1), tune(gen = "llvm_code_selftest::add_plus_k")]
def bad_reserved_suffix(a, b : int) : int {
    return a + b
}

// 6. no explicit return type (function_to_type runs pre-infer; the registry needs it)
[tune_perm(k = 1), tune(gen = "llvm_code_selftest::add_plus_k")]
def bad_no_return_type(a, b : int) {
    return a + b
}

[export]
def main {
}
