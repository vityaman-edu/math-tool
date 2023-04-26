#pragma once

#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra {

using PolynomialDegree = Size;

template <typename T>
class Polynomial {
public:
  T operator()(T argument) const noexcept;

  T& operator[](Index index) noexcept;
  T operator[](Index index) const noexcept;
  [[nodiscard]] PolynomialDegree degree() const noexcept;

  Polynomial<T> operator+(const Polynomial<T>& other) const noexcept;
  void operator+=(const Polynomial<T>& other) noexcept;

  Polynomial<T> operator-(const Polynomial<T>& other) const noexcept;
  void operator-=(const Polynomial<T>& other) noexcept;

  Polynomial<T> operator*(T scalar) const noexcept;
  void operator*=(T scalar) noexcept;

  Polynomial<T> operator*(const Polynomial<T>& other) const noexcept;
  void operator*=(const Polynomial<T>& other) noexcept;

  Polynomial<T> operator/(T scalar) const noexcept;
  void operator/=(T scalar) noexcept;

  Polynomial<T> operator-() const noexcept;
};

}