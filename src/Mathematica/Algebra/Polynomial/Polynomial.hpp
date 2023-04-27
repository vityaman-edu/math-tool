#pragma once

#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Algebra/Linear/IO.hpp"
#include "Mathematica/Core.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

namespace Mathematica::Algebra {

using PolynomialDegree = Integer;
constexpr PolynomialDegree PolynomialDegreeMinusInfty = -1;

template <
    typename F,
    PolynomialDegree N,
    Field::BasicOp<F> Op = Field::BasicOp<F>()>
class Polynomial {
public:
  explicit Polynomial(const Linear::Vector<F, N>& coefficients)
      : coefficients(coefficients) {}

  Polynomial(const Polynomial& other) : Polynomial(other.coefficients) {}

  F operator()(F argument) const noexcept {
    auto value = Op.zero();
    const auto deg = degree();
    for (auto i = 0; i <= deg; i++) {
      // TODO: std::pow - not an abstract operation
      const auto element = Op.mul(coefficients[i], std::pow(argument, i));
      value = Op.sum(value, element);
    }
    return value;
  }

  F& operator[](Index index) noexcept {
    assert(index < N);
    return coefficients[index];
  }

  F operator[](Index index) const noexcept {
    if (N <= index) {
      return 0;
    }
    return coefficients[index];
  }

  [[nodiscard]] PolynomialDegree degree() const noexcept {
    for (PolynomialDegree i = N - 1; 0 <= i; i--) {
      if (!Op.equals(coefficients[i], Op.zero())) {
        return i;
      }
    }
    return PolynomialDegreeMinusInfty;
  }

  Polynomial operator+(const Polynomial& other) const noexcept {
    return Polynomial(coefficients + other.coefficients);
  }

  Polynomial& operator+=(const Polynomial& other) noexcept {
    coefficients += other.coefficients;
    return *this;
  }

  Polynomial operator-(const Polynomial& other) const noexcept {
    return Polynomial(coefficients - other.coefficients);
  }

  Polynomial& operator-=(const Polynomial& other) noexcept {
    coefficients -= other.coefficients;
    return *this;
  }

  Polynomial operator*(F scalar) const noexcept {
    return Polynomial(coefficients * scalar);
  }

  Polynomial& operator*=(F scalar) noexcept {
    coefficients *= scalar;
    return *this;
  }

  Polynomial operator/(F scalar) const noexcept {
    return Polynomial(coefficients / scalar);
  }

  Polynomial& operator/=(F scalar) noexcept {
    coefficients /= scalar;
    return *this;
  }

  Polynomial operator-() const noexcept { return Polynomial(-coefficients); }

private:
  Linear::Vector<F, N> coefficients;
};

template <
    typename F,
    PolynomialDegree A,
    PolynomialDegree B,
    Field::BasicOp<F> Op = Field::BasicOp<F>()>
Polynomial<F, A + B>
operator*(const Polynomial<F, A>& a, const Polynomial<F, B>& b) noexcept {
  return Polynomial(Linear::Vector<F, A + B>([=](auto n) {
    auto sum = Op.zero();
    for (auto i = 0; i < n; i++) {
      sum = Op.sum(sum, Op.mul(a[i], b[n - i]));
    }
    return sum;
  }));
}

}