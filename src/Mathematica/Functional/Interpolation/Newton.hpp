#pragma once

#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Variable.hpp"
#include <cassert>
#include <numeric>

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

template <Abstract::Real F, Size N>
F dividedDifference(const Array<Point<F>, N>& points, Index n) noexcept {
  assert(n < N);
  auto sum = F::zero();
  for (auto j = 0; j < n + 1; j++) {
    auto numerator = points[j].y;
    auto denominator = F::unit();
    for (auto i = 0; i < n + 1; i++) {
      if (i != j) {
        denominator *= (points[j].x - points[i].x);
      }
    }
    sum += numerator / denominator;
  }
  return sum;
}

// Reference: https://www.youtube.com/watch?v=Bi4KzPGtdQU
template <Count N>
Ptr<Expression> symbolicNewton(
    const Array<Point<F>, N>& points, const Ptr<Variable>& x
) noexcept {
  Ptr<Expression> poly = l(0);
  for (auto k = 0; k < N; k++) {
    Ptr<Expression> tail = l(1);
    for (auto i = 0; i < k; i++) {
      tail = tail * (x - l(points[i].x.value));
    }
    std::cout << "dividedDifference(" << k << ") = " << dividedDifference(points, k).value << std::endl;
    poly = poly + l(dividedDifference(points, k).value) * tail;
  }
  return poly;
}

}