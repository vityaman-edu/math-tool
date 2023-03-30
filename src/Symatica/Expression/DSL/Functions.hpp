#pragma once

#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Literal.hpp"

namespace Symatica::Expression::DSL {

using Symatica::Expression::Exponentiation;
using Symatica::Expression::Literal;

using E = Expression;

Ptr<Exponentiation> sqare(const Ptr<E>& argument);
Ptr<Literal> l(Number number);

}