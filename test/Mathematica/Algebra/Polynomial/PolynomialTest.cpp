#include "Mathematica/Algebra/Polynomial/Polynomial.hpp"
#include "Mathematica/Abstract/Field.hpp"
#include "Mathematica/Abstract/Float.hpp"
#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Mathematica/Core.hpp"
#include <gtest/gtest.h>
#include <tuple>
#include <utility>

using namespace Mathematica;           // NOLINT
using namespace Mathematica::Abstract; // NOLINT
using namespace Mathematica::Algebra;  // NOLINT
using Mathematica::Algebra::Linear::Vector;
using R = Float<double>;

template <Abstract::Field R, PolynomialDegree N>
Polynomial<R, N> poly(const Array<R, N>& a) {
  return Polynomial<R, N>(Vector<R, N>(a));
}

TEST(Polynomial, Degree) { // NOLINT
  const auto a = poly<R, 2>({0, 0});
  const auto b = poly<R, 2>({1, 1});
  const auto c = poly<R, 2>({0, 1});
  const auto d = poly<R, 7>({9, 0, 1, 0, 0, 0, 0});
  const auto e = poly<R, 7>({9, 0, 1, 0, 0, 0, 6});

  ASSERT_EQ(a.degree(), PolynomialDegreeMinusInfty);
  ASSERT_EQ(b.degree(), 1);
  ASSERT_EQ(c.degree(), 1);
  ASSERT_EQ(d.degree(), 2);
  ASSERT_EQ(e.degree(), 6);
}

TEST(Polynomial, Evaluation) { // NOLINT
  const auto constant = poly<R, 1>({5});
  const auto parabola = poly<R, 3>({-90, 213, 213.2});
  for (R x = -10; x < 10; x += 0.2) { // NOLINT
    ASSERT_NEAR(constant(x).value, 5.0, 0.0001);

    const auto f = Float(213.2) * x * x + Float(213.0) * x - Float(90.0);
    ASSERT_NEAR(parabola(x).value, f.value, 0.0001);
  }
}

template <Abstract::Field R, PolynomialDegree A, PolynomialDegree B>
void check(
    const Array<R, A>& a, // NOLINT
    const Array<R, B>& b,
    const Array<R, A + B - 1>& c
) {
  const auto pa = poly<R, A>(a);
  const auto pb = poly<R, B>(b);
  const auto pc = poly<R, A + B - 1>(c);
  ASSERT_EQ(pa * pb, pc);
}

TEST(Polynomial, Multiplication) {                                // NOLINT
  check<R, 2, 2>({5, 1}, {-1, 2}, {-5, 9, 2});                    // NOLINT
  check<R, 2, 2>({-2, 3}, {-5, 2}, {10, -19, 6});                 // NOLINT
  check<R, 2, 3>({2, 2}, {-6, 5, 1}, {-12, -2, 12, 2});           // NOLINT
  check<R, 3, 2>({-1, 1, 2}, {1, 2}, {-1, -1, 4, 4});             // NOLINT
  check<R, 1, 3>({3}, {4, -5, 2}, {12, -15, 6});                  // NOLINT
  check<R, 4, 3>({4, 5, 0, 2}, {1, 2, 2}, {4, 13, 18, 12, 4, 4}); // NOLINT
}
