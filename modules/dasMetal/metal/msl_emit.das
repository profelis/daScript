options gen2
options indenting = 4

// MSL text emitter (Phase-3 subset: full scalar/vector arithmetic, comparisons, logical, control
// flow, threadgroup memory + barriers + simdgroup intrinsics). generate_msl lowers one
// [metal_kernel] class method to a Metal compute kernel: @ssbo class members become device-pointer
// parameters (const when no statement writes them), @uniform members become constant-address-space
// reference parameters, @workgroup members become threadgroup declarations at the top of the kernel
// body, referenced builtin globals become attributed parameters, the body lowers by manual
// recursion. Every construct records a census kind at its emit site (gate B: the union across all
// test fixtures must equal declared_msl_census, both directions — text has no disassembler, so the
// census IS the emitter's coverage proxy).

module msl_emit shared public

require msl_types
require daslib/ast
require daslib/ast_boost
require daslib/rtti
require daslib/strings_boost
require strings

struct public MslEmitConfig {
    kernel_name : string    // "" -> the method name (class-prefix stripped)
}

struct private MslMember {
    msl_name : string
    elem : string
    binding : int
    written : bool
    uniform : bool
    workgroup : bool
    wg_dim : int            // @workgroup fixed-array count; -1 = scalar/vector
}

struct private MslCtx {
    errors : array<string>
    census : table<string>
    members : table<string; MslMember>          // das field name -> lowering
    builtins_used : table<string>               // referenced builtin globals (gl_*)
    renames : table<string; string>             // das identifier -> MSL-safe identifier
    self_name : string
}

// MSL reserves the C++14 keyword set plus its own address-space/type keywords; colliding
// identifiers get a trailing underscore
let private MSL_RESERVED : table<string> <- {
    "kernel", "device", "constant", "thread", "threadgroup", "vertex", "fragment",
    "half", "short", "char", "uchar", "ushort", "auto", "template", "typename",
    "using", "namespace", "constexpr", "new", "delete", "this", "class", "struct",
    "union", "signed", "unsigned", "void", "atomic_int", "atomic_uint"
}

def private msl_safe_name(name : string) : string {
    return key_exists(MSL_RESERVED, name) ? "{name}_" : name
}

def private err(var ctx : MslCtx; at : LineInfo; msg : string) {
    ctx.errors |> push("{msg} at line {int(at.line)}")
}

// ===== builtin globals (name-keyed, mirroring spirv_emit's classifier) =====

def private builtin_msl_info(name : string) : tuple<ok : bool; mslType : string; attr : string> {
    if (name == "gl_GlobalInvocationID") {
        return (ok = true, mslType = "uint3", attr = "thread_position_in_grid")
    } elif (name == "gl_LocalInvocationID") {
        return (ok = true, mslType = "uint3", attr = "thread_position_in_threadgroup")
    } elif (name == "gl_WorkGroupID") {
        return (ok = true, mslType = "uint3", attr = "threadgroup_position_in_grid")
    } elif (name == "gl_NumWorkGroups") {
        return (ok = true, mslType = "uint3", attr = "threadgroups_per_grid")
    } elif (name == "gl_WorkGroupSize") {
        return (ok = true, mslType = "uint3", attr = "threads_per_threadgroup")
    } elif (name == "gl_LocalInvocationIndex") {
        return (ok = true, mslType = "uint", attr = "thread_index_in_threadgroup")
    } elif (name == "gl_SubgroupInvocationID") {
        return (ok = true, mslType = "uint", attr = "thread_index_in_simdgroup")
    } elif (name == "gl_SubgroupSize") {
        return (ok = true, mslType = "uint", attr = "threads_per_simdgroup")
    } elif (name == "gl_NumSubgroups") {
        return (ok = true, mslType = "uint", attr = "simdgroups_per_threadgroup")
    } elif (name == "gl_SubgroupID") {
        return (ok = true, mslType = "uint", attr = "simdgroup_index_in_threadgroup")
    }
    return (ok = false, mslType = "", attr = "")
}

// ===== member + builtin scans =====

