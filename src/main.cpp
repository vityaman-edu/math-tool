#include "tool/lineqsys.hpp"
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>

int usage() {
  std::cout << "usage: math-tool --help" << std::endl;
  return 1;
}

int main(int argc, char* argv[]) {
  std::cin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  if (argc < 2) {
    return usage();
  }

  auto tool = std::string(argv[1]); // NOLINT
  if (tool == "--help") {
    std::cout << "overview: Math tool" << std::endl;
    usage();
    std::cout << "options:" << std::endl;
    std::cout << "  lineqsys: solves systems of linear equations"
              << std::endl;
    std::cout << "    -i reads lineqsys from stdin" << std::endl;
    std::cout << "    <filepath> reads lineqsys from file"
              << std::endl;
  } else if (tool == "lineqsys") {
    if (argc != 3) {
      return usage();
    }
    std::string filepath = argv[2]; // NOLINT
    try {
      tool::lineqsys::run(std::cin, std::cout, {filepath});
    } catch (std::invalid_argument& e) {
      std::cerr << "error: " << e.what() << std::endl;
    } catch (std::ios_base::failure& e) {
      std::cerr << "error: invalid input (" << e.what() << ")"
                << std::endl;
    }
  } else {
    return usage();
  }

  return 0;
}
