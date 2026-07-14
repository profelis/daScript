options gen2
options indenting = 4
options no_unused_block_arguments = false
options no_unused_function_arguments = false

module gltf_gl shared

require gltf/gltf_types
require opengl/opengl_boost public
require daslib/safe_addr
require stbimage
require math

// OPT-IN OpenGL adapter: uploads a backend-agnostic GltfScene to GL buffers + textures.
// The neutral core (gltf_types/gltf_accessor/gltf_parse/gltf_scene) never requires opengl;
// requiring THIS module is what pulls GL in. gltf_pbr renders a GltfGlModel with the PBR shader.

// GL vertex layout. Field ORDER is the attribute-location contract with gltf_pbr's vertex
// shader (@location 0..7). The uploader copies each gltf_types::GltfVertex into one of these,
// so this struct — not GltfVertex — owns the GL stride/offsets that bind_vertex_buffer emits.
[vertex_buffer]
struct private GltfGlVertex {
    position : float3     // @location 0
    normal   : float3     // @location 1
    tangent  : float4     // @location 2  (xyz + handedness w)
    uv0      : float2     // @location 3
    uv1      : float2     // @location 4
    color0   : float4     // @location 5
    joints0  : float4     // @location 6
    weights0 : float4     // @location 7
}

struct GltfGlPrimitive {
    vao, vbo, ebo : uint
    indexCount    : int
    mode          : uint      // GL_TRIANGLES / GL_LINES / GL_POINTS
    material      : int = -1  // GltfScene.materials index, -1 = default
}

struct GltfGlMesh {
    primitives : array<GltfGlPrimitive>
}

struct GltfGlModel {
    meshes        : array<GltfGlMesh>   // parallel to GltfScene.meshes
    textures      : array<uint>         // GL handle per GltfScene.textures entry (0 = missing)
    whiteTex      : uint                // 1x1 opaque white — base-color/metal-rough/occlusion/emissive default
    flatNormalTex : uint                // 1x1 (0.5,0.5,1) — tangent-space "no perturbation" normal default
}

// ===== helpers =====

def private gl_mode(m : GltfPrimitiveMode) : uint {
    if (m == GltfPrimitiveMode.points) return GL_POINTS
    if (m == GltfPrimitiveMode.lines) return GL_LINES
    return GL_TRIANGLES
}

// glTF sampler wrap enum -> GL. 10497 REPEAT (default), 33071 CLAMP_TO_EDGE, 33648 MIRRORED_REPEAT.
def private gl_wrap(w : int) : uint {
    if (w == 33071) return GL_CLAMP_TO_EDGE
    if (w == 33648) return GL_MIRRORED_REPEAT
    return GL_REPEAT
}

// glTF minFilter enum -> GL. 0 (unspecified) defaults to trilinear since we always build mipmaps.
def private gl_min_filter(f : int) : uint {
    if (f == 9728) return GL_NEAREST
    if (f == 9729) return GL_LINEAR
    if (f == 9984) return GL_NEAREST_MIPMAP_NEAREST
    if (f == 9985) return GL_LINEAR_MIPMAP_NEAREST
    if (f == 9986) return GL_NEAREST_MIPMAP_LINEAR
    if (f == 9987) return GL_LINEAR_MIPMAP_LINEAR
    return GL_LINEAR_MIPMAP_LINEAR
}

def private gl_mag_filter(f : int) : uint {
    if (f == 9728) return GL_NEAREST
    return GL_LINEAR
}

