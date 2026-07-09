options gen2
options indenting = 4

module gltf_scene shared

require gltf/gltf_types
require math

def private update_node_world(var scene : GltfScene; ni : int; parent : float4x4) {
    if (ni < 0 || ni >= length(scene.nodes)) return
    scene.nodes[ni].world = parent * scene.nodes[ni].local
    let w = scene.nodes[ni].world
    for (c in scene.nodes[ni].children) {
        update_node_world(scene, c, w)
    }
}

//! Recompute every node's `world` transform by walking the hierarchy from the
//! scene roots (world = parent.world * local).
def update_world_transforms(var scene : GltfScene) {
    let id = identity4x4()
    for (r in scene.roots) {
        update_node_world(scene, r, id)
    }
}

//! World-space axis-aligned bounds (min, max) over every mesh vertex, using each node's `world`
//! transform. Returns (0, 0) for a scene with no drawable vertices. Handy for auto-framing a camera.
def gltf_scene_bounds(scene : GltfScene) : tuple<float3; float3> {
    var lo = float3(1.0e30, 1.0e30, 1.0e30)
    var hi = float3(-1.0e30, -1.0e30, -1.0e30)
    var any = false
    for (node in scene.nodes) {
        if (node.mesh < 0 || node.mesh >= length(scene.meshes)) {
            continue
        }
        for (prim in scene.meshes[node.mesh].primitives) {
            for (v in prim.vertices) {
                let wp = (node.world * float4(v.position, 1.0)).xyz
                lo = min(lo, wp)
                hi = max(hi, wp)
                any = true
            }
        }
    }
    if (!any) {
        return (float3(0., 0., 0.), float3(0., 0., 0.))
    }
    return (lo, hi)
}

//! Evaluate an animation at time `t` (seconds), writing sampled TRS into the
//! target nodes' local transforms. M3 fills the body.
[unused_argument(scene), unused_argument(animation), unused_argument(t)]
def evaluate_animation(var scene : GltfScene; animation : int; t : float) {
    // M3: per-channel keyframe sampling (STEP/LINEAR/CUBICSPLINE) + quat_slerp.
}
