#pragma once

#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/UnaryOperation.hpp"

namespace Symatica::Expression {

class Negation : public UnaryOperation {
public:
  explicit Negation(const Ptr<Expression>& child)
      : UnaryOperation(child) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::NEGATION;
  };
};

}