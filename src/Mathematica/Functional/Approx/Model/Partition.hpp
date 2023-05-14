#pragma once

#include "Mathematica/Abstract/Real.hpp"
#include "Mathematica/Collection/Array.hpp"
#include "Mathematica/Common/Interval.hpp"
#include "Mathematica/Core.hpp"
#include "Mathematica/Functional/Approx/Model/Core.hpp"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

namespace Mathematica::Functional::Approx::Model {

using Mathematica::Collection::Array;

template <Abstract::Real R, Count N, Count M>
class PartitionModel : public Model<R, N> {
public:
  explicit PartitionModel(Model<R, N / M>& model) : model(model) {}

  // points must be sorted by x
  // TODO: create class for such partial functions
  Function<R> trainedOn(const Array<Point<R>, N>& points) override {
    std::vector<std::pair<Interval<R>, Function<R>>> fragments;
    for (auto i = 0; i < M; i++) {
      const auto chosen = Array<Point<R>, N / M>([i, &points](auto j) {
        return points[N / M * i + j];
      });
      const auto fragment = model.trainedOn(chosen);
      fragments.emplace_back(Interval(chosen[0].x, chosen[N / M - 1].x), fragment);
    }
    return [fragments](R x) {
      for (const auto& [interval, fragment] : fragments) {
        if (interval.contains(x)) {
          return fragment(x);
        }
      }
      if (x <= fragments[0].first.left()) {
        return fragments[0].second(x);
      }
      return fragments[fragments.size() - 1].second(x);
    };
  }

private:
  Model<R, N / M>& model;
};

}