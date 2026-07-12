options gen2

require daslib/module_path
require daslib/command_line
require daslib/fio

// The dasllama scope tuner — the wrapper the policy rail (auto default / --tune / daspkg
// release) spawns. Runs BOTH halves as child daslang processes, each upserting the same
// env-pointed sidecar (DAS_TUNE_MODE/DAS_TUNE_MANIFEST inherit):
//   1. gen_tune_probe   — the [tune] generator-grid winners (q8q8 tile family)
//   2. tune_kernels     — the [tuned] loop-hint winners + the "runtime" knob snapshot
// A child failure is reported but does not abort the other half — the completeness check
// upstream names whatever ends up missing.

def private run_half(name : string) : bool {
    let cmd = "\"{get_das_exe()}\" -jit \"{path_join(get_this_module_dir(), name)}\" -dasroot \"{get_das_root()}\" 2>&1"
    // cmd.exe strips the first and last quote of a line that starts with a quote —
    // wrap in a sacrificial outer pair on windows (same trap as the daspkg popen incident)
    let full = get_platform_name() == "windows" ? "\"{cmd}\"" : cmd
    print("dasllama_tuner: {cmd}\n")
    var rc : int
    unsafe {
        rc = popen_timeout(full, 3600.0) $(f) {
            if (f == null) {
                return
            }
            while (!feof(f)) {
                print(fgets(f))
            }
        }
    }
    if (rc != 0) {
        print("dasllama_tuner: {name} FAILED (rc={rc})\n")
    }
    return rc == 0
}

[export]
def main : int {
    print("dasllama_tuner: sidecar = {get_env_variable("DAS_TUNE_MANIFEST")}\n")
    let ok1 = run_half("gen_tune_probe.das")
    let ok2 = run_half("tune_kernels.das")
    return ok1 && ok2 ? 0 : 1
}
