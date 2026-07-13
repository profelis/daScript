options gen2
options indenting = 4

module jobque_profile shared public

//! Self-describing jobque profiling on top of the per-lane event tracer.
//!
//! Wraps the ``jobque_trace_*`` builtins with named **categories** (colored
//! legend entries for the op tags stamped via ``profile_tag``) and **markers**
//! (instant "unit" events such as ``frame`` or ``token``), so saved traces
//! carry their own meaning. Files stay perfetto-compatible; the category and
//! marker tables ride in a ``jobqueProfile`` sibling key viewers read.

require jobque public

// dark-theme viewer hues first (lane-timeline palette), then 4 extra distinct hues
let private DEFAULT_PALETTE = fixed_array<uint>(
    0x5E96DEu, 0x43B08Au, 0xAC82E4u, 0xC39536u, 0xE08563u, 0x4FC3D0u,
    0xD678B4u, 0x8385E8u, 0xD8626Au, 0x9BB556u, 0x7A9AAEu, 0xB08968u)

let public PROFILE_COLOR_BLUE = 0x5E96DEu
let public PROFILE_COLOR_GREEN = 0x43B08Au
let public PROFILE_COLOR_PURPLE = 0xAC82E4u
let public PROFILE_COLOR_AMBER = 0xC39536u
let public PROFILE_COLOR_CORAL = 0xE08563u
let public PROFILE_COLOR_TEAL = 0x4FC3D0u
let public PROFILE_COLOR_MAGENTA = 0xD678B4u
let public PROFILE_COLOR_INDIGO = 0x8385E8u

var private g_categoryIds : table<string; int>
var private g_usedCategoryIds : table<int>
var private g_markerIds : table<string; int>
var private g_nextCategoryId = 1

def private resolve_color(name : string; color : uint) : uint {
    if (color != 0u) return color
    return DEFAULT_PALETTE[int(hash(name) % uint64(12))]
}

def public profile_start(events_per_lane : int = 65536) {
    //! Arm the per-lane trace rings (`events_per_lane` events each; full lanes stop recording).
    jobque_trace_start(events_per_lane)
}

def public profile_stop() {
    //! Disarm tracing. Must be called before `profile_save`.
    jobque_trace_stop()
}

def public profile_save(path : string) : bool {
    //! Write the recorded trace as perfetto-compatible JSON, including the category and
    //! marker registries. Returns false when tracing is still on or nothing was recorded.
    return jobque_trace_save(path)
}

def public profile_tag(tag : int) {
    //! Stamp the current op tag; subsequent chain publishes carry it (viewer color channel).
    jobque_trace_tag(tag)
}

def public profile_category(id : int; name : string; color : uint = 0u) {
    //! Register a named category for an existing tag id (`color` is 0xRRGGBB;
    //! 0 picks from the default palette by name hash).
    g_usedCategoryIds |> insert(id)
    g_categoryIds[name] = id
    jobque_trace_category(id, name, resolve_color(name, color))
}

def public profile_category(name : string; color : uint = 0u) : int {
    //! Register a named category with an auto-assigned tag id (idempotent per name).
    //! Returns the tag to stamp via `profile_tag`.
    var id = g_categoryIds?[name] ?? -1
    if (id < 0) {
        while (g_usedCategoryIds |> key_exists(g_nextCategoryId)) {
            g_nextCategoryId++
        }
        id = g_nextCategoryId++
        g_usedCategoryIds |> insert(id)
        g_categoryIds[name] = id
    }
    jobque_trace_category(id, name, resolve_color(name, color))
    return id
}

def public profile_marker_id(name : string) : int {
    //! Register/look up a marker kind (e.g. "token", "frame"); idempotent per name.
    let existing = g_markerIds?[name] ?? -1
    if (existing >= 0) return existing
    let id = jobque_trace_marker_name(name)
    g_markerIds[name] = id
    return id
}

def public profile_marker(id : int; arg : int = 0) {
    //! Stamp an instant unit boundary on the caller lane (no-op when tracing is off).
    jobque_trace_marker(id, arg)
}

def public profile_marker(name : string; arg : int = 0) {
    //! Convenience form of `profile_marker`; prefer the id form in hot loops.
    jobque_trace_marker(profile_marker_id(name), arg)
}
