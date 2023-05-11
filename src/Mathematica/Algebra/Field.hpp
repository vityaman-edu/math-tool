#pragma once

#include "Mathematica/Core.hpp"
#include <cmath>
#include <concepts>
#include <cstddef>

namespace Mathematica::Algebra {

template <typename T>
concept EqualityComparable = std::equality_comparable<T>;

template <typename T>
concept TotallyOredered = std::totally_ordered<T>;

template <typename F>
concept Field = //
    requires(std::size_t m, F a, F b) {
      { a + b } -> std::same_as<F>;
      { a - b } -> std::same_as<F>;
      { F::zero() } -> std::same_as<F>;

      { a* b } -> std::same_as<F>;
      { a / b } -> std::same_as<F>;
      { F::unit() } -> std::same_as<F>;

      { -a } -> std::same_as<F>;
      { F::unit() / a } -> std::same_as<F>;
      { a.pow(m) } -> std::same_as<F>;
    } && EqualityComparable<F>;

template <std::floating_point T, std::size_t ACCURACY = 1000000> // NOLINT
struct Float {
  constexpr Float() = default;
  constexpr Float(T value) : value(value) {} // NOLINT
  Float(const Float& other) : Float(other.value) {}

  Float operator-() const noexcept { return -value; }

  Float operator+(Float other) const noexcept { return value + other.value; }
  Float operator-(Float other) const noexcept { return value - other.value; }
  Float operator*(Float other) const noexcept { return value * other.value; }
  Float operator/(Float other) const noexcept { return value / other.value; }

  void operator+=(Float other) noexcept { value += other.value; }
  void operator-=(Float other) noexcept { value -= other.value; }
  void operator*=(Float other) noexcept { value *= other.value; }
  void operator/=(Float other) noexcept { value /= other.value; }

  bool operator==(Float other) const noexcept {
    return std::abs(value - other.value) * ACCURACY < 1;
  }

  bool operator!=(Float other) const noexcept { //
    return !(*this == other);
  }

  bool operator<(Float other) const noexcept { return value < other.value; }
  bool operator<=(Float other) const noexcept { return value <= other.value; }
  bool operator>(Float other) const noexcept { return value > other.value; }
  bool operator>=(Float other) const noexcept { return value >= other.value; }

  [[nodiscard]] Float pow(NotNegativeInteger power) const noexcept {
    return std::pow(value, power);
  }

  constexpr static Float zero() noexcept { return Float(static_cast<T>(0)); }
  constexpr static Float unit() noexcept { return Float(static_cast<T>(1)); }

  T value; // NOLINT
};

template <typename T>
concept Real = Field<T> && TotallyOredered<T>;

static_assert(Real<Float<float>>);
static_assert(Real<Float<double>>);

template <Real T>
T abs(T value) noexcept {
  if (value > T::zero()) {
    return value;
  }
  return -value;
}

}