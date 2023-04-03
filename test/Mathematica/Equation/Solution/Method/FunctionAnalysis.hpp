#pragma once

#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/Interval.hpp"
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
std::vector<Interval<T>> rootSeparabilityIntervals(
    Interval<T> scope, T fineness, Function<T> f
) noexcept {
  assert(fineness > 0);
  assert(fineness <= scope.length());

  auto result = std::vector<Interval<T>>();
  for ( //
    auto currentScope = scope.leftFrom(scope.left() + fineness);
    currentScope.right() < scope.right();
    currentScope += currentScope
  ) {
    if (isDefinitelyRootInside(currentScope, f)) {
      result.emplace_back(currentScope);
    }
  }
  return result;
}

}