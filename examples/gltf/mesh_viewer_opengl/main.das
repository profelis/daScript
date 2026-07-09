options gen2
options indenting = 4
options persistent_heap = true
options _allow_glfw_calls = true

require imgui/imgui_harness
require imgui/imgui_live
require opengl/opengl_boost
require live/glfw_live
require gltf/gltf_boost
require gltf/gltf_gl
require gltf/gltf_pbr
require daslib/safe_addr
require daslib/fio
require math
require daslib/math_boost
require strings

// dasGLTF mesh viewer (OpenGL + Dear ImGui). Loads a .glb/.gltf, orbits it under the metallic-roughness
// PBR shader, and exposes the model transform, animation playback and lighting through two ImGui windows.
// The 3D is drawn between the GL clear and ImGui's RenderDrawData (a manual harness_end_frame split, like
// furier), so the panels sit on top of the live render. Drag to orbit, scroll to zoom. Defaults to the
// shipped BoomBox (full PBR); pass Fox.glb (or any rigged .glb) as an argument to drive the animation UI.

// ----- viewer state (all main-thread; init() loads, update() drives) -----
var g_scene    : GltfScene
var g_model    : GltfGlModel
var g_renderer : GltfPbrRenderer

var g_center : float3
var g_radius = 1.0f

// orbit camera (mouse drag + scroll, mirrored by no widgets — the viewport owns it)
var g_cam_yaw   = 0.6f
var g_cam_pitch = 0.3f
var g_cam_dist  = 2.2f

// model transform (Model window): euler degrees + uniform scale, applied about the model centre
var g_rot_euler   : float3
var g_scale       = 1.0f
var g_auto_rotate = false

// animation (Model window)
var g_clip       = 0
var g_playing    = true
var g_anim_time  = 0.0f
var g_clip_names : array<string>

// lighting (Lighting window) — flat globals so safe_addr binds a stable top-level address
var g_light_dir       = float3(0.3, 0.7, 0.5)
var g_light_color     = float3(1.0, 1.0, 1.0)
var g_light_intensity = 3.0f
var g_light_ambient   = float3(0.15, 0.15, 0.18)

var g_model_name = ""

def model_path : string {
    // get_command_line_arguments() includes the interpreter + script + harness flags, so pick the first
    // argument that actually names a glTF file; otherwise fall back to the shipped BoomBox.
    for (a in get_command_line_arguments()) {
        if (ends_with(a, ".glb") || ends_with(a, ".gltf")) {
            return a
        }
    }
    return "{get_das_root()}/examples/gltf/media/BoomBox.glb"
}

// T(centre) * R * S * T(-centre): rotate/scale about the model centre so the framed model stays framed.
def model_root_transform : float4x4 {
    let q = quat_from_euler(g_rot_euler * (PI / 180.0f))
    let rs = compose(float3(0.0, 0.0, 0.0), q, float3(g_scale))
    return translation(g_center) * rs * translation(-g_center)
}

def build_ui {
    window(MODEL_WIN, (text = "Model", closable = false, flags = ImGuiWindowFlags.None)) {
        text("{g_model_name}")
        text("meshes {length(g_scene.meshes)}   materials {length(g_scene.materials)}   nodes {length(g_scene.nodes)}")
        separator(SEP_ANIM)
        if (!empty(g_scene.animations)) {
            edit_combo(safe_addr(g_clip), (id = "CLIP", text = "Clip", items = g_clip_names))
            g_clip = clamp(g_clip, 0, length(g_scene.animations) - 1)
            edit_checkbox(safe_addr(g_playing), (id = "PLAY", text = "Play"))
            edit_slider_float(safe_addr(g_anim_time),
                (id = "TIME", text = "Time", v_min = 0.0f, v_max = max(g_scene.animations[g_clip].duration, 0.001f)))
        } else {
            text("(no animations)")
        }
        separator(SEP_XFORM)
        edit_slider_float3(safe_addr(g_rot_euler), (id = "ROT", text = "Rotation", v_min = -180.0f, v_max = 180.0f))
        edit_slider_float(safe_addr(g_scale), (id = "SCALE", text = "Scale", v_min = 0.05f, v_max = 4.0f))
        edit_checkbox(safe_addr(g_auto_rotate), (id = "AUTOROT", text = "Auto-rotate"))
        separator(SEP_HINT)
        text("drag: orbit   scroll: zoom")
    }
    window(LIGHT_WIN, (text = "Lighting", closable = false, flags = ImGuiWindowFlags.None)) {
        edit_slider_float3(safe_addr(g_light_dir), (id = "LDIR", text = "Direction", v_min = -1.0f, v_max = 1.0f))
        edit_slider_float(safe_addr(g_light_intensity), (id = "LINT", text = "Intensity", v_min = 0.0f, v_max = 10.0f))
        edit_color_edit3(safe_addr(g_light_color), (id = "LCOL", text = "Color"))
        edit_color_edit3(safe_addr(g_light_ambient), (id = "LAMB", text = "Ambient"))
    }
}

