#pragma once

#include "Symatica/Core.hpp"
#include <stdexcept>
#include <string>

namespace Symatica::Error {

using Symatica::Core::Id;

class General : std::runtime_error {
public:
  explicit General(const std::string& message)
      : std::runtime_error(message) {}
};

class SymbolNotFound : public General {
public:
  explicit SymbolNotFound(Id number)
      : General(
          "Symbol with id " + std::to_string(number) + "not found"
      ) {}
};

}