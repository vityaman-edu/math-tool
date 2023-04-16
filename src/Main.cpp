#include "App/Tool/EquationSolver.hpp"
#include "App/Tool/EquationSystemSolver.hpp"
#include "App/Tool/Integrator.hpp"
#include "App/Tool/lineqsys.hpp"
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

int usage() {
  std::cout << "usage: math-tool --help" << std::endl;
  return 1;
}

int main(int argc, char* argv[]) {
  std::cin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  if (argc < 2) {
    return usage();
  }

  auto args = std::vector<std::string>(argv, argv + argc);
  
  auto tool = args[1]; // NOLINT
  if (tool == "--help") {
    std::cout << "overview: Math tool" << std::endl;
    usage();
    std::cout << "options:" << std::endl;
    std::cout << "  lineqsys: solves systems of linear equations" << std::endl;
    std::cout << "    -i reads lineqsys from stdin" << std::endl;
    std::cout << "    <filepath> reads lineqsys from file" << std::endl;
    std::cout << "  eqsolver" << std::endl;
    std::cout << "  syssolver" << std::endl;
    std::cout << "  integrator" << std::endl;
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
      std::cerr << "error: invalid input (" << e.what() << ")" << std::endl;
    }
  } else if (tool == "eqsolver") {
    auto arguments = App::Tool::EquationSolver::Arguments::parseArgs(args);
    auto runner = App::Tool::EquationSolver::Runner(arguments);
    runner.run(std::cin, std::cout);
  } else if (tool == "syssolver") {
    auto arguments = App::Tool::EquationSystemSolver::Arguments::parseArgs(args);
    auto runner = App::Tool::EquationSystemSolver::Runner(arguments);
    runner.run(std::cin, std::cout);
  } else if (tool == "integrator") {
    auto arguments = App::Tool::Integrator::Arguments::parseArgs(args);
    auto runner = App::Tool::Integrator::Runner(arguments);
    runner.run(std::cin, std::cout);
  } else {
    return usage();
  }

  return 0;
}
