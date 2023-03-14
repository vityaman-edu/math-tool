#include "math/eq/lin/sys/lineqsys.hpp"
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
#include <stdexcept>
#include <string>

using math::eq::lin::sys::solve::iter::solve;
using math::eq::lin::sys::solve::iter::valid_lineqsys;
using math::linal::matrix;
using math::linal::vector;

constexpr float EPS = 0.001;

template <typename F, size_t N>
void test() {
  const auto n = std::to_string(N); // NOLINT
  const std::string basepath = "./test/io/sle/" + n + "x" + n + "/ok";

  for (const auto& entry :
       std::filesystem::directory_iterator(basepath)) {
    std::ifstream file(entry.path());
    if (!file.is_open()) {
      throw std::runtime_error("can't open file");
    }

    matrix<F, N, N> a; // NOLINT
    vector<F, N> b;    // NOLINT

    for (std::size_t i = 0; i < N; i++) {
      for (std::size_t j = 0; j < N; j++) {
        file >> a[i][j];
      }
      file >> b[i];
    }

    const auto expected_result = vector<F, N>([&file](size_t) {
      F number;
      file >> number;
      return number;
    });

    file.close();

    const auto system = valid_lineqsys<F, N>::from({a, b});
    const auto actual_result = solve<F, N>(system, EPS).value;

    auto diff = (actual_result - expected_result);
    diff = math::linal::map<F, F, N>(diff, [=](F element) {
      return std::abs(element);
    });
    const auto max_diff = *std::max_element(diff.begin(), diff.end());

    ASSERT_LT(max_diff, EPS);
  }
}

TEST(LinEqSysSolveIter, IOCases3x3) { test<float, 3>(); }
