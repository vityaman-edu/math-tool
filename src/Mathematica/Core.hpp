#pragma once

#include <array>
#include <cstddef>
#include <functional>

namespace Mathematica {

using Size = std::size_t;
using Count = Size;
using Index = Size;
using Integer = int64_t;
using Real = double;

template <typename Signature>
using Mapping = std::function<Signature>;

template <typename T>
using Function = Mapping<T(T)>;

template <typename T, Size N>
using Array = std::array<T, N>;

}