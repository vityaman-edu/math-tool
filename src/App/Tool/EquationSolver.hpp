#pragma once

#include <istream>
#include <ostream>
#include <utility>

#include "App/Core.hpp"
#include "App/Tool/Base/Runner.hpp"

namespace App::Tool::EquationSolver {

constexpr auto REQUIRED_ARGS_SIZE = 6;

enum Method {
  HALF_DIVISION,
  NEWTON,
  SIMPLE_ITERATION,
};

struct Arguments {
  Method method;
  Scope scope;
  Real accuracy;

  static Arguments parseArgs(const Vector<String>& args);
};

class Runner : BaseRunner<Arguments> {
public:
  explicit Runner(Arguments args) : BaseRunner(std::move(args)) {}

  void run(std::istream &input, std::ostream &output) override;
};

}