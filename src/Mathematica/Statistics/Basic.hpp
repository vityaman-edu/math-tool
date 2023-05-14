#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Core.hpp"
#include <cmath>
#include <concepts>
#include <numeric>

namespace Mathematica::Statistics {

using Mathematica::Collection::Array;

template <Abstract::Real F, Size N>
F mean(const Array<F, N>& numbers) noexcept {
  return std::accumulate(numbers.begin(), numbers.end(), F::zero()) / N;
}

template <Abstract::Real F, Size N>
F variance(const Array<F, N>& numbers, F mean) noexcept {
  // TODO: generialize sum of sqares
  auto sumOfSquares = F::zero();
  for (const auto number : numbers) {
    sumOfSquares += Abstract::abs(number - mean).pow(2);
  }
  return sumOfSquares / N;
}

template <Abstract::Real F, Size N>
F variance(const Array<F, N>& numbers) noexcept {
  return variance(numbers, mean(numbers));
}

}
