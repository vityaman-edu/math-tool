#pragma once

#include "Mathematica/Algebra/FieldTrait.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"

namespace Mathematica::Statistics {

template <
    typename F,
    Algebra::Field::BasicOp<F> Op = Algebra::Field::BasicOp<F>()>
F pcc(const ArrayList<Point<F>>& points) { // TODO: take Iterable
  (void)points;
  return 0; // TODO: Not implemented
}

}