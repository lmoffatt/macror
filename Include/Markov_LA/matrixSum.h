/*!
 * @file matrixSum.h @brief Sum, mean and differences in the elements of the Matrix

 */
#ifndef MATRIX_SUM_H
#define MATRIX_SUM_H

//#include "Markov_LA.h"
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{
    template<typename T>
    M_Matrix<T> sum(const M_Matrix<T>& x,bool eachRow=true);


    template<typename T>
    M_Matrix<double>  mean(const M_Matrix<T>& x, bool eachRow=true);


    template<typename T>
    M_Matrix<T> diff(const M_Matrix<T>& x,
		     bool eachRow=true);


    template<typename T>
    M_Matrix<T> cumsum(const M_Matrix<T>& x,bool eachRow=true);


    template<typename T>
    T totalsum(const M_Matrix<T>& x);

    template<typename T>
    double totalmean(const M_Matrix<T>& x);


    template<typename T>
    std::size_t count(const M_Matrix<T>& x);

}
#endif // MATRIX_SUM_H
