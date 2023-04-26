#pragma once

#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra::Linear {

template <typename T, Size N>
class Vector {
public:
  explicit Vector() = default;

  explicit Vector(const Array<T, N>& array)
      : Vector([=](auto index) { return array[index]; }) {}

  explicit Vector(const Mapping<T(Index)>& item) {
    for (auto i = 0; i < N; i++) {
      data[i] = item(i);
    }
  }

  Vector(const Vector& other) : Vector(other.data) {}

  T& operator[](Index index) noexcept {
    assert(index < data.size());
    return data[index];
  }

  T operator[](Index index) const noexcept { return (*this)[index]; }

  Vector& operator+=(const Vector& other) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] += other[i];
    }
    return *this;
  }

  Vector operator+(const Vector& other) const noexcept {
    return *this += other;
  }

  Vector& operator-=(const Vector& other) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] -= other[i];
    }
    return *this;
  }

  Vector operator-(const Vector& other) const noexcept {
    return *this -= other;
  }

  Vector& operator*=(T scalar) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  Vector operator*(T scalar) const noexcept {
    return *this *= scalar; //
  }

  Vector& operator/=(T scalar) noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] /= scalar;
    }
    return *this;
  }

  Vector operator/(T scalar) const noexcept {
    return *this /= scalar; //
  }

  Vector operator-() const noexcept {
    return this->negate(); //
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
    return Vector([](Index) { return 0; });
  }

private:
  Vector& negate() noexcept {
    for (auto i = 0; i < N; i++) {
      data[i] = -data[i];
    }
    return *this;
  }

  Array<T, N> data;
};

template <typename T, size_t N>
Vector<T, N> operator*(T scalar, const Vector<T, N>& vector) noexcept {
  return vector * scalar;
}

}