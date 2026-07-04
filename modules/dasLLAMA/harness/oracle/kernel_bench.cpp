// kernel_bench — single-thread raw Q8_0 x Q8_0 kernel throughput for llama.cpp/ggml.
// The kernel-to-kernel mirror of dasLLAMA's harness/gemm_1core_probe.das: no graph, no threadpool.
//
// Three kernels per shape:
//   vec_dot  — ggml_vec_dot_q8_0_q8_0 on row-major weights, rows OUTER / tokens INNER (weights
//              streamed once, activation slice cache-resident — the das row-major batch traversal)
//   gemm     — ggml_gemm_q8_0_<mr>x<bl>_q8_0 on repacked weights + interleaved activations, ONE call
//              (their production traversal: 4-token groups OUTER, weights re-streamed ntok/4 times)
//   gemv     — ggml_gemv_q8_0_<mr>x<bl>_q8_0, 1 token on repacked weights (the decode-side kernel)
// gemm/gemv are the arch's repack tier: on arm64+dotprod that is the 4x4 vdotq_laneq family
// (repack traits pick 4x4 on M1; 4x8 needs i8mm). Correctness: gemm/gemv checked vs vec_dot.
//
// Lives in dasLLAMA/harness/oracle/. Build directly against a llama.cpp CPU build (the repack
// symbols are exported from libggml-cpu; no examples/ wiring needed):
//   LCPP=~/Work/llama.cpp
//   clang++ -O3 -std=c++17 -I $LCPP/ggml/include kernel_bench.cpp -o kernel_bench \
//     -L $LCPP/build-cpu/bin -lggml -lggml-cpu -lggml-base -Wl,-rpath,$LCPP/build-cpu/bin

#include "ggml.h"
#include "ggml-cpu.h"

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

// mirror of ggml-common.h block_q8_0 / repack.h block_q8_0x4 (avoids internal-header includes)
struct block_q8_0 {
    uint16_t d;         // fp16 delta
    int8_t   qs[32];
};
struct block_q8_0x4 {
    uint16_t d[4];      // fp16 deltas of the 4 interleaved rows
    int8_t   qs[128];   // 32 groups of 4 bytes, group i from row i%4, bytes (i/4)*4..
};
static_assert(sizeof(block_q8_0) == 34, "block_q8_0 layout");
static_assert(sizeof(block_q8_0x4) == 136, "block_q8_0x4 layout");

extern "C" {
void ggml_quantize_mat_q8_0_4x4(const float * x, void * vy, int64_t k);
void ggml_gemv_q8_0_4x4_q8_0(int n, float * s, size_t bs, const void * vx, const void * vy, int nr, int nc);
void ggml_gemm_q8_0_4x4_q8_0(int n, float * s, size_t bs, const void * vx, const void * vy, int nr, int nc);
}

static void fillf(std::vector<float> & a, int64_t cnt) {
    a.resize((size_t) cnt);
    for (int64_t i = 0; i < cnt; i++) {
        a[(size_t) i] = (float) (i % 13) * 0.1f - 0.6f;
    }
}

static double now_us() {
    using namespace std::chrono;
    return duration<double, std::micro>(steady_clock::now().time_since_epoch()).count();
}

// repack_q8_0_to_q8_0_4_bl with interleave_block=4 (make_block_q8_0x4), minus the tensor plumbing
static void repack_w_4x4(const block_q8_0 * src, block_q8_0x4 * dst, int64_t d, int64_t nb) {
    for (int64_t g = 0; g < d / 4; g++) {
        const block_q8_0 * in = src + g * 4 * nb;
        for (int64_t x = 0; x < nb; x++) {
            block_q8_0x4 * o = dst++;
            for (int r = 0; r < 4; r++) {
                o->d[r] = in[x + r * nb].d;
            }
            for (int i = 0; i < 32; i++) {
                memcpy(o->qs + i * 4, in[x + (i % 4) * nb].qs + (i / 4) * 4, 4);
            }
        }
    }
}

static double best_of(int rounds, int reps, void (*fn)(void *), void * ud) {
    double best = 1e30;
    for (int r = 0; r < rounds; r++) {
        const double t0 = now_us();
        for (int rep = 0; rep < reps; rep++) {
            fn(ud);
        }
        const double us = now_us() - t0;
        if (us < best) {
            best = us;
        }
    }
    return best;
}

struct ShapeCtx {
    int64_t n, d, ntok;
    const ggml_type_traits_cpu * tr;
    size_t row_sz;
    std::vector<uint8_t> wq;       // row-major q8_0 weights
    std::vector<uint8_t> wq4;      // repacked block_q8_0x4 weights
    std::vector<uint8_t> xq;       // row-major q8_0 activations (ntok rows)
    std::vector<uint8_t> xq4;      // interleaved q8_0x4 activations (ntok/4 groups)
    std::vector<float>   y;
};

