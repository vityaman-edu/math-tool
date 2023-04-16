#include "App/Tool/EquationSystemSolver.hpp"
#include "App/Canvas.hpp"
#include "App/Error.hpp"
#include <cmath>
#include <iostream>
#include <ostream>

namespace App::Tool::EquationSystemSolver {

static Real parseReal(const String& string) { return std::stof(string); }

static System parseSystem(const String& string) {
  if (string == "1") {
    return {
        .x = [](Real x, Real y) { return 0.1 * x * x + x + 0.2 * y * y - 0.3; },
        .y = [](Real x, Real y) { return 0.2 * x * x + y + 0.1 * x * y - 0.7; },
        .phiX = [](Real x, Real y) { return 0.3 - 0.1 * x * x - 0.2 * y * y; },
        .phiY = [](Real x, Real y) { return 0.7 - 0.2 * x * x - 0.1 * x * y; },
    };
  }
  if (string == "2") {
    return {
        .x = [](Real x, Real y) { return x + y * y - 9; },
        .y = [](Real x, Real y) { return x - y - 1; },
        .phiX = [](Real x, Real y) { return 9 - y * y; },
        .phiY = [](Real x, Real y) { return x - 1; },
    };
  }
  throw Error::IllegalArgument("expected '1' or '2', got " + string);
}

Arguments Arguments::parseArgs(const Vector<String>& args) {
  return {
      .start = Point<Real>(parseReal(args[2]), parseReal(args[3])),
      .accuracy = parseReal(args[4]),
  };
}

void Runner::run(std::istream& input, std::ostream& output) const {
  auto systemStr = std::string("");
  input >> systemStr;
  auto system = parseSystem(systemStr);

  output << "Report" << std::endl;
  output << "Taken start point is: (" << //
      args.start.x() << ", " << args.start.y() << ")" << std::endl;
  output << "Accuracy: " << args.accuracy << std::endl;

  output << "Graph: " << std::endl;

  constexpr auto HEIGHT = 80;
  constexpr auto WIDTH = 120;
  constexpr auto STEP = 0.1;

  const auto scopeX = Scope(-6, 6);
  const auto scopeY = Scope(-20, 20);

  ConsoleCanvas canvas(Point<Size>(HEIGHT, WIDTH), scopeX);
  auto x = scopeX.left();
  while (x < scopeX.right()) {
    auto y = scopeY.left();
    while (y < scopeY.right()) {
      auto resultX = system.x(x, y);
      if (std::abs(resultX) < STEP) {
        canvas.draw({x, y}, '@');
      }

      auto resultY = system.y(x, y);
      if (std::abs(resultY) < STEP) {
        canvas.draw({x, y}, '#');
      }

      canvas.draw({x, 0}, '-');
      canvas.draw({0, y}, '|');

      y += STEP;
    }

    x += STEP;
  }

  const auto dist = [](Point<Real> a, Point<Real> b) {
    return std::sqrt(
        std::pow((a.x() - b.x()), 2) //
        + std::pow((a.y() - b.y()), 2)
    );
  };

  auto prev = args.start;

  if (!system.isOK(prev.x(), prev.y())) {
    canvas.print(output);
    std::cout << "Can not find a root using simple iteration" << std::endl;
    return;
  }

  int i = 0;
  while (true) {
    auto next = system.phi(prev);
    if (dist(next, prev) < args.accuracy) {
      break;
    }
    canvas.draw(prev, '0' + i++);
    prev = next;
  }

  canvas.print(output);

  output << "Result: " << prev.asString() << std::endl;
}

}