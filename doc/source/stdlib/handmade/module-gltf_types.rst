dasGLTF loads `glTF 2.0 <https://www.khronos.org/gltf/>`_ models — ``.glb`` (binary),
``.gltf`` (JSON), external or base64-embedded buffers — into a **backend-neutral scene**,
with no new native code (it builds on ``json_boost``, ``base64``, ``fio``, ``stbimage`` and
``math``).

The backend-neutral core parses, decodes accessors, builds the node hierarchy, and evaluates
skinning and keyframe animation with **no OpenGL or Vulkan dependency** — usable headless for
tooling or a future renderer. Require it with:

.. code-block:: das

    require gltf/gltf_boost

An opt-in OpenGL adapter (``gltf/gltf_gl`` + ``gltf/gltf_pbr``, requiring ``dasOpenGL`` /
``dasGlsl``) maps a loaded scene to GL buffers and renders it with a Cook-Torrance
metallic-roughness PBR shader; it is documented with the OpenGL examples, not here.

The scene model
^^^^^^^^^^^^^^^

:ref:`load_gltf <function-gltf_parse_load_gltf_string>` returns a
:ref:`GltfScene <struct-gltf_types-GltfScene>`, which aggregates the meshes, materials,
textures, images, samplers, nodes, skins and animations of the default scene. Geometry is
decoded to a fixed :ref:`GltfVertex <struct-gltf_types-GltfVertex>` layout (position, normal,
tangent, two UV sets, color, and joints/weights decoded to ``float4``), so interleaved,
normalized and integer-lane attributes need no downstream handling.

.. code-block:: das

    require gltf/gltf_boost

    var scene <- load_gltf("model.glb")
    update_world_transforms(scene)              // fill GltfNode.world from the hierarchy
    let (mn, mx) = gltf_scene_bounds(scene)     // world-space AABB for auto-framing

Animation and skinning
^^^^^^^^^^^^^^^^^^^^^^

:ref:`evaluate_animation <function-gltf_scene_evaluate_animation_GltfScene_int_float>` samples
one animation at a time ``t`` (STEP / LINEAR / CUBICSPLINE), writes the result into each target
node's TRS, and refreshes the world transforms.
:ref:`gltf_joint_matrix <function-gltf_scene_gltf_joint_matrix_GltfScene_int_int>` returns the
per-joint skinning matrix (``jointNode.world * inverseBind[j]``) that deforms skinned geometry.
Morph targets and saving/export are out of scope.
