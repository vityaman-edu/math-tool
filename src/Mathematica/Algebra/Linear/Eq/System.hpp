#pragma once

#include "Mathematica/Algebra/Field.hpp"
#include "Mathematica/Algebra/Linear/Matrix.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra::Linear::Eq {

template <typename F, Size N> requires Real<F>
struct System {
  Matrix<F, N, N> a;
  Vector<F, N> b;
};

template <typename F, Size N> requires Real<F>
struct Solution {
  Vector<F, N> value;
  Vector<F, N> error;
};

}