static void run_vec_dot(void * ud) {
    ShapeCtx & c = *(ShapeCtx *) ud;
    for (int64_t row = 0; row < c.d; row++) {
        const uint8_t * wrow = c.wq.data() + (size_t) row * c.row_sz;
        for (int64_t tk = 0; tk < c.ntok; tk++) {
            c.tr->vec_dot((int) c.n, &c.y[(size_t) (tk * c.d + row)], 0, wrow, 0, c.xq.data() + (size_t) tk * c.row_sz, 0, 1);
        }
    }
}

static void run_gemm(void * ud) {
    ShapeCtx & c = *(ShapeCtx *) ud;
    ggml_gemm_q8_0_4x4_q8_0((int) c.n, c.y.data(), (size_t) c.d, c.wq4.data(), c.xq4.data(), (int) c.ntok, (int) c.d);
}

static void run_gemv(void * ud) {
    ShapeCtx & c = *(ShapeCtx *) ud;
    ggml_gemv_q8_0_4x4_q8_0((int) c.n, c.y.data(), (size_t) c.d, c.wq4.data(), c.xq.data(), 1, (int) c.d);
}

static void bench_shape(const char * name, int64_t n, int64_t d, int64_t ntok, int reps, int rounds) {
    ShapeCtx c;
    c.n      = n;
    c.d      = d;
    c.ntok   = ntok;
    c.tr     = ggml_get_type_traits_cpu(GGML_TYPE_Q8_0);
    c.row_sz = ggml_row_size(GGML_TYPE_Q8_0, n);
    const int64_t nb = n / 32;

    std::vector<float> wf;
    fillf(wf, n * d);
    c.wq.resize(c.row_sz * (size_t) d);
    ggml_quantize_chunk(GGML_TYPE_Q8_0, wf.data(), c.wq.data(), 0, d, n, nullptr);
    c.wq4.resize(c.wq.size());
    repack_w_4x4((const block_q8_0 *) c.wq.data(), (block_q8_0x4 *) c.wq4.data(), d, nb);

    std::vector<float> xf;
    fillf(xf, n * ntok);        // distinct tokens so the gemm's 4-token tiles do real work
    c.xq.resize(c.row_sz * (size_t) ntok);
    for (int64_t tk = 0; tk < ntok; tk++) {
        c.tr->from_float(xf.data() + (size_t) (tk * n), c.xq.data() + (size_t) tk * c.row_sz, n);
    }
    c.xq4.resize(c.row_sz * (size_t) ntok);
    for (int64_t tk = 0; tk < ntok; tk += 4) {
        ggml_quantize_mat_q8_0_4x4(xf.data() + (size_t) (tk * n), c.xq4.data() + (size_t) tk * c.row_sz, n);
    }

    c.y.assign((size_t) (ntok * d), 0.0f);

    // correctness: gemm vs vec_dot (fp assoc differs — expect small diff, not zero)
    std::vector<float> yref((size_t) (ntok * d));
    run_vec_dot(&c);
    yref = c.y;
    run_gemm(&c);
    float md = 0.0f;
    double ref2 = 0.0;
    for (size_t i = 0; i < yref.size(); i++) {
        const float df = c.y[i] - yref[i];
        md = std::max(md, df < 0 ? -df : df);
        ref2 = std::max(ref2, (double) (yref[i] < 0 ? -yref[i] : yref[i]));
    }

    printf("--- %s (n=%lld d=%lld ntok=%lld, x%d) ---\n", name, (long long) n, (long long) d, (long long) ntok, reps);

    const double us_dot = best_of(rounds, reps, run_vec_dot, &c);
    printf("  vec_dot row-major : %7.3f GMAC/s  (%.0f us best-of-%d)\n",
           (double) n * d * ntok * reps / (us_dot * 1e3), us_dot, rounds);

    const double us_gemm = best_of(rounds, reps, run_gemm, &c);
    printf("  gemm_4x4 repacked : %7.3f GMAC/s  (%.0f us best-of-%d)  maxdiff vs vec_dot %.4g (ref max %.4g)\n",
           (double) n * d * ntok * reps / (us_gemm * 1e3), us_gemm, rounds, md, ref2);

    const int gemv_reps = reps * (int) ntok / 4;
    const double us_gemv = best_of(rounds, gemv_reps, run_gemv, &c);
    printf("  gemv_4x4 repacked : %7.3f GMAC/s  (%.0f us best-of-%d, x%d)\n",
           (double) n * d * gemv_reps / (us_gemv * 1e3), us_gemv, rounds, gemv_reps);
}

int main() {
    printf("single-thread raw ggml Q8_0 x Q8_0 kernel throughput (no graph, no threadpool), ntok=128\n\n");
    bench_shape("kv  2048x512  ", 2048, 512, 128, 8, 6);
    bench_shape("qo  2048x2048 ", 2048, 2048, 128, 3, 6);
    bench_shape("w13 2048x5632 ", 2048, 5632, 128, 1, 6);
    bench_shape("w2  5632x2048 ", 5632, 2048, 128, 1, 6);
    return 0;
}
