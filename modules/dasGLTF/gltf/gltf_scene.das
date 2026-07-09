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

//! Evaluate an animation at time `t` (seconds), writing sampled TRS into the
//! target nodes' local transforms. M3 fills the body.
[unused_argument(scene), unused_argument(animation), unused_argument(t)]
def evaluate_animation(var scene : GltfScene; animation : int; t : float) {
    // M3: per-channel keyframe sampling (STEP/LINEAR/CUBICSPLINE) + quat_slerp.
}
