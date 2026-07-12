options gen2

module dasllama_gguf shared public

require daslib/array_boost // nolint:STYLE030 — temp_array is [template]; STYLE030 misses template-fn refs
require strings
require llvm/daslib/f16_cvt public  // f16_to_f32 / f32_to_f16 (re-export: whisper/vad/parakeet/audio callers)

// Generic GGUF (v2/v3) reader: parses the header, typed key-value metadata, and the
// tensor-info table out of an mmap'd byte buffer, then exposes typed getters. Knows nothing
// about transformers — the semantic mapping (tensor names -> weight blob) lives in
// dasllama_transformer. Mirrors llama.cpp's gguf_context / llama_model_loader split.
//
// File layout (little-endian): "GGUF" magic, u32 version, i64 n_tensors, i64 n_kv,
// then n_kv {key:str, type:i32, [arr_type:i32, count:i64], value...} pairs,
// then n_tensors {name:str, n_dims:u32, dims:i64[], ggml_type:i32, offset:u64},
// then padding to alignment (only if n_tensors>0), then the tensor data blob.

// GGUF value type tags
let private GT_U8 = 0
let private GT_I8 = 1
let private GT_U16 = 2
let private GT_I16 = 3
let private GT_U32 = 4
let private GT_I32 = 5
let private GT_F32 = 6
let private GT_BOOL = 7
let private GT_STRING = 8
let private GT_ARRAY = 9
let private GT_U64 = 10
let private GT_I64 = 11
let private GT_F64 = 12

// ggml tensor data types (subset we read)
let GGML_TYPE_F32 = 0
let GGML_TYPE_F16 = 1
let GGML_TYPE_Q4_0 = 2
let GGML_TYPE_Q8_0 = 8
let GGML_TYPE_Q4_K = 12
let GGML_TYPE_Q5_K = 13
let GGML_TYPE_Q6_K = 14
let GGML_TYPE_BF16 = 30
let GGML_TYPE_MXFP4 = 39

// MXFP4 e2m1 magnitudes DOUBLED (nibble -> ±{0,.5,1,1.5,2,3,4,6}×2, OCP MX spec via ggml
// kvalues_mxfp4); the E8M0 block scale below is halved to compensate.
let private MXFP4_KVALUES = fixed_array(0.0, 1.0, 2.0, 3.0, 4.0, 6.0, 8.0, 12.0,
                                        0.0, -1.0, -2.0, -3.0, -4.0, -6.0, -8.0, -12.0)

// ===== little-endian byte readers =====

def rd_u16(b : array<uint8> | #; o : int64) : uint {
    return uint(b[o]) | (uint(b[o + 1l]) << 8u)
}

def rd_u32(b : array<uint8> | #; o : int64) : uint {
    return uint(b[o]) | (uint(b[o + 1l]) << 8u) | (uint(b[o + 2l]) << 16u) | (uint(b[o + 3l]) << 24u)
}

def private rd_u64(b : array<uint8> | #; o : int64) : uint64 {
    return uint64(rd_u32(b, o)) | (uint64(rd_u32(b, o + 4l)) << 32ul)
}

def rd_i32(b : array<uint8> | #; o : int64) : int {
    return int(rd_u32(b, o))
}

def private rd_i64(b : array<uint8> | #; o : int64) : int64 {
    return int64(rd_u64(b, o))
}

def rd_f32(b : array<uint8> | #; o : int64) : float {
    return unsafe(reinterpret<float>(rd_u32(b, o)))
}

// Read a length-prefixed string (u64 length + raw bytes), advancing the cursor.
def private rd_str(b : array<uint8> | #; var o : int64&) : string {
    let n = rd_i64(b, o)
    o += 8l
    var s = ""
    unsafe {
        s = string(temp_array(reinterpret<uint8?>(addr(b[o])), n, type<uint8>))
    }
    o += n
    return s
}

// E8M0 block scale -> fp32 * 0.5 = 2^(e-128) (the half matches the doubled MXFP4_KVALUES).
// e < 2 lands in fp32 denormal territory -> precomputed bit patterns (ggml_e8m0_to_fp32_half).
def private e8m0_to_f32_half(e : uint) : float {
    let bits = e < 2u ? (0x00200000u << e) : ((e - 1u) << 23u)
    return unsafe(reinterpret<float>(bits))
}

// ===== metadata model =====

//! Location of one KV value within the byte buffer (the value bytes are read lazily by getters).
struct GGUFKVLoc {
    gtype : int
    arr_type : int   // element type when gtype == array
    count : int64    // array element count (1 for scalars)
    data_off : int64 // byte offset of the value payload
}

//! One tensor's descriptor: name, type, element count, and offset within the data blob.
struct GGUFTensorInfo {
    name : string
    ggml_type : int
    offset : int64   // relative to the tensor data blob start
    n_elem : int64
    dims : array<int64>
}

//! Parsed GGUF metadata: version, alignment, the KV table, the tensor list, and the
//! absolute byte offset where tensor data begins.
struct GGUFMeta {
    version : uint
    alignment : int64
    data_offset : int64
    kv : table<string; GGUFKVLoc>
    tensors : array<GGUFTensorInfo>
}

def private gguf_scalar_size(gtype : int) : int64 {
    if (gtype == GT_U8 || gtype == GT_I8 || gtype == GT_BOOL) {
        return 1l
    }
    if (gtype == GT_U16 || gtype == GT_I16) {
        return 2l
    }
    if (gtype == GT_U32 || gtype == GT_I32 || gtype == GT_F32) {
        return 4l
    }
    if (gtype == GT_U64 || gtype == GT_I64 || gtype == GT_F64) {
        return 8l
    }
    return 0l  // string is length-prefixed, handled by the caller
}

// Walk past an array value, returning the offset just after it.
def private skip_array(b : array<uint8> | #; off : int64; arr_type : int; count : int64) : int64 {
    if (arr_type == GT_STRING) {
        var o = off
        for (_i in range64(count)) {
            let slen = rd_i64(b, o)
            o += 8l + slen
        }
        return o
    }
    return off + count * gguf_scalar_size(arr_type)
}

