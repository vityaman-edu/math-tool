#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/Linear.hpp"
#include <string>

namespace Mathematica::Functional::Approx::Exponential {

using Mathematica::Collection::Array;

template <Abstract::Real F>
struct Trend {
  F multiplier; // NOLINT
  F powerSlope; // NOLINT

  F operator()(F x) const noexcept {
    return multiplier * F::exp().pow(powerSlope * x);
  }

  [[nodiscard]] String asString() const noexcept {
    const auto a = multiplier.asString();
    const auto b = powerSlope.asString();
    return a + " * e ^ (" + b + " * x)";
  }
};


template <Abstract::Real F, Count N>
Trend<F> train(const Array<Point<F>, N>& points) noexcept {
  const auto line = Linear::trendLine(points.map([](auto point) {
    return Point(point.x, Abstract::ln(point.y));
  }));
  return {
      .multiplier = F::exp().pow(line.bias()),
      .powerSlope = line.slope(),
  };
}

}