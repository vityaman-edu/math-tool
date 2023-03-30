#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
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
using Symatica::Expression::DSL::pow;
using Symatica::Expression::DSL::var;

TEST(TestExpression, AsString) { // NOLINT
  ASSERT_EQ(l(0)->asString(), "0.000000");
  ASSERT_EQ(l(5)->asString(), "5.000000");
  ASSERT_EQ(l(12.0213)->asString(), "12.021300");
  ASSERT_EQ(var(1)->asString(), "$1");
  ASSERT_EQ((l(5) + l(6))->asString(), "(5.000000 + 6.000000)");
  ASSERT_EQ((l(5) - l(6))->asString(), "(5.000000 - 6.000000)");
  ASSERT_EQ((l(5) * l(6))->asString(), "(5.000000 * 6.000000)");
  ASSERT_EQ((l(5) / l(6))->asString(), "(5.000000 / 6.000000)");
  ASSERT_EQ((pow(var(1) + var(2), var(3)))->asString(), "(($1 + $2) ^ $3)");
}
