#pragma once

#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/gauss/method.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace tool::lineqsys {

using math::eq::lin::sys::lineqsys;
using math::eq::lin::sys::solve::gauss::result;
using math::eq::lin::sys::solve::gauss::solve;

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
  // TODO: det sign from swaps inside gauss
  out << "det: " << det << '\n';
  out << "triangle matrix:" << '\n';
  out << result.triangle;
  out << "result: " << result.value << '\n';
  out << "error: " << result.error << '\n';
}

template <typename F, size_t N>
void impl(std::istream& file, std::ostream& output) {
  auto system = parse_system_from<F, N>(file);
  auto result = solve(system);
  report(output, result);
}

void run(
    std::istream& in, // NOLINT
    std::ostream& out,
    const std::vector<std::string>& args
);

}
