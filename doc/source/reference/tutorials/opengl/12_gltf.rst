12 - glTF PBR Capstone
======================

The ladder's finale, and the one rung that loads a real production asset. Every prior
rung generated its geometry procedurally or read a Wavefront OBJ; this one loads a
**glTF 2.0** model -- Khronos's runtime 3D format -- and renders it with the whole modern
pipeline the earlier rungs built. It is where the series' two heaviest rungs meet: tutorial
10's **deferred shading** (a multi-target G-buffer + shadow map + SSAO) and tutorial 11's
**HDR float target + Karis bloom + ACES tonemap**, applied together to a textured PBR mesh.

The model is **BoomBox** (CC0, from the Khronos sample set): a portable stereo with a full
metallic-roughness material set -- base colour, metal-rough, tangent-space normal, occlusion,
and an **emissive** display. That emissive map is the point of pairing the two rungs: the
glowing panel carries above-1.0 intensity into the HDR target and blooms, exactly like rung
11's emissive cubes, but now driven by a real texture on a real mesh.

.. literalinclude:: ../../../../../tutorials/opengl/12_gltf/12_gltf.das
   :language: das
   :start-at: geometry pass: vertex layout

Loading a glTF model
--------------------

The whole asset side is the ``dasGLTF`` module -- a pure-daslang glTF 2.0 loader. Two calls
do everything::

    require gltf/gltf_boost   // the backend-neutral parser + scene
    require gltf/gltf_gl      // the OpenGL adapter

    g_scene <- load_gltf(MODEL)       // .glb -> backend-agnostic GltfScene
    g_model <- upload_gltf(g_scene)   // GltfScene -> GL buffers + textures

