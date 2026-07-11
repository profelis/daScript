options gen2
options indenting = 4

// Shared gates for the dasGlsl test suite. validate_glsl shells the emitted shader text out to
// glslang (the reference GLSL front-end — the real syntax/extension oracle the substring pins
// can't provide); it soft-skips when the tool is absent locally and CI enforces presence.
// Mirrors tests/spirv/_spirv_common.das validate_spirv (discovery, temp file, soft-skip shape).

module _glsl_common shared public

require daslib/fio
require strings

def public has(hay, needle : string) : bool {
    return find(hay, needle) >= 0
}

struct GlslValResult {
    ran : bool      // false => tool not found (soft-skip locally; CI provides it)
    ok  : bool
    msg : string
}

def private tool_runs(exe : string) : bool {
    var out : string
    return run_and_capture([exe, "--version"], out, 10.0) == 0
}

def private find_glslang : string {
    var cands : array<string>
    if (has_env_variable("VULKAN_SDK")) {
        let sdk = get_env_variable("VULKAN_SDK")
        cands |> push("{sdk}/Bin/glslangValidator")     // Windows SDK layout
        cands |> push("{sdk}/Bin/glslangValidator.exe")
        cands |> push("{sdk}/bin/glslangValidator")     // Linux SDK layout
    }
    cands |> push("glslangValidator")                   // PATH (CI)
    cands |> push("glslangValidator.exe")
    var found = ""
    for (p in cands) {
        if (tool_runs(p)) {
            found = p
            break
        }
    }
    delete cands
    return found
}

// stage_ext: "frag" | "vert" | "comp" — glslang reads the stage off the file extension.
// Desktop-GL mode (no -V): validates against the #version/#extension lines in the text.
def public validate_glsl(text : string; stage_ext : string) : GlslValResult {
    let exe = find_glslang()
    if (empty(exe)) return GlslValResult(ran = false, ok = false, msg = "glslangValidator not found")
    let tf = create_temp_file_result("das_glsl", ".{stage_ext}")
    if (tf is error) return GlslValResult(ran = true, ok = false, msg = "temp file: {tf as error}")
    let path = tf as value
    var wrote = false
    fopen(path, "wb") $(f) {
        if (f != null) {
            fwrite(f, text)
            wrote = true
        }
    }
    if (!wrote) {
        remove_result(path)
        return GlslValResult(ran = true, ok = false, msg = "write failed: {path}")
    }
    var out : string
    let rc = run_and_capture([exe, path], out, 30.0)
    remove_result(path)
    return GlslValResult(ran = true, ok = rc == 0, msg = out)
}
