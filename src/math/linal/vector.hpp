#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <functional>

namespace math::linal {

template <typename F, size_t N>
class vector {
public:
  explicit vector() = default;

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

  F operator[](size_t index) const {
    assert(index < data.size());
    return data[index];
  }

  F& operator[](size_t index) {
    assert(index < data.size());
    return data[index];
  }

  vector& operator*=(F scalar) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] *= scalar;
    }
    return *this;
  }

  vector operator*(F scalar) const noexcept {
    auto mult = *this;
    return mult *= scalar;
  }

  vector& operator+=(const vector& other) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] += other[i];
    }
    return *this;
  }

  vector operator+(const vector& other) const noexcept {
    auto sum = *this;
    return sum += other;
  }

  vector& operator-=(const vector& other) noexcept {
    for (size_t i = 0; i < N; i++) {
      data[i] -= other[i];
    }
    return *this;
  }

  vector operator-(const vector& other) const noexcept {
    auto diff = *this;
    return diff -= other;
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

  vector& operator=(const vector& other) noexcept = default;
  vector& operator=(vector&& other) noexcept = default;

  ~vector() = default;

  static vector zero() noexcept {
    return vector([](size_t) { return 0; });
  }

private:
  std::array<F, N> data;
};

}
