#include "Symatica/Core.hpp"
#include "Symatica/Expression/DSL/Literals.hpp"
#include "Symatica/Expression/DSL/Operators.hpp"
#include "Symatica/Expression/Expression.hpp"
#include "Symatica/Expression/Variable.hpp"
#include "Symatica/Symbol/TreeTable.hpp"
#include "Symatica/Visitor/Derivativer.hpp"
#include "Symatica/Visitor/Evaluator.hpp"
#include "Symatica/Visitor/Optimizer.hpp"
#include "math/eq/solve/SimpleIteration.hpp"
#include "math/eq/solve/function.hpp"
#include "math/eq/solve/half_division.hpp"
#include "math/eq/solve/interval.hpp"
#include "math/eq/solve/max.hpp"
#include "math/eq/solve/method.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <iterator>
#include <vector>

TEST(EqSolveTest, CompareAllOnSample) { // NOLINT
  constexpr auto EPS = 0.00001;
  using F = float;
  using namespace math::eq::solve; // NOLINT

  const auto f = function<F>([](F x) { // NOLINT
    return -0.38 * x * x * x           // NOLINT
           - 3.42 * x * x              // NOLINT
           + 2.51 * x                  // NOLINT
           + 8.75;                     // NOLINT
  });

  const auto intervals = std::vector<interval<F>>({
      interval<F>(-10, -5),
      interval<F>(-5, 0),
      interval<F>(0, 5),
  });

  const auto results = std::vector<F>({
      -9.44129,
      -1.35656,
      1.79785,
  });

  const auto tabulated_intervals = f.tabulate(interval<F>(-10, 5), 100);
  ASSERT_EQ(tabulated_intervals.size(), 3);
  for (auto result : results) {
    ASSERT_NE(
        (std::find_if(
            tabulated_intervals.begin(),
            tabulated_intervals.end(),
            [result](const interval<F>& interval) {
              return interval.contains(result);
            }
        )),
        tabulated_intervals.end()
    );
  }

  auto half_division_tracer = half_division::empty_tracer<F>();
  auto half_division_method
      = half_division::method<F, half_division::empty_tracer<F>>(
          EPS, half_division_tracer
      );

  const auto methods = std::vector<method<F>*>({
      &half_division_method,
  });

  for (std::size_t i = 0; i < intervals.size(); i++) {
    const auto& interval = intervals[i];
    const auto expected_result = results[i];
    for (auto* method : methods) {
      const auto actual_result = method->find_some_root(interval, f);
      ASSERT_NEAR(actual_result, expected_result, EPS);
    }
  }
}

using Symatica::Expression::DSL::operator+;
using Symatica::Expression::DSL::operator-;
using Symatica::Expression::DSL::operator*;
using Symatica::Expression::DSL::operator/;
using Symatica::Core::Ptr;
using Symatica::Expression::Expression;
using Symatica::Expression::Variable;
using Symatica::Expression::DSL::l;
using Symatica::Expression::DSL::pow;
using Symatica::Expression::DSL::var;

Ptr<Expression>
derivativeOf(const Ptr<Expression>& expression, Symatica::Core::Id varId) {
  auto make = Symatica::Visitor::Optimizer();
  auto basic = Symatica::Visitor::Derivativer(varId);
  return make.optimized(basic.derivativeOf(expression));
}

double evaluate(const Ptr<Expression>& expression, double x) {
  auto table = Symatica::Symbol::TreeTable({});
  auto eval = Symatica::Visitor::Evaluator(table);
  table.put(1, l(x));
  return eval.valueOf(expression);
}

TEST(EqSolveTest, SimpleIterationOnSample) { // NOLINT
  constexpr auto EPS = 0.00001;
  using F = float;
  using namespace math::eq::solve; // NOLINT

  const auto xId = 1;
  auto x = var(xId);

  const auto f = -l(0.38) * pow(x, l(3))  //
                 - l(3.42) * pow(x, l(2)) //
                 + l(2.51) * x            //
                 + l(8.75);
  const auto df = derivativeOf(f, xId);

  const auto lambda
      = -1
        / std::abs(math::eq::solve::max<F>(
            interval<F>(-5, 0), [=](F x) { return evaluate(df, x); }, 1000
        ));

  const auto phi = x + l(lambda) * f;
  ASSERT_NEAR(evaluate(phi, -1.35656), -1.35656, EPS);

  using Tracer = SimpleIteration::MarkdownTableTracer<F>;
  auto tracer = Tracer(std::cout);
  auto method = SimpleIteration::Method<F, Tracer>(EPS, tracer);

  auto root1 = method.findSomeRoot(-1, [=](F x) { return evaluate(phi, x); });
  auto root2 = method.findSomeRoot(-2, [=](F x) { return evaluate(phi, x); });

  ASSERT_NEAR(root1, root2, EPS);
  ASSERT_NEAR(evaluate(f, root1), 0, EPS);
  ASSERT_NEAR(evaluate(f, root2), 0, EPS);
}
