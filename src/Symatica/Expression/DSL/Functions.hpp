#pragma once

#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Literal.hpp"

namespace Symatica::Expression::DSL {

using Symatica::Expression::Exponentiation;
using Symatica::Expression::Literal;

using E = Expression;

Exponentiation sqare(const E& argument) noexcept;
Literal l(Number number) noexcept;

}