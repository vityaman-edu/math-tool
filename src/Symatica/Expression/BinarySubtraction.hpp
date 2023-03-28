#pragma once

#include "Symatica/Expression/BinaryOperation.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class BinarySubtraction : public BinaryOperation {
public:
  BinarySubtraction(const Expression& left, const Expression& right)
      : BinaryOperation(left, right) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::BINARY_SUBTRACTION;
  };
};

}