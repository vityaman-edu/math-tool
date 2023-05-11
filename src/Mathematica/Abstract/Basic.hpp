#pragma once

#include <concepts>

namespace Mathematica::Abstract {

template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

template <typename T>
concept TotallyOredered = std::totally_ordered<T>;

}