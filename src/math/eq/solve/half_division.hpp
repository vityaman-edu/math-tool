#pragma once
#include "method.hpp"
#include <cassert>
#include <functional>
#include <ostream>

namespace math::eq::solve::half_division {

template <typename T>
class tracer {
public:
  virtual void on_start() = 0;
  virtual void on_iteration(T a, T b, T x, T fa, T fb, T fx, T ab) = 0;
  virtual void on_end() = 0;
};

template <typename T>
class empty_tracer : public tracer<T> {
public:
  void on_start() override {}
  void on_iteration(T a, T b, T x, T fa, T fb, T fx, T ab) // NOLINT
      override {}
  void on_end() override {}
};

template <typename T>
class md_table_tracer : public tracer<T> {
public:
  explicit md_table_tracer(std::ostream& out) : out(out) {}

  void on_start() override {
    out << "| n | a | b | x | f(a) | f(b) | f(x) | b - a |" << '\n'
        << "|---|---|---|---|------|------|------|-------|" << '\n';
  }

  void on_iteration(T a, T b, T x, T fa, T fb, T fx, T ab) // NOLINT
      override {
    out << '|' << ++n << '|' << a << '|' << b << '|' << x   //
        << '|' << fa << '|' << fb << '|' << fx << '|' << ab //
        << '|' << '\n';
  }

  void on_end() override {}

private:
  std::ostream& out;
  std::size_t n = 0;
};

template <typename T, class Tracer>
class method : public math::eq::solve::method<T> {
public:
  explicit method(T epsilon, Tracer& tracer)
      : tracer(tracer), epsilon(epsilon) {}

  T find_some_root(interval<T> interval, function<T> function) override {
    assert(function.exactly_has_root_inside(interval));
    tracer.on_start();
    while (true) {
      auto left = interval.left_from(interval.middle());
      auto right = interval.right_from(interval.middle());
      if (function.exactly_has_root_inside(left)) {
        interval = left;
      } else {
        interval = right;
      }
      tracer.on_iteration(
          interval.left(),
          interval.right(),
          interval.middle(),
          function(interval.left()),
          function(interval.right()),
          function(interval.middle()),
          interval.length()
      );
      if (interval.length() < epsilon) {
        tracer.on_end();
        return interval.middle();
      }
    };
  }

private:
  Tracer& tracer;
  T epsilon;
};

}