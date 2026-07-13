The JOBQUE_PROFILE module wraps the low-level ``jobque_trace_*`` builtins into a
self-describing profiling API: named **categories** with colors for the op tags
stamped via ``profile_tag``, and **markers** — instant "unit" events such as
``token`` or ``frame`` — so saved traces carry their own legend and are navigable
unit-to-unit. Files remain perfetto-compatible; the category and marker tables
ride in a ``jobqueProfile`` sibling key that Perfetto ignores.

See also :doc:`jobque` for the underlying event tracer.

All functions and symbols are in "jobque_profile" module, use require to get access to it.

.. code-block:: das

    require daslib/jobque_profile

Example:

.. code-block:: das

    require daslib/jobque_boost
    require daslib/jobque_profile

    [export]
    def main() {
        with_job_que() {
            let heavy = profile_category("heavy op")     // auto id + palette color
            let tok = profile_marker_id("token")
            profile_start(65536)
            for (i in range(4)) {
                profile_marker(tok, i)                   // unit boundary
                profile_tag(heavy)
                // ... dispatch work ...
            }
            profile_stop()
            profile_save("trace.json")                   // open in Perfetto or the timeline viewer
        }
    }
