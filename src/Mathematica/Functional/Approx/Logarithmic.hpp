#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Functional/Approx/Linear.hpp"

namespace Mathematica::Functional::Approx::Logarithmic {

using Mathematica::Collection::Array;

template <Abstract::Real F>
struct Trend {
  F slope; // NOLINT
  F bias;  // NOLINT

  F operator()(F x) const noexcept { return slope * Abstract::ln(x) + bias; }

  [[nodiscard]] String asString() const noexcept {
    const auto a = slope.asString();
    const auto b = bias.asString();
    return a + " * ln(x) + " + b;
  }
};

template <Abstract::Real F, Count N>
Trend<F> train(const Array<Point<F>, N>& points) noexcept {
  // TODO: X = Ln X, Y = Y
  const auto line = Linear::trendLine(points.map([](auto point) {
    return Point(Abstract::ln(point.x), point.y);
  }));
  return {
      .slope = line.slope(),
      .bias = line.bias(),
  };
}

}