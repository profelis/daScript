options gen2
options indenting = 4

// ===== 16/8-bit lattice: real-GPU parity gate (MANUAL — see the run book below) =====
//
// Compiles das-authored fragment shaders (the dasGlsl EXT-gated fp16 rail) on a REAL OpenGL
// driver, executes them, reads the result back, and compares BIT-EXACT against the CPU tier
// running the same math (the das fp16 reference semantics are RNE per op — identical to
// native GPU fp16 by the double-rounding safety bound, so exact equality is the correct
// assertion). Lattice values stay shader-internal (f32 uniforms in, f32 color out): failures
// isolate to arithmetic/convert codegen, which is exactly what this gate proves.
//
// RUN BOOK (the gate is zen2-only by construction — macOS GL 4.1 has no
// GL_EXT_shader_explicit_arithmetic_types and this script soft-skips there):
//   ssh zen2
//   cd /d E:\das
//   bin\daslang.exe tests\opengl_gpu\_lattice_gpu_parity.das
// Expect: "LATTICE GPU PARITY: ALL OK (N cases)". Any "MISMATCH" line is a real
// codegen/driver divergence — report it, do not paper over it.
//
// (`_`-prefixed so no automated test walker or AOT glob ever executes it — it needs a live
// GL context and a driver with the EXT family.)

require glfw/glfw_boost
require opengl/opengl_boost
require daslib/shader_lingua_franca
require daslib/safe_addr

// ---- the shader pair (fullscreen quad, fp16 math inside, f32 in/out) ----

var @in @location q_pos : float2
var @uniform u_a : float
var @uniform u_b : float
var @out lp_color : float4

[vertex_program]
def lp_vs {
    gl_Position = float4(q_pos, 0.0, 1.0)
}

[fragment_program]
def lp_fs {
    // fp16 chain: splat-converts, closed arithmetic, converts out — plus the pack bridge
    let a = half4(u_a)
    let b = half4(u_b)
    var m = a * b
    m = m + half4(0.25h)
    m = m - a
    let bits = packHalf2x16(float2(u_a, u_b))
    let up = unpackHalf2x16(bits)
    lp_color = float4(float(m.x), float(m.w), up.x, up.y)
}

// ---- the CPU reference: the SAME math on the CPU lattice tier ----

def cpu_reference(ua, ub : float) : float4 {
    let a = half4(ua)
    let b = half4(ub)
    var m = a * b
    m = m + half4(0.25h)
    m = m - a
    let bits = packHalf2x16(float2(ua, ub))
    let up = unpackHalf2x16(bits)
    return float4(float(m.x), float(m.w), up.x, up.y)
}

// ---- driver-truth probe: compile a minimal EXT fragment; status==0 -> unsupported ----

let PROBE_SRC = "#version 330 core\n#extension GL_EXT_shader_explicit_arithmetic_types_float16 : require\nout vec4 c;\nvoid main() \{ float16_t h = float16_t(1.5); c = vec4(float(h)); \}\n"

def ext_supported : bool {
    return create_shader(PROBE_SRC, GL_FRAGMENT_SHADER, true) != 0u
}

var window : GLFWwindow?
var program : uint
var vao, vbo, fbo, tex : uint

[vertex_buffer]
struct QuadVert {
    xy : float2
}

let quad = [
    QuadVert(xy = float2(-1., -1.)), QuadVert(xy = float2(3., -1.)), QuadVert(xy = float2(-1., 3.))
]

// non-subnormal seeds only: the EXT leaves fp16 denormal behavior implementation-defined,
// so the exactness claim is scoped to normal values (which is what real shader code uses)
let seeds = [
    float2(1.5, 2.0),
    float2(0.1, 3.0),
    float2(-2.25, 0.5),
    float2(1024.0, 0.125),
    float2(-0.333, 7.0)
]

[export]
def main {
    if (glfwInit() == 0) {
        panic("can't init glfw")
    }
    glfwInitOpenGL(3, 3)
    glfwWindowHint(int(GLFW_VISIBLE), 0)
    window = glfwCreateWindow(64, 64, "lattice gpu parity", null, null)
    if (window == null) {
        print("LATTICE GPU PARITY: SKIP (no GL context)\n")
        glfwTerminate()
        return
    }
    glfwMakeContextCurrent(window)
    if (!ext_supported()) {
        print("LATTICE GPU PARITY: SKIP (driver lacks GL_EXT_shader_explicit_arithmetic_types_float16 — run on zen2, see the run book)\n")
        glfwDestroyWindow(window)
        glfwTerminate()
        return
    }
    program = create_shader_program(@@lp_vs, @@lp_fs)
    if (program == 0u) {
        panic("LATTICE GPU PARITY: shader program failed to link on an EXT-capable driver")
    }
    glGenVertexArrays(1, safe_addr(vao))
    glBindVertexArray(vao)
    glGenBuffers(1, safe_addr(vbo))
    glBindBuffer(GL_ARRAY_BUFFER, vbo)
    glBufferData(GL_ARRAY_BUFFER, quad, GL_STATIC_DRAW)
    bind_vertex_buffer(null, type<QuadVert>)
    // 1x1 float FBO — one pixel carries four parity lanes per draw
    glGenTextures(1, safe_addr(tex))
    glBindTexture(GL_TEXTURE_2D, tex)
    glTexImage2D(GL_TEXTURE_2D, 0, int(GL_RGBA32F), 1, 1, 0, GL_RGBA, GL_FLOAT, null)
    glGenFramebuffers(1, safe_addr(fbo))
    glBindFramebuffer(GL_FRAMEBUFFER, fbo)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0)
    glViewport(0, 0, 1, 1)
    var failures = 0
    for (s in seeds) {
        u_a = s.x
        u_b = s.y
        glClearColor(0., 0., 0., 0.)
        glClear(GL_COLOR_BUFFER_BIT)
        glUseProgram(program)
        lp_vs_bind_uniform(program)
        lp_fs_bind_uniform(program)
        glBindVertexArray(vao)
        glDrawArrays(GL_TRIANGLES, 0, 3)
        glFinish()
        var pixel : float4
        glReadPixels(0, 0, 1, 1, GL_RGBA, GL_FLOAT, unsafe(addr(pixel)))
        let want = cpu_reference(s.x, s.y)
        if (pixel != want) {
            print("MISMATCH seed {s}: gpu {pixel} != cpu {want}\n")
            failures ++
        } else {
            print("ok seed {s}: {pixel}\n")
        }
    }
    glfwDestroyWindow(window)
    glfwTerminate()
    if (failures != 0) {
        panic("LATTICE GPU PARITY: {failures} mismatch(es)")
    }
    print("LATTICE GPU PARITY: ALL OK ({length(seeds)} cases)\n")
}
