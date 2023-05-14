#pragma once

#include "Mathematica/Abstract/Field.hpp"
#include "Mathematica/Core.hpp"
#include <cassert>

namespace Mathematica::Algebra::Linear {

template <Abstract::Field F, Size N>
class Vector {
public:
  explicit Vector() = default;

  explicit Vector(const Array<F, N>& array)
      : Vector([&](auto index) { return array[index]; }) {}

  explicit Vector(const Mapping<F(Index)>& item) {
    for (auto i = 0; i < N; i++) {
      data[i] = item(i);
    }
  }

  Vector(const Vector& other) : Vector(other.data) {}

  ~Vector() = default;

  F& operator[](Index index) noexcept {
    assert(index < data.size());
    return data[index];
  }

  F operator[](Index index) const noexcept {
    assert(index < data.size());
    return data[index];
  }

  Vector& operator+=(const Vector& other) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] = data[i] + other[i];
    }
    return *this;
  }

  Vector operator+(const Vector& other) const noexcept {
    auto copy = *this;
    return copy += other;
  }

  Vector& operator-=(const Vector& other) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] = data[i] - other[i];
    }
    return *this;
  }

  Vector operator-(const Vector& other) const noexcept {
    auto copy = *this;
    return copy -= other;
  }

  Vector& operator*=(F scalar) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] = data[i] * scalar;
    }
    return *this;
  }

  Vector operator*(F scalar) const noexcept {
    auto copy = *this;
    return copy *= scalar;
  }

  Vector& operator/=(F scalar) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] = data[i] / scalar;
    }
    return *this;
  }

  Vector operator/(F scalar) const noexcept {
    auto copy = *this;
    return copy /= scalar;
  }

  Vector operator-() const noexcept {
    auto copy = *this;
    return copy->negate();
  }

  bool operator==(const Vector& other) const noexcept {
    for (auto i = 0; i < N; i++) {
      if (data[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Vector& other) const noexcept {
    return !(*this == other);
  }

  static Vector zero() noexcept {
    return Vector([](Index) { return F::zero(); });
  }

  using container = Array<F, N>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  iterator begin() noexcept { return data.begin(); }

  iterator end() noexcept { return data.end(); }

  [[nodiscard]] const_iterator begin() const noexcept { return data.begin(); }

  [[nodiscard]] const_iterator end() const noexcept { return data.end(); }

private:
  Vector& negate() noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] = -data[i];
    }
    return *this;
  }

  // TODO: use Mathematica::Collection::Array
  Array<F, N> data;
};

template <typename T, size_t N>
Vector<T, N> operator*(T scalar, const Vector<T, N>& vector) noexcept {
  return vector * scalar;
}

}