options gen2
options indenting = 4

// packHalf2x16/unpackHalf2x16 on the SPIR-V rail: GLSL.std.450 PackHalf2x16/UnpackHalf2x16
// ext-insts (numbers 58/62). Ext-inst NUMBERS don't enter the opcode census (only ExtInst
// itself, already declared); spirv-val is the correctness oracle.

require dastest/testing_boost public
require _spirv_common
require spirv/spirv_shader
require spirv/spirv_dis
require spirv/spirv_grammar

var @ssbo @binding = 0 ph_data : array<uint>

[compute_shader(local_size_x=64, name="pack_half_spv"), marker(no_coverage)]
def pack_half_kernel {
    let gi = gl_GlobalInvocationID.x
    let back = unpackHalf2x16(ph_data[gi])
    ph_data[gi] = packHalf2x16(float2(back.y, back.x))
}

[test]
def test_pack_half_spirv(t : T?) {
    t |> run("pack/unpack lower to GLSL.std.450 ext-insts and validate") <| @(t : T?) {
        var words <- clone_to_move(pack_half_spv)
        t |> equal(words[0], SPV_MAGIC)
        t |> equal(count_op(words, SpvOp.ExtInst), 2)       // one pack + one unpack
        t |> success(has_op(words, SpvOp.ExtInstImport), "GLSL.std.450 imported")
        let r = validate_spirv(words)
        if (r.ran) {
            t |> success(r.ok, "spirv-val: {r.msg}")
        } else {
            feint("spirv-val not found locally; skipping (CI enforces)\n")
        }
        delete words
    }
}
