options gen2
options rtti

require daslib/ast
require daslib/rtti
require daslib/ast_boost
require dastest/testing_boost public
require strings

// structural FIRED proof for the ConstFolding algebraic identities: inspects the
// post-optimize AST of the target functions below and asserts the rewrite actually
// happened. the behavioral half (value preservation, purity gates) lives in
// optimization_folding.das — a silently disabled fold passes there but fails here.

[export]
def target_mul_one(x : int) : int {
    return x * 1
}

[export]
def target_add_zero(f : float) : float {
    return f + 0.0
}

[export]
def target_mul_zero(x : int) : int {
    return x * 0
}

[export]
def target_compare_flip(x : int) : bool {
    return !(x < 5)
}

[export]
def target_cast(x : int) : int {
    return int(x) // nolint:PERF020 -- deliberate: the fold under test
}

[export]
def target_not_not(b : bool) : bool {
    return !!b
}

[export]
def target_tern_bool(x : int) : bool {
    return x > 3 ? true : false
}

[export]
def target_dead_while(x : int) : int {
    var acc = x
    while (false) {
        acc ++
    }
    return acc
}

[export]
def target_dead_for(x : int) : int {
    var acc = x
    for (_i in range(3, 3)) {
        acc ++
    }
    return acc
}

[export]
def target_splat(v : float3; s : float) : float3 {
    return v * float3(s)
}

[export]
def target_div_one(f : float) : float {
    return f / 1.0
}

[export]
def target_shift_zero(u : uint) : uint {
    return u << 0u
}

[export]
def target_xor_self(u : uint) : uint {
    return u ^ u // nolint:LINT007 -- deliberate: the fold under test
}

[export]
def target_and_false(b : bool) : bool {
    return b && false
}

[export]
def target_reassoc(f : float) : float {
    return (f + 1.0) + 2.0
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
    return body
}

[test]
def test_identity_folds_fired(t : T?) {
    ast_gc_guard() {
        t |> run("x*1 leaves no multiply") @(t : T?) {
            let b = body_of(t, "target_mul_one")
            t |> success(!has(b, "*"), "no `*` survives: {b}")
            t |> success(has(b, "return x"), "operand returned directly: {b}")
        }
        t |> run("x+0.0 leaves no add") @(t : T?) {
            let b = body_of(t, "target_add_zero")
            t |> success(!has(b, "+"), "no `+` survives: {b}")
        }
        t |> run("x*0 becomes the zero constant") @(t : T?) {
            let b = body_of(t, "target_mul_zero")
            t |> success(!has(b, "*"), "no `*` survives: {b}")
            t |> success(has(b, "return 0"), "constant zero returned: {b}")
        }
        t |> run("!(a<b) becomes the flipped compare") @(t : T?) {
            let b = body_of(t, "target_compare_flip")
            t |> success(!has(b, "!"), "no `!` survives: {b}")
            t |> success(has(b, ">="), "flipped compare present: {b}")
        }
        t |> run("same-type cast is erased") @(t : T?) {
            let b = body_of(t, "target_cast")
            t |> success(!has(b, "int("), "no cast call survives: {b}")
        }
        t |> run("!!x is erased") @(t : T?) {
            let b = body_of(t, "target_not_not")
            t |> success(!has(b, "!"), "no `!` survives: {b}")
        }
        t |> run("c ? true : false becomes c") @(t : T?) {
            let b = body_of(t, "target_tern_bool")
            t |> success(!has(b, "?"), "no ternary survives: {b}")
        }
        t |> run("while(false) is removed") @(t : T?) {
            let b = body_of(t, "target_dead_while")
            t |> success(!has(b, "while"), "no while survives: {b}")
        }
        t |> run("for over const empty range is removed") @(t : T?) {
            let b = body_of(t, "target_dead_for")
            t |> success(!has(b, "for"), "no for survives: {b}")
        }
        t |> run("v*float3(s) collapses the splat") @(t : T?) {
            let b = body_of(t, "target_splat")
            t |> success(!has(b, "float3("), "no splat ctor survives: {b}")
            t |> success(has(b, "v * s"), "vec*scalar form present: {b}")
        }
        t |> run("x/1.0 leaves no divide") @(t : T?) {
            let b = body_of(t, "target_div_one")
            t |> success(!has(b, "/"), "no `/` survives: {b}")
        }
        t |> run("x<<0 leaves no shift") @(t : T?) {
            let b = body_of(t, "target_shift_zero")
            t |> success(!has(b, "<<"), "no `<<` survives: {b}")
        }
        t |> run("x^x becomes the zero constant") @(t : T?) {
            let b = body_of(t, "target_xor_self")
            t |> success(!has(b, "^"), "no `^` survives: {b}")
        }
        t |> run("x && false becomes false") @(t : T?) {
            let b = body_of(t, "target_and_false")
            t |> success(!has(b, "&&"), "no `&&` survives: {b}")
            t |> success(has(b, "return false"), "constant false returned: {b}")
        }
        t |> run("reassociation stays OFF without fast_math") @(t : T?) {
            let b = body_of(t, "target_reassoc")
            t |> success(has(b, "1f") && has(b, "2f"), "chain not regrouped: {b}")
        }
    }
}
