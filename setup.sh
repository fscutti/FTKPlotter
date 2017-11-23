#!/bin/bash
setupATLAS
mkdir build
cp scripts/setenv.sh build
cp scripts/compile.sh build
cd build
source setenv.sh
source compile.sh
source x86_64-slc6-gcc62-opt/setup.sh
