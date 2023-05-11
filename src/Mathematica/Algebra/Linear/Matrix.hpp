#pragma once

#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra::Linear {

template <Abstract::Field F, Size R, Size C>
class Matrix {
public:
  explicit Matrix() = default;

  explicit Matrix(const Array<Array<F, C>, R>& data)
      : Matrix([&data](auto row, auto col) { return data[row][col]; }) {}

  explicit Matrix(const Mapping<F(Index, Index)>& item) {
    for (auto i = 0; i < R; i++) {
      for (auto j = 0; j < C; j++) {
        data[i][j] = item(i, j);
      }
    }
  }

  Matrix(const Matrix& other)
      : Matrix([&other](auto row, auto col) { return other[row][col]; }) {}

  ~Matrix() = default;

  Vector<F, C>& operator[](Index row) noexcept {
    assert(row < data.size());
    return data[row];
  }

  const Vector<F, C>& operator[](Index row) const noexcept {
    assert(row < data.size());
    return data[row];
  }

  Matrix& operator+=(const Matrix& other) noexcept {
    for (auto i = 0; i < R; i++) {
      data[i] += other[i];
    }
    return *this;
  }

  Matrix operator+(const Matrix& other) const noexcept {
    auto copy = *this;
    return copy += other;
  }

  Matrix& operator-=(const Matrix& other) noexcept {
    for (auto i = 0; i < R; i++) {
      data[i] -= other[i];
    }
    return *this;
  }

  Matrix operator-(const Matrix& other) const noexcept {
    auto copy = *this;
    return copy -= other;
  }

  Matrix& operator*=(F scalar) noexcept {
    for (auto i = 0; i < R; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  Matrix operator*(F scalar) const noexcept {
    auto copy = *this;
    return copy *= scalar;
  }

  Matrix& operator/=(F scalar) noexcept {
    for (auto i = 0; i < R; i++) {
      data[i] /= scalar;
    }
    return *this;
  }

  Matrix operator/(F scalar) const noexcept { return *this /= scalar; }

  Matrix operator-() const noexcept { return this->negate(); }

  bool operator==(const Matrix& other) const noexcept {
    for (auto i = 0; i < R; i++) {
      if (data[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Matrix& other) const noexcept {
    return !(*this == other);
  }

  void swapRows(Index i, Index j) noexcept {
    assert(i < R && j < R);
    std::swap(data[i], data[j]);
  }

  void swapCols(Index i, Index j) noexcept {
    assert(i < C && j < C);
    for (auto k = 0; k < R; k++) {
      std::swap(data[k][i], data[k][j]);
    }
  }

  static Matrix zero() noexcept {
    return matrix([](auto, auto) { return F::zero(); });
  }

  static Matrix unit() noexcept {
    return matrix([](auto row, auto col) {
      return ((row == col) ? (F::unit()) : (F::zero()));
    });
  }

private:
  Matrix& negate() noexcept {
    for (auto i = 0; i < R; i++) {
      data[i] = - data[i];
    }
    return *this;
  }

  Array<Vector<F, C>, R> data;
};

}