``load_gltf`` parses the ``.glb`` container (a 12-byte header plus JSON and binary chunks),
decodes every accessor honouring its component type, stride, and sparse encoding, builds the
node hierarchy into world matrices, and decodes the embedded images -- all in daslang, no
native code. ``upload_gltf`` then turns that neutral scene into GL objects: one VAO/VBO/EBO
per primitive (the vertex layout is ``GltfGlVertex`` -- position / normal / tangent / uv at
``@location`` 0..3, which is exactly what this tutorial's geometry vertex shader reads), and
one GL texture per glTF texture -- **sRGB** internal format for base-colour and emissive maps
(so the hardware decodes them to linear on sample) and **linear** for metal-rough, normal, and
occlusion, all mipmapped with the glTF sampler's wrap and filter. An absent map folds to a 1x1
white or flat-normal default, so every sampler is always valid.

The tutorial never touches a vertex or a pixel by hand. To draw, it walks ``scene.nodes``,
sets ``u_model = root * node.world`` per node, binds each primitive's material factors and
resolved textures (``gltf_gl_resolve_tex``), and issues ``gltf_gl_draw_primitive``. A small
``root`` transform, computed once from ``gltf_scene_bounds``, normalises the model to about two
units tall with its base on the floor -- BoomBox is modelled at ~0.02 m, so without this it
would be a speck. (This rung renders **static** models; skinned glTF animation is shown by the
standalone dasGLTF animation example.)

The G-buffer: four targets for PBR
----------------------------------

Rung 10's G-buffer had three attachments for a Blinn-Phong surface. A metallic-roughness
surface needs more channels, so the geometry pass writes **four**:

* attachment 0 -- ``GL_RGBA8``: albedo in ``.rgb``, baked occlusion in ``.a``;
* attachment 1 -- ``GL_RGBA16F``: world-space (normal-mapped) normal in ``.xyz``, roughness in ``.a``;
* attachment 2 -- ``GL_RGBA16F``: world-space position in ``.xyz``, metallic in ``.a``;
* attachment 3 -- ``GL_RGBA16F``: raw emissive in ``.rgb``.

Signed normals, out-of-``[0, 1]`` positions, and above-one emissive (a material's
``emissiveFactor`` may exceed 1) all need the float format; only albedo fits in 8-bit. WebGL2
guarantees at least four draw buffers, so ``glDrawBuffers(4, ...)`` enables
all of them and the geometry fragment shader's four ``@out @location = N`` writes land in one
draw. As in rung 10, the ``@location`` on a fragment output is load-bearing: GLSL ES 3.00
requires an explicit ``layout(location = N)`` on every output once there is more than one.

The geometry fragment shader samples the glTF material exactly as a forward PBR shader would --
base colour (already linear, from the sRGB texture), metal-rough, occlusion, emissive, and a
tangent-space normal perturbed with the mesh's tangent frame -- but instead of lighting the
surface it *stores* those values across the four targets. The procedural floor takes the same
program down a ``u_material`` branch, writing a plain rough dielectric.

Deferred PBR lighting
---------------------

The lighting pass is fullscreen: it reads the four G-buffer targets plus the SSAO and shadow
buffers, reconstructs each surface, and runs **Cook-Torrance GGX** -- the same metallic-roughness
BRDF the dasGLTF forward shader uses, shared here between one shadowed directional sun and three
orbiting coloured point lights. Because the material work already happened in the geometry pass,
each of those lights is just a cheap add over the screen -- the deferred dividend, now over a real
PBR surface.

Ambient is hemisphere sky blended with the tutorial-10 HDR **image-based lighting**: the
equirectangular environment sampled along the normal for diffuse and along the reflected view
vector for a Fresnel-weighted specular. That IBL specular is what gives BoomBox's chrome antenna
and glossy dome real reflections -- without it, metallic surfaces (which have almost no diffuse)
would read as black. Both the baked occlusion and the SSAO factor modulate the ambient term.

The whole result is written **linear** into an ``RGBA16F`` HDR target -- no gamma here. That is
the join with rung 11: the sun and lights stay in physical range, and the emissive display,
multiplied by ``EMISSIVE_BOOST``, lands well above 1.0.

Emissive into bloom, then tonemap
---------------------------------

From the HDR target the frame runs rung 11's bloom pyramid unchanged: a soft-knee **bright
pass** with the Karis ``1/(1+luma)`` weight isolates the above-1.0 pixels (here, the emissive
display), a 5-tap **downsample** builds the mip chain, a 9-tap **tent upsample** additively
widens the glow, and the **composite** adds the bloom back onto the HDR scene, ACES-tonemaps the
sum into ``[0, 1]``, and gamma-encodes for the display. The glowing panel becomes a real light
source, its halo built from a float render target -- the same technique rung 11 proved on cubes,
now on a boombox.

The six passes
--------------

1. **Shadow** -- depth-only from the sun's point of view (the tutorial-08 pattern).
2. **Geometry** -- the glTF model + floor into the four-attachment G-buffer.
3. **SSAO** -- a hemisphere-kernel occlusion factor from the G-buffer normal + position,
   then a depth-aware (bilateral) separable Gaussian blur. The kernel is rotated per pixel,
   so the raw factor is noisy; the blur smooths it while the view-space depth weight stops the
   occlusion bleeding across a silhouette edge into the background.
4. **Lighting** -- deferred Cook-Torrance PBR + shadow + SSAO + IBL + emissive, into the HDR target.
5. **Bloom** -- bright / downsample x4 / upsample x4 over the HDR target.
6. **Composite** -- add bloom, ACES-tonemap, gamma-encode, to the screen.

Loading external assets in the browser
--------------------------------------

Like rung 10, this tutorial reads files from disk -- ``BoomBox.glb`` and the HDR environment
map -- with plain ``fopen`` underneath ``load_gltf`` and ``stbi_loadf``, byte-identical on
desktop and web. In the browser the in-memory filesystem starts empty, so the playground fetches
the files listed in the sidecar manifest (``gl_12_gltf.das.assets.json``) into the virtual
filesystem at the exact paths the tutorial expects before it runs. The daslang code never changes.

Run it
------

Locally, in a window::

    daslang tutorials/opengl/12_gltf/12_gltf.das

In the browser, it runs live in the daslang playground -- the same ``.das``, lowered to WebGL2,
with BoomBox and the HDR environment fetched into the virtual filesystem first: a real glTF PBR
model on a shadowed floor, lit by a sun and three drifting coloured lights, its emissive display
glowing through a real bloom built from a float render target on your GPU. The whole ladder, in
one frame.
