#!/usr/bin/env bash

rm -rf ./build

pushd .
mkdir -p build/release
cd build/release
cmake ../.. -DCMAKE_BUILD_TYPE=Release \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=1
make all
popd
