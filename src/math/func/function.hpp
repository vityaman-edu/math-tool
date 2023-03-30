#pragma once
#include <functional>

namespace math {

template <typename D, typename E>
using function = std::function<E(D)>;

}
