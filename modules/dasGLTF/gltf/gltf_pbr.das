options gen2
options indenting = 4
options no_unused_block_arguments = false
options no_unused_function_arguments = false

module gltf_pbr shared

require gltf/gltf_types
require gltf/gltf_gl public
require opengl/opengl_boost public
require glsl/glsl_opengl public
require daslib/safe_addr
require math
require daslib/math_boost

// OPT-IN metallic-roughness PBR renderer for a GltfGlModel. The shader is authored once in the
// portable shader DSL (Cook-Torrance GGX) and lowered to GLSL by the [*_program] macros — the same
// body ports to Vulkan by swapping the annotation name. The shader globals below are module-private:
// the app never touches them, it drives everything through gltf_pbr_create / gltf_pbr_render.

// ===== vertex stage =====
// @location order is the contract with gltf_gl's GltfGlVertex (0..7); we consume 0..3 here.
var @in @location = 0 a_position : float3
var @in @location = 1 a_normal   : float3
var @in @location = 2 a_tangent  : float4
var @in @location = 3 a_uv0      : float2

var @uniform u_model    : float4x4
var @uniform u_viewProj : float4x4

var @inout v_world_pos     : float3
var @inout v_world_normal  : float3
var @inout v_world_tangent : float3
var @inout v_tangent_w     : float
var @inout v_uv0           : float2

[vertex_program]
def gltf_pbr_vs {
    let world = u_model * float4(a_position, 1.0)
    v_world_pos = world.xyz
    let nm = float3x3(u_model)
    v_world_normal = normalize(nm * a_normal)
    v_world_tangent = nm * a_tangent.xyz
    v_tangent_w = a_tangent.w
    v_uv0 = a_uv0
    gl_Position = u_viewProj * world
}

// ===== fragment stage =====
var @uniform u_cam_pos     : float3
var @uniform u_light_dir   : float3   // direction TOWARD the light, normalized
var @uniform u_light_color : float3   // radiance (color * intensity)
var @uniform u_ambient     : float3   // constant ambient irradiance

var @uniform u_base_color_factor  : float4
var @uniform u_metallic_factor    : float
var @uniform u_roughness_factor   : float
var @uniform u_emissive_factor    : float3
var @uniform u_normal_scale       : float
var @uniform u_occlusion_strength : float
var @uniform u_alpha_cutoff       : float
var @uniform u_alpha_mode         : float   // 0 OPAQUE, 1 MASK, 2 BLEND

// base-color / emissive are sRGB textures (hardware decode -> linear); the rest are linear.
var @uniform @stage = 0 u_base_color_tex  : sampler2D
var @uniform @stage = 1 u_metal_rough_tex : sampler2D
var @uniform @stage = 2 u_normal_tex      : sampler2D
var @uniform @stage = 3 u_occlusion_tex   : sampler2D
var @uniform @stage = 4 u_emissive_tex    : sampler2D

var @out o_color : float4

// Trowbridge-Reitz GGX normal distribution.
def private distribution_ggx(n, h : float3; roughness : float) : float {
    let a = roughness * roughness
    let a2 = a * a
    let ndoth = max(dot(n, h), 0.0)
    let d = ndoth * ndoth * (a2 - 1.0) + 1.0
    return a2 / max(3.14159265 * d * d, 0.0000001)
}

// Smith geometry term with Schlick-GGX, direct-lighting k = (r+1)^2 / 8.
def private geometry_smith(n, v, l : float3; roughness : float) : float {
    let r = roughness + 1.0
    let k = r * r * 0.125
    let ndotv = max(dot(n, v), 0.0)
    let ndotl = max(dot(n, l), 0.0)
    let gv = ndotv / (ndotv * (1.0 - k) + k)
    let gl = ndotl / (ndotl * (1.0 - k) + k)
    return gv * gl
}

def private fresnel_schlick(cos_theta : float; f0 : float3) : float3 {
    let m = clamp(1.0 - cos_theta, 0.0, 1.0)
    let m5 = m * m * m * m * m
    return f0 + (float3(1.0, 1.0, 1.0) - f0) * m5
}

// Perturb the geometric normal by the tangent-space normal map when a tangent frame exists; fall back
// to the geometric normal otherwise (the flat-normal default texture also yields no perturbation).
def private shade_normal(uv : float2) : float3 {
    let n_geom = normalize(v_world_normal)
    let tlen = length(v_world_tangent)
    var n = n_geom
    if (tlen > 0.0001) {
        let t = v_world_tangent * (1.0 / tlen)
        let b = cross(n_geom, t) * v_tangent_w
        let s = texture(u_normal_tex, uv).xyz * 2.0 - float3(1.0, 1.0, 1.0)
        let sx = s.x * u_normal_scale
        let sy = s.y * u_normal_scale
        n = normalize(t * sx + b * sy + n_geom * s.z)
    }
    return n
}

