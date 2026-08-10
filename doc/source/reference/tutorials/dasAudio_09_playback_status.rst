.. _tutorial_dasAudio_playback_status:

==================================
AUDIO-09 — Playback Status
==================================

.. index::
    single: Tutorial; Playback Status
    single: Tutorial; AudioChannelStatus
    single: Tutorial; get_sound_status
    single: Tutorial; dasAudio

This tutorial covers monitoring a playing sound. Audio runs on its own thread, so
the mixer publishes a snapshot of every sound on each mix, and you read the latest
one whenever you want. This is how you detect that a one-shot sound has finished,
or how full a streaming queue is.

Reading a Sound's Status
========================

The sound id you got from ``play_*`` is all you need. ``get_sound_status`` returns
the newest ``AudioChannelStatus`` the audio thread published for it:

.. das-doc: given var tone : array<float>

.. code-block:: das

   require audio/audio_boost

   let sid = play_sound_from_pcm(MA_SAMPLE_RATE, 1, tone)
   let s = get_sound_status(sid)
   // s.state              : AudioChannelState
   // s.playback_position  : frames played
   // s.consumed_position  : frames of real audio consumed
   // s.stream_que_length  : pending PCM chunks (for streaming sounds)

The read owns nothing. There is no handle to create, attach or release, reading
does not consume the value, and it never makes the mixer wait on you — the
snapshot lives in a lock-free slot that the audio thread writes and you copy out
of. Read one sound every frame, or a hundred, or none.

Watching a Sound Finish
=======================

``AudioChannelState`` is ``starting`` → ``playing`` → ``stopped``, with
``stopping`` during a fade-out and ``paused`` while paused. Poll to watch a
one-shot sound run to completion:

.. das-doc: given let sid : SID = 0ul

.. code-block:: das

   require audio/audio_boost
   require daslib/fio

   for (i in range(100)) {
       break if (get_sound_status(sid).state == AudioChannelState.stopped)
       sleep(20u)
   }

A sound the mixer has finished with reads back as ``stopped``, and so does a sid
that was never played at all. That is deliberate: for the question you actually
ask — "is this still going?" — both answers are the same one, and it means a sid
you kept past the sound's lifetime is still safe to read. ``is_sound_playing``
wraps the same check:

.. das-doc: alt
.. das-doc: given let sid : SID = 0ul

.. code-block:: das

   require audio/audio_boost

   if (!is_sound_playing(sid)) {
       // the sound has ended, or never existed
   }

Mixer Statistics
================

The mixer publishes its own snapshot the same way, refreshed about once a second:

.. code-block:: das

   let stats = get_audio_stats()
   // stats.utilization_pct : mixer CPU over the last window
   // stats.hrtf_count      : channels routed through HRTF
   // stats.total_3d        : active 3D channels

It reads back all-zero until the first window closes.

.. seealso::

   Full source: :download:`tutorials/dasAudio/09_playback_status.das <../../../../tutorials/dasAudio/09_playback_status.das>`

   Previous tutorial: :ref:`tutorial_dasAudio_midi`

   Next tutorial: :ref:`tutorial_dasAudio_global_controls`
