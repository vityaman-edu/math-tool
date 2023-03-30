#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Functions.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include <exception>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using Symatica::Expression::DSL::operator*;
using Symatica::Expression::DSL::operator+;
using Symatica::Expression::DSL::operator/;
using Symatica::Expression::DSL::operator-;
using Symatica::Core::Number;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::sqare;
using Symatica::Symbol::TreeTable;
using Symatica::Visitor::Evaluator;

TEST(TestEvaluator, OnlyLiterals) { // NOLINT
  auto table = TreeTable({});
  auto eval = Evaluator<Number>(table);
  ASSERT_EQ(eval.valueOf(l(2)), 2);
  ASSERT_EQ(eval.valueOf(l(2) + l(2)), 4);
  ASSERT_EQ(eval.valueOf(l(2) - l(2)), 0);
  ASSERT_EQ(eval.valueOf(l(2) * l(2)), 4);
  ASSERT_EQ(eval.valueOf(l(2) / l(2)), 1);
  ASSERT_EQ(eval.valueOf(sqare(l(2))), 4);
  ASSERT_EQ(eval.valueOf(l(2) + l(2) + l(2)), 6);
  ASSERT_EQ(eval.valueOf(l(2) * l(2) * l(2)), 8);
  ASSERT_EQ(eval.valueOf(sqare(sqare(l(2)))), 16);
  ASSERT_EQ(eval.valueOf(l(2) * sqare(l(2))), 8);
  ASSERT_EQ(eval.valueOf(l(2) * sqare(l(2)) + l(2) - l(2)), 8);
}