//! Parse the GGUF header, KV metadata, and tensor-info table out of `bytes`.
def parse_gguf_meta(bytes : array<uint8> | #) : GGUFMeta {
    var m : GGUFMeta
    if (!(int(bytes[0]) == 'G' && int(bytes[1]) == 'G' && int(bytes[2]) == 'U' && int(bytes[3]) == 'F')) {
        panic("gguf: bad magic (not a GGUF file)")
    }
    m.version = rd_u32(bytes, 4l)
    let n_tensors = rd_i64(bytes, 8l)
    let n_kv = rd_i64(bytes, 16l)
    m.alignment = 32l
    var off = 24l
    // key-value metadata
    for (_i in range64(n_kv)) {
        let key = rd_str(bytes, off)
        let gtype = rd_i32(bytes, off)
        off += 4l
        var loc : GGUFKVLoc
        loc.gtype = gtype
        loc.count = 1l
        if (gtype == GT_ARRAY) {
            loc.arr_type = rd_i32(bytes, off)
            off += 4l
            loc.count = rd_i64(bytes, off)
            off += 8l
            loc.data_off = off
            off = skip_array(bytes, off, loc.arr_type, loc.count)
        } elif (gtype == GT_STRING) {
            loc.data_off = off
            let slen = rd_i64(bytes, off)
            off += 8l + slen
        } else {
            loc.data_off = off
            off += gguf_scalar_size(gtype)
        }
        m.kv |> insert(key, loc)
    }
    if (key_exists(m.kv, "general.alignment")) {
        let alip = m.kv?["general.alignment"] ?? default<GGUFKVLoc>
        m.alignment = rd_i64(bytes, alip.data_off)
    }
    // tensor info table
    m.tensors |> reserve(int(n_tensors))
    for (_i in range64(n_tensors)) {
        var ti : GGUFTensorInfo
        ti.name = rd_str(bytes, off)
        let nd = rd_u32(bytes, off)
        off += 4l
        ti.n_elem = 1l
        ti.dims |> reserve(int(nd))
        for (_d in range(int(nd))) {
            let dv = rd_i64(bytes, off)
            off += 8l
            ti.dims |> push(dv)
            ti.n_elem *= dv
        }
        ti.ggml_type = rd_i32(bytes, off)
        off += 4l
        ti.offset = rd_i64(bytes, off)
        off += 8l
        m.tensors |> emplace(ti)
    }
    // tensor data starts here, padded to alignment only when the file has tensors
    m.data_offset = off
    if (n_tensors > 0l) {
        m.data_offset = ((off + m.alignment - 1l) / m.alignment) * m.alignment
    }
    return <- m
}

// ===== typed getters (call inside the mmap block — they read from `bytes`) =====

//! True if `key` is present in the metadata.
def gguf_has(m : GGUFMeta; key : string) : bool {
    return key_exists(m.kv, key)
}

//! Read an integer-typed value (any width / signedness) widened to int64.
def gguf_int(m : GGUFMeta; bytes : array<uint8> | #; key : string) : int64 {
    if (!key_exists(m.kv, key)) {
        panic("gguf: missing key '{key}'")
    }
    let loc = m.kv?[key] ?? default<GGUFKVLoc>
    let o = loc.data_off
    let t = loc.gtype
    if (t == GT_U8 || t == GT_I8 || t == GT_BOOL) {
        return int64(bytes[o])
    }
    if (t == GT_U16) {
        return int64(rd_u16(bytes, o))
    }
    if (t == GT_U32) {
        return int64(rd_u32(bytes, o))
    }
    if (t == GT_I32) {
        return int64(rd_i32(bytes, o))
    }
    if (t == GT_U64 || t == GT_I64) {
        return rd_i64(bytes, o)
    }
    panic("gguf: key '{key}' is not an integer (type {t})")
    return 0l
}

//! Read a float32 value (also accepts the rare f64-typed key, narrowed).
def gguf_f32(m : GGUFMeta; bytes : array<uint8> | #; key : string) : float {
    if (!key_exists(m.kv, key)) {
        panic("gguf: missing key '{key}'")
    }
    let loc = m.kv?[key] ?? default<GGUFKVLoc>
    if (loc.gtype == GT_F32) {
        return rd_f32(bytes, loc.data_off)
    }
    if (loc.gtype == GT_F64) {
        return float(unsafe(reinterpret<double>(rd_u64(bytes, loc.data_off))))
    }
    panic("gguf: key '{key}' is not a float (type {loc.gtype})")
    return 0.0
}

//! Read a string value.
def gguf_str(m : GGUFMeta; bytes : array<uint8> | #; key : string) : string {
    if (!key_exists(m.kv, key)) {
        panic("gguf: missing key '{key}'")
    }
    let loc = m.kv?[key] ?? default<GGUFKVLoc>
    if (loc.gtype != GT_STRING) {
        panic("gguf: key '{key}' is not a string (type {loc.gtype})")
    }
    var o = loc.data_off
    return rd_str(bytes, o)
}

//! Read a string array (e.g. tokenizer.ggml.tokens).
def gguf_str_array(m : GGUFMeta; bytes : array<uint8> | #; key : string) : array<string> {
    if (!key_exists(m.kv, key)) {
        panic("gguf: missing key '{key}'")
    }
    let loc = m.kv?[key] ?? default<GGUFKVLoc>
    if (loc.gtype != GT_ARRAY || loc.arr_type != GT_STRING) {
        panic("gguf: key '{key}' is not a string array")
    }
    var out : array<string>
    out |> reserve(int(loc.count))
    var o = loc.data_off
    for (_i in range64(loc.count)) {
        out |> push(rd_str(bytes, o))
    }
    return <- out
}

