#include "Mathematica/Functional/Interpolation/Newton.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include <gtest/gtest.h>

using Mathematica::Point;
using Mathematica::Collection::Array;
using Mathematica::Functional::Interpolation::dividedDifference;
using Mathematica::Functional::Interpolation::symbolicNewton;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::var;
using Symatica::Symbol::TreeTable;
using Symatica::Visitor::Evaluator;
using R = Mathematica::Abstract::Float<double>;

TEST(MathematicaFunctionalInterpolation, NewtonSymbolic1) { // NOLINT
  // clang-format off
  const auto points = Array<Point<R>, 4>({{
    { 0, 0 }, { 2, 1 }, { 3, 3 }, { 5, 2 },
  }});
  // clang-format on

  ASSERT_NEAR(dividedDifference(points, 0).value, 0, 0.00001);
  ASSERT_NEAR(dividedDifference(points, 1).value, 0.5, 0.00001);
  ASSERT_NEAR(dividedDifference(points, 2).value, 0.5, 0.00001);
  ASSERT_NEAR(dividedDifference(points, 3).value, -4.0 / 15, 0.00001);

  const auto x = var(1);
  const auto poly = symbolicNewton(points, x);

  std::cout << poly->asString() << std::endl;

  // use some fast micromap to store values
  auto table = TreeTable({});
  auto eval = Evaluator(table);

  auto actual = [&table, &eval, &poly](double x) {
    table.put(1, l(x));
    return eval.valueOf(poly);
  };

  auto expected = [](double x) {
    return 0                                         // NOLINT
           + 0.5 * (x - 0)                           // NOLINT
           + 0.5 * (x - 0) * (x - 2)                 // NOLINT
           - 4.0 / 15 * (x - 0) * (x - 2) * (x - 3); // NOLINT
  };

  for (const auto& [x, y] : points) {
    ASSERT_NEAR(actual(x.value), y.value, 0.0001);
  }
  for (double x = -100; x <= 100; x += 0.5) { // NOLINT
    ASSERT_NEAR(actual(x), expected(x), 0.00001);
  }
}