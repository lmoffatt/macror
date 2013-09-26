/*!
 * @file matrixRounding.h @brief rounding Matrices

 */
#ifndef MATRIXROUNDING_H
#define MATRIXROUNDING_H

#include <cmath>
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{
    template<typename T>
    void round_to_zero(M_Matrix<T>& data);

    template<typename T>
    bool isfinite(const M_Matrix<T>& x);


};

#endif // MATRIXROUNDING_H