def private scan_members(var ctx : MslCtx; fn : FunctionPtr) {
    for (fld in fn.classParent.fields) {
        if ((fld.name == "__rtti" || fld.name == "__finalize") ||
                (fld._type != null && (fld._type.baseType == Type.tFunction || fld._type.baseType == Type.tLambda))) {
            continue
        }
        var isSsbo = false
        var isUniform = false
        var isWorkgroup = false
        var binding = -1
        var setIdx = 0
        for (annDecl in fld.annotation) {
            if (annDecl.name == "ssbo") {
                isSsbo = true
            } elif (annDecl.name == "uniform") {
                isUniform = true
            } elif (annDecl.name == "workgroup") {
                isWorkgroup = true
            } elif (annDecl.name == "binding" && annDecl.basicType == Type.tInt) {
                binding = annDecl.iValue
            } elif (annDecl.name == "set" && annDecl.basicType == Type.tInt) {
                setIdx = annDecl.iValue
            }
        }
        if (!isSsbo && !isUniform && !isWorkgroup) {
            err(ctx, fld.at, "member `{fld.name}` is neither @ssbo, @uniform, nor @workgroup — kernels support @ssbo array<T> buffers, @uniform scalar/vector values, and @workgroup threadgroup memory")
            continue
        }
        if ((isSsbo ? 1 : 0) + (isUniform ? 1 : 0) + (isWorkgroup ? 1 : 0) > 1) {
            err(ctx, fld.at, "member `{fld.name}` mixes @ssbo/@uniform/@workgroup — pick one")
            continue
        }
        if (setIdx != 0) {
            err(ctx, fld.at, "member `{fld.name}` has @set = {setIdx} — Metal has no descriptor sets; only @set = 0 (or none) is allowed")
        }
        if (isWorkgroup) {
            if (binding >= 0) {
                err(ctx, fld.at, "@workgroup member `{fld.name}` has @binding = {binding} — threadgroup memory is not a bindable buffer")
                continue
            }
            var wgElem = ""
            var wgDim = -1
            if (fld._type != null && fld._type.baseType == Type.tFixedArray && fld._type.firstType != null &&
                    fld._type.firstType.baseType != Type.tFixedArray) {
                wgElem = msl_type_name(fld._type.firstType)
                wgDim = fld._type.fixedDim
            } else {
                wgElem = msl_type_name(fld._type)
            }
            if (empty(wgElem) || (wgDim == 0)) {
                err(ctx, fld.at, "@workgroup member `{fld.name}` must be a scalar, vector, or single-dimension fixed array of those (e.g. uint[64]); got {fld._type == null ? "?" : describe(fld._type)}")
                continue
            }
            let wgName = string(fld.name)
            ctx.renames[wgName] = msl_safe_name(wgName)
            ctx.members[wgName] = MslMember(msl_name = msl_safe_name(wgName), elem = wgElem, binding = -1,
                written = false, uniform = false, workgroup = true, wg_dim = wgDim)
            continue
        }
        if (binding < 0) {
            err(ctx, fld.at, "member `{fld.name}` has no @binding — every buffer needs an explicit [[buffer(N)]] index")
            continue
        }
        var elem = ""
        if (isSsbo) {
            if (fld._type == null || fld._type.baseType != Type.tArray) {
                err(ctx, fld.at, "@ssbo member `{fld.name}` must be array<T>; got {fld._type == null ? "?" : describe(fld._type)}")
                continue
            }
            elem = msl_type_name(fld._type.firstType)
            if (empty(elem)) {
                err(ctx, fld.at, "@ssbo member `{fld.name}` element type {describe(fld._type.firstType)} has no MSL form (32-bit scalars + 2/3/4 vectors)")
                continue
            }
        } else {
            if (fld._type != null && fld._type.baseType == Type.tArray) {
                err(ctx, fld.at, "@uniform member `{fld.name}` must be a scalar or vector value — array members are @ssbo buffers")
                continue
            }
            elem = msl_type_name(fld._type)
            if (empty(elem)) {
                err(ctx, fld.at, "@uniform member `{fld.name}` type {fld._type == null ? "?" : describe(fld._type)} has no MSL form (32-bit scalars + 2/3/4 vectors)")
                continue
            }
        }
        let fldName = string(fld.name)
        for (existing, m in keys(ctx.members), values(ctx.members)) {
            if (m.binding == binding) {
                err(ctx, fld.at, "members `{existing}` and `{fldName}` share @binding = {binding} — bindings must be unique within a kernel class")
            }
        }
        ctx.renames[fldName] = msl_safe_name(fldName)
        ctx.members[fldName] = MslMember(msl_name = msl_safe_name(fldName), elem = elem, binding = binding,
            written = false, uniform = isUniform, workgroup = false, wg_dim = -1)
    }
    var ssboCount = 0
    for (m in values(ctx.members)) {
        if (!m.uniform && !m.workgroup) {
            ssboCount++
        }
    }
    if (empty(ctx.errors) && ssboCount == 0) {
        err(ctx, fn.at, "kernel class `{fn.classParent.name}` has no @ssbo members — a kernel with no buffers cannot observe or produce anything")
    }
}

// Walks an lvalue chain (ExprAt / ExprSwizzle / ExprRef2Value) down to the member ExprField and
// marks that member written; a write to anything else is reported by the emit pass, not here.
def private mark_write_target(var ctx : MslCtx; e : Expression?) {
    if (e == null) {
        return
    }
    if (e is ExprRef2Value) {
        mark_write_target(ctx, (e as ExprRef2Value).subexpr)
    } elif (e is ExprAt) {
        mark_write_target(ctx, (e as ExprAt).subexpr)
    } elif (e is ExprSwizzle) {
        mark_write_target(ctx, (e as ExprSwizzle).value)
    } elif (e is ExprField) {
        let name = string((e as ExprField).name)
        if (key_exists(ctx.members, name)) {
            ctx.members[name].written = true
        }
    }
}

