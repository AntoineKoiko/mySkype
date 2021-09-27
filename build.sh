#! /bin/bash

return_code='0'

if [[ -d ./build ]]
then
    echo "build folder already exists, skipping..."
else
    return_code=`mkdir build`
fi

cd build && conan install .. --build=missing && cmake -G "Unix Makefiles" .. && cmake --build .