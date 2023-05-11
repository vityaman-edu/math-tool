#include "generator.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <array>
#include <cstddef>
#include <gtest/gtest.h>

using math::linal::Matrix;

static constexpr size_t N = 10; // NOLINT
static constexpr size_t M = 15; // NOLINT
static constexpr int B = 100;   // NOLINT
using F = int;

TEST(matrix, CreateFromMArray) {
  auto data = random_array_2d<F, N, M>(-B, B);
  auto mat = Matrix<F, N, M>(data);
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      ASSERT_EQ(mat[i][j], data[i][j]);
    }
  }
}

TEST(matrix, Copy) {
  auto input = random_matrix<F, N, M>(-B, B);
  auto copy = input;

  auto index = random_size(N);
  auto new_value = random_vector<F, M>(-B, B);
  auto was_value = input[index];
  input[index] = new_value;

  ASSERT_EQ(input[index], new_value);
  ASSERT_EQ(copy[index], was_value);
}

TEST(matrix, AddSub) {
  auto left = random_matrix<F, N, M>(-B, B);
  auto right = random_matrix<F, N, M>(-B, B);

  auto expected_sum = Matrix<F, N, M>([=](size_t row, size_t col) {
    return left[row][col] + right[row][col];
  });

  auto expected_diff = Matrix<F, N, M>([=](size_t row, size_t col) {
    return left[row][col] - right[row][col];
  });

  ASSERT_EQ(left + right, expected_sum);
  ASSERT_EQ(right + left, expected_sum);
  ASSERT_EQ(left - right, expected_diff);
  ASSERT_NE(right - left, expected_diff);
}

TEST(matrix, MultOnScalar) {
  auto input = random_matrix<F, N, M>(-B, B);
  auto scalar = random_int(-B, B);

  auto actual = input * scalar;

  auto expected = Matrix<F, N, M>([=](size_t row, size_t col) {
    return input[row][col] * scalar;
  });

  ASSERT_EQ(actual, expected);
}

TEST(matrix, SwapRows) {
  auto input = random_matrix<F, N, M>(-B, B);

  for (size_t i = 0; i < N; i++) {
    auto copy = input;
    auto row_1 = random_size(N);
    auto row_2 = random_size(N);
    copy.swap_rows(row_1, row_2);
    ASSERT_EQ(copy[row_1], input[row_2]);
    ASSERT_EQ(copy[row_2], input[row_1]);
  }
}
