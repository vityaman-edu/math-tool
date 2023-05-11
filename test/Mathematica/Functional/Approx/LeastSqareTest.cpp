#include "Mathematica/Functional/Approx/LeastSqare.hpp"
#include "Mathematica/Algebra/Field.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Interop/Polynomial.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;                     // NOLINT
using namespace Mathematica::Functional::Approx; // NOLINT
using Mathematica::Algebra::Float;
using Mathematica::Interop::symbolic;
using Symatica::Expression::DSL::var;
using F = double;

TEST(LeastSqare, Playground) { // NOLINT
  // clang-format off
  const auto points = Array<Point<Float<F>>, 3>({{
      {.x = 1,  .y = 0 },
      {.x = -6, .y = 0 },
      {.x = 0,  .y = -6},
  }});
  // clang-format on

  const auto poly = LeastSqare::optimalPolynomial<Float<F>, 3>(points);
  const auto expr = symbolic(poly, var(1));
  std::cout << expr->asString() << std::endl;
}

TEST(LeastSqare, Polynomial) { // NOLINT
  const auto parabola = [](const Float<F>& x) {
    return x * x + Float(5.0) * x - Float(6.0); // NOLINT
  };

  // clang-format off
  const auto points = Array<Point<Float<F>>, 3>({{
      {.x =  1,  .y = parabola(1) },
      {.x = -6, .y = parabola(-6) },
      {.x =  0,  .y = parabola(0) },
  }});
  // clang-format on

  const auto poly = LeastSqare::optimalPolynomial<Float<F>, 3>(points);
  for (Float<F> x = -30; x < 30; x += 0.2) { // NOLINT
    ASSERT_EQ(poly(x), parabola(x));
  }
}