// Pre-scan pass over the body: collects the member write-set (drives device vs device const) and
// the referenced builtin set (drives the attributed parameters). Unhandled node classes are
// reported by the emit pass — this scan stays permissive.
def private scan_body(var ctx : MslCtx; e : Expression?) {
    if (e == null) {
        return
    }
    if (e is ExprRef2Value) {
        scan_body(ctx, (e as ExprRef2Value).subexpr)
    } elif (e is ExprBlock) {
        for (s in (e as ExprBlock).list) {
            scan_body(ctx, s)
        }
    } elif (e is ExprWith) {
        scan_body(ctx, (e as ExprWith).body)
    } elif (e is ExprLet) {
        for (v in (e as ExprLet).variables) {
            scan_body(ctx, v.init)
        }
    } elif (e is ExprCopy) {
        mark_write_target(ctx, (e as ExprCopy).left)
        scan_body(ctx, (e as ExprCopy).left)
        scan_body(ctx, (e as ExprCopy).right)
    } elif (e is ExprOp2) {
        let o2 = e as ExprOp2
        if (o2._type != null && o2._type.baseType == Type.tVoid) {   // compound assignment writes its left side
            mark_write_target(ctx, o2.left)
        }
        scan_body(ctx, o2.left)
        scan_body(ctx, o2.right)
    } elif (e is ExprOp1) {
        let o1 = e as ExprOp1
        let op = string(o1.op)
        if (op == "++" || op == "--" || op == "+++" || op == "---") {
            mark_write_target(ctx, o1.subexpr)
        }
        scan_body(ctx, o1.subexpr)
    } elif (e is ExprOp3) {
        scan_body(ctx, (e as ExprOp3).subexpr)
        scan_body(ctx, (e as ExprOp3).left)
        scan_body(ctx, (e as ExprOp3).right)
    } elif (e is ExprIfThenElse) {
        scan_body(ctx, (e as ExprIfThenElse).cond)
        scan_body(ctx, (e as ExprIfThenElse).if_true)
        scan_body(ctx, (e as ExprIfThenElse).if_false)
    } elif (e is ExprWhile) {
        scan_body(ctx, (e as ExprWhile).cond)
        scan_body(ctx, (e as ExprWhile).body)
    } elif (e is ExprFor) {
        for (src in (e as ExprFor).sources) {
            scan_body(ctx, src)
        }
        scan_body(ctx, (e as ExprFor).body)
    } elif (e is ExprCall) {
        for (arg in (e as ExprCall).arguments) {
            scan_body(ctx, arg)
        }
    } elif (e is ExprReturn) {
        scan_body(ctx, (e as ExprReturn).subexpr)
    } elif (e is ExprAt) {
        scan_body(ctx, (e as ExprAt).subexpr)
        scan_body(ctx, (e as ExprAt).index)
    } elif (e is ExprField) {
        scan_body(ctx, (e as ExprField).value)
    } elif (e is ExprSwizzle) {
        scan_body(ctx, (e as ExprSwizzle).value)
    } elif (e is ExprVar) {
        let ev = e as ExprVar
        if (!(ev.varFlags.local || ev.varFlags.argument || ev.varFlags._block)) {
            let bi = builtin_msl_info(string(ev.name))
            if (bi.ok) {
                ctx.builtins_used |> insert(string(ev.name))
            }
        }
    }
}

// ===== expression emission (returns text; records census + errors in ctx) =====

def private note(var ctx : MslCtx; kind : string) {
    ctx.census |> insert(kind)
}

// scalar class of a type for census keys: f32/i32/u32/bool scalars, f32v/i32v/u32v vectors
// (lane count does not change the emitted text, so the census is lane-agnostic)
def private census_class(t : TypeDecl?) : string {
    if (t == null) {
        return "?"
    }
    let bt = t.baseType
    if (bt == Type.tFloat) {
        return "f32"
    } elif (bt == Type.tInt) {
        return "i32"
    } elif (bt == Type.tUInt) {
        return "u32"
    } elif (bt == Type.tBool) {
        return "bool"
    } elif (bt == Type.tFloat2 || bt == Type.tFloat3 || bt == Type.tFloat4) {
        return "f32v"
    } elif (bt == Type.tInt2 || bt == Type.tInt3 || bt == Type.tInt4) {
        return "i32v"
    } elif (bt == Type.tUInt2 || bt == Type.tUInt3 || bt == Type.tUInt4) {
        return "u32v"
    }
    return "?"
}

def private is_vec_class(cls : string) : bool {
    return cls == "f32v" || cls == "i32v" || cls == "u32v"
}

