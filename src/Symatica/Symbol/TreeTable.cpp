#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Error.hpp"
#include <utility>

namespace Symatica::Symbol {

TreeTable::TreeTable(std::map<Id, Ptr<Expression>> expressionById)
    : _expressionById(std::move(expressionById)) {}

[[nodiscard]] Ptr<Expression> TreeTable::get(Id number) const {
  if (!has(number)) {
    throw Error::SymbolNotFound(number);
  }
  return _expressionById.at(number);
}

void TreeTable::put(Id number, const Ptr<Expression>& expression) {
  _expressionById.insert(std::make_pair(number, std::ref(expression)));
}

[[nodiscard]] bool TreeTable::has(Id number) const noexcept {
  return _expressionById.find(number) != _expressionById.end();
}

}