options gen2
options rtti

require daslib/ast
require daslib/rtti
require daslib/ast_boost
require dastest/testing_boost public
require strings
require daslib/strings_boost

// structural FIRED proof + behavioral safety net for the dead-store-elimination pass
// (src/ast/ast_dse.cpp): a store to a plain local is removed when nothing reads it
// before the next full overwrite AND the rhs is pure. The behavioral tests pin the
// safety gates: impure rhs kept, aliased/by-ref/op-assign locals untouched, functions
// with finally skipped whole.

var g_count = 0
var g_obs = 0

def bump() : int {
    g_count ++
    return g_count
}

def call_it(blk : block) {
    invoke(blk)
}

[export]
def target_overwrite(x : int) : int {
    var t = 0 // nolint:LINT010 -- deliberate dead init
    t = x * 5 // nolint:LINT010 -- dead: overwritten below before any read
    t = x + 7
    return t
}

[export]
def target_trailing(x : int) : int {
    var t = x + 1
    let r = t * 2
    t = x * 9 // nolint:LINT010 -- dead: t never read again
    return r
}

[export]
def target_branch_dead(x : int; c : bool) : int {
    var t = 0 // nolint:LINT010 -- deliberate dead init
    t = x * 11 // dead: overwritten on both arms before any read
    if (c) {
        t = x + 1
    } else {
        t = x + 2
    }
    return t
}

[export]
def target_branch_live(x : int; c : bool) : int {
    var t = 0 // nolint:LINT010 -- deliberate dead init
    t = x + 3 // LIVE: read on the then-path
    if (c) {
        return t
    }
    return x
}

[export]
def target_loop_live(x : int) : int {
    var acc = 0
    var i = 0
    while (i < x) {
        acc = acc + i // LIVE: read next iteration and after the loop
        i = i + 1     // LIVE: read by the condition
    }
    return acc
}

[export]
def target_chain(x : int) : int {
    var a = 0 // nolint:LINT010 -- deliberate dead init
    var b = 0 // nolint:LINT010 -- deliberate dead init
    a = x + 13 // nolint:LINT010 -- dead: only read by the dead store below
    b = a * 2 // nolint:LINT010 -- dead: b never read
    return x
}

[export]
def target_impure(x : int) : int {
    var t = 0
    t = bump() // target is dead but the rhs has side effects — statement must stay
    return x
}

[export]
def target_alias(x : int) : int {
    var t = 0
    t = x + 5
    var p = unsafe(addr(t))
    t = x * 6 // looks dead by direct uses, but p aliases t — addr() disqualifies t
    return *p
}

[export]
def target_string() : string {
    var s = "" // nolint:LINT010 -- deliberate dead init
    s = "deadbeef" // nolint:LINT010 -- dead: overwritten before any read
    s = "live"
    return s
}

[export]
def target_ptr(a, b : int const?) : int const? {
    var p : int const?
    p = a // nolint:LINT010,STYLE011 -- dead: overwritten before any read; decl-then-assign is the shape under test
    p = b
    return p
}

[export]
def target_capture(x : int) : int {
    var t = 0 // nolint:LINT010 -- deliberate dead init
    var r = 0
    t = x + 40 // LIVE: read inside the block below
    call_it() $ {
        r = t + 2
    }
    return r
}

[export]
def target_finally(x : int) : int {
    var t = 0 // nolint:LINT010 -- deliberate dead init
    {
        t = x + 21 // LIVE: the finally reads it on the early-return path the CFG does not model
        return x
    } finally {
        g_obs = t
    }
    return 0
}

[export]
def target_opassign(x : int) : int {
    var t = x
    t += 1 // nolint:PERF013 -- op-assign disqualifies t; the `+=` shape is the point
    return x
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
    // the coverage lane (dastest --cov-path) injects add_func_coverage/add_line_coverage
    // statements whose arguments collide with the substrings asserted here — drop them
    let clean <- [for (ln in split(body, "\n")); ln; where !(ln |> has("coverage("))]
    return join(clean, "\n")
}

