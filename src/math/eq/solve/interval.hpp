#pragma once
#include <type_traits>

namespace math::eq::solve {

template <typename T>
class interval {
  static_assert(std::is_arithmetic<T>::value);

public:
  interval(T start, T end) : _start(start), _end(end) {}

  T length() const noexcept { return end() - start(); }

  T start() const noexcept { return _start; }

  T end() const noexcept { return _end; }

  T middle() const noexcept { return (start() + end()) / 2; }

  interval<T> left_from(T point) const noexcept {
    return interval<T>(start(), point);
  }

  interval<T> right_from(T point) const noexcept {
    return interval<T>(point, end());
  }

private:
  T _start;
  T _end;
};

}