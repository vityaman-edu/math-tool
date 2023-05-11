#include "generator.hpp"
#include "math/linal/vector.hpp"
#include <array>
#include <cstddef>
#include <gtest/gtest.h>

using math::linal::Vector;

static constexpr size_t N = 10; // NOLINT
static constexpr int B = 100;   // NOLINT
using T = int;

TEST(vector, CreateFromArray) {
  auto data = random_array<T, N>(-B, B);
  auto vec = Vector<T, N>(data);
  for (size_t i = 0; i < N; i++) {
    ASSERT_EQ(vec[i], data[i]);
  }
}

TEST(vector, Copy) {
  auto input = random_vector<T, N>(-B, B);
  auto copy = input;

  auto index = random_size(N);
  auto new_value = random_int(-B, B);
  auto was_value = input[index];
  input[index] = new_value;

  ASSERT_EQ(input[index], new_value);
  ASSERT_EQ(copy[index], was_value);
}

TEST(vector, AddSub) {
  auto left = random_vector<T, N>(-B, B);
  auto right = random_vector<T, N>(-B, B);

  auto expected_sum = Vector<T, N>([=](size_t index) {
    return left[index] + right[index];
  });

  auto expected_diff = Vector<T, N>([=](size_t index) {
    return left[index] - right[index];
  });

  ASSERT_EQ(left + right, expected_sum);
  ASSERT_EQ(right + left, expected_sum);
  ASSERT_EQ(left - right, expected_diff);
  ASSERT_NE(right - left, expected_diff);
}

TEST(vector, MultOnScalar) {
  auto input = random_vector<T, N>(-B, B);
  auto scalar = random_int(-B, B);

  auto actual = input * scalar;

  auto expected = Vector<T, N>([=](size_t index) {
    return input[index] * scalar;
  });

  ASSERT_EQ(actual, expected);
}
