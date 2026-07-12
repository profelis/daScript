options gen2
options indenting = 4

// Metal-only builtin surface on top of the shared shader lingua franca (the spirv_builtins
// pattern: re-export the shared compute IDs + barrier(), add what only this backend speaks).
// All declarations are AST markers: the emitter lowers references/calls by NAME; the stub
// bodies exist so the same kernel method compiles and runs on the CPU. The simd stubs are
// IDENTITY functions — that is the degenerate-but-valid width-1 simdgroup semantics, so a CPU
// replay that sets gl_SubgroupSize = 1u and gl_SubgroupInvocationID = 0u stays exact.

module metal_builtins shared public

require daslib/shader_lingua_franca public

// ===== compute builtins (Metal-only additions) =====
// gl_WorkGroupSize is a layout CONSTANT in GLSL; Metal surfaces it as a real kernel parameter
// ([[threads_per_threadgroup]]), so here it is an ordinary builtin global the host/driver can set.
var gl_WorkGroupSize : uint3            // threads per threadgroup     -> [[threads_per_threadgroup]]

// simdgroup IDs, GLSL subgroup spellings (KHR_shader_subgroup names — portable if dasSpirv grows
// subgroup support later); the emitter lowers each to Metal's simdgroup attribute.
var gl_SubgroupInvocationID : uint      // lane within the simdgroup   -> [[thread_index_in_simdgroup]]
var gl_SubgroupSize : uint              // simdgroup execution width   -> [[threads_per_simdgroup]]
var gl_NumSubgroups : uint              // simdgroups per threadgroup  -> [[simdgroups_per_threadgroup]]
var gl_SubgroupID : uint                // simdgroup within the group  -> [[simdgroup_index_in_threadgroup]]

// ===== simdgroup reductions + shuffles (Metal spellings — the Metal value-add) =====
// simd_sum(v): sum of v across the simdgroup's active lanes.
[unused_argument(v), sideeffects] def public simd_sum(v : float) : float { return v }
[unused_argument(v), sideeffects] def public simd_sum(v : int) : int { return v }
[unused_argument(v), sideeffects] def public simd_sum(v : uint) : uint { return v }

// simd_shuffle(v, lane): v from the given absolute lane. Reading an inactive lane is undefined —
// keep shuffles in simdgroup-uniform control flow and select the edge cases on the VALUE after.
[unused_argument(lane), sideeffects] def public simd_shuffle(v : float; lane : uint) : float { return v }
[unused_argument(lane), sideeffects] def public simd_shuffle(v : int; lane : uint) : int { return v }
[unused_argument(lane), sideeffects] def public simd_shuffle(v : uint; lane : uint) : uint { return v }

// simd_shuffle_up/_down(v, delta): v from lane - delta / lane + delta (NOT wrapping — the result
// is undefined for lanes whose source falls outside the simdgroup).
[unused_argument(delta), sideeffects] def public simd_shuffle_up(v : float; delta : uint) : float { return v }
[unused_argument(delta), sideeffects] def public simd_shuffle_up(v : int; delta : uint) : int { return v }
[unused_argument(delta), sideeffects] def public simd_shuffle_up(v : uint; delta : uint) : uint { return v }

[unused_argument(delta), sideeffects] def public simd_shuffle_down(v : float; delta : uint) : float { return v }
[unused_argument(delta), sideeffects] def public simd_shuffle_down(v : int; delta : uint) : int { return v }
[unused_argument(delta), sideeffects] def public simd_shuffle_down(v : uint; delta : uint) : uint { return v }

// simd_shuffle_xor(v, mask): v from lane ^ mask (the butterfly primitive; always in range).
[unused_argument(mask), sideeffects] def public simd_shuffle_xor(v : float; mask : uint) : float { return v }
[unused_argument(mask), sideeffects] def public simd_shuffle_xor(v : int; mask : uint) : int { return v }
[unused_argument(mask), sideeffects] def public simd_shuffle_xor(v : uint; mask : uint) : uint { return v }
