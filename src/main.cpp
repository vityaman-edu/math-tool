#include "math/eq/lin/sys/lineqsys.hpp"
#include "math/eq/lin/sys/solve/gauss/method.hpp"
#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>

using math::eq::lin::sys::lineqsys;
using math::eq::lin::sys::solve::gauss::result;
using math::eq::lin::sys::solve::gauss::solve;

void usage() {
  std::cout << "usage: math-tool <filepath>" << std::endl;
}

template <typename F, size_t N>
lineqsys<F, N> parse_system_from(std::istream& input) {
  lineqsys<F, N> sys; // NOLINT: init in for-loop
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < N; j++) {
      input >> sys.a[i][j];
    }
    input >> sys.b[i];
  }
  return sys;
}

template <typename F, size_t N>
void report(std::ostream& out, const result<F, N>& result) {
  F det = 1;
  for (size_t i = 0; i < N; i++) {
    det *= result.triangle.a[i][i];
  }

  out << "lineqsys gauss method results report" << '\n';
  // TODO: det sign from swaps inside gauss
  out << "det: " << det << '\n';
  out << "triangle matrix:" << '\n';
  out << result.triangle;
  out << "result: " << result.value << '\n';
  out << "error: " << result.error << '\n';
}

template <typename F, size_t N>
int impl(std::ifstream& file) {
  try {
    auto system = parse_system_from<F, N>(file);
    file.close();
    auto result = solve(system);
    report(std::cout, result);
  } catch (std::invalid_argument& e) {
    std::cerr << "error: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  using F = float;

  if (argc != 2) {
    usage();
  }

  auto filepath = std::string(argv[1]); // NOLINT

  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "error: can't open file " << filepath << std::endl;
    return 1;
  }

  size_t size; // NOLINT
  file >> size;
  switch (size) {
  case 1:                     // NOLINT
    return impl<F, 1>(file);  // NOLINT
  case 2:                     // NOLINT
    return impl<F, 2>(file);  // NOLINT
  case 3:                     // NOLINT
    return impl<F, 3>(file);  // NOLINT
  case 4:                     // NOLINT
    return impl<F, 4>(file);  // NOLINT
  case 5:                     // NOLINT
    return impl<F, 5>(file);  // NOLINT
  case 6:                     // NOLINT
    return impl<F, 6>(file);  // NOLINT
  case 7:                     // NOLINT
    return impl<F, 7>(file);  // NOLINT
  case 8:                     // NOLINT
    return impl<F, 8>(file);  // NOLINT
  case 9:                     // NOLINT
    return impl<F, 9>(file);  // NOLINT
  case 10:                    // NOLINT
    return impl<F, 10>(file); // NOLINT
  case 11:                    // NOLINT
    return impl<F, 11>(file); // NOLINT
  case 12:                    // NOLINT
    return impl<F, 12>(file); // NOLINT
  case 13:                    // NOLINT
    return impl<F, 13>(file); // NOLINT
  case 14:                    // NOLINT
    return impl<F, 14>(file); // NOLINT
  case 15:                    // NOLINT
    return impl<F, 15>(file); // NOLINT
  case 16:                    // NOLINT
    return impl<F, 16>(file); // NOLINT
  case 17:                    // NOLINT
    return impl<F, 17>(file); // NOLINT
  case 18:                    // NOLINT
    return impl<F, 18>(file); // NOLINT
  case 19:                    // NOLINT
    return impl<F, 19>(file); // NOLINT
  case 20:                    // NOLINT
    return impl<F, 20>(file); // NOLINT
  default: {
    std::cerr << "error: size must be in [1, 20], got " << size
              << std::endl;
    return 1;
  }
  }
}
