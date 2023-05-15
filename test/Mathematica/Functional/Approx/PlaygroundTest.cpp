#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Functional/Approx/Exponential.hpp"
#include "Mathematica/Functional/Approx/LeastSqare.hpp"
#include "Mathematica/Functional/Approx/Linear.hpp"
#include "Mathematica/Functional/Approx/Logarithmic.hpp"
#include "Mathematica/Functional/Approx/Model/ChoiceOptimal.hpp"
#include "Mathematica/Functional/Approx/Model/Core.hpp"
#include "Mathematica/Functional/Approx/Model/Partition.hpp"
#include "Mathematica/Functional/Approx/Power.hpp"
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

TEST(Approx, PlaygroundPartition) {        // NOLINT
  using namespace Mathematica;             // NOLINT
  using namespace Functional::Exploration; // NOLINT
  using namespace Functional::Approx;      // NOLINT
  using namespace Statistics;              // NOLINT
  using Algebra::Polynomial;
  using Functional::Approx::Model::Algorithm;
  using Functional::Approx::Model::ChoiceOptimal;
  using Functional::Approx::Model::Model;
  using Functional::Approx::Model::PartitionModel;
  using Mathematica::Collection::Array;
  using Mathematica::Functional::Approx::LeastSqare::optimalPolynomial;
  using R = Mathematica::Abstract::Float<double>;

  constexpr auto N = 1000;
  constexpr auto M = 100;

  const auto points = Tabulate::trivial<R, N>(
      [](R x) { // NOLINT
        constexpr auto K = 3;
        return R(K * std::sin(x.value));
      },                //
      Interval<R>(-15, 15) //
  );

  // clang-format off
  auto line = Algorithm<R, N / M, Linear::TrendLine<R>>(Linear::trendLine<R, N / M>);
  auto pow = Algorithm<R, N / M, Power::Trend<R>>(Power::train<R, N / M>);
  auto exp = Algorithm<R, N / M, Exponential::Trend<R>>(Exponential::train<R, N / M>);
  auto log = Algorithm<R, N / M, Logarithmic::Trend<R>>(Logarithmic::train<R, N / M>);
  auto poly2 = Algorithm<R, N / M, Polynomial<R, 3>>(optimalPolynomial<R, 3, N / M>);
  auto poly3 = Algorithm<R, N / M, Polynomial<R, 4>>(optimalPolynomial<R, 4, N / M>);
  
  const auto algorithms = Array<Model<R, N / M>*, 5>({{ 
      &line, &pow, &exp, &log,
      &poly2
  }});
  // clang-format on

  auto optimal = ChoiceOptimal<R, N / M, 5>( // NOLINT
      algorithms,
      Score::R2<R, N / M, Mathematica::Function<R>>
  );

  auto partiton = PartitionModel<R, N, M>(optimal);
  const auto trend = partiton.trainedOn(points);
  const auto s = standartDeviation(trend, points);
  const auto r2 = Score::R2(trend, points);
  std::cout << "=== Approx::Partition ===" << std::endl;
  std::cout << "std   = " + s.asString() << std::endl;
  std::cout << "r2    = " + r2.asString() << std::endl;
}