// Upload a decoded RGBA8 image as a 2D texture. `srgb` picks the internal format so base-color /
// emissive maps are sampled with hardware sRGB->linear decode while normal / metal-rough / occlusion
// stay linear. Mipmaps are always generated; wrap/filter come from the glTF sampler.
def private create_gl_texture(img : GltfImage; sampler : GltfSampler; srgb : bool) : uint {
    if (img.width <= 0 || img.height <= 0 || empty(img.pixels)) return 0u
    var tex : uint
    glGenTextures(1, safe_addr(tex))
    glBindTexture(GL_TEXTURE_2D, tex)
    let internal = int(srgb ? GL_SRGB8_ALPHA8 : GL_RGBA8)
    // decoded rows are tightly packed RGBA8; force 1-byte unpack alignment and restore it after
    var prev_align : int
    glGetIntegerv(GL_UNPACK_ALIGNMENT, safe_addr(prev_align))
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1)
    unsafe {
        glTexImage2D(GL_TEXTURE_2D, 0, internal, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
            addr<void const?>(img.pixels[0]))
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, prev_align)
    glGenerateMipmap(GL_TEXTURE_2D)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl_wrap(sampler.wrapS))
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl_wrap(sampler.wrapT))
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_min_filter(sampler.minFilter))
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_mag_filter(sampler.magFilter))
    glBindTexture(GL_TEXTURE_2D, 0u)
    return tex
}

// A 1x1 linear-space RGBA texture used as a fold-in default for an absent material map.
def private create_solid_texture(r, g, b, a : uint) : uint {
    var tex : uint
    glGenTextures(1, safe_addr(tex))
    glBindTexture(GL_TEXTURE_2D, tex)
    var px = [uint8(r), uint8(g), uint8(b), uint8(a)]
    unsafe {
        glTexImage2D(GL_TEXTURE_2D, 0, int(GL_RGBA8), 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE,
            addr<void const?>(px[0]))
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glBindTexture(GL_TEXTURE_2D, 0u)
    delete px
    return tex
}

// A texture is sampled in sRGB space iff a material references it as base-color or emissive; every
// other slot (normal / metal-rough / occlusion) is linear. A texture used in both roles reads sRGB.
def private mark_srgb(scene : GltfScene) : array<bool> {
    var srgb : array<bool>
    srgb |> resize(length(scene.textures))
    for (m in scene.materials) {
        if (m.baseColorTex >= 0 && m.baseColorTex < length(srgb)) { srgb[m.baseColorTex] = true }
        if (m.emissiveTex >= 0 && m.emissiveTex < length(srgb)) { srgb[m.emissiveTex] = true }
    }
    return <- srgb
}

def private upload_primitive(prim : GltfPrimitive) : GltfGlPrimitive {
    var glp = GltfGlPrimitive(material = prim.material, mode = gl_mode(prim.mode),
        indexCount = length(prim.indices))
    var verts : array<GltfGlVertex>
    verts |> resize(length(prim.vertices))
    for (i in range(length(prim.vertices))) {
        let v = prim.vertices[i]
        verts[i] = GltfGlVertex(position = v.position, normal = v.normal, tangent = v.tangent,
            uv0 = v.uv0, uv1 = v.uv1, color0 = v.color0, joints0 = v.joints0, weights0 = v.weights0)
    }
    with (glp) {
        glGenVertexArrays(1, safe_addr(vao))
        glBindVertexArray(vao)
        glGenBuffers(1, safe_addr(vbo))
        glBindBuffer(GL_ARRAY_BUFFER, vbo)
        glBufferData(GL_ARRAY_BUFFER, verts, GL_STATIC_DRAW)
        bind_vertex_buffer(null, type<GltfGlVertex>)
        glGenBuffers(1, safe_addr(ebo))
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo)
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, prim.indices, GL_STATIC_DRAW)
    }
    glBindVertexArray(0u)
    delete verts
    return glp
}

// ===== public API =====

//! Upload a parsed GltfScene to GL: per-primitive VAO/VBO/EBO, one GL texture per glTF texture
//! (sRGB / linear per usage, mipmapped, sampler wrap/filter), plus white / flat-normal defaults.
//! Call with a current GL context. `delete` the returned model to release every GL object.
def upload_gltf(scene : GltfScene) : GltfGlModel {
    var model = GltfGlModel()
    model.meshes |> reserve(length(scene.meshes))
    for (mesh in scene.meshes) {
        var glmesh = GltfGlMesh()
        glmesh.primitives |> reserve(length(mesh.primitives))
        for (prim in mesh.primitives) {
            glmesh.primitives |> emplace(upload_primitive(prim))
        }
        model.meshes |> emplace(glmesh)
    }
    var srgb <- mark_srgb(scene)
    model.textures |> resize(length(scene.textures))
    for (ti in range(length(scene.textures))) {
        let t = scene.textures[ti]
        if (t.image < 0 || t.image >= length(scene.images)) { continue }
        let smp = (t.sampler >= 0 && t.sampler < length(scene.samplers)
            ? scene.samplers[t.sampler]
            : GltfSampler(wrapS = 10497, wrapT = 10497))
        model.textures[ti] = create_gl_texture(scene.images[t.image], smp, srgb[ti])
    }
    delete srgb
    model.whiteTex = create_solid_texture(255u, 255u, 255u, 255u)
    model.flatNormalTex = create_solid_texture(128u, 128u, 255u, 255u)
    return <- model
}

