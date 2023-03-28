#pragma once
#include "method.hpp"
#include <cassert>
#include <utility>

namespace math::eq::solve {
template <typename T>
using half_division_callback
    = void(T a, T b, T x, T fa, T fb, T fx, T ab); // NOLINT

template <typename T, half_division_callback<T> OnIteration>
class half_division : public method<T> {
public:
  explicit half_division(T epsilon) : epsilon(epsilon) {}

  T find_some_root(interval<T> interval, function<T> function)
      override {
    assert(function.exactly_has_root_inside(interval));
    while (true) {
      auto left = interval.left_from(interval.middle());
      auto right = interval.right_from(interval.middle());
      if (function.exactly_has_root_inside(left)) {
        interval = left;
      } else {
        interval = right;
      }
      OnIteration(
          interval.start(),
          interval.end(),
          interval.middle(),
          function(interval.start()),
          function(interval.end()),
          function(interval.middle()),
          interval.length()
      );
      if (interval.length() < epsilon) {
        return interval.middle();
      }
    };
  }

private:
  T epsilon;
};

}