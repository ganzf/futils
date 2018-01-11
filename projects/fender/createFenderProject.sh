#!/bin/bash

cp -r ./fenderGettingStarted "$1"
echo "Created $1 directory."
sed -i "s/TEMPLATE_NAME/$1/g" $1/CMakeLists.txt
echo "Updated CMakeLists.txt"
