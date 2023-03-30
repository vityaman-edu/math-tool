#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Core.hpp"
#include "Symatica/Expression/Literal.hpp"
#include "Symatica/Expression/Variable.hpp"
#include <memory>

namespace Symatica::Expression::DSL {

using Symatica::Core::makePtr;

Ptr<Literal> l(Number number) { return makePtr<Literal>(number); }

Ptr<Variable> var(Id number) { return makePtr<Variable>(number); }

}