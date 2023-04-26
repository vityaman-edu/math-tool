#pragma once

#include "Mathematica/Algebra/FieldTrait.hpp"
#include "Mathematica/Algebra/Linear/Eq/System.hpp"
#include "Mathematica/Algebra/Linear/Operation.hpp"
#include "Mathematica/Core.hpp"
#include <stdexcept>

namespace Mathematica::Algebra::Linear::Eq {

template <typename F, Size N, Field::BasicOp<F> Op = Field::BasicOp<F>()>
class GaussSolver {
public:
  Solution<F, N, Op> solve(const System<F, N, Op>& sys) {
    auto triangle = sys;
    auto tresult = triangulate(triangle);
    auto value = solveTriangle(triangle);

    if (tresult.colSwapsCount > 0) {
      for (auto i = tresult.colSwapsCount - 1;; i--) {
        auto swap = tresult.swaps[i];
        std::swap(value[swap.i], value[swap.j]);
        if (i == 0) {
          break;
        }
      }
    }

    F det = 1;
    for (auto i = 0; i < N; i++) {
      det *= triangle.a[i][i];
    }
    if ((tresult.rowSwapsCount + tresult.colSwapsCount) % 2 == 1) {
      det *= -1;
    }

    return {
        .value = value,
        .error = sys.b - sys.a * value,
    };
  }

private:
  struct MatIndex {
    Index i, j;
  };

  static MatIndex peek(const Matrix<F, N, N, Op>& matrix, MatIndex start) {
    auto max = start;
    auto j = start.j;
    for (auto i = start.i; i < N; i++) {
      if (matrix[max.i][max.j] < matrix[i][j]) {
        max.i = i;
        max.j = j;
      }
    }
    return max;
  }

  struct TriangulizationResult {
    Array<MatIndex, N> swaps;
    Count colSwapsCount = 0;
    Count rowSwapsCount = 0;
  };

  TriangulizationResult triangulate(System<F, N, Op>& sys) {
    TriangulizationResult result = {};

    for (Index row = 0; row < N; row++) {
      // Put max element in working position
      // const index_pair pos = {row, row};
      const auto pos = peek(sys.a, {row, row,});

      if (sys.a[pos.i][pos.j] == 0) {
        throw std::invalid_argument("matrix can't be solved by gauss");
      }

      if (pos.i != row) {
        sys.a.swapRows(pos.i, row);
        std::swap(sys.b[pos.i], sys.b[row]);
        result.rowSwapsCount++;
      }

      if (pos.j != row) {
        sys.a.swapCols(pos.j, row);
        result.swaps[result.colSwapsCount++] = {
            .i = pos.j,
            .j = row,
        };
      }

      // Go ahead and make zeros below
      for (auto i = row + 1; i < N; i++) {
        const auto multiplier = sys.a[i][row] / sys.a[row][row];
        sys.a[i] -= multiplier * sys.a[row];
        sys.b[i] -= multiplier * sys.b[row];
      }
    }

    return result;
  }

  static Vector<F, N, Op> solveTriangle(const System<F, N, Op>& sys) {
    Vector<F, N, Op> result;
    for (auto row = N - 1;; row--) {
      auto x = sys.b[row];
      for (auto col = row + 1; col < N; col++) {
        x -= sys.a[row][col] * result[col];
      }
      result[row] = x / sys.a[row][row];
      if (row == 0) {
        break;
      }
    }
    return result;
  }
};
}