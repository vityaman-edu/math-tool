#include "Mathematica/Algebra/Linear/Operation.hpp"
#include "Generator.hpp"
#include "Mathematica/Core.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;                  // NOLINT
using namespace Mathematica::Algebra::Linear; // NOLINT

static constexpr Size N = 10; // NOLINT
static constexpr int B = 100; // NOLINT
using T = int;

TEST(LinearOp, ScalarProduct) { // NOLINT
  auto left = randomVector<T, N>(-B, B);
  auto right = randomVector<T, N>(-B, B);

  T expectedProduct = 0;
  for (auto i = 0; i < N; i++) {
    expectedProduct += left[i] * right[i];
  }

  auto actualProduct = scalarProduct<T, N>(left, right);
  ASSERT_EQ(actualProduct, expectedProduct);
}

TEST(LinearOp, OperatorComposition) { // NOLINT
  // clang-format off
  auto left = Matrix<T, 2, 3>({{
    {1, 2, 3}, // NOLINT
    {4, 5, 6}, // NOLINT
  }});
  auto right = Matrix<T, 3, 2>({{
    {7 , 8 }, // NOLINT
    {9 , 10}, // NOLINT
    {11, 12}, // NOLINT
  }});

  auto expectedLApplyR = Matrix<T, 2, 2>({{
    {58 ,  64}, // NOLINT
    {139, 154}, // NOLINT
  }});

  auto expectedRApplyL = Matrix<T, 3, 3>({{
    {39, 54,  69}, // NOLINT
    {49, 68,  87}, // NOLINT
    {59, 82, 105}, // NOLINT
  }});
  // clang-format on

  auto actualLApplyR = left * right;
  auto actualRApplyL = right * left;

  ASSERT_EQ(actualLApplyR, expectedLApplyR);
  ASSERT_EQ(actualRApplyL, expectedRApplyL);
}

TEST(LinearOp, OperatorApplyVector) { // NOLINT
  // clang-format off
  auto scale = randomVector<T, N>(-B, B);
  auto scaleOp = Matrix<T, 3, 3>({{
    {scale[0], 0       , 0       },
    {0       , scale[1], 0       },
    {0       , 0       , scale[2]},
  }});
  // clang-format on
  auto originalVector = randomVector<T, 3>(-B, B);
  auto actualScaledVector = scaleOp * originalVector;

  auto expectedScaledVector = Vector<T, 3>([=](auto index) {
    return originalVector[index] * scale[index];
  });

  ASSERT_EQ(actualScaledVector, expectedScaledVector);
}