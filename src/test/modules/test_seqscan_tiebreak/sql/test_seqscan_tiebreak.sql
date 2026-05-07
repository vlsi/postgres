CREATE EXTENSION test_seqscan_tiebreak;

-- Seq Scan added first, then Index Scan: tie-breaker must drop Seq Scan.
SELECT test_seqscan_tiebreak(seqscan_first => true);

-- Index Scan added first, then Seq Scan: tie-breaker must reject Seq Scan.
SELECT test_seqscan_tiebreak(seqscan_first => false);
