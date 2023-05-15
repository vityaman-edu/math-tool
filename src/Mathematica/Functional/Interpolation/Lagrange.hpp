#pragma once

#include "Mathematica/Abstract/Field.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
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
using Symatica::Expression::DSL::operator/;
using Symatica::Core::Ptr;
using Symatica::Expression::Expression;
using Symatica::Expression::Variable;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::var;

using Mathematica::Collection::Array;

template <Abstract::Field F, Count N>
Ptr<Expression>
lagrangeSymbolic(const Array<Point<F>, N>& points, const Ptr<Variable>& x) noexcept {
  auto poly = l(0);
  for (const auto& [xi, yi] : points) {
    auto summand = l(yi);
    for (const auto& [xj, yj] : points) {
      if (xi != xj) {
        summand = summand * ((x - l(xj)) / (xi - xj));
      }
    }
  }
  return poly;
}

}