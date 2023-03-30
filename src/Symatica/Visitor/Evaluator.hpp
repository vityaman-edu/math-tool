#pragma once

#include "Symatica/Expression/BinaryAddition.hpp"
#include "Symatica/Expression/BinaryDivision.hpp"
#include "Symatica/Expression/BinaryMultiplication.hpp"
#include "Symatica/Expression/BinaryOperation.hpp"
#include "Symatica/Expression/BinarySubtraction.hpp"
#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Literal.hpp"
#include "Symatica/Expression/Variable.hpp"
#include "Symatica/Symbol/Table.hpp"
#include "Symatica/Visitor/Visitor.hpp"
#include <cmath>
#include <functional>

namespace Symatica::Visitor {

using Symatica::Core::Ptr;
using Symatica::Expression::BinaryAddition;
using Symatica::Expression::BinaryDivision;
using Symatica::Expression::BinaryMultiplication;
using Symatica::Expression::BinaryOperation;
using Symatica::Expression::BinarySubtraction;
using Symatica::Expression::Exponentiation;
using Symatica::Expression::Literal;
using Symatica::Expression::Variable;

template <typename R>
class Evaluator : public Visitor<R> {
public:
  explicit Evaluator(Symbol::Table& table) : _table(table) {}

  R valueOf(const Ptr<Expression>& expression) {
    return this->visitExpression(expression);
  }

  R visitBinaryAddition(const Ptr<BinaryAddition>& operation) override {
    return visitBinaryOperation(
        operation, [](R a, R b) { return a + b; } // NOLINT
    );
  };

  R visitBinaryDivision(const Ptr<BinaryDivision>& operation) override {
    // TODO: FIXME: throw Division by zero error
    return visitBinaryOperation(
        operation, [](R a, R b) { return a / b; } // NOLINT
    );
  }

  R visitBinaryMultiplication(const Ptr<BinaryMultiplication>& operation
  ) override {
    return visitBinaryOperation(
        operation, [](R a, R b) { return a * b; } // NOLINT
    );
  }

  R visitBinarySubtraction(const Ptr<BinarySubtraction>& operation) override {
    return visitBinaryOperation(
        operation, [](R a, R b) { return a - b; } // NOLINT
    );
  }

  R visitExponentiation(const Ptr<Exponentiation>& operation) override {
    return visitBinaryOperation(
        operation, [](R a, R b) { return std::pow(a, b); } // NOLINT
    );
  }

  R visitNegation(const Ptr<Negation>& operation) override {
    return -1 * valueOf(operation->child());
  }

  R visitLiteral(const Ptr<Literal>& literal) override {
    return literal->value();
  }

  R visitVariable(const Ptr<Variable>& variable) override {
    return valueOf(_table.get(variable->id()));
  }

private:
  using combinator = std::function<R(R, R)>;
  R visitBinaryOperation(
      const Ptr<BinaryOperation>& op, combinator comb // NOLINT
  ) {
    return comb(valueOf(op->left()), valueOf(op->right()));
  }

  Symbol::Table& _table;
};

}