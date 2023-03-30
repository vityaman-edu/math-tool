#include "Symatica/Visitor/Derivativer.hpp"
#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
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

TEST(TestDerivativer, Playground) { // NOLINT
  auto derivativer = Symatica::Visitor::Derivativer(1);
  auto expression = l(7) * pow(var(1), l(3)) + l(5) * pow(var(1), l(2)) + l(3) * var(1) + l(2);
  std::cout << "OUT:" << std::endl;
  std::cout << derivativer.derivativeOf(expression)->asString() << std::endl;
  std::cout << "END" << std::endl;
}
