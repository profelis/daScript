options gen2
options indenting = 4

module gltf_scene shared

require gltf/gltf_types
require math

//! Recompute every node's `world` transform by walking the hierarchy from the
//! scene roots (world = parent.world * local). M1 fills the body.
def update_world_transforms(var scene : GltfScene) {
    // M1: recursive walk from scene.roots composing parent.world * node.local.
}

//! Evaluate an animation at time `t` (seconds), writing sampled TRS into the
//! target nodes' local transforms. M3 fills the body.
def evaluate_animation(var scene : GltfScene; animation : int; t : float) {
    // M3: per-channel keyframe sampling (STEP/LINEAR/CUBICSPLINE) + quat_slerp.
}
