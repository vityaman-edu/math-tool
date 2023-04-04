#pragma once

#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/FunctionAnalysis.hpp"
#include "Mathematica/Equation/Solution/Method/Interval.hpp"
#include <iomanip>
#include <ostream>

namespace Mathematica::Equation::Solution::Method::HalfDivision {

template <typename T>
class Tracer {
public:
  virtual void onStart() = 0;
  virtual void onIteration(T a, T b, T x, T fa, T fb, T fx, T ab) = 0;
  virtual void onEnd() = 0;
  virtual ~Tracer() = default;
};

template <typename T>
class EmptyTracer : public Tracer<T> {
public:
  void onStart() override{};
  void onIteration(T a, T b, T x, T fa, T fb, T fx, T ab) override{}; // NOLINT
  void onEnd() override{};
};

template <typename T>
class MardownTableTracer : public Tracer<T> {
public:
  explicit MardownTableTracer(std::ostream& out) : out(out) {}

  void onStart() override {
    printedRowsCount = 0;
    out << "| n | a | b | x | f(a) | f(b) | f(x) | b - a |" << '\n'
        << "|---|---|---|---|------|------|------|-------|" << '\n';
  }

  void onIteration(T a, T b, T x, T fa, T fb, T fx, T ab) override {
    out << '|' << ++printedRowsCount << '|' //
        << a << '|' << b << '|' << x << '|' //
        << fa << '|' << fb << '|' << fx     //
        << '|' << ab << '|' << '\n';
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

  T findSomeRoot(Interval<T> scope, Function<Real> f) {
    assert(isDefinitelyRootInside(scope, f));

    tracer.onStart();

    while (true) {
      auto left = scope.leftFrom(scope.middle());
      auto right = scope.rightFrom(scope.middle());
      if (isDefinitelyRootInside(left, f)) {
        scope = left;
      } else {
        scope = right;
      }

      tracer.onIteration(
          scope.left(),
          scope.right(),
          scope.middle(),
          f(scope.left()),
          f(scope.right()),
          f(scope.middle()),
          scope.length()
      );

      if (scope.length() < epsilon) {
        break;
      }
    };

    tracer.onEnd();
    return scope.middle();
  }

private:
  Tracer& tracer;
  T epsilon;
};

}
