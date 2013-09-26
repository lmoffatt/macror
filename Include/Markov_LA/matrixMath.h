/*!
 * @file matrixMath.h @brief Simple operations on the elements of a Matrix
 */
#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include "Markov_LA/Matrix.h"

namespace Markov_LA
{

    template<typename T>
    M_Matrix<T>  abs(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T> operator-(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T>  exp(const M_Matrix<T>& x);


    template<typename T>
    M_Matrix<T>  exp10(const M_Matrix<T>&);

    template<typename T>
    M_Matrix<T>  log10(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T>  sqrt(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T>  log(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T>  floor(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T>  ceil(const M_Matrix<T>& x);


}
#endif // MATRIXMATH_H
