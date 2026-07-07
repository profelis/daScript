options gen2

require daslib/fio

// Instant fake tuner for llvm_tune_scope.das (no [test] on purpose): records k2 for
// scope_add into the manifest the framework points it at via DAS_TUNE_MANIFEST.
[export]
def main {
    let path = get_env_variable("DAS_TUNE_MANIFEST")
    print("FAKE TUNER -> {path}\n")
    fwrite(path, "\{\"scope_add\":\"k2\"\}")
}
