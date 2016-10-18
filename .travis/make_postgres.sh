#!/usr/bin/env bash
set -x -e

sudo service postgresql stop

PREFIX=$HOME/pg_head

./configure --prefix=$PREFIX

# Build PostgreSQL from source and start the DB
make && make install && $PREFIX/bin/pg_ctl -D $PREFIX/data initdb && $PREFIX/bin/pg_ctl -D $PREFIX/data -l postgres.log start

sleep 10

cat postgres.log
