#pragma once

#include "Mathematica/Algebra/FieldTrait.hpp"
#include "Mathematica/Algebra/Linear/Matrix.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra::Linear::Eq {

template <typename F, Size N, Field::BasicOp<F> Op = Field::BasicOp<F>()>
struct System {
  Matrix<F, N, N, Op> a;
  Vector<F, N, Op> b;
};

template <typename F, Size N, Field::BasicOp<F> Op = Field::BasicOp<F>()>
struct Solution {
  Vector<F, N, Op> value;
  Vector<F, N, Op> error;
};

}