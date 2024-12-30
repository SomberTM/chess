mkdir -p build
cd build
cmake .. -DBUILD_TESTS=OFF
cmake --build . 
