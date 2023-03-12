#pragma once

#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>

namespace math::eq::lin::sys {

template <typename F, size_t N>
struct lineqsys { // NOLINT
  math::linal::matrix<F, N, N> a;
  math::linal::vector<F, N> b;
};

}