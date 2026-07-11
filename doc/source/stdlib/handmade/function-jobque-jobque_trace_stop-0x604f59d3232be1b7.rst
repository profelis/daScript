Stops the per-lane JobQue event tracer armed by jobque_trace_start. Recorded events stay in the rings until the next jobque_trace_start, so jobque_trace_save can still export them after stopping.
