#include "App/Tool/Interpolator.hpp"
#include "App/Canvas.hpp"
#include "App/Error.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Exploration/Tabulate.hpp"
#include "Mathematica/Functional/Interpolation/Lagrange.hpp"
#include "Mathematica/Functional/Interpolation/Newton.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include <algorithm>
#include <cmath>
#include <ostream>

namespace App::Tool::Interpolator {

using Mathematica::Collection::Array;
using R = Mathematica::Abstract::Float<double>;

static Mode parse(const String& string) {
  if (string == "points") {
    return Mode::POINTS;
  }
  if (string == "func") {
    return Mode::FUNCTION;
  }
  throw Error::IllegalArgument("expected `points` or `func`, got " + string);
}

Arguments Arguments::parseArgs(const Vector<String>& args) {
  return {
      parse(args[2]),
  };
}

Mathematica::Function<R> parseFunction(const String& string) {
  if (string == "1") {
    return [](R x) { return R(std::sin(x.value)); }; // NOLINT
  }
  if (string == "2") {
    return [](R x) { return R(std::tan(x.value)); }; // NOLINT
  }
  throw Error::IllegalArgument("expected 1-2, got " + string);
}

template <Mathematica::Count N>
Array<Mathematica::Point<R>, N>
getPoints(std::istream& input, std::ostream& out, Mode mode) {
  if (mode == Mode::POINTS) {
    return Array<Mathematica::Point<R>, N>([&input](auto) {
      double x = 0;
      double y = 0;
      input >> x >> y;
      return Mathematica::Point<R>(x, y);
    });
  }

  out << "Choice a function: " << std::endl;
  out << "1) y = sin(x)" << std::endl;
  out << "2) y = tan(x)" << std::endl;
  out << "I choice [1-2]: ";
  String text;
  input >> text;
  const auto f = parseFunction(text);

  double left, right; // NOLINT
  out << "Type an interval.left: ";
  input >> left;
  out << "Type an interval.right: ";
  input >> right;

  return Mathematica::Functional::Exploration::Tabulate::trivial<R, N>(
      f, Mathematica::Interval<R>(left, right)
  );
}

void Runner::run(std::istream& input, std::ostream& out) {
  constexpr auto N = 5;
  const auto points = getPoints<N>(input, out, args().mode);

  constexpr auto X = 1;
  const auto x = Symatica::Expression::DSL::var(X);
  auto table = Symatica::Symbol::TreeTable({});
  auto eval = Symatica::Visitor::Evaluator(table);

  const auto lagrange
      = Mathematica::Functional::Interpolation::symbolicLagrange(points, x);
  const auto newton
      = Mathematica::Functional::Interpolation::symbolicNewton(points, x);

  const auto lagrangeAt = [&table, &eval, &lagrange](double x) {
    table.put(X, Symatica::Expression::DSL::l(x));
    return eval.valueOf(lagrange);
  };

  const auto newtonAt = [&table, &eval, &newton](double x) {
    table.put(X, Symatica::Expression::DSL::l(x));
    return eval.valueOf(newton);
  };

  out << "=== Interpolation::symbolicLagrange ===" << std::endl;
  out << "Symathica::Expression::asString:" << std::endl;
  out << lagrange->asString() << std::endl;

  out << "=== Interpolation::symbolicNewton ===" << std::endl;
  out << "Symathica::Expression::asString:" << std::endl;
  out << newton->asString() << std::endl;

  {
    constexpr auto HEIGHT = 80;
    constexpr auto WIDTH = 120;
    constexpr auto STEP = 0.1;

    const auto xs = Array<R, N>([&points](auto i) { return points[i].x; });
    const auto minX = *std::min_element(xs.begin(), xs.end());
    const auto maxX = *std::max_element(xs.begin(), xs.end());
    const auto scope = Mathematica::Interval<Real>(minX.value, maxX.value);

    ConsoleCanvas canvas(Point<Size>(HEIGHT, WIDTH), scope);
    auto x = scope.left();
    while (x <= scope.right()) {
      auto ly = lagrangeAt(x);
      auto ny = newtonAt(x);
      canvas.draw({x, 0}, '-');
      canvas.draw({0, ly}, '|');
      canvas.draw({0, ny}, '|');
      canvas.draw({x, ny}, 'n');
      canvas.draw({x, ly}, 'l');
      x += STEP;
    }
    for (const auto& point : points) {
      canvas.draw({point.x.value, point.y.value}, '#');
    }
    canvas.print(out);
  }

  auto argument = 0.0;
  out << "Enter x: ";
  while (input >> argument) {
    out << "lagrangeAt(" << argument << ") = " << lagrangeAt(argument) << std::endl;
    out << "newtonAt(" << argument << ") = " << newtonAt(argument) << std::endl;
    out << "Enter x: ";
  }
}

}