#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"

namespace Symatica::Symbol {

using Symatica::Core::Id;
using Symatica::Core::Ptr;
using Symatica::Expression::Expression;

class Table {
public:
  [[nodiscard]] virtual Ptr<Expression> get(Id number) const = 0;
  virtual void put(Id number, const Ptr<Expression>& expression) = 0;
  [[nodiscard]] virtual bool has(Id number) const noexcept = 0;
  virtual ~Table() = default;
};

}
