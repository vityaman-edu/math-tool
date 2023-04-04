#include "App/Tool/EquationSolver.hpp"
#include "App/Canvas.hpp"
#include "App/Error.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/FunctionAnalysis.hpp"
#include "Mathematica/Equation/Solution/Method/HalfDivision.hpp"
#include "Mathematica/Equation/Solution/Method/Newton.hpp"
#include "Mathematica/Equation/Solution/Method/SimpleIteration.hpp"

#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

namespace App::Tool::EquationSolver {

static Method parseMethod(const String& string) {
  if (string == "half-division") {
    return Method::HALF_DIVISION;
  }
  if (string == "newton") {
    return Method::NEWTON;
  }
  if (string == "simple-iteration") {
    return Method::SIMPLE_ITERATION;
  }
  throw Error::IllegalArgument(
      "expected 'half-division', 'newton' or 'simple-iteration',"
      " got "
      + string
  );
}

static std::string toString(Method method) {
  switch (method) {
  case Method::HALF_DIVISION:
    return "Half Division";
  case Method::NEWTON:
    return "Newton";
  case Method::SIMPLE_ITERATION:
    return "Simple Iteration";
  default:
    return "???";
  }
}

static Real parseReal(const String& string) { return std::stof(string); }

Arguments Arguments::parseArgs(const Vector<String>& args) {
  return {
      .method = parseMethod(args[2]),
      .scope = Scope(parseReal(args[3]), parseReal(args[4])),
      .accuracy = parseReal(args[5]),
  };
};

static Function<Real> parseExpression(const String& string) {
  if (string == "1") {
    return [](Real x) {
      return x * x * x + 2.64 * x * x - 5.41 * x - 11.76; // NOLINT
    };
  }
  if (string == "2") {
    return [](Real x) {
      return 5 * std::sin(x) / x; // NOLINT
    };
  }
  if (string == "3") {
    return [](Real x) {
      return 3 * (x * x / 2 - 1) * std::sin(x / 2 + 5); // NOLINT
    };
  }
  if (string == "4") {
    return [](Real x) {
      return x * x - 1; // NOLINT
    };
  }
  throw Error::IllegalArgument("expected '1', '2' or '3', got " + string);
}

void Runner::run(std::istream& input, std::ostream& output) const {
  auto equation = std::string("");
  input >> equation;
  auto f = parseExpression(equation);

  auto eps = 0.00001;
  auto df = [&f, eps](Real x) { return (f(x + eps) - f(x)) / eps; };
  auto ddf = [&df, eps](Real x) { return (df(x + eps) - df(x)) / eps; };

  output << "Report" << std::endl;
  output << "Taken method: " << toString(args.method) << std::endl;
  output << "Scope: " << args.scope.asString() << std::endl;
  output << "Accuracy: " << args.accuracy << std::endl;

  output << "Graph: " << std::endl;

  constexpr auto HEIGHT = 80;
  constexpr auto WIDTH = 120;
  constexpr auto STEP = 0.1;

  ConsoleCanvas canvas(Point<Size>(HEIGHT, WIDTH), args.scope);
  auto x = args.scope.left();
  while (x < args.scope.right()) {
    auto y = f(x);
    canvas.draw({x, 0}, '-');
    canvas.draw({0, y}, '|');
    canvas.draw({x, y}, '+');
    x += STEP;
  }

  using Mathematica::Equation::Solution::Method::rootSeparabilityIntervals;
  const auto interestingScopes = rootSeparabilityIntervals<Real>(
      args.scope, args.scope.length() / 30, f
  );

  for (const auto& scope : interestingScopes) {
    canvas.draw({scope.left(), 0}, '{');
    canvas.draw({scope.right(), 0}, '}');
  }

  canvas.print(output);

  using namespace Mathematica::Equation::Solution::Method;

  auto halfDivisionTracer = HalfDivision::MarkdownTableTracer<Real>(std::cout);
  auto halfDivision = HalfDivision::Executor<Real, typeof(halfDivisionTracer)>(
      args.accuracy, halfDivisionTracer
  );

  auto newtonTracer = Newton::MarkdownTableTracer<Real>(std::cout);
  auto newton = Newton::Executor<Real, typeof(newtonTracer)>(
      args.accuracy, newtonTracer
  );

  auto simpleIterationTracer = SimpleIteration::MarkdownTableTracer<Real>(std::cout);
  auto simpleIteration
      = SimpleIteration::Executor<Real, typeof(simpleIterationTracer)>(
          args.accuracy, simpleIterationTracer
      );

  for (const auto& scope : interestingScopes) {
    std::cout << "Scope: " << scope.asString() << std::endl;

    if (bool halfDivisionAccepts = true) {
      const auto result = halfDivision.findSomeRoot(scope, f);
      std::cout << "HalfDivision result is " << result << std::endl;
    }

    if (newton.accepts(scope, f, df, ddf)) {
      const auto result = newton.findSomeRoot(scope, f, df, ddf);
      std::cout << "Newton result is " << result << std::endl;
    } else {
      std::cout << "Newton CAN NOT" << std::endl;
    }

    auto dphi = SimpleIteration::buildDPhiFrom<Real>(scope, df);
    if (simpleIteration.accepts(scope, dphi)) {
      const auto phi = SimpleIteration::buildPhiFrom<Real>(scope, f, df);
      const auto result = simpleIteration.findSomeRoot(scope.left(), phi);
      std::cout << "SimpleIteration result is " << result << std::endl;
    } else {
      std::cout << "SimpleIteration CAN NOT" << std::endl;
    }

    std::cout << std::endl;
  }
}

}