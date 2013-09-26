/*!
 * @file matrixProduct.h @brief Matrix Multiplication and elementary Matrices
 */
#ifndef MATRIXPRODUCT_H
#define MATRIXPRODUCT_H
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixInit.h"

#define USE_LAPACK_FOR_MATRIX_PRODUCT 1




namespace Markov_LA
{

    template<typename T>
    M_Matrix<T> TranspMult(const M_Matrix<T>& x,const M_Matrix<T>& y);

    template<typename T>
    M_Matrix<T> multTransp(const M_Matrix<T>& x,const M_Matrix<T>& y);

    template<typename T>
    M_Matrix<T> operator*(const M_Matrix<T>& x,const M_Matrix<T>& y);

    M_Matrix<double> operator*(const M_Matrix<std::size_t>& x,
			       const M_Matrix<double>& y);


    M_Matrix<double> operator*(const M_Matrix<double>& x,
			       const M_Matrix<std::size_t>& y);

}
#endif // MATRIXPRODUCT_H
