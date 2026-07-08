options gen2

require smt/daslib/smt_macro
require math

// The solver places spawn/enemies/loot/exit on a walled map. `valid_cell` is
// an ordinary das function lifted by [smt_fn]; `chebyshev` an ordinary generic
// — both are used symbolically (constraints) AND concretely (the render).

let WALL_X = [0, 0, 0, 23, 6, 14, 10]
let WALL_Y = [0, 11, 0, 0, 3, 5, 8]
let WALL_W = [24, 24, 1, 1, 6, 1, 4]
let WALL_H = [1, 1, 12, 12, 1, 6, 1]

[smt_fn]
def valid_cell(x, y : int) : bool {
    for (i in range(0, 7)) {
        if (x >= WALL_X[i] && x < WALL_X[i] + WALL_W[i] && y >= WALL_Y[i] && y < WALL_Y[i] + WALL_H[i]) {
            return false
        }
    }
    return x >= 0 && x < 24 && y >= 0 && y < 12
}

def chebyshev(ax, ay, bx, by) => max(abs(ax - bx), abs(ay - by))

[export]
def main {
    let names = ["S", "E", "E", "E", "L", "L", "X"]  // spawn, enemies, loot, exit
    let n = length(names)
    with_solver() $(var s) {
        let xs <- [for (i in range(n)); s |> int_const("x{i}")]
        let ys <- [for (i in range(n)); s |> int_const("y{i}")]
        s |> constrain(all_of(n) $(i) => valid_cell(xs[i], ys[i]))
        s |> constrain(all_pairs(n) $(i, j) => chebyshev(xs[i], ys[i], xs[j], ys[j]) >= 2)
        s |> constrain(all_of(3) $(e) => chebyshev(xs[e + 1], ys[e + 1], xs[0], ys[0]) >= 6)   // enemies far from spawn
        s |> constrain(all_of(2) $(l) => chebyshev(xs[l + 4], ys[l + 4], xs[0], ys[0]) <= 5)   // loot near spawn
        s |> constrain(chebyshev(xs[6], ys[6], xs[0], ys[0]) >= 14)                                // exit far away
        print("--- formula (SMT-LIB2) ---\n{s |> to_smtlib()}--------------------------\n")
        verify((s |> check()) == SmtResult.SAT)

        let px <- [for (x in xs); s |> model_int(x)]
        let py <- [for (y in ys); s |> model_int(y)]
        for (i in range(n)) {
            verify(valid_cell(px[i], py[i]))   // same function, now concrete
        }
        for (r in range(12)) {
            var line = ""
            for (c in range(24)) {
                var ch = valid_cell(c, r) ? "." : "#"
                for (i in range(n)) {
                    if (px[i] == c && py[i] == r) {
                        ch = names[i]
                    }
                }
                line += ch
            }
            print("{line}\n")
        }
    }
}
