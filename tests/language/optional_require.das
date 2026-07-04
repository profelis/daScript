options gen2
require dastest/testing_boost public

// Optional require: `require ?guard target` loads *target* when module *guard* is available,
// OR when the target's own file resolves (a mounted pure-das package — no C++ module to guard
// on). When neither holds the require is skipped with no error — even if *target* itself does
// not exist (proven below: the second require names a nonexistent target yet this file still
// compiles). The guard-present-but-target-missing case still errors with 20605 (verified by
// hand; module-resolution failures fire before the `expect` line parses, so that case is not
// expressible as a cant_ test).
require ?math math                                  // nolint:STYLE030 — the guarded-load mechanics ARE the test: guard present (math is a core builtin) -> target loaded
require ?no_such_guard_xyz no_such_target_also_xyz  // guard absent, target unresolvable -> skipped
require ?no_such_guard_pkg optional_require_fixture // guard absent, target RESOLVABLE (same-dir das file) -> loaded
// PATH guard (contains '/'): availability = the guard's OWN file resolves; NO target fallback.
// This is the cross-package dependency witness — the target may live in an always-present package
// while depending on an optional one (e.g. dasllama_math_gen guarding on llvm/daslib/llvm_tune).
require ?daslib/fio optional_require_fixture_pathguard        // path guard resolves -> target loaded
require ?daslib/no_such_file_xyz optional_require_fixture_skipme  // path guard unresolvable -> SKIPPED even though the target file resolves

[test]
def test_optional_require_guard(t : T?) {
    // builtin_module_exists is the same availability primitive the require guard uses.
    t |> success(typeinfo builtin_module_exists(math))
    t |> success(!typeinfo builtin_module_exists(no_such_guard_xyz))
    // static_if over an absent guard drops its branch *before name resolution*, so the undefined
    // symbol below is never resolved. This is the invariant that lets a guarded require pair safely
    // with a guarded use of the (possibly-unloaded) target's symbols.
    static_if (typeinfo builtin_module_exists(no_such_guard_xyz)) {
        undefined_symbol_in_dead_branch_xyz()
    } else {
        t |> success(true)
    }
}

[test]
def test_optional_require_path_guard(t : T?) {
    // path guard resolved (daslib/fio is always mounted): the target loaded and its symbols work
    t |> equal(optional_require_fixture_pathguard::pathguard_marker(), 43)
    t |> success(typeinfo builtin_module_exists(optional_require_fixture_pathguard))
    // path guard unresolvable: the require was SKIPPED even though the target file exists on disk —
    // the pin for path-guard semantics (a plain-name guard would have loaded it via the fallback)
    t |> success(!typeinfo builtin_module_exists(optional_require_fixture_skipme))
    static_if (typeinfo builtin_module_exists(optional_require_fixture_skipme)) {
        this_symbol_must_never_resolve_xyz()
    } else {
        t |> success(true)
    }
}

[test]
def test_optional_require_resolvable_das_target(t : T?) {
    // the fixture loaded through the resolvability fallback: its symbols are usable
    t |> equal(optional_require_fixture::fixture_marker(), 42)
    // builtin_module_exists sees SHARED das modules compiled earlier in the program (they are
    // promoted into the global registry) — the static_if pairing works for das contributors too
    t |> success(typeinfo builtin_module_exists(optional_require_fixture))
    static_if (typeinfo builtin_module_exists(optional_require_fixture)) {
        t |> equal(optional_require_fixture::fixture_marker(), 42)
    } else {
        t |> success(false)  // must not be taken: the module is required above
    }
}
