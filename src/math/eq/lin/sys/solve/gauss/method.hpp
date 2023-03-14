#pragma once

#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/iter/valid_lineqsys.hpp"
#include "math/linal/basic_op.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <array>
#include <cstddef>
#include <functional>
#include <iterator>
#include <random>
#include <stdexcept>

namespace math::eq::lin::sys::solve::gauss {

template <typename F, size_t N>
static linal::vector<size_t, 2> peek(
    const linal::matrix<F, N, N>& matrix,
    linal::vector<size_t, 2> start
) {
  auto max = start;
  for (size_t row = start[0]; row < N; row++) {   // NOLINT
    for (size_t col = start[1]; col < N; col++) { // NOLINT
      if (matrix[max[0]][max[1]] < matrix[row][col]) {
        max[0] = row;
        max[1] = col;
      }
    }
  }
  return max;
}

template <typename F, size_t N>
struct triangulization_result { // NOLINT
};

template <typename F, size_t N>
triangulization_result<F, N> triangulate(lineqsys<F, N>& system) {
  for (size_t row = 0; row < N; row++) {

    // Put max element in working position
    const auto position = linal::vector<size_t, 2>({row, row});
    // const auto position
    //     = peek<F, N>(system.a, linal::vector<size_t, 2>({row,
    //     row}));

    if (system.a[position[0]][position[1]] == 0) {
      throw std::invalid_argument("matrix can't be solved by gauss");
    }

    system.a.swap_rows(position[0], row);
    std::swap(system.b[position[0]], system.b[row]);

    system.a.swap_cols(position[1], row);

    // Go ahead and make zeros below
    for (size_t i = row + 1; i < N; i++) { // NOLINT
      F multiplier = system.a[i][row] / system.a[row][row];
      system.a[i] -= multiplier * system.a[row];
      system.b[i] -= multiplier * system.b[row];
    }
  }

  return {};
}

template <typename F, size_t N>
static linal::vector<F, N> solve_triangle(const lineqsys<F, N>& system
) {
  linal::vector<F, N> result; // NOLINT: fill in the loop
  for (size_t row = N - 1;; row--) {
    auto x = system.b[row];                      // NOLINT
    for (size_t col = row + 1; col < N; col++) { // NOLINT
      x -= system.a[row][col] * result[col];
    }
    result[row] = x / system.a[row][row];
    if (row == 0) {
      break;
    }
  }
  return result;
}

template <typename F, size_t N>
struct result { // NOLINT
  linal::vector<F, N> value;
  lineqsys<F, N> triangle;
};

template <typename F, size_t N>
result<F, N> solve(const lineqsys<F, N>& sys) {
  auto triangle = sys;
  triangulate(triangle);
  auto shuffled_result = solve_triangle(triangle);
  // auto eps = sys.b - sys.a * shuffled_result;
  return {
      .value = shuffled_result,
      .triangle = triangle,
  };
}
}