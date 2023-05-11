#pragma once

#include "math/func/function.hpp"
#include <cmath>
#include <ostream>
#include <type_traits>

namespace math::eq::solve::SimpleIteration {

template <typename T>
class Tracer {
public:
  virtual void onStart() = 0;
  virtual void onIteration(T prev, T next, T fNext, T diff) = 0;
  virtual void onEnd() = 0;
};

template <typename T>
class MarkdownTableTracer : Tracer<T> {
public:
  explicit MarkdownTableTracer(std::ostream& out) : out(out) {}

  void onStart() override {
    out << "| n | prev | next | f(next) | b - a |" << '\n'
        << "|---|------|------|---------|-------|" << '\n';
  }

  void onIteration(T prev, T next, T fNext, T diff) override {
    out << '|' << ++n << '|' << prev << '|' << next //
        << '|' << fNext << '|' << diff << '|' << '\n';
  }

  void onEnd() override {}

private:
  std::ostream& out;
  std::size_t n = 0;
};

template <typename T, class Tracer>
class Method {
public:
  explicit Method(T epsilon, Tracer& tracer)
      : tracer(tracer), epsilon(epsilon) {}

  T findSomeRoot(T prev, function<T, T> phi) {
    tracer.onStart();
    auto next = phi(prev);
    for (int i = 0; i < 100; i++) {
      tracer.onIteration(prev, next, phi(next), std::abs(next - prev));
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