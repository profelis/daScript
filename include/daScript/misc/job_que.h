#pragma once

#include <condition_variable>
#include <deque>
#include <thread>
#include <atomic>

namespace das {
    struct LineInfo;

    // shared tracking counter for JobStatus and Feature
    DAS_API extern atomic<uint64_t> g_jobque_track_total;
    DAS_API extern atomic<uint64_t> g_jobque_track_id;       // ID to detail-trace (0 = none)
    // single job
    typedef function<void()> Job;
    typedef function<void(int,int)> JobChunk;

    typedef uint32_t JobCategory;

    enum class JobPriority : int32_t {
        Inactive = 0x66,                    // just some high number to indicate the thread is inactive
        Minimum = -2,
        Low = -1,
        Medium = 0,
        High = 1,
        Maximum = 2,
        Default = Medium,
        Realtime = High,
    };

    class DAS_API JobStatus {
    public:
        enum { STATUS_MAGIC = 0xdeadbeef };
        JobStatus();
        JobStatus(uint32_t count);
        JobStatus ( JobStatus && ) = delete;
        JobStatus ( const JobStatus & ) = delete;
        virtual ~JobStatus();
        JobStatus & operator = ( JobStatus && ) = delete;
        JobStatus & operator = ( const JobStatus & ) = delete;
        bool Notify();
        bool NotifyAndRelease( LineInfo * at = nullptr );
        bool isReady();
        void Wait();
        void Clear(uint32_t count = 1);
        int addRef( LineInfo * at = nullptr );
        int releaseRef( LineInfo * at = nullptr );
        int size() const;
        int append(int size);
        bool isValid() const { return mMagic==uint32_t(STATUS_MAGIC); }
    // tracking
    public:
        uint64_t        mTrackId = 0;
        JobStatus *     mTrackNext = nullptr;
        JobStatus *     mTrackPrev = nullptr;
        uint32_t        mTrackMagic = 0;
        string          mCreatedAt;
        static JobStatus *  sTrackHead;
        static mutex        sTrackMutex;
        static constexpr uint32_t TRACK_JOB_STATUS = 0xDA5CA001;
        static constexpr uint32_t TRACK_CHANNEL    = 0xDA5CA002;
        static constexpr uint32_t TRACK_LOCKBOX    = 0xDA5CA003;
        static constexpr uint32_t TRACK_STREAM     = 0xDA5CA004;
        // Join poll level (0 = park on the condvar immediately, the default). Wait() polls
        // mRemaining for level*1024*128 relax-rounds before blocking — the ggml hybrid-poll shape
        // and denomination (their --poll 0..100; 50 = their default ≈ 6.5M rounds). With the
        // calling thread executing parallel_for chunks itself, the join wait is just the workers'
        // tail — the poll removes the last per-fork OS park/wake. Global (all wait groups),
        // opt-in via set_jobque_join_spin: polling burns idle CPU.
        static atomic<int32_t> sJoinSpin;
        static void DumpJobQueLeaks();
        static uint64_t CountJobQueLeaks();
        void trackEvent ( LineInfo * at, bool isAddRef );
    protected:
        void trackInsert();
        void trackRemove();
    protected:
        mutable mutex       mCompleteMutex;
        atomic<uint32_t>    mRemaining{0};  // atomic so Wait()'s spin phase can poll lock-free; all writes stay under mCompleteMutex for the condvar protocol
        condition_variable  mCond;
        atomic<int>         mRef{0};
        uint32_t            mMagic = uint32_t(STATUS_MAGIC);
    };

