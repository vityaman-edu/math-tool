set -o errexit

echo 'Formatting...'
find src test \( -name "*.h" -o -name "*.cpp" \) > build/sources.txt
clang-format \
    -i --dry-run \
    --style=file \
    -sort-includes \
    --files=build/sources.txt

echo 'Linting...'
clang-tidy \
    --checks=*,-llvmlibc-callee-namespace,-llvmlibc-restrict-system-libc-headers,-llvmlibc-implementation-in-namespace,-fuchsia-trailing-return,-altera-unroll-loops,-cppcoreguidelines-pro-bounds-constant-array-index,-fuchsia-default-arguments-calls,-modernize-use-trailing-return-type,-google-readability-namespace-comments,-llvm-namespace-comment,-fuchsia-overloaded-operator,-google-readability-todo,-llvm-header-guard,-llvm-include-order,-cppcoreguidelines-special-member-functions,-hicpp-special-member-functions \
    --header-filter=.* \
    --format-style=.clang-format \
    --use-color \
    --warnings-as-errors=* \
    -p ./compile_commands.json \
    src/*.cpp test/*.cpp
