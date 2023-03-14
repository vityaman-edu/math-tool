#pragma once

#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <exception>
#include <iostream>
#include <numeric>
#include <set>
#include <stdexcept>

namespace math::eq::lin::sys::solve::iter {

template <typename F, size_t N>
struct valid_lineqsys : lineqsys<F, N> { // NOLINT
public:
  static valid_lineqsys from(const lineqsys<F, N>& original) {
    std::array<std::set<size_t>, N> row_candidates;
    for (size_t i = 0; i < N; i++) {
      row_candidates[i] = std::set<size_t>();
    }

    for (size_t i = 0; i < N; i++) {
      const auto row = original.a[i];
      F row_abs_sum = std::accumulate(
          row.begin(),
          row.end(),
          0,
          [](F left, F right) {
            return std::abs(left) + std::abs(right);
          }
      );
      for (size_t j = 0; j < N; j++) {
        if (row_abs_sum < 2 * std::abs(row[j])) {
          row_candidates[j].insert(i);
        }
      }
    }

    std::array<size_t, N> indexes; // NOLINT
    for (size_t i = 0; i < N; i++) {
      indexes[i] = i;
    }

    auto less_by_candidates_count
        = [row_candidates](size_t row, size_t col) {
            return row_candidates[row].size()
                   < row_candidates[col].size();
          };
    std::sort(
        indexes.begin(), indexes.end(), less_by_candidates_count
    );

    std::array<size_t, N> suitable; // NOLINT
    std::set<size_t> used_rows;
    for (size_t i = 0; i < N; i++) {
      const auto& candidates = row_candidates[indexes[i]];

      std::set<size_t> diff;
      std::set_difference(
          candidates.begin(),
          candidates.end(),
          used_rows.begin(),
          used_rows.end(),
          std::inserter(diff, diff.end())
      );

      if (diff.empty()) {
        throw std::invalid_argument(
            "matrix can't be made diagonal predominant"
        );
      }
      size_t candidate = *diff.begin();
      used_rows.insert(candidate);
      suitable[indexes[i]] = candidate;
    }

    valid_lineqsys<F, N> result;
    for (size_t i = 0; i < N; i++) {
      result.a[i] = original.a[suitable[i]];
      result.b[i] = original.b[suitable[i]];
    }
    return result;
  }

private:
  valid_lineqsys() = default;
};

}