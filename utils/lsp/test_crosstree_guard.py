#!/usr/bin/env python3
"""Standalone regression test for the LSP cross-tree guard (lsp_supervisor.crosstree_diagnostic).

Builds two throwaway git-style trees under a tempdir and checks: a file in a different tree than
the binary warns (severity 2, with the right bootstrap hint); a file in the binary's own tree is
silent; and an explicit -project_root that scopes the file suppresses the warning.

Run:  python3 utils/lsp/test_crosstree_guard.py   (exit 0 = pass)
"""
import os
import shutil
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lsp_supervisor as L


def make_tree(base, name, *, with_bin=False, with_mcp=False):
    root = os.path.join(base, name)
    os.makedirs(os.path.join(root, "sub"), exist_ok=True)
    open(os.path.join(root, ".git"), "w").close()  # worktree-style .git file (a dir also works)
    if with_bin:
        os.makedirs(os.path.join(root, "bin"), exist_ok=True)
        open(os.path.join(root, "bin", "daslang"), "w").close()
    if with_mcp:
        open(os.path.join(root, ".mcp.json"), "w").close()
    return root


def main():
    tmp = tempfile.mkdtemp(prefix="lsp_crosstree_")
    try:
        binroot = make_tree(tmp, "binder", with_bin=True)
        wt_bin = make_tree(tmp, "worktree-bin", with_bin=True)              # binary, no mcp
        wt_boot = make_tree(tmp, "worktree-boot", with_bin=True, with_mcp=True)  # bootstrapped
        wt_bare = make_tree(tmp, "worktree-bare")                           # nothing

        s = L.Server()
        s.compiler = os.path.join(binroot, "bin", "daslang")
        s.init_options = {}

        # git_tree_root basics
        assert L.git_tree_root(os.path.join(wt_bin, "sub")) == wt_bin, "git_tree_root walks up to .git"

        # cross-tree, binary-but-no-mcp -> warn with the --no-build hint
        d = s.crosstree_diagnostic(os.path.join(wt_bin, "sub", "x.das"))
        assert d and d["severity"] == 2 and "CROSS-TREE" in d["message"], "cross-tree must warn"
        assert "no MCP config" in d["message"] and "--no-build" in d["message"], "bin-but-no-mcp hint"

        # cross-tree, bootstrapped -> "start a session rooted"
        d2 = s.crosstree_diagnostic(os.path.join(wt_boot, "sub", "x.das"))
        assert d2 and "bootstrapped" in d2["message"] and "session rooted" in d2["message"], "bootstrapped hint"

        # cross-tree, bare -> "isn't bootstrapped"
        d3 = s.crosstree_diagnostic(os.path.join(wt_bare, "sub", "x.das"))
        assert d3 and "isn't bootstrapped" in d3["message"], "not-bootstrapped hint"

        # same tree as the binary -> silent
        assert s.crosstree_diagnostic(os.path.join(binroot, "sub", "y.das")) is None, "same-tree silent"

        # -project_root scoping the file -> suppressed
        s.init_options = {"project_root": wt_bin}
        assert s.crosstree_diagnostic(os.path.join(wt_bin, "sub", "x.das")) is None, "project_root-scoped silent"

        print("OK: LSP cross-tree guard (5 cases)")
    finally:
        shutil.rmtree(tmp, ignore_errors=True)


if __name__ == "__main__":
    main()
