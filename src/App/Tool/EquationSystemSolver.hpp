#pragma once

#include "App/Canvas.hpp"
#include "App/Core.hpp"
#include <cmath>
#include <functional>

namespace App::Tool::EquationSystemSolver {

constexpr auto REQUIRED_ARGS_SIZE = 8;

using Function2 = std::function<Real(Real, Real)>;

struct System { // NOLINT
  Function2 x;
  Function2 y;

  Function2 phiX;
  Function2 phiY;

  [[nodiscard]] Point<Real> phi(Point<Real> p) const noexcept {
    return {phiX(p.x(), p.y()), phiY(p.x(), p.y())};
  }

  [[nodiscard]] bool isOK(Real x, Real y) const noexcept {
    auto eps = 0.00001;
    auto dfdx = (this->x(x + eps, y) - this->x(x, y)) / eps;
    auto dfdy = (this->x(x, y + eps) - this->x(x, y)) / eps;
    auto dgdx = (this->y(x, y + eps) - this->y(x, y)) / eps;
    auto dgdy = (this->y(x + eps, y) - this->y(x, y)) / eps;
    auto J = dfdx * dgdy - dfdy * dgdx;
    return std::abs(J) < 1;
  }
};

struct Arguments { // NOLINT
  Point<Real> start;
  Real accuracy;

  static Arguments parseArgs(const Vector<String>& args);
};

class Runner {
public:
  explicit Runner(Arguments args) : args(std::move(args)) {}

  void run(std::istream& input, std::ostream& output) const;

private:
  Arguments args;
};

}