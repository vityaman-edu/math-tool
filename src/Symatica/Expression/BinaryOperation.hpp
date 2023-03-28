#pragma once

#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression {

class BinaryOperation : public Expression {
public:
  BinaryOperation(Expression& left, Expression& right) // NOLINT
      : _left(left), _right(right) {}

  Expression& left() noexcept { return _left; }
  Expression& right() noexcept { return _right; }

private:
  Expression& _left;
  Expression& _right;
};

}
