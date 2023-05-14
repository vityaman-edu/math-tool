#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include <concepts>

namespace Mathematica::Functional::Approx::Model {

using Mathematica::Collection::Array;

template <Abstract::Real R, Count N>
class Model {
public:
  virtual Function<R> trainedOn(const Array<Point<R>, N>& points) = 0;
};

template <Abstract::Real R, Count N, typename Predictor>
class Algorithm : public Model<R, N> {
public:
  explicit Algorithm(const Mapping<Predictor(const Array<Point<R>, N>&)>& method)
      : method(method) {}

  Function<R> trainedOn(const Array<Point<R>, N>& points) override {
    const auto trend = method(points);
    return [trend](R x) { return trend(x); };
  }

private:
  Mapping<Predictor(const Array<Point<R>, N>&)> method;
};

}