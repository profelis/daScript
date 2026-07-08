options gen2

require smt/daslib/smt_boost
require daslib/strings_boost

[export]
def main {
    with_context() $(ctx) {
        let res = Z3_eval_smtlib2_string(ctx,
            "(declare-const x Int)(assert (> x 2))(assert (< x 10))(check-sat)(get-model)")
        z3_check_error(ctx)
        print("{res}\n")
        assert(res |> starts_with("sat"))
    }
}
