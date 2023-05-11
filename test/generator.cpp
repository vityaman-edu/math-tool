#include "generator.hpp"
#include <cstdlib>
#include <cassert>

// TODO: use c++11 random features
int random_int(const int left, const int right) {
  assert(left <= right);
  return rand() % (right - left) + left; // NOLINT
}

// TODO: use c++11 random features
size_t random_size(const size_t limit) {
  return rand() % limit; // NOLINT
}
