#include "Symatica/Expression/DSL/Functions.hpp"
#include "Symatica/Core.hpp"
#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Literal.hpp"
#include <memory>

namespace Symatica::Expression::DSL {

using Symatica::Core::makePtr;

Ptr<Exponentiation> sqare(const Ptr<E>& argument) {
  return makePtr<Exponentiation>(argument, l(2));
}

Ptr<Literal> l(Number number) { return makePtr<Literal>(number); }

}