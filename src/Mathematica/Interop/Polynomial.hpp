#pragma once

#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Variable.hpp"
#include "Symatica/Visitor/Optimizer.hpp"

namespace Mathematica::Interop {

using Symatica::Core::Ptr;
using Symatica::Expression::Expression;
using Symatica::Expression::Variable;
using namespace Symatica::Expression::DSL; // NOLINT

template <typename F, Algebra::PolynomialDegree D>
Ptr<Expression>
symbolic(Algebra::Polynomial<F, D> polynomial, const Ptr<Variable>& x) {
  Ptr<Expression> poly = l(0);
  for (auto i = 0; i < D; i++) {
    poly = poly + l(polynomial[i]) * pow(x, l(i));
  }
  auto make = Symatica::Visitor::Optimizer();
  return make.optimized(poly);
}

}
