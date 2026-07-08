options gen2

require dastest/testing_boost
require daslib/module_path
require daslib/strings_boost
require daslib/fio
require strings

// [tune_scope]/[tune_policy]/--tune/tune_status round-trip through child daslang processes
// (the policy rail is compile-time). Two libraries each ship a scope + tuner; the second
// tuner is poisoned with an entry for the first library's kernel, which the
// scope-restricted restamp must ignore. The scope manifests live at
// <das_root>/llvm_tune_scope_probe{,2}.tune.json — that per-box location IS the feature
// under test — created and removed here. Children mostly run interp (stamp prints and
// STATUS lines are mode-independent); only the auto flow runs -jit to prove the restamped
// tier executes (RESULT 7 = 2+3+k2).

def private tune_env(policy : string) : string {
    return (get_platform_name() == "windows" ?
        "set DAS_TUNE_MODE=&& set DAS_TUNE_MANIFEST=&& set DAS_TUNE_POLICY={policy}&& " :
        "DAS_TUNE_MODE= DAS_TUNE_MANIFEST= DAS_TUNE_POLICY={policy} ")
}

// env prefix leads, so no sacrificial-quote wrap is needed (cmd.exe only strips a LEADING quote)
def private spawn_child(cmd : string; var lines : array<string>) : int {
    var rc : int
    unsafe {
        rc = popen_timeout("{cmd} 2>&1", 300.0) $(f) {
            if (f == null) {
                return
            }
            while (!feof(f)) {
                let ln = strip(fgets(f))
                if (!empty(ln)) {
                    lines |> push("{ln}")
                }
            }
        }
    }
    return rc
}

def private has(lines : array<string>; needle : string) : bool {
    for (ln in lines) {
        if (find(ln, needle) >= 0) return true
    }
    return false
}

[test]
def test_llvm_tune_scope_policy(t : T?) {
    if (!jit_enabled()) {
        // the auto flow's RESULT fingerprint needs the generator tier; children need -jit too
        t |> success(true)
        return
    }
    let args <- get_command_line_arguments()  // locked view — do not delete
    let bin = args[0]
    let client = "{get_this_module_dir()}/llvm_tune_scope_client.das"
    let manifest1 = path_join(get_das_root(), "llvm_tune_scope_probe.tune.json")
    let manifest2 = path_join(get_das_root(), "llvm_tune_scope_probe2.tune.json")
    remove(manifest1)
    remove(manifest2)

    // 1. policy=fallback (the annotation default), no manifests: fallback stamps, quiet
    var l1 : array<string>
    t |> equal(spawn_child("{tune_env("")}\"{bin}\" \"{client}\"", l1), 0)
    t |> success(l1 |> has("scope_add <- k1 (fallback)"))
    t |> success(l1 |> has("scope_mul <- k2 (fallback)"))
    t |> success(l1 |> has("STATUS scope_add|llvm_tune_scope_probe|k1|fallback"))
    t |> success(l1 |> has("STATUS scope_mul|llvm_tune_scope_probe2|k2|fallback"))
    t |> success(l1 |> has("RESULT 5"))   // interp = reference body regardless of stamp

    // 2. policy=error: the compile must fail, naming the untuned scope + the tuner command
    var l2 : array<string>
    t |> success(spawn_child("{tune_env("error")}\"{bin}\" \"{client}\"", l2) != 0)
    t |> success(l2 |> has("untuned"))

    // 3. policy=auto (-jit): both tuners run mid-compile, each scope restamps from its own
    //    manifest, the poison entry does NOT cross-stamp, and the k2 tier actually executes
    var l3 : array<string>
    t |> equal(spawn_child("{tune_env("auto")}\"{bin}\" -jit \"{client}\"", l3), 0)
    t |> success(l3 |> has("FAKE TUNER ->"))
    t |> success(l3 |> has("FAKE TUNER2 ->"))
    t |> success(l3 |> has("scope_add <- k2 ("))
    t |> success(l3 |> has("scope_mul <- k0 ("))
    t |> success(!(l3 |> has("scope_add <- k0")))   // the poison stays in its own scope
    t |> success(l3 |> has("RESULT 7"))             // 2+3+k2 — the restamped tier ran
    t |> success(l3 |> has("RESULT2 5"))            // 2+3+k0 — its own scope's winner
    t |> success(l3 |> has("STATUS scope_add|llvm_tune_scope_probe|k2|manifest"))
    t |> success(l3 |> has("STATUS scope_mul|llvm_tune_scope_probe2|k0|manifest"))
    t |> success(!empty(fread(manifest1)))
    t |> success(!empty(fread(manifest2)))

    // 4. plain start with manifests present: [tune]-time scope resolution, no policy activity
    var l4 : array<string>
    t |> equal(spawn_child("{tune_env("")}\"{bin}\" \"{client}\"", l4), 0)
    t |> success(l4 |> has("scope_add <- k2 ("))
    t |> success(l4 |> has("scope_mul <- k0 ("))
    t |> success(!(l4 |> has("FAKE TUNER")))

    // 5. --tune forces a re-tune even though the manifests exist
    var l5 : array<string>
    t |> equal(spawn_child("{tune_env("")}\"{bin}\" \"{client}\" -- --tune", l5), 0)
    t |> success(l5 |> has("FAKE TUNER ->"))
    t |> success(l5 |> has("FAKE TUNER2 ->"))

    // 6. policy=restart: each start tunes one missing scope via the main-guard and asks for
    //    a restart (no RESULT); with both tuned, main runs
    remove(manifest1)
    remove(manifest2)
    var l6a : array<string>
    t |> equal(spawn_child("{tune_env("restart")}\"{bin}\" \"{client}\"", l6a), 0)
    t |> success(l6a |> has("restart to apply the winners"))
    t |> success(!(l6a |> has("RESULT")))
    var l6b : array<string>
    t |> equal(spawn_child("{tune_env("restart")}\"{bin}\" \"{client}\"", l6b), 0)
    t |> success(l6b |> has("restart to apply the winners"))
    t |> success(!(l6b |> has("RESULT")))
    var l6c : array<string>
    t |> equal(spawn_child("{tune_env("restart")}\"{bin}\" \"{client}\"", l6c), 0)
    t |> success(l6c |> has("RESULT 5"))

    // 7. AOT gate: policy=error + missing manifests must stay COMPLETELY silent
    remove(manifest1)
    remove(manifest2)
    let outRes = create_temp_file_result("llvm_tune_scope_aot_", ".cpp")
    if (outRes is error) {
        t |> failure("could not create a temp file: {outRes as error}")
        return
    }
    let aotOut = outRes as value
    var l7 : array<string>
    t |> equal(spawn_child("{tune_env("error")}\"{bin}\" -aot \"{client}\" \"{aotOut}\"", l7), 0)
    t |> success(!(l7 |> has("llvm_tune:")))
    t |> success(!(l7 |> has("untuned")))

    // 8. -exe gate: stamping runs (fallback, no manifests) but the policy rail is dead
    var l8 : array<string>
    t |> equal(spawn_child("{tune_env("error")}\"{bin}\" -jit -exe \"{client}\"", l8), 0)
    t |> success(l8 |> has("scope_add <- k1 (fallback)"))
    t |> success(!(l8 |> has("untuned")))

    remove(manifest1)
    remove(manifest2)
    remove(aotOut)
    delete l1
    delete l2
    delete l3
    delete l4
    delete l5
    delete l6a
    delete l6b
    delete l6c
    delete l7
    delete l8
}
