#pragma once

#include "Mathematica/Core.hpp"
#include <concepts>

namespace Mathematica::Abstract {

template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

template <typename T>
concept TotallyOredered = std::totally_ordered<T>;

// clang-format off
template <typename T>
concept ToString = requires(T object) {
 { object.asString() } -> std::same_as<String>;
};
// clang-format on

}