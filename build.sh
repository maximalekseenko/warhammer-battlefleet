rm -r ./bin
rm -r ./build


cmake -S. -B bin -DCMAKE_TOOLCHAIN_FILE="cmake/mac.cmake"
cmake --build bin --clean-first

./build/mac/client

# rm -r ./bin
# cmake -S. -B bin -DCMAKE_TOOLCHAIN_FILE="cmake/win.cmake"
# cmake --build bin --clean-first