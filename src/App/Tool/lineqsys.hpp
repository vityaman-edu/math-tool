#pragma once

#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Algebra/Linear/Eq/GaussSolver.hpp"
#include "Mathematica/Algebra/Linear/Eq/System.hpp"
#include "Mathematica/Algebra/Linear/IO.hpp"

#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace tool::lineqsys {

using Mathematica::Abstract::Float;
using Mathematica::Algebra::Linear::Eq::GaussSolver;
using Mathematica::Algebra::Linear::Eq::Solution;
using Mathematica::Algebra::Linear::Eq::System;
using Mathematica::Algebra::Linear::IO::operator<<;

template <typename F, size_t N>
System<Float<F>, N> parseSystem(std::istream& input) {
  System<Float<F>, N> sys; // NOLINT: init in for-loop
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      input >> sys.a[i][j].value;
    }
    input >> sys.b[i].value;
  }
  return sys;
}

template <typename F, size_t N>
void report(std::ostream& out, const Solution<Float<F>, N>& result) {
  out << "lineqsys gauss method results report" << '\n';
  out << "result: " << result.value << '\n';
  out << "error:  " << result.error << '\n';
}

template <typename F, size_t N>
void impl(std::istream& file, std::ostream& output) {
  auto system = parseSystem<F, N>(file);
  auto gauss = GaussSolver<Float<F>, N>();
  auto result = gauss.solve(system);
  report(output, result);
}

void run(
    std::istream& in, //
    std::ostream& out,
    const std::vector<std::string>& args
);

}
