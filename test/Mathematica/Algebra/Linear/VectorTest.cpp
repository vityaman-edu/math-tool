#include "Mathematica/Algebra/Linear/Vector.hpp"
#include "Generator.hpp"

#include <array>
#include <cstddef>
#include <gtest/gtest.h>

using Mathematica::Algebra::Linear::Vector;

static constexpr std::size_t N = 10; // NOLINT
static constexpr int B = 100;   // NOLINT
using R = double;

TEST(Vector, CreateFromArray) { // NOLINT
  auto data = randomArray<R, N>(-B, B);
  auto vec = Vector<Float<R>, N>(data);
  for (auto i = 0; i < N; i++) {
    ASSERT_EQ(vec[i], data[i]);
  }
}

TEST(Vector, Copy) { // NOLINT
  auto input = randomVector<R, N>(-B, B);
  auto copy = input;

  auto index = randomSize(N);
  auto new_value = randomInt(-B, B);
  auto was_value = input[index];
  input[index] = new_value;

  ASSERT_EQ(input[index], new_value);
  ASSERT_EQ(copy[index], was_value);
}

TEST(Vector, AddSub) { // NOLINT
  auto left = randomVector<R, N>(-B, B);
  auto right = randomVector<R, N>(-B, B);

  auto expected_sum = Vector<Float<R>, N>([=](size_t index) {
    return left[index] + right[index];
  });

  auto expected_diff = Vector<Float<R>, N>([=](size_t index) {
    return left[index] - right[index];
  });

  ASSERT_EQ(left + right, expected_sum);
  ASSERT_EQ(right + left, expected_sum);
  ASSERT_EQ(left - right, expected_diff);
  ASSERT_NE(right - left, expected_diff);
}

TEST(Vector, MultOnScalar) { // NOLINT
  auto input = randomVector<R, N>(-B, B);
  auto scalar = randomInt(-B, B);

  auto actual = input * scalar;

  auto expected = Vector<Float<R>, N>([=](size_t index) {
    return input[index] * scalar;
  });

  ASSERT_EQ(actual, expected);
}
