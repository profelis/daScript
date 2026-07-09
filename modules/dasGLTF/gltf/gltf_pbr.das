options gen2
options indenting = 4
options no_unused_block_arguments = false
options no_unused_function_arguments = false

module gltf_pbr shared

require gltf/gltf_types
require gltf/gltf_scene
require gltf/gltf_pbr_common public
require gltf/gltf_gl public
require opengl/opengl_boost public
require glsl/glsl_opengl public
require daslib/safe_addr
require math
require daslib/math_boost

// Max joints in the palette uniform. Desktop GL guarantees >= 1024 vec4 of vertex uniforms; 64 mat4 is
// 256 vec4, leaving ample room for the rest. Skins with more joints are clamped (rare for game assets).
let GLTF_MAX_JOINTS = 64

// OPT-IN metallic-roughness PBR renderer for a GltfGlModel. The shader is authored once in the
// portable shader DSL (Cook-Torrance GGX) and lowered to GLSL by the [*_program] macros — the same
// body ports to Vulkan by swapping the annotation name. The shader globals below are module-private:
// the app never touches them, it drives everything through gltf_pbr_create / gltf_pbr_render.

// ===== vertex stage =====
// @location order is the contract with gltf_gl's GltfGlVertex (0..7); we consume 0..3 + 6..7 (skinning).
var @in @location = 0 a_position : float3
var @in @location = 1 a_normal   : float3
var @in @location = 2 a_tangent  : float4
var @in @location = 3 a_uv0      : float2
var @in @location = 6 a_joints0  : float4   // joint indices (decoded to float at parse time)
var @in @location = 7 a_weights0 : float4   // per-joint blend weights (sum to 1)

var @uniform u_model    : float4x4
var @uniform u_viewProj : float4x4
var @uniform u_skinned  : float                    // 1 = blend the joint palette, 0 = rigid (use u_model)
var @uniform u_joints   : float4x4[GLTF_MAX_JOINTS] // world-space skinning palette (joint.world * inverseBind)
var @uniform u_normal_matrix : float3x3            // inverse-transpose of u_model's 3x3 (rigid-path normals)

var @inout v_world_pos     : float3
var @inout v_world_normal  : float3
var @inout v_world_tangent : float3
var @inout v_tangent_w     : float
var @inout v_uv0           : float2

