/* src/test/modules/test_seqscan_tiebreak/test_seqscan_tiebreak--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION test_seqscan_tiebreak" to load this file. \quit

CREATE FUNCTION test_seqscan_tiebreak(seqscan_first bool)
RETURNS text
STRICT
AS 'MODULE_PATHNAME' LANGUAGE C;
