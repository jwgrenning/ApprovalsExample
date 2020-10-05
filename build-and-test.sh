mkdir  -p build
pushd build

cmake ..
cmake --build .
ctest . --output-on-failure

popd