def gltf_gl_load_hdr_env(path : string) : tuple<uint; float> {
    //! Load an equirectangular (2:1 lat-long) HDR image as a mipmapped RGB16F texture for
    //! gltf_pbr_set_environment. Returns (texture, max mip lod); (0, 0) if it fails to load.
    //! The caller owns the texture (glDeleteTextures when done).
    var x, y, comp : int
    let data = stbi_loadf(path, safe_addr(x), safe_addr(y), safe_addr(comp), 3)
    if (data == null) {
        to_log(LOG_ERROR, "gltf: HDR environment load failed: {path}\n")
        return (0u, 0.0)
    }
    if (x <= 0 || y <= 0) {
        // fail closed on a decodable-but-degenerate image: glTexImage2D and log2 below
        // both assume positive dimensions
        stbi_image_free(unsafe(reinterpret<void?>(data)))
        to_log(LOG_ERROR, "gltf: HDR environment has invalid dimensions {x}x{y}: {path}\n")
        return (0u, 0.0)
    }
    var tex : uint
    glGenTextures(1, safe_addr(tex))
    glBindTexture(GL_TEXTURE_2D, tex)
    glTexImage2D(GL_TEXTURE_2D, 0, int(GL_RGB16F), x, y, 0, GL_RGB, GL_FLOAT, unsafe(reinterpret<void?>(data)))
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)             // longitude wraps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)      // latitude clamps at the poles
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glGenerateMipmap(GL_TEXTURE_2D)                                          // mips = prefiltered roughness levels
    stbi_image_free(unsafe(reinterpret<void?>(data)))
    return (tex, floor(log2(float(max(x, y)))))
}

//! GL texture handle for a GltfScene.textures index, or `fallback` when the index is out of range
//! or the texture had no decodable image. gltf_pbr uses this to fold absent maps to white / flat-normal.
def gltf_gl_resolve_tex(model : GltfGlModel; texIndex : int; fallback : uint) : uint {
    if (texIndex < 0 || texIndex >= length(model.textures)) return fallback
    let h = model.textures[texIndex]
    return h != 0u ? h : fallback
}

//! Bind a primitive's VAO and issue its indexed draw. The caller binds the program, uniforms and
//! textures first (gltf_pbr does this per node/material).
def gltf_gl_draw_primitive(glp : GltfGlPrimitive) {
    glBindVertexArray(glp.vao)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glp.ebo)
    glDrawElements(glp.mode, glp.indexCount, GL_UNSIGNED_INT, null)
}

def finalize(var model : GltfGlModel) {
    for (mesh in model.meshes) {
        for (glp in mesh.primitives) {
            var vao = glp.vao
            var vbo = glp.vbo
            var ebo = glp.ebo
            if (vao != 0u) { glDeleteVertexArrays(1, safe_addr(vao)) }
            if (vbo != 0u) { glDeleteBuffers(1, safe_addr(vbo)) }
            if (ebo != 0u) { glDeleteBuffers(1, safe_addr(ebo)) }
        }
    }
    for (t in model.textures) {
        var tt = t
        if (tt != 0u) { glDeleteTextures(1, safe_addr(tt)) }
    }
    if (model.whiteTex != 0u) {
        var w = model.whiteTex
        glDeleteTextures(1, safe_addr(w))
    }
    if (model.flatNormalTex != 0u) {
        var f = model.flatNormalTex
        glDeleteTextures(1, safe_addr(f))
    }
    delete model.meshes
    delete model.textures
}
