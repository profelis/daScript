options gen2
options indenting = 4

// Phase-2 loop gate (text layer): the @uniform scalar -> constant-address-space reference param,
// the non-exact-grid bounds guard (early return), while + break/continue, constant range-for, and
// the dynamic-end range-for hoist — das evaluates range endpoints ONCE, so a non-constant end
// lands in a loop-scoped `<i>_end` local (comma-declared: sequential same-name loops can't collide).

require dastest/testing_boost public
require _msl_common
require daslib/strings_boost

let GOLDEN_LOOPS = "#include <metal_stdlib>
using namespace metal;
kernel void loops(device const int* src [[buffer(0)]],
        device int* dst [[buffer(1)]],
        constant uint& n [[buffer(2)]],
        device uint* udst [[buffer(3)]],
        uint3 gl_GlobalInvocationID [[thread_position_in_grid]]) \{
    uint i = gl_GlobalInvocationID.x;
    if ((i >= n)) \{
        return;
    \}
    int s = 0;
    int j = 0;
    while ((j < 100)) \{
        ++j;
        if ((j == 3)) \{
            continue;
        \}
        if ((j >= 7)) \{
            break;
        \}
        s += j;
    \}
    for (int k = 0; k < 4; ++k) \{
        s += (k * src[i]);
    \}
    for (int _k = 0, _k_end = s; _k < _k_end; ++_k) \{
        ++s;
    \}
    dst[i] = s;
    uint usum = 0u;
    for (uint ku = 0u, ku_end = n; ku < ku_end; ++ku) \{
        usum += ku;
    \}
    udst[i] = usum;
\}
"

[test]
def test_loops_shape(t : T?) {
    t |> run("loops: @uniform scalar param") <| @(t : T?) {
        t |> success(contains(loops_msl, "constant uint& n [[buffer(2)]]"), "@uniform uint -> constant-address-space reference")
    }
    t |> run("loops: bounds guard") <| @(t : T?) {
        t |> success(contains(loops_msl, "if ((i >= n)) \{"), "guard compares thread id against the uniform")
        t |> success(contains(loops_msl, "return;"), "void early return")
    }
    t |> run("loops: while + break/continue") <| @(t : T?) {
        t |> success(contains(loops_msl, "while ((j < 100)) \{"), "while loop")
        t |> success(contains(loops_msl, "continue;"), "continue")
        t |> success(contains(loops_msl, "break;"), "break")
    }
    t |> run("loops: range-for forms") <| @(t : T?) {
        t |> success(contains(loops_msl, "for (int k = 0; k < 4; ++k) \{"), "constant range inlines its bounds")
        t |> success(contains(loops_msl, "for (int _k = 0, _k_end = s; _k < _k_end; ++_k) \{"),
            "dynamic end hoists into a loop-scoped local (das evaluates range endpoints once)")
        t |> success(contains(loops_msl, "for (uint ku = 0u, ku_end = n; ku < ku_end; ++ku) \{"), "urange over the uniform, uint induction")
    }
}

[test]
def test_loops_golden(t : T?) {
    t |> run("loops: golden snapshot") <| @(t : T?) {
        t |> equal(loops_msl, GOLDEN_LOOPS)
    }
}
