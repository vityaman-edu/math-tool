#pragma once

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

class Expression {
public:
  [[nodiscard]] virtual Type type() const noexcept = 0;
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
