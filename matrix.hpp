/*
 * matrix.hpp
 *
 *  Created on: Sep 12, 2016
 *      Author: Michal Kielan
 * Description: Simple matrix library
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <array>
#include <utility>
#include <cmath>

 ////for debug only
 #include <iostream>


/**
 * \bref Matrix type definition
 *
 * \Usage: Matrix<type, row, col>
 */
template <typename T, std::size_t i, std::size_t j,
typename Arithmetic = std::enable_if_t<std::is_arithmetic<T>::value>>
using Matrix = std::array<std::array<T, j>, i>;


/**
 * \brief Create i,j matrix filling with some data
 * 
 * Usage: <type, row , col>(data)
 * \param [in] data to fill the matrix
 * 
 * \return matrix with i, j size
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> fill(T data)
{
  Matrix<T, i, j> A{};
  for(auto& a : A)
  {
    a.fill(data);
  }

  return A;
}


/**
 * \brief Create i,j matrix filling with one
 * 
 * Usage: <type, row , col>(data)
 * 
 * \return matrix with i, j size
 */
template<unsigned int, std::size_t i, std::size_t j = i>
Matrix<unsigned int, i, j> ones()
{
  return fill<unsigned int, i, j>(1);
}

template<typename T, std::size_t i, std::size_t j = i>
Matrix<T, i, i> ones()
{
  return fill<T, i, j>(1);
}


/**
 * \brief Create i,j matrix filling with zeros
 * 
 * Usage: <type, row , col>(data)
 * 
 * \return matrix with i, j size
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> zeros()
{
  return fill<T, i, j>(static_cast<T>(0));
}


/**
 * \brief Create a matrix with one number at the diagonal
 * 
 * Usage: <type, row , col>(data) or <type, row , col>()
 * \param [in] data to fill the matrix if empty, the default is 1
 * 
 * \return matrix with i, j size
 */
template<typename T, std::size_t n>
Matrix<T, n, n> eye(T data = 1)
{
  auto eye = fill<T, n, n>(0);

  for (std::size_t i = 0; i < n; i++)
  {
    eye[i][i] = data;
  }
  return eye;
}


/**
 * \brief Sum of two matrices
 * 
 * \param [in] Matrix A with i, j size
 * \param [in] Matrix B with i, j size
 * 
 * \return Result of sum matrix A and B
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> sum(const Matrix<T, i, j>& A, const Matrix<T, i, j>& B)
{
  Matrix<T, i, j> sum{};

  for(std::size_t it = 0; it < i; it++)
  {
    for(std::size_t jt = 0; jt < j; jt++)
    {
      sum[it][jt] = A[it][jt] + B[it][jt];
    }
  }
  return sum;
}


/**
 * \brief Sum matrix and scalar
 * 
 * \param [in] Matrix A with i, j size
 * \param [in] Scalar data with the same type as matrix A
 * 
 * \return Result of sum each element of A matrix and scalar data
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> sum(const Matrix<T, i, j>& A, T& scalar)
{
  Matrix<T, i, j> sum{};

  for(std::size_t it = 0; it < i; it++)
  {
    for(std::size_t jt = 0; jt < j; jt++)
    {
      sum[it][jt] = A[it][jt] + scalar;
    }
  }
  return sum;
}


/**
 * \brief Substraction of two matrices
 * 
 * \param [in] Matrix A with i, j size
 * \param [in] Matrix B with i, j size
 * 
 * \return Result of substraction matrix A and B
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> sub(const Matrix<T, i, j>& A, const Matrix<T, i, j>& B)
{
  Matrix<T, i, j> sub{};

  for(std::size_t it = 0; it < i; it++)
  {
    for(std::size_t jt = 0; jt < j; jt++)
    {
      sub[it][jt] = A[it][jt] - B[it][jt];
    }
  }
  return sub;
}


/**
 * \brief Substraction matrix and scalar
 * 
 * \param [in] Matrix A with i, j size
 * \param [in] Scalar data with the same type as matrix A
 * 
 * \return Result of substraction each element of A matrix and scalar data
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> sub(const Matrix<T, i, j>& A, T& scalar)
{
  Matrix<T, i, j> sub{};

  for(std::size_t it = 0; it < i; it++)
  {
    for(std::size_t jt = 0; jt < j; jt++)
    {
      sub[it][jt] = A[it][jt] - scalar;
    }
  }
  return sub;
}


/**
 * \brief  Multiplication of two matrices
 *
 * Usage: If sizes of matrix A and B are illegal to multiply,
 *        the function will not compile
 * \param [in] Matrix A with n, m size
 * \param [in] Matrix B with m, p size
 * 
 * \return Result of multiplication matrix A and B
 */
