#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include <gtest/gtest.h>

using Symatica::Expression::DSL::operator*; // NOLINT
using Symatica::Expression::DSL::operator+; // NOLINT
using Symatica::Expression::DSL::operator/; // NOLINT
using Symatica::Expression::DSL::operator-; // NOLINT
using Symatica::Core::Number;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::pow;
using Symatica::Expression::DSL::var;

TEST(TestExpression, AsString) { // NOLINT
  ASSERT_EQ(l(0)->asString(), "0");
  ASSERT_EQ(l(5)->asString(), "5");
  ASSERT_EQ(l(12.0213)->asString(), "12.021300");
  ASSERT_EQ(var(1)->asString(), "x");
  ASSERT_EQ((l(5) + l(6))->asString(), "(5 + 6)");
  ASSERT_EQ((l(5) - l(6))->asString(), "(5 - 6)");
  ASSERT_EQ((l(5) * l(6))->asString(), "(5 * 6)");
  ASSERT_EQ((l(5) / l(6))->asString(), "(5 / 6)");
  ASSERT_EQ((pow(var(1) + var(2), var(3)))->asString(), "((x + $2) ^ $3)");
}
