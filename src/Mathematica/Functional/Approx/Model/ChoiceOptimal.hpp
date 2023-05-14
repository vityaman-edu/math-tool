#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/Model/Core.hpp"
#include <algorithm>
#include <iostream>

namespace Mathematica::Functional::Approx::Model {

using Mathematica::Collection::Array;

template <Abstract::Real R, Count N>
using Score
    = Mapping<R(const Function<R>& predict, const Array<Point<R>, N>& points)>;

template <Abstract::Real R, Count N, Count M>
class ChoiceOptimal : public Model<R, N> {
public:
  explicit ChoiceOptimal(
      const Array<Model<R, N>*, M>& models, //
      const Score<R, N>& score
  )
      : models(models), score(score) {}

  Function<R> trainedOn(const Array<Point<R>, N>& points) override {
    const auto trends = Array<Function<R>, M>([*this, &points](auto i) {
      return models[i]->trainedOn(points);
    });

    const auto r2scores = Array<R, M>([*this, &trends, &points](auto i) {
      return score(trends[i], points);
    });

    const auto best = std::max_element(r2scores.begin(), r2scores.end());
    const auto bestIndex = best - r2scores.begin();
    return trends[bestIndex];
  }

private:
  Array<Model<R, N>*, M> models;
  Score<R, N> score;
};

}