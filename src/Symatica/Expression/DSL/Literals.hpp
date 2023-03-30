#pragma once

#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Literal.hpp"
#include "Symatica/Expression/Variable.hpp"

namespace Symatica::Expression::DSL {

using Symatica::Expression::Literal;

using E = Expression;

Ptr<Literal> l(Number number);

Ptr<Variable> var(Id number);

}