set -o errexit

find src/* test/* > build/sources.txt
clang-format --dry-run --Werror --files=build/sources.txt

clang-tidy \
    --checks=*,-llvmlibc-callee-namespace,-llvmlibc-restrict-system-libc-headers,-llvmlibc-implementation-in-namespace,-fuchsia-trailing-return \
    --header-filter=.* \
    --format-style=.clang-format \
    --use-color \
    --warnings-as-errors=* \
    src/* test/*