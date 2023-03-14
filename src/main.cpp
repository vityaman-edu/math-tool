#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/gauss/method.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  // clang-format off
  math::eq::lin::sys::lineqsys<double, 3> sys = {
    .a = math::linal::matrix<double, 3, 3>({{
      { 2, -1,   1 },   // NOLINT
      { 3,  5,  -2 },   // NOLINT
      { 1, -4,  10 }    // NOLINT
    }}),
    .b = math::linal::vector<double, 3>(
      {-3, 1, 0}  // NOLINT
    )
  };
  // clang-format on

  try {
    auto result = math::eq::lin::sys::solve::gauss::solve(sys);
    std::cout << result.triangle << std::endl;
    std::cout << result.value << std::endl;
  } catch (std::invalid_argument& e) {
    std::cout << "error: " << e.what() << std::endl;
  }

  return 0;
}
