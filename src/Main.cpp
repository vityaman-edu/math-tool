#include "App/Tool/Approx.hpp"
#include "App/Tool/EquationSolver.hpp"
#include "App/Tool/EquationSystemSolver.hpp"
#include "App/Tool/Integrator.hpp"
#include "App/Tool/LinEqSys.hpp"
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

int help() {
  std::cout << "overview: Math tool" << std::endl;
  usage();
  std::cout << //
      "options:\n"
      "  lineqsys: solves systems of linear equations\n"
      "    -i reads lineqsys from stdin\n"
      "    <filepath> reads lineqsys from file\n"
      "  eqsolver\n"
      "  syssolver\n"
      "  integrator:\n"
      "    <method> rect-l rect-m rect-r trapeze simpson cotes5\n"
      "    <left> <right> scope\n"
      "    <accuracy>\n"
      "  approx\n";
  return 0;
}

int lineqsys(const std::vector<std::string>& args) {
  if (args.size() != 3) {
    return usage();
  }
  const auto& filepath = args[2];
  try {
    App::Tool::LinEqSys::run(std::cin, std::cout, {filepath});
  } catch (std::invalid_argument& e) {
    std::cerr << "error: " << e.what() << std::endl;
  } catch (std::ios_base::failure& e) {
    std::cerr << "error: invalid input (" << e.what() << ")" << std::endl;
  }
  return 0;
}

int eqsolver(const std::vector<std::string>& args) {
  auto arguments = App::Tool::EquationSolver::Arguments::parseArgs(args);
  auto runner = App::Tool::EquationSolver::Runner(arguments);
  runner.run(std::cin, std::cout);
  return 0;
}

int syssolver(const std::vector<std::string>& args) {
  auto arguments = App::Tool::EquationSystemSolver::Arguments::parseArgs(args);
  auto runner = App::Tool::EquationSystemSolver::Runner(arguments);
  runner.run(std::cin, std::cout);
  return 0;
}

int integrator(const std::vector<std::string>& args) {
  auto arguments = App::Tool::Integrator::Arguments::parseArgs(args);
  auto runner = App::Tool::Integrator::Runner(arguments);
  runner.run(std::cin, std::cout);
  return 0;
}

int approx(const std::vector<std::string>& args) {
  auto arguments = App::Tool::Approx::Arguments::parseArgs(args);
  auto runner = App::Tool::Approx::Runner(arguments);
  runner.run(std::cin, std::cout);
  return 0;
}

int main(int argc, char* argv[]) {
  std::cin.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  if (argc < 2) {
    return usage();
  }

  auto args = std::vector<std::string>(argv, argv + argc);
  auto tool = args[1];

  // clang-format off
  if (tool == "--help"    ) return help      (    ); // NOLINT
  if (tool == "lineqsys"  ) return lineqsys  (args); // NOLINT
  if (tool == "eqsolver"  ) return eqsolver  (args); // NOLINT
  if (tool == "syssolver" ) return syssolver (args); // NOLINT
  if (tool == "integrator") return integrator(args); // NOLINT
  if (tool == "approx"    ) return approx    (args); // NOLINT
  return usage();
  // clang-format on

  return 0;
}