//! Read a float32 array (e.g. tokenizer.ggml.scores).
def gguf_f32_array(m : GGUFMeta; bytes : array<uint8> | #; key : string) : array<float> {
    if (!key_exists(m.kv, key)) {
        panic("gguf: missing key '{key}'")
    }
    let loc = m.kv?[key] ?? default<GGUFKVLoc>
    if (loc.gtype != GT_ARRAY || loc.arr_type != GT_F32) {
        panic("gguf: key '{key}' is not a float32 array")
    }
    var out : array<float>
    out |> resize(loc.count)
    var o = loc.data_off
    for (i in range64(loc.count)) {
        out[i] = rd_f32(bytes, o)
        o += 4l
    }
    return <- out
}

//! Read an int32 array (e.g. tokenizer.ggml.token_type), widened to int64.
def gguf_i32_array(m : GGUFMeta; bytes : array<uint8> | #; key : string) : array<int64> {
    if (!key_exists(m.kv, key)) {
        panic("gguf: missing key '{key}'")
    }
    let loc = m.kv?[key] ?? default<GGUFKVLoc>
    if (loc.gtype != GT_ARRAY || loc.arr_type != GT_I32) {
        panic("gguf: key '{key}' is not an int32 array")
    }
    var out : array<int64>
    out |> resize(loc.count)
    var o = loc.data_off
    for (i in range64(loc.count)) {
        out[i] = int64(rd_i32(bytes, o))
        o += 4l
    }
    return <- out
}

//! True if `key` is present AND holds an array-typed value (some keys are scalar-or-array,
//! e.g. gemma4's per-layer attention.head_count_kv / sliding_window_pattern).
def gguf_is_array(m : GGUFMeta; key : string) : bool {
    if (!key_exists(m.kv, key)) {
        return false
    }
    return (m.kv?[key] ?? default<GGUFKVLoc>).gtype == GT_ARRAY
}

//! Read an integer array of any element width (u8/i8/bool/u16/i16/u32/i32/u64/i64), widened to
//! int64. gemma4 stores sliding_window_pattern as bool[] and head_count_kv as i32[].
def gguf_int_array(m : GGUFMeta; bytes : array<uint8> | #; key : string) : array<int64> {
    if (!key_exists(m.kv, key)) {
        panic("gguf: missing key '{key}'")
    }
    let loc = m.kv?[key] ?? default<GGUFKVLoc>
    if (loc.gtype != GT_ARRAY) {
        panic("gguf: key '{key}' is not an array")
    }
    let et = loc.arr_type
    var out : array<int64>
    out |> resize(loc.count)
    var o = loc.data_off
    for (i in range64(loc.count)) {
        if (et == GT_U8 || et == GT_BOOL) {
            out[i] = int64(bytes[o])
            o++
        } elif (et == GT_I8) {
            let v = int(bytes[o])
            out[i] = int64(v < 128 ? v : v - 256)
            o++
        } elif (et == GT_U16) {
            out[i] = int64(rd_u16(bytes, o))
            o += 2l
        } elif (et == GT_I16) {
            let v = int(rd_u16(bytes, o))
            out[i] = int64(v < 32768 ? v : v - 65536)
            o += 2l
        } elif (et == GT_U32) {
            out[i] = int64(rd_u32(bytes, o))
            o += 4l
        } elif (et == GT_I32) {
            out[i] = int64(rd_i32(bytes, o))
            o += 4l
        } elif (et == GT_U64 || et == GT_I64) {
            out[i] = rd_i64(bytes, o)
            o += 8l
        } else {
            panic("gguf: key '{key}' element type {et} is not an integer")
        }
    }
    return <- out
}

//! Index of tensor `name` in m.tensors, or -1 if absent.
def gguf_find_tensor(m : GGUFMeta; name : string) : int {
    for (i in range(length(m.tensors))) {
        if (m.tensors[i].name == name) {
            return i
        }
    }
    return -1
}

// ===== K-quant superblock dequant (256-weight superblocks, ggml Q4_K / Q6_K) =====

// int8 read (K-quant sub-scales are signed bytes)
def private rd_i8(b : array<uint8> | #; o : int64) : int {
    let u = int(b[o])
    return u < 128 ? u : u - 256
}

// 6-bit sub-scale/min unpack for Q4_K/Q5_K superblocks (ggml get_scale_min_k4). The 12 scale
// bytes hold 8 scales + 8 mins: j<4 live in the low 6 bits of bytes j / j+4; j>=4 split as
// low-4 in byte j+4 (scale = low nibble, min = high) + top-2 of bytes j-4 / j.
def private q4k_scale_min(b : array<uint8> | #; so, j : int64) : int2 {
    if (j < 4l) {
        return int2(int(b[so + j]) & 63, int(b[so + j + 4l]) & 63)
    }
    let sc = (int(b[so + j + 4l]) & 15) | ((int(b[so + j - 4l]) >> 6) << 4)
    let mn = (int(b[so + j + 4l]) >> 4) | ((int(b[so + j]) >> 6) << 4)
    return int2(sc, mn)
}

//! Dequantize one Q4_K superblock (144 bytes at `bo`: fp16 d, fp16 dmin, 12 bytes of 6-bit
//! sub-scales/mins for 8 sub-blocks of 32, 128 nibble bytes) into dst[doff .. doff+256).
//! w = (d*sc)*q - (dmin*m) with q the RAW nibble — the min term absorbs the offset. Per 64-weight
//! chunk the 32 quant bytes carry weights 0..31 in low nibbles, 32..63 in high (ggml order).
//! Matches llama.cpp dequantize_row_q4_K op-for-op, so the expansion is bit-exact.
def dequant_q4k_superblock(bytes : array<uint8> | #; bo : int64; var dst : array<float>; doff : int64) {
    let d = f16_to_f32(rd_u16(bytes, bo))
    let dmin = f16_to_f32(rd_u16(bytes, bo + 2l))
    let so = bo + 4l    // 12 scale/min bytes
    var qo = bo + 16l   // 128 quant bytes
    var dsto = doff
    for (js in range64(4l)) {   // 4 chunks of 64 weights = sub-blocks 2js, 2js+1
        let s0 = q4k_scale_min(bytes, so, 2l * js)
        let s1 = q4k_scale_min(bytes, so, 2l * js + 1l)
        let d1 = d * float(s0.x)
        let m1 = dmin * float(s0.y)
        let d2 = d * float(s1.x)
        let m2 = dmin * float(s1.y)
        for (l in range64(32l)) {
            let b = int(bytes[qo + l])
            dst[dsto + l] = d1 * float(b & 15) - m1
            dst[dsto + 32l + l] = d2 * float(b >> 4) - m2
        }
        qo += 32l
        dsto += 64l
    }
}