def private op2_census_name(op : string) : string {
    if (op == "+") {
        return "add"
    } elif (op == "-") {
        return "sub"
    } elif (op == "*") {
        return "mul"
    } elif (op == "/") {
        return "div"
    } elif (op == "%") {
        return "mod"
    } elif (op == "&") {
        return "band"
    } elif (op == "|") {
        return "bor"
    } elif (op == "^") {
        return "bxor"
    } elif (op == "<<") {
        return "shl"
    } elif (op == ">>") {
        return "shr"
    }
    return ""
}

def private cmp_census_name(op : string) : string {
    if (op == "==") {
        return "eq"
    } elif (op == "!=") {
        return "ne"
    } elif (op == "<") {
        return "lt"
    } elif (op == "<=") {
        return "le"
    } elif (op == ">") {
        return "gt"
    } elif (op == ">=") {
        return "ge"
    }
    return ""
}

def private compound_base(op : string) : string {
    if (op == "+=") {
        return "+"
    } elif (op == "-=") {
        return "-"
    } elif (op == "*=") {
        return "*"
    } elif (op == "/=") {
        return "/"
    } elif (op == "%=") {
        return "%"
    } elif (op == "&=") {
        return "&"
    } elif (op == "|=") {
        return "|"
    } elif (op == "^=") {
        return "^"
    } elif (op == "<<=") {
        return "<<"
    } elif (op == ">>=") {
        return ">>"
    }
    return ""
}

// das prints integral floats bare ("{2f}" is "2"), and bare-int + "f" is not a valid MSL literal
def private msl_float_literal(var ctx : MslCtx; at : LineInfo; v : float) : string {
    let s = "{v}"
    if (s == "inf" || s == "-inf" || s == "nan") {
        err(ctx, at, "non-finite float literal has no MSL form")
        return "0.0f"
    }
    if ((s |> find(".")) < 0 && (s |> find("e")) < 0) {
        return "{s}.0f"
    }
    return "{s}f"
}

