options gen2
options indenting = 4

module audio_record shared private
//! Microphone capture: enumerate input devices, start/stop recording, drain samples, record-to-WAV.
//!
//! Capture runs on its own device, independent of playback. The audio-thread callback fills a
//! lock-free ring; scripts drain it on the main thread with `sound_record_read`. Samples are
//! interleaved 32-bit float at the native rate/channels you request — resample or downmix
//! separately (e.g. via the `ma_resampler_*` bindings) if you need a different format.

require audio public
require audio/audio_wav public
require daslib/fio

struct public AudioDeviceInfo {
    //! A capture (microphone) device, as returned by `sound_record_list_devices`.
    name : string           //!< Human-readable device name.
    is_default : bool       //!< True if this is the system default input device.
    index : int             //!< Index to pass as `device_index` to `sound_record_start` / `record_to_wav`.
}

def public sound_record_list_devices() : array<AudioDeviceInfo> {
    //! Enumerate available capture (microphone) devices. Pass an entry's `index` to
    //! `sound_record_start` / `record_to_wav` as `device_index`, or -1 for the system default.
    let n = sound_record_device_count()
    return <- [for (i in range(n));
        AudioDeviceInfo(name = sound_record_device_name(i),
            is_default = sound_record_device_is_default(i), index = i)]
}

def public record_to_wav(fname : string; seconds : float; rate : int = 44100; channels : int = 1; device_index : int = -1) : bool {
    //! Record `seconds` of audio from the microphone into a 16-bit PCM WAV file. Blocks until done.
    //! Returns false if the capture device fails to open or produces no audio.
    if (!sound_record_start(rate, channels, rate, device_index)) {
        return false
    }
    var samples : array<float>
    var scratch : array<float>
    scratch |> resize(rate * channels)   // ~1s drain buffer
    let total_frames = int(float(rate) * seconds)
    var got_frames = 0
    var stall_ms = 0
    while (got_frames < total_frames) {
        let n = sound_record_read(scratch)
        if (n > 0) {
            let base = length(samples)
            samples |> resize(base + n * channels)
            for (i in range(n * channels)) {
                samples[base + i] = scratch[i]
            }
            got_frames += n
            stall_ms = 0
        } else {
            sleep(5u)
            stall_ms += 5
            break if (stall_ms > 2000)   // device produced nothing for ~2s — bail rather than hang
        }
    }
    sound_record_stop()
    return false if (got_frames == 0)   // device opened but produced nothing — don't leave an empty WAV behind
    write_wav(fname, samples, uint(rate), channels)
    return true
}
