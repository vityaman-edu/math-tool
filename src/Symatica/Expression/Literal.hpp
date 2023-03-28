#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class Literal : public Expression {
public:
  [[nodiscard]] Type type() const noexcept override {
    return Type::ATOM_LITERAL;
  };

  [[nodiscard]] Core::F value() const noexcept { return _value; }

private:
  Core::F _value;
};

}