#!/usr/bin/env bash
set -x -e

git clone --depth=1 https://github.com/pgjdbc/pgjdbc.git

git log -1

cd pgjdbc

mvn clean package -B -V
