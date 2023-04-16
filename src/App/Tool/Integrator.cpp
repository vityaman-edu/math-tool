#include "App/Tool/Integrator.hpp"
#include "App/Canvas.hpp"
#include "App/Core.hpp"
#include "App/Error.hpp"
#include "Mathematica/Error.hpp"
#include "Mathematica/Integration/Approx.hpp"
#include "Mathematica/Integration/Core.hpp"
#include "Mathematica/Integration/Cotes.hpp"
#include <cmath>
#include <cstddef>

namespace App::Tool::Integrator {
using Mathematica::Error::ProcessDiverges;

static Method parseMethod(const String& string) {
  if (string == "rect-l") {
    return Method::RECTANGLE_L;
  }
  if (string == "rect-m") {
    return Method::RECTANGLE_M;
  }
  if (string == "rect-r") {
    return Method::RECTANGLE_R;
  }
  if (string == "trapeze") {
    return Method::TRAPEZE;
  }
  if (string == "simpson") {
    return Method::SIMPSON;
  }
  if (string == "cotes5") {
    return Method::COTES_5;
  }
  throw Error::IllegalArgument(
      "expected 'rect-*', 'trapeze', "
      "'simpson' or 'cotes5', got "
      + string
  );
}

static std::string toString(Method method) {
  switch (method) {
  case Method::RECTANGLE_L:
    return "Rectangle Left";
  case Method::RECTANGLE_M:
    return "Rectangle Middle";
  case Method::RECTANGLE_R:
    return "Rectangle Right";
  case Method::TRAPEZE:
    return "Trapeze";
  case Method::SIMPSON:
    return "Simpson";
  case Method::COTES_5:
    return "Cotes n = 5";
  default:
    return "???";
  }
}

static Function<Real> parseExpression(const String& string) {
  // NOLINTBEGIN(readability-magic-numbers)
  if (string == "1") {
    return [](Real x) { return x * x * x + 2.64 * x * x - 5.41 * x - 11.76; };
  }
  if (string == "2") {
    return [](Real x) { return 5 * std::sin(x) / x; };
  }
  if (string == "3") {
    return [](Real x) { return 3 * (x * x / 2 - 1) * std::sin(x / 2 + 5); };
  }
  if (string == "4") {
    return [](Real x) { return x * x - 1; };
  }
  if (string == "5") {
    return [](Real x) { return std::sqrt(x); };
  }
  if (string == "6") {
    return [](Real x) { return 3 * x * x * x - 4 * x * x + 7 * x - 17; };
  }
  if (string == "7") {
    return [](Real x) { return 1 / x; };
  }
  throw Error::IllegalArgument("expected '1', '2' or '3', got " + string);
  // NOLINTEND(readability-magic-numbers)
}

static Real parseReal(const String& string) { return std::stof(string); }

Arguments Arguments::parseArgs(const Vector<String>& args) {
  return {
      .method = parseMethod(args[2]),
      .scope = Scope(parseReal(args[3]), parseReal(args[4])),
      .accuracy = parseReal(args[5]),
  };
};

template <typename F>
static Mathematica::Integration::TrivialMethod<F> trivial(Method method) {
  using namespace Mathematica::Integration; // NOLINT
  switch (method) {
  case Method::RECTANGLE_L:
    return trivial0<F>([](auto i) { return i.left(); });
  case Method::RECTANGLE_M:
    return trivial0<F>([](auto i) { return i.middle(); });
  case Method::RECTANGLE_R:
    return trivial0<F>([](auto i) { return i.right(); });
  case Method::TRAPEZE:
    return trivial1<F>();
  case Method::SIMPSON:
    return trivial2<F>();
  case Method::COTES_5:
    return trivial5<F>();
  };
}

void Runner::run(std::istream& input, std::ostream& output) {
  using F = double;

  auto equation = std::string();
  input >> equation;
  auto f = parseExpression(equation);

  auto args = this->args();

  output << "Report" << std::endl;
  output << "Taken method: " << toString(args.method) << std::endl;
  output << "Scope: " << args.scope.asString() << std::endl;
  output << "Accuracy: " << args.accuracy << std::endl;

  using namespace Mathematica::Integration; // NOLINT
  auto tracer = MarkdownTableTracer<F>(std::cout);
  const auto approx = ApproxFactory(args.accuracy, tracer);
  auto method = approx.of(trivial<F>(args.method));
  try {
    auto result = method.integrate(f, args.scope);
    output << "Result: " << result << std::endl;
  } catch (ProcessDiverges& e) {
    output << "No result: " << e.what() << std::endl;
  }

  output << "Graph: " << std::endl;

  constexpr auto HEIGHT = 80;
  constexpr auto WIDTH = 120;
  constexpr auto STEP = 0.1;

  ConsoleCanvas canvas(Point<Size>(HEIGHT, WIDTH), args.scope);
  auto x = args.scope.left();
  while (x <= args.scope.right()) {
    auto y = f(x);
    canvas.draw({x, 0}, '-');
    canvas.draw({0, y}, '|');
    canvas.draw({x, y}, '+');
    x += STEP;
  }
  for (Real y = -HEIGHT / 2; y <= HEIGHT / 2; y++) { // NOLINT
    canvas.draw({args.scope.left(), y}, '[');
    canvas.draw({args.scope.right(), y}, ']');
  }
  for (Real x = args.scope.left(); x <= args.scope.right(); x++) { // NOLINT
    canvas.draw({x, 0}, '=');
  }
  canvas.print(output);
}

}