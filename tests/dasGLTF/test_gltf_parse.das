options gen2
options indenting = 4

require dastest/testing_boost public
require gltf/gltf_boost

// M0 smoke: proves the module require chain compiles/loads and the public API is
// callable. Real parse asserts (Box / BoxInterleaved / SimpleSkin) land in M1.

[test]
def test_gltf_module_loads(t : T?) {
    t |> run("empty scene is empty") @(t : T?) {
        var scene <- load_gltf("nonexistent.gltf")
        t |> equal(length(scene.meshes), 0)
        t |> equal(length(scene.nodes), 0)
    }
}
