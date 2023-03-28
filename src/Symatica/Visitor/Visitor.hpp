#pragma once

#include "Symatica/Expression/BinaryAddition.hpp"
#include "Symatica/Expression/BinaryDivision.hpp"
#include "Symatica/Expression/BinaryMultiplication.hpp"
#include "Symatica/Expression/BinarySubtraction.hpp"
#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Literal.hpp"
#include "Symatica/Expression/Variable.hpp"
#include <type_traits>

namespace Symatica::Visitor {

using Symatica::Expression::BinaryAddition;
using Symatica::Expression::BinaryDivision;
using Symatica::Expression::BinaryMultiplication;
using Symatica::Expression::BinarySubtraction;
using Symatica::Expression::Exponentiation;
using Symatica::Expression::Expression;
using Symatica::Expression::Literal;
using Symatica::Expression::Type;
using Symatica::Expression::Variable;

template <typename R>
class Visitor {
  static_assert(std::is_default_constructible_v<R>);

public:
  virtual R visitBinaryAddition(const BinaryAddition& /*unused*/) {
    return R();
  };

  virtual R visitBinaryDivision(const BinaryDivision& /*unused*/) {
    return R();
  };

  virtual R
  visitBinaryMultiplication(const BinaryMultiplication& /*unused*/) {
    return R();
  };

  virtual R visitBinarySubtraction(const BinarySubtraction& /*unused*/) {
    return R();
  };

  virtual R visitExponentiation(const Exponentiation& /*unused*/) {
    return R();
  };

  virtual R visitLiteral(const Literal& /*unused*/) { return R(); };
  virtual R visitVariable(const Variable& /*unused*/) { return R(); };

  R visitExpression(const Expression& expression) {
    switch (expression.type()) {
    case Type::BINARY_ADDITION:
      return visitBinaryAddition( //
          dynamic_cast<const BinaryAddition&>(expression)
      );
    case Type::BINARY_SUBTRACTION:
      return visitBinarySubtraction( //
          dynamic_cast<const BinarySubtraction&>(expression)
      );
    case Type::BINARY_MULTIPLICATION:
      return visitBinaryMultiplication( //
          dynamic_cast<const BinaryMultiplication&>(expression)
      );
    case Type::BINARY_DIVISION:
      return visitBinaryDivision( //
          dynamic_cast<const BinaryDivision&>(expression)
      );
    case Type::EXPONENTIATION:
      return visitExponentiation( //
          dynamic_cast<const Exponentiation&>(expression)
      );
    case Type::ATOM_VARIABLE:
      return visitVariable( //
          dynamic_cast<const Variable&>(expression)
      );
    case Type::ATOM_LITERAL:
      return visitLiteral( //
          dynamic_cast<const Literal&>(expression)
      );
    }
  }
};

}