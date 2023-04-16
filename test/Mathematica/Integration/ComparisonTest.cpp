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

  auto rectL = Cotes(trivial0<F>([](auto i) { return i.left(); }));
  auto rectM = Cotes(trivial0<F>([](auto i) { return i.middle(); }));
  auto rectR = Cotes(trivial0<F>([](auto i) { return i.right(); }));
  auto trapeze = Cotes(trivial1<F>());
  auto simpson = Cotes(trivial2<F>());
  auto cotes5 = Cotes(trivial5<F>());

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