//! Dequantize one Q5_K superblock (176 bytes at `bo`: fp16 d, fp16 dmin, 12 bytes of 6-bit
//! sub-scales/mins, 32 high-bit bytes qh, 128 nibble bytes qs) into dst[doff .. doff+256).
//! w = (d*sc)*q - (dmin*m) with q = nibble | (high bit << 4) in 0..31; the high bit for chunk
//! js lives in bit 2js (low nibbles) / 2js+1 (high nibbles) of qh[l], qh base fixed per
//! superblock. Matches llama.cpp dequantize_row_q5_K op-for-op.
def dequant_q5k_superblock(bytes : array<uint8> | #; bo : int64; var dst : array<float>; doff : int64) {
    let d = f16_to_f32(rd_u16(bytes, bo))
    let dmin = f16_to_f32(rd_u16(bytes, bo + 2l))
    let so = bo + 4l     // 12 scale/min bytes
    let qho = bo + 16l   // 32 high-bit bytes (fixed base for the whole superblock)
    var qo = bo + 48l    // 128 nibble bytes
    var dsto = doff
    for (js in range64(4l)) {
        let s0 = q4k_scale_min(bytes, so, 2l * js)
        let s1 = q4k_scale_min(bytes, so, 2l * js + 1l)
        let d1 = d * float(s0.x)
        let m1 = dmin * float(s0.y)
        let d2 = d * float(s1.x)
        let m2 = dmin * float(s1.y)
        let u1 = 1 << (int(js) * 2)
        let u2 = 2 << (int(js) * 2)
        for (l in range64(32l)) {
            let b = int(bytes[qo + l])
            let h = int(bytes[qho + l])
            dst[dsto + l] = d1 * float((b & 15) + ((h & u1) != 0 ? 16 : 0)) - m1
            dst[dsto + 32l + l] = d2 * float((b >> 4) + ((h & u2) != 0 ? 16 : 0)) - m2
        }
        qo += 32l
        dsto += 64l
    }
}

//! Dequantize one Q6_K superblock (210 bytes at `bo`: 128 low-nibble bytes ql, 64 high-2-bit
//! bytes qh, 16 int8 sub-scales for 16 sub-blocks of 16, fp16 d) into dst[doff .. doff+256).
//! w = (d*sc)*q with q = (ql | qh<<4) - 32. Matches llama.cpp dequantize_row_q6_K op-for-op.
def dequant_q6k_superblock(bytes : array<uint8> | #; bo : int64; var dst : array<float>; doff : int64) {
    let d = f16_to_f32(rd_u16(bytes, bo + 208l))
    var qlo = bo          // ql cursor (64 bytes per 128-weight half)
    var qho = bo + 128l   // qh cursor (32 bytes per half)
    var sco = bo + 192l   // sub-scale cursor (8 per half)
    var dsto = doff
    for (_half in range(2)) {
        for (l in range64(32l)) {
            let si = l / 16l
            let hl = int(bytes[qho + l])
            let q1 = ((int(bytes[qlo + l]) & 15) | (((hl >> 0) & 3) << 4)) - 32
            let q2 = ((int(bytes[qlo + 32l + l]) & 15) | (((hl >> 2) & 3) << 4)) - 32
            let q3 = ((int(bytes[qlo + l]) >> 4) | (((hl >> 4) & 3) << 4)) - 32
            let q4 = ((int(bytes[qlo + 32l + l]) >> 4) | (((hl >> 6) & 3) << 4)) - 32
            dst[dsto + l] = d * float(rd_i8(bytes, sco + si)) * float(q1)
            dst[dsto + 32l + l] = d * float(rd_i8(bytes, sco + si + 2l)) * float(q2)
            dst[dsto + 64l + l] = d * float(rd_i8(bytes, sco + si + 4l)) * float(q3)
            dst[dsto + 96l + l] = d * float(rd_i8(bytes, sco + si + 6l)) * float(q4)
        }
        qlo += 64l
        qho += 32l
        sco += 8l
        dsto += 128l
    }
}

// ===== K-quant native-plane transcode (superblock payloads -> split quant/scale planes) =====
// Plane layouts (per 256-weight superblock; element offsets are plane-local and superblock-aligned):
//   k4 quant: 128B nibbles verbatim            k4 scale: [f16 d][f16 dmin][12B 6-bit sc/mn][4B pad] = 20B
//   k5 quant: [128B nibbles][32B high-bits]    k5 scale: 8 x (f16 d*sc, f16 dmin*m) = 32B
//   k6 quant: [128B ql][64B qh]                k6 scale: [16 x int8 sub-scales][f16 d] = 18B
// k4 keeps the DISK scale block verbatim (kq v2 — the lcpp fold scheme: integer sub-scale and
// bsums-x-mins accumulation against per-256 Q8_K activations, one d*d8 float fold per
// superblock); the 4B pad brings the stride to 20 so the grp repack can decode the 6-bit
// packing into [d][dmin][sc u8][mn u8] rows IN PLACE. k5's f16 (s, o) pairs are the v1
// load-time unpack of the 6-bit sub-scales — f16 rounding of d*sc / dmin*m is <= 2^-12
// relative, and the k5 plane-dequant reference applies the SAME rounding, so those kernels
// gate bit-exactly against it. k4/k6 plane dequants are bit-exact vs the DISK dequant (their
// planes are verbatim).

def private wr_f16(var p : array<uint8>; o : int64; v : float) {
    let h = f32_to_f16(v)
    p[o] = uint8(h & 0xFF)
    p[o + 1l] = uint8(h >> 8u)
}

