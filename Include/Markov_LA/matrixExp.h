/*!
 * @file matrixExp.h @brief Exponential of a Matrix

 */



#ifndef MATRIXEXP_H
#define MATRIXEXP_H
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{
template<typename T>
M_Matrix<T>  expm(const M_Matrix<T>&);

}

#endif // MATRIXEXP_H
