---
title: Pretty things.
date: 2026-07-02 06:52:20
tags:
    - daScript
    - life
---

They are so pretty.

<!-- more -->

Code is the best painkiller. No ifs, no buts. If u been there u can't help but to know. Surprisingly it works even if I'm not the one pushing buttons. Better buttons than daisies.

Now with all this new hardware and full of energy I get to play with new toys.

WASM. Now WASM64. Its because we cross-compile. Its because daslang runs macros in compilation time. Think about it. Like really stop and think, because I did not. Here is your first true downside - cross-compilation needs similar target. There is no 32-bit cross-platform target worth mentioning.

Then you get size differences. Field offset differences. U name it - i've hit it. At the end of the day most things run from most hosts. But if u truly serious about releasing anything - copy our release process. There is one diverging class, and it matters not (I hope).

Next thing u'd want is to have threads. Thats when it kills u. It uses dlmalloc, not wrapped in ~~bacon~~ mutex. Threads are sort of threads. Jobque has no idea how many. Fun times.

Then u'd want audio. Surprise, its a worklet - and it needs async start, sort of. Strudel also needs to run somewhere.

You'd want OpenGL. WebGL. That GL thing which draws GL things on the screen. It's ok - we've been targeting 4.1 all alone - thank you certain produce company. Love your phone, laptop, and maybe something else maybe. Ah, yes, lack of WASM64 support. Loving it. 2/3 is a-okay.

I get it. I honestly get it. It's too fragile. Why give people something that broken. Grey hair? Lol. By the time u done pulling billiard ball would have nothing on ya.

[And yet here we are.](https://daslang.io/examples.html) Particularly Physarum lab. Watch it, and listen. Listen. Move some sliders. Click on canvas. Collapse that ugly imgui window. It's oddly fascinating. Just don't go on safari. Run it locally too - it's in the examples.

I've got so many examples lately. The one from today is hardware raytracing demo via dasVulkan.

![Hardware ray-tracing demo via dasVulkan](https://daslang.io/files/blog/box-of-pixels.png)

dasVulkan shares a lot of dna with dasOpenGL - same homogeneous native das integration. When u author from the same source u can share a lot of code. Or pain (WASM anyone)? I did and there is sure more where it came from. But thats the whole point, for things to homogenise. For things to get pretty.