template<typename T,  std::size_t n, std::size_t m, std::size_t p>
Matrix<T, n, p> mult(const Matrix<T, n, m>& A, const Matrix<T, m, p>& B)
{
  auto prod = zeros<T, n, p>();

  for(std::size_t i = 0; i < n; ++i)
  {
    for(std::size_t j = 0; j < p; ++j)
    {
      for(std::size_t k = 0; k < m; ++k)
      {
        prod[i][j] += (A[i][k] * B[k][j]);
      }
    }
  }
  return prod;
}


 /**
 * \brief  Multiplication matrix and scalar
 * 
 * \param [in] Matrix A with i, j size
 * \param [in] Scalar data with the same type as matrix A
 * 
 * \return Result of multiplication each element of A matrix and scalar data
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> mult(const Matrix<T, i, j>& A, T& scalar)
{
  Matrix<T, i, j> prod{};

  for(std::size_t it = 0; it < i; it++)
  {
    for(std::size_t jt = 0; jt < j; jt++)
    {
      prod[it][jt] = A[it][jt] * scalar;
    }
  }
  return prod;
}


 /**
 * \brief Divide matrix and scalar
 * 
 * \param [in] Matrix A with i, j size
 * \param [in] Scalar data with the same type as matrix A
 * 
 * \return Result of divide each element of A matrix and scalar data
 */
template<typename T, std::size_t n, std::size_t m>
Matrix<T, n, m> div(const Matrix<T, n, m>& A, T& scalar)
{
  if(scalar == 0)
    throw;

  Matrix<T, n, m> prod{};

  for(std::size_t i = 0; i < n; i++)
  {
    for(std::size_t j = 0; j < m; j++)
    {
      prod[i][j] = A[i][j] / scalar;
    }
  }
  return prod;
}


/**
 * \brief LU decomposition
 * 
 * Usage: The result of function is pair of matrices where L matrix is first 
 *        element of pair, the second element is U matrix
 * \param [in] Square Matrix A
 * 
 * \return Two matrices L and U
 */
template<typename T, std::size_t n>
std::pair<Matrix<T,n,n>, Matrix<T,n,n>>lu(const Matrix<T,n,n>& A)
{
  auto L = eye<T, n>();
  auto U = zeros<T, n, n>();
  T sum;

  for(std::size_t j = 0; j < n; j++)
  {
    for(std::size_t i = 0; i <= j; i++)
    {
      sum = 0.0;
      for(std::size_t p = 0; p < i; p++)
      {
        sum += U[p][j] * L[i][p];
      }
      U[i][j] = A[i][j] - sum;
    }
    for(std::size_t i = j; i < n; i++)
    {
      sum = 0.0;
      for(std::size_t p = 0; p < i; p++)
      {
        sum += U[p][j] * L[i][p];
      }

      if(U[j][j] == 0)
        throw;
      else
        L[i][j] = (A[i][j] - sum) / U[j][j];
    }
  }
  return std::pair<Matrix<T,n,n>, Matrix<T,n,n>>{L, U};
}


/**
 * \brief Determinant of matrix 1x1
 *
 * \param [in] Square Matrix A with 1x1 size
 * 
 * \return Determinant of matrix A
 */
template<typename T>
T det(const Matrix<T, 1, 1>& A)
{
  return A[0][0]; 
}

/**
 * \brief Determinant of matrix 2x2
 *
 * \param [in] Square Matrix A with 2x2 size
 * 
 * \return Determinant of matrix A
 */
template<typename T>
T det(const Matrix<T, 2, 2>& A)
{
  auto&& a = A[0][0]; auto&& b = A[0][1];
  auto&& c = A[1][0]; auto&& d = A[1][1];

  return a*d - b*c; 
}

/**
 * \brief Determinant of matrix 3x3
 *
 * \param [in] Square Matrix A with 3x3 size
 * 
 * \return Determinant of matrix A
 */
template<typename T>
T det(const Matrix<T, 3, 3>& A)
{
  auto&& a = A[0][0]; auto&& b = A[0][1]; auto&& c = A[0][2];
  auto&& d = A[1][0]; auto&& e = A[1][1]; auto&& f = A[1][2];
  auto&& g = A[2][0]; auto&& h = A[2][1]; auto&& i = A[2][2];

  return a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h;
}


/**
 * \brief Determinant of matrix nxn
 *
 * \param [in] Square Matrix A with nxn size
 * 
 * \return Determinant of matrix A
 */
template<typename T, std::size_t n>
T det(const Matrix<T, n, n>& A)
{
  // TODO do it using LU algorithm (faster)
  // auto LU = lu(A);
  // auto&& L = LU.first;
  // auto&& U = LU.second;
  return -1;
}


/**
 * \brief Minor of A - A with crossed-out i-th column and j-th row
 *
 * \param [in] Square Matrix A with nxn size
 * 
 * \return Minor of A matrix
 */
