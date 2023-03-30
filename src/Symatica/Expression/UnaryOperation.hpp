#pragma once

#include "Symatica/Expression/Expression.hpp"
#include <memory>
#include <utility>

namespace Symatica::Expression {

class UnaryOperation : public Expression {
public:
  explicit UnaryOperation(const Ptr<Expression>& child)
      : _child(child) {}

  [[nodiscard]] Ptr<Expression> child() const noexcept {
    return _child;
  }

  [[nodiscard]] std::string asString() const noexcept override {
    return symbolOf(type()) + _child->asString();
  }

private:
  static std::string symbolOf(Type type) noexcept {
    switch (type) {
    case NEGATION:
      return "-";
    default:
      return "?";
    }
  }

  Ptr<Expression> _child;
};

}