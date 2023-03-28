#include "math/eq/solve/function.hpp"
#include "math/eq/solve/half_division.hpp"
#include "math/eq/solve/interval.hpp"
#include "math/eq/solve/method.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <iterator>
#include <vector>

TEST(EqSolveTest, CompareAllOnSample) { // NOLINT
  constexpr auto EPS = 0.00001;
  using F = float;
  using namespace math::eq::solve; // NOLINT

  const auto f = function<F>([](F x) { // NOLINT
    return -0.38 * x * x * x           // NOLINT
           - 3.42 * x * x              // NOLINT
           + 2.51 * x                  // NOLINT
           + 8.75;                     // NOLINT
  });

  const auto intervals = std::vector<interval<F>>({
      interval<F>(-10, -5),
      interval<F>(-5, 0),
      interval<F>(0, 5),
  });

  const auto results = std::vector<F>({
      -9.44129,
      -1.35656,
      1.79785,
  });

  const auto tabulated_intervals
      = f.tabulate(interval<F>(-10, 5), 100);
  ASSERT_EQ(tabulated_intervals.size(), 3);
  for (auto result : results) {
    ASSERT_NE((
        std::find_if(
            tabulated_intervals.begin(),
            tabulated_intervals.end(),
            [result](const interval<F>& interval) {
              return interval.contains(result);
            }
        )),
        tabulated_intervals.end()
    );
  }

  auto half_division_tracer = half_division::empty_tracer<F>();
  auto half_division_method
      = half_division::method<F, typeof(half_division_tracer)>(
          EPS, half_division_tracer
      );

  const auto methods = std::vector<method<F>*>({
      &half_division_method,
  });

  for (std::size_t i = 0; i < intervals.size(); i++) {
    const auto& interval = intervals[i];
    const auto expected_result = results[i];
    for (auto* method : methods) {
      const auto actual_result = method->find_some_root(interval, f);
      ASSERT_NEAR(actual_result, expected_result, EPS);
    }
  }
}
