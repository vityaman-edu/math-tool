#pragma once

#include "math/eq/solve/interval.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <ostream>
namespace math::eq::solve {

template <typename T>
T max(interval<T> scope, std::function<T(T)> function, std::size_t count) {
  assert(count > 0);
  auto right = scope.right();
  auto length = scope.length() / count;
  auto max = function(scope.left());
  while (scope.left() + length < right) {
    auto left = scope.left_from(scope.left() + length);
    max = std::max(max, function(left.middle()));
    scope = scope.right_from(scope.left() + length);
  }
  max = std::max(max, function(right));
  return max;
}

}