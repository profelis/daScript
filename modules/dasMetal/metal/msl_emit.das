options gen2
options indenting = 4

// MSL text emitter (PoC subset). generate_msl lowers one [metal_kernel] class method to a Metal
// compute kernel: @ssbo class members become device-pointer parameters (const when no statement
// writes them), referenced builtin globals become attributed parameters, the body lowers by manual
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
        var binding = -1
        var setIdx = 0
        for (annDecl in fld.annotation) {
            if (annDecl.name == "ssbo") {
                isSsbo = true
            } elif (annDecl.name == "binding" && annDecl.basicType == Type.tInt) {
                binding = annDecl.iValue
            } elif (annDecl.name == "set" && annDecl.basicType == Type.tInt) {
                setIdx = annDecl.iValue
            }
        }
        if (!isSsbo) {
            err(ctx, fld.at, "member `{fld.name}` is not @ssbo — Phase-1 kernels support only @ssbo array<T> members")
            continue
        }
        if (setIdx != 0) {
            err(ctx, fld.at, "member `{fld.name}` has @set = {setIdx} — Metal has no descriptor sets; only @set = 0 (or none) is allowed")
        }
        if (binding < 0) {
            err(ctx, fld.at, "@ssbo member `{fld.name}` has no @binding — every buffer needs an explicit [[buffer(N)]] index")
            continue
        }
        if (fld._type == null || fld._type.baseType != Type.tArray) {
            err(ctx, fld.at, "@ssbo member `{fld.name}` must be array<T>; got {fld._type == null ? "?" : describe(fld._type)}")
            continue
        }
        let elem = msl_type_name(fld._type.firstType)
        if (empty(elem)) {
            err(ctx, fld.at, "@ssbo member `{fld.name}` element type {describe(fld._type.firstType)} has no MSL form (Phase-1 set: 32-bit scalars + 2/3/4 vectors)")
            continue
        }
        let fldName = string(fld.name)
        for (existing, m in keys(ctx.members), values(ctx.members)) {
            if (m.binding == binding) {
                err(ctx, fld.at, "@ssbo members `{existing}` and `{fldName}` share @binding = {binding} — bindings must be unique within a kernel class")
            }
        }
        ctx.renames[fldName] = msl_safe_name(fldName)
        ctx.members[fldName] = MslMember(msl_name = msl_safe_name(fldName), elem = elem, binding = binding, written = false)
    }
    if (empty(ctx.errors) && empty(ctx.members)) {
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
        scan_body(ctx, (e as ExprOp2).left)
        scan_body(ctx, (e as ExprOp2).right)
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

def private op2_census_type(t : TypeDecl?) : string {
    if (t == null) {
        return "?"
    }
    if (t.baseType == Type.tFloat) {
        return "f32"
    } elif (t.baseType == Type.tInt) {
        return "i32"
    } elif (t.baseType == Type.tUInt) {
        return "u32"
    }
    return "?"
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
    }
    return ""
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
        return "{(e as ExprConstUInt).value}u"
    } elif (e is ExprConstFloat) {
        note(ctx, "const.float")
        return "{(e as ExprConstFloat).value}f"
    } elif (e is ExprConstBool) {
        note(ctx, "const.bool")
        return (e as ExprConstBool).value ? "true" : "false"
    } elif (e is ExprVar) {
        let ev = e as ExprVar
        let name = string(ev.name)
        if (ev.varFlags.local || ev.varFlags.argument || ev.varFlags._block) {
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
        err(ctx, ef.at, "field access `.{fieldName}` is not a kernel-class member access — Phase-1 lowers only self.<@ssbo member>")
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
        let opName = op2_census_name(string(op2.op))
        if (empty(opName)) {
            err(ctx, op2.at, "operator `{op2.op}` is not in the Phase-1 set (+ - * /)")
            return "/*op {op2.op}*/"
        }
        let l = emit_value(ctx, op2.left)
        let r = emit_value(ctx, op2.right)
        note(ctx, "op.{opName}.{op2_census_type(op2._type)}")
        return "({l} {op2.op} {r})"
    }
    err(ctx, e.at, "expression {e.__rtti} is not in the Phase-1 MSL subset")
    return "/*{e.__rtti}*/"
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
            if (v.init == null) {
                err(ctx, v.at, "local `{v.name}` has no initializer — Phase-1 locals must initialize at declaration")
                continue
            }
            let vname = string(v.name)
            ctx.renames[vname] = msl_safe_name(vname)
            let init = emit_value(ctx, v.init)
            note(ctx, "stmt.let")
            lines |> push("{indent}{tname} {ctx.renames[vname]} = {init};")
        }
    } elif (e is ExprCopy) {
        let ec = e as ExprCopy
        let l = emit_value(ctx, ec.left)
        let r = emit_value(ctx, ec.right)
        note(ctx, "stmt.assign")
        lines |> push("{indent}{l} = {r};")
    } else {
        err(ctx, e.at, "statement {e.__rtti} is not in the Phase-1 MSL subset")
    }
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
        errors |> push("[metal_kernel] `{fn.name}` must take no parameters beyond self — Phase-1 kernels read/write only @ssbo members")
        return ""
    }
    ctx.self_name = string(fn.arguments[0].name)
    scan_members(ctx, fn)
    scan_body(ctx, fn.body)
    var body_lines : array<string>
    emit_stmt(ctx, fn.body, "    ", body_lines)

    var params : array<string>
    params |> reserve((ctx.members |> length) + (ctx.builtins_used |> length))
    var ordered <- [for (name in keys(ctx.members)); name]
    ordered |> sort() $(a, b : string) : bool {
        let ba = ctx.members?[a] ?. binding ?? 0
        let bb = ctx.members?[b] ?. binding ?? 0
        return ba < bb
    }
    for (name in ordered) {
        let m = ctx.members[name]
        if (m.written) {
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
        join(body_lines, "\n"),
        "\n\}\n"
    ]
    for (kind in keys(ctx.census)) {
        census |> insert(kind)
    }
    return join(chunks, "")
}

