#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/FunctionAnalysis.hpp"
#include "Mathematica/Equation/Solution/Method/HalfDivision.hpp"
#include "Mathematica/Equation/Solution/Method/Interval.hpp"
#include "Mathematica/Equation/Solution/Method/Newton.hpp"
#include "Mathematica/Equation/Solution/Method/SimpleIteration.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace Mathematica;                // NOLINT
using namespace Equation::Solution::Method; // NOLINT

// TODO: disable some checks only in tests
TEST(ComparisonTest, Sample) { // NOLINT
  constexpr auto EPS = 0.001;
  constexpr auto FIT = 1;
  std::cout << std::setprecision(3);

  const auto f = [](Real x) {
    return -0.38 * x * x * x // NOLINT
           - 3.42 * x * x    // NOLINT
           + 2.51 * x        // NOLINT
           + 8.75;           // NOLINT
  };

  const auto df = [](Real x) {
    return -0.38 * 3 * x * x // NOLINT
           - 3.42 * 2 * x    // NOLINT
           + 2.51;           // NOLINT
  };

  const auto ddf = [](Real x) {
    return -0.38 * 3 * 2 * x // NOLINT
           - 3.42 * 2;       // NOLINT
  };

  const auto mainInterval = Interval<Real>(-10, 5);
  const auto scopes = std::vector<Interval<Real>>({
      Interval<Real>(-10, -5),
      Interval<Real>(-5, 0),
      Interval<Real>(0, 5),
  });

  const auto interestingScopes
      = rootSeparabilityIntervals<Real>(mainInterval, FIT, f);
  ASSERT_EQ(interestingScopes.size(), 3);

  const auto results = std::vector<Real>({
      -9.44129,
      -1.35656,
      1.79785,
  });

  for (auto result : results) {
    ASSERT_NE(
        (std::find_if(
            interestingScopes.begin(),
            interestingScopes.end(),
            [result](const Interval<Real>& interval) {
              return interval.contains(result);
            }
        )),
        interestingScopes.end()
    );
  }

  auto halfDivisionTracer = HalfDivision::MarkdownTableTracer<Real>(std::cout);
  auto halfDivision = HalfDivision::Executor<Real, HalfDivision::MarkdownTableTracer<Real>>(
      EPS, halfDivisionTracer
  );

  auto newtonTracer = Newton::MarkdownTableTracer<Real>(std::cout);
  auto newton = Newton::Executor<Real, Newton::MarkdownTableTracer<Real>>(EPS, newtonTracer);

  auto simpleIterationTracer
      = SimpleIteration::MarkdownTableTracer<Real>(std::cout);
  auto simpleIteration
      = SimpleIteration::Executor<Real, SimpleIteration::MarkdownTableTracer<Real>>(
          EPS, simpleIterationTracer
      );

  for (std::size_t i = 0; i < interestingScopes.size(); i++) {
    const auto& scope = interestingScopes[i];
    const auto expectedResult = results[i];

    std::cout << "[INFO]: Picked scope is " + scope.asString() << std::endl;

    if (bool halfDivisionAccepts = true) {
      std::cout << "[INFO] (HalfDivision): OK" << std::endl;
      const auto actualResult //
          = halfDivision.findSomeRoot(scope, f);
      ASSERT_NEAR(actualResult, expectedResult, EPS);
    }

    if (newton.accepts(scope, f, df, ddf)) {
      std::cout << "[INFO] (Newton): OK" << std::endl;
      const auto actualResult //
          = newton.findSomeRoot(scope, f, df, ddf);
      ASSERT_NEAR(actualResult, expectedResult, EPS);
    } else {
      std::cout << "[INFO] (Newton) CAN NOT:" << std::endl;
    }

    auto dphi = SimpleIteration::buildDPhiFrom<Real>(scope, df);
    if (simpleIteration.accepts(scope, dphi)) {
      std::cout << "[INFO] (SimpleIteration): OK" << std::endl;
      const auto phi = SimpleIteration::buildPhiFrom<Real>(scope, f, df);
      const auto actualResult //
          = simpleIteration.findSomeRoot(scope.left(), phi);
      ASSERT_NEAR(actualResult, expectedResult, EPS);
    } else {
      std::cout << "[INFO] (SimpleIteration) CAN NOT:" << std::endl;
    }
  }
}
