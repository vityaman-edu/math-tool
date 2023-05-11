#pragma once

#include "Mathematica/Abstract/Field.hpp"

namespace Mathematica::Abstract {

template <typename T>
concept Real = Field<T> && TotallyOredered<T>;

template <Real T>
T abs(T value) noexcept {
  if (value > T::zero()) {
    return value;
  }
  return -value;
}

}