//! Transcode one Q4_K superblock (144 bytes at `bo`) into the k4 planes: nibbles verbatim to
//! kq[kqo..+128), the disk scale block verbatim to ks[kso..+16) (f16 d, f16 dmin, 12 bytes of
//! 6-bit sub-scales/mins) + 4 zero pad bytes (stride 20 — see the plane-layout comment above).
def transcode_q4k_superblock(bytes : array<uint8> | #; bo : int64; var kq : array<uint8>; kqo : int64; var ks : array<uint8>; kso : int64) {
    for (i in range64(16l)) {
        ks[kso + i] = bytes[bo + i]   // f16 d, f16 dmin, 12 packed scale/min bytes — disk order
    }
    for (i in range64(4l)) {
        ks[kso + 16l + i] = uint8(0)
    }
    for (i in range64(128l)) {
        kq[kqo + i] = bytes[bo + 16l + i]
    }
}

//! Transcode one Q5_K superblock (176 bytes at `bo`) into the k5 planes: [nibbles][high-bits]
//! to kq[kqo..+160), f16 (d*sc, dmin*m) pairs to ks[kso..+32).
def transcode_q5k_superblock(bytes : array<uint8> | #; bo : int64; var kq : array<uint8>; kqo : int64; var ks : array<uint8>; kso : int64) {
    let d = f16_to_f32(rd_u16(bytes, bo))
    let dmin = f16_to_f32(rd_u16(bytes, bo + 2l))
    for (j in range64(8l)) {
        let sm = q4k_scale_min(bytes, bo + 4l, j)
        wr_f16(ks, kso + j * 4l, d * float(sm.x))
        wr_f16(ks, kso + j * 4l + 2l, dmin * float(sm.y))
    }
    for (i in range64(128l)) {
        kq[kqo + i] = bytes[bo + 48l + i]   // qs
    }
    for (i in range64(32l)) {
        kq[kqo + 128l + i] = bytes[bo + 16l + i]   // qh
    }
}

//! Transcode one Q6_K superblock (210 bytes at `bo`) into the k6 planes: [ql][qh] to
//! kq[kqo..+192), the native int8 sub-scales + f16 d to ks[kso..+18) — all verbatim (exact).
def transcode_q6k_superblock(bytes : array<uint8> | #; bo : int64; var kq : array<uint8>; kqo : int64; var ks : array<uint8>; kso : int64) {
    for (i in range64(192l)) {
        kq[kqo + i] = bytes[bo + i]   // ql (128) then qh (64) — disk order
    }
    for (i in range64(18l)) {
        ks[kso + i] = bytes[bo + 192l + i]   // 16 int8 sub-scales + f16 d halfword
    }
}

// f16 (s, o) pair read for the k4/k5 plane-dequant references
def private rd_pair(ks : array<uint8> | #; o : int64) : float2 {
    return float2(f16_to_f32(rd_u16(ks, o)), f16_to_f32(rd_u16(ks, o + 2l)))
}

//! Reference dequant of one k4-plane superblock (the exact math the k4 kernels must reproduce):
//! w = (d*sc)*q - (dmin*m) with the plane's verbatim disk scale block — bit-identical to the
//! disk dequant (kq v2: the plane IS the disk block, split).
def dequant_k4_plane_superblock(kq : array<uint8> | #; kqo : int64; ks : array<uint8> | #; kso : int64; var dst : array<float> | #; doff : int64) {
    let d = f16_to_f32(rd_u16(ks, kso))
    let dmin = f16_to_f32(rd_u16(ks, kso + 2l))
    var dsto = doff
    for (js in range64(4l)) {
        let s0 = q4k_scale_min(ks, kso + 4l, 2l * js)
        let s1 = q4k_scale_min(ks, kso + 4l, 2l * js + 1l)
        let d1 = d * float(s0.x)
        let m1 = dmin * float(s0.y)
        let d2 = d * float(s1.x)
        let m2 = dmin * float(s1.y)
        for (l in range64(32l)) {
            let b = int(kq[kqo + 32l * js + l])
            dst[dsto + l] = d1 * float(b & 15) - m1
            dst[dsto + 32l + l] = d2 * float(b >> 4) - m2
        }
        dsto += 64l
    }
}

//! Reference dequant of one k5-plane superblock: w = s*q - o, q = nibble | (high bit << 4).
def dequant_k5_plane_superblock(kq : array<uint8> | #; kqo : int64; ks : array<uint8> | #; kso : int64; var dst : array<float> | #; doff : int64) {
    var dsto = doff
    for (js in range64(4l)) {
        let p0 = rd_pair(ks, kso + 2l * js * 4l)
        let p1 = rd_pair(ks, kso + (2l * js + 1l) * 4l)
        let u1 = 1 << (int(js) * 2)
        let u2 = 2 << (int(js) * 2)
        for (l in range64(32l)) {
            let b = int(kq[kqo + 32l * js + l])
            let h = int(kq[kqo + 128l + l])
            dst[dsto + l] = p0.x * float((b & 15) + ((h & u1) != 0 ? 16 : 0)) - p0.y
            dst[dsto + 32l + l] = p1.x * float((b >> 4) + ((h & u2) != 0 ? 16 : 0)) - p1.y
        }
        dsto += 64l
    }
}

