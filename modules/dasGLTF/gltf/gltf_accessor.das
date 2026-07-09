options gen2
options indenting = 4

module gltf_accessor shared

require math
require daslib/array_boost

// Little-endian typed reads from a raw byte buffer. glTF is always little-endian
// (matches x86 native), so these compose bytes directly. Pattern mirrors the
// dasLLAMA GGUF reader (modules/dasLLAMA/dasllama/dasllama_gguf.das).

def gltf_rd_u8(b : array<uint8> | #; o : int64) : uint {
    return uint(b[o])
}

def gltf_rd_u16(b : array<uint8> | #; o : int64) : uint {
    return uint(b[o]) | (uint(b[o + 1l]) << 8u)
}

def gltf_rd_u32(b : array<uint8> | #; o : int64) : uint {
    return uint(b[o]) | (uint(b[o + 1l]) << 8u) | (uint(b[o + 2l]) << 16u) | (uint(b[o + 3l]) << 24u)
}

def gltf_rd_i8(b : array<uint8> | #; o : int64) : int {
    let v = int(b[o])
    return v >= 128 ? v - 256 : v
}

def gltf_rd_i16(b : array<uint8> | #; o : int64) : int {
    let v = int(gltf_rd_u16(b, o))
    return v >= 32768 ? v - 65536 : v
}

def gltf_rd_f32(b : array<uint8> | #; o : int64) : float {
    return unsafe(reinterpret<float>(gltf_rd_u32(b, o)))
}
