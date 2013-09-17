#!/usr/bin/env bash
set -e
HERE=$(dirname $(readlink -f $0))
mkdir -p $HERE/build
cd $HERE/build
cmake $HERE
make doc
make lint
make test
make memcheck
