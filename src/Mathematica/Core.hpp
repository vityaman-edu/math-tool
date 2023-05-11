#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <set>
#include <vector>

namespace Mathematica {

using NotNegativeInteger = std::size_t;
using Size = NotNegativeInteger;
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

template <typename T>
using ArrayList = std::vector<T>;

template <typename T>
using OrderedSet = std::set<T>;

}