#pragma once
#include "math/linal/matrix.hpp"
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
math::linal::Vector<T, N>
random_vector(int left, int right) noexcept {
  return math::linal::Vector<T, N>(
      random_array<T, N>(left, right)
  );
}

template <typename T, size_t R, size_t C>
std::array<std::array<T, C>, R>
random_array_2d(int left, int right) noexcept {
  std::array<std::array<T, C>, R> array = {{}};
  for (size_t i = 0; i < R; i++) {
    array[i] = random_array<T, C>(left, right);
  }
  return array;
}

template <typename T, size_t R, size_t C>
math::linal::Matrix<T, R, C>
random_matrix(int left, int right) noexcept {
  return math::linal::Matrix<T, R, C>(
      random_array_2d<T, R, C>(left, right)
  );
}