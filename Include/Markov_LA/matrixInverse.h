/*!
 * @file matrixInverse.h @brief Inverse of a Matrix

 */

#ifndef MATRIXINVERSE_H
#define MATRIXINVERSE_H
#include <stdexcept> // for std::runtime_error
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{

    template<typename T>
    M_Matrix<T> inv(const M_Matrix<T>& a);


    /**
      Exception class for matrix singularity (i.e, that do not have Matrix
    Inverse)
    */
    class SingularMatrix_error: public std::runtime_error
    {
    public:
	SingularMatrix_error(const char* msg);
    };


    M_Matrix<double> invSafe(const M_Matrix<double>& a);
}



#endif // MATRIXINVERSE_H
