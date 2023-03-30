#include "generator.hpp"
#include "math/linal/basic_op.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <array>
#include <cstddef>
#include <gtest/gtest.h>

using math::linal::matrix;
using math::linal::scalar_product;
using math::linal::vector;

static constexpr size_t N = 10; // NOLINT
static constexpr int B = 100;   // NOLINT
using T = int;

TEST(BasicOp, ScalarProduct) { // NOLINT
  auto left = random_vector<T, N>(-B, B);
  auto right = random_vector<T, N>(-B, B);

  T expected_product = 0;
  for (size_t i = 0; i < N; i++) {
    expected_product += left[i] * right[i];
  }

  auto actual_product = scalar_product<T, N>(left, right);
  ASSERT_EQ(actual_product, expected_product);
}

TEST(BasicOp, OperatorComposition) { // NOLINT
  // clang-format off
  auto left = matrix<T, 2, 3>({{
    {1, 2, 3}, // NOLINT
    {4, 5, 6}, // NOLINT
  }});
  auto right = matrix<T, 3, 2>({{
    {7 , 8 }, // NOLINT
    {9 , 10}, // NOLINT
    {11, 12}, // NOLINT
  }});

  auto expected_l_apply_r = matrix<T, 2, 2>({{
    {58 ,  64}, // NOLINT
    {139, 154}, // NOLINT
  }});

  auto expected_r_apply_l = matrix<T, 3, 3>({{
    {39, 54,  69}, // NOLINT
    {49, 68,  87}, // NOLINT
    {59, 82, 105}, // NOLINT
  }});
  // clang-format on

  auto actual_l_apply_r = left * right;
  auto actual_r_apply_l = right * left;

  ASSERT_EQ(actual_l_apply_r, expected_l_apply_r);
  ASSERT_EQ(actual_r_apply_l, expected_r_apply_l);
}

TEST(BasicOp, OperatorApplyVector) { // NOLINT
  // clang-format off
  auto scale = random_vector<T, N>(-B, B);
  auto scale_op = matrix<T, 3, 3>({{
    {scale[0], 0       , 0       },
    {0       , scale[1], 0       },
    {0       , 0       , scale[2]},
  }});
  // clang-format on
  auto original_vector = random_vector<T, 3>(-B, B);
  auto actual_scaled_vector = scale_op * original_vector;

  auto expected_scaled_vector = vector<T, 3>([=](size_t index) {
    return original_vector[index] * scale[index];
  });

  ASSERT_EQ(actual_scaled_vector, expected_scaled_vector);
}
