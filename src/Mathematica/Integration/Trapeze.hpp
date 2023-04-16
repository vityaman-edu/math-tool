#pragma once

#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Integration::Trapeze {

template <typename T>
T AreaUnderGraph(Function<T> function, Partition<T> partition) noexcept {
    T sum = 0;
    for (auto interval : partition) {
        auto left = function(interval.left());
        auto right = function(interval.right());
        sum += (left + right) / 2 * interval.length();
    }
    return sum;
}

}