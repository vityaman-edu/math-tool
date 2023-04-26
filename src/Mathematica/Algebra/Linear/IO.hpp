#pragma once

#include "Mathematica/Algebra/Linear/Vector.hpp"
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

}