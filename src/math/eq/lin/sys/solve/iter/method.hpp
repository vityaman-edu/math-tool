#pragma once

#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/iter/valid_lineqsys.hpp"
#include "math/linal/basic_op.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include "math/linal/io.hpp"
#include <algorithm>
#include <cstddef>

namespace math::eq::lin::sys::solve::iter {

using math::linal::io::operator<<;

template <typename F, std::size_t N>
static math::linal::matrix<F, N, N>
build_alpha(const valid_lineqsys<F, N>& sys) {
  return linal::matrix<F, N, N>([=](size_t row, size_t col) {
    return (
        (row != col)                              //
            ? (-sys.a[row][col] / sys.a[row][row]) //
            : (0)                                 //
    );
  });
}

template <typename F, std::size_t N>
static linal::vector<F, N>
build_beta(const valid_lineqsys<F, N>& sys) {
  return linal::vector<F, N>([=](size_t index) {
    return sys.b[index] / sys.a[index][index];
  });
}

template <typename F, std::size_t N>
struct result { // NOLINT
  linal::vector<F, N> value;
  linal::vector<F, N> error;
  size_t steps_count;
};

template <typename F, std::size_t N>
result<F, N> solve(const valid_lineqsys<F, N>& sys, F eps) {
  const auto alpha = build_alpha(sys);
  const auto beta = build_beta(sys);

  size_t steps_count = 0;
  linal::vector<F, N> x = beta; // NOLINT: x is ok for math
  linal::vector<F, N> prev = beta;
  while (true) {
    prev = x;
    x = alpha * x;
    x = x + beta;

    steps_count += 1;
    auto error
        = math::linal::map<F, F, N>(prev - x, [=](F element) {
            return std::abs(element);
          });
    if (*std::max_element(error.begin(), error.end()) < eps) {
      return {
          .value = x,
          .error = error,
          .steps_count = steps_count,
      };
    }
  }
}

}
