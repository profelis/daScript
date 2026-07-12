options gen2
options indenting = 4

// Text-assertion units for the Phase-1 a*b kernel: structural facts about the emitted MSL
// (signature shape, per-binding attributes, write-set const-ness, builtin param, statement forms),
// the companion globals, and the golden snapshot of our own emitted text — the forward regression
// guard (any emitter change that reshapes output must consciously update the golden).

require dastest/testing_boost public
require _msl_common
require daslib/strings_boost

let GOLDEN_MUL_AB = "#include <metal_stdlib>
using namespace metal;
kernel void mul_ab(device const float* a [[buffer(0)]],
        device const float* b [[buffer(1)]],
        device float* c [[buffer(2)]],
        uint3 gl_GlobalInvocationID [[thread_position_in_grid]]) \{
    uint i = gl_GlobalInvocationID.x;
    c[i] = (a[i] * b[i]);
\}
"

[test]
def test_mul_ab_shape(t : T?) {
    t |> run("mul_ab: kernel signature") <| @(t : T?) {
        t |> success(contains(mul_ab_msl, "#include <metal_stdlib>"), "preamble include")
        t |> success(contains(mul_ab_msl, "using namespace metal;"), "preamble namespace")
        t |> success(contains(mul_ab_msl, "kernel void mul_ab("), "kernel qualifier + entry name")
        t |> success(contains(mul_ab_msl, "device const float* a [[buffer(0)]]"), "a: read-only -> device const, binding 0")
        t |> success(contains(mul_ab_msl, "device const float* b [[buffer(1)]]"), "b: read-only -> device const, binding 1")
        t |> success(contains(mul_ab_msl, "device float* c [[buffer(2)]]"), "c: written -> device (mutable), binding 2")
        t |> success(contains(mul_ab_msl, "uint3 gl_GlobalInvocationID [[thread_position_in_grid]]"), "builtin param synthesized")
    }
    t |> run("mul_ab: body statements") <| @(t : T?) {
        t |> success(contains(mul_ab_msl, "uint i = gl_GlobalInvocationID.x;"), "value let lowers to typed local")
        t |> success(contains(mul_ab_msl, "c[i] = (a[i] * b[i]);"), "assignment through pointer index")
    }
    t |> run("mul_ab: companion globals") <| @(t : T?) {
        t |> equal(mul_ab_msl_entry, "mul_ab")
        t |> success(mul_ab_msl_fastmath, "fastmath defaults ON ([metal_kernel] property)")
        t |> success(!empty(mul_ab_msl_census), "census companion is filled")
    }
}

[test]
def test_mul_ab_golden(t : T?) {
    t |> run("mul_ab: golden snapshot") <| @(t : T?) {
        t |> equal(mul_ab_msl, GOLDEN_MUL_AB)
    }
}
