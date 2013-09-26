#ifndef MATRIXOPERATORS_H
#define MATRIXOPERATORS_H

#include "Markov_LA/Matrix.h"

namespace Markov_LA
{
    template<typename T>
    M_Matrix<T>  Transpose(const M_Matrix<T>& X);

    template<typename T>
    M_Matrix<T> diag(const M_Matrix<T>& x);

    template<typename T>
    T diagProduct(const M_Matrix<T>& x);


    template<typename T>
    M_Matrix<T> col_vector(const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T> row_vector(const M_Matrix<T>& x);


}



#endif // MATRIXOPERATORS_H
