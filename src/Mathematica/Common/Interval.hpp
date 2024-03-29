#pragma once

#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

namespace Mathematica {

// TODO: add partition for iterval as object
// to reduce count of parameters in function

template <typename T>
class Interval {
public:
  explicit Interval(T left, T right) : _left(left), _right(right) { // NOLINT
    assert(left <= right);
  }

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

  bool operator==(Interval<T> other) const noexcept {
    return _left == other._left && _right == other._right;
  }

private:
  T _left;
  T _right;
};

}