#!/usr/bin/env bash

rm -rf ./build

pushd .
mkdir -p build/debug
cd build/debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=1
make all
popd
