cd build
make
cp libfender.a ../demo
cp libfender.a ../release/libfender.a
cd ../demo/build

make
cd ..
./demo
cd ..
