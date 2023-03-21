#pragma once

#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/iter/valid_lineqsys.hpp"
#include "math/linal/basic_op.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <iterator>
#include <random>
#include <stdexcept>
#include <vector>

namespace math::eq::lin::sys::solve::gauss {

struct index_pair { // NOLINT
  size_t i;
  size_t j;
};

template <typename F, size_t N>
static index_pair
peek(const linal::matrix<F, N, N>& matrix, index_pair start) {
  auto max = start;
  size_t j = start.j;                    // NOLINT
  for (size_t i = start.i; i < N; i++) { // NOLINT
    if (matrix[max.i][max.j] < matrix[i][j]) {
      max.i = i;
      max.j = j;
    }
  }
  return max;
}

template <size_t N>
struct triangulization_result { // NOLINT
  std::array<index_pair, N> swaps;
  size_t col_swaps_count = 0;
  size_t row_swaps_count = 0;
};

template <typename F, size_t N>
triangulization_result<N> triangulate(lineqsys<F, N>& sys) {
  triangulization_result<N> result = {};

  for (size_t row = 0; row < N; row++) {
    // Put max element in working position
    // const index_pair pos = {row, row};
    const auto pos = peek<F, N>(sys.a, {row, row});

    if (sys.a[pos.i][pos.j] == 0) {
      throw std::invalid_argument("matrix can't be solved by gauss");
    }

    if (pos.i != row) {
      sys.a.swap_rows(pos.i, row);
      std::swap(sys.b[pos.i], sys.b[row]);
      result.row_swaps_count++;
    }

    if (pos.j != row) {
      sys.a.swap_cols(pos.j, row);
      result.swaps[result.col_swaps_count++] = {.i = pos.j, .j = row};
    }

    // Go ahead and make zeros below
    for (size_t i = row + 1; i < N; i++) { // NOLINT
      F multiplier = sys.a[i][row] / sys.a[row][row];
      sys.a[i] -= multiplier * sys.a[row];
      sys.b[i] -= multiplier * sys.b[row];
    }
  }

  return result;
}

template <typename F, size_t N>
static linal::vector<F, N> solve_triangle(const lineqsys<F, N>& sys) {
  linal::vector<F, N> result; // NOLINT: fill in the loop
  for (size_t row = N - 1;; row--) {
    auto x = sys.b[row];                         // NOLINT
    for (size_t col = row + 1; col < N; col++) { // NOLINT
      x -= sys.a[row][col] * result[col];
    }
    result[row] = x / sys.a[row][row];
    if (row == 0) {
      break;
    }
  }
  return result;
}

template <typename F, size_t N>
struct result : solution<F, N> { // NOLINT
public:
  result(
      math::linal::vector<F, N> value, // NOLINT
      math::linal::vector<F, N> error, // NOLINT
      const lineqsys<F, N>& triangle,
      F det
  )
      : solution<F, N>(value, error), triangle(triangle), det(det) {}

  lineqsys<F, N> triangle; // NOLINT
  F det;                   // NOLINT
};

template <typename F, size_t N>
result<F, N> solve(const lineqsys<F, N>& sys) {
  auto triangle = sys;
  auto tresult = triangulate(triangle);
  auto value = solve_triangle(triangle);

  if (tresult.col_swaps_count > 0) {
    for (size_t i = tresult.col_swaps_count - 1;; i--) { // NOLINT
      auto swap = tresult.swaps[i];
      std::swap(value[swap.i], value[swap.j]);
      if (i == 0) {
        break;
      }
    }
  }

  F det = 1;
  for (size_t i = 0; i < N; i++) {
    det *= triangle.a[i][i];
  }
  if ((tresult.row_swaps_count + tresult.col_swaps_count) % 2 == 1) {
    det *= -1;
  }

  return result<F, N>(
      value,                 //
      sys.b - sys.a * value, //
      triangle,              //
      det                    //
  );
}

}