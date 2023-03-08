#include "generator.hpp"
#include "math/linal/vector.hpp"
#include <array>
#include <cstddef>
#include <gtest/gtest.h>

using math::linal::vector;

constexpr size_t N = 10; // NOLINT
constexpr int B = 100;   // NOLINT
using T = int;

TEST(Vector, CreateFromArray) {
  auto data = random_array<T, N>(-B, B);
  auto vec = vector<T, N>(data);
  for (size_t i = 0; i < N; i++) {
    ASSERT_EQ(vec[i], data[i]);
  }
}

TEST(Vector, Copy) {
  auto input = random_vector<T, N>(-B, B);
  auto copy = input;

  auto index = random_size(N);
  auto new_value = random_int(-B, B);
  auto was_value = input[index];
  input[index] = new_value;

  ASSERT_EQ(input[index], new_value);
  ASSERT_EQ(copy[index], was_value);
}

TEST(Vector, AddSub) {
  auto left = random_vector<T, N>(-B, B);
  auto right = random_vector<T, N>(-B, B);

  auto expected_sum = vector<T, N>::zero();
  for (size_t i = 0; i < N; i++) {
    expected_sum[i] = left[i] + right[i];
  }

  auto expected_diff = vector<T, N>::zero();
  for (size_t i = 0; i < N; i++) {
    expected_diff[i] = left[i] - right[i];
  }

  ASSERT_EQ(left + right, expected_sum);
  ASSERT_EQ(right + left, expected_sum);
  ASSERT_EQ(left - right, expected_diff);
  ASSERT_NE(right - left, expected_diff);
}

TEST(Vector, MultOnScalar) {
  auto input = random_vector<T, N>(-B, B);
  auto scalar = random_int(-B, B);

  auto actual = input * scalar;

  auto expected = vector<T, N>::zero();
  for (size_t i = 0; i < N; i++) {
    expected[i] = input[i] * scalar;
  }

  ASSERT_EQ(actual, expected);
}
