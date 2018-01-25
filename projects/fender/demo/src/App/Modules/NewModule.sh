#!/bin/bash

echo "Creating $1.cpp and $1.hpp : System name will be [$2]"

read -p "Is that right? [y/N] " -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    cp .template.cpp $1.cpp
    cp .template.hpp $1.hpp
    echo "Replacing template elements..."
    sed -i s/_T_ARG1/"$1"/g $1.cpp
    sed -i s/_T_ARG1/"$1"/g $1.hpp
    sed -i s/_T_ARG2/"$2"/g $1.cpp
    sed -i s/_T_ARG2/"$2"/g $1.hpp
    echo "+----------------------+"
    echo "|Done. Please rebuild !|"
    echo "+----------------------+"
    exit
fi
echo "Ok bye !"
