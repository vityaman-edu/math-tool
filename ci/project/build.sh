set -o errexit

cmake -S . -B build
cmake --build build
cd build
cp compile_commands.json ../compile_commands.json
cd ..
