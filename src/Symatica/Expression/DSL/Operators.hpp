#pragma once

#include "Symatica/Expression/BinaryAddition.hpp"
#include "Symatica/Expression/BinaryDivision.hpp"
#include "Symatica/Expression/BinaryMultiplication.hpp"
#include "Symatica/Expression/BinarySubtraction.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Expression::DSL {

using Symatica::Expression::BinaryAddition;
using Symatica::Expression::BinaryDivision;
using Symatica::Expression::BinaryMultiplication;
using Symatica::Expression::BinarySubtraction;

using E = Expression;

Ptr<BinaryAddition>
operator+(const Ptr<E>& left, const Ptr<E>& right);

Ptr<BinarySubtraction>
operator-(const Ptr<E>& left, const Ptr<E>& right);

Ptr<BinaryMultiplication>
operator*(const Ptr<E>& left, const Ptr<E>& right);

Ptr<BinaryDivision>
operator/(const Ptr<E>& left, const Ptr<E>& right);

}