#pragma once
#include "interval.hpp"
#include "math/eq/solve/function.hpp"

namespace math::eq::solve {

template <typename T>
class method {
public:
  virtual T find_some_root(interval<T> interval, function<T> function) = 0;
};

}