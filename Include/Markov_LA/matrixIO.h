/*!
 * @file matrixIO.h @brief I/O operations on Matrix

 */

#ifndef MATRIXIO_H
#define MATRIXIO_H
#include "Markov_LA/Matrix.h"
#include <iostream>


namespace Markov_LA
{

    template<typename T>
    std::istream& operator>> (std::istream& s, M_Matrix<T>& A);

    template<typename T>
    std::ostream& operator<< (std::ostream& s,const M_Matrix<T>& A);
}
#endif // MATRIXIO_H