//! Reference dequant of one k6-plane superblock: w = (d*sc16)*(q - 32) — bit-identical to the
//! disk dequant (the k6 planes are verbatim).
def dequant_k6_plane_superblock(kq : array<uint8> | #; kqo : int64; ks : array<uint8> | #; kso : int64; var dst : array<float> | #; doff : int64) {
    let d = f16_to_f32(rd_u16(ks, kso + 16l))
    var qlo = kqo
    var qho = kqo + 128l
    var sco = kso
    var dsto = doff
    for (_half in range(2)) {
        for (l in range64(32l)) {
            let si = l / 16l
            let hl = int(kq[qho + l])
            let q1 = ((int(kq[qlo + l]) & 15) | (((hl >> 0) & 3) << 4)) - 32
            let q2 = ((int(kq[qlo + 32l + l]) & 15) | (((hl >> 2) & 3) << 4)) - 32
            let q3 = ((int(kq[qlo + l]) >> 4) | (((hl >> 4) & 3) << 4)) - 32
            let q4 = ((int(kq[qlo + 32l + l]) >> 4) | (((hl >> 6) & 3) << 4)) - 32
            dst[dsto + l] = d * float(rd_i8(ks, sco + si)) * float(q1)
            dst[dsto + 32l + l] = d * float(rd_i8(ks, sco + si + 2l)) * float(q2)
            dst[dsto + 64l + l] = d * float(rd_i8(ks, sco + si + 4l)) * float(q3)
            dst[dsto + 96l + l] = d * float(rd_i8(ks, sco + si + 6l)) * float(q4)
        }
        qlo += 64l
        qho += 32l
        sco += 8l
        dsto += 128l
    }
}

// K-quant plane strides (bytes per 256-weight superblock)
let K4_QSB = 128l
let K4_SSB = 20l   // kq v2: 16B verbatim disk scale block + 4B pad (repack decodes in place)
let K5_QSB = 160l
let K5_SSB = 32l
let K6_QSB = 192l
let K6_SSB = 18l

// Shared header for the three file-level transcodes: locate + type-check + bounds-check, return
// the superblock-aligned disk cursor.
def private kq_transcode_base(m : GGUFMeta; name : string; want_type : int; type_name : string; src_off, expect_n, disk_sb : int64) : int64 {
    let ti = gguf_find_tensor(m, name)
    if (ti < 0) {
        panic("gguf: tensor '{name}' not found")
    }
    if (m.tensors[ti].ggml_type != want_type) {
        panic("gguf: tensor '{name}' is not {type_name} (type {m.tensors[ti].ggml_type})")
    }
    if (src_off % 256l != 0l || expect_n % 256l != 0l) {
        panic("gguf: tensor '{name}' {type_name} slice [{src_off}, +{expect_n}) is not superblock-aligned")
    }
    if (src_off + expect_n > m.tensors[ti].n_elem) {
        panic("gguf: tensor '{name}' slice [{src_off}, {src_off + expect_n}) exceeds {m.tensors[ti].n_elem} elems")
    }
    return m.data_offset + m.tensors[ti].offset + (src_off / 256l) * disk_sb
}

//! Transcode a Q4_K tensor into the k4 planes at plane-local element offset `eloff` (from the
//! layout's k4 cursor): quant bytes at (eloff/256)*128, scale blocks at (eloff/256)*20.
def gguf_transcode_q4k(m : GGUFMeta; bytes : array<uint8> | #; name : string; var kq : array<uint8>; var ks : array<uint8>; eloff, expect_n : int64; src_off : int64 = 0l) {
    var bo = kq_transcode_base(m, name, GGML_TYPE_Q4_K, "Q4_K", src_off, expect_n, 144l)
    var kqo = (eloff / 256l) * K4_QSB
    var kso = (eloff / 256l) * K4_SSB
    for (_blk in range64(expect_n / 256l)) {
        transcode_q4k_superblock(bytes, bo, kq, kqo, ks, kso)
        bo += 144l
        kqo += K4_QSB
        kso += K4_SSB
    }
}

//! Transcode a Q5_K tensor into the k5 planes (see gguf_transcode_q4k; strides 160/32).
def gguf_transcode_q5k(m : GGUFMeta; bytes : array<uint8> | #; name : string; var kq : array<uint8>; var ks : array<uint8>; eloff, expect_n : int64; src_off : int64 = 0l) {
    var bo = kq_transcode_base(m, name, GGML_TYPE_Q5_K, "Q5_K", src_off, expect_n, 176l)
    var kqo = (eloff / 256l) * K5_QSB
    var kso = (eloff / 256l) * K5_SSB
    for (_blk in range64(expect_n / 256l)) {
        transcode_q5k_superblock(bytes, bo, kq, kqo, ks, kso)
        bo += 176l
        kqo += K5_QSB
        kso += K5_SSB
    }
}

//! Transcode a Q6_K tensor into the k6 planes (see gguf_transcode_q4k; strides 192/18, exact).
def gguf_transcode_q6k(m : GGUFMeta; bytes : array<uint8> | #; name : string; var kq : array<uint8>; var ks : array<uint8>; eloff, expect_n : int64; src_off : int64 = 0l) {
    var bo = kq_transcode_base(m, name, GGML_TYPE_Q6_K, "Q6_K", src_off, expect_n, 210l)
    var kqo = (eloff / 256l) * K6_QSB
    var kso = (eloff / 256l) * K6_SSB
    for (_blk in range64(expect_n / 256l)) {
        transcode_q6k_superblock(bytes, bo, kq, kqo, ks, kso)
        bo += 210l
        kqo += K6_QSB
        kso += K6_SSB
    }
}

