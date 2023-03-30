#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Error.hpp"
#include "Symatica/Expression/BinaryAddition.hpp"
#include "Symatica/Expression/BinaryDivision.hpp"
#include "Symatica/Expression/BinaryMultiplication.hpp"
#include "Symatica/Expression/BinaryOperation.hpp"
#include "Symatica/Expression/BinarySubtraction.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Literal.hpp"
#include "Symatica/Expression/Variable.hpp"
#include "Symatica/Visitor/Visitor.hpp"
#include <cmath>
#include <functional>

namespace Symatica::Visitor {

using Symatica::Core::Ptr;
using Symatica::Expression::DSL::operator+; // NOLINT
using Symatica::Expression::DSL::operator-; // NOLINT
using Symatica::Expression::DSL::operator*; // NOLINT
using Symatica::Expression::DSL::operator/; // NOLINT
using Symatica::Expression::BinaryAddition;
using Symatica::Expression::BinaryDivision;
using Symatica::Expression::BinaryMultiplication;
using Symatica::Expression::BinarySubtraction;
using Symatica::Expression::Exponentiation;
using Symatica::Expression::Literal;
using Symatica::Expression::Variable;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::pow;

// TODO: inplace version
class Derivativer : public Visitor<Ptr<Expression>> {
  using R = Ptr<Expression>;

public:
  explicit Derivativer(Core::Id variableId) : _variableId(variableId) {}

  R derivativeOf(const Ptr<Expression>& expression) { return d(expression); }

  R visitBinaryAddition(const Ptr<BinaryAddition>& op) override {
    auto a = op->left();
    auto b = op->right();
    return d(a) + d(b);
  };

  R visitBinaryDivision(const Ptr<BinaryDivision>& op) override {
    auto a = op->left();
    auto b = op->right();
    return (d(a) * b - a * d(b)) / (pow(b, l(2)));
  }

  R visitBinaryMultiplication(const Ptr<BinaryMultiplication>& op) override {
    auto a = op->left();
    auto b = op->right();
    return d(a) * b + a * d(b);
  }

  R visitBinarySubtraction(const Ptr<BinarySubtraction>& op) override {
    auto a = op->left();
    auto b = op->right();
    return d(a) - d(b);
  }

  R visitExponentiation(const Ptr<Exponentiation>& op) override {
    auto a = op->left();
    auto b = op->right();
    if (b->type() != Type::ATOM_LITERAL) {
      throw Error::UnsuppotedFeature(
          "only f(x) ^ n, where n = const is supported"
      );
    }
    auto power = Core::castPtr<Literal>(b);
    return (power - l(1)) * a * derivativeOf(a);
  }

  R visitNegation(const Ptr<Negation>& operation) override {
    return l(-1) * d(operation->child());
  }

  R visitLiteral(const Ptr<Literal>& /*literal*/) override { return l(0); }

  R visitVariable(const Ptr<Variable>& variable) override {
    if (variable->id() == _variableId) {
      return l(1);
    }
    return l(0);
  }

private:
  R d(const Ptr<Expression>& expression) {
    return this->visitExpression(expression);
  }

  Core::Id _variableId;
};

}