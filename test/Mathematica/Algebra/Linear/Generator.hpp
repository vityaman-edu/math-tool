#pragma once

#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Algebra/Linear/Matrix.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"
#include <array>
#include <cstddef>
#include <random>

using namespace Mathematica;                  // NOLINT
using namespace Mathematica::Algebra::Linear; // NOLINT
using namespace Mathematica::Abstract;        // NOLINT

int randomInt(int left, int right);

Size randomSize(Size limit);

template <typename T, Size N>
Array<Float<T>, N> randomArray(int left, int right) noexcept {
  Array<Float<T>, N> array = {0};
  for (auto i = 0; i < N; i++) {
    array[i] = Float<T>(randomInt(left, right));
  }
  return array;
}

template <typename T, Size N>
Vector<Float<T>, N> randomVector(int left, int right) noexcept {
  return Vector<Float<T>, N>(randomArray<T, N>(left, right));
}

template <typename T, Size R, Size C>
Array<Array<Float<T>, C>, R> randomArray2D(int left, int right) noexcept {
  Array<Array<Float<T>, C>, R> array = {{}};
  for (auto i = 0; i < R; i++) {
    array[i] = randomArray<T, C>(left, right);
  }
  return array;
}

template <typename T, Size R, Size C>
Matrix<Float<T>, R, C> randomMatrix(int left, int right) noexcept {
  return Matrix<Float<T>, R, C>(randomArray2D<T, R, C>(left, right));
}
