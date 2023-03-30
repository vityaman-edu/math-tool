#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/BinaryAddition.hpp"
#include "Symatica/Expression/BinaryDivision.hpp"
#include "Symatica/Expression/BinaryMultiplication.hpp"
#include "Symatica/Expression/BinarySubtraction.hpp"
#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Literal.hpp"
#include "Symatica/Expression/Negation.hpp"
#include "Symatica/Expression/Variable.hpp"
#include <memory>
#include <type_traits>

namespace Symatica::Visitor {

using Symatica::Core::castPtr;
using Symatica::Core::Ptr;
using Symatica::Expression::BinaryAddition;
using Symatica::Expression::BinaryDivision;
using Symatica::Expression::BinaryMultiplication;
using Symatica::Expression::BinarySubtraction;
using Symatica::Expression::Exponentiation;
using Symatica::Expression::Expression;
using Symatica::Expression::Literal;
using Symatica::Expression::Negation;
using Symatica::Expression::Type;
using Symatica::Expression::Variable;

template <typename R>
class Visitor {
public:
  virtual R visitBinaryAddition(const Ptr<BinaryAddition>&) = 0;
  virtual R visitBinaryDivision(const Ptr<BinaryDivision>&) = 0;
  virtual R visitBinaryMultiplication(const Ptr<BinaryMultiplication>&) = 0;
  virtual R visitBinarySubtraction(const Ptr<BinarySubtraction>&) = 0;
  virtual R visitExponentiation(const Ptr<Exponentiation>&) = 0;
  virtual R visitNegation(const Ptr<Negation>&) = 0;
  virtual R visitLiteral(const Ptr<Literal>&) = 0;
  virtual R visitVariable(const Ptr<Variable>&) = 0;

  R visitExpression(const Ptr<Expression>& e) { // NOLINT
    switch (e->type()) {
    case Type::BINARY_ADDITION:
      return visitBinaryAddition(castPtr<BinaryAddition>(e));
    case Type::BINARY_SUBTRACTION:
      return visitBinarySubtraction(castPtr<BinarySubtraction>(e));
    case Type::BINARY_MULTIPLICATION:
      return visitBinaryMultiplication(castPtr<BinaryMultiplication>(e));
    case Type::BINARY_DIVISION:
      return visitBinaryDivision(castPtr<BinaryDivision>(e));
    case Type::EXPONENTIATION:
      return visitExponentiation(castPtr<Exponentiation>(e));
    case Type::NEGATION:
      return visitNegation(castPtr<Negation>(e));
    case Type::ATOM_VARIABLE:
      return visitVariable(castPtr<Variable>(e));
    case Type::ATOM_LITERAL:
      return visitLiteral(castPtr<Literal>(e));
    }
  }
};

}