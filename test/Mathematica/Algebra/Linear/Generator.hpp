#pragma once

#include "Mathematica/Algebra/Linear/Matrix.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"
#include <array>
#include <cstddef>
#include <random>

using namespace Mathematica;                  // NOLINT
using namespace Mathematica::Algebra::Linear; // NOLINT

int randomInt(int left, int right);

Size randomSize(Size limit);

template <typename T, Size N>
Array<T, N> randomArray(int left, int right) noexcept {
  Array<T, N> array = {0};
  for (auto i = 0; i < N; i++) {
    array[i] = randomInt(left, right);
  }
  return array;
}

template <typename T, Size N>
Vector<T, N> randomVector(int left, int right) noexcept {
  return Vector<T, N>(randomArray<T, N>(left, right));
}

template <typename T, Size R, Size C>
Array<Array<T, C>, R> randomArray2D(int left, int right) noexcept {
  Array<Array<T, C>, R> array = {{}};
  for (auto i = 0; i < R; i++) {
    array[i] = randomArray<T, C>(left, right);
  }
  return array;
}

template <typename T, Size R, Size C>
Matrix<T, R, C> randomMatrix(int left, int right) noexcept {
  return Matrix<T, R, C>(randomArray2D<T, R, C>(left, right));
}
