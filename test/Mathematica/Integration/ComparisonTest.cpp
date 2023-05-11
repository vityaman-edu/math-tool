#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Integration/Cotes.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <utility>

// NOLINTBEGIN(google-build-using-namespace, readability-magic-numbers)
// NOLINTNEXTLINE
TEST(Integration, Sample) {                
  using namespace Mathematica;             
  using namespace Mathematica::Integration;
  using F = double;

  auto interval = Interval<F>(2, 35);
  auto partition = Partition<F>(interval, 1000);
  auto function = [](F x) { return std::sqrt(x); };
  auto expected = 136.16;

  auto rectL = Cotes(trivial0<F>([](auto i) { return i.left(); }), 0);
  auto rectM = Cotes(trivial0<F>([](auto i) { return i.middle(); }), 0);
  auto rectR = Cotes(trivial0<F>([](auto i) { return i.right(); }), 0);
  auto trapeze = Cotes(trivial1<F>(), 1);
  auto simpson = Cotes(trivial2<F>(), 2);
  auto cotes5 = Cotes(trivial5<F>(), 5);

  auto methods = {
      rectL,
      rectM,
      rectR,
      trapeze,
      simpson,
      cotes5
  };

  for (auto method : methods) {
    auto actual = method.areaUnderGraph(function, partition);
    ASSERT_NEAR(expected, actual, 0.1);
  }
}
// NOLINTEND(google-build-using-namespace, readability-magic-numbers)