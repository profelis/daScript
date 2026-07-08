options gen2

require daslib/fio

// Fake tuner for scope llvm_tune_scope_probe2 (no [test] on purpose) — POISONED: also
// writes an entry for scope_add, which belongs to the OTHER scope. The scope-restricted
// restamp must leave lib1's kernel on its own winner.
[export]
def main {
    let path = get_env_variable("DAS_TUNE_MANIFEST")
    print("FAKE TUNER2 -> {path}\n")
    fwrite(path, "\{\"scope_mul\":\"k0\",\"scope_add\":\"k0\"\}")
}
