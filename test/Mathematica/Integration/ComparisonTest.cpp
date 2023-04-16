#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Integration/Rectangle.hpp"
#include "Mathematica/Integration/Trapeze.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <utility>

TEST(Integration, Sample) { // NOLINT
  using Mathematica::Function;
  using Mathematica::Interval;
  using Mathematica::Partition;
  using namespace Mathematica::Integration; // NOLINT
  using F = double;

  auto interval = Interval<F>(2, 35);            // NOLINT
  auto partition = Partition<F>(interval, 1000); // NOLINT

  auto function = [](F x) { return std::sqrt(x); };

  auto rectangle = Rectangle::Method<F>([](const auto& interval) {
    return interval.middle();
  });

  auto expectedResult = 136.16; // NOLINT
  auto actualRectangleResult = rectangle.areaUnderGraph(function, partition);
  auto actualTrapezeResult = Trapeze::AreaUnderGraph<F>(function, partition);
  ASSERT_NEAR(expectedResult, actualRectangleResult, 0.01);
  ASSERT_NEAR(expectedResult, actualTrapezeResult, 0.01);
}