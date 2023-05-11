#pragma once

#include <utility>

#include "App/Core.hpp"
#include "App/Tool/Base/Runner.hpp"

namespace App::Tool::Integrator {

enum Method {
  RECTANGLE_L,
  RECTANGLE_M,
  RECTANGLE_R,
  TRAPEZE,
  SIMPSON,
  COTES_5,
};

struct Arguments {
  Method method;
  Scope scope;
  Real accuracy;

  static Arguments parseArgs(const Vector<String>& args);
};

class Runner : public BaseRunner<Arguments> {
public:
  explicit Runner(Arguments args) : BaseRunner(std::move(args)) {}
  ~Runner() override = default;

  void run(std::istream& input, std::ostream& output) override;
};

}