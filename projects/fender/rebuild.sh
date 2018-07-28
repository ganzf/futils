rm -rf build
mkdir build
cd build
cmake ..
make
cp libfender.a ../release
echo '> libfender.a built and moved to release folder'
# cp libfender.a ../demo          

# cd ../demo
# rm -rf build
# mkdir build
# cd build
# cmake ..
# make
# cd ..
# ./demo
# cd ..
