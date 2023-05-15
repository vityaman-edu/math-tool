#pragma once

#include "App/Core.hpp"
#include "App/Tool/Base/Runner.hpp"

namespace App::Tool::Interpolator {

enum Mode {
  POINTS,
  FUNCTION,
};

struct Arguments {
  Mode mode;

  static Arguments parseArgs(const Vector<String>& args);
};

class Runner : BaseRunner<Arguments> {
public:
  explicit Runner(Arguments args) : BaseRunner(args) {}

  void run(std::istream& input, std::ostream& output) override;
};

}