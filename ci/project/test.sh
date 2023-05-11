set -o errexit

cd $(dirname -- "$0"; )
cd ../..

cd build
ctest
cd ..
