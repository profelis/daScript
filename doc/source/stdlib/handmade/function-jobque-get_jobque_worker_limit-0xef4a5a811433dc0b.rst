Returns the current worker limit set by set_jobque_worker_limit. When no limit is active the value is a large sentinel (INT_MAX) — not 0, which is a real limit meaning all workers dormant.
