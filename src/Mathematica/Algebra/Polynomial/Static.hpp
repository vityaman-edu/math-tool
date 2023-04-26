#pragma once

#include "Mathematica/Algebra/Polynomial/Abstraction.hpp"
#include <array>

namespace Mathematica::Algebra {

template <typename T, PolynomialDegree N>
class StaticPolynomial : public Polynomial<T> {
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

private:
  std::array<T, N> coefficients;
};

}