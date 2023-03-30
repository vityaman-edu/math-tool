#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"
#include <string>

namespace Symatica::Expression {

using Symatica::Core::Id;

class Variable : public Expression {
public:
  [[nodiscard]] Type type() const noexcept override {
    return Type::ATOM_VARIABLE;
  }

  [[nodiscard]] Id id() const noexcept { return _id; }

  [[nodiscard]] std::string asString() const noexcept override {
    return "$" + std::to_string(_id);
  }

private:
  Id _id;
};

}