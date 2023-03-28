#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class Variable : public Expression {
public:
  [[nodiscard]] Type type() const noexcept override {
    return Type::ATOM_VARIABLE;
  }

  [[nodiscard]] Core::Id id() const noexcept { return _id; }

private:
  Core::Id _id;
};

}