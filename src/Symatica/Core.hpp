#pragma once

#include <cstddef>
#include <memory>

namespace Symatica::Core {

using Id = std::size_t;
using Number = double;

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T, typename... Args>
Ptr<T> makePtr(Args&&... args) {
  return std::make_shared<T>(args...);
}

template <typename U, typename T>
Ptr<U> castPtr(const Ptr<T>& ptr) noexcept {
  return std::static_pointer_cast<U>(ptr);
}

}
