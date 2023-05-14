#pragma once

#include "Mathematica/Algebra/Linear/Matrix.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"
#include <iomanip>
#include <ostream>

namespace Mathematica::Algebra::Linear::IO {

template <typename T, Size N>
std::ostream& operator<<(std::ostream& out, const Vector<T, N>& vec) {
  out << "{ ";
  for (auto i = 0; i < N - 1 && 0 < N; i++) {
    out << vec[i] << ", ";
  }
  if (0 < N) {
    out << vec[N - 1];
  }
  out << " }";
  return out;
}

template <typename F, Size R, Size C>
std::ostream& operator<<(std::ostream& out, const Matrix<F, R, C>& mat) {
  for (auto i = 0; i < R; i++) {
    out << mat[i] << '\n';
  }
  return out;
}

}