options gen2

require smt/daslib/smt_boost
require daslib/safe_addr
require strings

// solve `x > 2 && x < 10` over the integers, read x back from the model
[export]
def main {
    with_context() $(ctx) {
        print("z3 version: {z3_version()}\n")
        let x = z3_int_const(ctx, "x")
        var conj_args = [
            Z3_mk_gt(ctx, x, z3_int(ctx, 2)),
            Z3_mk_lt(ctx, x, z3_int(ctx, 10))
        ]
        let conj = Z3_mk_and(ctx, conj_args)
        with_solver(ctx) $(s) {
            Z3_solver_assert(ctx, s, conj)
            let r = Z3_solver_check(ctx, s)
            assert(r == Z3_lbool.Z3_L_TRUE)
            with_model(ctx, s) $(m) {
                var val : Z3_ast
                Z3_model_eval(ctx, m, x, true, safe_addr(val))
                let v = to_int(Z3_get_numeral_string(ctx, val))
                print("x = {v}\n")
                assert(v > 2 && v < 10)
            }
        }
        z3_check_error(ctx)
    }
}
