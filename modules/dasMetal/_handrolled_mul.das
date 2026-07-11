options gen2

// Phase-0 dev scaffold (MASTERPLAN.md) — proves the das_metal binding end to end with a
// hand-written INLINE MSL string; deleted when the Phase-1 emitter lands. Probes:
//   (1) device -> queue -> pipeline -> dispatch -> readback, exact
//   (2) bad MSL surfaces the Metal compiler log as a clean das error string
//   (3) the shim live-object counter round-trips to zero

require das_metal

let MSL_MUL = "
#include <metal_stdlib>
using namespace metal;
kernel void mul_ab(device const float* a [[buffer(0)]],
                   device const float* b [[buffer(1)]],
                   device float* c [[buffer(2)]],
                   uint3 gid [[thread_position_in_grid]]) \{
    c[gid.x] = a[gid.x] * b[gid.x];
\}
"

let MSL_BAD = "
#include <metal_stdlib>
kernel void broken(device float* c [[buffer(0)]]) \{
    c[0] = undeclared_identifier;
\}
"

let N = 256
let TPG = 64u

def verify_c(pc : float const?; tag : string) : bool {
    var bad = 0
    for (i in range(N)) {
        let want = float(i) * float(i % 7 + 1)
        let got = unsafe(pc[i])
        if (got != want) {
            if (bad < 4) {
                print("  {tag}: c[{i}] = {got}, expected {want}\n")
            }
            bad++
        }
    }
    if (bad != 0) print("FAILED: {tag}: {bad} of {N} elements wrong\n")
    return bad == 0
}

[export]
def main() : int {
    var dev = metal_create_system_default_device()
    if (dev == null) {
        print("FAILED: no Metal device\n")
        return 1
    }
    print("device: {metal_device_name(dev)}, unified memory: {metal_device_has_unified_memory(dev)}\n")

    // probe (2): bad MSL must fail with the compiler log, not crash or succeed
    var bad_err : string
    let bad_lib = metal_new_library_from_source(dev, MSL_BAD, true, bad_err)
    if (bad_lib != null || empty(bad_err)) {
        print("FAILED: bad MSL did not surface an error\n")
        return 1
    }
    print("bad-MSL probe OK, compiler log:\n{bad_err}\n")

    // probe (1): the a*b kernel, exact readback
    var lib_err : string
    let lib = metal_new_library_from_source(dev, MSL_MUL, true, lib_err)
    if (lib == null) {
        print("FAILED: MSL compile: {lib_err}\n")
        return 1
    }
    let fn = metal_new_function(lib, "mul_ab")
    if (fn == null) {
        print("FAILED: kernel `mul_ab` not found in library\n")
        return 1
    }
    var pso_err : string
    let pso = metal_new_compute_pipeline(dev, fn, pso_err)
    if (pso == null) {
        print("FAILED: pipeline: {pso_err}\n")
        return 1
    }
    let queue = metal_new_command_queue(dev)

    let bytes = uint64(N * 4)
    let ba = metal_new_buffer(dev, bytes)
    let bb = metal_new_buffer(dev, bytes)
    let bc = metal_new_buffer(dev, bytes)
    var pa = unsafe(reinterpret<float?>(metal_buffer_contents(ba)))
    var pb = unsafe(reinterpret<float?>(metal_buffer_contents(bb)))
    var pc = unsafe(reinterpret<float?>(metal_buffer_contents(bc)))
    for (i in range(N)) {
        unsafe {
            pa[i] = float(i)
            pb[i] = float(i % 7 + 1)
            pc[i] = 0.0
        }
    }

    // threadgroup-count dispatch (portable form)
    let cb1 = metal_new_command_buffer(queue)
    let enc1 = metal_new_compute_encoder(cb1)
    metal_set_pipeline(enc1, pso)
    metal_set_buffer(enc1, ba, 0ul, 0)
    metal_set_buffer(enc1, bb, 0ul, 1)
    metal_set_buffer(enc1, bc, 0ul, 2)
    metal_dispatch_threadgroups(enc1, uint3(uint(N) / TPG, 1u, 1u), uint3(TPG, 1u, 1u))
    metal_end_encoding(enc1)
    metal_commit(cb1)
    metal_wait_until_completed(cb1)
    let cb1_err = metal_command_buffer_error(cb1)
    if (!empty(cb1_err)) {
        print("FAILED: command buffer (threadgroups): {cb1_err}\n")
        return 1
    }
    if (!verify_c(pc, "dispatch_threadgroups")) return 1
    print("dispatch_threadgroups OK, {N} elements exact\n")

    // exact-grid dispatch (Apple-family fast path)
    for (i in range(N)) {
        unsafe(pc[i]) = 0.0
    }
    let cb2 = metal_new_command_buffer(queue)
    let enc2 = metal_new_compute_encoder(cb2)
    metal_set_pipeline(enc2, pso)
    metal_set_buffer(enc2, ba, 0ul, 0)
    metal_set_buffer(enc2, bb, 0ul, 1)
    metal_set_buffer(enc2, bc, 0ul, 2)
    metal_dispatch_threads(enc2, uint3(uint(N), 1u, 1u), uint3(TPG, 1u, 1u))
    metal_end_encoding(enc2)
    metal_commit(cb2)
    metal_wait_until_completed(cb2)
    let cb2_err = metal_command_buffer_error(cb2)
    if (!empty(cb2_err)) {
        print("FAILED: command buffer (threads): {cb2_err}\n")
        return 1
    }
    if (!verify_c(pc, "dispatch_threads")) return 1
    print("dispatch_threads OK, {N} elements exact\n")

    // probe (3): every handle released -> live-object counter back to zero
    metal_release(enc1)
    metal_release(cb1)
    metal_release(enc2)
    metal_release(cb2)
    metal_release(ba)
    metal_release(bb)
    metal_release(bc)
    metal_release(pso)
    metal_release(fn)
    metal_release(lib)
    metal_release(queue)
    metal_release(dev)
    let live = metal_live_object_count()
    if (live != 0l) {
        print("FAILED: {live} Metal objects still live after release\n")
        return 1
    }
    print("live-object probe OK, counter is 0\n")
    print("PHASE 0 SCAFFOLD: ALL PROBES PASSED\n")
    return 0
}
