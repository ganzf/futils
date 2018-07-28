#!/usr/bin/env bash
echo "Creating module $1"
cp -r TEMPLATES $1
mv $1/TEMPLATE.cpp $1/$1.cpp
mv $1/TEMPLATE.hpp $1/$1.hpp
mv $1/TEMPLATE.md $1/$1.md
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/CMakeLists.txt
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/$1.cpp
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/$1.hpp
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/$1.md
echo 'Done'

