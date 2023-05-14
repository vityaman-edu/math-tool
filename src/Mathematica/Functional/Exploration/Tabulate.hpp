#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Functional::Exploration::Tabulate {

using Mathematica::Collection::Array;

template <Abstract::Real R, Size N, Function1<R, R> Func>
Array<Point<R>, N> trivial(const Func& f, const Interval<R>& scope) noexcept {
  auto points = Array<Point<R>, N>();
  auto i = 0;
  const auto partition = Partition(scope, N);
  for (const auto& interval : partition) {
    const auto x = interval.middle();
    points[i] = Point(x, f(x));
    i += 1;
  }
  return points;
}

}