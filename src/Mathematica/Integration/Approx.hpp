#pragma once

#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Common/Partition.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Integration/Cotes.hpp"
#include <cmath>
#include <ostream>

namespace Mathematica::Integration {

template <typename T>
class Tracer {
public:
  virtual void onStart() = 0;
  virtual void onIteration(Size size, T prev, T curr, T diff) = 0;
  virtual void onEnd() = 0;
  virtual ~Tracer() = default;
};

template <typename T>
class EmptyTracer : public Tracer<T> {
public:
  void onStart() override{};
  void onIteration(Size size, T prev, T curr, T diff) override{}; // NOLINT
  void onEnd() override{};
};

template <typename T>
class MarkdownTableTracer : public Tracer<T> {
public:
  explicit MarkdownTableTracer(std::ostream& out) : out(out) {}

  void onStart() override {
    printedRowsCount = 0;
    out << "| n | size | prev | curr | diff |" << '\n'
        << "|---|------|------|------|------|" << '\n';
  }

  void onIteration(Size size, T prev, T curr, T diff) override { // NOLINT
    out << '|' << ++printedRowsCount << '|'                      //
        << size << '|' << prev << '|' << curr << '|'             //
        << diff << '|' << '\n';
  }

  void onEnd() override { printedRowsCount = 0; }

private:
  std::ostream& out;
  std::size_t printedRowsCount = 0;
};

template <typename T, class Tracer>
class Approx {
public:
  explicit Approx(T epsilon, Cotes<T> cotes, Tracer tracer)
      : epsilon(epsilon), cotes(cotes), tracer(tracer) {}

  T integrate(Function<T> f, Interval<T> scope) {
    tracer.onStart();
    auto size = 4;
    auto prev = cotes.areaUnderGraph(f, Partition<T>(scope, size));
    while (true) {
      size *= 2;
      auto curr = cotes.areaUnderGraph(f, Partition<T>(scope, size));
      tracer.onIteration(size, prev, curr, std::abs(prev - curr));
      if (std::abs(prev - curr) < epsilon) {
        tracer.onEnd();
        return curr;
      }
      prev = curr;
    };
  }

private:
  T epsilon;
  Cotes<T> cotes;
  Tracer tracer;
};

template <typename T, class Tracer>
class ApproxFactory {
public:
  explicit ApproxFactory(T epsilon, Tracer tracer)
      : epsilon(epsilon), tracer(tracer) {}

  Approx<T, Tracer> of(Cotes<T> cotes) const noexcept {
    return Approx<T, Tracer>(epsilon, cotes, tracer);
  }

  Approx<T, Tracer> of(TrivialMethod<T> trivial) const noexcept {
    return Approx<T, Tracer>(epsilon, Cotes(trivial), tracer);
  }

private:
  T epsilon;
  Tracer tracer;
};

}