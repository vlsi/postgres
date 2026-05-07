# Copyright (c) 2026, PostgreSQL Global Development Group

test_seqscan_tiebreak_sources = files(
  'test_seqscan_tiebreak.c',
)

if host_system == 'windows'
  test_seqscan_tiebreak_sources += rc_lib_gen.process(win32ver_rc, extra_args: [
    '--NAME', 'test_seqscan_tiebreak',
    '--FILEDESC', 'test_seqscan_tiebreak - test the has_seqscan tie-breaker in add_path()',])
endif

test_seqscan_tiebreak = shared_module('test_seqscan_tiebreak',
  test_seqscan_tiebreak_sources,
  kwargs: pg_test_mod_args,
)
test_install_libs += test_seqscan_tiebreak

test_install_data += files(
  'test_seqscan_tiebreak.control',
  'test_seqscan_tiebreak--1.0.sql',
)

tests += {
  'name': 'test_seqscan_tiebreak',
  'sd': meson.current_source_dir(),
  'bd': meson.current_build_dir(),
  'regress': {
    'sql': [
      'test_seqscan_tiebreak',
    ],
  },
}
