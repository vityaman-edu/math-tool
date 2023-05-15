#include "Mathematica/Functional/Interpolation/Lagrange.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include <gtest/gtest.h>

using Mathematica::Point;
using Mathematica::Collection::Array;
using Mathematica::Functional::Interpolation::lagrangeSymbolic;
using Symatica::Expression::DSL::var;
using Symatica::Expression::DSL::l;
using Symatica::Symbol::TreeTable;
using Symatica::Visitor::Evaluator;
using R = Mathematica::Abstract::Float<double>;

TEST(MathematicaFunctionalInterpolation, LagrangeSymbolic) { // NOLINT
  // clang-format off
  const auto points = Array<Point<R>, 10>({{
    { 0.1, 1.25 },
    { 0.2, 2.38 },
    { 0.3, 3.79 },
    { 0.4, 5.54 },
    { 0.5, 7.14 },
  }});
  // clang-format on

  const auto x = var(1);
  const auto poly = lagrangeSymbolic(points, x);

  auto table = TreeTable({});
  auto eval = Evaluator(table);

  table.put(1, l(0.35)); // NOLINT
  ASSERT_NEAR(eval.valueOf(poly), 4.59336, 0.01);
}