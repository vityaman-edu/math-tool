#pragma once

#include <string>
#include <type_traits>
#include <vector>
#include <cassert>

namespace Mathematica::Equation::Solution::Method {

template <typename T>
class Interval {
  static_assert(std::is_arithmetic<T>::value);

public:
  explicit Interval(T left, T right) : _left(left), _right(right) {} // NOLINT
  Interval(const Interval& other) : Interval(other.left(), other.right()) {}

  T length() const noexcept { return right() - left(); }

  T left() const noexcept { return _left; }

  T right() const noexcept { return _right; }

  T middle() const noexcept { return (left() + right()) / 2; }

  bool contains(T point) const noexcept {
    return left() <= point && point <= right();
  }

  Interval<T> leftFrom(T point) const noexcept {
    assert(contains(point));
    return Interval<T>(left(), point);
  }

  Interval<T> rightFrom(T point) const noexcept {
    assert(contains(point));
    return Interval<T>(point, right());
  }

  [[nodiscard]] std::string asString() const noexcept {
    return "[" + std::to_string(_left) + ", " + std::to_string(_right) + "]";
  }

  Interval<T>& operator+=(T shift) noexcept {
    this->_left += shift;
    this->_right += shift;
    return *this;
  }

  Interval<T> operator+(T shift) const noexcept {
    auto copy = *this;
    return copy += shift;
  }

private:
  T _left;
  T _right;
};

}