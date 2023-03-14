#pragma once

#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>

namespace math::eq::lin::sys {

template <typename F, size_t N>
struct lineqsys { // NOLINT
  math::linal::matrix<F, N, N> a;
  math::linal::vector<F, N> b;
};

template <typename F, size_t N>
std::ostream&
operator<<(std::ostream& out, const lineqsys<F, N>& sys) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      out << sys.a[i][j] << '\t';
    } 
    out << "|\t" << sys.b[i] << '\n';
  }
  return out;
}

}