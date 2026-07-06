options gen2
options rtti
options no_coverage

require daslib/ast
require daslib/rtti
require daslib/ast_boost
require dastest/testing_boost public
require strings
require daslib/strings_boost

// structural FIRED proof + behavioral safety net for automatic block inlining and
// invoke-of-literal devirtualization (src/ast/ast_inline.cpp): a direct call passing a
// block LITERAL argument splices the callee body (best-effort MAY contract - silent
// declines, never errors), and an invoke whose block resolves to a same-function
// literal splices the block body in place. The negative tests pin the decline gates:
// forwarded (non-literal) blocks, multi-exit callees, and recursion stay regular calls.

var g_log : string = ""

def side(tag : string; v : int) : int {
    g_log += tag
    return v
}

def for_each_val(src : array<int>; blk : block<(v : int) : void>) {
    for (v in src) {
        invoke(blk, v)
    }
}

def transform_sum(src : array<int>; blk : block<(v : int) : int>) : int {
    var total = 0
    for (v in src) {
        total += invoke(blk, v)
    }
    return total
}

def chain_sum(src : array<int>; k : int; blk : block<(v : int) : int>) : int {
    // forwards the block down: the inner call inlines through on a later wave
    return transform_sum(src, blk) + k
}

def multi_exit(src : array<int>; blk : block<(v : int) : int>) : int {
    // two returns: single-exit gate declines this callee
    if (empty(src)) {
        return -1
    }
    return invoke(blk, src[0])
}

def recursive_taker(n : int; blk : block<(v : int) : int>) : int {
    if (n <= 0) {
        return invoke(blk, 0)
    }
    return recursive_taker(n - 1, blk) + 1  // nolint:LINT010
}

[export]
def target_auto(src : array<int>) : int {
    return src |> transform_sum() $(v) => v * v
}

[export]
def target_void_auto(src : array<int>) : int {
    var sum = 0
    src |> for_each_val() $(v) {
        sum += v
    }
    return sum
}

[export]
def target_chain(src : array<int>) : int {
    return src |> chain_sum(100) $(v) => v + 1
}

[export]
def target_multi_exit(src : array<int>) : int {
    return src |> multi_exit() $(v) => v * 3
}

[export]
def target_recursive(src : array<int>) : int {
    return recursive_taker(length(src)) $(v) => v + 7
}

[export]
def target_impure_args(a, b : int) : int {
    // call-order evaluation of impure arguments must survive the splice
    return transform_sum([side("a", a), side("b", b)]) $(v) => v * 2
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
def test_auto_inline_fired(t : T?) {
    ast_gc_guard() {
        t |> run("block-literal call splices and devirtualizes") @(t : T?) {
            let b = body_of(t, "target_auto")
            t |> success(!has(b, "transform_sum("), "call is gone: {b}")
            t |> success(!has(b, "invoke("), "invoke devirtualized: {b}")
        }
        t |> run("void block-literal call splices") @(t : T?) {
            let b = body_of(t, "target_void_auto")
            t |> success(!has(b, "for_each_val("), "call is gone: {b}")
            t |> success(!has(b, "invoke("), "invoke devirtualized: {b}")
        }
        t |> run("forwarded block inlines through on later waves") @(t : T?) {
            let b = body_of(t, "target_chain")
            t |> success(!has(b, "chain_sum("), "outer call is gone: {b}")
            t |> success(!has(b, "transform_sum("), "forwarded call is gone: {b}")
            t |> success(!has(b, "invoke("), "invoke devirtualized: {b}")
        }
        t |> run("multi-exit callee declines") @(t : T?) {
            let b = body_of(t, "target_multi_exit")
            t |> success(has(b, "multi_exit("), "call stays regular: {b}")
        }
        t |> run("recursive callee declines") @(t : T?) {
            let b = body_of(t, "target_recursive")
            t |> success(has(b, "recursive_taker("), "call stays regular: {b}")
        }
    }
}

[test]
def test_auto_inline_behavior(t : T?) {
    t |> run("values preserved") @(t : T?) {
        let src <- [1, 2, 3, 4]
        t |> equal(target_auto(src), 30)
        t |> equal(target_void_auto(src), 10)
        t |> equal(target_chain(src), 114)
        t |> equal(target_multi_exit(src), 3)
        let none : array<int>
        t |> equal(target_multi_exit(none), -1)
        t |> equal(target_recursive(src), 11)
    }
    t |> run("impure arguments evaluate once in call order") @(t : T?) {
        g_log = ""
        t |> equal(target_impure_args(3, 4), 14)
        t |> equal(g_log, "ab")
    }
}
