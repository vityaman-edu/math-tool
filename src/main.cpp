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
  math::eq::lin::sys::lineqsys<float, 3> sys = {
    .a = math::linal::matrix<float, 3, 3>({{
      {2, 2, 10},   // NOLINT
      {2, 10, 1},   // NOLINT
      {10, 1, 1}    // NOLINT
    }}),
    .b = math::linal::vector<float, 3>(
      {14, 13, 12}  // NOLINT
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
