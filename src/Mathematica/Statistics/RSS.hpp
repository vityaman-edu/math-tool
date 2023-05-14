#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include <cmath>
#include <numeric>

namespace Mathematica::Statistics {

using Mathematica::Collection::Array;

// Residual sum of squares.
template <Abstract::Real R, Size N, Function1<R, R> Func>
R rss(const Func& f, const Array<Point<R>, N>& points) noexcept {
  auto sumOfSquares = R::zero();
  for (const auto point : points) {
    sumOfSquares += abs(f(point.x) - point.y).pow(2);
  }
  return sumOfSquares;
}

template <Abstract::Real R, Size N, Function1<R, R> Func>
R standartDeviation(const Func& f, const Array<Point<R>, N>& points) noexcept {
  return Abstract::sqrt(rss(f, points) / N);
}

}