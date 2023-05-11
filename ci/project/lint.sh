set -o errexit

cd $(dirname -- "$0"; )
cd ../..

echo 'Formatting...'
find src test \( -name "*.h" -o -name "*.cpp" \) > build/sources.txt
clang-format \
    -i --dry-run \
    --style=file \
    -sort-includes \
    --files=build/sources.txt

echo 'Linting...'
clang-tidy -header-filter=.* -p ./compile_commands.json src/*.cpp test/*.cpp