def private emit_value(var ctx : MslCtx; e : Expression?) : string {
    if (e == null) {
        err(ctx, LineInfo(), "internal: null expression")
        return "/*null*/"
    }
    if (e is ExprRef2Value) {
        return emit_value(ctx, (e as ExprRef2Value).subexpr)
    } elif (e is ExprConstInt) {
        note(ctx, "const.int")
        return "{(e as ExprConstInt).value}"
    } elif (e is ExprConstUInt) {
        note(ctx, "const.uint")
        // das interpolates uint as hex ("{1u}" is "0x1"); go through int64 for a decimal literal
        return "{int64(uint64((e as ExprConstUInt).value))}u"
    } elif (e is ExprConstFloat) {
        note(ctx, "const.float")
        return msl_float_literal(ctx, e.at, (e as ExprConstFloat).value)
    } elif (e is ExprConstBool) {
        note(ctx, "const.bool")
        return (e as ExprConstBool).value ? "true" : "false"
    } elif (e is ExprVar) {
        let ev = e as ExprVar
        let name = string(ev.name)
        // renames also catches for-loop iterators, whose ExprVar flags are not `local`
        if (ev.varFlags.local || ev.varFlags.argument || ev.varFlags._block || key_exists(ctx.renames, name)) {
            if (name == ctx.self_name) {
                err(ctx, ev.at, "`self` used as a value — only member access (self.field) lowers to MSL")
                return "/*self*/"
            }
            note(ctx, "expr.var")
            return ctx.renames?[name] ?? name
        }
        let bi = builtin_msl_info(name)
        if (bi.ok) {
            note(ctx, "expr.builtin.{bi.attr}")
            return name
        }
        err(ctx, ev.at, "global `{name}` is not a supported builtin — kernels reach data only through @ssbo members and builtin IDs")
        return "/*{name}*/"
    } elif (e is ExprField) {
        let ef = e as ExprField
        let fieldName = string(ef.name)
        if (base_is_self(ctx, ef.value) && key_exists(ctx.members, fieldName)) {
            note(ctx, "expr.member")
            return ctx.members[fieldName].msl_name
        }
        err(ctx, ef.at, "field access `.{fieldName}` is not a kernel-class member access — only self.<@ssbo/@uniform member> lowers to MSL")
        return "/*.{fieldName}*/"
    } elif (e is ExprAt) {
        let ea = e as ExprAt
        let sub = emit_value(ctx, ea.subexpr)
        let idx = emit_value(ctx, ea.index)
        note(ctx, "expr.index")
        return "{sub}[{idx}]"
    } elif (e is ExprSwizzle) {
        let sw = e as ExprSwizzle
        let sub = emit_value(ctx, sw.value)
        let compName = fixed_array<string>("x", "y", "z", "w")
        var comps : array<string>
        for (fch in sw.fields) {
            let f = int(fch)
            if (f < 0 || f > 3) {
                err(ctx, sw.at, "swizzle component {f} out of xyzw range")
                return "/*swizzle*/"
            }
            comps |> push(compName[f])
        }
        note(ctx, "expr.swizzle")
        return "{sub}.{join(comps, "")}"
    } elif (e is ExprOp2) {
        let op2 = e as ExprOp2
        let op = string(op2.op)
        if (op2._type != null && op2._type.baseType == Type.tVoid) {
            err(ctx, op2.at, "compound assignment `{op}` used as a value")
            return "/*op {op}*/"
        }
        let cmp = cmp_census_name(op)
        if (!empty(cmp)) {
            let lcls = census_class(op2.left._type)
            let l = emit_value(ctx, op2.left)
            let r = emit_value(ctx, op2.right)
            if (is_vec_class(lcls)) {
                // das vector ==/!= yields a scalar bool (all-equal / any-differ); MSL's yields boolN
                if (op == "==") {
                    note(ctx, "op.eq.{lcls}")
                    return "all({l} == {r})"
                } elif (op == "!=") {
                    note(ctx, "op.ne.{lcls}")
                    return "any({l} != {r})"
                }
                err(ctx, op2.at, "ordered comparison `{op}` on vectors has no scalar das form")
                return "/*op {op}*/"
            }
            note(ctx, "op.{cmp}.{lcls}")
            return "({l} {op} {r})"
        }
        if (op == "&&" || op == "||") {
            let l = emit_value(ctx, op2.left)
            let r = emit_value(ctx, op2.right)
            note(ctx, op == "&&" ? "op.land" : "op.lor")
            return "({l} {op} {r})"
        }
        let opName = op2_census_name(op)
        if (empty(opName)) {
            err(ctx, op2.at, "operator `{op}` is not in the supported MSL set")
            return "/*op {op}*/"
        }
        let cls = census_class(op2._type)
        if (cls == "?") {
            err(ctx, op2.at, "operator `{op}` result type {describe(op2._type)} has no MSL form")
            return "/*op {op}*/"
        }
        let l = emit_value(ctx, op2.left)
        let r = emit_value(ctx, op2.right)
        note(ctx, "op.{opName}.{cls}")
        if (op == "%" && (cls == "f32" || cls == "f32v")) {
            return "fmod({l}, {r})"     // MSL % is integral-only
        }
        return "({l} {op} {r})"
    } elif (e is ExprOp1) {
        let op1 = e as ExprOp1
        let op = string(op1.op)
        if (op == "+") {
            return emit_value(ctx, op1.subexpr)     // unary plus is the identity
        }
        let sub = emit_value(ctx, op1.subexpr)
        if (op == "-") {
            note(ctx, "op.neg.{census_class(op1._type)}")
            return "(-{sub})"
        } elif (op == "!") {
            note(ctx, "op.lnot")
            return "(!{sub})"
        } elif (op == "~") {
            note(ctx, "op.bnot.{census_class(op1._type)}")
            return "(~{sub})"
        } elif (op == "++") {
            note(ctx, "op.preinc")
            return "(++{sub})"
        } elif (op == "--") {
            note(ctx, "op.predec")
            return "(--{sub})"
        } elif (op == "+++") {
            note(ctx, "op.postinc")
            return "({sub}++)"
        } elif (op == "---") {
            note(ctx, "op.postdec")
            return "({sub}--)"
        }
        err(ctx, op1.at, "unary operator `{op}` is not in the supported MSL set")
        return "/*op {op}*/"
    } elif (e is ExprOp3) {
        let op3 = e as ExprOp3
        if (op3.op != "?") {
            err(ctx, op3.at, "ternary operator `{op3.op}` is not supported")
            return "/*op {op3.op}*/"
        }
        let c = emit_value(ctx, op3.subexpr)
        let tv = emit_value(ctx, op3.left)
        let fv = emit_value(ctx, op3.right)
        note(ctx, "op.select")
        return "({c} ? {tv} : {fv})"
    } elif (e is ExprCall) {
        return emit_call_value(ctx, e as ExprCall)
    }
    err(ctx, e.at, "expression {e.__rtti} is not in the supported MSL subset")
    return "/*{e.__rtti}*/"
}

// simdgroup intrinsics are the only calls with a VALUE lowering (metal_builtins declares them for
// float/int/uint; the identity stub bodies never matter here — only the call AST is read)
def private emit_call_value(var ctx : MslCtx; ec : ExprCall?) : string {
    let cname = "{ec.name}"
    let na = length(ec.arguments)
    if (cname == "simd_sum") {
        if (na != 1) {
            err(ctx, ec.at, "simd_sum takes exactly one argument")
            return "/*call {cname}*/"
        }
        let v = emit_value(ctx, ec.arguments[0])
        note(ctx, "call.simd_sum.{census_class(ec._type)}")
        return "simd_sum({v})"
    } elif (cname == "simd_shuffle" || cname == "simd_shuffle_up" ||
            cname == "simd_shuffle_down" || cname == "simd_shuffle_xor") {
        if (na != 2) {
            err(ctx, ec.at, "{cname} takes exactly two arguments")
            return "/*call {cname}*/"
        }
        let v = emit_value(ctx, ec.arguments[0])
        let l = emit_value(ctx, ec.arguments[1])
        note(ctx, "call.{cname}.{census_class(ec._type)}")
        return "{cname}({v}, {l})"
    }
    err(ctx, ec.at, "call `{cname}` is not a supported MSL builtin — user function calls do not lower (a kernel is a single function)")
    return "/*call {cname}*/"
}