    class JobQue {
    public:
        JobQue();
        JobQue ( const JobQue & ) = delete;
        JobQue ( JobQue && ) = delete;
        JobQue & operator = ( const JobQue & ) = delete;
        JobQue & operator = ( JobQue && ) = delete;
        ~JobQue ();
        bool isEmpty (bool includingMainThreadJobs = false);
        bool areJobsPending(JobCategory category);
        int getNumberOfQueuedJobs();
        int getTotalHwJobs();
        void push(Job && job, JobCategory category, JobPriority priority);
        void pushBatch(vector<Job> && jobs, JobCategory category, JobPriority priority);   // one lock hold + one notify for the whole batch (workers wake-propagate, see JobQue::job)
        bool tryRunOneJob();    // pop one queued job and execute it on the CALLING thread (dispatcher work-stealing at a fork/join); false when the fifo is empty
        void parallel_for ( JobStatus & status, int from, int to, const JobChunk & chunk, JobCategory category, JobPriority priority, int chunk_count = -1, int step = 1 );
        void parallel_for ( int from, int to, const JobChunk & chunk, JobCategory category, JobPriority priority, int chunk_count = -1, int step = 1 );
        void parallel_for_with_consume (int from, int to, const JobChunk & chunk, const JobChunk & consume, JobCategory category, JobPriority priority, int chunk_count = -1, int step = 1);
        static int get_num_threads();
        static int get_num_physical_cores();            // physical cores (SMT siblings collapsed); logical count where topology is unknown
        static void set_default_threads_cap(int cap);   // cap the DEFAULT worker count of a future JobQue (min with the stock rule); 0 = off. DAS_JOBQUE_THREADS still overrides
        static int get_default_threads_cap();
        void EvalOnMainThread(Job && expr);
        void EvalMainThreadJobs();
        void wait();
        void Reset() { wait( ); }
        // Worker spin-before-park window, microseconds (0 = park on the condvar immediately, the
        // default). An idle worker spin-polls the fifo for this long before blocking, so a
        // fork/join burst (e.g. an LLM decode token's back-to-back matmuls) never pays the OS
        // thread-wake per job — measured ~3-4.5us per notify_one to a PARKED worker vs ~0.1us to a
        // spinning one, paid serially by the DISPATCHING thread. Opt-in: spinning burns idle CPU.
        void setWorkerSpin ( int usec ) { mSpinUs = usec; }
        // Team mode (opt-in, sticky): alongside the fifo, workers poll a single published team op
        // and self-serve chunks off one atomic (the ggml threadpool shape). teamParallelFor
        // replaces the whole per-chunk fifo path — no push, no mutex, no wait group, no condvar —
        // with one seq bump per dispatch; join is a spin on a remaining counter. Hybrid poll/park
        // like ggml's --poll: workers spin only for the setWorkerSpin window, then park; a publish
        // that finds parked workers takes the fifo mutex and notifies (zero mutex traffic while
        // everyone spins). Pair with setWorkerSpin — with a 0 window every publish pays the wake.
        // Single dispatcher at a time.
        void setTeamMode ( bool on );
        bool getTeamMode () const { return mTeamMode.load(std::memory_order_relaxed) != 0; }
        int getNumWorkers () const { return mThreadCount.load(); }
        void teamParallelFor ( int numChunks, const JobChunk & work );   // work(chunkIndex, workerSlot); caller participates as slot getNumWorkers()
        // Multi-stage team dispatch: one rendezvous, numStages dependent phases. Every lane
        // (workers + caller) serves stage s chunks, then waits on that stage's remaining counter
        // before advancing — stage s+1 may read anything stage s wrote. One publish + one join
        // for the whole chain; the inter-stage barriers are worker-side spins, so a fused
        // norm→matmul→matmul chain pays the dispatch rendezvous once instead of per op.
        static constexpr int MAX_TEAM_STAGES = 4;
        struct TeamStage {
            const JobChunk * work;      // work(chunkIndex, workerSlot)
            int numChunks;
        };
        void teamParallelForStages ( const TeamStage * stages, int numStages );
    protected:
        struct JobEntry {
            JobEntry( Job&& _function, JobCategory _category, JobPriority _priority) {
                function = das::move(_function);
                priority = _priority;
                category = _category;
            }
            Job                function = nullptr;
            JobPriority        priority = JobPriority::Inactive;
            JobCategory        category = 0;
        };
        struct ThreadEntry {
            ThreadEntry( unique_ptr<thread> && thread) {
                threadPointer = das::move(thread);
            };
            unique_ptr<thread>  threadPointer;
            JobPriority         currentPriority = JobPriority::Inactive;
            JobPriority         appliedPriority = JobPriority::Inactive;  // last priority actually pushed to the OS thread
            JobCategory         currentCategory = 0;
        };
    protected:
        void join();
        void job(int threadIndex);
        void submit(Job && job, JobCategory category, JobPriority priority);
        bool runTeamChunks(int threadIndex, uint32_t & seqSeen);
    protected:
        condition_variable mCond;
        int mSleepMs;
        atomic<bool>    mShutdown{false};
        atomic<int>     mThreadCount{0};
        static thread::id mTheMainThread;
        mutex mFifoMutex;
    protected:
        deque<JobEntry> mFifo;
        vector<ThreadEntry> mThreads;
        atomic<int> mJobsRunning{0};
        atomic<int32_t> mSpinUs{0};
        atomic<int32_t> mFifoCount{0};  // lock-free mirror of mFifo.size() for the spin poll
    protected:
        // team-mode publish slots, one per stage. Publish protocol (seqlock + entrant gate):
        // the dispatcher bumps mTeamSeq to ODD ("publishing"), waits for mTeamInFlight == 0,
        // writes work/remaining/op words for every stage, then bumps mTeamSeq to EVEN. Workers
        // enter with mTeamInFlight++ then re-verify the (even) seq — the seq_cst store/load pairs
        // on both sides make it a Dekker: either the publisher sees the entrant and waits, or the
        // entrant sees the odd/new seq and backs out. So no lane can hold a stage claim word
        // while it is rewritten — which is what makes the INTER-CHAIN stage-order invariant hold
        // (a straggler can never claim a later chain's stage-s chunk before that chain's stage
        // s-1 completed, because it can't be inside the chain loop across a publish at all).
        // Claim words still pack {numChunks:32 | counter:32} so a claim carries its stage's chunk
        // count with the index (overflow self-describes, the single-op epoch-race fix). A valid
        // claim's pending remaining-decrement blocks that stage's barrier, which keeps
        // mTeamWorkS (the dispatcher's stack) alive while dereferenced.
        atomic<int32_t>  mTeamMode{0};
        atomic<uint32_t> mTeamSeq{0};
        atomic<int32_t>  mTeamInFlight{0};
        int              mTeamStageCount = 0;
        atomic<uint64_t> mTeamOpS[MAX_TEAM_STAGES] = {};
        atomic<int32_t>  mTeamRemainingS[MAX_TEAM_STAGES] = {};
        const JobChunk * mTeamWorkS[MAX_TEAM_STAGES] = {};
        // workers currently in cond_wait — the publish-side wake gate. Dekker pair with mTeamSeq
        // (worker: parked++ then read seq; publisher: bump seq then read parked — all four seq_cst),
        // so either the worker sees the new op before sleeping or the publisher sees it parked.
        atomic<int32_t>  mParkedWorkers{0};
        // team dispatch anatomy profiler (env DAS_TEAM_PROF=1): per-op phase aggregates, dumped
        // at queue destruction. Caller-side counters except the two claim-timestamp slots;
        // worker stores happen only under the flag (they perturb the op being measured).
        bool mTeamProf = false;
        atomic<uint64_t> mTeamFirstClaimT{0};   // current op: first worker claim ts (0 = none yet)
        atomic<uint64_t> mTeamLastClaimT{0};    // current op: last worker claim ts
        uint64_t mTPn = 0, mTPchunks = 0, mTPcallerChunks = 0, mTPsolo = 0;
        uint64_t mTPpub = 0, mTPserve = 0, mTPtail = 0, mTPtotal = 0;
        uint64_t mTPreact = 0, mTPreactN = 0, mTPlastRel = 0, mTPlastN = 0;
    protected:
        mutex mEvalMainThreadMutex;
        vector<Job> mEvalMainThread;
    };

    void SetCurrentThreadName ( const string & str );
    void SetCurrentThreadPriority ( JobPriority priority );             // change priority of current thread, 0 - normal, >0 above normal, <0 below normal
}
