#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/gauss/method.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>

using math::eq::lin::sys::lineqsys;
using math::eq::lin::sys::solve::gauss::result;
using math::eq::lin::sys::solve::gauss::solve;

void usage() {
  std::cout << "usage: math-tool <filepath>" << std::endl;
}

template <typename F, size_t N>
lineqsys<F, N> parse_system_from(std::istream& input) {
  lineqsys<F, N> sys; // NOLINT: init in for-loop
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      input >> sys.a[i][j];
    }
    input >> sys.b[i];
  }
  return sys;
}

template <typename F, size_t N>
void report(std::ostream& out, const result<F, N>& result) {
  F det = 1;
  for (size_t i = 0; i < N; i++) {
    det *= result.triangle.a[i][i];
  }

  out << "lineqsys gauss method results report" << '\n';
  // TODO: det sign from swaps inside gaus
  out << "det: " << det << '\n';
  out << "triangle matrix:" << '\n';
  out << result.triangle;
  out << "result: " << result.value << '\n';
  out << "error: " << result.error << '\n';
}

int main(int argc, char* argv[]) {
  using F = float;
  constexpr size_t N = 3; // NOLINT

  if (argc != 2) {
    usage();
  }

  auto filepath = std::string(argv[1]); // NOLINT

  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "error: can't open file " << filepath << std::endl;
    return 1;
  }

  try {
    auto system = parse_system_from<F, N>(file);
    auto result = solve(system);
    report(std::cout, result);
  } catch (std::invalid_argument& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