[fragment_program]
def gltf_pbr_fs {
    let uv = v_uv0
    let base = texture(u_base_color_tex, uv) * u_base_color_factor
    // MASK: hard cutoff; BLEND leaves alpha for host-side blending; OPAQUE forces alpha 1.
    if (u_alpha_mode > 0.5 && u_alpha_mode < 1.5 && base.w < u_alpha_cutoff) {
        discard()
    }
    let mr = texture(u_metal_rough_tex, uv)
    let metallic = mr.z * u_metallic_factor
    let roughness = clamp(mr.y * u_roughness_factor, 0.04, 1.0)
    let occ = texture(u_occlusion_tex, uv).x
    let emissive = texture(u_emissive_tex, uv).xyz * u_emissive_factor

    let albedo = base.xyz
    let n = shade_normal(uv)
    let v = normalize(u_cam_pos - v_world_pos)
    let l = normalize(u_light_dir)
    let h = normalize(v + l)
    let ndotl = max(dot(n, l), 0.0)
    let ndotv = max(dot(n, v), 0.0)

    let f0 = lerp(float3(0.04, 0.04, 0.04), albedo, float3(metallic, metallic, metallic))
    let d = distribution_ggx(n, h, roughness)
    let g = geometry_smith(n, v, l, roughness)
    let f = fresnel_schlick(max(dot(h, v), 0.0), f0)
    let spec_denom = 4.0 * ndotv * ndotl + 0.0001
    let specular = f * (d * g * (1.0 / spec_denom))

    let kd = (float3(1.0, 1.0, 1.0) - f) * (1.0 - metallic)
    let diffuse = kd * albedo * (1.0 / 3.14159265)
    let direct = (diffuse + specular) * u_light_color * ndotl

    // occlusion darkens indirect (ambient) only, per the glTF strength blend
    let ao = 1.0 + u_occlusion_strength * (occ - 1.0)
    let ambient = u_ambient * albedo * ao

    let linear = ambient + direct + emissive
    // no sRGB default framebuffer -> encode linear -> sRGB (approximate 2.2 gamma)
    let g22 = 1.0 / 2.2
    let out_rgb = pow(linear, float3(g22, g22, g22))
    let out_a = u_alpha_mode > 1.5 ? base.w : 1.0
    o_color = float4(out_rgb, out_a)
}

// ===== host renderer =====

struct GltfPbrRenderer {
    program : uint
}

//! A single directional light plus a flat ambient term. `direction` points TOWARD the light.
struct GltfPbrLight {
    direction : float3 = float3(0.3, 0.7, 0.5)
    color     : float3 = float3(1.0, 1.0, 1.0)
    intensity : float  = 3.0
    ambient   : float3 = float3(0.15, 0.15, 0.18)
}

//! Compile + link the PBR program. Call with a current GL context; `delete` the renderer to release it.
def gltf_pbr_create : GltfPbrRenderer {
    var r = GltfPbrRenderer()
    r.program = create_shader_program(@@gltf_pbr_vs, @@gltf_pbr_fs)
    return r
}

def finalize(var r : GltfPbrRenderer) {
    if (r.program != 0u) {
        glDeleteProgram(r.program)
    }
}

def private bind_material(model : GltfGlModel; mat : GltfMaterial) {
    u_base_color_factor = mat.baseColorFactor
    u_metallic_factor = mat.metallicFactor
    u_roughness_factor = mat.roughnessFactor
    u_emissive_factor = mat.emissiveFactor
    u_normal_scale = mat.normalScale
    u_occlusion_strength = mat.occlusionStrength
    u_alpha_cutoff = mat.alphaCutoff
    u_alpha_mode = (mat.alphaMode == GltfAlphaMode.mask ? 1.0
        : (mat.alphaMode == GltfAlphaMode.blend ? 2.0 : 0.0))
    u_base_color_tex := gltf_gl_resolve_tex(model, mat.baseColorTex, model.whiteTex)
    u_metal_rough_tex := gltf_gl_resolve_tex(model, mat.metalRoughTex, model.whiteTex)
    u_normal_tex := gltf_gl_resolve_tex(model, mat.normalTex, model.flatNormalTex)
    u_occlusion_tex := gltf_gl_resolve_tex(model, mat.occlusionTex, model.whiteTex)
    u_emissive_tex := gltf_gl_resolve_tex(model, mat.emissiveTex, model.whiteTex)
    if (mat.doubleSided) {
        glDisable(GL_CULL_FACE)
    } else {
        glEnable(GL_CULL_FACE)
        glCullFace(GL_BACK)
    }
    if (mat.alphaMode == GltfAlphaMode.blend) {
        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
    } else {
        glDisable(GL_BLEND)
    }
}

//! Render every mesh instance in `scene` with the PBR shader, using the GL objects in `model`. Each
//! node's precomputed `world` matrix is the model transform; per primitive the material factors +
//! textures are bound and doubleSided/alpha GL state is set. The caller owns clear + depth-test state.
def gltf_pbr_render(r : GltfPbrRenderer; model : GltfGlModel; scene : GltfScene;
                    view, proj : float4x4; camPos : float3; light : GltfPbrLight) {
    glUseProgram(r.program)
    u_viewProj = proj * view
    u_cam_pos = camPos
    u_light_dir = normalize(light.direction)
    u_light_color = light.color * light.intensity
    u_ambient = light.ambient
    for (node in scene.nodes) {
        if (node.mesh < 0 || node.mesh >= length(model.meshes)) {
            continue
        }
        u_model = node.world
        for (glp in model.meshes[node.mesh].primitives) {
            if (glp.material >= 0 && glp.material < length(scene.materials)) {
                bind_material(model, scene.materials[glp.material])
            } else {
                bind_material(model, GltfMaterial())
            }
            gltf_pbr_vs_bind_uniform(r.program)
            gltf_pbr_fs_bind_uniform(r.program)
            gltf_gl_draw_primitive(glp)
        }
    }
    glUseProgram(0u)
}
