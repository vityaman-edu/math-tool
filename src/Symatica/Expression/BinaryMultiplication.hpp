#pragma once

#include "Symatica/Expression/BinaryOperation.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class BinaryMultiplication : public BinaryOperation {
public:
  BinaryMultiplication(const Expression& left, const Expression& right)
      : BinaryOperation(left, right) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::BINARY_MULTIPLICATION;
  };
};

}