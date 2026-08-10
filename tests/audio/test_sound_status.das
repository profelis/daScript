options gen2
options indenting = 4
options no_unused_function_arguments = false
options no_unused_block_arguments = false

require dastest/testing_boost
require audio/audio_boost

// Device-free half of the status-snapshot contract. get_sound_status reads a lock-free slot
// published by the audio thread, so it answers for ANY sid without a mixer running, without
// registering anything first, and without anything to release afterwards. That "owns nothing"
// property is what these tests pin: a caller may read a sid it never played, one that finished
// long ago, or one from a process with no audio system at all, and always get a sane answer.
//
// The device-driven half (a sound actually advancing starting -> playing -> stopped) lives in
// tests/strudel_device/test_sound_status_device.das, which is gated interpreter-only.

[test]
def test_unknown_sid_reads_stopped(t : T?) {
    t |> run("a sid that was never played reads back stopped") @(t : T?) {
        let st = get_sound_status(0xdead0001ul)
        t |> equal(st.state, AudioChannelState.stopped)
        t |> equal(st.playback_position, 0ul)
        t |> equal(st.consumed_position, 0ul)
        t |> equal(st.stream_que_length, 0)
    }
}

[test]
def test_invalid_sid_reads_stopped(t : T?) {
    t |> run("INVALID_SID reads back stopped rather than faulting") @(t : T?) {
        let st = get_sound_status(INVALID_SID)
        t |> equal(st.state, AudioChannelState.stopped)
    }
}

[test]
def test_is_sound_playing_false_for_unknown(t : T?) {
    t |> run("is_sound_playing is false for a sid the mixer never had") @(t : T?) {
        t |> equal(is_sound_playing(0xdead0002ul), false)
    }
}

[test]
def test_status_read_is_repeatable(t : T?) {
    t |> run("reading a status consumes nothing — the same sid reads the same twice") @(t : T?) {
        let sid : SID = 0xdead0003ul
        let first = get_sound_status(sid)
        let second = get_sound_status(sid)
        t |> equal(first.state, second.state)
        t |> equal(first.playback_position, second.playback_position)
    }
}

[test]
def test_audio_stats_without_mixer(t : T?) {
    t |> run("get_audio_stats reads zeroes when no mixer has published yet") @(t : T?) {
        let s = get_audio_stats()
        t |> equal(s.hrtf_count, 0)
        t |> equal(s.total_3d, 0)
    }
}

// The table is a limit on CONCURRENT sounds, not on how many a session may ever play: a slot goes
// back the moment its channel is gone. These drive the slot layer directly, because through the
// public API the property is only visible as an absence of failure.

[test]
def test_slots_are_recycled(t : T?) {
    t |> run("far more claims than the table holds still all succeed, one at a time") @(t : T?) {
        var failures = 0
        for (i in range(20000)) {
            let sid : SID = 0x51070000ul + uint64(i)
            let slot = _builtin_audio_status_claim(sid)
            if (slot < 0) {
                failures ++
                break
            }
            _builtin_audio_status_release(slot)
        }
        t |> equal(failures, 0, "a released slot must be reusable by the next sound")
    }
}

[test]
def test_claim_is_idempotent_per_sid(t : T?) {
    t |> run("claiming the same sid twice hands back the same slot") @(t : T?) {
        let sid : SID = 0x51080001ul
        let first = _builtin_audio_status_claim(sid)
        t |> success(first >= 0, "first claim must succeed")
        let second = _builtin_audio_status_claim(sid)
        t |> equal(second, first)
        // the audio thread's non-allocating lookup must agree with both
        t |> equal(_builtin_audio_status_find(sid), first)
        _builtin_audio_status_release(first)
        t |> equal(_builtin_audio_status_find(sid), -1)
    }
}

[test]
def test_released_slot_reads_as_gone(t : T?) {
    t |> run("a published snapshot stops being readable once the slot is released") @(t : T?) {
        let sid : SID = 0x51080002ul
        let slot = _builtin_audio_status_claim(sid)
        t |> success(slot >= 0, "claim must succeed")
        var published = AudioChannelStatus(state = AudioChannelState.playing, playback_position = 4242ul)
        _builtin_audio_status_publish(slot, unsafe(addr<void?>(published)), typeinfo sizeof(type<AudioChannelStatus>))
        let seen = get_sound_status(sid)
        t |> equal(seen.state, AudioChannelState.playing)
        t |> equal(seen.playback_position, 4242ul)
        _builtin_audio_status_release(slot)
        t |> equal(get_sound_status(sid).state, AudioChannelState.stopped)
    }
}

[test]
def test_concurrent_capacity(t : T?) {
    t |> run("the table holds thousands of sounds at once, not a fraction of its slots") @(t : T?) {
        // Guards the probing scheme: linear probing clustered badly enough to refuse claims at
        // about half the table, which would surface as sounds silently reporting no status.
        // Stops short of the wall so the test does not depend on the exact ceiling.
        let WANT = 3000
        var held : array<int>
        var granted = 0
        for (i in range(WANT)) {
            let slot = _builtin_audio_status_claim(0x5109000000ul + uint64(i))
            break if (slot < 0)
            held |> push(slot)
            granted ++
        }
        for (s in held) {
            _builtin_audio_status_release(s)
        }
        t |> equal(granted, WANT, "table refused a claim well before it was full")
    }
}
