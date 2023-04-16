#pragma once

#include <cstddef>
#include <functional>

namespace Mathematica {

using Size = std::size_t;
using Count = Size;
using Index = Size;
using Integer = int64_t;
using Real = double;

template <typename T>
using Function = std::function<T(T)>;

}