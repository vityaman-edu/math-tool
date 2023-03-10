#pragma once

#include "math/linal/vector.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <functional>

namespace math::linal {

template <typename F, size_t R, size_t C>
class matrix {
public:
  explicit matrix() = default;

  explicit matrix(const std::array<std::array<F, C>, R>& data)
      : matrix([&data](size_t row, size_t col) {
          return data[row][col];
        }) {}

  explicit matrix(const std::function<F(size_t, size_t)>& fill) {
    for (size_t i = 0; i < R; i++) {
      for (size_t j = 0; j < C; j++) {
        data[i][j] = fill(i, j);
      }
    }
  }

  matrix(const matrix& other)
      : matrix([&other](size_t row, size_t col) {
          return other.data[row][col];
        }) {}

  template <size_t I, size_t J>
  [[nodiscard]] F at() const noexcept {
    static_assert(
        I < R, "I (row) should be less than size rows count R"
    );
    static_assert(
        J < C, "J (col) should be less than size cols count C"
    );
    return data[I][J];
  }

  const vector<F, C>& operator[](size_t row) const {
    assert(row < data.size());
    return data[row];
  }

  vector<F, C>& operator[](size_t row) {
    assert(row < data.size());
    return data[row];
  }

  matrix& operator*=(F scalar) noexcept {
    for (size_t i = 0; i < R; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  matrix operator*(F scalar) const noexcept {
    auto mult = *this;
    return mult *= scalar;
  }

  matrix& operator+=(const matrix& other) noexcept {
    for (size_t i = 0; i < R; i++) {
      data[i] += other[i];
    }
    return *this;
  }

  matrix operator+(const matrix& other) const noexcept {
    auto sum = *this;
    return sum += other;
  }

  matrix& operator-=(const matrix& other) noexcept {
    for (size_t i = 0; i < R; i++) {
      data[i] -= other[i];
    }
    return *this;
  }

  matrix operator-(const matrix& other) const noexcept {
    auto diff = *this;
    return diff -= other;
  }

  bool operator==(const matrix& other) const noexcept {
    for (size_t i = 0; i < R; i++) {
      if (data[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const matrix& other) const noexcept {
    return !(*this == other);
  }

  matrix& operator=(const matrix& other) noexcept = default;
  matrix& operator=(matrix&& other) noexcept = default;

  ~matrix() = default;

  static matrix zero() noexcept {
    return matrix([](size_t, size_t) { return 0; });
  }

  static matrix unit() noexcept {
    return matrix([](size_t row, size_t col) {
      return ((row == col) ? (1) : (0));
    });
  }

private:
  std::array<vector<F, C>, R> data;
};

}