[vertex_program]
def gltf_pbr_vs {
    var world = float4(0.0, 0.0, 0.0, 1.0)
    var wnormal = float3(0.0, 0.0, 0.0)
    var wtangent = float3(0.0, 0.0, 0.0)
    if (u_skinned > 0.5) {
        // The palette already maps into world space (joint.world * inverseBind), so u_model is not
        // applied. clamp to the palette size: a skin with > GLTF_MAX_JOINTS joints (or malformed
        // JOINTS_0) would otherwise index u_joints out of range -> undefined shader behavior.
        let jx = clamp(int(a_joints0.x), 0, GLTF_MAX_JOINTS - 1)
        let jy = clamp(int(a_joints0.y), 0, GLTF_MAX_JOINTS - 1)
        let jz = clamp(int(a_joints0.z), 0, GLTF_MAX_JOINTS - 1)
        let jw = clamp(int(a_joints0.w), 0, GLTF_MAX_JOINTS - 1)
        world = gltf_skin_point(u_joints[jx], u_joints[jy], u_joints[jz], u_joints[jw],
            a_weights0, float4(a_position, 1.0))
        wnormal = gltf_skin_point(u_joints[jx], u_joints[jy], u_joints[jz], u_joints[jw],
            a_weights0, float4(a_normal, 0.0)).xyz
        wtangent = gltf_skin_point(u_joints[jx], u_joints[jy], u_joints[jz], u_joints[jw],
            a_weights0, float4(a_tangent.xyz, 0.0)).xyz
    } else {
        world = u_model * float4(a_position, 1.0)
        // u_normal_matrix is inverse-transpose(u_model 3x3), so normals stay correct under
        // non-uniform scale / shear (float3x3(u_model) would skew them).
        wnormal = u_normal_matrix * a_normal
        wtangent = u_normal_matrix * a_tangent.xyz
    }
    v_world_pos = world.xyz
    v_world_normal = normalize(wnormal)
    v_world_tangent = wtangent
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
// equirect HDR environment (linear radiance, mipmapped); u_env_amount = 0 -> flat ambient
var @uniform @stage = 5 u_env_tex         : sampler2D
var @uniform u_env_amount  : float
var @uniform u_env_max_lod : float

var @out o_color : float4

// The BRDF / normal-perturbation / skinning math lives in gltf/gltf_pbr_common — shared with the
// dasVulkan renderer; this module only samples textures and feeds the values in.
def private shade_normal(uv : float2) : float3 {
    return gltf_perturb_normal(normalize(v_world_normal), v_world_tangent, v_tangent_w,
        texture(u_normal_tex, uv).xyz, u_normal_scale)
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
    let direct = gltf_pbr_direct(albedo, metallic, roughness, n, v, l, u_light_color)
    var ambient = gltf_pbr_ambient(albedo, u_ambient, occ, u_occlusion_strength)
    if (u_env_amount > 0.0) {
        // image-based ambient: irradiance from a deep mip along n, reflection from a
        // roughness-scaled mip along the mirror direction (mips as prefiltered environment)
        let irr = textureLod(u_env_tex, gltf_equirect_uv(n), u_env_max_lod - 2.0).xyz
        let refl = textureLod(u_env_tex, gltf_equirect_uv(gltf_reflect_dir(n, v)), roughness * u_env_max_lod).xyz
        ambient = gltf_env_ambient(albedo, metallic, roughness, n, v, irr, refl,
            gltf_occlusion_factor(occ, u_occlusion_strength)) * u_env_amount
    }

    let linear = ambient + direct + emissive
    // no sRGB default framebuffer -> encode linear -> sRGB (approximate 2.2 gamma)
    let out_rgb = gltf_srgb_encode(linear)
    let out_a = u_alpha_mode > 1.5 ? base.w : 1.0
    o_color = float4(out_rgb, out_a)
}

// ===== host renderer =====

struct GltfPbrRenderer {
    program   : uint
    envTex    : uint     // mipmapped equirect HDR environment, 0 = none (flat ambient)
    envMaxLod : float
}

//! Attach a mipmapped equirect HDR environment (see gltf_gl_load_hdr_env); pass 0 to remove it.
//! The renderer does not take ownership of the texture. `GltfPbrLight.environment` scales its
//! contribution per frame.
def gltf_pbr_set_environment(var r : GltfPbrRenderer; tex : uint; max_lod : float) {
    r.envTex = tex
    r.envMaxLod = max_lod
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

// Fill the joint-palette uniform for a skin (clamped to GLTF_MAX_JOINTS), pre-multiplied by the world-
// space `root` transform. The skinned vertex path blends the palette directly (it never reads u_model),
// so baking root here is what makes a viewer turntable transform reach skinned geometry too.
def private bind_skin_palette(scene : GltfScene; skinIndex : int; root : float4x4) {
    let njoint = min(length(scene.skins[skinIndex].joints), GLTF_MAX_JOINTS)
    for (j in range(njoint)) {
        u_joints[j] = root * gltf_joint_matrix(scene, skinIndex, j)
    }
    // clear the unused slots so a clamped / out-of-range joint index reads identity rather than a
    // stale matrix left over from a previously-bound skin
    for (j in range(njoint, GLTF_MAX_JOINTS)) {
        u_joints[j] = identity4x4()
    }
}

//! Render every mesh instance in `scene` with the PBR shader, using the GL objects in `model`. A node
//! with a `skin` is drawn skinned (its joint palette is uploaded and the mesh-node transform ignored);
//! otherwise the node's precomputed `world` matrix is the model transform. Per primitive the material
//! factors + textures are bound and doubleSided/alpha GL state is set. Caller owns clear + depth state.
def gltf_pbr_render(r : GltfPbrRenderer; model : GltfGlModel; scene : GltfScene;
                    view, proj : float4x4; camPos : float3; light : GltfPbrLight) {
    gltf_pbr_render(r, model, scene, identity4x4(), view, proj, camPos, light)
}

//! As above, but pre-multiplies a world-space `root` transform onto the whole scene (a viewer turntable
//! rotation/scale, say). Rigid nodes render at `root * node.world`; for skinned nodes `root` is baked into
//! the joint palette, so it transforms rigid and skinned geometry alike — and lighting responds correctly
//! (root reaches the world-space normals). The plain overload passes `identity4x4()`, so it is unchanged.
def gltf_pbr_render(r : GltfPbrRenderer; model : GltfGlModel; scene : GltfScene; root : float4x4;
                    view, proj : float4x4; camPos : float3; light : GltfPbrLight) {
    glUseProgram(r.program)
    u_viewProj = proj * view
    u_cam_pos = camPos
    u_light_dir = normalize(light.direction)
    u_light_color = light.color * light.intensity
    u_ambient = light.ambient
    u_env_tex := (r.envTex != 0u ? r.envTex : model.whiteTex)
    u_env_amount = r.envTex != 0u ? light.environment : 0.0
    u_env_max_lod = r.envMaxLod
    for (node in scene.nodes) {
        if (node.mesh < 0 || node.mesh >= length(model.meshes)) {
            continue
        }
        if (node.skin >= 0 && node.skin < length(scene.skins)) {
            bind_skin_palette(scene, node.skin, root)
            u_skinned = 1.0
            u_model = identity4x4()   // skinned path blends the (root-baked) palette; u_model is unused
            u_normal_matrix = identity3x3()   // unused in the skinned branch
        } else {
            u_skinned = 0.0
            u_model = root * node.world
            u_normal_matrix = float3x3(transpose(inverse(u_model)))
        }
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
