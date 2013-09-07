#!/usr/bin/env bash
set -e
HERE=$(dirname $(readlink -f $0))
$HERE/run_doxygen.sh
mkdir -p $HERE/build
cd $HERE/build
cmake $HERE
make lint
make test
