#pragma once

#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"
#include <functional>
#include <numeric>

namespace Mathematica::Integration::Rectangle {

template <typename T>
using PointPeeker = std::function<T(Interval<T>)>;

template <typename T>
class Method {
public:
  explicit Method(PointPeeker<T> peek) : peek(peek) {}

  T areaUnderGraph(Function<T> function, Partition<T> partition) {
    T sum = 0;
    for (auto interval : partition) {
        sum += function(peek(interval)) * interval.length();
    }
    return sum;
  }

private:
  PointPeeker<T> peek;
};

}