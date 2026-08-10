// Tutorial AUDIO-09: Playback Status
//
// This tutorial covers:
//   - Reading a sound's status snapshot with get_sound_status
//   - Watching a sound advance through its AudioChannelState lifecycle
//   - Detecting that a one-shot sound has finished
//   - Reading mixer utilization with get_audio_stats
//
// The audio thread publishes a snapshot per sound on every mix; you read the
// latest one whenever you want. Reading owns nothing — there is no handle to
// create, register or release, and your read never makes the mixer wait.
//
// Run: daslang.exe tutorials/dasAudio/09_playback_status.das

options gen2
options persistent_heap
options indenting = 4

require audio/audio_boost
require daslib/fio
require math

// ──────────────────────────────────────────────────────────────────────────
// Helper — a short (non-looping) tone so the sound finishes on its own
// ──────────────────────────────────────────────────────────────────────────

def generate_short_tone(seconds : float) : array<float> {
    let n = int(float(MA_SAMPLE_RATE) * seconds)
    return <- [for (x in range(n)); sin(2.0 * PI * 440.0 * float(x) / float(MA_SAMPLE_RATE))]
}

[export]
def main() {
    print("AUDIO-09: Playback Status\n\n")
    with_audio_system() {
        var tone <- generate_short_tone(0.3)
        let sid = play_sound_from_pcm(MA_SAMPLE_RATE, 1, tone)
        assert(sid != INVALID_SID, "failed to start sound")
        print("Playing a 0.3s tone, SID = {sid}\n")

        // ──────────────────────────────────────────────────────────────────
        // Poll the status until the sound reports `stopped` (or we give up
        // after ~2s), printing each state transition we observe. The SID is
        // the only thing you need — no setup call precedes this loop.
        // ──────────────────────────────────────────────────────────────────
        var last_state = AudioChannelState.starting
        var reached_stopped = false
        for (_i in range(100)) {
            let s = get_sound_status(sid)
            if (s.state != last_state) {
                print("  state: {s.state}  (position={int(s.playback_position)} frames, queue={s.stream_que_length})\n")
                last_state = s.state
            }
            if (s.state == AudioChannelState.stopped) {
                reached_stopped = true
                break
            }
            sleep(20u)
        }

        print("  final observed state: {last_state}\n")
        // Detecting completion is the point of the status snapshot, so confirm
        // the one-shot tone really ran through to `stopped` (0.3s tone, ~2s window).
        assert(reached_stopped, "sound never reached the stopped state within the poll window")

        // A sound the mixer has finished with reads back as `stopped`, so the
        // same call answers "is this still playing?" for any SID you hold —
        // including one that ended long ago.
        let still_playing = is_sound_playing(sid)
        assert(!still_playing, "finished sound still reports as playing")

        // ──────────────────────────────────────────────────────────────────
        // The mixer publishes its own snapshot the same way. It refreshes
        // about once a second, so early in a short run it reads back zero.
        // ──────────────────────────────────────────────────────────────────
        let stats = get_audio_stats()
        print("\nmixer utilization: {stats.utilization_pct}%  (hrtf {stats.hrtf_count}/{stats.total_3d})\n")

        print("\nDone!\n")
    }
}
