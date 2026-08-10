options gen2
options indenting = 4
options persistent_heap
options no_unused_function_arguments = false
options no_unused_block_arguments = false

require dastest/testing_boost
require daslib/defer
require daslib/fio
require audio/audio_boost
require jobque
require math

// Device-driven half of the status-snapshot contract: a real sound advancing through its states,
// on miniaudio's NULL backend so it runs headless. The device-free half is tests/audio/test_sound_status.das.
//
// This directory is INTERPRETER-ONLY (gated off under --use-aot in tests/.das_test) — see
// test_device_teardown.das for why no device test is AOT'd.
//
// What this guards: the snapshot is readable the instant play_* returns (seeded on the calling
// thread, so a read that beats the audio thread does not look like "already finished"), it tracks
// the sound to completion, and it needs no registration or teardown — the leak counter is the
// proof of that last part.

def private short_tone(seconds : float) : array<float> {
    let n = int(float(MA_SAMPLE_RATE) * seconds)
    return <- [for (x in range(n)); sin(2.0 * PI * 440.0 * float(x) / float(MA_SAMPLE_RATE))]
}

[test]
def test_status_is_readable_immediately(t : T?) {
    t |> run("status reads `starting` the moment play_sound_from_pcm returns") @(t : T?) {
        sound_set_null_device(true)
        defer() {
            sound_set_null_device(false)
        }
        with_audio_system() {
            var tone <- short_tone(0.2)
            let sid = play_sound_from_pcm(MA_SAMPLE_RATE, 1, tone)
            // No await, no registration: the dispatching thread seeded the slot, so this read
            // cannot land in the window where the audio thread has not processed the add yet.
            let st = get_sound_status(sid)
            t |> equal(st.state, AudioChannelState.starting)
            t |> equal(is_sound_playing(sid), true)
            stop(sid)
        }
    }
}

[test]
def test_status_reaches_stopped(t : T?) {
    t |> run("a one-shot tone advances to stopped and stays there") @(t : T?) {
        sound_set_null_device(true)
        defer() {
            sound_set_null_device(false)
        }
        with_audio_system() {
            var tone <- short_tone(0.2)
            let sid = play_sound_from_pcm(MA_SAMPLE_RATE, 1, tone)
            var reached_stopped = false
            for (_i in range(200)) {
                if (get_sound_status(sid).state == AudioChannelState.stopped) {
                    reached_stopped = true
                    break
                }
                sleep(20u)
            }
            t |> success(reached_stopped, "0.2s tone never reported stopped within a 4s window")
            // A finished sound keeps reading stopped — the answer does not decay or get consumed.
            t |> equal(get_sound_status(sid).state, AudioChannelState.stopped)
            t |> equal(is_sound_playing(sid), false)
        }
    }
}

[test]
def test_status_owns_nothing(t : T?) {
    t |> run("playing and polling many sounds leaves no jobque object behind") @(t : T?) {
        sound_set_null_device(true)
        defer() {
            sound_set_null_device(false)
        }
        let before = count_jobque_leaks()
        with_audio_system() {
            var sids : array<SID>
            for (_i in range(16)) {
                var tone <- short_tone(0.05)
                sids |> push(play_sound_from_pcm(MA_SAMPLE_RATE, 1, tone))
            }
            // Poll every one of them — under the old LockBox status this would be 16 boxes to
            // create, register, join and remove; here it is 16 reads and nothing to clean up.
            for (_i in range(20)) {
                for (sid in sids) {
                    let st = get_sound_status(sid)
                    t |> success(st.stream_que_length >= 0, "queue depth must never read negative")
                }
                sleep(10u)
            }
        }
        let after = count_jobque_leaks()
        t |> equal(after, before)
    }
}

[test]
def test_status_dies_with_the_audio_system(t : T?) {
    t |> run("a torn-down sound stops reporting, and its sid is safe to reuse") @(t : T?) {
        sound_set_null_device(true)
        defer() {
            sound_set_null_device(false)
        }
        var first : SID = INVALID_SID
        with_audio_system() {
            var long_tone <- short_tone(30.0)
            first = play_sound_from_pcm(MA_SAMPLE_RATE, 1, long_tone)
            sleep(40u)
            t |> equal(is_sound_playing(first), true, "the sound should be live inside the block")
        }
        // The system is gone; so is every status it published — a sid outliving its mixer must not
        // keep answering `playing` forever.
        t |> equal(get_sound_status(first).state, AudioChannelState.stopped)

        // A fresh system restarts the sid counter, so the next sound very likely gets `first` back.
        // It must report ITS own progress, never the torn-down sound's.
        with_audio_system() {
            var fresh <- short_tone(5.0)
            let second = play_sound_from_pcm(MA_SAMPLE_RATE, 1, fresh)
            let early = get_sound_status(second)
            t |> equal(early.state, AudioChannelState.starting, "a new sound starts at `starting`, not mid-playback")
            t |> equal(early.playback_position, 0ul, "a reused sid must not inherit a position")
            sleep(120u)
            t |> equal(is_sound_playing(second), true, "the new sound should still be running")
        }
    }
}
