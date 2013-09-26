/*!
 * @file matrixInit.h @brief Diagonal Operator and Zero and Ones initializers

 */
#ifndef MATRIXINIT_H
#define MATRIXINIT_H
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{

    template<typename T>
    M_Matrix<T>  ones(size_t nrows_, size_t ncols_);

    template<typename T>
    M_Matrix<T>  ones(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T>  zeros(std::size_t nrows_, std::size_t ncols_);

    template<typename T>
    M_Matrix<T>  zeros(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T> eye(std::size_t n);




}  //end of namespace Markov_LA
#endif // MATRIXINIT_H
