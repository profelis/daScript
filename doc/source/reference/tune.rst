.. _tune:

==========================================================================
Kernel tuning — ``[tune]`` and the per-app tune sidecar
==========================================================================

``llvm/daslib/llvm_tune`` turns **one reference function into a tuned kernel
family**: a grid of code-generation permutations, a per-app record of which
one wins, and a small policy rail that keeps an application honest about
whether it is running tuned code. It sits on top of ``[llvm_code]`` (the
JIT-time external code generator), so the family only *generates* under the
LLVM JIT; on every other tier the reference body runs verbatim.

The design goal is that a shipped application reaches *its own box's* floor
with **defaults that are data** — a small JSON sidecar — rather than a fork
of the kernels per machine. The winners are compile-time stamps: the front
end reads the sidecar and stamps the winning permutation onto the function
before codegen.

The sidecar is **per-app**: ``<app>.tune.json`` beside the app — the root
script this process runs (the first ``.das`` on the command line), or the
binary itself when there is none (standalone exe, embedded host).
``DAS_TUNE_MANIFEST`` overrides the location outright. A sidecar **older than
the running binary is stale** and reads as absent everywhere — a rebuilt
binary invalidates every measured winner, so copied-around stale files can
never resurrect dead measurements.

.. note::

   This is the ``[tune]`` framework (the ``[llvm_code]`` generator grid). An
   application's own loop-hint profile (e.g. dasLLAMA's ``[tuned]`` macro)
   tunes a different thing, but shares the same sidecar file — perm winners
   under ``"kernels"``, library runtime knobs under ``"runtime"``.

Overview
========

.. code-block:: das

    options gen2
    require llvm/daslib/llvm_tune

    // one reference function, a grid of [llvm_code] generator permutations,
    // and a per-ISA fallback for an app with no sidecar yet.
    [tune_perm(kstep = 1), tune_perm(kstep = 2), tune_perm(kstep = 4),
     tune(gen = "mylib::gemm_gen", fallback = "kstep2")]
    def gemm(a, b, c : float?; n : int) : void {
        // reference implementation — runs on the interpreter, AOT, and any
        // target the generator declines. Never edited per box.
    }

At compile time exactly one winner is stamped onto ``gemm``:

* the sidecar entry for ``gemm`` when one exists (this app has been tuned on
  this box, and the sidecar is not stale),
* else the ``fallback=`` permutation (a generic per-ISA default),
* else the reference body.

A harness discovers the winner by benching the whole grid, then records it in
the sidecar. The next compile picks it up. Nothing about ``gemm``'s callers
changes — the annotated function *is* the real symbol.

The annotations
===============

``[tune_perm(...)]``
--------------------

One grid row. Its arguments are passed verbatim to the ``[llvm_code]``
generator (they become the generator's parameters and fold into the JIT DLL
cache key). ``suffix="..."`` overrides the auto-derived variant name;
``requires="feat"`` is a fallback-eligibility hint (a comma-separated AND of
``|``-separated OR alternatives, matched against the host CPU features plus the
``DAS_JIT_*_FORCE_FEATURES`` overrides).

``[tune(gen="key", fallback="suffix")]``
----------------------------------------

Closes a bracket of ``[tune_perm]`` rows (annotations apply in declaration
order; ``tune`` consumes the rows banked before it). ``gen=`` is the
``[llvm_code]`` generator key. ``fallback=`` is a ``;``-separated chain tried in
declaration order — the first permutation whose ``requires=`` hint passes on
this box is the manifest-less default; ``reference`` forces the original body.
The tuned function needs an **explicit return type**.

``[tune_companion(fn="sibling", gen="key")]``
---------------------------------------------

Listed between the ``[tune_perm]`` rows and ``tune(...)``. Stamps a sibling
function with the **same** permutation from the same manifest entry — the
two-function stamp, so a kernel and (say) its repack-layout query can never
desync, JIT-time declines included. The sibling is a plain function declared
earlier in the same module, with an explicit return type.

