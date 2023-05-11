#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Core.hpp"
#include <cmath>
#include <concepts>
#include <ostream>

namespace Mathematica::Abstract {

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

  T value; // NOLINT TODO: must be zero-cost abstraction
};

static_assert(Real<Float<float>>);
static_assert(Real<Float<double>>);

template <typename T>
std::ostream& operator<<(std::ostream& out, const Float<T>& number) {
  return out << number.value;
}

}