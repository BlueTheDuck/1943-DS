#!/bin/sh
cd $GITHUB_WORKSPACE
git submodule init
git submodule update
make clean
make build
