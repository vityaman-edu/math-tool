#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <functional>

namespace math::linal {

template <typename F, size_t N>
class vector {
public:
  explicit vector(const std::array<F, N>& array)
      : vector([&array](size_t index) { return array[index]; }) {
  }

  explicit vector(const std::function<F(size_t)>& fill) {
    for (size_t i = 0; i < N; i++) {
      data[i] = fill(i);
    }
  }

  vector(const vector& other) : vector(other.data) {}

  template <size_t I>
  [[nodiscard]] F at() const noexcept {
    static_assert(I < N, "index I should be less than size N");
    return data[I];
  }

  F operator[](const size_t index) const {
    assert(index < data.size());
    return data[index];
  }

  F& operator[](const size_t index) {
    assert(index < data.size());
    return data[index];
  }

  vector& operator*=(const F scalar) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  vector operator*(const F scalar) const noexcept {
    auto mult = *this;
    mult *= scalar;
    return mult;
  }

  vector& operator+=(const vector& other) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] += other[i];
    }
    return *this;
  }

  vector operator+(const vector& other) const noexcept {
    vector sum = *this;
    sum += other;
    return sum;
  }

  vector& operator-=(const vector& other) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] -= other[i];
    }
    return *this;
  }

  vector operator-(const vector& other) const noexcept {
    auto diff = *this;
    diff -= other;
    return diff;
  }

  bool operator==(const vector& other) const noexcept {
    for (size_t i = 0; i < N; i++) {
      if (data[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const vector& other) const noexcept {
    return !(*this == other);
  }

  vector& operator=(const vector& other) = delete;
  vector& operator=(const vector&& other) = delete;

  ~vector() = default;

  static vector zero() noexcept {
    return vector([](size_t) { return 0; });
  }

private:
  vector() = default;

  std::array<F, N> data;
};

}
