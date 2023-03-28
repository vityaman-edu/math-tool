#pragma once

#include "Symatica/Expression/BinaryOperation.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class Exponentiation : public BinaryOperation {
public:
  Exponentiation(Expression& left, Expression& right)
      : BinaryOperation(left, right) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::EXPONENTIATION;
  };
};

}