cd build
make -j4
cp libfender.a ../demo
cp libfender.a ../release/libfender.a
cd ../demo/build

make -j4
cd ..
./demo
cd ..
