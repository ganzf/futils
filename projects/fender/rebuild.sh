#!/usr/bin/env bash
echo 'Removing existing build folder'
rm -rf build
mkdir build
cd build
echo 'Building...'
cmake ..
make
cd ../
read -p "What version of the library is it ?" version
echo "Moving files to release folder. Version: ${version}"
dir="./release/$version/"
mkdir -p ${dir}
cp build/libfender.a ${dir}
cp -r "./src/Components/*.hpp" "${dir}/include/"
cp -r "./src/Entities/*.hpp" "${dir}/include/"
cp -r ./bundledSystems/ "${dir}/include/"
rm "${dir}/include/createSystem.sh"
rm -rf "${dir}/include/.TemplateSystem"
echo "> libfender.a built and moved to release folder: ${dir}"