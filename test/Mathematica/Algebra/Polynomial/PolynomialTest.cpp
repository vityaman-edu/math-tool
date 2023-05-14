#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;           // NOLINT
using namespace Mathematica::Abstract; // NOLINT
using namespace Mathematica::Algebra;  // NOLINT
using Mathematica::Algebra::Linear::Vector;
using R = double;

TEST(Polynomial, Degree) { // NOLINT
  const auto a = Polynomial<Float<R>, 2>(Vector<Float<R>, 2>({0, 0}));
  const auto b = Polynomial<Float<R>, 2>(Vector<Float<R>, 2>({1, 1}));
  const auto c = Polynomial<Float<R>, 2>(Vector<Float<R>, 2>({0, 1}));
  const auto d
      = Polynomial<Float<R>, 7>(Vector<Float<R>, 7>({9, 0, 1, 0, 0, 0, 0}));
  const auto e
      = Polynomial<Float<R>, 7>(Vector<Float<R>, 7>({9, 0, 1, 0, 0, 0, 6}));

  ASSERT_EQ(a.degree(), PolynomialDegreeMinusInfty);
  ASSERT_EQ(b.degree(), 1);
  ASSERT_EQ(c.degree(), 1);
  ASSERT_EQ(d.degree(), 2);
  ASSERT_EQ(e.degree(), 6);
}

TEST(Polynomial, Evaluation) { // NOLINT
  const auto constant
      = Polynomial<Float<R>, 1>(Linear::Vector<Float<R>, 1>({5}));
  const auto parabola
      = Polynomial<Float<R>, 3>(Linear::Vector<Float<R>, 3>({-90, 213, 213.2}));
  for (Float<R> x = -10; x < 10; x += 0.2) { // NOLINT
    ASSERT_NEAR(constant(x).value, 5.0, 0.0001);

    const auto f = Float(213.2) * x * x + Float(213.0) * x - Float(90.0);
    ASSERT_NEAR(parabola(x).value, f.value, 0.0001);
  }
}

TEST(Polynomial, Multiplication) { // NOLINT
}
