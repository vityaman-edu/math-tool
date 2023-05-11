#pragma once

#include "Mathematica/Abstract/Field.hpp"
#include "Mathematica/Algebra/Linear/Eq/GaussSolver.hpp"
#include "Mathematica/Algebra/Linear/Matrix.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
#include "Mathematica/Common/Point.hpp"
#include "Mathematica/Core.hpp"
#include <cmath>

namespace Mathematica::Functional::Approx::LeastSqare {

template <Abstract::Field F, Algebra::PolynomialDegree D, Count N>
Algebra::Linear::Matrix<F, D, D> buildMatrix(const Array<Point<F>, N>& points
) noexcept {
  //     0 1 2 3
  //     -------
  // 0 | 0 1 2 3
  // 1 | 1 2 3 4
  // 2 | 2 3 4 5
  // 3 | 3 4 5 6
  auto sums = Array<F, 2 * D - 1>();
  sums.fill(0);
  for (auto i = 0; i < 2 * D - 1; i++) {
    for (const auto point : points) {
      sums[i] += point.x.pow(i);
    }
  }
  return Algebra::Linear::Matrix<F, D, D>([&sums](auto i, auto j) {
    return sums[i + j];
  });
}

template <Abstract::Field F, Algebra::PolynomialDegree D, Count N>
Algebra::Linear::Vector<F, D> buildVector( //
    const Array<Point<F>, N>& points
) {
  return Algebra::Linear::Vector<F, D>([&](auto i) {
    auto value = F::zero();
    for (const auto point : points) {
      value += point.x.pow(i) * point.y;
    }
    return value;
  });
}

template <Abstract::Field F, Algebra::PolynomialDegree D, Count N>
Algebra::Polynomial<F, D> optimalPolynomial( //
    const Array<Point<F>, N>& points
) noexcept {
  const auto matrix = buildMatrix<F, D, N>(points);
  const auto vector = buildVector<F, D, N>(points);
  const auto gauss = Algebra::Linear::Eq::GaussSolver<F, D>();
  const auto coefficients = gauss.solve({matrix, vector}).value;
  return Algebra::Polynomial<F, D>(coefficients);
}

}
