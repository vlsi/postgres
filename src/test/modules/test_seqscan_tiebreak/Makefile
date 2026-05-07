# src/test/modules/test_seqscan_tiebreak/Makefile

MODULE_big = test_seqscan_tiebreak
OBJS = \
	$(WIN32RES) \
	test_seqscan_tiebreak.o
PGFILEDESC = "test_seqscan_tiebreak - test the has_seqscan tie-breaker in add_path()"

EXTENSION = test_seqscan_tiebreak
DATA = test_seqscan_tiebreak--1.0.sql

REGRESS = test_seqscan_tiebreak

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = src/test/modules/test_seqscan_tiebreak
top_builddir = ../../../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
