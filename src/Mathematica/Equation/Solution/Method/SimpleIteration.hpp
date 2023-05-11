#pragma once

#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/FunctionAnalysis.hpp"
#include "Mathematica/Common/Interval.hpp"
#include <ostream>

namespace Mathematica::Equation::Solution::Method::SimpleIteration {

template <typename T>
class Tracer {
public:
  virtual void onStart() = 0;
  virtual void onIteration(T prev, T next, T fNext, T diff) = 0;
  virtual void onEnd() = 0;
};

template <typename T>
class EmptyTracer : public Tracer<T> {
public:
  void onStart() override {}
  void onIteration(T prev, T next, T fNext, T diff) override {}
  void onEnd() override {}
};

template <typename T>
class MarkdownTableTracer : Tracer<T> {
public:
  explicit MarkdownTableTracer(std::ostream& out) : out(out) {}

  void onStart() override {
    printedRowsCount = 0;
    out << "| n | prev | next | f(next) | b - a |" << '\n'
        << "|---|------|------|---------|-------|" << '\n';
  }

  void onIteration(T prev, T next, T fNext, T diff) override {
    out << '|' << ++printedRowsCount << '|' << prev << '|' << next //
        << '|' << fNext << '|' << diff << '|' << '\n';
  }

  void onEnd() override {}

private:
  std::ostream& out;
  std::size_t printedRowsCount = 0;
};

template <typename T>
Function<T> buildPhiFrom(
    Interval<T> scope, const Function<T>& f, const Function<T>& df
) noexcept {
  auto lambda = -1 / max<T>(scope, 0.0001, [&df](T x) { // TODO: hardcoded value
    return std::abs(df(x));
  });
  return [f, lambda](T x) { return x + lambda * f(x); };
}

template <typename T>
Function<T> buildDPhiFrom(Interval<T> scope, const Function<T>& df) noexcept {
  auto lambda = -1 / max<T>(scope, 0.0001, [&df](T x) { // TODO: hardcoded value
    return std::abs(df(x));
  });
  return [df, lambda](T x) { return 1 + lambda * df(x); };
}

template <typename T, class Tracer>
class Executor {
public:
  explicit Executor(T epsilon, Tracer& tracer)
      : tracer(tracer), epsilon(epsilon) {}

  bool accepts(Interval<T> scope, const Function<T>& dphi) {
    // TODO: hardcoded value
    auto absmax
        = max<T>(scope, 0.0001, [&dphi](T x) { return std::abs(dphi(x)); });
    return absmax < 1;
  }

  T findSomeRoot(T prev, const Function<T>& phi) {

    tracer.onStart();

    auto next = phi(prev);
    for (int i = 0; i < 100; i++) {
      tracer.onIteration(prev, next, phi(next), std::abs(next - prev));

      if (std::abs(next - prev) < epsilon) {
        break;
      }

      prev = next;
      next = phi(next);
    }

    tracer.onEnd();

    return next;
  }

private:
  Tracer& tracer;
  T epsilon;
};

}