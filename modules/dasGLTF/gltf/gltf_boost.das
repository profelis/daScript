options gen2
options indenting = 4

module gltf_boost shared

// Backend-neutral glTF core. Require this for headless use (parsing, the agnostic
// scene, node/skin/animation evaluation) with no OpenGL/Vulkan dependency.
// The GL adapter lives in gltf/gltf_gl (added in M2) and requires this transitively.

require gltf/gltf_types public
require gltf/gltf_accessor public
require gltf/gltf_parse public
require gltf/gltf_scene public
