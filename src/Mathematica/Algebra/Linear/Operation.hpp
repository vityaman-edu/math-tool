#pragma once


#include "Mathematica/Core.hpp"

namespace Mathematica::Algebra::Linear {

template <typename F, Size N, Field::BasicOp<F> Op = Field::BasicOp<F>()>
F scalarProduct(const Vector<F, N>& left, const Vector<F, N>& right) noexcept {
  F product = 0;
  for (auto i = 0; i < N; i++) {
    product = Op.sum(product, Op.mul(left[i], right[i]));
  }
  return product;
}

template <
    typename F,
    Size A,
    Size B,
    Size C,
    Field::BasicOp<F> Op = Field::BasicOp<F>()>
Matrix<F, A, B, Op> operator*(
    const Matrix<F, A, C, Op>& left, const Matrix<F, C, B, Op>& right
) noexcept {
  return Matrix<F, A, B, Op>([=](auto row, auto col) {
    F value = 0;
    for (auto k = 0; k < C; k++) {
      value = Op.sum(value, Op.mul(left[row][k], right[k][col]));
    }
    return value;
  });
}

template <typename F, Size N>
Vector<F, N> operator*(const Matrix<F, N, N>& mat, const Vector<F, N>& vec) noexcept {
  return Vector<F, N>([=](auto index) { return scalarProduct(mat[index], vec); });
}

template <typename T, typename F, Size N>
Vector<T, N> map(const Vector<T, N>& vec, const Mapping<T(F)>& func) {
  return Vector<T, N>([=](auto index) { return func(vec[index]); });
}

}