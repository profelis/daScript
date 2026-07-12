options gen2
options indenting = 4

// Phase-2 arithmetic gate (text layer): per-scalar-class structural facts about the emitted MSL —
// every binary/unary opcode spelling, fmod for float %, all()/any() for das's scalar-bool vector
// ==/!= — plus a golden snapshot per kernel as the forward regression guard.

require dastest/testing_boost public
require _msl_common
require daslib/strings_boost

let GOLDEN_UARITH = "#include <metal_stdlib>
using namespace metal;
kernel void uarith(device const uint* a [[buffer(0)]],
        device const uint* b [[buffer(1)]],
        device uint* c [[buffer(2)]],
        device uint* d [[buffer(3)]],
        uint3 gl_GlobalInvocationID [[thread_position_in_grid]]) \{
    uint i = gl_GlobalInvocationID.x;
    uint x = a[i];
    uint y = (b[i] | 1u);
    c[i] = (((x + y) - (x * y)) + ((x / y) + (x % y)));
    d[i] = (((x & y) | (x ^ y)) + ((~x) + ((x << 2u) >> 1u)));
\}
"

let GOLDEN_IARITH = "#include <metal_stdlib>
using namespace metal;
kernel void iarith(device const int* a [[buffer(0)]],
        device const int* b [[buffer(1)]],
        device int* c [[buffer(2)]],
        device int* d [[buffer(3)]],
        uint3 gl_GlobalInvocationID [[thread_position_in_grid]]) \{
    uint i = gl_GlobalInvocationID.x;
    int x = a[i];
    int y = (b[i] | 1);
    c[i] = ((((x + y) - (x * y)) + ((x / y) + (x % y))) + (-x));
    d[i] = (((x & y) | (x ^ y)) + ((~x) + ((x << 2) >> 1)));
\}
"

let GOLDEN_FARITH = "#include <metal_stdlib>
using namespace metal;
kernel void farith(device const float* a [[buffer(0)]],
        device const float* b [[buffer(1)]],
        device float* c [[buffer(2)]],
        uint3 gl_GlobalInvocationID [[thread_position_in_grid]]) \{
    uint i = gl_GlobalInvocationID.x;
    float x = a[i];
    float y = (b[i] + 1.5f);
    c[i] = (((((x + y) - (x * y)) + (x / y)) + fmod(x, y)) + (-x));
\}
"

let GOLDEN_VECARITH = "#include <metal_stdlib>
using namespace metal;
kernel void vecarith(device const float4* fa [[buffer(0)]],
        device const float4* fb [[buffer(1)]],
        device float4* fc [[buffer(2)]],
        device const int2* ia [[buffer(3)]],
        device const int2* ib [[buffer(4)]],
        device int* flags [[buffer(5)]],
        uint3 gl_GlobalInvocationID [[thread_position_in_grid]]) \{
    uint i = gl_GlobalInvocationID.x;
    float4 u = fa[i];
    float4 v = (fb[i] * 0.5f);
    fc[i] = ((((u + v) - (u * v)) + (u / v)) + ((u * 2.0f) + (-u)));
    int2 p = ia[i];
    int2 q = ib[i];
    flags[i] = (all(p == q) ? 1 : (any(((p + q) - (p * q)) != q) ? 2 : 3));
\}
"

[test]
def test_uarith_shape(t : T?) {
    t |> run("uarith: uint arithmetic + bitwise spellings") <| @(t : T?) {
        t |> success(contains(uarith_msl, "device const uint* a [[buffer(0)]]"), "read-only uint buffer")
        t |> success(contains(uarith_msl, "device uint* c [[buffer(2)]]"), "written uint buffer")
        t |> success(contains(uarith_msl, "(x + y)") && contains(uarith_msl, "(x * y)"), "add/mul")
        t |> success(contains(uarith_msl, "(x / y)") && contains(uarith_msl, "(x % y)"), "div/mod stay infix for uint")
        t |> success(contains(uarith_msl, "(x & y)") && contains(uarith_msl, "(x ^ y)"), "band/bxor")
        t |> success(contains(uarith_msl, "(b[i] | 1u)"), "bor + decimal uint literal (das prints uint as hex)")
        t |> success(contains(uarith_msl, "(~x)"), "bitwise not")
        t |> success(contains(uarith_msl, "((x << 2u) >> 1u)"), "shifts")
    }
    t |> run("uarith: golden snapshot") <| @(t : T?) {
        t |> equal(uarith_msl, GOLDEN_UARITH)
    }
}

[test]
def test_iarith_shape(t : T?) {
    t |> run("iarith: int arithmetic + unary negate") <| @(t : T?) {
        t |> success(contains(iarith_msl, "device const int* a [[buffer(0)]]"), "read-only int buffer")
        t |> success(contains(iarith_msl, "(x % y)"), "int % stays infix (C-truncated on both sides)")
        t |> success(contains(iarith_msl, "(-x)"), "unary negate")
        t |> success(contains(iarith_msl, "((x << 2) >> 1)"), "int shifts (arithmetic >> matches das)")
    }
    t |> run("iarith: golden snapshot") <| @(t : T?) {
        t |> equal(iarith_msl, GOLDEN_IARITH)
    }
}

[test]
def test_farith_shape(t : T?) {
    t |> run("farith: float arithmetic, % lowers to fmod") <| @(t : T?) {
        t |> success(contains(farith_msl, "fmod(x, y)"), "float % -> fmod (MSL % is integral-only)")
        t |> success(contains(farith_msl, "(b[i] + 1.5f)"), "float literal keeps its fraction + f suffix")
        t |> success(contains(farith_msl, "(x / y)"), "float div")
        t |> success(contains(farith_msl, "(-x)"), "float negate")
    }
    t |> run("farith: golden snapshot") <| @(t : T?) {
        t |> equal(farith_msl, GOLDEN_FARITH)
    }
}

[test]
def test_vecarith_shape(t : T?) {
    t |> run("vecarith: componentwise vectors, broadcast, all/any compare") <| @(t : T?) {
        t |> success(contains(vecarith_msl, "device const float4* fa [[buffer(0)]]"), "float4 buffer param")
        t |> success(contains(vecarith_msl, "device const int2* ia [[buffer(3)]]"), "int2 buffer param")
        t |> success(contains(vecarith_msl, "(u + v)") && contains(vecarith_msl, "(u / v)"), "componentwise infix")
        t |> success(contains(vecarith_msl, "(u * 2.0f)") && contains(vecarith_msl, "(fb[i] * 0.5f)"), "vector * scalar broadcast")
        t |> success(contains(vecarith_msl, "(-u)"), "vector negate")
        t |> success(contains(vecarith_msl, "all(p == q)"), "das vector == is all-equal -> all()")
        t |> success(contains(vecarith_msl, "any("), "das vector != is any-differ -> any()")
        t |> success(contains(vecarith_msl, "? 1 : "), "ternary select")
    }
    t |> run("vecarith: golden snapshot") <| @(t : T?) {
        t |> equal(vecarith_msl, GOLDEN_VECARITH)
    }
}
