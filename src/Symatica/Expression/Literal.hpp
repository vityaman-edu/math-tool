#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"
#include <cmath>
#include <string>

namespace Symatica::Expression {

using Symatica::Core::Number;

class Literal : public Expression {
public:
  explicit Literal(Number value) : _value(value) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::ATOM_LITERAL;
  };

  [[nodiscard]] Number value() const noexcept { return _value; }

  [[nodiscard]] std::string asString() const noexcept override {
    if (value() == static_cast<Core::Integer>(value())) {
      return std::to_string(static_cast<Core::Integer>(value()));
    }
    return std::to_string(value()); // NOLINT
  }

private:
  Number _value;
};

}