[test]
def test_dead_stores_fired(t : T?) {
    ast_gc_guard() {
        t |> run("overwritten store is removed") @(t : T?) {
            let b = body_of(t, "target_overwrite")
            t |> success(!has(b, "* 5"), "dead store gone: {b}")
            t |> success(has(b, "+ 7"), "live store kept: {b}")
        }
        t |> run("store after the last read is removed") @(t : T?) {
            let b = body_of(t, "target_trailing")
            t |> success(!has(b, "* 9"), "trailing dead store gone: {b}")
            t |> success(has(b, "* 2"), "live read kept: {b}")
        }
        t |> run("store killed on both branch arms is removed") @(t : T?) {
            let b = body_of(t, "target_branch_dead")
            t |> success(!has(b, "* 11"), "pre-branch dead store gone: {b}")
            t |> success(has(b, "+ 1") && has(b, "+ 2"), "arm stores kept: {b}")
        }
        t |> run("store live on one path only is kept") @(t : T?) {
            let b = body_of(t, "target_branch_live")
            t |> success(has(b, "+ 3"), "partially-live store kept: {b}")
        }
        t |> run("loop-carried stores are kept") @(t : T?) {
            let b = body_of(t, "target_loop_live")
            t |> success(has(b, "+ i"), "accumulator kept: {b}")
            t |> success(has(b, "+ 1"), "counter kept: {b}")
        }
        t |> run("dead-store chain falls in one pass") @(t : T?) {
            let b = body_of(t, "target_chain")
            t |> success(!has(b, "+ 13") && !has(b, "* 2"), "whole chain gone: {b}")
        }
        t |> run("impure rhs keeps the statement") @(t : T?) {
            let b = body_of(t, "target_impure")
            t |> success(has(b, "bump"), "side-effecting store kept: {b}")
        }
        t |> run("addr() disqualifies the variable") @(t : T?) {
            let b = body_of(t, "target_alias")
            t |> success(has(b, "* 6"), "aliased store kept: {b}")
        }
        t |> run("dead string store is removed") @(t : T?) {
            let b = body_of(t, "target_string")
            t |> success(!has(b, "deadbeef"), "dead string store gone: {b}")
            t |> success(has(b, "live"), "live string store kept: {b}")
        }
        t |> run("dead pointer store is removed") @(t : T?) {
            let b = body_of(t, "target_ptr")
            t |> success(!has(b, "p = a"), "dead pointer store gone: {b}")
            t |> success(has(b, "p = b"), "live pointer store kept: {b}")
        }
        t |> run("store read inside a block capture is kept") @(t : T?) {
            let b = body_of(t, "target_capture")
            t |> success(has(b, "+ 40"), "block-read store kept: {b}")
        }
        t |> run("function with finally is skipped whole") @(t : T?) {
            let b = body_of(t, "target_finally")
            t |> success(has(b, "+ 21"), "store read by finally kept: {b}")
        }
        t |> run("op-assign disqualifies the variable") @(t : T?) {
            let b = body_of(t, "target_opassign")
            t |> success(has(b, "+="), "op-assign statement kept: {b}")
        }
    }
}

[test]
def test_dead_stores_behavior(t : T?) {
    t |> run("values preserved") @(t : T?) {
        t |> equal(target_overwrite(3), 10)
        t |> equal(target_trailing(4), 10)
        t |> equal(target_branch_dead(5, true), 6)
        t |> equal(target_branch_dead(5, false), 7)
        t |> equal(target_branch_live(2, true), 5)
        t |> equal(target_branch_live(2, false), 2)
        t |> equal(target_loop_live(4), 6)
        t |> equal(target_chain(15), 15)
        t |> equal(target_string(), "live")
        t |> equal(target_capture(1), 43)
        t |> equal(target_opassign(5), 5)
    }
    t |> run("side effects of a dead target's rhs still happen") @(t : T?) {
        g_count = 0
        t |> equal(target_impure(1), 1)
        t |> equal(g_count, 1)
        t |> equal(target_impure(2), 2)
        t |> equal(g_count, 2)
    }
    t |> run("aliased store still lands") @(t : T?) {
        t |> equal(target_alias(7), 42)
    }
    t |> run("finally observes the store on the early-return path") @(t : T?) {
        g_obs = 0
        t |> equal(target_finally(9), 9)
        t |> equal(g_obs, 30)
    }
    t |> run("pointer store chain") @(t : T?) {
        var va = 1
        var vb = 2
        let res = target_ptr(unsafe(addr(va)), unsafe(addr(vb)))
        t |> equal(*res, 2)
    }
}
