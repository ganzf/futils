cd build
make -j6
cp libfender.a ../demo
cp libfender.a ../release/libfender.a
cd ../demo/build

make -j6
cd ..
./demo
cd ..
