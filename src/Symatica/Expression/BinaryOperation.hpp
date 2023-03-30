#pragma once

#include "Symatica/Expression/Expression.hpp"
#include <array>
#include <string>

namespace Symatica::Expression {

class BinaryOperation : public Expression {
public:
  explicit BinaryOperation(
      const Ptr<Expression>& left, // NOLINT
      const Ptr<Expression>& right // NOLINT
  )
      : _left(left), _right(right) {}

  [[nodiscard]] Ptr<Expression> left() const noexcept {
    return _left; //
  }

  [[nodiscard]] Ptr<Expression> right() const noexcept {
    return _right;
  }

  [[nodiscard]] std::string asString() const noexcept override {
    return "("                            //
           + left()->asString()           //
           + " " + symbolOf(type()) + " " //
           + right()->asString()          //
           + ")";
  }

private:
  static std::string symbolOf(Type type) noexcept {
    switch (type) {
    case BINARY_SUBTRACTION:
      return "-";
    case BINARY_MULTIPLICATION:
      return "*";
    case BINARY_ADDITION:
      return "+";
    case BINARY_DIVISION:
      return "/";
    case EXPONENTIATION:
      return "^";
    default:
      return "?";
    }
  }

  Ptr<Expression> _left;
  Ptr<Expression> _right;
};

}
