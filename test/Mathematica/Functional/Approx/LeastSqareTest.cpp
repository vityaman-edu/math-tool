#include "Mathematica/Functional/Approx/LeastSqare.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/Point.hpp"
#include "Mathematica/Interop/Polynomial.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;                     // NOLINT
using namespace Mathematica::Functional::Approx; // NOLINT
using Mathematica::Interop::symbolic;
using Symatica::Expression::DSL::var;
using F = double;
constexpr auto EPS = 0.0000001;

TEST(LeastSqare, Playground) { // NOLINT
  // clang-format off
  const auto points = Array<Point<F>, 3>({{
      {.x = 1,  .y = 0 },
      {.x = -6, .y = 0 },
      {.x = 0,  .y = -6},
  }});
  // clang-format on

  const auto poly = LeastSqare::optimalPolynomial<F, 3>(points);
  const auto expr = symbolic(poly, var(1));
  std::cout << expr->asString() << std::endl;
}

TEST(LeastSqare, Polynomial) { // NOLINT
  const auto parabola = [](F x) {
    return x * x + 5 * x - 6; // NOLINT
  };

  // clang-format off
  const auto points = Array<Point<F>, 3>({{
      {.x =  1,  .y = parabola(1) },
      {.x = -6, .y = parabola(-6) },
      {.x =  0,  .y = parabola(0) },
  }});
  // clang-format on

  const auto poly = LeastSqare::optimalPolynomial<F, 3>(points);
  for (F x = -30; x < 30; x += 0.2) { // NOLINT
    ASSERT_NEAR(poly(x), parabola(x), EPS);
  }
}