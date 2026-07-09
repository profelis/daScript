options gen2
options indenting = 4

module gltf_parse shared

require gltf/gltf_types
require gltf/gltf_accessor
require daslib/json_boost
require daslib/base64
require daslib/fio
require stbimage/stbimage_boost
require strings

//! Load a glTF 2.0 file (.gltf or .glb) into a backend-agnostic `GltfScene`.
//! Returns an empty scene on failure (M0 skeleton — real parse lands in M1).
def load_gltf(path : string) : GltfScene {
    var scene : GltfScene
    // M1: GLB/.gltf container parse, buffer/image resolution, accessor decode,
    //     node hierarchy. Placeholder for now.
    return <- scene
}
