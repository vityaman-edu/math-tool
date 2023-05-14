#pragma once

#include "App/Tool/Base/Runner.hpp"
#include "App/Core.hpp"

namespace App::Tool::Approx {

struct Arguments {
  static Arguments parseArgs(const Vector<String>& args);
};

class Runner : BaseRunner<Arguments> {
public:
  explicit Runner(Arguments args) : BaseRunner(args) {}

  void run(std::istream &input, std::ostream &output) override;
};

}