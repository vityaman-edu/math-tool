#pragma once

#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/iter/valid_lineqsys.hpp"
#include "math/linal/basic_op.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>
#include <functional>
#include <iterator>
#include <stdexcept>

namespace math::eq::lin::sys::solve::gauss {

template <typename F, size_t N>
linal::vector<size_t, 2> peek(
    const linal::matrix<F, N, N>& matrix,
    linal::vector<size_t, 2> start
) {
  auto max = start;
  for (size_t row = start[0]; row < N; row++) {   // NOLINT
    for (size_t col = start[1]; col < N; col++) { // NOLINT
      if (matrix[max[0]][max[1]] < matrix[row][col]) {
        max[0] = row;
        max[0] = col;
      }
    }
  }
  return max;
}

template <typename F, size_t N>
struct result { // NOLINT
  linal::vector<F, N> value;
  lineqsys<F, N> triangle;
};

template <typename F, size_t N>
result<F, N> solve(const lineqsys<F, N>& sys) {
  auto triangle = sys;

  for (size_t row = 0; row < N; row++) {

    // Put max element in working position
    const auto position = peek<F, N>(
        triangle.a, linal::vector<size_t, 2>({row, row})
    );

    if (triangle.a[position[0]][position[1]] == 0) {
      throw std::invalid_argument("matrix can't be solved by gauss");
    }

    triangle.a.swap_rows(position[0], row);
    std::swap(triangle.b[position[0]], triangle.b[row]);

    triangle.a.swap_cols(position[1], row);

    // Go ahead and make zeros below
    for (size_t i = row + 1; i < N; i++) { // NOLINT
      F multiplier = triangle.a[i][row] / triangle.a[row][row];
      triangle.a[i] -= multiplier * triangle.a[row];
      triangle.b[i] -= multiplier * triangle.b[row];
    }
  }

  linal::vector<F, N> result; // NOLINT: fill in the loop
  for (size_t row = N - 1; row != static_cast<size_t>(-1); row--) {
    auto x = triangle.b[row]; // NOLINT
    for (size_t col = row + 1; col < N; col++) { // NOLINT
      x -= triangle.a[row][col];
    }
    result[row] = x / triangle.a[row][row];
  }

  return {
      .value = result,
      .triangle = triangle,
  };
}
}