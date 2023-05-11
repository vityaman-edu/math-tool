#pragma once

#include "Mathematica/Algebra/FieldTrait.hpp"
#include "Mathematica/Algebra/Linear/Eq/System.hpp"
#include "Mathematica/Algebra/Linear/Operation.hpp"
#include "Mathematica/Core.hpp"
#include <numeric>
#include <stdexcept>

namespace Mathematica::Algebra::Linear::Eq {

template <typename F, Size N, Field::BasicOp<F> Op = Field::BasicOp<F>()>
class IterationSolver {
public:
  explicit IterationSolver(F epsilon) : epsilon(epsilon) {}

  Solution<F, N, Op> operator()(const System<F, N, Op>& system) {
    return solve(system);
  }

  Solution<F, N, Op> solve(const System<F, N, Op>& system) {
    const auto sys = valid(system);
    const auto alpha = buildAlpha(sys);
    const auto beta = buildBeta(sys);

    auto x = beta;
    auto prev = beta;
    while (true) {
      prev = x;
      x = alpha * x;
      x = x + beta;

      auto error = map<F, F, N>(prev - x, [=](auto element) {
        return std::abs(element);
      });
      if (*std::max_element(error.begin(), error.end()) < epsilon) {
        return {
            .value = x,
            .error = error,
        };
      }
    }
  }

private:
  static System<F, N, Op> valid(const System<F, N, Op>& system) {
    Array<OrderedSet<Index>, N> row_candidates;
    for (auto i = 0; i < N; i++) {
      row_candidates[i] = OrderedSet<Index>();
    }

    for (auto i = 0; i < N; i++) {
      const auto row = system.a[i];
      const auto row_abs_sum
          = std::accumulate(row.begin(), row.end(), 0, [](F left, F right) {
              return std::abs(left) + std::abs(right);
            });
      for (auto j = 0; j < N; j++) {
        if (row_abs_sum < 2 * std::abs(row[j])) {
          row_candidates[j].insert(i);
        }
      }
    }

    Array<Index, N> indexes; // NOLINT
    for (auto i = 0; i < N; i++) {
      indexes[i] = i;
    }

    auto less_by_candidates_count = [row_candidates](Index row, Index col) {
      return row_candidates[row].size() < row_candidates[col].size();
    };
    std::sort(indexes.begin(), indexes.end(), less_by_candidates_count);

    Array<Index, N> suitable; // NOLINT
    OrderedSet<Index> used_rows;
    for (auto i = 0; i < N; i++) {
      const auto& candidates = row_candidates[indexes[i]];

      OrderedSet<Index> diff;
      std::set_difference(
          candidates.begin(),
          candidates.end(),
          used_rows.begin(),
          used_rows.end(),
          std::inserter(diff, diff.end())
      );

      if (diff.empty()) {
        throw std::invalid_argument("matrix can't be made diagonal predominant"
        );
      }
      size_t candidate = *diff.begin();
      used_rows.insert(candidate);
      suitable[indexes[i]] = candidate;
    }

    System<F, N, Op> result;
    for (size_t i = 0; i < N; i++) {
      result.a[i] = system.a[suitable[i]];
      result.b[i] = system.b[suitable[i]];
    }
    return result;
  }

  static Matrix<F, N, N, Op> buildAlpha(const System<F, N, Op>& sys) noexcept {
    return Matrix<F, N, N, Op>([=](Index row, Index col) {
      return ((row != col) ? (-sys.a[row][col] / sys.a[row][row]) : (0));
    });
  }

  static Vector<F, N, Op> buildBeta(const System<F, N, Op>& sys) noexcept {
    return Vector<F, N, Op>([=](auto index) {
      return sys.b[index] / sys.a[index][index];
    });
  }

  F epsilon;
};

}