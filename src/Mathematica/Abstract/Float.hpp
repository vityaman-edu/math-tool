#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Core.hpp"
#include <cmath>
#include <concepts>
#include <ostream>
#include <string>

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

  [[nodiscard]] String asString() const noexcept {
    return std::to_string(value);
  }

  bool operator<(Float other) const noexcept { return value < other.value; }
  bool operator<=(Float other) const noexcept { return value <= other.value; }
  bool operator>(Float other) const noexcept { return value > other.value; }
  bool operator>=(Float other) const noexcept { return value >= other.value; }

  [[nodiscard]] Float pow(NotNegativeInteger power) const noexcept {
    return pow(Float(power));
  }

  [[nodiscard]] Float pow(Float power) const noexcept {
    return std::pow(value, power.value);
  }

  [[nodiscard]] Float abs() const noexcept {
    return std::abs(value);
  }

  [[nodiscard]] Float sqrt() const noexcept {
    return std::sqrt(value);
  }

  [[nodiscard]] Float ln() const noexcept {
    return std::log(value);
  }

  constexpr static Float zero() { return Float(static_cast<T>(0)); }
  constexpr static Float unit() { return Float(static_cast<T>(1)); }
  constexpr static Float exp() { return Float(static_cast<T>(std::exp(1))); }

  T value; // NOLINT TODO: must be zero-cost abstraction
};

static_assert(Real<Float<float>>);
static_assert(Real<Float<double>>);

template <typename T>
std::ostream& operator<<(std::ostream& out, const Float<T>& number) {
  return out << number.value;
}

}