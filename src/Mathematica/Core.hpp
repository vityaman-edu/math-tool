#pragma once

#include <cstddef>
#include <functional>

namespace Mathematica {

using Integer = int64_t;
using Real = double;

template <typename T>
using Function = std::function<T(T)>;

}