options gen2
options indenting = 4

// daslang TypeDecl -> MSL type name. Covers the 32-bit scalars + their 2/3/4 vectors and the
// 16/8-bit lattice (MSL has native half/short/ushort/char/uchar), classified via the shared
// shader_block_layout rails. 8/16-lane lattice forms are CPU-only by design (shader vectors cap
// at 4 lanes) — callers key their dedicated fail-closed diagnostic on cpu_only_lattice_width.

module msl_types shared public

require daslib/ast
require daslib/rtti
require daslib/shader_block_layout public

//! MSL spelling of a daslang type, or "" when the type has no supported MSL form.
def public msl_type_name(t : TypeDecl?) : string {
    if (t == null) {
        return ""
    }
    let bt = t.baseType
    if (bt == Type.tBool) {
        return "bool"
    }
    let cls = scalar_class(bt)
    if (cls < 0) {
        return ""
    }
    let w = scalar_width(bt)
    var base = ""
    if (cls == 2) {
        base = w == 32 ? "float" : "half"
    } elif (cls == 0) {
        base = w == 32 ? "int" : (w == 16 ? "short" : "char")
    } else {
        base = w == 32 ? "uint" : (w == 16 ? "ushort" : "uchar")
    }
    let cc = component_count(bt)
    return cc > 1 ? "{base}{cc}" : base
}

//! MSL spelling for a buffer/uniform ELEMENT — the layout-bearing position. das packs vectors
//! tightly (float3 = 12B, half3 = 6B, byte3 = 3B) while non-packed MSL 3-vectors stride padded
//! (float3 = 16B, half3 = 8B); with unified memory the das array IS the buffer, so 3-lane
//! elements must take MSL's packed_T3 spelling (identical bytes to das). 1/2/4-lane sizes match
//! the plain spelling already.
def public msl_buffer_elem_name(t : TypeDecl?) : string {
    let plain = msl_type_name(t)
    if (empty(plain)) {
        return ""
    }
    return component_count(t.baseType) == 3 ? "packed_{plain}" : plain
}
