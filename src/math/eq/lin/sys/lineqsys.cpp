#include "math/eq/lin/sys/lineqsys.hpp"
#include <iomanip>

namespace math::eq::lin::sys {

std::ostream& operator<<(std::ostream& out, Format /*format*/) {
  constexpr int PRECISION = 4;
  constexpr int COL_WIDTH = 8;
  out << std::setprecision(PRECISION) //
      << std::setw(COL_WIDTH)         //
      << std::setfill(' ');
  return out;
}

}