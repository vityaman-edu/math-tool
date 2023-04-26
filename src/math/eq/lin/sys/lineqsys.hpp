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
  math::linal::Matrix<F, N, N> a;
  math::linal::Vector<F, N> b;
};

template <typename F, size_t N>
struct solution { // NOLINT
public:
  solution(
      math::linal::Vector<F, N> value, // NOLINT
      math::linal::Vector<F, N> error  // NOLINT
  )
      : value(value), error(error) {}

  math::linal::Vector<F, N> value; // NOLINT
  math::linal::Vector<F, N> error; // NOLINT
};

template <typename F, size_t N>
using solver = std::function<solution<F, N>(const lineqsys<F, N>&)>;

struct Format { // NOLINT
  static Format col() { return {}; }
};

std::ostream& operator<<(std::ostream& out, Format format);

template <typename F, size_t N>
std::ostream&
operator<<(std::ostream& out, const lineqsys<F, N>& sys) {
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      out << Format::col() << sys.a[i][j] << ' ';
    }
    out << " | " << Format::col() << sys.b[i] << '\n';
  }
  return out;
}

}