#pragma once

#include <string>
namespace App::Misc {

template <typename T>
class Point {
public:
  Point(T x, T y) : _x(x), _y(y) {} // NOLINT
  Point(const Point& other) : Point(other._x, other._y) {}

  T x() const noexcept { return _x; }
  T y() const noexcept { return _y; }

  Point& operator*=(Point other) noexcept {
    this->_x *= other._x;
    this->_y *= other._y;
    return *this;
  }

  Point& operator+=(Point other) noexcept {
    this->_x += other._x;
    this->_y += other._y;
    return *this;
  }

  Point operator+(Point other) const noexcept {
    auto copy = *this;
    return copy += other;
  }

  [[nodiscard]] std::string asString() const noexcept {
    return "(" + std::to_string(x()) + ", " + std::to_string(y()) + ")";
  }

private:
  T _x;
  T _y;
};

}