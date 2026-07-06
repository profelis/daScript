options gen2
options rtti
options no_coverage

require daslib/ast
require daslib/rtti
require daslib/ast_boost
require dastest/testing_boost public
require strings
require daslib/strings_boost

// structural FIRED proof + behavioral safety net for [inline] splicing
// (src/ast/ast_inline.cpp): every direct call to an [inline] function is replaced
// with the callee body during the patch slot. leaf and pure-single-use arguments
// substitute textually; impure arguments bind call-site temps in call order; `var`
// by-value params become mutable local copies; while / elif / && / ?: positions
// lower first. the behavioral tests pin evaluation order and snapshot semantics.

var g_log : string = ""
var g_count = 0

def side(tag : string; v : int) : int {
    g_log += tag;
    return v;
}

struct SVec {
    x : int;
    y : int;
}

[inline]
def add(a, b : int) : int {
    return a + b;
}

[inline]
def clamp01f(x : float) : float {
    return x < 0.0 ? 0.0 : (x > 1.0 ? 1.0 : x); // nolint:PERF015 -- ternaries in the inline body are the point
}

[inline]
def madd(a, b, c : int) : int {
    let t = a * b;
    return t + c;
}

[inline]
def bump(var x : int) : int {
    x++;
    return x;
}

[inline]
def add_g(a : int) : int {
    g_count += 10;
    return a + g_count;
}

[inline]
def vsum(v : SVec) : int {
    return v.x + v.y;
}

[inline]
def wsum(var v : SVec) : int {
    v.x++;
    return v.x + v.y;
}

[inline]
def read_after_write(a : int; var s : SVec) : int {
    s.x = 100;
    return a;
}

[inline]
def set_y(var s : SVec) {
    s.y = 99;
}

[inline]
def sum_range(n : int) : int {
    var s = 0;
    for (k in range(n)) {
        s += k;
    }
    return s;
}

[inline]
def chain_inner(x : int) : int {
    return x + 1;
}

[inline]
def chain_outer(x : int) : int {
    return chain_inner(x) + 2;
}

[inline]
def twice(x : auto) {
    return x + x;
}

[export]
def target_basic(x, y : int) : int {
    return add(x, y + 1); // inlines to x + (y + 1), zero temps
}

[export]
def target_fold : float {
    return clamp01f(2.5); // constant arg: folds through the inlined body
}

[export]
def target_multi_stmt(x : int) : int {
    return madd(x, 4, 5);
}

[export]
def target_generic(x : int; f : float) : float {
    return float(twice(x)) + twice(f); // one instance per type, both inlined
}

[export]
def target_while(x : int) : int {
    var i = 0;
    while (madd(i, 1, 0) < x) { // statement-needing callee in a while cond: lowered
        i++;
    }
    return i;
}

[export]
def target_lazy(q : int) : int {
    let c = (q > 0) && (madd(q, 1, 1) > 0); // && right side: lowered to if-form
    let s = q > 0 ? madd(q, 1, 0) : madd(q, 2, 0); // ?: arms: lowered to if-form
    return (c ? 1 : 0) + s;
}

def has(s, sub : string) : bool {
    return find(s, sub, 0) >= 0;
}

def count_of(s, sub : string) : int {
    return length(split(s, sub)) - 1;
}

def body_of(t : T?; nm : string) : string {
    var body = "";
    compiling_module() |> for_each_function("{nm}") $(func) {
        if (empty(body)) {
            body = "{describe(func.body)}";
        }
    }
    t |> success(!empty(body), "target function found");
    return body;
}

