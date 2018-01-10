#!/bin/bash

# Cloning into teamfcm/futils



if [ ! -d ".dl_futils" ]; then
    echo " - Downloading futils..."
    git clone -b master --single-branch git@github.com:ganzf/futils.git .dl_futils --depth=1
    echo " - Done."
fi

cd .dl_futils
echo "Fetching update..."
git pull origin master
cd ..

if [ ! -d "./futils" ]; then
   mkdir ./futils
fi

ls ./futils > oldUtils
cp .dl_futils/utils/* ./futils/
ls ./futils > newUtils
diff oldUtils newUtils
rm -f oldUtils
rm -f newUtils
cp .dl_futils/projects/fender/release/libfender.a ./lib
cp .dl_futils/projects/fender/include/*.hpp ./include

if [ ! -d "./futils/Components" ]; then
    echo "Creating ./futils/Components..."
    mkdir -p ./futils/Components/
    echo " - Done";
fi

if [ ! -d "./futils/Entities" ]; then
    echo "Creating ./futils/Entities..."
    mkdir -p ./futils/Entities/
    echo " - Done";
fi

if [ ! -d "./futils/Systems" ]; then
    echo "Creating ./futils/Systems..."
    mkdir -p ./futils/Systems/
    echo " - Done";
fi

echo " - Fetching fender *.hpp";
ls ./futils/Components > oldComponents
find .dl_futils/projects/fender/src/Components -type f -name '*.hpp' -exec cp {} ./futils/Components \;
ls ./futils/Components > newComponents
echo "New Components : (may be empty)"
diff oldComponents newComponents
rm -f oldComponents newComponents

ls ./futils/Entities > oldEntities
find .dl_futils/projects/fender/src/Entities -type f -name '*.hpp' -exec cp {} ./futils/Entities \;
ls ./futils/Entities > newEntities
echo "New Entities : (may be empty)"
diff oldEntities newEntities
rm -f oldEntities newEntities

ls ./futils/Systems > oldSystems
find .dl_futils/projects/fender/src/Systems -type f -name '*.hpp' -exec cp {} ./futils/Systems \;
ls ./futils/Systems > newSystems
echo "New Systems : (may be empty)"
diff oldSystems newSystems
rm -f oldSystems newSystems

echo "Update complete."
