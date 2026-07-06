options gen2

require dastest/testing_boost
require daslib/module_path
require daslib/strings_boost
require daslib/fio
require strings

// [tune_manifest] round-trip, declaration-driven (no env): copy the client template into a
// temp directory (the declaration resolves the manifest against the declaring file's dir),
// spawn it once with "write" — the injected [init] points tune_manifest_set at
// <tempdir>/llvm_tune_manifest_probe.tune.json and it records k2 — then spawn it again: the
// fresh compile's [tune_manifest] apply re-stamps man_add from the manifest, so RESULT moves
// from the fallback k1 tier (6) to the k2 tier (7).

def private spawn_client(cmd : string; var lines : array<string>) : int {
    // cmd.exe /c strips the first and last quote of a line that starts with a quote —
    // wrap in a sacrificial outer pair on windows (same trap as the daspkg popen incident)
    let full = get_platform_name() == "windows" ? "\"{cmd}\"" : cmd
    var rc : int
    unsafe {
        rc = popen_timeout(full, 300.0) $(f) {
            if (f == null) {
                return
            }
            while (!feof(f)) {
                let ln = fgets(f)
                if (ln |> starts_with("WRITE ") || ln |> starts_with("RESULT ") || ln |> starts_with("KV ")
                        || ln |> starts_with("OTHER ") || ln |> starts_with("REF ") || ln |> starts_with("llvm_tune:")) {
                    lines |> push(strip("{ln}"))
                }
            }
        }
    }
    return rc
}

[test]
def test_llvm_tune_manifest_roundtrip(t : T?) {
    if (!jit_enabled()) {
        // the generator only fires under the LLVM JIT; the child needs -jit too
        t |> success(true)
        return
    }
    let args <- get_command_line_arguments()  // locked view — do not delete
    let bin = args[0]
    let tmpRes = create_temp_file_result("llvm_tune_manifest_", ".das")
    if (tmpRes is error) {
        t |> failure("could not create a temp file: {tmpRes as error}")
        return
    }
    let clientPath = tmpRes as value
    let tmplText = fread("{get_this_module_dir()}/llvm_tune_manifest_client.das")
    t |> success(!empty(tmplText))
    t |> success(fwrite(clientPath, tmplText))
    let manifestPath = path_join(dir_name(clientPath), "llvm_tune_manifest_probe.tune.json")

    var wlines : array<string>
    let rcw = spawn_client("\"{bin}\" -jit \"{clientPath}\" -- write", wlines)
    t |> equal(rcw, 0)
    var wrote = false
    for (ln in wlines) {
        wrote ||= ln |> starts_with("WRITE ok")
    }
    t |> success(wrote)
    t |> success(!empty(fread(manifestPath)))

    var rlines : array<string>
    let rcr = spawn_client("\"{bin}\" -jit \"{clientPath}\"", rlines)
    t |> equal(rcr, 0)
    var stamped = false
    var result7 = false
    var kv2 = false
    var other6 = false
    var ref5 = false
    for (ln in rlines) {
        stamped ||= ln |> starts_with("llvm_tune: man_add <- k2")
        result7 ||= ln == "RESULT 7"
        kv2 ||= ln == "KV 2"
        other6 ||= ln == "OTHER 6"
        ref5 ||= ln == "REF 5"
    }
    t |> success(stamped)  // the declaration's re-stamp consumed the manifest
    t |> success(result7)  // and the k2 tier actually ran
    t |> success(kv2)      // and the companion was re-stamped from the same entry
    t |> success(other6)   // no manifest entry -> the fallback stamp (k1) stands
    t |> success(ref5)     // explicit "reference" entry -> the original body despite fallback

    remove(manifestPath)
    remove(clientPath)
    delete wlines
    delete rlines
}
