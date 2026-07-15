#include <doctest/doctest.h>
#include "daScript/daScript.h"
#include "daScript/misc/job_que.h"
#include "daScript/simulate/aot_builtin_jobque.h"

#include <atomic>
#include <chrono>
#include <thread>

using namespace das;

TEST_CASE("team dispatch serializes concurrent callers") {
    const int oldCap = JobQue::get_default_threads_cap();
    JobQue::set_default_threads_cap(4);
    {
        JobQue jq;
        jq.setTeamMode(true);
        jq.setWorkerLimit(4);

        std::atomic<bool> start{false};
        std::atomic<int> ready{0};
        std::atomic<int> activeA{0};
        std::atomic<int> activeB{0};
        std::atomic<bool> overlapped{false};
        std::atomic<int> chunksA{0};
        std::atomic<int> chunksB{0};

        auto dispatch = [&](std::atomic<int> & mine, std::atomic<int> & other,
                            std::atomic<int> & chunks) {
            ready.fetch_add(1, std::memory_order_release);
            while (!start.load(std::memory_order_acquire)) std::this_thread::yield();
            for (int iteration = 0; iteration != 32; ++iteration) {
                jq.teamParallelFor(16, [&](int, int) {
                    mine.fetch_add(1, std::memory_order_acq_rel);
                    if (other.load(std::memory_order_acquire) != 0)
                        overlapped.store(true, std::memory_order_release);
                    std::this_thread::sleep_for(std::chrono::microseconds(20));
                    chunks.fetch_add(1, std::memory_order_relaxed);
                    mine.fetch_sub(1, std::memory_order_acq_rel);
                });
            }
        };

        std::thread a(dispatch, std::ref(activeA), std::ref(activeB), std::ref(chunksA));
        std::thread b(dispatch, std::ref(activeB), std::ref(activeA), std::ref(chunksB));
        while (ready.load(std::memory_order_acquire) != 2) std::this_thread::yield();
        start.store(true, std::memory_order_release);
        a.join();
        b.join();

        CHECK_FALSE(overlapped.load());
        CHECK_EQ(chunksA.load(), 32 * 16);
        CHECK_EQ(chunksB.load(), 32 * 16);
    }
    JobQue::set_default_threads_cap(oldCap);
}

TEST_CASE("team dispatch caller override is thread-local") {
    CHECK(get_jobque_thread_team_mode(nullptr, nullptr));
    set_jobque_thread_team_mode(false, nullptr, nullptr);
    CHECK_FALSE(get_jobque_thread_team_mode(nullptr, nullptr));

    bool childEnabled = false;
    std::thread child([&]() { childEnabled = get_jobque_thread_team_mode(nullptr, nullptr); });
    child.join();
    CHECK(childEnabled);

    set_jobque_thread_team_mode(true, nullptr, nullptr);
    CHECK(get_jobque_thread_team_mode(nullptr, nullptr));
}
