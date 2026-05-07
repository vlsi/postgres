/*-------------------------------------------------------------------------
 *
 * test_seqscan_tiebreak.c
 *	  Test the has_seqscan tie-breaker in add_path().
 *
 * Constructs two Path objects with identical costs, rows, pathkeys,
 * parallel_safe, disabled_nodes, and parameterization, but with different
 * has_seqscan flags. add_path() should keep the path without a Seq Scan
 * regardless of insertion order.
 *
 * Copyright (c) 2026, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *		src/test/modules/test_seqscan_tiebreak/test_seqscan_tiebreak.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include "fmgr.h"
#include "nodes/bitmapset.h"
#include "nodes/pathnodes.h"
#include "optimizer/pathnode.h"
#include "optimizer/tlist.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(test_seqscan_tiebreak);

static Path *
make_dummy_path(RelOptInfo *rel, NodeTag pathtype, bool has_seqscan)
{
	Path	   *p = makeNode(Path);

	p->pathtype = pathtype;
	p->parent = rel;
	p->pathtarget = rel->reltarget;
	p->param_info = NULL;
	p->parallel_aware = false;
	p->parallel_safe = true;
	p->parallel_workers = 0;
	p->rows = 1;
	p->disabled_nodes = 0;
	p->startup_cost = 1.0;
	p->total_cost = 1.0;
	p->pathkeys = NIL;
	p->has_seqscan = has_seqscan;
	return p;
}

static RelOptInfo *
make_dummy_rel(void)
{
	RelOptInfo *rel = makeNode(RelOptInfo);

	rel->reloptkind = RELOPT_BASEREL;
	rel->relids = bms_make_singleton(1);
	rel->rows = 1;
	rel->consider_startup = true;
	rel->consider_param_startup = true;
	rel->consider_parallel = true;
	rel->reltarget = create_empty_pathtarget();
	rel->pathlist = NIL;
	rel->partial_pathlist = NIL;
	rel->cheapest_startup_path = NULL;
	rel->cheapest_total_path = NULL;
	rel->cheapest_parameterized_paths = NIL;
	rel->lateral_relids = NULL;
	return rel;
}

/*
 * test_seqscan_tiebreak(seqscan_first bool) returns text
 *
 * If seqscan_first is true, add the Seq Scan path first and the index path
 * second; otherwise reverse the order. In either case, the surviving path
 * must be the one with has_seqscan = false.
 *
 * Returns the pathtype of the surviving path as text. Errors out if the
 * pathlist does not end up with exactly one entry.
 */
Datum
test_seqscan_tiebreak(PG_FUNCTION_ARGS)
{
	bool		seqscan_first = PG_GETARG_BOOL(0);
	RelOptInfo *rel = make_dummy_rel();
	Path	   *p_seq = make_dummy_path(rel, T_SeqScan, true);
	Path	   *p_idx = make_dummy_path(rel, T_IndexScan, false);
	Path	   *survivor;
	const char *name;

	if (seqscan_first)
	{
		add_path(rel, p_seq);
		add_path(rel, p_idx);
	}
	else
	{
		add_path(rel, p_idx);
		add_path(rel, p_seq);
	}

	if (list_length(rel->pathlist) != 1)
		elog(ERROR, "expected one surviving path, got %d",
			 list_length(rel->pathlist));

	survivor = (Path *) linitial(rel->pathlist);
	switch (survivor->pathtype)
	{
		case T_SeqScan:
			name = "SeqScan";
			break;
		case T_IndexScan:
			name = "IndexScan";
			break;
		default:
			name = "other";
			break;
	}

	PG_RETURN_TEXT_P(cstring_to_text(name));
}
