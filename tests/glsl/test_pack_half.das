options gen2
options indenting = 4

// packHalf2x16/unpackHalf2x16 bridge (shader_lingua_franca): CPU bodies are exact bit packs
// (das half2 is layout-identical to the packed uint), the GLSL rail passes the names through
// and adds GL_ARB_shading_language_packing on demand below 4.20. This is the ONE fp16 story
// the ES/WebGL2 rail keeps (core in ES 3.00 — no extension line there).

require dastest/testing_boost public
require _glsl_common
require glsl/glsl_opengl

var @inout ph_uv : float2
var @out ph_color : float4

[fragment_program(name="pack_half_glsl")]
def pack_half_fragment {
    let bits = packHalf2x16(ph_uv)
    let back = unpackHalf2x16(bits)
    ph_color = float4(back.x, back.y, 0., 1.)
}

[test]
def test_pack_half_cpu(t : T?) {
    t |> run("CPU pack/unpack: exact bits and round trip") <| @(t : T?) {
        t |> equal(packHalf2x16(float2(1.5, -2.25)), 0xc0803e00)
        t |> equal(packHalf2x16(float2(0., 0.)), 0x0)
        let rt = unpackHalf2x16(packHalf2x16(float2(0.125, 65504.0)))
        t |> success(rt == float2(0.125, 65504.0), "f16-exact values round trip")
    }
}

[test]
def test_pack_half_glsl_emission(t : T?) {
    t |> run("GLSL: pass-through names + demand-driven ARB packing extension") <| @(t : T?) {
        t |> success(has(pack_half_glsl, "#extension GL_ARB_shading_language_packing : require"), "extension line")
        t |> success(has(pack_half_glsl, "packHalf2x16("), "pack call")
        t |> success(has(pack_half_glsl, "unpackHalf2x16("), "unpack call")
        let r = validate_glsl(pack_half_glsl, "frag")
        if (r.ran) {
            t |> success(r.ok, "glslang: {r.msg}")
        } else {
            feint("glslangValidator not found locally; skipping (CI enforces)\n")
        }
    }
}
