#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Statistics/Basic.hpp"
#include "Mathematica/Statistics/RSS.hpp"

namespace Mathematica::Statistics::Metrics {

using Mathematica::Collection::Array;

template <Abstract::Real R, Size N, Function1<R, R> Func>
R R2Score(
    const Func& predict, //
    const Array<Point<R>, N>& points
) noexcept {
  const auto ssres = rss(predict, points);

  const auto y = Array<R, N>([&points](auto i) { 
    return points[i].y; 
    });
  const auto sstot = variance(y) * N;

  return R::unit() - ssres / sstot;
}

}