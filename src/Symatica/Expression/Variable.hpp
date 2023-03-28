#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

using Symatica::Core::Id;

class Variable : public Expression {
public:
  [[nodiscard]] Type type() const noexcept override {
    return Type::ATOM_VARIABLE;
  }

  [[nodiscard]] Id id() const noexcept { return _id; }

private:
  Id _id;
};

}