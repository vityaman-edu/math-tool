#pragma once
#include "math/linal/vector.hpp"
#include <array>
#include <cstddef>
#include <cstdlib>
#include <random>

int random_int(int left, int right);

size_t random_size(size_t limit);

template <typename T, size_t N>
std::array<T, N> random_array(int left, int right) noexcept {
  std::array<T, N> array = {0};
  for (size_t i = 0; i < N; i++) {
    array[i] = random_int(left, right);
  }
  return array;
}

template <typename T, size_t N>
math::linal::vector<T, N>
random_vector(int left, int right) noexcept {
  return math::linal::vector<T, N>(
      random_array<T, N>(left, right)
  );
}
