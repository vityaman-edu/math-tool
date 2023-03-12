#include "generator.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <array>
#include <cstddef>
#include <gtest/gtest.h>

using math::linal::matrix;

static constexpr size_t N = 10; // NOLINT
static constexpr size_t M = 15; // NOLINT
static constexpr int B = 100;   // NOLINT
using T = int;

TEST(Matrix, CreateFromMArray) {
  auto data = random_array2d<T, N, M>(-B, B);
  auto mat = matrix<T, N, M>(data);
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < M; j++) {
      ASSERT_EQ(mat[i][j], data[i][j]);
    }
  }
}

TEST(Matrix, Copy) {
  auto input = random_matrix<T, N, M>(-B, B);
  auto copy = input;

  auto index = random_size(N);
  auto new_value = random_vector<T, M>(-B, B);
  auto was_value = input[index];
  input[index] = new_value;

  ASSERT_EQ(input[index], new_value);
  ASSERT_EQ(copy[index], was_value);
}

TEST(Matrix, AddSub) {
  auto left = random_matrix<T, N, M>(-B, B);
  auto right = random_matrix<T, N, M>(-B, B);

  auto expected_sum
      = matrix<T, N, M>([=](size_t row, size_t col) {
          return left[row][col] + right[row][col];
        });

  auto expected_diff
      = matrix<T, N, M>([=](size_t row, size_t col) {
          return left[row][col] - right[row][col];
        });

  ASSERT_EQ(left + right, expected_sum);
  ASSERT_EQ(right + left, expected_sum);
  ASSERT_EQ(left - right, expected_diff);
  ASSERT_NE(right - left, expected_diff);
}

TEST(Matrix, MultOnScalar) {
  auto input = random_matrix<T, N, M>(-B, B);
  auto scalar = random_int(-B, B);

  auto actual = input * scalar;

  auto expected = matrix<T, N, M>([=](size_t row, size_t col) {
    return input[row][col] * scalar;
  });

  ASSERT_EQ(actual, expected);
}
