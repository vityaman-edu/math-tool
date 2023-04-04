#pragma once

#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/Interval.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <optional>
#include <vector>

namespace Mathematica::Equation::Solution::Method {

template <typename T>
bool isDefinitelyRootInside(Interval<T> scope, Function<T> f) noexcept {
  return f(scope.left()) * f(scope.right()) < 0;
}

template <typename T>
bool constSign(Interval<T> scope, T fineness, Function<T> df) noexcept {
  assert(fineness > 0);
  assert(fineness <= scope.length());

  for ( //
    auto currentScope = scope.leftFrom(scope.left() + fineness);
    currentScope.right() < scope.right();
    currentScope += fineness
  ) {
    if (df(currentScope.left()) * df(currentScope.right()) < 0) {
      return false;
    }
  }
  return true;
}

template <typename T>
std::vector<Interval<T>> rootSeparabilityIntervals(
    Interval<T> scope, T fineness, Function<T> f
) noexcept {
  assert(0 < fineness);
  assert(fineness <= scope.length());

  auto result = std::vector<Interval<T>>();
  for ( //
    auto currentScope = scope.leftFrom(scope.left() + fineness);
    currentScope.right() < scope.right();
    currentScope += fineness
  ) {
    if (isDefinitelyRootInside(currentScope, f)) {
      result.emplace_back(currentScope);
    }
  }
  return result;
}

// TODO: use iterators
template <typename T>
T max(Interval<T> scope, T fineness, Function<T> f) {
  assert(0 < fineness);
  assert(fineness <= scope.length());

  auto max = f(scope.left());
  for ( //
    auto currentScope = scope.leftFrom(scope.left() + fineness);
    currentScope.right() < scope.right();
    currentScope += fineness
  ) {
    max = std::max(max, f(scope.right()));
  }
  return max;
}

}