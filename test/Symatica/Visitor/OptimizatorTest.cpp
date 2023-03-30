#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Visitor/Derivativer.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include "Symatica/Visitor/Optimizer.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <string>

using Symatica::Expression::DSL::operator*; // NOLINT
using Symatica::Expression::DSL::operator+; // NOLINT
using Symatica::Expression::DSL::operator/; // NOLINT
using Symatica::Expression::DSL::operator-; // NOLINT
using Symatica::Core::Number;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::pow;
using Symatica::Expression::DSL::var;

TEST(TestOptimizer, Derivative) { // NOLINT
  auto derivativer = Symatica::Visitor::Derivativer(1);
  auto optimizer = Symatica::Visitor::Optimizer();
  auto table = Symatica::Symbol::TreeTable({});
  auto eval = Symatica::Visitor::Evaluator(table);
  auto expression = l(2) * pow(var(1), l(3))   // NOLINT
                    + l(5) * pow(var(1), l(2)) // NOLINT
                    - l(4) * var(1)            // NOLINT
                    + l(9);                    // NOLINT
  auto actual_derivative
      = optimizer.optimized(derivativer.derivativeOf(expression));
  std::cout << actual_derivative->asString() << std::endl;
  auto expected_derivative
      = l(-4) + l(10) * var(1) + l(6) * pow(var(1), l(2)); // NOLINT
  for (Number n = -10; n <= 10; n++) {                     // NOLINT
    table.put(1, l(n));
    ASSERT_FLOAT_EQ(
        eval.valueOf(actual_derivative), eval.valueOf(expected_derivative)
    );
  }
}
