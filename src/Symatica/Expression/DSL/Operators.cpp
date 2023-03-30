#include "Symatica/Expression/DSL/Operators.hpp"

namespace Symatica::Expression::DSL {

using Symatica::Core::makePtr;

Ptr<BinaryAddition>
operator+(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinaryAddition>(left, right);
}

Ptr<BinarySubtraction>
operator-(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinarySubtraction>(left, right);
}

Ptr<BinaryMultiplication>
operator*(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinaryMultiplication>(left, right);
}

Ptr<BinaryDivision>
operator/(const Ptr<E>& left, const Ptr<E>& right) {
  return makePtr<BinaryDivision>(left, right);
}

}