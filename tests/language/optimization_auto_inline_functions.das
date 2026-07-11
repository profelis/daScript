options gen2
options rtti
options no_coverage
options auto_inline_functions = true

require daslib/ast
require daslib/rtti
require daslib/ast_boost
require dastest/testing_boost public
require strings
require daslib/strings_boost

// structural FIRED proof + behavioral safety net for heuristic auto inlining of plain
// calls (src/ast/ast_inline.cpp, `options auto_inline_functions`): a call to a small
// [inline]-shaped callee splices best-effort (silent declines, never errors) when the
// body is loop-free and within the auto_inline_cost node budget, and regardless of
// budget when the callee is private and referenced exactly once (the body moves, it
// cannot grow the program). The negative tests pin the decline gates: over-budget
// bodies, loops, [never_inline], recursion, multiple references, and @@-taken callees
// all stay regular calls.

var g_log : string = ""

def side(tag : string; v : int) : int {
    g_log += tag
    return v
}

def small_mul(a, b : int) : int => a * b

def small_stmts(a : int) : int {
    var t = a + 1
    t *= 2
    return t
}

def clamped01(x : float) : float {
    // guard-return ladder: return canonicalization folds this into a single ternary
    // return at patch time, which makes it a valid heuristic splice callee
    if (x < 0.0) {
        return 0.0
    }
    if (x > 1.0) {
        return 1.0
    }
    return x
}

[never_inline]
def marked_off(a, b : int) : int => a + b

def big_pure(a : int) : int {
    // loop-free but far over the default 32-node budget: declines on cost
    var t = a
    t++
    t *= 3
    t -= 2
    t += a * a
    t *= a + 4
    t -= a * 3
    t += 11
    t *= 2
    t -= a + 9
    t += a * a * a
    t *= 5
    t -= 77
    t += a * 13
    return t
}

def loopy_sum(a : int) : int {
    // small but carries a loop: heuristic worthiness declines it
    var s = 0
    for (i in range(a)) {
        s += i
    }
    return s
}

def private big_private_once(src : array<int>) : int {
    // over budget AND loopy, but private with exactly one reference: budget-exempt,
    // the body moves into the single call site
    var s = 0
    for (v in src) {
        s += v * v
    }
    s += 100
    return s
}

def private big_private_twice(a : int) : int {
    // same size, but referenced twice: no exemption, declines on cost at both sites
    var t = a
    t++
    t *= 3
    t -= 2
    t += a * a
    t *= a + 4
    t -= a * 3
    t += 11
    t *= 2
    t -= a + 9
    t += a * a * a
    t *= 5
    t -= 77
    t += a * 13
    return t
}

def private big_private_addr(a : int) : int {
    // referenced once as a plain call, but also @@-taken: two references, no
    // exemption, and over budget - stays a regular call (and stays alive)
    var t = a
    t++
    t *= 3
    t -= 2
    t += a * a
    t *= a + 4
    t -= a * 3
    t += 11
    t *= 2
    t -= a + 9
    t += a * a * a
    t *= 5
    t -= 77
    t += a * 13
    return t
}

def recur_inc(n : int) : int => n <= 0 ? 0 : recur_inc(n - 1) + 1  // nolint:LINT010

def gadd(a, b : auto) => a + b  // generic: instances stay out of the heuristic tier

struct Node {
    v : int
}

def make_node(v : int) : Node? => new Node(v = v)

def make_node_stmts(v : int) : Node? {
    var n = new Node(v = v)
    n.v++
    return n
}

def len_plus(xs : array<int>; k : int) : int => length(xs) + k

[export]
def target_expr_body(a, b : int) : int {
    return small_mul(a, b) + small_mul(b, a + 1)
}

[export]
def target_stmt_body(a : int) : int {
    return small_stmts(a)
}

[export]
def target_canonicalized(x : float) : float {
    return clamped01(x)
}

[export]
def target_never_inline(a, b : int) : int {
    return marked_off(a, b)
}

[export]
def target_over_budget(a : int) : int {
    return big_pure(a)
}

[export]
def target_loopy(a : int) : int {
    return loopy_sum(a)
}

[export]
def target_private_once(src : array<int>) : int {
    return big_private_once(src)
}

[export]
def target_private_twice_1(a : int) : int {
    return big_private_twice(a)
}

[export]
def target_private_twice_2(a : int) : int {
    return big_private_twice(a + 1)
}

[export]
def target_private_addr(a : int) : int {
    let fp = @@big_private_addr
    return big_private_addr(a) + invoke(fp, a)
}

[export]
def target_recursive(n : int) : int {
    return recur_inc(n)
}

[export]
def target_generic(a, b : int) : int {
    return gadd(a, b)
}

[export]
def target_mixed_ternary_graft(f : bool; v : int) : int {
    // expression-body callee in a mixed-type ternary arm: the pure graft keeps
    // the ternary intact, so the per-arm null-to-pointer coercion survives
    var p = f ? make_node(v) : null
    let r = p != null ? p.v : -1
    unsafe {
        delete p
    }
    return r
}

[export]
def target_mixed_ternary_stmts(f : bool; v : int) : int {
    // STATEMENT-body callee in a mixed-type ternary arm: the lazy lowering must
    // decline - splitting the ternary into bare arm stores would lose the
    // per-arm null-to-pointer coercion
    var p = f ? make_node_stmts(v) : null
    let r = p != null ? p.v : -1
    unsafe {
        delete p
    }
    return r
}

[export]
def target_const_empty_array(k : int) : int {
    // const non-copyable rvalue argument (the empty array literal): the arg temp
    // must clone-initialize - a move from a constant is error 30940
    return len_plus([], k)
}

