#pragma once


#include <iomanip>
#include <ostream>

namespace Mathematica::Algebra::Linear::IO {

template <typename T, size_t N>
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

template <typename F, size_t R, size_t C>
std::ostream& operator<<(std::ostream& out, const Matrix<F, R, C>& mat) {
  constexpr int COL_WIDTH = 5;
  for (size_t i = 0; i < R; i++) {
    out << std::setw(COL_WIDTH) << std::setfill(' ') << mat[i] << '\n';
  }
  return out;
}

}