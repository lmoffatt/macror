/*!
 * @file matrixMaxMin.h @brief elementary Statistics on Matrices.
Max,min, sum, cumsum and diff

 */
#ifndef MATRIXMAXMIN_H
#define MATRIXMAXMIN_H
#include "Markov_LA/Matrix.h"
#include <cmath>

namespace Markov_LA
{

    template<class T>
    T maxAbs(const M_Matrix<T>& x);

    template<class T>
    T minAbs(const M_Matrix<T>& x);

    template<class T>
    T max(const M_Matrix<T> & x);

    template<class T>
    T min(const M_Matrix<T> & x);

    template<class T>
    T minPositive(const M_Matrix<T> & x);


    template<typename T>
    T norm_inf(const M_Matrix<T>& x);

    template<typename T>
    T norm(const M_Matrix<T>& x);
}

#endif // MATRIXMAXMIN_H
