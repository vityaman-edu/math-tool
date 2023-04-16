set -o errexit

export CXX=/usr/bin/clang++ && cmake -Wno-dev -S . -B build
cmake --build build
cd build
cp compile_commands.json ../compile_commands.json
cd ..
