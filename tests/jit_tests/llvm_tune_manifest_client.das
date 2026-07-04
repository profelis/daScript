options gen2

require llvm/daslib/llvm_tune

// Template fixture for llvm_tune_manifest.das (no [test] on purpose — the suite just
// compile-checks it in place, where the declared manifest file is absent). The test COPIES
// this file into a temp directory and spawns it there: the [tune_manifest] declaration
// resolves against the declaring file's directory, so the manifest lands in the temp dir.
// Spawned with "write" among the args it records k2 as the winner via tune_manifest_set
// (the harness write API); spawned again without, the fresh compile re-stamps man_add from
// the manifest and RESULT reports the k2 tier.

[tune_perm(k = 0), tune_perm(k = 1), tune_perm(k = 2), tune(gen = "llvm_code_selftest::add_plus_k", fallback = "k1")]
def man_add(a, b : int) : int {
    return a + b
}

[export, tune_manifest(name = "llvm_tune_manifest_probe")]
def main {
    var n = 2  // nolint:LINT003 — var defeats const-fold so the calls survive to codegen
    let args <- get_command_line_arguments()  // locked view — do not delete
    var doWrite = false
    for (a in args) {
        doWrite ||= a == "write"
    }
    if (doWrite) {
        let ok = tune_manifest_set("man_add", "k2")
        print("WRITE {ok ? "ok" : "FAILED"} -> {tune_manifest_path()}\n")
    } else {
        print("RESULT {man_add(n, 3)}\n")
    }
}
