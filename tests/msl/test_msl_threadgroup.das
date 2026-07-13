options gen2
options indenting = 4

// Phase-3 threadgroup gate (text layer): @workgroup fixed-array + scalar members lower to
// threadgroup declarations at the top of the kernel body (name-sorted, never parameters);
// barrier() and memoryBarrierShared() both lower to threadgroup_barrier(mem_flags::mem_threadgroup)
// (MSL has no execution-free threadgroup fence — the SPIRV-Cross strengthening); and the five
// workgroup-grid builtins lower to their attributed parameters.

require dastest/testing_boost public
require _msl_common
require daslib/strings_boost

let GOLDEN_REDUCE = "#include <metal_stdlib>
using namespace metal;
kernel void reduce(device const uint* src [[buffer(0)]],
        device uint* dst [[buffer(1)]],
        uint3 gl_GlobalInvocationID [[thread_position_in_grid]],
        uint3 gl_LocalInvocationID [[thread_position_in_threadgroup]],
        uint gl_LocalInvocationIndex [[thread_index_in_threadgroup]],
        uint3 gl_NumWorkGroups [[threadgroups_per_grid]],
        uint3 gl_WorkGroupID [[threadgroup_position_in_grid]],
        uint3 gl_WorkGroupSize [[threads_per_threadgroup]],
        threadgroup char * shmem [[threadgroup(0)]]) \{
    threadgroup uint * tile = (threadgroup uint *)(shmem);
    threadgroup uint * total_wg = (threadgroup uint *)(shmem + 256);
    uint gid = gl_GlobalInvocationID.x;
    uint lid = gl_LocalInvocationID.x;
    tile[lid] = src[gid];
    threadgroup_barrier(mem_flags::mem_threadgroup);
    uint s = (gl_WorkGroupSize.x / 2u);
    while ((s > 0u)) \{
        if ((lid < s)) \{
            tile[lid] += tile[(lid + s)];
        \}
        threadgroup_barrier(mem_flags::mem_threadgroup);
        s /= 2u;
    \}
    if ((gl_LocalInvocationIndex == 0u)) \{
        (*total_wg) = (tile[0] + (gl_NumWorkGroups.x * 0u));
    \}
    threadgroup_barrier(mem_flags::mem_threadgroup);
    if ((gl_LocalInvocationIndex == 0u)) \{
        dst[gl_WorkGroupID.x] = (*total_wg);
    \}
\}
"

[test]
def test_threadgroup_shape(t : T?) {
    t |> run("reduce: @workgroup members -> body-top threadgroup declarations") <| @(t : T?) {
        t |> success(contains(reduce_msl, "    threadgroup uint * tile = (threadgroup uint *)(shmem);"), "fixed array -> shmem-derived pointer")
        t |> success(contains(reduce_msl, "    threadgroup uint * total_wg = (threadgroup uint *)(shmem + 256);"), "scalar -> shmem-derived pointer, accesses dereference")
        t |> success(!contains(reduce_msl, "tile [[buffer"), "threadgroup memory is never a buffer parameter")
    }
    t |> run("reduce: barrier lowering") <| @(t : T?) {
        t |> success(contains(reduce_msl, "threadgroup_barrier(mem_flags::mem_threadgroup);"), "barrier() -> threadgroup rendezvous+fence")
    }
    t |> run("reduce: workgroup-grid builtin parameters") <| @(t : T?) {
        t |> success(contains(reduce_msl, "uint3 gl_LocalInvocationID [[thread_position_in_threadgroup]]"), "local invocation id")
        t |> success(contains(reduce_msl, "uint3 gl_WorkGroupID [[threadgroup_position_in_grid]]"), "workgroup id")
        t |> success(contains(reduce_msl, "uint3 gl_NumWorkGroups [[threadgroups_per_grid]]"), "workgroup count")
        t |> success(contains(reduce_msl, "uint3 gl_WorkGroupSize [[threads_per_threadgroup]]"), "workgroup size")
        t |> success(contains(reduce_msl, "uint gl_LocalInvocationIndex [[thread_index_in_threadgroup]]"), "flat local index")
    }
}

[test]
def test_threadgroup_golden(t : T?) {
    t |> run("reduce: golden snapshot") <| @(t : T?) {
        t |> equal(reduce_msl, GOLDEN_REDUCE)
    }
}
