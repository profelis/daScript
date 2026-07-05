options gen2

require dastest/testing_boost public
require dasllama/dasllama_math
require daslib/jobque_boost
require math

// Work-proportional dispatch shaping: lanes_for_work boundaries + per-regime caps, and the
// 3-arg matmul_chunks / matmul_chunks_gemv shapers (the inline signal, wave alignment, grain
// floors). Pure shaping math — no kernels, no model. The shapers read get_dispatch_lanes(),
// so every case runs inside with_job_que; knobs are restored after each case.

def private restore_shaping_defaults() {
    set_target_chunk_work(1_000_000l)
    set_gemv_lane_cap(0)
    set_batch_lane_cap(0)
    set_matmul_min_chunk_rows(16)
    set_matmul_min_chunk_rows_gemv(64)
    set_gemv_wave_fill(true)
}

[test]
def test_lanes_for_work(t : T?) {
    with_job_que() {
        restore_shaping_defaults()
        let lanes = get_dispatch_lanes()
        t |> run("boundary: 1 lane below 2x target (the old 2M inline boundary)") @(t : T?) {
            t |> equal(lanes_for_work(1l, 0), 1)
            t |> equal(lanes_for_work(1_999_999l, 0), 1, "just under 2x target stays inline")
            t |> equal(lanes_for_work(2_000_000l, 0), min(2, lanes), "2x target = first parallel work")
            t |> equal(lanes_for_work(5_500_000l, 0), min(5, lanes), "work/target lanes in the mid band")
        }
        t |> run("huge work saturates to full dispatch lanes (structural guard)") @(t : T?) {
            t |> equal(lanes_for_work(1_000_000_000_000l, 0), lanes, ">=1e9-scale work invites every lane")
        }
        t |> run("caps clamp; 0 = uncapped; cap beyond lanes is inert") @(t : T?) {
            t |> equal(lanes_for_work(1_000_000_000_000l, 1), 1, "cap 1 forces the inline signal")
            t |> equal(lanes_for_work(1_000_000_000_000l, 2), min(2, lanes))
            t |> equal(lanes_for_work(1_000_000_000_000l, lanes + 100), lanes, "cap above lanes clamps to lanes")
        }
        t |> run("target knob moves the boundary; extremes force always-inline / always-parallel") @(t : T?) {
            set_target_chunk_work(1_000l)
            t |> equal(lanes_for_work(2_000l, 0), min(2, lanes), "smaller target parallelizes earlier")
            set_target_chunk_work(1l << 62l)
            t |> equal(lanes_for_work(1_000_000_000_000l, 0), 1, "huge target = never parallel")
            set_target_chunk_work(1l)
            t |> equal(lanes_for_work(int64(lanes) * 10l, 0), lanes, "target 1 = full lanes for any real matmul")
            restore_shaping_defaults()
        }
    }
}

[test]
def test_matmul_chunks_batch(t : T?) {
    with_job_que() {
        restore_shaping_defaults()
        let lanes = get_dispatch_lanes()
        let huge = 1_000_000_000_000l
        t |> run("sub-2x-target work returns the inline signal") @(t : T?) {
            t |> equal(matmul_chunks(4096, 4, 1_999_999l), 1)
        }
        t |> run("huge work: whole L-waves under the grain cap, oversplit waves wanted") @(t : T?) {
            // rows admit exactly 2 grain-waves: cap = rows/16 = 2*lanes < want = 4*lanes
            let chunks = matmul_chunks(16 * lanes * 2, 4, huge)
            t |> equal(chunks, 2 * lanes, "grain caps the wave count; result stays wave-aligned")
            // roomy rows: the full oversplit want survives
            t |> equal(matmul_chunks(16 * lanes * 8, 4, huge), 4 * lanes, "want = L x oversplit when grain allows")
        }
        t |> run("tiny rows floor at one chunk (a partial wave beats sub-grain shredding)") @(t : T?) {
            t |> equal(matmul_chunks(8, 4, huge), 1)
        }
        t |> run("grain off = raw L x oversplit; batch cap bounds L") @(t : T?) {
            set_matmul_min_chunk_rows(0)
            t |> equal(matmul_chunks(8, 4, huge), lanes * 4, "grain disabled returns the raw want")
            restore_shaping_defaults()
            set_batch_lane_cap(2)
            let capped = matmul_chunks(16 * lanes * 8, 4, huge)
            t |> equal(capped, min(2, lanes) * 4, "cap bounds the wave width")
            restore_shaping_defaults()
        }
    }
}

[test]
def test_matmul_chunks_gemv(t : T?) {
    with_job_que() {
        restore_shaping_defaults()
        let lanes = get_dispatch_lanes()
        let huge = 1_000_000_000_000l
        t |> run("sub-2x-target work returns the inline signal") @(t : T?) {
            t |> equal(matmul_chunks_gemv(4096, 1, 1_999_999l), 1)
        }
        t |> run("huge work: one chunk per lane once rows clear the GEMV grain") @(t : T?) {
            t |> equal(matmul_chunks_gemv(64 * lanes, 1, huge), lanes)
            t |> equal(matmul_chunks_gemv(64 * lanes * 4, 8, huge), lanes, "oversplit never exceeds one chunk per lane")
        }
        t |> run("GEMV grain floors small row counts; wave fill rounds near-full up") @(t : T?) {
            if (lanes > 2) {
                t |> equal(matmul_chunks_gemv(64, 1, huge), 1, "one grain of rows = one chunk")
            }
            if (lanes >= 2) {
                t |> equal(matmul_chunks_gemv(64 * (lanes - 1), 1, huge), lanes, "within half a wave rounds up to a full wave")
            }
            set_gemv_wave_fill(false)
            if (lanes >= 2) {
                t |> equal(matmul_chunks_gemv(64 * (lanes - 1), 1, huge), lanes - 1, "wave fill off keeps the grain count")
            }
            restore_shaping_defaults()
        }
        t |> run("gemv cap bounds the lanes; grain off = raw L x oversplit") @(t : T?) {
            set_gemv_lane_cap(2)
            t |> equal(matmul_chunks_gemv(64 * lanes, 1, huge), min(2, lanes))
            restore_shaping_defaults()
            set_matmul_min_chunk_rows_gemv(0)
            t |> equal(matmul_chunks_gemv(16, 3, huge), lanes * 3, "grain disabled returns the raw want")
            restore_shaping_defaults()
        }
    }
}
