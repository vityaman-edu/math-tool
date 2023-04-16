#pragma once

#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Integration/Core.hpp"
#include <array>
#include <cstddef>

namespace Mathematica::Integration {

template <typename T>
using PointPeeker = std::function<T(Interval<T>)>;

template <typename T>
TrivialMethod<T> trivial0(PointPeeker<T> peek) noexcept {
  return [peek](auto f, auto interval) {
    return f(peek(interval)) * interval.length();
  };
}

template <typename T>
TrivialMethod<T> trivial1() noexcept {
  return [](auto f, auto interval) {
    auto left = f(interval.left());
    auto right = f(interval.right());
    return (left + right) / 2 * interval.length();
  };
}

template <typename T>
TrivialMethod<T> trivial2() noexcept {
  return [](auto f, auto interval) {
    auto a = interval.left();
    auto b = interval.right();
    return (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b)); // NOLINT
  };
}

template <typename T>
TrivialMethod<T> trivial5() noexcept {
  return [](auto f, auto interval) {
    const auto s = interval.left();
    const auto l = interval.length() / 6;
    return interval.length() / 288  // NOLINT
           * (                      // NOLINT
               +(19 * f(s + 0 * l)) // NOLINT
               + 75 * f(s + 1 * l)  // NOLINT
               + 50 * f(s + 2 * l)  // NOLINT
               + 50 * f(s + 3 * l)  // NOLINT
               + 75 * f(s + 4 * l)  // NOLINT
               + 19 * f(s + 5 * l)  // NOLINT
           );
  };
}

template <typename T>
class Cotes {
public:
  explicit Cotes(TrivialMethod<T> trivial) //
      : trivialAreaUnderGraph(trivial) {}

  T areaUnderGraph(Function<T> function, Partition<T> partition) noexcept {
    T sum = 0;
    for (auto interval : partition) {
      sum += trivialAreaUnderGraph(function, interval);
    }
    return sum;
  }

private:
  TrivialMethod<T> trivialAreaUnderGraph;
};

}