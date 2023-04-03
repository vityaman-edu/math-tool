#include "Mathematica/Equation/Solution/Method/HalfDivision.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/FunctionAnalysis.hpp"
#include "Mathematica/Equation/Solution/Method/Interval.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;                // NOLINT
using namespace Equation::Solution::Method; // NOLINT

// TODO: disable some checks only in tests
TEST(HalfDivisionTest, Sample) {
  constexpr auto EPS = 0.00001;
  constexpr auto FIT = 0.1;

  const auto sample = [](Real x) {
    return -0.38 * x * x * x // NOLINT
           - 3.42 * x * x    // NOLINT
           + 2.51 * x        // NOLINT
           + 8.75;           // NOLINT
  };

  const auto mainInterval = Interval<Real>(-10, 5);
  const auto intervals = std::vector<Interval<Real>>({
      Interval<Real>(-10, -5),
      Interval<Real>(-5, 0),
      Interval<Real>(0, 5),
  });

  const auto interestingIntervals
      = rootSeparabilityIntervals<Real>(mainInterval, FIT, sample);
  ASSERT_EQ(interestingIntervals.size(), 3);

  const auto results = std::vector<Real>({
      -9.44129,
      -1.35656,
      1.79785,
  });

  for (auto result : results) {
    ASSERT_NE(
        (std::find_if(
            interestingIntervals.begin(),
            interestingIntervals.end(),
            [result](const Interval<Real>& interval) {
              return interval.contains(result);
            }
        )),
        interestingIntervals.end()
    );
  }

  auto tracer = HalfDivision::MardownTableTracer<Real>(std::cout);
  auto method = HalfDivision::Executor<Real, typeof(tracer)>(EPS, tracer);

  for (std::size_t i = 0; i < intervals.size(); i++) {
    const auto& interval = intervals[i];
    const auto expected_result = results[i];
    const auto actual_result = method.findSomeRoot(interval, sample);
    ASSERT_NEAR(actual_result, expected_result, EPS);
  }
}
