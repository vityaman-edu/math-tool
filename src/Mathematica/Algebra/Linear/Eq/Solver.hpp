#pragma once

#include "Mathematica/Algebra/Linear/Eq/System.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra::Linear::Eq {

template <typename F, Size N, Field::BasicOp<F> Op = Field::BasicOp<F>()>
using Solver = Mapping<Solution<F, N, Op>(System<F, N, Op>)>;

}