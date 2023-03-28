#include "Symatica/Expression/DSL/Functions.hpp"
#include "Symatica/Expression/Exponentiation.hpp"
#include "Symatica/Expression/Literal.hpp"

namespace Symatica::Expression::DSL {

// FIXME: it is here as Literal(2) was destoryed after
// scope exit in such code
//
// Exponentiation sqare(const E& argument) noexcept {
//   return Exponentiation(argument, Literal(2));
// }
const auto two = Literal(2); // NOLINT

Exponentiation sqare(const E& argument) noexcept {
  return Exponentiation(argument, two);
}

Literal l(Number number) noexcept { return Literal(number); }

}