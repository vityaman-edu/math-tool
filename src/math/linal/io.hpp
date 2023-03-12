#pragma once

#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>
#include <iostream>

namespace math::linal::io {

template <typename F, size_t N>
std::ostream&
operator<<(std::ostream& out, const vector<F, N>& vec) {
  out << "{ ";
  for (size_t i = 0; i < N - 1 && N > 0; i++) {
    out << vec[i] << ", ";
  }
  if (N > 0) {
    out << vec[N - 1];
  }
  out << " }";
  return out;
}

template <typename F, size_t R, size_t C>
std::ostream&
operator<<(std::ostream& out, const matrix<F, R, C>& mat) {
  for (size_t i = 0; i < R; i++) {
    out << mat[i] << '\n';
  }
  return out;
}

}