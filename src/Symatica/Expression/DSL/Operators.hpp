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

BinaryAddition operator+(const E& left, const E& right) noexcept;
BinarySubtraction operator-(const E& left, const E& right) noexcept;
BinaryMultiplication operator*(const E& left, const E& right) noexcept;
BinaryDivision operator/(const E& left, const E& right) noexcept;

}