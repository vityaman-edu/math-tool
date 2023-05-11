#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;           // NOLINT
using namespace Mathematica::Abstract; // NOLINT
using namespace Mathematica::Algebra;  // NOLINT
using Mathematica::Algebra::Linear::Vector;
using F = double;

TEST(Polynomial, Degree) { // NOLINT
  const auto a = Polynomial<Float<F>, 2>(Vector<Float<F>, 2>({0, 0}));
  const auto b = Polynomial<Float<F>, 2>(Vector<Float<F>, 2>({1, 1}));
  const auto c = Polynomial<Float<F>, 2>(Vector<Float<F>, 2>({0, 1}));
  const auto d
      = Polynomial<Float<F>, 7>(Vector<Float<F>, 7>({9, 0, 1, 0, 0, 0, 0}));
  const auto e
      = Polynomial<Float<F>, 7>(Vector<Float<F>, 7>({9, 0, 1, 0, 0, 0, 6}));

  ASSERT_EQ(a.degree(), PolynomialDegreeMinusInfty);
  ASSERT_EQ(b.degree(), 1);
  ASSERT_EQ(c.degree(), 1);
  ASSERT_EQ(d.degree(), 2);
  ASSERT_EQ(e.degree(), 6);
}

TEST(Polynomial, Evaluation) { // NOLINT
  const auto constant
      = Polynomial<Float<F>, 1>(Linear::Vector<Float<F>, 1>({5}));
  const auto parabola
      = Polynomial<Float<F>, 3>(Linear::Vector<Float<F>, 3>({-90, 213, 213.2}));
  for (Float<F> x = -10; x < 10; x += 0.2) { // NOLINT
    ASSERT_EQ(constant(x), Float(5.0));

    const auto f = Float(213.2) * x * x + Float(213.0) * x - Float(90.0);
    ASSERT_EQ(parabola(x), f);
  }
}

TEST(Polynomial, Multiplication) { // NOLINT
}
