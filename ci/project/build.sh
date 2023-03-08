set -o errexit

cmake -S . -B build
cmake --build build
cd build && ctest
cp compile_commands.json ../compile_commands.json
cd ..
