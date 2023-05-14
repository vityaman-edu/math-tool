#pragma once

#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Core.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>

namespace Mathematica {

template <typename T>
class Partition {
public:
  class iterator {
    using iterator_category = std::forward_iterator_tag;
    using value_type = Interval<T>;
    using difference_type = std::size_t;
    using pointer = const Interval<T>*;
    using reference = Interval<T>;

  public:
    explicit iterator(Index i, Partition<T> owner) : owner(owner), i(i) {}

    iterator& operator++() noexcept {
      i += 1;
      return *this;
    }

    iterator operator++(int) noexcept {
      iterator retval = *this;
      ++(*this);
      return retval;
    }

    bool operator==(iterator other) const noexcept {
      return i == other.i && owner == other.owner;
    }

    bool operator!=(iterator other) const noexcept { return !(*this == other); }

    Interval<T> operator*() const {
      auto left = owner.interval.left() + owner.atomLength() * i;
      return Interval<T>(left, left + owner.atomLength());
    }

  private:
    Partition<T> owner;
    Index i;
  };

  Partition(Interval<T> interval, Count count)
      : interval(interval), count(count) {}

  iterator begin() const noexcept { return iterator(0, *this); }

  iterator end() const noexcept { return iterator(count, *this); }

  bool operator==(Partition other) const noexcept {
    return interval == other.interval && count == other.count;
  }

  T atomLength() const noexcept { return interval.length() / count; }

  static Partition<T> fromFineness(Interval<T> interval, T fineness) noexcept {
    assert(0 < fineness);
    assert(fineness <= interval.length());
    auto count = std::ceil(interval.length() / fineness);
    return Partition<T>(interval, count);
  }

private:
  Interval<T> interval;
  Count count;
};

}