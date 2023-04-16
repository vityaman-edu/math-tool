#pragma once

#include <istream>

namespace App::Tool {

template <typename Arguments>
class BaseRunner {
public:
  explicit BaseRunner(Arguments args) : _args(std::move(args)) {}
  virtual ~BaseRunner() = default;

  virtual void run(std::istream& input, std::ostream& output) = 0;

  Arguments args() const noexcept {
    return _args;
  }
  
private:
  Arguments _args;
};

}
