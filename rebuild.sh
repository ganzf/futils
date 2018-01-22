#!/bin/bash

rm -rf build
mkdir build
cd build
cmake ..
make -j4
cd ../projects/fender/demo
./demoExe
