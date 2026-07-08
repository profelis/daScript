options gen2

require smt/daslib/smt_expr

// ordinary generic function — instantiates with SInt and builds a formula
def chebyshev(ax, ay, bx, by) => max(abs(ax - bx), abs(ay - by))

[export]
def main {
    with_solver() $(var s) {
        let x = s |> int_const("x")
        let y = s |> int_const("y")
        s |> add(x > 2)
        s |> add(s_and(x < 10, x + y == 7))
        s |> add(chebyshev(x, y, 0, 0) <= 8)
        print("--- formula (SMT-LIB2) ---\n{s |> to_smtlib()}--------------------------\n")
        verify((s |> check()) == SmtResult.SAT)
        let xv = s |> model_int(x)
        let yv = s |> model_int(y)
        print("x = {xv}, y = {yv}\n")
        assert(xv > 2 && xv < 10 && xv + yv == 7)

        // incremental: prove there is no solution with x > 100
        s |> push()
        s |> add(x > 100)
        verify((s |> check()) == SmtResult.UNSAT)
        s |> pop()
        verify((s |> check()) == SmtResult.SAT)

        // reals and strings
        let r = s |> real_const("r")
        s |> add(r * 2.0lf == 3.0lf)
        let z = s |> string_const("z")
        s |> add(length(z) == x)
        s |> add(z |> starts_with("da"))
        verify((s |> check()) == SmtResult.SAT)
        print("r = {s |> model_real(r)}, z = \"{s |> model_string(z)}\"\n")
        s |> check_error()
    }
    print("hello_api ok\n")
}
