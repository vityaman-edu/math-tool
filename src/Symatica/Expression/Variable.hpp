#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"
#include <string>

namespace Symatica::Expression {

using Symatica::Core::Id;

class Variable : public Expression {
public:
  explicit Variable(Id id) : _id(id) {} // NOLINT

  [[nodiscard]] Type type() const noexcept override {
    return Type::ATOM_VARIABLE;
  }

  [[nodiscard]] Id id() const noexcept { return _id; }

  [[nodiscard]] std::string asString() const noexcept override {
    if (_id == 1) {
      return "x";
    }
    return "$" + std::to_string(_id);
  }

private:
  Id _id;
};

}