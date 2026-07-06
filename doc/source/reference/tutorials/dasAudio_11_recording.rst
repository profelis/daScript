.. _tutorial_dasAudio_recording:

==========================================
AUDIO-11 — Recording from the Microphone
==========================================

.. index::
    single: Tutorial; Recording
    single: Tutorial; Microphone
    single: Tutorial; Capture
    single: Tutorial; Audio

This tutorial covers capturing audio from a microphone with the
``audio/audio_record`` module: enumerating input devices, recording to a WAV
file, and driving the low-level capture loop yourself for live processing.

Capture is independent of playback — you do **not** need ``with_audio_system``.
A dedicated capture device runs on the audio thread and fills a lock-free ring
buffer; your script drains it on the main thread. Samples are interleaved 32-bit
float at the sample rate and channel count you request.

Enumerating Capture Devices
===========================

``sound_record_list_devices`` returns the available microphones. Each
``AudioDeviceInfo`` has a display ``name``, an ``is_default`` flag, and an
``index`` you pass to the recording calls as ``device_index`` (``-1`` means the
system default):

.. code-block:: das

    require audio/audio_record

    for (d in sound_record_list_devices()) {
        let tag = d.is_default ? " (default)" : ""
        print("[{d.index}] {d.name}{tag}\n")
    }

Listing devices does not open the microphone, so it works before any capture
permission prompt.

Recording to a WAV File
=======================

``record_to_wav`` is the one-call path: it opens the default capture device,
records for the requested duration, writes a 16-bit PCM WAV, and returns
``false`` if the device could not be opened (no microphone, or the OS denied
access). Pass a ``device_index`` to target a specific input:

.. code-block:: das

    // fname, seconds, rate = 44100, channels = 1, device_index = -1
    if (record_to_wav("recording.wav", 2.0, 44100, 1)) {
        print("wrote recording.wav\n")
    }

The Manual Capture Loop
=======================

For live processing you drive the loop yourself. ``sound_record_start`` opens
the device; ``sound_record_read`` drains as many buffered frames as fit in your
scratch array, returning the frame count; ``sound_record_stop`` closes the
device. The ``rb_frames`` argument sizes the ring buffer (a sample rate's worth
is about one second of headroom):

.. code-block:: das

    require audio/audio_record
    require audio
    require math

    if (sound_record_start(44100, 1, 44100, -1)) {
        var scratch : array<float>
        scratch |> resize(44100)
        var frames = 0
        var peak = 0.0
        while (frames < 44100) {          // ~1 second
            let n = sound_record_read(scratch)
            if (n > 0) {
                for (i in range(n)) {
                    peak = max(peak, abs(scratch[i]))
                }
                frames += n
            } else {
                sleep(5u)
            }
        }
        sound_record_stop()
        print("peak {peak}, dropped {sound_record_overflow_frames()} frames\n")
    }

``sound_record_overflow_frames`` reports frames the audio thread had to drop
because the ring filled up — a non-zero value means your drain loop fell behind.
``sound_record_available`` reports how many frames are currently buffered, and
``sound_is_recording`` reports whether a capture device is open.

The samples are at the native rate you requested; resample to another rate (for
example 16 kHz mono for speech models) with the ``ma_resampler_*`` bindings.

Running the Tutorial
====================

Run from the project root::

   daslang.exe tutorials/dasAudio/11_recording.das

The tutorial lists the capture devices, records two seconds to ``recording.wav``,
reads the file back to confirm the round-trip, then runs the manual loop for one
second and reports the peak amplitude.

.. note::

   On macOS the microphone is gated by the system privacy settings — the process
   (or the terminal that launched it) must be granted microphone access, or
   capture returns silence. Enumeration is unaffected.

.. seealso::

   Full source: :download:`tutorials/dasAudio/11_recording.das <../../../../tutorials/dasAudio/11_recording.das>`

   Previous tutorial: :ref:`tutorial_dasAudio_global_controls`
