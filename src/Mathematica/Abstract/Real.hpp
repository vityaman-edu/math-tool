#pragma once

#include "Mathematica/Abstract/Basic.hpp"
#include "Mathematica/Abstract/Field.hpp"

namespace Mathematica::Abstract {

// clang-format off

template <typename F>
concept Real = requires(F a, F b) {
  { a.pow(b) } -> std::same_as<F>;

  // TODO: remove it, make a better abstraction
  { a.abs() } ->  std::same_as<F>;
  { a.sqrt() } -> std::same_as<F>;
  { a.ln() } -> std::same_as<F>;

  { F::exp() } -> std::same_as<F>;
} && Field<F> && TotallyOredered<F>;

// clang-format on

template <Real T>
T abs(T value) noexcept {
  return value.abs();
}

template <Real T>
T sqrt(T value) noexcept {
  return value.pow(T::unit() / (T::unit() + T::unit()));
}

template <Real T>
T ln(T value) noexcept {
  return value.ln();
}

}