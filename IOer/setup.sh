#!/bin/bash

CWD=`pwd`

FILEDIR=$(dirname "${BASH_SOURCE[0]}")
cd $FILEDIR
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/install ..
make
make install
make test

cd $CWD
