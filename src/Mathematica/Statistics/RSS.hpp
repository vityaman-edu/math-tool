#pragma once

#include "Mathematica/Algebra/FieldTrait.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include <cmath>
#include <numeric>

namespace Mathematica::Statistics {

template <
    typename F,
    Algebra::Field::BasicOp<F> Op = Algebra::Field::BasicOp<F>()>
F rss(const Function<F>& f, const ArrayList<Point<F>>& points) noexcept {
  auto sumOfSquares = Op.zero();
  for (const auto point : points) {
    sumOfSquares += std::pow(std::abs(f(point.x) - point.y), 2);
  }
  return sumOfSquares;
}

}