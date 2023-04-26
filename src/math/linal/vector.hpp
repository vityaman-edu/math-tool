#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>

namespace math::linal {

template <typename F, size_t N>
class Vector {
public:
  explicit Vector() = default;

  explicit Vector(const std::array<F, N>& array)
      : Vector([&array](size_t index) { return array[index]; }) {}

  explicit Vector(const std::function<F(size_t)>& fill) {
    for (size_t i = 0; i < N; i++) {
      data[i] = fill(i);
    }
  }

  Vector(const Vector& other) : Vector(other.data) {}

  F operator[](size_t index) const {
    assert(index < data.size());
    return data[index];
  }

  F& operator[](size_t index) {
    assert(index < data.size());
    return data[index];
  }

  Vector& operator*=(F scalar) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  Vector operator*(F scalar) const noexcept {
    auto mult = *this;
    return mult *= scalar;
  }

  Vector& operator+=(const Vector& other) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] += other[i];
    }
    return *this;
  }

  Vector operator+(const Vector& other) const noexcept {
    auto sum = *this;
    return sum += other;
  }

  Vector& operator-=(const Vector& other) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] -= other[i];
    }
    return *this;
  }

  Vector operator-(const Vector& other) const noexcept {
    auto diff = *this;
    return diff -= other;
  }

  bool operator==(const Vector& other) const noexcept {
    for (size_t i = 0; i < N; i++) {
      if (data[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Vector& other) const noexcept {
    return !(*this == other);
  }

  Vector& operator=(const Vector& other) noexcept = default;
  Vector& operator=(Vector&& other) noexcept = default;

  using container = std::array<F, N>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;

  iterator begin() noexcept { return data.begin(); }

  iterator end() noexcept { return data.end(); }

  [[nodiscard]] const_iterator begin() const noexcept {
    return data.begin();
  }

  [[nodiscard]] const_iterator end() const noexcept {
    return data.end();
  }

  ~Vector() = default;

  static Vector zero() noexcept {
    return Vector([](size_t) { return 0; });
  }

private:
  container data;
};

template <typename F, size_t N>
Vector<F, N>
operator*(F scalar, const Vector<F, N>& vector) noexcept {
  return vector * scalar;
}

template <typename F, size_t N>
std::ostream& operator<<(std::ostream& out, const Vector<F, N>& vec) {
  out << "{ ";
  for (size_t i = 0; i < N - 1 && N > 0; i++) {
    out << vec[i] << ", ";
  }
  if (N > 0) {
    out << vec[N - 1];
  }
  out << " }";
  return out;
}

}