template<typename T, std::size_t n>
Matrix<T, (n-1), (n-1)> getminor(const Matrix<T, n, n>& A, std::size_t i, std::size_t j)
{
  Matrix<T, (n-1), (n-1)> minor{};
  std::size_t it = 0, jt = 0;
  for(std::size_t k = 0; k < n; k++)
  {
    for(std::size_t l = 0; l < n; l++)
    {
      if (k != i || l != j)
      {
        minor[it][jt] = A[k][l];
        jt++;
      }
    }
    it++; jt=0;
  }
  return minor;
}


/**
 * \brief Transpose of matrix nxm
 *
 * \param [in] Matrix A with nxm size
 * 
 * \return Transpose of matrix A
 */
template<typename T, std::size_t n, std::size_t m>
Matrix<T, m, n> trans(const Matrix<T, n, m>& A)
{
  Matrix<T, m, n> transA{};

  for (std::size_t i = 0; i < n; i++)
  {
    for (std::size_t j = 0; j < m; j++)
    {
      transA[j][i] = A[i][j];
    }
  }
  return transA;
}


/**
 * \brief Inverse of matrix 1x1
 *
 * \param [in] Square Matrix A with 1x1 size
 * 
 * \return Inverse of matrix A
 */
template<typename T>
Matrix<T, 1, 1> inv(const Matrix<T, 1, 1>& A)
{
  return Matrix<T, 1, 1>{ 1/det(A) };
}


/**
 * \brief Inverse of matrix 2x2
 *
 * \param [in] Square Matrix A with 2x2 size
 * 
 * \return Inverse of matrix A
 *         error with the A is zero
 */
template<typename T>
Matrix<T, 2, 2> inv(const Matrix<T, 2, 2>& A)
{
  Matrix<T, 2, 2> invA{};
  auto detA = det(A);
  if (detA == 0)
  {
    throw;
  }
  invA = {A[1][1], -A[0][1],
         -A[1][0],  A[0][0]};
  invA = invA / detA;
  return invA;
}


/**
 * \brief Inverse of matrix nxn
 *
 * \param [in] Square Matrix A with nxn size
 * 
 * \return Inverse of matrix A
 */
template<typename T, std::size_t n>
Matrix<T, n, n> inv(const Matrix<T, n, n>& A)
{
  Matrix<T, n, n> invA{};
  auto detA = det(A);
  for(std::size_t i = 0; i < n; i++)
  {
    for(std::size_t j = 0; j < n; j++)
    {
      invA[i][j] = (((i+j) % 2) ? 1 : -1) * det(getminor(A,i,j));
    }
  }
  invA = trans(invA) / detA;
  return invA;
}


/**
 * \brief Check if the matrix A is identity
 *
 * \param [in] Matrix A with nxn size
 * 
 * \return true - if A matrix is identity
 *         false - if A matrix is not identity
 */
template<typename T, std::size_t n>
bool isIdentity(const Matrix<T, n, n>& A)
{
  auto identity = eye<unsigned int, n>();
  auto uiA = static_cast<Matrix<unsigned int, n, n>>(A);
  return (uiA == identity);
}


/**
 * \brief Power of A matrix to p
 *
 * \param [in] Matrix A with nxn size
 * \param [in] Power number
 * 
 * \return Matrix A power by p
 */
template<typename T, typename P, std::size_t n>
Matrix<T, n, n> pow(Matrix<T, n, n>A, P p)
{
  if(p == 0)
  {
    return eye<T, n>();
  }

  else if(p == 1)
  {
    return A;
  }

  else
  {
    if(p < 0)
    {
      A = inv(A);
      p = std::abs(p);
    }

    auto powA = ones<T, n, n>();

    powA = pow(A, p/2);
    if ((p % 2) == 0)
    {
      return powA * powA;
    }
    else
    {
      return powA * powA * A;
    }
  }
}


/**
 * \brief Absolut value of matrix
 *
 * \param [in] Matrix A with ixj size
 * 
 * \return Matrix A which is result of absolut each element of matrix
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> abs(const Matrix<T, i, j>& A)
{
  Matrix<T, i, j> absA;

  for (std::size_t it = 0; it < i; it++)
  {
    for (std::size_t jt = 0; jt < j; jt++)
    {
      absA[it][jt] = std::abs(A[it][jt]);
    }
  }
  return absA;
}


/**
 * \brief Overloaded '+' operator of sum two matrices
 *
 * \param [in] Matrix A ixj
 * \param [in] Matrix B ixj
 * 
 * \return Result of sum matrix A and B
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> operator+(const Matrix<T, i, j>& A, const Matrix<T, i, j>& B)
{
	return sum(A, B);
}


/**
 * \brief Overloaded '+' operator for add matrix and scalar
 *
 * \param [in] Matrix A ixj
 * \param [in] Scalar data
 * 
 * \return Result of sum matrix A and scalar
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> operator+(const Matrix<T, i, j>& A, T scalar)
{
  return sum(A, scalar);
}


/**
 * \brief Overloaded '+' operator for add scalar and matrix
 *
 * \param [in] Scalar data
 * \param [in] Matrix A ixj
 * 
 * \return Result of sum scalar and matrix A
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> operator+(T scalar, const Matrix<T, i, j>& A)
{
  return sum(A, scalar);
}


/**
 * \brief Overloaded '-' operator for substraction two matrices
 *
 * \param [in] Matrix A ixj
 * \param [in] Matrix B ixj
 * 
 * \return Result of substraction matrix A and B
 */
