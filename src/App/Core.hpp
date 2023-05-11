#include "Mathematica/Core.hpp"
#include "Mathematica/Common/Interval.hpp"
#include <optional>
#include <string>
#include <vector>

namespace App {

using String = std::string;
template <typename T>

using Vector = std::vector<T>;

using Real = Mathematica::Real;

using Integer = Mathematica::Integer;

using Scope = Mathematica::Interval<Real>;

template <typename T>
using Function = Mathematica::Function<T>;

}