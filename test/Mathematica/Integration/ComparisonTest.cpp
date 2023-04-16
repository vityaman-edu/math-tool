#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Integration/Rectangle.hpp"
#include <cmath>
#include <gtest/gtest.h>

TEST(Integration, Sample) { // NOLINT
  using Mathematica::Interval;
  using Mathematica::Partition;
  using namespace Mathematica::Integration; // NOLINT
  using F = double;

  auto interval = Interval<F>(2, 35);            // NOLINT
  auto partition = Partition<F>(interval, 1000); // NOLINT

  auto method = Rectangle::Method<F>([](const Interval<F>& interval) {
    return interval.middle();
  });

  auto function = [](F x) {
    return std::sqrt(x);
  };

  auto expectedResult = 136.16; // NOLINT
  auto actualResult = method.areaUnderGraph(partition, function);
  ASSERT_NEAR(expectedResult, actualResult, 0.01);
}