def private base_is_self(ctx : MslCtx; e : Expression?) : bool {
    if (e == null) {
        return false
    }
    if (e is ExprRef2Value) {
        return base_is_self(ctx, (e as ExprRef2Value).subexpr)
    }
    let ev = e ?as ExprVar
    return ev != null && ev.name == ctx.self_name
}

// ===== statement emission =====

def private emit_stmt(var ctx : MslCtx; e : Expression?; indent : string; var lines : array<string>) {
    if (e == null) {
        return
    }
    if (e is ExprBlock) {
        for (s in (e as ExprBlock).list) {
            emit_stmt(ctx, s, indent, lines)
        }
    } elif (e is ExprWith) {
        // the typer's with(self) scope wrapper: member access inside is already explicit
        // (self.a[i]), so the wrapper itself is transparent — and census-silent, or the gate
        // would depend on whether the optimizer already dropped it
        emit_stmt(ctx, (e as ExprWith).body, indent, lines)
    } elif (e is ExprLet) {
        for (v in (e as ExprLet).variables) {
            let tname = msl_type_name(v._type)
            if (empty(tname)) {
                err(ctx, v.at, "local `{v.name}` type {describe(v._type)} has no MSL form")
                continue
            }
            let vname = string(v.name)
            ctx.renames[vname] = msl_safe_name(vname)
            if (v.init == null) {
                // das zero-initializes locals declared without an initializer; = {} is MSL's spelling
                note(ctx, "stmt.var.zero")
                lines |> push("{indent}{tname} {ctx.renames[vname]} = \{\};")
            } else {
                let init = emit_value(ctx, v.init)
                note(ctx, v._type.flags.constant ? "stmt.let" : "stmt.var")
                lines |> push("{indent}{tname} {ctx.renames[vname]} = {init};")
            }
        }
    } elif (e is ExprCopy) {
        let ec = e as ExprCopy
        let l = emit_value(ctx, ec.left)
        let r = emit_value(ctx, ec.right)
        note(ctx, "stmt.assign")
        lines |> push("{indent}{l} = {r};")
    } elif (e is ExprOp2) {
        let op2 = e as ExprOp2
        let op = string(op2.op)
        let base = compound_base(op)
        if (op2._type == null || op2._type.baseType != Type.tVoid || empty(base)) {
            err(ctx, op2.at, "operator `{op}` as a statement is not an assignment")
            return
        }
        let l = emit_value(ctx, op2.left)
        let r = emit_value(ctx, op2.right)
        let cls = census_class(op2.left._type)
        note(ctx, "op.{op2_census_name(base)}_assign.{cls}")
        if (base == "%" && (cls == "f32" || cls == "f32v")) {
            lines |> push("{indent}{l} = fmod({l}, {r});")      // MSL % is integral-only
        } else {
            lines |> push("{indent}{l} {op} {r};")
        }
    } elif (e is ExprOp1) {
        let op1 = e as ExprOp1
        let op = string(op1.op)
        let sub = emit_value(ctx, op1.subexpr)
        if (op == "++") {
            note(ctx, "op.preinc")
            lines |> push("{indent}++{sub};")
        } elif (op == "--") {
            note(ctx, "op.predec")
            lines |> push("{indent}--{sub};")
        } elif (op == "+++") {
            note(ctx, "op.postinc")
            lines |> push("{indent}{sub}++;")
        } elif (op == "---") {
            note(ctx, "op.postdec")
            lines |> push("{indent}{sub}--;")
        } else {
            err(ctx, op1.at, "unary `{op}` is not a statement")
        }
    } elif (e is ExprIfThenElse) {
        emit_if(ctx, e as ExprIfThenElse, indent, lines, "")
    } elif (e is ExprWhile) {
        let wh = e as ExprWhile
        let c = emit_value(ctx, wh.cond)
        note(ctx, "stmt.while")
        lines |> push("{indent}while ({c}) \{")
        emit_stmt(ctx, wh.body, indent + "    ", lines)
        lines |> push("{indent}\}")
    } elif (e is ExprFor) {
        emit_for(ctx, e as ExprFor, indent, lines)
    } elif (e is ExprCall) {
        let ec = e as ExprCall
        let cname = "{ec.name}"
        // both lower to Metal's one threadgroup rendezvous+fence: MSL has no execution-free
        // threadgroup memory fence (pre-MSL-3.2), so memoryBarrierShared() strengthens to the full
        // barrier — the same lowering SPIRV-Cross ships under MoltenVK
        if (cname == "barrier" || cname == "memoryBarrierShared") {
            if (!empty(ec.arguments)) {
                err(ctx, ec.at, "{cname}() takes no arguments")
                return
            }
            note(ctx, cname == "barrier" ? "call.barrier" : "call.memory_barrier_shared")
            lines |> push("{indent}threadgroup_barrier(mem_flags::mem_threadgroup);")
        } else {
            err(ctx, ec.at, "call `{cname}` as a statement has no MSL lowering — only barrier() / memoryBarrierShared() sync calls are supported")
        }
    } elif (e is ExprBreak) {
        note(ctx, "stmt.break")
        lines |> push("{indent}break;")
    } elif (e is ExprContinue) {
        note(ctx, "stmt.continue")
        lines |> push("{indent}continue;")
    } elif (e is ExprReturn) {
        let er = e as ExprReturn
        if (er.subexpr != null) {
            err(ctx, er.at, "kernels return void — `return <value>` has no MSL form")
            return
        }
        note(ctx, "stmt.return")
        lines |> push("{indent}return;")
    } else {
        err(ctx, e.at, "statement {e.__rtti} is not in the supported MSL subset")
    }
}

