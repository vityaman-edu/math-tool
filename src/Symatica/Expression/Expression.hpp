#pragma once

#include "Symatica/Core.hpp"
#include <string>

namespace Symatica::Expression {

using Symatica::Core::Ptr;

enum Type {
  BINARY_ADDITION,
  BINARY_SUBTRACTION,
  BINARY_MULTIPLICATION,
  BINARY_DIVISION,
  EXPONENTIATION,
  NEGATION,
  ATOM_VARIABLE,
  ATOM_LITERAL,
};

class Expression {
public:
  [[nodiscard]] virtual Type type() const noexcept = 0;
  [[nodiscard]] virtual std::string asString() const noexcept = 0;
  virtual ~Expression() = default;
};

}
