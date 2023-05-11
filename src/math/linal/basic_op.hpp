#pragma once

#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>

namespace math::linal {

template <typename F, size_t N>
F scalar_product(
    const Vector<F, N>& left, const Vector<F, N>& right
) noexcept {
  F product = 0;
  for (size_t i = 0; i < N; i++) {
    product += left[i] * right[i];
  }
  return product;
}

template <typename F, size_t A, size_t B, size_t C>
Matrix<F, A, B> operator*(
    const Matrix<F, A, C>& left, const Matrix<F, C, B>& right
) noexcept {
  return Matrix<F, A, B>([=](size_t row, size_t col) {
    F value = 0;
    for (size_t k = 0; k < C; k++) {
      value += left[row][k] * right[k][col];
    }
    return value;
  });
}

template <typename F, size_t N>
Vector<F, N> operator*(
    const Matrix<F, N, N>& mat, const Vector<F, N>& vec
) noexcept {
  return Vector<F, N>([=](size_t index) {
    return scalar_product(mat[index], vec);
  });
}

template <typename T, typename F, size_t N>
Vector<T, N>
map(const Vector<T, N>& vec, const std::function<T(F)>& func) {
  return Vector<T, N>([=](size_t index) {
    return func(vec[index]);
  });
}

}
