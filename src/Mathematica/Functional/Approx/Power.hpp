#pragma once

#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/Linear.hpp"

namespace Mathematica::Functional::Approx::Power {

using Mathematica::Collection::Array;

template <Abstract::Real F>
struct Trend {
  F multiplier; // NOLINT
  F power;      // NOLINT

  F operator()(F x) const noexcept { return multiplier * x.pow(power); }

  [[nodiscard]] String asString() const noexcept {
    const auto a = multiplier.asString();
    const auto b = power.asString();
    return a + " * x ^ " + b;
  }
};

template <Abstract::Real F, Count N>
Trend<F> train(const Array<Point<F>, N>& points) noexcept {
  const auto line = Linear::trendLine(points.map([](auto point) {
    return Point(Abstract::ln(point.x), Abstract::ln(point.y));
  }));
  return {
      .multiplier = F::exp().pow(line.bias()),
      .power = line.slope(),
  };
}

}