//! Decode tensor `name` (F32 or F16 on disk) into dst[dst_off ..] as fp32. Panics if the
//! tensor is missing, has a different element count than expected, or uses a type we don't
//! yet read (quantized types are wired in a later step).
def gguf_read_tensor_f32(m : GGUFMeta; bytes : array<uint8> | #; name : string; var dst : array<float>; dst_off, expect_n : int64; src_off : int64 = 0l) {
    let ti = gguf_find_tensor(m, name)
    if (ti < 0) {
        panic("gguf: tensor '{name}' not found")
    }
    let nelem = m.tensors[ti].n_elem
    // src_off (element offset into the tensor) reads a sub-range — used to split fused qkv / gate_up
    // tensors (Phi3). For quantized types it must be 32-aligned so it lands on a block boundary
    // (256-aligned for the K-quant superblock types — those arms check).
    if (src_off + expect_n > nelem) {
        panic("gguf: tensor '{name}' slice [{src_off}, {src_off + expect_n}) exceeds {nelem} elems")
    }
    let gtype = m.tensors[ti].ggml_type
    let base = m.data_offset + m.tensors[ti].offset
    if (gtype == GGML_TYPE_F32) {
        unsafe {
            let src = temp_array(reinterpret<float?>(addr(bytes[base + src_off * 4l])), expect_n, type<float>)
            for (i in range64(expect_n)) {
                dst[dst_off + i] = src[i]
            }
        }
    } elif (gtype == GGML_TYPE_F16) {
        unsafe {
            let src = temp_array(reinterpret<uint16?>(addr(bytes[base + src_off * 2l])), expect_n, type<uint16>)
            for (i in range64(expect_n)) {
                dst[dst_off + i] = f16_to_f32(uint(src[i]))
            }
        }
    } elif (gtype == GGML_TYPE_BF16) {
        // bf16 is the top 16 bits of an f32 — the shift-up conversion is exact
        unsafe {
            let src = temp_array(reinterpret<uint16?>(addr(bytes[base + src_off * 2l])), expect_n, type<uint16>)
            for (i in range64(expect_n)) {
                dst[dst_off + i] = reinterpret<float>(uint(src[i]) << 16u)
            }
        }
    } elif (gtype == GGML_TYPE_Q8_0) {
        // block of 32: fp16 scale d (2 bytes) + 32 int8 quants; x[i] = q[i] * d
        let nb = expect_n / 32l
        var bo = base + (src_off / 32l) * 34l
        for (blk in range64(nb)) {
            let d = f16_to_f32(rd_u16(bytes, bo))
            bo += 2l
            for (k in range64(32l)) {
                let u = int(bytes[bo + k])
                let q = u < 128 ? u : u - 256
                dst[dst_off + blk * 32l + k] = float(q) * d
            }
            bo += 32l
        }
    } elif (gtype == GGML_TYPE_Q4_0) {
        // block of 32: fp16 scale d (2 bytes) + 16 bytes (split-half nibbles); x = (nibble - 8) * d
        let nb = expect_n / 32l
        var bo = base + (src_off / 32l) * 18l
        for (blk in range64(nb)) {
            let d = f16_to_f32(rd_u16(bytes, bo))
            bo += 2l
            for (k in range64(16l)) {
                let b = int(bytes[bo + k])
                dst[dst_off + blk * 32l + k] = float((b & 15) - 8) * d
                dst[dst_off + blk * 32l + k + 16l] = float((b >> 4) - 8) * d
            }
            bo += 16l
        }
    } elif (gtype == GGML_TYPE_Q4_K) {
        if (src_off % 256l != 0l || expect_n % 256l != 0l) {
            panic("gguf: tensor '{name}' Q4_K slice [{src_off}, +{expect_n}) is not superblock-aligned")
        }
        let nb = expect_n / 256l
        var bo = base + (src_off / 256l) * 144l
        for (blk in range64(nb)) {
            dequant_q4k_superblock(bytes, bo, dst, dst_off + blk * 256l)
            bo += 144l
        }
    } elif (gtype == GGML_TYPE_Q5_K) {
        if (src_off % 256l != 0l || expect_n % 256l != 0l) {
            panic("gguf: tensor '{name}' Q5_K slice [{src_off}, +{expect_n}) is not superblock-aligned")
        }
        let nb = expect_n / 256l
        var bo = base + (src_off / 256l) * 176l
        for (blk in range64(nb)) {
            dequant_q5k_superblock(bytes, bo, dst, dst_off + blk * 256l)
            bo += 176l
        }
    } elif (gtype == GGML_TYPE_Q6_K) {
        if (src_off % 256l != 0l || expect_n % 256l != 0l) {
            panic("gguf: tensor '{name}' Q6_K slice [{src_off}, +{expect_n}) is not superblock-aligned")
        }
        let nb = expect_n / 256l
        var bo = base + (src_off / 256l) * 210l
        for (blk in range64(nb)) {
            dequant_q6k_superblock(bytes, bo, dst, dst_off + blk * 256l)
            bo += 210l
        }
    } elif (gtype == GGML_TYPE_MXFP4) {
        // block of 32: 1 E8M0 scale byte + 16 nibble bytes (low nibbles = elems 0..15, high = 16..31);
        // x = e2m1[nibble] * scale — both sides carry the ×2/÷2 ggml convention (see MXFP4_KVALUES)
        let nb = expect_n / 32l
        var bo = base + (src_off / 32l) * 17l
        for (blk in range64(nb)) {
            let d = e8m0_to_f32_half(uint(bytes[bo]))
            bo++
            for (k in range64(16l)) {
                let b = int(bytes[bo + k])
                dst[dst_off + blk * 32l + k] = MXFP4_KVALUES[b & 15] * d
                dst[dst_off + blk * 32l + k + 16l] = MXFP4_KVALUES[b >> 4] * d
            }
            bo += 16l
        }
    } else {
        panic("gguf: tensor '{name}' type {gtype} not supported (have F32/F16/BF16/Q8_0/Q4_0/Q4_K/Q5_K/Q6_K/MXFP4)")
    }
}

//! Copy a BF16 tensor's raw halfwords into dst[dst_off..] — no fp32 expand (read kernels widen
//! in-loop by the exact bit shift). Requires the tensor to be BF16 on disk (check gguf_tensor_type).
def gguf_transcode_bf16(m : GGUFMeta; bytes : array<uint8> | #; name : string; var dst : array<uint16>; dst_off, expect_n : int64) {
    let ti = gguf_find_tensor(m, name)
    if (ti < 0) {
        panic("gguf: tensor '{name}' not found")
    }
    if (m.tensors[ti].ggml_type != GGML_TYPE_BF16) {
        panic("gguf: tensor '{name}' is not BF16 (type {m.tensors[ti].ggml_type})")
    }
    if (expect_n != m.tensors[ti].n_elem) {
        panic("gguf: tensor '{name}' has {m.tensors[ti].n_elem} elems, expected {expect_n}")
    }
    let base = m.data_offset + m.tensors[ti].offset
    unsafe {
        let src = temp_array(reinterpret<uint16?>(addr(bytes[base])), expect_n, type<uint16>)
        for (i in range64(expect_n)) {
            dst[dst_off + i] = src[i]
        }
    }
}

