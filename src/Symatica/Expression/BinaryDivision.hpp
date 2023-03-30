#pragma once

#include "Symatica/Expression/BinaryOperation.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class BinaryDivision : public BinaryOperation {
public:
  explicit BinaryDivision(
      const Ptr<Expression>& left, //
      const Ptr<Expression>& right
  )
      : BinaryOperation(left, right) {}

  [[nodiscard]] Type type() const noexcept override {
    return Type::BINARY_DIVISION;
  };
};

}