// if/elif/else chain: an if_false that is itself an ExprIfThenElse continues the chain as
// `} else if (...) {` — `opener` carries the closing brace of the previous arm
def private emit_if(var ctx : MslCtx; ite : ExprIfThenElse?; indent : string; var lines : array<string>; opener : string) {
    let c = emit_value(ctx, ite.cond)
    note(ctx, empty(opener) ? "stmt.if" : "stmt.elif")
    lines |> push("{indent}{opener}if ({c}) \{")
    emit_stmt(ctx, ite.if_true, indent + "    ", lines)
    if (ite.if_false == null) {
        lines |> push("{indent}\}")
    } elif (ite.if_false is ExprIfThenElse) {
        emit_if(ctx, ite.if_false as ExprIfThenElse, indent, lines, "\} else ")
    } else {
        note(ctx, "stmt.else")
        lines |> push("{indent}\} else \{")
        emit_stmt(ctx, ite.if_false, indent + "    ", lines)
        lines |> push("{indent}\}")
    }
}

// for (i in range(lo, hi)) -> for (T i = lo, _end_i = hi; i < _end_i; ++i). das evaluates range
// endpoints ONCE at loop entry, so a non-constant end is hoisted into a loop-scoped local (the
// comma-declaration keeps sequential same-name loops from colliding); a body that mutates memory
// the end expression reads stays das-exact. Constant ranges inline the bounds.
def private emit_for(var ctx : MslCtx; fr : ExprFor?; indent : string; var lines : array<string>) {
    if (length(fr.iteratorVariables) != 1 || length(fr.sources) != 1) {
        err(ctx, fr.at, "only a single `for (i in range(...))` loop lowers to MSL")
        return
    }
    let iv = fr.iteratorVariables[0]
    if (iv._type == null || (iv._type.baseType != Type.tInt && iv._type.baseType != Type.tUInt)) {
        err(ctx, iv.at, "for-loop induction variable `{iv.name}` must be int or uint (range/urange source)")
        return
    }
    let isU = iv._type.baseType == Type.tUInt
    let tname = isU ? "uint" : "int"
    var lo = ""
    var hi = ""
    var hiIsConst = false
    // infer may already have folded a literal range(...) into a const-range node — handle both shapes
    if (fr.sources[0] is ExprConstRange) {
        let fromto = unsafe(reinterpret<int2>((fr.sources[0] as ExprConstRange).value))
        lo = "{fromto.x}"
        hi = "{fromto.y}"
        hiIsConst = true
    } elif (fr.sources[0] is ExprConstURange) {
        let fromto = unsafe(reinterpret<uint2>((fr.sources[0] as ExprConstURange).value))
        lo = "{fromto.x}u"
        hi = "{fromto.y}u"
        hiIsConst = true
    } else {
        let src = fr.sources[0] ?as ExprCall
        if (src == null || (src.name != "range" && src.name != "urange")) {
            err(ctx, fr.at, "for-loop source must be range(...) or urange(...)")
            return
        }
        let na = length(src.arguments)
        if (na != 1 && na != 2) {
            err(ctx, fr.at, "range with a step is not supported")
            return
        }
        lo = na == 2 ? emit_value(ctx, src.arguments[0]) : (isU ? "0u" : "0")
        hi = emit_value(ctx, src.arguments[na - 1])
        hiIsConst = src.arguments[na - 1] is ExprConstInt || src.arguments[na - 1] is ExprConstUInt
    }
    let ivName = string(iv.name)
    ctx.renames[ivName] = msl_safe_name(ivName)
    let mn = ctx.renames[ivName]
    note(ctx, "stmt.for")
    if (hiIsConst) {
        lines |> push("{indent}for ({tname} {mn} = {lo}; {mn} < {hi}; ++{mn}) \{")
    } else {
        lines |> push("{indent}for ({tname} {mn} = {lo}, {mn}_end = {hi}; {mn} < {mn}_end; ++{mn}) \{")
    }
    emit_stmt(ctx, fr.body, indent + "    ", lines)
    lines |> push("{indent}\}")
}

