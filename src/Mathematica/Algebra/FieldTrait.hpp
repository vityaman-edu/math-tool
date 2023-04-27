#pragma once

#include <cmath>
namespace Mathematica::Algebra::Field {

template <typename T>
class Op {
public:
  virtual T sum(T left, T right) const noexcept;
  virtual T neg(T value) const noexcept;
  virtual T zero() const noexcept;
  virtual T dif(T left, T right) const noexcept { return left + neg(right); }
  virtual T mul(T left, T right) const noexcept;
  virtual T rev(T value) const noexcept;
  virtual T unit() const noexcept;
  virtual T div(T left, T right) const noexcept { return left * rev(right); }
  virtual bool equals(T left, T right) const noexcept;
};

template <typename T>
class BasicOp : public Op<T> {
private:
  constexpr static auto EPSILON = 0.00000001;
public:
  constexpr BasicOp() = default;

  constexpr T sum(T left, T right) const noexcept override {
    return left + right;
  }

  constexpr T neg(T value) const noexcept override { return -value; }

  constexpr T zero() const noexcept override { return 0; }

  constexpr T dif(T left, T right) const noexcept override {
    return left - right;
  }

  constexpr T mul(T left, T right) const noexcept override {
    return left * right;
  }

  constexpr T rev(T value) const noexcept override { return 1 / value; }

  constexpr T unit() const noexcept override { return 1; }

  constexpr T div(T left, T right) const noexcept override {
    return left / right;
  }

  constexpr bool equals(T left, T right) const noexcept override {
    return std::abs(left - right) < EPSILON;
  }
};

}