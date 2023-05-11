#pragma once

#include <stdexcept>
#include <string>

namespace Mathematica::Error {

class General : public std::runtime_error {
public:
  explicit General(const std::string& message) : std::runtime_error(message) {}
};

class ProcessDiverges : public General {
public:
  explicit ProcessDiverges(const std::string& message) : General(message) {}
};

}