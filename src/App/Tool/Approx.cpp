#include "App/Tool/Approx.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/Exponential.hpp"
#include "Mathematica/Functional/Approx/LeastSqare.hpp"
#include "Mathematica/Functional/Approx/Linear.hpp"
#include "Mathematica/Functional/Approx/Logarithmic.hpp"
#include "Mathematica/Functional/Approx/Model/ChoiceOptimal.hpp"
#include "Mathematica/Functional/Approx/Model/Core.hpp"
#include "Mathematica/Functional/Approx/Power.hpp"
#include "Mathematica/Interop/Polynomial.hpp"
#include "Mathematica/Statistics/PCC.hpp"
#include "Mathematica/Statistics/RSS.hpp"
#include "Mathematica/Statistics/Score.hpp"

namespace App::Tool::Approx {

Arguments Arguments::parseArgs(const Vector<String>& /*args*/) { return {}; }

void Runner::run(std::istream& input, std::ostream& out) {
  using Mathematica::Interop::symbolic;
  using Symatica::Expression::DSL::var;

  using namespace Mathematica;             // NOLINT
  using namespace Mathematica::Statistics; // NOLINT
  using Mathematica::Collection::Array;
  using Mathematica::Functional::Approx::LeastSqare::optimalPolynomial;
  using Mathematica::Statistics::Score::R2;
  using R = Mathematica::Abstract::Float<double>;
  constexpr auto N = 10;

  const auto points = Array<Point<R>, N>([&input](auto) {
    double x = 0;
    double y = 0;
    input >> x >> y;
    return Point<R>(x, y);
  });

  out << "=== Approx::Linear ===" << std::endl;
  auto line = Functional::Approx::Linear::trendLine(points);
  out << "y     = " + line.asString() << std::endl;
  out << "slope = " + line.slope().asString() << std::endl;
  out << "bias  = " + line.bias().asString() << std::endl;
  out << "std   = " + standartDeviation(line, points).asString() << std::endl;
  out << "r2    = " + R2(line, points).asString() << std::endl;
  out << "r     = " + pcc(points).asString() << std::endl;

  out << "=== Approx::Power ===" << std::endl;
  const auto pow = Functional::Approx::Power::train(points);
  out << "y     = " + pow.asString() << std::endl;
  out << "mult  = " + pow.multiplier.asString() << std::endl;
  out << "power = " + pow.power.asString() << std::endl;
  out << "std   = " + standartDeviation(pow, points).asString() << std::endl;
  out << "r2    = " + R2(pow, points).asString() << std::endl;

  out << "=== Approx::Exponential ===" << std::endl;
  const auto exp = Functional::Approx::Exponential::train(points);
  out << "y     = " + exp.asString() << std::endl;
  out << "mult  = " + exp.multiplier.asString() << std::endl;
  out << "powk  = " + exp.powerSlope.asString() << std::endl;
  out << "std   = " + standartDeviation(exp, points).asString() << std::endl;
  out << "r2    = " + R2(exp, points).asString() << std::endl;

  out << "=== Approx::Logarithmic ===" << std::endl;
  const auto log = Functional::Approx::Logarithmic::train(points);
  out << "y     = " + log.asString() << std::endl;
  out << "mult  = " + log.slope.asString() << std::endl;
  out << "powk  = " + log.bias.asString() << std::endl;
  out << "std   = " + standartDeviation(log, points).asString() << std::endl;
  out << "r2    = " + R2(log, points).asString() << std::endl;

  out << "=== Approx::optimalPolynomial::2 ===" << std::endl;
  const auto poly2 = optimalPolynomial<R, 3>(points);
  out << "y     = " + symbolic(poly2, var(1))->asString() << std::endl;
  out << "std   = " + standartDeviation(poly2, points).asString() << std::endl;
  out << "r2    = " + R2(poly2, points).asString() << std::endl;

  out << "=== Approx::optimalPolynomial::3 ===" << std::endl;
  const auto poly3 = optimalPolynomial<R, 4>(points);
  out << "y     = " + symbolic(poly3, var(1))->asString() << std::endl;
  out << "std   = " + standartDeviation(poly3, points).asString() << std::endl;
  out << "r2    = " + R2(poly3, points).asString() << std::endl;

  out << "=== Approx::optimalPolynomial::4 ===" << std::endl;
  const auto poly4 = optimalPolynomial<R, 5>(points);
  out << "y     = " + symbolic(poly4, var(1))->asString() << std::endl;
  out << "std   = " + standartDeviation(poly4, points).asString() << std::endl;
  out << "r2    = " + R2(poly4, points).asString() << std::endl;

  {
    using Functional::Approx::Model::Algorithm;
    using Functional::Approx::Model::ChoiceOptimal;
    using Functional::Approx::Model::Model;
    using namespace Functional::Approx; // NOLINT
    using Algebra::Polynomial;

    auto line = Algorithm<R, N, Linear::TrendLine<R>>(Linear::trendLine<R, N>);
    auto pow = Algorithm<R, N, Power::Trend<R>>(Power::train<R, N>);
    auto exp = Algorithm<R, N, Exponential::Trend<R>>(Exponential::train<R, N>);
    auto log = Algorithm<R, N, Logarithmic::Trend<R>>(Logarithmic::train<R, N>);
    auto poly2 = Algorithm<R, N, Polynomial<R, 3>>(optimalPolynomial<R, 3, N>);
    auto poly3 = Algorithm<R, N, Polynomial<R, 4>>(optimalPolynomial<R, 4, N>);
    auto poly4 = Algorithm<R, N, Polynomial<R, 5>>(optimalPolynomial<R, 5, N>);

    const auto algorithms = Array<Model<R, N>*, 7>({
        {&line, &pow, &exp, &log, &poly2, &poly3, &poly4}
    });

    auto optimal = ChoiceOptimal<R, N, 7>( // NOLINT
      algorithms,
      Score::R2<R, N, Mathematica::Function<R>>
    );

    const auto trend = optimal.trainedOn(points);
    const auto s = standartDeviation(trend, points);
    const auto r2 = R2(trend, points);
    out << "=== Approx::ChoiceOptimal ===" << std::endl;
    out << "std   = " + s.asString() << std::endl;
    out << "r2    = " + r2.asString() << std::endl;
  }
}

}