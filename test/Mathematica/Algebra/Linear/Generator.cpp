#include "Generator.hpp"
#include <cstdlib>
#include <cassert>

// TODO: use c++11 random features
int randomInt(const int left, const int right) {
  assert(left <= right); // NOLINT
  return rand() % (right - left) + left; // NOLINT
}

// TODO: use c++11 random features
Size randomSize(Size limit) {
  return rand() % limit; // NOLINT
}
