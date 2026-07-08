The MD_BOOST module provides Markdown generation helpers: GitHub-flavored table
rendering with aligned columns and per-column alignment, plus small text utilities
(bold, cell-separator escaping). Numeric cell formatting is left to the caller (the
``"{x:.2f}"`` interpolation-format form); this module handles layout and alignment.

All functions and symbols are in "md_boost" module, use require to get access to it.

.. code-block:: das

    require daslib/md_boost
