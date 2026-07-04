options gen2
options indenting = 4

module llvm_user_modules shared private

require llvm/daslib/llvm_code_selftest
require dasllama/dasllama_gemm_gen  // M2 GEMM tile generator (gemm_generator_plan.md) — needs dasLLAMA linked; require ?-gating is the planned form

//! User-extensible wiring for `[llvm_code]` generator modules. The JIT calls
//! `register_user_llvm_code_generators` (lazily, in the context that reads the registry)
//! before the first generator lookup. To plug in your generator module: `require` it above
//! and call its registration function below. (Planned: `require ?<gate> <module>` +
//! `static_if (typeinfo builtin_module_exists(<gate>))` so entries load only when the gating
//! C++ module is linked — the linq-adapter pattern.)

var private g_registered = false

[macro_function]
def public register_user_llvm_code_generators {
    if (g_registered) {
        return
    }
    g_registered = true
    llvm_code_selftest::register_selftest()  // worked example + self-test generator (add_i32)
    dasllama_gemm_gen::register_dasllama_gemm_generators()
}