The mode contract
=================

The ``DAS_TUNE_MODE`` environment variable selects the compile-time behavior:

``normal`` (default)
    Stamp exactly one winner onto the function (manifest > ``fallback=`` >
    reference). No variant stubs are emitted; a reference-row-only
    ``<name>_variants()`` registry still exists so harness code compiles in
    every mode.

``tune`` / ``test``
    Stamp the full grid as ``<name>__<suffix>`` clones plus the
    ``<name>_variants()`` registry (name → function-pointer rows). A harness
    benches them and records the winner (``tune``), or bit-exact-gates every
    variant against the reference row (``test``).

.. note::

   A sidecar with **no entry** for a function falls through to its
   ``fallback=`` — a sidecar written before a kernel family landed must not
   silently drop that family to the reference tier. An explicit ``"reference"``
   entry forces the original body.

Tuner wiring — ``[tune_scope]``
===============================

A library that owns tuned kernels declares one scope:

.. code-block:: das

    [tune_scope(name = "mylib", tuner = "../harness/tune_mylib.das")]
    struct private MyLibTuneScope {}

``tuner=`` (resolved against the declaring file) names the harness that
regenerates this library's winners; the policy rail and ``--tune`` run it with
``DAS_TUNE_MANIFEST`` pointed at the app sidecar. The winners themselves live
in the ONE per-app file — every library's tuner **upserts its own keys** and
preserves everyone else's (that upsert is the isolation contract; "is this
scope tuned" is per-key completeness, not file existence). Reading winners
needs no scope at all — every ``[tune]`` resolves against the app sidecar.

Application policy — ``[tune_policy]`` and ``--tune``
=====================================================

An application declares what to do when a scope's kernels are missing from the
sidecar at compile time (a stale sidecar counts as missing). The annotation
goes on ``main`` (the ``auto`` / ``restart`` flavors prepend a runtime guard
to its body):

.. code-block:: das

    [export, tune_policy(missing = "auto")]
    def main {
        // ...
    }

