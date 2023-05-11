#include "generator.hpp"
#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/gauss/method.hpp"
#include "math/eq/lin/sys/solve/iter/method.hpp"
#include "math/eq/lin/sys/solve/iter/valid_lineqsys.hpp"
#include "math/linal/basic_op.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cmath>
#include <cstddef>
#include <exception>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

constexpr float EPS = 0.001;

template <typename F, size_t N>
void assert_result(
    const math::linal::Vector<F, N>& actual,  // NOLINT
    const math::linal::Vector<F, N>& expected // NOLINT
) {
  auto diff = (actual - expected);
  diff = math::linal::map<F, F, N>(diff, [=](F element) {
    return std::fabs(element);
  });
  const auto max_diff = *std::max_element(diff.begin(), diff.end());
  ASSERT_LT(max_diff, EPS);
}

template <typename F, size_t N>
void test() {
  using namespace math::linal;               // NOLINT
  using namespace math::eq::lin::sys::solve; // NOLINT

  const auto n = std::to_string(N); // NOLINT
  const std::string basepath = "./test/io/sle/" + n + "x" + n;

  for (const auto& entry :
       std::filesystem::directory_iterator(basepath)) {

    std::ifstream file(entry.path());
    if (!file.is_open()) {
      throw std::runtime_error("can't open file");
    }

    Matrix<F, N, N> a; // NOLINT
    Vector<F, N> b;    // NOLINT

    for (size_t i = 0; i < N; i++) {
      for (size_t j = 0; j < N; j++) {
        file >> a[i][j];
      }
      file >> b[i];
    }

    const auto expected_result = Vector<F, N>([&file](size_t) {
      F number;
      file >> number;
      return number;
    });

    file.close();

    try {
      const auto valid_system
          = iter::valid_lineqsys<F, N>::from({a, b});
      const auto iter_result
          = iter::solve<F, N>(valid_system, EPS).value;
      assert_result(iter_result, expected_result);
    } catch (std::invalid_argument& e) {
      std::cerr << "iter error: " << e.what() << std::endl;
    }

    try {
      const auto gauss_result = gauss::solve<F, N>({a, b}).value;
      assert_result(gauss_result, expected_result);
    } catch (std::invalid_argument& e) {
      std::cerr << "gauss error: " << e.what() << std::endl;
    }
  }
}

TEST(LinEqSysSolve, IOCases3x3) { test<double, 3>(); }

TEST(LinEqSysSolve, Fuzzing) {
  constexpr size_t ROUNDS = 10;              // NOLINT
  constexpr size_t N = 30;                   // NOLINT
  constexpr int B = 100;                     // NOLINT
  using F = float;                           // NOLINT
  using namespace math::linal;               // NOLINT
  using namespace math::eq::lin::sys::solve; // NOLINT

  for (size_t i = 0; i < ROUNDS; i++) {
    Matrix<F, N, N> a = random_matrix<F, N, N>(-B, B); // NOLINT
    Vector<F, N> b = random_vector<F, N>(-B, B);       // NOLINT

    // Make diagonal predominance
    for (size_t j = 0; j < N; j++) {
      a[j][j] = static_cast<float>(std::reduce(
          a[j].begin(),
          a[j].end(),
          1,
          [](F left, F right) {
            return std::abs(left) + std::abs(right);
          }
      ));
    }

    // Shuffle
    for (size_t i = 0; i < N; i++) {
      auto row_1 = random_size(N);
      auto row_2 = random_size(N);
      a.swap_rows(row_1, row_2);
    }
    for (size_t i = 0; i < N; i++) {
      auto col_1 = random_size(N);
      auto col_2 = random_size(N);
      a.swap_cols(col_1, col_2);
    }

    try {
      const auto valid_system
          = iter::valid_lineqsys<F, N>::from({a, b});
      const auto iter_result
          = iter::solve<F, N>(valid_system, EPS).value;
      const auto gauss_result = gauss::solve<F, N>({a, b}).value;
      assert_result(gauss_result, iter_result);
      std::cout << "[FUZZ]: OK" << std::endl;
    } catch (std::invalid_argument& e) {
      std::cerr << "[FUZZ]: Error " << e.what() << std::endl;
    }
  }
}
