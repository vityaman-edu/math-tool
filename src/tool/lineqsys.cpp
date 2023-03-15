#include "tool/lineqsys.hpp"
#include <cassert>

namespace tool::lineqsys {

static std::istream* open(const std::string& filepath) {
  auto* file = new std::ifstream(filepath); // NOLINT
  if (!file->is_open()) {
    throw std::invalid_argument("error: can't open file " + filepath);
  }
  return file;
}

void run(
    std::istream& in, // NOLINT
    std::ostream& out,
    const std::vector<std::string>& args
) {
  assert(!args.empty()); // NOLINT

  using F = float;

  bool reading_stdin = (args[0] == "-i");
  std::istream* input = nullptr;
  if (reading_stdin) {
    input = &in;
  } else {
    input = open(args[0]);
  }

  size_t size; // NOLINT
  *input >> size;
  switch (size) {
  case 1:                    // NOLINT
    impl<F, 1>(*input, out); // NOLINT
    break;
  case 2:                    // NOLINT
    impl<F, 2>(*input, out); // NOLINT
    break;
  case 3:                    // NOLINT
    impl<F, 3>(*input, out); // NOLINT
    break;
  case 4:                    // NOLINT
    impl<F, 4>(*input, out); // NOLINT
    break;
  case 5:                    // NOLINT
    impl<F, 5>(*input, out); // NOLINT
    break;
  case 6:                    // NOLINT
    impl<F, 6>(*input, out); // NOLINT
    break;
  case 7:                    // NOLINT
    impl<F, 7>(*input, out); // NOLINT
    break;
  case 8:                    // NOLINT
    impl<F, 8>(*input, out); // NOLINT
    break;
  case 9:                    // NOLINT
    impl<F, 9>(*input, out); // NOLINT
    break;
  case 10:                    // NOLINT
    impl<F, 10>(*input, out); // NOLINT
    break;
  case 11:                    // NOLINT
    impl<F, 11>(*input, out); // NOLINT
    break;
  case 12:                    // NOLINT
    impl<F, 12>(*input, out); // NOLINT
    break;
  case 13:                    // NOLINT
    impl<F, 13>(*input, out); // NOLINT
    break;
  case 14:                    // NOLINT
    impl<F, 14>(*input, out); // NOLINT
    break;
  case 15:                    // NOLINT
    impl<F, 15>(*input, out); // NOLINT
    break;
  case 16:                    // NOLINT
    impl<F, 16>(*input, out); // NOLINT
    break;
  case 17:                    // NOLINT
    impl<F, 17>(*input, out); // NOLINT
    break;
  case 18:                    // NOLINT
    impl<F, 18>(*input, out); // NOLINT
    break;
  case 19:                    // NOLINT
    impl<F, 19>(*input, out); // NOLINT
    break;
  case 20:                    // NOLINT
    impl<F, 20>(*input, out); // NOLINT
    break;
  default: {
    throw std::invalid_argument(
        "error: size must be in [1, 20], got " + std::to_string(size)
    );
  }
  }

  std::ifstream* file; // NOLINT:
  if (!reading_stdin
      && (file = dynamic_cast<std::ifstream*>(input))) { // NOLINT
    file->close();
    delete file; // NOLINT
  }
}

}