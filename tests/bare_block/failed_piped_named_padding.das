options gen2
expect 30341

require dastest/testing_boost public

// A piped block on a named call lands on the next positional slot. Unlike a regular
// piped call, it does NOT pad across a default parameter to reach a later block param
// (full padding for named calls is a follow-up). Here 'body' is last, behind the
// defaulted 'opt', so the block cannot reach it and the call does not resolve.
def sec(tag : int; opt : int = 0; body : block<() : int>) : int {
    return tag + opt + invoke(body)
}

[test]
def test_named_piped_no_padding(t : T?) {
    sec(5, opt = 3) {
        return 1
    }
}
