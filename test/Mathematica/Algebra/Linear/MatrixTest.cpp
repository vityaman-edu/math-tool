#include "Generator.hpp"
#include "Mathematica/Core.hpp"
#include <gtest/gtest.h>

using namespace Mathematica;                  // NOLINT
using namespace Mathematica::Algebra::Linear; // NOLINT

static constexpr Size N = 10; // NOLINT
static constexpr Size M = 15; // NOLINT
static constexpr int B = 100; // NOLINT
using R = double;

TEST(Matrix, CreateFromMArray) { // NOLINT
  auto data = randomArray2D<R, N, M>(-B, B);
  auto mat = Matrix<Float<R>, N, M>(data);
  for (auto i = 0; i < N; i++) {
    for (auto j = 0; j < M; j++) {
      ASSERT_EQ(mat[i][j], data[i][j]);
    }
  }
}

TEST(Matrix, Copy) { // NOLINT
  auto input = randomMatrix<R, N, M>(-B, B);
  auto copy = input;

  auto index = randomSize(N);
  auto newValue = randomVector<R, M>(-B, B);
  auto wasValue = input[index];
  input[index] = newValue;

  ASSERT_EQ(input[index], newValue);
  ASSERT_EQ(copy[index], wasValue);
}

TEST(Matrix, AddSub) { // NOLINT
  auto left = randomMatrix<R, N, M>(-B, B);
  auto right = randomMatrix<R, N, M>(-B, B);

  auto expectedSum = Matrix<Float<R>, N, M>([=](auto i, auto j) {
    return left[i][j] + right[i][j];
  });

  auto expectedDiff = Matrix<Float<R>, N, M>([=](auto i, auto j) {
    return left[i][j] - right[i][j];
  });

  ASSERT_EQ(left + right, expectedSum);
  ASSERT_EQ(right + left, expectedSum);
  ASSERT_EQ(left - right, expectedDiff);
  ASSERT_NE(right - left, expectedDiff);
}

TEST(Matrix, MultOnScalar) { // NOLINT
  auto input = randomMatrix<R, N, M>(-B, B);
  auto scalar = randomInt(-B, B);

  auto actual = input * scalar;

  auto expected = Matrix<Float<R>, N, M>([=](auto i, auto j) { //
    return input[i][j] * scalar;
  });

  ASSERT_EQ(actual, expected);
}

TEST(Matrix, SwapRows) { // NOLINT
  auto input = randomMatrix<R, N, M>(-B, B);

  for (auto i = 0; i < N; i++) {
    auto copy = input;
    auto row1 = randomSize(N);
    auto row2 = randomSize(N);
    copy.swapRows(row1, row2);
    ASSERT_EQ(copy[row1], input[row2]);
    ASSERT_EQ(copy[row2], input[row1]);
  }
}
