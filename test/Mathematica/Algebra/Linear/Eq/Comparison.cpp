#include "../Generator.hpp"
#include "Mathematica/Algebra/FieldTrait.hpp"
#include "Mathematica/Algebra/Linear/Eq/GaussSolver.hpp"
#include "Mathematica/Algebra/Linear/Eq/IterationSolver.hpp"
#include "Mathematica/Core.hpp"
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

using namespace Mathematica;
using namespace Mathematica::Algebra::Linear;

constexpr float EPS = 0.001;

template <typename F, Size N>
void assert_result(const Vector<F, N>& actual, const Vector<F, N>& expected) {
  auto diff = (actual - expected);
  diff = map<F, F, N>(diff, [=](auto element) { return std::abs(element); });
  const auto max_diff = *std::max_element(diff.begin(), diff.end());
  ASSERT_LT(max_diff, EPS);
}

template <typename F, Size N>
void test() {
  const auto n = std::to_string(N);
  const std::string basepath = "./test/io/sle/" + n + "x" + n;

  for (const auto& entry : std::filesystem::directory_iterator(basepath)) {
    auto file = std::ifstream(entry.path());
    if (!file.is_open()) {
      throw std::runtime_error("can't open file");
    }

    auto a = Matrix<F, N, N>();
    auto b = Vector<F, N>();

    for (auto i = 0; i < N; i++) {
      for (auto j = 0; j < N; j++) {
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
      auto iter = Eq::IterationSolver<F, N>(EPS);
      const auto iter_result = iter.solve({a, b}).value;
      assert_result(iter_result, expected_result);
    } catch (std::invalid_argument& e) {
      std::cerr << "iter error: " << e.what() << std::endl;
    }

    try {
      auto gauss = Eq::GaussSolver<F, N>();
      const auto gauss_result = gauss.solve({a, b}).value;
      assert_result(gauss_result, expected_result);
    } catch (std::invalid_argument& e) {
      std::cerr << "gauss error: " << e.what() << std::endl;
    }
  }
}

TEST(LinearEqSolve, IOCases3x3) { // NOLINT
  test<double, 3>();
}

TEST(LinearEqSolve, Fuzzing) { // NOLINT
  constexpr Count ROUNDS = 10;
  constexpr Size N = 30;
  constexpr int B = 100;
  using F = float;

  for (auto i = 0; i < ROUNDS; i++) {
    auto a = randomMatrix<F, N, N>(-B, B);
    auto b = randomVector<F, N>(-B, B);

    // Make diagonal predominance
    for (size_t j = 0; j < N; j++) {
      a[j][j] = static_cast<float>(std::reduce(
          a[j].begin(),
          a[j].end(),
          1,
          [](F left, F right) { return std::abs(left) + std::abs(right); }
      ));
    }

    // Shuffle
    for (auto i = 0; i < N; i++) {
      const auto row_1 = randomSize(N);
      const auto row_2 = randomSize(N);
      a.swapRows(row_1, row_2);
    }
    for (auto i = 0; i < N; i++) {
      const auto col_1 = randomSize(N);
      const auto col_2 = randomSize(N);
      a.swapCols(col_1, col_2);
    }

    try {
      auto gauss = Eq::GaussSolver<F, N>();
      auto iter = Eq::IterationSolver<F, N>(EPS);

      const auto iter_result = iter.solve({a, b}).value;
      const auto gauss_result = gauss.solve({a, b}).value;
      assert_result(gauss_result, iter_result);
      std::cout << "[FUZZ]: OK" << std::endl;
    } catch (std::invalid_argument& e) {
      std::cerr << "[FUZZ]: Error " << e.what() << std::endl;
    }
  }
}
