options gen2
options indenting = 4

module llvm_code_selftest shared private

require llvm/daslib/llvm_boost
require llvm/daslib/llvm_jit_code
require daslib/ast_boost

//! Worked example of an `[llvm_code]` generator, and the self-test vehicle for the rail
//! (tests/llvm_code/): emits `a + b` for an `(int, int) : int` stub, declines any other
//! signature so the reference body compiles instead.

def private is_int_pair_to_int(fn : Function const?) : bool {
    if ((length(fn.arguments) != 2)
        || (fn.arguments[0]._type.baseType != Type.tInt)
        || (fn.arguments[1]._type.baseType != Type.tInt)) return false
    return fn.result.baseType == Type.tInt
}

def private add_i32_gen(var gc : LlvmCodeCtx) : bool {
    if (!is_int_pair_to_int(gc.fn)) return false // decline: the reference body compiles as usual
    var entry = LLVMAppendBasicBlockInContext(gc.jit.ctx, gc.impl, "entry")
    LLVMPositionBuilderAtEnd(gc.jit.builder, entry)
    let sum = LLVMBuildAdd(gc.jit.builder, LLVMGetParam(gc.impl, 0u), LLVMGetParam(gc.impl, 1u), "llvm_code.sum")
    LLVMBuildRet(gc.jit.builder, sum)
    return true
}

// Called from llvm_user_modules::register_user_llvm_code_generators — the JIT invokes that
// in the context that reads the registry, so the direct call lands in the right table copy.
[macro_function]
def public register_selftest {
    register_llvm_code_generator("llvm_code_selftest::add_i32", @@add_i32_gen)
}
