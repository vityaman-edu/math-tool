#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Functional/Approx/LeastSqare.hpp"
#include "Mathematica/Functional/Exploration/Tabulate.hpp"
#include "Mathematica/Interop/Polynomial.hpp"
#include "Mathematica/Statistics/RSS.hpp"
#include "Mathematica/Statistics/Score.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include <gtest/gtest.h>

TEST(Approx, Playground) { // NOLINT
  using Mathematica::Interop::symbolic;
  using Symatica::Expression::DSL::var;

  using namespace Mathematica; // NOLINT
  using R = Mathematica::Abstract::Float<double>;
  using namespace Mathematica::Functional; // NOLINT
  constexpr auto MIN = 0;
  constexpr auto MAX = 2;
  constexpr auto FINENESS = 0.2;
  constexpr Mathematica::Count N = (MAX - MIN) / FINENESS;

  const auto scope = Interval<R>(MIN, MAX);
  const auto f = [](R x) -> R {             // NOLINT
    return (R(2) * x) / (x.pow(4) + R(17)); // NOLINT
  };

  const auto points = Exploration::Tabulate::trivial<R, N>(f, scope);
  for (const auto& point : points) {
    std::cout << "( " << point.x.asString() //
              << ", " << point.y.asString() //
              << " )" << std::endl;
  }

  const auto line = Approx::LeastSqare::optimalPolynomial<R, 2>(points);
  const auto sline = symbolic(line, var(1));
  const auto parabola = Approx::LeastSqare::optimalPolynomial<R, 3>(points);
  const auto sparabola = symbolic(parabola, var(1));

  const auto lineS = Statistics::standartDeviation(line, points);
  const auto parabolaS = Statistics::standartDeviation(parabola, points);

  const auto lineR2 = Statistics::Score::R2(line, points);
  const auto parabolaR2 = Statistics::Score::R2(parabola, points);

  std::cout << "Line: " + sline->asString() << std::endl;
  std::cout << "Line: STD = " + lineS.asString() << std::endl;
  std::cout << "Line: R2 = " + lineR2.asString() << std::endl;

  std::cout << "Parabola: " + sparabola->asString() << std::endl;
  std::cout << "Parabola: STD = " + parabolaS.asString() << std::endl;
  std::cout << "Parabola: R2 = " + parabolaR2.asString() << std::endl;
}