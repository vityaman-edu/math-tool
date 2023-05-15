#include "Mathematica/Functional/Interpolation/Lagrange.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include <gtest/gtest.h>

using Mathematica::Point;
using Mathematica::Collection::Array;
using Mathematica::Functional::Interpolation::symbolicLagrange;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::var;
using Symatica::Symbol::TreeTable;
using Symatica::Visitor::Evaluator;
using R = Mathematica::Abstract::Float<double>;

TEST(MathematicaFunctionalInterpolation, LagrangeSymbolic1) { // NOLINT
  // clang-format off
  const auto points = Array<Point<R>, 5>({{
    { 0.1, 1.25 },
    { 0.2, 2.38 },
    { 0.3, 3.79 },
    { 0.4, 5.44 },
    { 0.5, 7.14 },
  }});
  // clang-format on

  const auto x = var(1);
  const auto poly = symbolicLagrange(points, x);

  auto table = TreeTable({});
  auto eval = Evaluator(table);

  auto f = [&table, &eval, &poly](double x) {
    table.put(1, l(x));
    return eval.valueOf(poly);
  };

  for (const auto& [x, y] : points) {
    ASSERT_NEAR(f(x.value), y.value, 0.0001);
  }
  ASSERT_NEAR(f(0.35), 4.59336, 0.0001);
}

TEST(MathematicaFunctionalInterpolation, LagrangeSymbolic2) { // NOLINT
  // clang-format off
  const auto points = Array<Point<R>, 4>({{
    { 1, 0 },
    { 2, 3 },
    { 3, 5 },
    { 4, 7 },
  }});
  // clang-format on

  const auto x = var(1);
  const auto poly = symbolicLagrange(points, x);

  auto table = TreeTable({});
  auto eval = Evaluator(table);

  auto actual = [&table, &eval, &poly](double x) {
    table.put(1, l(x));
    return eval.valueOf(poly);
  };

  auto expected = [](double x) {
    return 3 * (x - 1) * (x - 3) * (x - 4) / ((2 - 1) * (2 - 3) * (2 - 4))
           + 5 * (x - 1) * (x - 2) * (x - 4) / ((3 - 1) * (3 - 2) * (3 - 4))
           + 7 * (x - 1) * (x - 2) * (x - 3) / ((4 - 1) * (4 - 2) * (4 - 3));
  };

  for (double x = -100; x <= 100; x += 0.5) { // NOLINT
    ASSERT_NEAR(actual(x), expected(x), 0.00001);
  }
}