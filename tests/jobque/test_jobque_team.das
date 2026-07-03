options gen2
require dastest/testing_boost public
require daslib/jobque_boost

// Correctness of team mode (set_jobque_team_mode + team_parallel_for): workers self-serve chunks
// off one published atomic instead of per-chunk fifo jobs. Checks the fallback (mode off → one
// inline invoke), coverage/exactly-once across chunk shapes, back-to-back dispatch storms
// (seq-bump reuse, stragglers), fifo parallel_for still working while team mode is on, and
// mode toggling (workers park again after off).

def team_sum_round(t : T?; nj, total : int) {
    var results : array<int>
    results |> resize(total)
    var pr = unsafe(addr(results[0]))
    team_parallel_for(0, total, nj) <| @(job_begin : int; job_end : int) {
        for (i in range(job_begin, job_end)) {
            unsafe(pr[i]) = i * 3 + 1
        }
    }
    var sum = 0
    for (i in range(total)) {
        sum += results[i]
    }
    t |> equal(3 * total * (total - 1) / 2 + total, sum)
    delete results
}

def team_once_round(t : T?; nj, total : int) {
    // every index written exactly once — catches both dropped and double-served chunks
    var hits : array<int>
    hits |> resize(total)
    var pr = unsafe(addr(hits[0]))
    team_parallel_for(0, total, nj) <| @(job_begin : int; job_end : int) {
        for (i in range(job_begin, job_end)) {
            unsafe(pr[i]) += 1
        }
    }
    var bad = 0
    for (i in range(total)) {
        if (hits[i] != 1) {
            bad++
        }
    }
    t |> equal(0, bad)
    delete hits
}

def fifo_sum_round(t : T?; nj, total : int) {
    // plain fifo parallel_for — must keep working while workers also poll the team slot
    var results : array<int>
    results |> resize(total)
    var pr = unsafe(addr(results[0]))
    parallel_for(0, total, nj) $(job_begin, job_end, wg) {
        for (i in range(job_begin, job_end)) {
            unsafe(pr[i]) = i * 3 + 1
        }
        wg |> notify_and_release
    }
    var sum = 0
    for (i in range(total)) {
        sum += results[i]
    }
    t |> equal(3 * total * (total - 1) / 2 + total, sum)
    delete results
}

def team_storm(t : T?; rounds : int) {
    // back-to-back dispatches at several shapes: 1 chunk (inline path), fewer chunks than items,
    // more chunks than workers, more chunks than items (clamp) — exercises seq reuse + stragglers
    for (_r in range(rounds)) {
        team_sum_round(t, 1, 4)
        team_sum_round(t, 4, 16)
        team_sum_round(t, 2 * get_total_hw_jobs(), 4 * get_total_hw_jobs())
        team_once_round(t, 4 * get_total_hw_jobs(), 8 * get_total_hw_jobs())
        team_once_round(t, 64, 7)
    }
}

[test]
def test_jobque_team(t : T?) {
    with_job_que() {
        t |> run("mode off - inline fallback") @(t : T?) {
            team_sum_round(t, 4, 16)
            team_once_round(t, 8, 32)
        }
        t |> run("team mode - no fork pool") @(t : T?) {
            set_jobque_team_mode(true)
            team_storm(t, 5)
            set_jobque_team_mode(false)
        }
        t |> run("team mode - fork pool") @(t : T?) {
            set_jobque_fork_pool(true, true)
            set_jobque_team_mode(true)
            team_storm(t, 10)
            set_jobque_team_mode(false)
        }
        t |> run("fifo while team mode on") @(t : T?) {
            set_jobque_team_mode(true)
            for (_r in range(5)) {
                team_sum_round(t, 4, 16)
                fifo_sum_round(t, 4, 16)
                fifo_sum_round(t, 2 * get_total_hw_jobs(), 4 * get_total_hw_jobs())
            }
            set_jobque_team_mode(false)
        }
        t |> run("workers park again after off") @(t : T?) {
            // team mode off → team_parallel_for falls back inline, fifo path unaffected
            team_sum_round(t, 4, 16)
            fifo_sum_round(t, 4, 16)
        }
        t |> run("production shape") @(t : T?) {
            // team mode + the fork/join knobs it will ship next to
            set_jobque_worker_spin(200)
            set_jobque_batch_dispatch(true)
            set_jobque_join_spin(2)
            set_jobque_team_mode(true)
            team_storm(t, 10)
            set_jobque_team_mode(false)
            set_jobque_join_spin(0)
            set_jobque_batch_dispatch(false)
            set_jobque_worker_spin(0)
        }
    }
}
