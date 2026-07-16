# Workspace hygiene

- Never use a deployment directory as a scratch directory. Put diagnostic logs under a dedicated
  `logs/` directory and benchmark inputs/results under a dedicated temporary directory.
- Clean up files created for probes, benchmarks, and abandoned launches when the work is complete.
  Preserve active process logs, current deployment artifacts, user data, and one useful rollback
  artifact unless the user explicitly asks to remove them too.
