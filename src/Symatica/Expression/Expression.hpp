#pragma once

#include <string>
namespace Symatica::Expression {

enum Type {
  BINARY_ADDITION,
  BINARY_SUBTRACTION,
  BINARY_MULTIPLICATION,
  BINARY_DIVISION,
  EXPONENTIATION,
  ATOM_VARIABLE,
  ATOM_LITERAL,
};

// TODO: Create some gathering expression 
// that we will expose as root from api
// and witch will dispose memory resources
class Expression {
public:
  [[nodiscard]] virtual Type type() const noexcept = 0;
  [[nodiscard]] virtual std::string asString() const noexcept = 0;
  virtual ~Expression() = default;

  [[nodiscard]] bool isBinary() const noexcept {
    switch (type()) {
    case BINARY_ADDITION:
    case BINARY_SUBTRACTION:
    case BINARY_MULTIPLICATION:
    case BINARY_DIVISION:
    case EXPONENTIATION:
      return true;
    default:
      return false;
    }
  }

  [[nodiscard]] bool isAtom() const noexcept {
    switch (type()) {
    case ATOM_VARIABLE:
    case ATOM_LITERAL:
      return true;
    default:
      return false;
    }
  }
};

}
