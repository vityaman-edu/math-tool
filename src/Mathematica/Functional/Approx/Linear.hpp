#pragma once

#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/LeastSqare.hpp"
#include <string>

namespace Mathematica::Functional::Approx::Linear {

using Mathematica::Collection::Array;

template <Abstract::Field F>
class TrendLine {
public:
  explicit TrendLine(F slope, F bias) : _slope(slope), _bias(bias) {} // NOLINT
  TrendLine(const TrendLine& other) : TrendLine(other._slope, other._bias) {}

  F operator()(F x) const noexcept { return _slope * x + _bias; }

  [[nodiscard]] String asString() const noexcept {
    const auto a = slope().asString();
    const auto b = bias().asString();
    return a + " * x + " + b;
  }

  F slope() const noexcept { return _slope; }
  F bias() const noexcept { return _bias; }

private:
  // y = kx + b
  F _slope;
  F _bias;
};

template <Abstract::Field F, Count N>
TrendLine<F> trendLine(const Array<Point<F>, N>& points) noexcept {
  const auto poly = LeastSqare::optimalPolynomial<F, 2>(points);
  return TrendLine(poly[1], poly[0]);
}

}
