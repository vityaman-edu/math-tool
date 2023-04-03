#pragma once
#include <cassert>
#include <string>
#include <type_traits>

namespace math::eq::solve {

template <typename T>
class interval {
  static_assert(std::is_arithmetic<T>::value);

public:
  explicit interval(T start, T end) : _left(start), _right(end) {}
  interval(const interval& other) : interval(other.left(), other.right()) {}

  T length() const noexcept { return right() - left(); }

  T left() const noexcept { return _left; }

  T right() const noexcept { return _right; }

  T middle() const noexcept { return (left() + right()) / 2; }

  bool contains(T point) const noexcept {
    return left() <= point && point <= right();
  }

  interval<T> left_from(T point) const noexcept {
    assert(contains(point));
    return interval<T>(left(), point);
  }

  interval<T> right_from(T point) const noexcept {
    assert(contains(point));
    return interval<T>(point, right());
  }

  [[nodiscard]] std::string asString() const noexcept {
    return "[" + std::to_string(_left) + ", " + std::to_string(_right) + "]";
  }

private:
  T _left;
  T _right;
};

}