#pragma once

#include "Symatica/Core.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Symbol/Table.hpp"
#include <map>
#include <utility>

namespace Symatica::Symbol {

using Symatica::Core::Id;
using Symatica::Expression::Expression;

class TreeTable : public Table {
public:
  explicit TreeTable(std::map<Id, Ptr<Expression>> expressionById);

  [[nodiscard]] Ptr<Expression> get(Id number) const override;
  void put(Id number, const Ptr<Expression>& expression) override;
  [[nodiscard]] bool has(Id number) const noexcept override;

private:
  std::map<Id, Ptr<Expression>> _expressionById;
};

}