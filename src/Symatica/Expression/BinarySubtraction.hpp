#pragma once

#include "Symatica/Expression/BinaryOperation.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class BinarySubtraction : public BinaryOperation {
public:
  explicit BinarySubtraction(
      const Ptr<Expression>& left, const Ptr<Expression>& right
  )
      : BinaryOperation(left, right) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::BINARY_SUBTRACTION;
  };
};

}