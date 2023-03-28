#pragma once

#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class BinaryOperation : public Expression {
public:
  BinaryOperation(
      const Expression& left, const Expression& right // NOLINT
  )
      : _left(left), _right(right) {}

  [[nodiscard]] const Expression& left() const noexcept { return _left; }
  [[nodiscard]] const Expression& right() const noexcept { return _right; }

  [[nodiscard]] std::string asString() const noexcept override {
    char symbol = '?';
    switch (type()) {
    case BINARY_SUBTRACTION:
      symbol = '-';
      break;
    case BINARY_MULTIPLICATION:
      symbol = '*';
      break;
    case BINARY_ADDITION:
      symbol = '+';
      break;
    case BINARY_DIVISION:
      symbol = '/';
      break;
    case EXPONENTIATION:
      symbol = '^';
    default:
      symbol = '!';
    }
    return "("                  //
           + left().asString()  //
           + " " + symbol + " " //
           + right().asString() //
           + ")";
  }

private:
  const Expression& _left;
  const Expression& _right;
};

}
