#pragma once

#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <ostream>

namespace math::eq::lin::sys {

template <typename F, size_t N>
struct lineqsys { // NOLINT
  math::linal::matrix<F, N, N> a;
  math::linal::vector<F, N> b;
};

template <typename F, size_t N>
struct solution { // NOLINT
public:
  solution(
      math::linal::vector<F, N> value, // NOLINT
      math::linal::vector<F, N> error  // NOLINT
  )
      : value(value), error(error) {}

  math::linal::vector<F, N> value; // NOLINT
  math::linal::vector<F, N> error; // NOLINT
};

template <typename F, size_t N>
using solver = std::function<solution<F, N>(const lineqsys<F, N>&)>;

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