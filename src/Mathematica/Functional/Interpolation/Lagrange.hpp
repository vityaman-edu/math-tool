#pragma once

#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Variable.hpp"

namespace Mathematica::Functional::Interpolation {

using Symatica::Expression::DSL::operator*;
using Symatica::Expression::DSL::operator-;
using Symatica::Expression::DSL::operator+;
using Symatica::Expression::DSL::operator/;
using Mathematica::Collection::Array;
using Symatica::Core::Ptr;
using Symatica::Expression::Expression;
using Symatica::Expression::Variable;
using Symatica::Expression::DSL::l;

// TODO: temporary due symatica uses only doubles
using F = Mathematica::Abstract::Float<double>;

template <Count N>
Ptr<Expression> lagrangeSymbolic(
    const Array<Point<F>, N>& points, const Ptr<Variable>& x
) noexcept {
  const auto X
      = Array<double, N>([&points](auto i) { return points[i].x.value; });
  const auto Y
      = Array<double, N>([&points](auto i) { return points[i].y.value; });
  Ptr<Expression> poly = l(0);
  for (auto i = 0; i < N; i++) {
    Ptr<Expression> summand = l(Y[i]);
    for (auto j = 0; j < N; j++) {
      if (i != j) {
        summand = summand * ((x - l(X[j])) / l(X[i] - X[j]));
      }
    }
    poly = poly + summand;
  }
  return poly;
}

}