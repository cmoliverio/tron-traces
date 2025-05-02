#!/bin/sh

rm -rf build lib/*

cmake -B build . -DCMAKE_INSTALL_PREFIX=$(qtpaths --install-prefix)

make -s -B -C build