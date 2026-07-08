options gen2
options no_aot

require daslib/ast
require daslib/fio
require strings

// [smt_fn] can only unroll a `for` over a LITERAL range. A loop whose bound is
// a runtime/symbolic value cannot be unrolled, so the macro must reject it at
// compile time rather than silently misbehave. This test compiles such a
// function — written to an OS temp file, so no deliberately-broken .das lives
// in the tree — and asserts the diagnostic fires.

let bad_src = "options gen2\nrequire smt/daslib/smt_macro\n[smt_fn]\ndef loop_bad(n : int) : bool \{\n var acc = 0\n for (i in range(n)) \{ acc = acc + i \}\n return acc == n\n\}\n"

[export]
def main {
    let tf = create_temp_file_result("smt_fn_forloop", ".das")
    if (tf is error) {
        panic("cannot create temp fixture: {tf as error}")
    }
    let path = tf as value
    if (!fwrite(path, bad_src)) {
        panic("cannot write temp fixture")
    }
    var compiled = true
    var diagnostic = ""
    var inscope access <- make_file_access("")
    using() $(var mg : ModuleGroup) {
        using() $(var cop : CodeOfPolicies) {
            compile_file(path, access, unsafe(addr(mg)), cop) $(ok; _program; issues) {
                compiled = ok
                diagnostic = "{issues}"
            }
        }
    }
    remove(path)
    verify(!compiled, "[smt_fn] must reject a non-literal-range for loop")
    verify(diagnostic |> find("for loop must iterate") >= 0, "rejection must cite the literal-range for-loop diagnostic")
    print("smt_fn_errors ok\n")
}
