#ifndef MATRIX_FILTERS_HPP_
#define MATRIX_FILTERS_HPP_

#include "matrix_type.hpp"

namespace mlib
{

/**
 * @brief median
 *
 * @param [in] Matrix A nxn
 *
 * @return median
 */
template<typename T,  std::size_t i, std::size_t j>
T median(const Matrix<T, i, j>& A)
{
  std::vector<T> v;
  const std::size_t size = i*j;
  v.reserve(size);

  for (std::size_t it = 0; it < i; it++)
  {
    for (std::size_t jt = 0; jt < j; jt++)
    {
      v.push_back(A[it][jt]);
    }
  }

  std::sort(v.begin(), v.end());

  if (size % 2 == 0)
  {
    return (v[size / 2] + v[size / 2 - 1]) / 2;
  }

  else
  {
    return v[floor(size / 2)];
  }

  return A[0][0];
}



} /* namespace mlib */

#endif // MATRIX_FILTERS_HPP_