//! The on-disk ggml type of tensor `name` (GGML_TYPE_*), or -1 if the tensor is absent. Lets a
//! caller pick the direct-transcode path when the disk type already matches the target precision.
def gguf_tensor_type(m : GGUFMeta; name : string) : int {
    let ti = gguf_find_tensor(m, name)
    return ti < 0 ? -1 : m.tensors[ti].ggml_type
}

//! Transcode a Q8_0 tensor straight from disk into our Q8 layout — no fp32 round-trip. int8 quants
//! copy verbatim to qdst[qoff..]; the per-block fp16 scale widens to fp32 in sdst[soff..]. Requires
//! the tensor to be Q8_0 on disk (check gguf_tensor_type first). qoff is the weight-element offset,
//! soff = qoff / 32. This is the memory-honest load of a pre-quantized GGUF.
def gguf_transcode_q8_0(m : GGUFMeta; bytes : array<uint8> | #; name : string; var qdst : array<int8>; var sdst : array<float>; qoff, soff, expect_n : int64; src_off : int64 = 0l) {
    let ti = gguf_find_tensor(m, name)
    if (ti < 0) {
        panic("gguf: tensor '{name}' not found")
    }
    if (m.tensors[ti].ggml_type != GGML_TYPE_Q8_0) {
        panic("gguf: tensor '{name}' is not Q8_0 (type {m.tensors[ti].ggml_type})")
    }
    // src_off (32-aligned element offset) transcodes a sub-range — preserves the original Q8 blocks
    // when splitting a fused tensor (Phi3 attn_qkv / gate_up), so there's no lossy fp32 requantize
    if (src_off + expect_n > m.tensors[ti].n_elem) {
        panic("gguf: tensor '{name}' slice [{src_off}, {src_off + expect_n}) exceeds {m.tensors[ti].n_elem} elems")
    }
    let nb = expect_n / 32l
    var bo = m.data_offset + m.tensors[ti].offset + (src_off / 32l) * 34l
    for (blk in range64(nb)) {
        sdst[soff + blk] = f16_to_f32(rd_u16(bytes, bo))
        bo += 2l
        for (k in range64(32l)) {
            let u = int(bytes[bo + k])
            qdst[qoff + blk * 32l + k] = int8(u < 128 ? u : u - 256)
        }
        bo += 32l
    }
}

//! Transcode a Q4_0 tensor straight from disk into our Q4 layout — no fp32 round-trip. Our Q4 uses
//! GGML's exact split-half nibble packing, so the 16 packed bytes per block copy verbatim to
//! qdst[qoff_bytes..] (qoff_bytes = weight-element-offset / 2); the per-block fp16 scale widens to
//! fp32 in sdst[soff..]. Requires the tensor to be Q4_0 on disk (check gguf_tensor_type first).
def gguf_transcode_q4_0(m : GGUFMeta; bytes : array<uint8> | #; name : string; var qdst : array<uint8>; var sdst : array<float>; qoff_bytes, soff, expect_n : int64; src_off : int64 = 0l) {
    let ti = gguf_find_tensor(m, name)
    if (ti < 0) {
        panic("gguf: tensor '{name}' not found")
    }
    if (m.tensors[ti].ggml_type != GGML_TYPE_Q4_0) {
        panic("gguf: tensor '{name}' is not Q4_0 (type {m.tensors[ti].ggml_type})")
    }
    if (src_off + expect_n > m.tensors[ti].n_elem) {
        panic("gguf: tensor '{name}' slice [{src_off}, {src_off + expect_n}) exceeds {m.tensors[ti].n_elem} elems")
    }
    let nb = expect_n / 32l
    var bo = m.data_offset + m.tensors[ti].offset + (src_off / 32l) * 18l
    for (blk in range64(nb)) {
        sdst[soff + blk] = f16_to_f32(rd_u16(bytes, bo))
        bo += 2l
        for (j in range64(16l)) {
            qdst[qoff_bytes + blk * 16l + j] = bytes[bo + j]
        }
        bo += 16l
    }
}

//! Transcode an MXFP4 tensor straight from disk into split native planes — the RAW bits, no dequant
//! round-trip: the 16 packed-nibble bytes per 32-block copy verbatim to ndst[noff_bytes..]
//! (noff_bytes = weight-element-offset / 2) and the 1 RAW E8M0 scale byte to edst[eoff..]
//! (eoff = offset / 32). Exact by construction (vs the old dequant->requantize-to-Q8 path, which
//! paid an amax error) and reads 17 bytes/block instead of writing 33+. Requires the tensor to be
//! MXFP4 on disk (check gguf_tensor_type first).
def gguf_transcode_mx4(m : GGUFMeta; bytes : array<uint8> | #; name : string; var ndst : array<uint8>; var edst : array<uint8>; noff_bytes, eoff, expect_n : int64; src_off : int64 = 0l) {
    let ti = gguf_find_tensor(m, name)
    if (ti < 0) {
        panic("gguf: tensor '{name}' not found")
    }
    if (m.tensors[ti].ggml_type != GGML_TYPE_MXFP4) {
        panic("gguf: tensor '{name}' is not MXFP4 (type {m.tensors[ti].ggml_type})")
    }
    if (src_off + expect_n > m.tensors[ti].n_elem) {
        panic("gguf: tensor '{name}' slice [{src_off}, {src_off + expect_n}) exceeds {m.tensors[ti].n_elem} elems")
    }
    let nb = expect_n / 32l
    var bo = m.data_offset + m.tensors[ti].offset + (src_off / 32l) * 17l
    for (blk in range64(nb)) {
        edst[eoff + blk] = bytes[bo]
        bo++
        for (j in range64(16l)) {
            ndst[noff_bytes + blk * 16l + j] = bytes[bo + j]
        }
        bo += 16l
    }
}
