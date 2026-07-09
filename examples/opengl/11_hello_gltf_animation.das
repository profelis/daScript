options gen2
require glfw/glfw_boost
require opengl/opengl_boost
require gltf/gltf_boost
require gltf/gltf_gl
require gltf/gltf_pbr
require daslib/defer
require math
require daslib/math_boost
require strings

// dasGLTF — skinned glTF animation viewer (OpenGL). Loads a rigged, animated .glb, uploads it to GL, and
// plays back its keyframe animation with GPU skinning under the same PBR shader as 10_hello_gltf. Orbit
// camera (drag to rotate, scroll to zoom); SPACE cycles animation clips. Defaults to the shipped Fox
// (3 clips: Survey / Walk / Run); pass a path as argv[1] for another rigged model.

def model_path : string {
    // get_command_line_arguments() includes the interpreter + script path, so pick the first
    // argument that actually names a glTF file; otherwise fall back to the shipped Fox.
    for (a in get_command_line_arguments()) {
        if (ends_with(a, ".glb") || ends_with(a, ".gltf")) {
            return a
        }
    }
    return "{get_das_root()}/examples/gltf/media/Fox.glb"
}

[export]
def main {
    if (glfwInit() == 0) {
        panic("can't init glfw")
    }
    defer() {
        glfwTerminate()
    }
    glfwInitOpenGL(3, 3)
    var window = glfwCreateWindow(1280, 720, "dasGLTF - Hello glTF Animation", null, null)
    if (window == null) {
        panic("can't create window")
    }
    defer() {
        glfwDestroyWindow(window)
    }
    glfwMakeContextCurrent(window)

    let path = model_path()
    var scene <- load_gltf(path)
    defer() {
        delete scene
    }
    if (empty(scene.meshes)) {
        panic("no meshes loaded from {path}")
    }
    var model <- upload_gltf(scene)
    defer() {
        delete model
    }
    var renderer <- gltf_pbr_create()
    defer() {
        delete renderer
    }

    // auto-frame: orbit the world-space bounding sphere so any model (Fox is ~80 units) fills the view
    let bounds = gltf_scene_bounds(scene)
    let center = (bounds._0 + bounds._1) * 0.5
    let radius = max(length(bounds._1 - bounds._0) * 0.5, 0.001)

    var camera_distance = radius * 2.2
    var camera_yaw = 0.9
    var camera_pitch = 0.25
    var cursor_prev = glfwGetCursorPos(window)
    var dragging = false
    let light = GltfPbrLight()

    // animation playback state: cycle clips with SPACE; time advances per frame and loops per clip duration
    let anim_count = length(scene.animations)
    var clip_index = 0
    var anim_time = 0.0
    var last_time = glfwGetTime()
    if (anim_count > 0) {
        print("dasGLTF: {anim_count} animation clip(s); press SPACE to cycle. Playing '{scene.animations[0].name}'\n")
    } else {
        print("dasGLTF: '{path}' has no animation clips; showing the static mesh.\n")
    }

    unsafe {
        glfwSetKeyCallback(window) @ capture(& clip_index, & anim_time, = anim_count) (w, key, scancode, action, mods) {
            if (key == int(GLFW_KEY_SPACE) && action == int(GLFW_PRESS) && anim_count > 0) {
                clip_index = (clip_index + 1) % anim_count
                anim_time = 0.0
            }
        }
        glfwSetScrollCallback(window) @ capture(& camera_distance, & radius) (w, x, y) {
            camera_distance = clamp(camera_distance * (y > 0.0lf ? 0.9 : 1.1), radius * 1.1, radius * 40.0)
        }
        glfwSetMouseButtonCallback(window) @ capture(& dragging, & cursor_prev) (w, b, a, m) {
            if (b == int(GLFW_MOUSE_BUTTON_1)) {
                dragging = a == int(GLFW_PRESS)
                cursor_prev = glfwGetCursorPos(window)
            }
        }
        glfwSetCursorPosCallback(window) @ capture(& dragging, & cursor_prev, & camera_yaw, & camera_pitch) (w, x, y) {
            let cur = glfwGetCursorPos(window)
            if (dragging) {
                let d = cur - cursor_prev
                camera_yaw -= float(d.x) * 0.01
                camera_pitch = clamp(camera_pitch + float(d.y) * 0.01, -1.5, 1.5)
            }
            cursor_prev = cur
        }
    }

    eval_main_loop() {
        if (glfwWindowShouldClose(window) != 0) {
            return false
        }
        glfwPollEvents()

        // advance + loop the active animation clip, then pose the skeleton for this frame
        let now = glfwGetTime()
        anim_time += float(now - last_time)
        last_time = now
        if (anim_count > 0) {
            let dur = scene.animations[clip_index].duration
            if (dur > 0.0 && anim_time >= dur) {
                anim_time -= dur * floor(anim_time / dur)
            }
            evaluate_animation(scene, clip_index, anim_time)
        }

        var display_w, display_h : int
        glfwGetFramebufferSize(window, display_w, display_h)
        let aspect = display_h != 0 ? float(display_w) / float(display_h) : 1.

        let cp = cos(camera_pitch)
        let eye = center + float3(cp * sin(camera_yaw), sin(camera_pitch), cp * cos(camera_yaw)) * camera_distance
        let view = look_at_rh(eye, center, float3(0., 1., 0.))
        let proj = perspective_rh_minus1_to_1(45.0f * PI / 180., aspect, radius * 0.05, radius * 60.0)

        glViewport(0, 0, display_w, display_h)
        glClearColor(0.10, 0.10, 0.12, 1.0)
        glClearDepth(1.0lf)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)
        glDepthFunc(GL_LESS)

        gltf_pbr_render(renderer, model, scene, view, proj, eye, light)

        glfwMakeContextCurrent(window)
        glfwSwapBuffers(window)
        return true
    }
}
