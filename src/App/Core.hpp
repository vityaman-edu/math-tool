#include "Mathematica/Core.hpp"
#include "Mathematica/Equation/Solution/Method/Interval.hpp"
#include <optional>
#include <string>
#include <vector>

namespace App {

using String = std::string;
template <typename T>

using Vector = std::vector<T>;

using Real = Mathematica::Real;

using Integer = Mathematica::Integer;

using Scope = Mathematica::Equation::Solution::Method::Interval<Real>;

template <typename T>
using Function = Mathematica::Function<T>;

}