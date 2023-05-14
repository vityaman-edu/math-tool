#pragma once

namespace Mathematica {

template <typename T>
struct Point {
  T x, y;

  Point() = default;
  Point(T x, T y) : x(x), y(y) {} // NOLINT
  Point(const Point& other) : Point(other.x, other.y) {}
};

}