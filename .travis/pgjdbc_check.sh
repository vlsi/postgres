#!/usr/bin/env bash
set -x -e

git clone --depth=1 https://github.com/pgjdbc/pgjdbc.git

cd pgjdbc

mvn clean package -B -V
