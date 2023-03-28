#pragma once
#include "math/eq/solve/interval.hpp"
#include "math/func/function.hpp"
#include <cassert>
#include <cstddef>
#include <vector>

namespace math::eq::solve {

constexpr auto EPSILON = 0.00000000001;

template <typename T>
math::function<T, T>
naive_derivative(math::function<T, T> function, T epsilon) noexcept {
  assert(epsilon != 0);
  assert(epsilon < 1);
  return [=](T argument) {
    return (function(argument + epsilon) - function(argument))
           / epsilon;
  };
}

template <typename T>
class function : math::function<T, T> {
public:
  explicit function(
      math::function<T, T> original,  // NOLINT
      math::function<T, T> derivative // NOLINT
  )
      : original(original), derivative(derivative) {}

  explicit function(math::function<T, T> original)
      : function(original, naive_derivative<T>(original, EPSILON)) {}

  function(const function& other)
      : function(other.original, other.derivative) {}

  bool exactly_has_root_inside(interval<T> interval) const noexcept {
    return original(interval.start()) * original(interval.end()) < 0;
  }

  std::vector<interval<T>>
  tabulate(interval<T> scope, T count) const noexcept {
    assert(count > 0);
    auto length = scope.length() / count;
    auto result = std::vector<interval<T>>();
    for (std::size_t i = 0; i < count; i++) {
      auto left = scope.left_from(scope.start() + length);
      if (exactly_has_root_inside(left)) {
        result.emplace_back(left);
      }
      scope = scope.right_from(scope.start() + length);
    }
    return result;
  }

  T operator()(T argument) const noexcept {
    return original(argument);
  }

  T derivative_at(T argument) const noexcept {
    return derivative(argument);
  }

private:
  math::function<T, T> original;
  math::function<T, T> derivative;
};

}