// Mouse orbit + scroll zoom while the pointer isn't over an ImGui window, then advance/pose the animation.
def update_input_and_anim(dt : float) {
    let io & = unsafe(GetIO())
    if (!io.WantCaptureMouse) {
        if (IsMouseDown(ImGuiMouseButton.Left)) {
            g_cam_yaw += io.MouseDelta.x * 0.01f
            g_cam_pitch = clamp(g_cam_pitch + io.MouseDelta.y * 0.01f, -1.5f, 1.5f)
        }
        if (io.MouseWheel != 0.0f) {
            g_cam_dist = clamp(g_cam_dist * (io.MouseWheel > 0.0f ? 0.9f : 1.1f), g_radius * 1.1f, g_radius * 40.0f)
        }
    }
    if (g_auto_rotate) {
        g_cam_yaw += dt * 0.5f
    }
    let anim_count = length(g_scene.animations)
    if (anim_count > 0) {
        let dur = g_scene.animations[g_clip].duration
        if (g_playing) {
            g_anim_time += dt
        }
        if (dur > 0.0f && g_anim_time >= dur) {
            g_anim_time -= dur * floor(g_anim_time / dur)
        }
        evaluate_animation(g_scene, g_clip, g_anim_time)
    }
}

def draw_scene {
    var w, h : int
    live_get_framebuffer_size(w, h)
    glViewport(0, 0, w, h)
    glClearColor(0.10f, 0.10f, 0.12f, 1.0f)
    glClearDepth(1.0lf)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)
    glDepthFunc(GL_LESS)

    let aspect = h != 0 ? float(w) / float(h) : 1.0f
    let cp = cos(g_cam_pitch)
    let eye = g_center + float3(cp * sin(g_cam_yaw), sin(g_cam_pitch), cp * cos(g_cam_yaw)) * g_cam_dist
    let view = look_at_rh(eye, g_center, float3(0.0, 1.0, 0.0))
    let proj = perspective_rh_minus1_to_1(45.0f * PI / 180.0f, aspect, g_radius * 0.05f, g_radius * 60.0f)
    let light = GltfPbrLight(direction = g_light_dir, color = g_light_color,
        intensity = g_light_intensity, ambient = g_light_ambient)

    gltf_pbr_render(g_renderer, g_model, g_scene, model_root_transform(), view, proj, eye, light)

    // hand a clean state back to the ImGui GL3 backend (it sets up its own, but leave depth/cull/blend off)
    glDisable(GL_DEPTH_TEST)
    glDisable(GL_CULL_FACE)
    glDisable(GL_BLEND)
}

[export]
def init {
    let path = model_path()
    harness_init("dasGLTF Mesh Viewer", 1280, 720)

    g_scene <- load_gltf(path)
    if (empty(g_scene.meshes)) {
        panic("no meshes loaded from {path}")
    }
    g_model <- upload_gltf(g_scene)
    g_renderer <- gltf_pbr_create()

    let bounds = gltf_scene_bounds(g_scene)
    g_center = (bounds._0 + bounds._1) * 0.5f
    g_radius = max(length(bounds._1 - bounds._0) * 0.5f, 0.001f)
    g_cam_dist = g_radius * 2.2f

    g_model_name = base_name(path)
    g_clip_names |> reserve(length(g_scene.animations))
    for (a in g_scene.animations) {
        g_clip_names |> push(empty(a.name) ? "clip {length(g_clip_names)}" : a.name)
    }
}

[export]
def update {
    if (!harness_begin_frame()) {
        return
    }
    harness_new_frame()

    build_ui()
    let io & = unsafe(GetIO())
    update_input_and_anim(io.DeltaTime)
    draw_scene()

    end_of_frame()
    Render()
    live_imgui_render()
    live_end_frame()
}

[export]
def shutdown {
    delete g_renderer
    delete g_model
    delete g_scene
    harness_shutdown()
}

[export]
def main {
    init()
    while (!exit_requested()) {
        update()
    }
    shutdown()
}
