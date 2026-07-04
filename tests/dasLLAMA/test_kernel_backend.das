options gen2

require dastest/testing_boost public
require dasllama/dasllama_math
require dasllama/dasllama_math_default        // registers the "portable" backend at [init]
require dasllama/dasllama_math_aarch64_neon   // registers "arm64-sdot" / "arm64-laneq" on arm64+jit
require dasllama/dasllama_math_x64_avx        // registers "x64-avx2*" (+repack/acc8/ps) on x86-64+avx2+jit

// The kernel-backend registry must self-populate at [init]: the portable Q8·Q8 backend is always
// registered (the fallback everywhere), and one is auto-activated as the row-major default. A repack
// backend (arm64 laneq / x64 grp4) is only activated by select_matmul_backend_for_load. No model file needed.

def private registered(name : string) : bool {
    for (n in kernel_backend_names()) {
        if (n == name) {
            return true
        }
    }
    return false
}

[test]
def test_portable_backend_always_registered(t : T?) {
    t |> run("portable backend registered + a row-major default auto-activated") @(t : T?) {
        t |> success(registered("portable"), "portable backend registered at [init]")
        t |> success(active_kernel_backend() != "", "a backend auto-activated (non-empty active)")
        t |> success(registered(active_kernel_backend()), "the active backend is a registered one")
        t |> success(!registered("bogus-backend"), "unknown backend not registered")
    }
}

[test]
def test_select_and_pin(t : T?) {
    t |> run("select / pin / for-load pick a registered backend and restore") @(t : T?) {
        let saved = active_kernel_backend()
        // explicit select by name
        select_kernel_backend("portable")
        t |> equal(active_kernel_backend(), "portable")
        // selecting an unknown name is a no-op (portable stays active)
        select_kernel_backend("does-not-exist")
        t |> equal(active_kernel_backend(), "portable")
        // for-load picks the best registered backend (a repack backend where available); its bool
        // return (needs_repack) drives whether the loader repacks — exercised for real by test_forward.
        select_matmul_backend_for_load()
        t |> success(registered(active_kernel_backend()), "for-load activated a registered backend")
        // pin forces a specific backend, overriding auto-select
        pin_kernel_backend("portable")
        t |> equal(active_kernel_backend(), "portable")
        // an unknown pin name is a no-op that keeps the current backend (regression: Copilot #3340 —
        // it must not stick an invalid pin that wedges the active kernels)
        pin_kernel_backend("no-such-backend")
        t |> equal(active_kernel_backend(), "portable", "unknown pin keeps the current backend")
        // restore the pre-test selection so later test files see the same active backend
        clear_kernel_backend_pin()
        if (saved != "") {
            select_kernel_backend(saved)
        }
    }
}

[test]
def test_batch_backend_pin(t : T?) {
    t |> run("batch pin overrides the batch slots, survives re-select, guards layout") @(t : T?) {
        let saved = active_kernel_backend()
        select_kernel_backend("portable")
        // no pin: batch backend follows the active backend
        t |> equal(active_batch_backend(), "portable", "batch backend defaults to the active one")
        // an unknown donor warns and keeps the active backend's batch slots
        select_batch_backend("no-such-backend")
        t |> equal(active_batch_backend(), "portable", "unknown batch donor keeps active batch slots")
        // a repack donor on a row-major active backend is layout-incompatible: warn + keep
        var tested_reject = false
        for (n in kernel_backend_names()) {
            if (n == "arm64-laneq" || n == "x64-avx2-repack") {
                select_batch_backend(n)
                t |> equal(active_batch_backend(), "portable", "repack donor rejected on row-major active")
                tested_reject = true
            }
        }
        if (!tested_reject) {
            to_log(LOG_WARNING, "test_batch_backend_pin: no repack donor (arm64-laneq/x64-avx2-repack) registered on this build — layout-guard path not exercised\n")
        }
        // a row-major donor takes the batch slots and survives re-activation
        var tested_accept = false
        for (n in kernel_backend_names()) {
            if (n == "arm64-sdot" || n == "x64-avx2-acc8") {
                select_batch_backend(n)
                t |> equal(active_batch_backend(), n, "row-major donor takes the batch slots")
                select_kernel_backend("portable")   // re-activate: the standing pin must re-apply
                t |> equal(active_batch_backend(), n, "batch pin survives re-selection")
                tested_accept = true
            }
        }
        if (!tested_accept) {
            to_log(LOG_WARNING, "test_batch_backend_pin: no row-major donor (arm64-sdot/x64-avx2-acc8) registered on this build — batch-pin override/survival not exercised\n")
        }
        // clearing the pin restores whole-backend slots on the next activation
        select_batch_backend("")
        select_kernel_backend("portable")
        t |> equal(active_batch_backend(), "portable", "cleared pin restores whole-backend slots")
        if (saved != "") {
            select_kernel_backend(saved)
        }
    }
}
