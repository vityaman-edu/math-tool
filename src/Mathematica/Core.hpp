#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <functional>
#include <set>
#include <string>
#include <vector>

namespace Mathematica {

using NotNegativeInteger = std::size_t;
using Size = NotNegativeInteger;
using Count = Size;
using Index = Size;
using Integer = int64_t;
using Real = double;

using String = std::string;

template <typename Signature>
using Mapping = std::function<Signature>;

// clang-format off
template <typename T, typename U, typename V>
concept Function1 = requires(T f, U u) {
  { f(u) } -> std::same_as<V>;
};
// clang-format on

template <typename T>
using Function = Mapping<T(T)>;

template <typename T, Size N>
using Array = std::array<T, N>;

template <typename T>
using OrderedSet = std::set<T>;

}