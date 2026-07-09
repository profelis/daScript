# dasGLTF Mesh Viewer (OpenGL + Dear ImGui)

An interactive glTF 2.0 viewer built on the in-tree **dasGLTF** module (`modules/dasGLTF`), the
OpenGL adapter (`gltf_gl` / `gltf_pbr`), and **dasImgui** for the UI. It loads a `.glb`/`.gltf`,
frames it automatically, orbits it under the metallic-roughness PBR shader, and drives the model
transform, animation playback and lighting from two ImGui windows.

## Run

dasImgui is an external dependency, pulled via daspkg from this example's `.das_package`:

```sh
# once — installs dasImgui into ./modules (gitignored), built against your daslang SDK
daslang utils/daspkg/main.das -- install --root examples/gltf/mesh_viewer_opengl

# then run the viewer, rooted here so the dasImgui dep resolves
daslang -project_root examples/gltf/mesh_viewer_opengl examples/gltf/mesh_viewer_opengl/main.das
```

Pass a model path to load your own; without one it opens the shipped **BoomBox** (full PBR):

```sh
daslang -project_root examples/gltf/mesh_viewer_opengl \
    examples/gltf/mesh_viewer_opengl/main.das examples/gltf/media/Fox.glb
```

`Fox.glb` exercises the animation UI (3 clips: Survey / Walk / Run).

## Controls

- **Drag** — orbit the camera. **Scroll** — zoom.
- **Model** window — animation clip + play/scrub, model rotation / scale, auto-rotate.
- **Lighting** window — directional light direction / intensity / color, and ambient.
