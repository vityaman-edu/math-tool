#pragma once

#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
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
  for (auto currentScope : Partition<T>::fromFineness(scope, fineness)) {
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
  auto result = std::vector<Interval<T>>();
  for (auto currentScope : Partition<T>::fromFineness(scope, fineness)) {
    if (isDefinitelyRootInside(currentScope, f)) {
      result.emplace_back(currentScope);
    }
  }
  return result;
}

template <typename T>
T max(Interval<T> scope, T fineness, Function<T> f) {
  auto max = f(scope.left());
  for (auto currentScope : Partition<T>::fromFineness(scope, fineness)) {
    max = std::max(max, f(currentScope.right()));
  }
  return max;
}

}