[export]
def target_impure_args(a, b : int) : int {
    // impure arguments must keep call-order evaluation through the splice
    return small_mul(side("a", a), side("b", b))
}

def has(s, sub : string) : bool {
    return find(s, sub, 0) >= 0
}

def body_of(t : T?; nm : string) : string {
    var body = ""
    compiling_module() |> for_each_function("{nm}") $(func) {
        if (empty(body)) {
            body = "{describe(func.body)}"
        }
    }
    t |> success(!empty(body), "target function found")
    let clean <- [for (ln in split(body, "\n")); ln; where !(ln |> has("coverage("))]
    return join(clean, "\n")
}

[test]
def test_auto_inline_functions_fired(t : T?) {
    ast_gc_guard() {
        t |> run("small expression-body callee splices at every site") @(t : T?) {
            let b = body_of(t, "target_expr_body")
            t |> success(!has(b, "small_mul("), "calls are gone: {b}")
        }
        t |> run("small statement-body callee splices") @(t : T?) {
            let b = body_of(t, "target_stmt_body")
            t |> success(!has(b, "small_stmts("), "call is gone: {b}")
        }
        t |> run("guard-return callee canonicalizes and splices") @(t : T?) {
            let b = body_of(t, "target_canonicalized")
            t |> success(!has(b, "clamped01("), "call is gone: {b}")
        }
        t |> run("private called-once callee splices regardless of budget") @(t : T?) {
            let b = body_of(t, "target_private_once")
            t |> success(!has(b, "big_private_once("), "call is gone: {b}")
        }
        t |> run("const empty-array argument splices via clone-init") @(t : T?) {
            let b = body_of(t, "target_const_empty_array")
            t |> success(!has(b, "len_plus("), "call is gone: {b}")
        }
        t |> run("expression-body callee grafts into a mixed-type ternary") @(t : T?) {
            let b = body_of(t, "target_mixed_ternary_graft")
            t |> success(!has(b, "make_node("), "call is gone: {b}")
        }
    }
}

[test]
def test_auto_inline_functions_declines(t : T?) {
    ast_gc_guard() {
        t |> run("[never_inline] callee stays a call") @(t : T?) {
            let b = body_of(t, "target_never_inline")
            t |> success(has(b, "marked_off("), "call stays regular: {b}")
        }
        t |> run("over-budget callee stays a call") @(t : T?) {
            let b = body_of(t, "target_over_budget")
            t |> success(has(b, "big_pure("), "call stays regular: {b}")
        }
        t |> run("loopy callee stays a call") @(t : T?) {
            let b = body_of(t, "target_loopy")
            t |> success(has(b, "loopy_sum("), "call stays regular: {b}")
        }
        t |> run("private called-twice callee stays a call") @(t : T?) {
            let b1 = body_of(t, "target_private_twice_1")
            let b2 = body_of(t, "target_private_twice_2")
            t |> success(has(b1, "big_private_twice("), "first site stays regular: {b1}")
            t |> success(has(b2, "big_private_twice("), "second site stays regular: {b2}")
        }
        t |> run("@@-taken private callee is not exempt") @(t : T?) {
            let b = body_of(t, "target_private_addr")
            t |> success(has(b, "big_private_addr("), "call stays regular: {b}")
        }
        t |> run("recursive callee stays a call") @(t : T?) {
            let b = body_of(t, "target_recursive")
            t |> success(has(b, "recur_inc("), "call stays regular: {b}")
        }
        t |> run("generic instance stays a call") @(t : T?) {
            let b = body_of(t, "target_generic")
            t |> success(has(b, "gadd"), "call stays regular: {b}")
        }
        t |> run("statement-body callee in a mixed-type ternary stays a call") @(t : T?) {
            let b = body_of(t, "target_mixed_ternary_stmts")
            t |> success(has(b, "make_node_stmts("), "call stays regular: {b}")
        }
    }
}

[test]
def test_auto_inline_functions_behavior(t : T?) {
    t |> run("spliced results match") @(t : T?) {
        t |> equal(target_expr_body(3, 4), 3 * 4 + 4 * 4)
        t |> equal(target_stmt_body(5), (5 + 1) * 2)
        t |> equal(target_canonicalized(-1.5), 0.0)
        t |> equal(target_canonicalized(0.25), 0.25)
        t |> equal(target_canonicalized(7.0), 1.0)
        t |> equal(target_private_once([1, 2, 3]), 1 + 4 + 9 + 100)
    }
    t |> run("declined results match") @(t : T?) {
        t |> equal(target_never_inline(2, 3), 5)
        t |> equal(target_over_budget(2), big_pure(2))
        t |> equal(target_loopy(5), 10)
        t |> equal(target_private_twice_1(1), target_private_twice_2(0))
        t |> equal(target_recursive(4), 4)
        t |> equal(target_generic(20, 22), 42)
    }
    t |> run("impure arguments evaluate in call order") @(t : T?) {
        g_log = ""
        let r = target_impure_args(6, 7)
        t |> equal(r, 42)
        t |> equal(g_log, "ab")
    }
    t |> run("mixed-type ternary results match") @(t : T?) {
        t |> equal(target_mixed_ternary_graft(true, 7), 7)
        t |> equal(target_mixed_ternary_graft(false, 7), -1)
        t |> equal(target_mixed_ternary_stmts(true, 7), 8)
        t |> equal(target_mixed_ternary_stmts(false, 7), -1)
    }
    t |> run("const empty-array argument results match") @(t : T?) {
        t |> equal(target_const_empty_array(5), 5)
    }
}
