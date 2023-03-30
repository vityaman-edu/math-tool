#pragma once

#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class Negation : public Expression {
public:
  explicit Negation(const Expression& child) : _child(child) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::NEGATION;
  };

  const Expression& child() noexcept { return _child; }

private:
  const Expression& _child;
};

}