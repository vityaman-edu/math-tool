#include "Symatica/Expression/DSL/Operators.hpp"

namespace Symatica::Expression::DSL {

BinaryAddition operator+(const E& left, const E& right) noexcept {
  return {left, right};
}

BinarySubtraction operator-(const E& left, const E& right) noexcept {
  return {left, right};
}

BinaryMultiplication operator*(const E& left, const E& right) noexcept {
  return {left, right};
}

BinaryDivision operator/(const E& left, const E& right) noexcept {
  return {left, right};
}

}