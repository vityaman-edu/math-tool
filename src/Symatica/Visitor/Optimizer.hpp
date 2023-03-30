#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Expression/Literal.hpp"
#include "Symatica/Visitor/Visitor.hpp"
#include <cmath>
#include <functional>
#include <numeric>
#include <regex.h>

#define MATCH(VAR, TYPE, CLASS, CASTED)                                        \
  Core::Ptr<CLASS>(CASTED); /* NOLINT */                                       \
  if (((VAR)->type() == (TYPE))                                                \
      && ((CASTED) = Core::castPtr<CLASS>((VAR)))) /* NOLINT */

namespace Symatica::Visitor {

using Symatica::Core::Integer;
using Symatica::Core::Ptr;
using Symatica::Expression::DSL::operator+; // NOLINT
using Symatica::Expression::DSL::operator-; // NOLINT
using Symatica::Expression::DSL::operator*; // NOLINT
using Symatica::Expression::DSL::operator/; // NOLINT
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::pow;

// TODO: add rational numbers a/b

class Optimizer : public Visitor<Ptr<Expression>> {
  using R = Ptr<Expression>;

public:
  R optimized(const Ptr<Expression>& expression) {
    return this->visitExpression(expression);
  }

  R visitBinaryAddition(const Ptr<BinaryAddition>& op) override {
    // TODO: write match
    auto optimized_left = optimized(op->left());
    auto optimized_right = optimized(op->right());
    MATCH(optimized_left, Type::ATOM_LITERAL, Literal, left_lit) {
      if (left_lit->value() == 0) {
        return optimized_right;
      }
    }
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, right_lit) {
      if (right_lit->value() == 0) {
        return optimized_left;
      }
    }
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, right) {
      MATCH(optimized_left, Type::ATOM_LITERAL, Literal, left) {
        return l(right->value() + left->value());
      }
    }
    // TODO: f(x) + f(x) = 2 * f(x), it requires equals !!!
    // not only in this optimization, but also
    // f(x) * f(x) = pow(f(x), 2)
    // f(x) / f(x) = 1 ??? case f(x) = 0
    // f(x) - f(x) = 0
    return optimized_left + optimized_right;
  }

  R visitBinaryDivision(const Ptr<BinaryDivision>& op) override {
    auto optimized_left = optimized(op->left());
    auto optimized_right = optimized(op->right());
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, lit_numerator) {
      MATCH(optimized_left, Type::ATOM_LITERAL, Literal, lit_denominator) {
        auto numerator_value = lit_numerator->value();
        auto denominator_value = lit_denominator->value();
        auto numerator_value_int = static_cast<Integer>(numerator_value);
        auto denominator_value_int = static_cast<Integer>(denominator_value);
        if (numerator_value_int == numerator_value
            && denominator_value_int == denominator_value) {
          numerator_value_int
              /= std::gcd(numerator_value_int, denominator_value_int);
          denominator_value_int
              /= std::gcd(numerator_value_int, denominator_value_int);
          return l(numerator_value_int) / l(denominator_value_int);
        }
        // FIXME: division by zero
        return l(numerator_value / denominator_value);
      }
    }
    // TODO: (2 * x / 4) == (x / 2)
    return optimized_left / optimized_right;
  }

  R visitBinaryMultiplication(const Ptr<BinaryMultiplication>& op) override {
    auto optimized_left = optimized(op->left());
    auto optimized_right = optimized(op->right());
    MATCH(optimized_left, Type::ATOM_LITERAL, Literal, lit_left) {
      if (lit_left->value() == 0) {
        return l(0);
      }
      if (lit_left->value() == 1) {
        return optimized_right;
      }
    }
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, lit_right) {
      if (lit_right->value() == 0) {
        return l(0);
      }
      if (lit_right->value() == 1) {
        return optimized_left;
      }
    }
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, lit_left_) {
      MATCH(optimized_left, Type::ATOM_LITERAL, Literal, lit_right_) {
        return l(lit_left_->value() * lit_right_->value());
      }
    }
    return optimized_left * optimized_right;
  }

  R visitBinarySubtraction(const Ptr<BinarySubtraction>& op) override {
    auto optimized_left = optimized(op->left());
    auto optimized_right = optimized(op->right());
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, lit_left_) {
      MATCH(optimized_left, Type::ATOM_LITERAL, Literal, lit_right_) {
        return l(lit_left_->value() - lit_right_->value());
      }
    }
    MATCH(optimized_left, Type::ATOM_LITERAL, Literal, lit_left) {
      if (lit_left->value() == 0) {
        return -optimized_right;
      }
    }
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, lit_right) {
      if (lit_right->value() == 0) {
        return optimized_left;
      }
    }
    return optimized_left - optimized_right;
  }

  R visitExponentiation(const Ptr<Exponentiation>& op) override {
    auto optimized_left = optimized(op->left());
    auto optimized_right = optimized(op->right());
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, lit_right) {
      if (lit_right->value() == 1) {
        return optimized_left;
      }
    }
    MATCH(optimized_left, Type::ATOM_LITERAL, Literal, lit_left) {
      if (lit_left->value() == 1) {
        return optimized_left;
      }
    }
    MATCH(optimized_right, Type::ATOM_LITERAL, Literal, lit_left_) {
      MATCH(optimized_left, Type::ATOM_LITERAL, Literal, lit_right_) {
        return l(std::pow(lit_left_->value(), lit_right_->value()));
      }
    }
    return pow(optimized_left, optimized_right);
  }

  R visitNegation(const Ptr<Negation>& op) override {
    auto optimized_child = op->child();
    MATCH(optimized_child, Type::ATOM_LITERAL, Literal, lit_child) {
      return l(-lit_child->value());
    }
    return optimized_child;
  }

  R visitLiteral(const Ptr<Literal>& literal) override { return literal; }

  R visitVariable(const Ptr<Variable>& variable) override { return variable; }

  virtual ~Optimizer() = default;
};

}