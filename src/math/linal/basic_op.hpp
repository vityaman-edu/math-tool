#include "math/linal/matrix.hpp"
#include "math/linal/vector.hpp"
#include <cstddef>

namespace math::linal {

template <typename F, size_t N>
F scalar_product(
    const vector<F, N>& left, const vector<F, N>& right
) noexcept {
  F product = 0;
  for (size_t i = 0; i < N; i++) {
    product += left[i] * right[i];
  }
  return product;
}

template <typename F, size_t A, size_t B, size_t C>
matrix<F, A, B> operator*(
    const matrix<F, A, C>& left, const matrix<F, C, B>& right
) noexcept {
  return matrix<F, A, B>([=](size_t row, size_t col) {
    F value = 0;
    for (size_t k = 0; k < C; k++) {
      value += left[row][k] * right[k][col];
    }
    return value;
  });
}

template <typename F, size_t N>
vector<F, N> operator*(
    const matrix<F, N, N>& mat, const vector<F, N>& vec
) noexcept {
  return vector<F, N>([=](size_t index) {
    return scalar_product(mat[index], vec);
  });
}

}
