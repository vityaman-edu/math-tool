#pragma once

#include <istream>
#include <ostream>
#include <utility>

#include "App/Core.hpp"

namespace App::Tool::EquationSolver {

constexpr auto REQUIRED_ARGS_SIZE = 6;

enum Method {
  HALF_DIVISION,
  NEWTON,
  SIMPLE_ITERATION,
};

struct Arguments { // NOLINT
  Method method;
  Scope scope;
  Real accuracy;

  static Arguments parseArgs(const Vector<String>& args);
};

class Runner {
public:
  explicit Runner(Arguments args) : args(std::move(args)) {}

  void run(std::istream& input, std::ostream& output) const;

private:
  Arguments args;
};

}