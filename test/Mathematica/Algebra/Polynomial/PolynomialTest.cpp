#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;          // NOLINT
using namespace Mathematica::Algebra; // NOLINT
using F = double;
constexpr F EPS = 0.00000001;

TEST(Polynomial, Degree) { // NOLINT
  const auto a = Polynomial<F, 2>(Linear::Vector<F, 2>({0, 0}));
  const auto b = Polynomial<F, 2>(Linear::Vector<F, 2>({1, 1}));
  const auto c = Polynomial<F, 2>(Linear::Vector<F, 2>({0, 1}));
  const auto d = Polynomial<F, 7>(Linear::Vector<F, 7>({9, 0, 1, 0, 0, 0, 0}));
  const auto e = Polynomial<F, 7>(Linear::Vector<F, 7>({9, 0, 1, 0, 0, 0, 6}));

  ASSERT_EQ(a.degree(), PolynomialDegreeMinusInfty);
  ASSERT_EQ(b.degree(), 1);
  ASSERT_EQ(c.degree(), 1);
  ASSERT_EQ(d.degree(), 2);
  ASSERT_EQ(e.degree(), 6);
}

TEST(Polynomial, Evaluation) { // NOLINT
  const auto constant = Polynomial<F, 1>(Linear::Vector<F, 1>({5}));
  const auto parabola
      = Polynomial<F, 3>(Linear::Vector<F, 3>({-90, 213, 213.2}));
  for (F x = -10; x < 10; x += 0.2) { // NOLINT
    ASSERT_NEAR(constant(x), 5, EPS);
    ASSERT_NEAR(parabola(x), (213.2 * x * x + 213 * x - 90), EPS);
  }
}

TEST(Polynomial, Multiplication) { // NOLINT
}
