#pragma once

#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"
#include <functional>

namespace Mathematica::Integration {

template <typename T>
using TrivialMethod = std::function<T(Function<T>, Interval<T>)>;

template <typename T>
using Method = std::function<T(Function<T>, Partition<T>)>;

}