options gen2
options indenting = 4

module gltf_types shared

require math

// ===== Vertex / mesh =====

struct GltfVertex {
    position : float3
    normal   : float3
    tangent  : float4        // xyz = tangent, w = handedness sign
    uv0      : float2
    uv1      : float2
    color0   : float4 = float4(1., 1., 1., 1.)
    joints0  : float4        // joint indices, decoded to float at parse time
    weights0 : float4
}

enum GltfPrimitiveMode {
    points
    lines
    triangles
}

struct GltfPrimitive {
    vertices : array<GltfVertex>
    indices  : array<uint>
    material : int = -1       // GltfScene.materials index, -1 = default
    mode     : GltfPrimitiveMode = GltfPrimitiveMode.triangles
}

struct GltfMesh {
    name       : string
    primitives : array<GltfPrimitive>
}

// ===== Materials / textures =====

enum GltfAlphaMode {
    opaque
    mask
    blend
}

struct GltfMaterial {
    name              : string
    baseColorFactor   : float4 = float4(1., 1., 1., 1.)
    emissiveFactor    : float3
    metallicFactor    : float = 1.
    roughnessFactor   : float = 1.
    baseColorTex      : int = -1     // GltfScene.textures index, -1 = none
    metalRoughTex     : int = -1
    normalTex         : int = -1
    occlusionTex      : int = -1
    emissiveTex       : int = -1
    normalScale       : float = 1.
    occlusionStrength : float = 1.
    alphaMode         : GltfAlphaMode = GltfAlphaMode.opaque
    alphaCutoff       : float = 0.5
    doubleSided       : bool = false
}

struct GltfImage {
    width, height : int
    pixels : array<uint8>            // decoded RGBA8, rows top-to-bottom
}

struct GltfSampler {
    wrapS, wrapT : int               // glTF sampler wrap enum (10497 = REPEAT default)
    minFilter, magFilter : int
}

struct GltfTexture {
    image   : int = -1               // GltfScene.images index
    sampler : int = -1               // GltfScene.samplers index, -1 = default sampler
}

// ===== Node hierarchy / skins / animation =====

struct GltfNode {
    name        : string
    translation : float3
    rotation    : float4 = float4(0., 0., 0., 1.)   // quaternion xyzw
    scale       : float3 = float3(1., 1., 1.)
    children    : array<int>
    mesh        : int = -1           // GltfScene.meshes index
    skin        : int = -1           // GltfScene.skins index
    local       : float4x4           // local transform (from TRS or matrix)
    world       : float4x4           // world transform (filled by update_world_transforms)
}

struct GltfSkin {
    joints      : array<int>         // node indices
    inverseBind : array<float4x4>    // one per joint
    skeleton    : int = -1           // common root node, -1 = unspecified
}

enum GltfInterp {
    step
    linear
    cubicspline
}

enum GltfPath {
    translation
    rotation
    scale
    weights
}

struct GltfAnimSampler {
    input  : array<float>            // keyframe times (seconds)
    output : array<float4>           // values, vec-packed (T/S use xyz, R uses xyzw)
    interp : GltfInterp = GltfInterp.linear
}

struct GltfAnimChannel {
    sampler    : int = -1            // GltfAnimation.samplers index
    targetNode : int = -1
    targetPath : GltfPath = GltfPath.translation
}

struct GltfAnimation {
    name     : string
    samplers : array<GltfAnimSampler>
    channels : array<GltfAnimChannel>
    duration : float                 // max keyframe time across samplers
}

// ===== Scene =====

struct GltfScene {
    meshes     : array<GltfMesh>
    materials  : array<GltfMaterial>
    textures   : array<GltfTexture>
    images     : array<GltfImage>
    samplers   : array<GltfSampler>
    nodes      : array<GltfNode>
    roots      : array<int>          // top-level node indices of the default scene
    skins      : array<GltfSkin>
    animations : array<GltfAnimation>
}
