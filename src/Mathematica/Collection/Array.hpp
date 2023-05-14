#pragma once

#include "Mathematica/Core.hpp"
#include <array>
#include <cassert>

namespace Mathematica::Collection {

template <typename T, Size N>
class Array {
public:
  explicit Array() = default;

  explicit Array(const std::array<T, N>& data)
    : Array([&data](auto index) { return data[index]; }) {}

  explicit Array(const Mapping<T(Index)>& item) {
    for (auto i = 0; i < N; i++) {
      data[i] = item(i);
    }
  }

  T& operator[](Index index) noexcept {
    assert(index < data.size());
    return data[index];
  }

  T operator[](Index index) const noexcept {
    assert(index < data.size());
    return data[index];
  }

  Array map(const Mapping<T(T)>& mapping) const noexcept {
    return Array<T, N>([&mapping, *this](auto i) { //
      return mapping(data[i]);
    });
  }

  using container = std::array<T, N>;
  using iterator = typename container::iterator;
  using const_iterator = typename container::const_iterator;
  iterator begin() noexcept { return data.begin(); }
  iterator end() noexcept { return data.end(); }
  [[nodiscard]] const_iterator begin() const noexcept { return data.begin(); }
  [[nodiscard]] const_iterator end() const noexcept { return data.end(); }

private:
  std::array<T, N> data;
};

}