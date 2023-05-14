#include "Mathematica/Functional/Approx/Linear.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Functional/Approx/Exponential.hpp"
#include "Mathematica/Functional/Approx/Logarithmic.hpp"
#include "Mathematica/Functional/Approx/Power.hpp"
#include "Mathematica/Statistics/Metrics.hpp"
#include "Mathematica/Statistics/RSS.hpp"
#include <gtest/gtest.h>

TEST(ApproxLinear, Example) { // NOLINT
  using Mathematica::Point;
  using Mathematica::Collection::Array;
  using Mathematica::Statistics::standartDeviation;
  using Mathematica::Statistics::Metrics::R2Score;
  using namespace Mathematica::Functional::Approx; // NOLINT
  using F = Mathematica::Abstract::Float<double>;
  constexpr auto N = 7;
  constexpr auto EPS = 0.001;

  // clang-format off
  const auto points = Array<Point<F>, N>({{
      { 1.1,  2.73 },
      { 2.3,  5.12 },
      { 3.7,  7.74 },
      { 4.5,  8.91 },
      { 5.4, 10.59 },
      { 6.8, 12.75 },
      { 7.5, 13.43 },
  }});
  // clang-format on

  const auto line = Linear::trendLine(points);
  const auto lineS = standartDeviation(line, points);
  ASSERT_NEAR(lineS.value, 0.25995, EPS);
  ASSERT_NEAR(line.slope().value, 1.685383, EPS);
  ASSERT_NEAR(line.bias().value, 1.216788, EPS);

  const auto pow = Power::train(points);
  const auto powS = standartDeviation(pow, points);
  ASSERT_NEAR(powS.value, 0.148514, EPS);
  ASSERT_NEAR(pow.multiplier.value, 2.542090, EPS);
  ASSERT_NEAR(pow.power.value, 0.838036, EPS);

  const auto exp = Exponential::train(points);
  const auto expS = standartDeviation(exp, points);
  ASSERT_NEAR(expS.value, 1.237, EPS);
  ASSERT_NEAR(exp.multiplier.value, 2.730945, EPS);
  ASSERT_NEAR(exp.powerSlope.value, 0.234550, EPS);

  const auto log = Logarithmic::train(points);
  const auto logS = standartDeviation(log, points);
  ASSERT_NEAR(logS.value, 0.774576, EPS);
  ASSERT_NEAR(log.slope.value, 5.650037, EPS);
  ASSERT_NEAR(log.bias.value, 1.198875, EPS);
}
