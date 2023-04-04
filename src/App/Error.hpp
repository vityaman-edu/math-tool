#pragma once

#include <stdexcept>

namespace App::Error {

class General : std::runtime_error {
public:
  explicit General(const std::string& message) //
      : std::runtime_error(message) {}
};

class IllegalArgument : public std::invalid_argument {
public:
  explicit IllegalArgument(const std::string& message)
      : std::invalid_argument(message) {}
};

}