[test]
def test_inline_fired(t : T?) {
    ast_gc_guard() {
        t |> run("expression body with leaf + pure args grafts in place") @(t : T?) {
            let b = body_of(t, "target_basic");
            t |> equal(count_of(b, "add("), 0);
            t |> success(!has(b, "__inl"), "no temps for leaf and pure single-use args: {b}");
        }
        t |> run("constant arg folds through the inlined body") @(t : T?) {
            let b = body_of(t, "target_fold");
            t |> equal(count_of(b, "clamp01f("), 0);
        }
        t |> run("multi-statement body splices") @(t : T?) {
            let b = body_of(t, "target_multi_stmt");
            t |> equal(count_of(b, "madd("), 0);
        }
        t |> run("generic instances inline per instantiation") @(t : T?) {
            let b = body_of(t, "target_generic");
            t |> equal(count_of(b, "twice("), 0);
        }
        t |> run("while condition lowers, call inlines inside the loop") @(t : T?) {
            let b = body_of(t, "target_while");
            t |> equal(count_of(b, "madd("), 0);
        }
        t |> run("lazy operators lower, calls inline in the branches") @(t : T?) {
            let b = body_of(t, "target_lazy");
            t |> equal(count_of(b, "madd("), 0);
        }
    }
}

[test]
def test_inline_behavior(t : T?) {
    t |> run("values preserved") @(t : T?) {
        t |> equal(target_basic(5, 6), 12);
        t |> equal(target_fold(), 1.0);
        t |> equal(target_multi_stmt(3), 17);
        t |> equal(target_generic(21, 1.5), 45.0);
        t |> equal(target_while(5), 5);
        t |> equal(target_lazy(41), 42);
    }
    t |> run("impure args evaluate once, in call order") @(t : T?) {
        g_log = "";
        let r = add(side("a", 1), side("b", 2));
        t |> equal(r, 3);
        t |> equal(g_log, "ab");
    }
    t |> run("impure prefix stays ahead of arg temps") @(t : T?) {
        g_log = "";
        let r = side("p", 10) + add(side("q", 1), side("r", 2));
        t |> equal(r, 13);
        t |> equal(g_log, "pqr");
    }
    t |> run("var by-value param is a private mutable copy") @(t : T?) {
        var q = 41; // nolint:LINT003 -- mutable on purpose: prove the callee's copy never writes back
        t |> equal(bump(q), 42);
        t |> equal(q, 41);
    }
    t |> run("global arg keeps snapshot semantics against global writes") @(t : T?) {
        g_count = 0;
        t |> equal(add_g(g_count), 10);
    }
    t |> run("struct by-ref params alias like the call did") @(t : T?) {
        var v = SVec(x = 3, y = 4);
        t |> equal(vsum(v), 7);
        t |> equal(wsum(v), 8);
        t |> equal(v.x, 4);
    }
    t |> run("pure memory-reading arg binds a temp when the body writes it") @(t : T?) {
        var v = SVec(x = 7, y = 0);
        t |> equal(read_after_write(v.x, v), 7);
        t |> equal(v.x, 100);
    }
    t |> run("void inline as a statement") @(t : T?) {
        var v = SVec(x = 1, y = 2);
        set_y(v);
        t |> equal(v.y, 99);
    }
    t |> run("callee locals and loop vars rename around caller names") @(t : T?) {
        let s = 1000;
        let k = 2000;
        t |> equal(sum_range(4), 6);
        t |> equal(s, 1000);
        t |> equal(k, 2000);
    }
    t |> run("nested calls and inline chains") @(t : T?) {
        t |> equal(add(add(1, 2), add(3, 4)), 10);
        t |> equal(chain_outer(5), 8);
    }
    t |> run("statement-needing callee in if and elif conditions") @(t : T?) {
        var hits = 0;
        if (madd(1, 2, 3) == 5) {
            hits += 1;
        }
        if (false) {
            hits += 100;
        } elif (madd(1, 1, 1) == 2) {
            hits += 1;
        }
        t |> equal(hits, 2);
    }
    t |> run("statement-needing callee in a for source") @(t : T?) {
        var total = 0;
        for (z in range(0, madd(1, 2, 1))) {
            total += z;
        }
        t |> equal(total, 3);
    }
    t |> run("user let keeps its metadata through lazy lowering") @(t : T?) {
        // the ?: lowering must hoist to a generated temp, not rewrite the user
        // declaration in place - an in-place rewrite would drop the aka
        let qq = 41;
        let picked aka chosen = qq > 0 ? madd(qq, 1, 0) : madd(qq, 2, 0);
        t |> equal(chosen, 41);
        t |> equal(picked, 41);
    }
}
