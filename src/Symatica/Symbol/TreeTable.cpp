#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Error.hpp"
#include <utility>

namespace Symatica::Symbol {

TreeTable::TreeTable(std::map<Id, Ptr<Expression>> expressionById)
    : _expressionById(std::move(expressionById)) {}

[[nodiscard]] Ptr<Expression> TreeTable::get(Id id) const {
  if (!has(id)) {
    throw Error::SymbolNotFound(id);
  }
  return _expressionById.at(id);
}

void TreeTable::put(Id id, const Ptr<Expression>& expression) {
  _expressionById[id] = std::ref(expression);
}

[[nodiscard]] bool TreeTable::has(Id id) const noexcept {
  return _expressionById.find(id) != _expressionById.end();
}

}