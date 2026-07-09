options gen2

// a named-argument call CAN now take a piped block: the block becomes the
// trailing positional argument (it used to be a parse error, error[30347]).
require dastest/testing_boost public

struct Holder {
    v : int
}

def setv(self : Holder; _caption : string; blk : block<() : int>; x : int = 0) : int {
    return self.v + x + invoke(blk)
}

def freefn(tag : int; blk : block<() : int>; scale : int = 1) : int {
    return tag + scale * invoke(blk)
}

[test]
def test_method_named_piped_block(t : T?) {
    let h = Holder(v = 100)
    let r = h.setv("go", x = 5) {
        return 20
    }
    t |> equal(r, 125)
}

[test]
def test_freefn_named_piped_block(t : T?) {
    let r = freefn(3, scale = 10) {
        return 4
    }
    t |> equal(r, 43)
}