template<typename T, std::size_t i, std::size_t j>
Matrix<T, i, j> operator-(const Matrix<T, i, j>& A, const Matrix<T, i, j>& B)
{
	return sub(A, B);
}


/**
 * \brief Overloaded '-' operator for substraction matrix and scalar
 *
 * \param [in] Matrix A ixj
 * \param [in] Scalar data
 * 
 * \return Result of substraction matrix A and scalar data
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> operator-(const Matrix<T, i, j>& A, T scalar)
{
  return sub(A, scalar);
}


/**
 * \brief Overloaded '*' operator for multiply two matrices
 *
 * \param [in] Matrix A
 * \param [in] Matrix B
 * 
 * \return Result of multiplication matrix A and B
 */
template<typename T,  std::size_t n, std::size_t m, std::size_t p>
Matrix<T, n, p> operator*(const Matrix<T, n, m>& A, const Matrix<T, m, p>& B)
{
	return mult(A, B);
}


/**
 * \brief Overloaded '*' operator for multiply matrix and scalar
 *
 * \param [in] Matrix A ixj
 * \param [in] Scalar data
 * 
 * \return Result of substraction matrix A and scalar
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> operator*(const Matrix<T, i, j>& A, T scalar)
{
  return mult(A, scalar);
}


/**
 * \brief Overloaded '*' operator for multiply scalar and matrix
 *
 * \param [in] Scalar data
 * \param [in] Matrix A ixj
 * 
 * \return Result of substraction scalar and matrix A
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> operator*(T scalar, const Matrix<T, i, j>& A)
{
  return mult(A, scalar);
}


/**
 * \brief Overloaded '/' operator for divide matrix and scalar
 *
 * \param [in] Matrix A ixj
 * \param [in] Scalar data
 *
 * \retirn Result of divide matrix A and scalar
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> operator/(const Matrix<T, i, j>& A, T scalar)
{
  return div(A, scalar);
}


/**
 * \brief Compare two matrices with the same size with specific error
 *
 * Usage: Check if two matrices are equal taking care about epsilon value
 *
 * \param [in] Matrix A ixj
 * \param [in] Matrix B ixj
 * \ Overloaded '/=' operator for divide matrix and scalar
 */
template<typename T,  std::size_t i, std::size_t j>
Matrix<T, i, j> operator/=(Matrix<T, i, j> A, T scalar)
{
  return div(A, scalar);
}


/**
 * \ Compare two matrices with the same size, specific error
 * \param [in] Matrix A ixj
 * \param [in] Matrix B ixj
 * \param [in] error
 *
 * return true if compare, otherwise false
 */
template<typename T, std::size_t i, std::size_t j>
bool compare(const Matrix<T, i, j>& A, const Matrix<T, i, j>& B, T epsilon)
{
  auto Err = fill<T, i, j>(epsilon);
  return abs(A - B) < Err;
}


 /**
 * \brief Multiplication two matrixec using Strassen algorithm
 * 
 * \param [in] Matrix A 2x2
 * \param [in] Matrix B 2x2
 * 
 * \return Result of multiplication matrix A and B
 */
template<typename T>
Matrix<T, 2, 2> strassen(const Matrix<T, 2, 2>& A, const Matrix<T, 2, 2>& B)
{
  Matrix<T, 2, 2> prod{};

  T M1 =  A[0][0] * (B[0][1] - B[1][1]);
  T M2 = (A[0][0] + A[0][1]) * B[1][1];
  T M3 = (A[1][0] + A[1][1]) * B[0][0];
  T M4 =  A[1][1] * (B[1][0] - B[0][0]);
  T M5 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
  T M6 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
  T M7 = (A[0][0] - A[1][0]) * (B[0][0] + B[0][1]);

  prod[0][0] = M5 + M4 - M2 + M6;
  prod[0][1] = M1 + M2;
  prod[1][0] = M3 + M4;
  prod[1][1] = ((M1 + M5) - (M3 + M7));

  return prod;
}

#endif /* MATRIX_HPP_ */