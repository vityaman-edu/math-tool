#pragma once

#include "Mathematica/Abstract/Field.hpp"
#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Statistics/Basic.hpp"
#include <cmath>
#include <concepts>

namespace Mathematica::Statistics {

using Mathematica::Collection::Array;

// Pearson correlation coefficient.
template <Abstract::Real R, Size N>
R pcc(const Array<Point<R>, N>& points) {
  // TODO: take Iterable
  // TODO: optimize
  const auto x = Array<R, N>([&points](auto i) { return points[i].x; });
  const auto y = Array<R, N>([&points](auto i) { return points[i].y; });

  const auto meanX = mean(x);
  const auto meanY = mean(y);

  const auto varX = variance(x, meanX);
  const auto varY = variance(y, meanY);

  const auto numerator = [meanX, meanY, &y, &x]() {
    auto productsSum = R::zero();
    for (auto i = 0; i < N; i++) {
      productsSum += (x[i] - meanX) * (y[i] - meanY);
    }
    return productsSum / N;
  };

  return numerator() / Abstract::sqrt(varX * varY);
}

}