.. list-table::
   :header-rows: 1
   :widths: 12 88

   * - ``missing``
     - behavior when a scope's sidecar entries are absent or stale
   * - ``fallback``
     - stamp ``fallback=`` silently (the default everywhere, also with no annotation)
   * - ``warn``
     - loud compile-time banner with the exact tuner command
   * - ``error``
     - fail the compile with the same message — the dev mode
   * - ``auto``
     - tune at startup (a guard runs each missing scope's tuner), then **re-exec**
       the process; the fresh compile stamps the winners. One launch, then it runs.
   * - ``restart``
     - like ``auto`` but no re-exec — tune at startup, then exit asking for a
       manual restart.

``--tune`` after ``--`` on the application's command line forces the tune path
even when the sidecar is complete (a re-tune; the flag is stripped from the
re-exec so the child converges). ``DAS_TUNE_POLICY`` overrides the declared
value — ``DAS_TUNE_POLICY=fallback`` is the CI kill switch.

.. note::

   Tuning cannot happen mid-compile: the tuner is a separate daslang process,
   and adopting its winners means new compile-time stamps regardless. That is
   why ``auto`` tunes at runtime and re-execs into a fresh compile rather than
   stamping in place — which also keeps the winners cross-module-safe (a
   required library's kernels are stamped at their own ``[tune]`` time, not
   mutated after the fact).

Standalone builds
=================

A frozen artifact must not demand or run tuning:

* **Cross-box artifacts** (``policies.tune_frozen`` — set by the ``-aot`` C++
  generator and by dastest's AST serializer) are fully tune-free — every tune
  annotation is inert, only the reference-row registries are emitted. Per-box
  stamps would otherwise desync the artifact against the box that consumes it.
* **AOT-consuming runs** (``policies.aot``) are tune-free only when the JIT is
  off: a stamp changes the function's semantic hash, so a stamped function
  would fail the AOT link. Under ``-jit`` the JIT supersedes AOT bodies and
  tuned stamps stay live.
* **Standalone exe** (``llvm-jit -exe``) still *stamps* — an exe built beside a
  sidecar ships those winners (a local-use artifact by definition), and one
  built without ships the generic ``fallback=`` stamps — but the policy rail
  is dead (no ``[tune_policy]``, no ``--tune``). A native exe carrying any
  ``[llvm_code]`` kernel also *targets the build box* (CPU **and** feature
  gates, decided before the target-flag pass) so the stamped generators
  actually emit instead of declining to their reference bodies on the
  generic-CPU rail; a kernel-free exe stays generic/redistributable.

Sidecar location and staleness
==============================

The sidecar is ``<app>.tune.json`` beside the app: ``utils/myapp/main.das``
reads and writes ``utils/myapp/main.tune.json``; a standalone exe (or an
embedded host with no ``.das`` on its command line) uses the binary's own stem.
The app identity is the first ``.das`` argument before ``--`` on the process
command line — macro time and runtime read the same argv, so compile-time
stamps and the harness write API always agree on the file. No declaration is
needed; ``DAS_TUNE_MANIFEST`` overrides the location, and
``set_tune_manifest_runtime_path`` points just the get/set APIs elsewhere for
self-managed harnesses.

A sidecar whose mtime **predates the running binary's** is stale: it reads as
absent (stamps fall back, the policy rail re-tunes), and the first
``tune_manifest_set`` resets it to a fresh document. Measurements never
outlive the binary that made them.

Runtime status — ``tune_status()``
==================================

``tune_status()`` returns one row per ``[tune]`` function — its winning suffix,
the source (``manifest`` / ``fallback`` / ``reference``), the scope, and the
sidecar path. It is populated when the application declares ``[tune_policy]``.
``log_tune_status("myapp")`` is the ready-made "am I tuned?" surface — it logs
the table at ``LOG_INFO`` (``<n>/<total> kernels tuned for this box``, one line
per function, plus a ``--tune`` hint when any kernel is on a non-manifest tier),
and is a no-op when the table is empty. Call it at startup:

.. code-block:: das

    log_tune_status("myapp")   // or iterate tune_status() yourself

Writing a harness
=================

A tuner is an ordinary ``[export] def main`` compiled with
``DAS_TUNE_MODE=tune``, so the ``<name>_variants()`` registry holds the full
grid as function pointers. It benches them (see the measurement discipline in
``modules/dasLLAMA/tune_for_this_box.md`` — interleaved A/B, correctness-gate
every candidate, best-of-N, confirm the winner), then records the winner:

.. code-block:: das

    let ok = tune_manifest_set("gemm", winning_suffix)

``tune_manifest_set`` writes to the ``DAS_TUNE_MANIFEST`` the policy rail sets
when it spawns the harness, so the winner lands in the app's sidecar. It
UPSERTS: other functions' entries and other sections survive. A following
``normal`` compile stamps it.

Sidecar format
==============

A sectioned JSON object — perm winners under ``"kernels"``, library runtime
knobs under ``"runtime"`` (owned by the library that reads them), and
``"provenance"`` (who wrote it) refreshed on every write:

.. code-block:: json

    {
        "kernels" : { "gemm" : "kstep4", "gemm_gemv" : "reference" },
        "provenance" : { "binary" : "...", "platform" : "windows", "arch" : "x86_64" }
    }

It is a per-app, per-box artifact — gitignored (``*.tune.json``), and any
change re-keys the JIT DLL cache automatically (the winning permutation's args
fold into the DLL basename).

.. seealso::

   ``modules/dasLLAMA/tune_for_this_box.md`` — a worked application of this
   framework (the dasLLAMA gen GEMM family), including the measurement
   discipline that separates a real win from a benchmark artifact, and the
   ``dasllama-server`` / ``ask`` / ``wav2txt`` trio sharing one box's winners.
