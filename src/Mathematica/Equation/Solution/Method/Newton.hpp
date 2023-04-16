#pragma once

#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/FunctionAnalysis.hpp"
#include "Mathematica/Common/Interval.hpp"
#include <cassert>
#include <cmath>
#include <ostream>

namespace Mathematica::Equation::Solution::Method::Newton {

template <typename T>
class Tracer {
public:
  virtual void onStart() = 0;
  virtual void onIteration(T x, T fx, T dfx, T y, T diff) = 0;
  virtual void onEnd() = 0;
  virtual ~Tracer() = default;
};

template <typename T>
class EmptyTracer : public Tracer<T> {
public:
  void onStart() override{};
  void onIteration(T x, T fx, T dfx, T y, T diff) override{}; // NOLINT
  void onEnd() override{};
};

template <typename T>
class MarkdownTableTracer : public Tracer<T> {
public:
  explicit MarkdownTableTracer(std::ostream& out) : out(out) {}

  void onStart() override {
    printedRowsCount = 0;
    out << "| n | x | fx | dfx | y | diff |" << '\n'
        << "|---|---|----|-----|---|------|" << '\n';
  }

  void onIteration(T x, T fx, T dfx, T y, T diff) override { // NOLINT
    out << '|' << ++printedRowsCount << '|'                  //
        << x << '|' << fx << '|' << dfx << '|'               //
        << y << '|' << diff << '|' << '\n';
  }

  void onEnd() override {}

private:
  std::ostream& out;
  std::size_t printedRowsCount = 0;
};

template <typename T, class Tracer>
class Executor {
public:
  explicit Executor(T epsilon, Tracer& tracer)
      : tracer(tracer), epsilon(epsilon) {}

  bool accepts(
      Interval<T> scope,
      Function<Real> f,  // NOLINT
      Function<Real> df, // NOLINT
      Function<Real> ddf // NOLINT
  ) {
    return isDefinitelyRootInside(scope, f)
           && constSign(scope, 0.0001, df)   // NOLINT TODO: pass as parameter
           && constSign(scope, 0.0001, ddf); // NOLINT TODO: pass as parameter
  }

  T findSomeRoot(
      Interval<T> scope,
      Function<Real> f,  // NOLINT
      Function<Real> df, // NOLINT
      Function<Real> ddf // NOLINT
  ) {
    assert(accepts(scope, f, df, ddf));
    
    tracer.onStart();

    auto prev = (                                 //
        (f(scope.left() * ddf(scope.left())) > 0) //
            ? (scope.left() + epsilon)
            : (scope.right() - epsilon)
    );

    while (true) {
      assert(df(prev) != 0);
      auto next = prev - f(prev) / df(prev);

      tracer.onIteration( //
          prev,
          f(prev),
          df(prev),
          next,
          std::abs(next - prev)
      );

      if (std::abs(next - prev) < epsilon) {
        break;
      }

      prev = next;
    }

    tracer.onEnd();
    return prev;
  }

private:
  Tracer& tracer;
  T epsilon;
};

}