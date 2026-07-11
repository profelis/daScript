options gen2
options indenting = 4

// daslang TypeDecl -> MSL type name, PoC subset (32-bit scalars + their 2/3/4 vectors).
// The 16/8-bit lattice (half, short/ushort/uchar vectors) arrives in Phase 4.

module msl_types shared public

require daslib/ast
require daslib/rtti

//! MSL spelling of a daslang type, or "" when the type has no supported MSL form.
def public msl_type_name(t : TypeDecl?) : string {
    if (t == null) {
        return ""
    }
    if (t.baseType == Type.tInt) {
        return "int"
    } elif (t.baseType == Type.tUInt) {
        return "uint"
    } elif (t.baseType == Type.tFloat) {
        return "float"
    } elif (t.baseType == Type.tBool) {
        return "bool"
    } elif (t.baseType == Type.tInt2) {
        return "int2"
    } elif (t.baseType == Type.tInt3) {
        return "int3"
    } elif (t.baseType == Type.tInt4) {
        return "int4"
    } elif (t.baseType == Type.tUInt2) {
        return "uint2"
    } elif (t.baseType == Type.tUInt3) {
        return "uint3"
    } elif (t.baseType == Type.tUInt4) {
        return "uint4"
    } elif (t.baseType == Type.tFloat2) {
        return "float2"
    } elif (t.baseType == Type.tFloat3) {
        return "float3"
    } elif (t.baseType == Type.tFloat4) {
        return "float4"
    }
    return ""
}
