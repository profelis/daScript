options gen2
expect 30341:2

require dastest/testing_boost public

// 'mid' has no default, so the piped block cannot pad across it to reach 'body'
def blocked(tag : int; mid : int; opt : int = 0; body : block<() : int>) : int {
    return tag + mid + opt + invoke(body)
}

// no block parameter at all -> the piped block has nowhere to land
def noblock(tag : int; opt : int = 0) : int {
    return tag + opt
}

[test]
def test_named_piped_cannot_pad(t : T?) {
    blocked(5, opt = 3) {
        return 1
    }
    noblock(5, opt = 3) {
        return 1
    }
}
