#include "tool/lineqsys.hpp"
#include <cassert>
#include <fstream>

namespace tool::lineqsys {

void run_delegate(std::istream& input, std::ostream& out) {
  using F = float;
  size_t size; // NOLINT
  input >> size;
  switch (size) {
  case 1:                   // NOLINT
    impl<F, 1>(input, out); // NOLINT
    break;
  case 2:                   // NOLINT
    impl<F, 2>(input, out); // NOLINT
    break;
  case 3:                   // NOLINT
    impl<F, 3>(input, out); // NOLINT
    break;
  case 4:                   // NOLINT
    impl<F, 4>(input, out); // NOLINT
    break;
  case 5:                   // NOLINT
    impl<F, 5>(input, out); // NOLINT
    break;
  case 6:                   // NOLINT
    impl<F, 6>(input, out); // NOLINT
    break;
  case 7:                   // NOLINT
    impl<F, 7>(input, out); // NOLINT
    break;
  case 8:                   // NOLINT
    impl<F, 8>(input, out); // NOLINT
    break;
  case 9:                   // NOLINT
    impl<F, 9>(input, out); // NOLINT
    break;
  case 10:                   // NOLINT
    impl<F, 10>(input, out); // NOLINT
    break;
  case 11:                   // NOLINT
    impl<F, 11>(input, out); // NOLINT
    break;
  case 12:                   // NOLINT
    impl<F, 12>(input, out); // NOLINT
    break;
  case 13:                   // NOLINT
    impl<F, 13>(input, out); // NOLINT
    break;
  case 14:                   // NOLINT
    impl<F, 14>(input, out); // NOLINT
    break;
  case 15:                   // NOLINT
    impl<F, 15>(input, out); // NOLINT
    break;
  case 16:                   // NOLINT
    impl<F, 16>(input, out); // NOLINT
    break;
  case 17:                   // NOLINT
    impl<F, 17>(input, out); // NOLINT
    break;
  case 18:                   // NOLINT
    impl<F, 18>(input, out); // NOLINT
    break;
  case 19:                   // NOLINT
    impl<F, 19>(input, out); // NOLINT
    break;
  case 20:                   // NOLINT
    impl<F, 20>(input, out); // NOLINT
    break;
  default:
    throw std::invalid_argument(
        "error: size must be in [1, 20], got " + std::to_string(size)
    );
  }
}

void run(
    std::istream& input,
    std::ostream& out,
    const std::vector<std::string>& args
) {
  assert(!args.empty()); // NOLINT

  if ((args[0] == "-i")) {
    run_delegate(input, out);
  } else {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      file.open(args[0]);
      run_delegate(file, out);
    } catch (std::ios_base::failure& e) {
      file.close();
      throw e;
    }
  }
}

}