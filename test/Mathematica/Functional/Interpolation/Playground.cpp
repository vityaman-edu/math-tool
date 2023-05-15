#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Functional/Interpolation/Lagrange.hpp"
#include "Mathematica/Functional/Interpolation/Newton.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include <gtest/gtest.h>
#include <iomanip>

using Mathematica::Point;
using Mathematica::Collection::Array;
using Mathematica::Functional::Interpolation::dividedDifference;
using R = Mathematica::Abstract::Float<double>;

TEST(MathematicaFunctionalInterpolation, Playground) { // NOLINT
  constexpr auto N = 7;
  // clang-format off
  const auto points = Array<Point<R>, N>({{
    { 0.25, 1.2557 },
    { 0.30, 2.1764 },
    { 0.35, 3.1218 },
    { 0.40, 4.0482 },
    { 0.45, 5.9875 },
    { 0.50, 6.9195 },
    { 0.55, 7.8359 },
  }});
  const auto testX = Array<R, N + N>({{
    0.251, 0.512, 0.255, 0.534, 0.272,
    0.551, 0.294, 0.402, 0.372, 0.405, 
    0.384, 0.445, 0.351, 0.437
  }});
  // clang-format on

  constexpr auto X = 1;
  const auto x = Symatica::Expression::DSL::var(X);
  auto table = Symatica::Symbol::TreeTable({});
  auto eval = Symatica::Visitor::Evaluator(table);

  const auto lagrange
      = Mathematica::Functional::Interpolation::symbolicLagrange(points, x);
  const auto newton
      = Mathematica::Functional::Interpolation::symbolicNewton(points, x);

  std::cout << "Interpolation::symbolicLagrange:" << std::endl;
  std::cout << lagrange->asString() << std::endl << std::endl;

  std::cout << "Interpolation::symbolicNewton:" << std::endl;
  std::cout << newton->asString() << std::endl;

  const auto lagrangeAt = [&table, &eval, &lagrange](double x) {
    table.put(X, Symatica::Expression::DSL::l(x));
    return eval.valueOf(lagrange);
  };

  const auto newtonAt = [&table, &eval, &newton](double x) {
    table.put(X, Symatica::Expression::DSL::l(x));
    return eval.valueOf(newton);
  };

  std::cout << "Interpolation::Newton::dividedDifferences: " << std::endl;
  for (auto i = 0; i < N; i++) {
    std::cout << i << ": " << dividedDifference(points, i).value << std::endl;
  }

  for (const auto& x : testX) {
    std::cout << "lagrange(" << x << ") = " << lagrangeAt(x.value) << std::endl;
    std::cout << "newton(" << x << ") = " << newtonAt(x.value) << std::endl;
  }
}