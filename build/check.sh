#!/usr/bin/env bash
HERE=$(dirname $(readlink -f $0))
mkdir -p $HERE/build
cd $HERE/build
cmake $HERE
make lint
make test
