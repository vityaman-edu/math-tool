#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Algebra/Linear/Matrix.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra::Linear::Eq {

template <Abstract::Real F, Size N>
struct System {
  Matrix<F, N, N> a;
  Vector<F, N> b;
};

template <Abstract::Real F, Size N>
struct Solution {
  Vector<F, N> value;
  Vector<F, N> error;
};

}