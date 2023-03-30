#pragma once

#include "Symatica/Expression/BinaryAddition.hpp"
#include "Symatica/Expression/BinaryDivision.hpp"
#include "Symatica/Expression/BinaryMultiplication.hpp"
#include "Symatica/Expression/BinarySubtraction.hpp"
#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Negation.hpp"

namespace Symatica::Expression::DSL {

using Symatica::Expression::BinaryAddition;
using Symatica::Expression::BinaryDivision;
using Symatica::Expression::BinaryMultiplication;
using Symatica::Expression::BinarySubtraction;

using E = Expression;

Ptr<BinaryAddition> operator+(const Ptr<E>& left, const Ptr<E>& right);

Ptr<BinarySubtraction> operator-(const Ptr<E>& left, const Ptr<E>& right);

Ptr<BinaryMultiplication> operator*(const Ptr<E>& left, const Ptr<E>& right);

Ptr<BinaryDivision> operator/(const Ptr<E>& left, const Ptr<E>& right);

Ptr<Negation> operator-(const Ptr<E>& child);

Ptr<Exponentiation> sqare(const Ptr<E>& argument);

Ptr<Exponentiation> pow(const Ptr<E>& number, const Ptr<E>& power);
}