#pragma once

#include "App/Core.hpp"
#include "App/Misc/Point.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace App {

using Size = std::size_t;

template <typename T>
using Point = Misc::Point<T>;

class ConsoleCanvas {
public:
  ConsoleCanvas(Point<Size> size, Scope scope) // NOLINT
      : size(size), scope(scope),
        canvas(std::vector<String>(size.y(), String(size.x(), ' '))) {}

  void draw(Point<Real> point, char symbol) {
    if (!scope.contains(point.x())) {
      return;
    }
    point = {
        (point.x() - scope.left()) * size.x() / scope.length(),
        point.y() * 3,
    };
    auto discrete = Point<Integer>(point.x(), point.y());
    auto rotated = Point<Integer>(discrete.x(), -discrete.y());
    auto shifted = rotated + center();
    if (shifted.y() < 0 || size.y() <= shifted.y()) {
      return;
    }
    minY = std::min(minY, static_cast<Size>(shifted.y()));
    maxY = std::max(maxY, static_cast<Size>(shifted.y()));
    canvas[shifted.y()][shifted.x()] = symbol;
  }

  void plot(const Function<Real>& f, double step, char symbol) { // NOLINT
    for (auto x = scope.left(); x <= scope.right(); x += step) { // NOLINT
      auto y = f(x);
      draw({x, 0}, '-');
      draw({0, y}, '|');
      draw({x, y}, symbol);
    }
  }

  void print(std::ostream& out) {
    for (std::size_t i = minY; i <= maxY; i++) {
      out << canvas[i] << std::endl;
    }
  }

private:
  [[nodiscard]] Point<Integer> center() const noexcept {
    return {
        0,
        static_cast<Integer>(size.y()) / 2,
    };
  }

  Point<Size> size;
  Scope scope;
  Vector<String> canvas;

  Size minY = size.y();
  Size maxY = 0;
};

}