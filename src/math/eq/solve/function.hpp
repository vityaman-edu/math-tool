#pragma once
#include "math/eq/solve/interval.hpp"
#include "math/func/function.hpp"
#include <cassert>

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
      : function(original, naive_derivative(original, EPSILON)) {}

  bool exactly_has_root_inside(interval<T> interval) const noexcept {
    return original(interval.start()) * original(interval.end()) < 0;
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