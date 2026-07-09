options gen2
require glfw/glfw_boost
require opengl/opengl_boost
require gltf/gltf_boost
require gltf/gltf_gl
require gltf/gltf_pbr
require daslib/defer
require math
require daslib/math_boost

// dasGLTF — minimal static glTF viewer (OpenGL). Loads a .glb, uploads it to GL, and renders it with
// the metallic-roughness PBR shader under an orbit camera (drag to rotate, scroll to zoom). Sibling to
// 09_hello_mesh but for full glTF PBR. Defaults to the shipped BoomBox; pass a path as argv[1].

def model_path : string {
    let args = get_command_line_arguments()
    if (length(args) > 1 && !empty(args[1])) {
        return args[1]
    }
    return "{get_das_root()}/examples/gltf/media/BoomBox.glb"
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
    var window = glfwCreateWindow(1280, 720, "dasGLTF - Hello glTF (PBR)", null, null)
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

    // auto-frame: orbit the world-space bounding sphere so any model (BoomBox is ~0.02m) fills the view
    let bounds = gltf_scene_bounds(scene)
    let center = (bounds._0 + bounds._1) * 0.5
    let radius = max(length(bounds._1 - bounds._0) * 0.5, 0.001)

    var camera_distance = radius * 2.2
    var camera_yaw = 0.6
    var camera_pitch = 0.3
    var cursor_prev = glfwGetCursorPos(window)
    var dragging = false
    let light = GltfPbrLight()

    unsafe {
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
                camera_yaw += float(d.x) * 0.01
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
