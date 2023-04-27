#pragma once

#include "Mathematica/Algebra/FieldTrait.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/LeastSqare.hpp"
#include "Mathematica/Common/Point.hpp"

namespace Mathematica::Functional::Approx::Linear {

template <typename F>
class TrendLine {
public:
  explicit TrendLine(F slope, F bias) : _slope(slope), _bias(bias) {} // NOLINT

  F operator()(F x) const noexcept { return _slope * x + _bias; }

  F slope() const noexcept { return _slope; }
  F bias() const noexcept { return _bias; }

private:
  // y = kx + b
  F _slope;
  F _bias;
};

template <
    typename F,
    Count N,
    Algebra::Field::BasicOp<F> Op = Algebra::Field::BasicOp<F>()>
TrendLine<F> trendLine(const Array<Point<F>, N>& points) {
  const auto poly = LeastSqare::optimalPolynomial<F, 2, Op>(points);
  return TrendLine(poly[1], poly[0]);
}

}
