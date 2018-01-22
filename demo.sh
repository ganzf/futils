#!/bin/bash

cd build
make -j4
cp projects/fender/libfender.a ../projects/fender/demo/lib
cd ../projects/fender/demo
./demoExe
