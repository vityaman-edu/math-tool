#pragma once

#include "Mathematica/Abstract/Basic.hpp"
#include "Mathematica/Core.hpp"
#include <concepts>

namespace Mathematica::Abstract {

// clang-format off

template <typename F>
concept Field = requires(NotNegativeInteger m, F a, F b) {
  { a + b         } -> std::same_as<F>;
  { a - b         } -> std::same_as<F>;
  { F::zero()     } -> std::same_as<F>;

  { a * b         } -> std::same_as<F>;
  { a / b         } -> std::same_as<F>;
  { F::unit()     } -> std::same_as<F>;

  { -a            } -> std::same_as<F>;
  { F::unit() / a } -> std::same_as<F>;
  { a.pow(m)      } -> std::same_as<F>;
} && EqualityComparable<F>;

// clang-format on

}