// ===== kernel signature + driver =====

[macro_function]
def public kernel_entry_name(fn : FunctionPtr; cfg : MslEmitConfig) : string {
    if (!empty(cfg.kernel_name)) {
        return cfg.kernel_name
    }
    // methods arrive named `Class`method` — the MSL entry point is the bare method name
    let name = "{fn.name}"
    let tick = name |> rfind("`")
    return msl_safe_name(tick >= 0 ? (name |> slice(tick + 1)) : name)
}

//! Lower a [metal_kernel] class method to MSL text. On any error the return is "" and `errors`
//! explains; `census` collects the construct kinds emitted (gate B).
[macro_function]
def public generate_msl(fn : FunctionPtr; var errors : array<string>; cfg : MslEmitConfig; var census : table<string>) : string {
    var ctx : MslCtx
    if (fn == null) {
        errors |> push("generate_msl: null function")
        return ""
    }
    if (fn.classParent == null) {
        errors |> push("[metal_kernel] `{fn.name}` is not a class method — kernels are methods of a class whose @ssbo members declare the buffers")
        return ""
    }
    if ((fn.arguments |> length) != 1) {
        errors |> push("[metal_kernel] `{fn.name}` must take no parameters beyond self — kernels read/write only @ssbo/@uniform members")
        return ""
    }
    ctx.self_name = string(fn.arguments[0].name)
    scan_members(ctx, fn)
    scan_body(ctx, fn.body)
    var body_lines : array<string>
    emit_stmt(ctx, fn.body, "    ", body_lines)

    // @workgroup members are not parameters — MSL has no module-scope threadgroup variables, so
    // each lowers to a threadgroup declaration at the top of the kernel body (name-sorted)
    var tg_lines : array<string>
    var wg_names <- [for (name, m in keys(ctx.members), values(ctx.members)); name; where m.workgroup]
    wg_names |> sort()
    for (name in wg_names) {
        let m = ctx.members[name]
        if (m.wg_dim > 0) {
            note(ctx, "decl.threadgroup_array")
            tg_lines |> push("    threadgroup {m.elem} {m.msl_name}[{m.wg_dim}];")
        } else {
            note(ctx, "decl.threadgroup")
            tg_lines |> push("    threadgroup {m.elem} {m.msl_name};")
        }
    }

    var params : array<string>
    params |> reserve((ctx.members |> length) + (ctx.builtins_used |> length))
    var ordered <- [for (name, m in keys(ctx.members), values(ctx.members)); name; where !m.workgroup]
    ordered |> sort() $(a, b : string) : bool {
        let ba = ctx.members?[a] ?. binding ?? 0
        let bb = ctx.members?[b] ?. binding ?? 0
        return ba < bb
    }
    for (name in ordered) {
        let m = ctx.members[name]
        if (m.uniform) {
            if (m.written) {
                err(ctx, fn.at, "@uniform member `{name}` is written — uniforms are read-only; outputs are @ssbo buffers")
                continue
            }
            note(ctx, "param.uniform")
            params |> push("constant {m.elem}& {m.msl_name} [[buffer({m.binding})]]")
        } elif (m.written) {
            note(ctx, "param.buffer")
            params |> push("device {m.elem}* {m.msl_name} [[buffer({m.binding})]]")
        } else {
            note(ctx, "param.buffer_const")
            params |> push("device const {m.elem}* {m.msl_name} [[buffer({m.binding})]]")
        }
    }
    var bnames <- [for (name in keys(ctx.builtins_used)); name]
    bnames |> sort()
    for (name in bnames) {
        let bi = builtin_msl_info(name)
        note(ctx, "param.builtin.{bi.attr}")
        params |> push("{bi.mslType} {name} [[{bi.attr}]]")
    }

    if (!empty(ctx.errors)) {
        errors |> push_from(ctx.errors)
        return ""
    }

    note(ctx, "preamble")
    note(ctx, "kernel_sig")
    let chunks = [
        "#include <metal_stdlib>\nusing namespace metal;\nkernel void {kernel_entry_name(fn, cfg)}(",
        join(params, ",\n        "),
        ") \{\n",
        empty(tg_lines) ? "" : join(tg_lines, "\n") + "\n",
        join(body_lines, "\n"),
        "\n\}\n"
    ]
    for (kind in keys(ctx.census)) {
        census |> insert(kind)
    }
    return join(chunks, "")
}

