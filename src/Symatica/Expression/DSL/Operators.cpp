#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/Negation.hpp"

namespace Symatica::Expression::DSL {

using Symatica::Core::makePtr;

Ptr<BinaryAddition> operator+(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinaryAddition>(left, right);
}

Ptr<BinarySubtraction> operator-(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinarySubtraction>(left, right);
}

Ptr<BinaryMultiplication> operator*(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinaryMultiplication>(left, right);
}

Ptr<BinaryDivision> operator/(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinaryDivision>(left, right);
}

Ptr<Negation> operator-(const Ptr<E>& child) {
  return makePtr<Negation>(child);
}

Ptr<Exponentiation> pow(const Ptr<E>& number, const Ptr<E>& power) {
  return makePtr<Exponentiation>(number, power);
}

Ptr<Exponentiation> sqare(const Ptr<E>& argument) {
  return pow(argument, l(2));
}

}