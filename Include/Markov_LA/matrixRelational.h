/*!
 * @file matrixRelational.h @brief Relational Operators between a Matrix and a single value

 */

#ifndef MATRIXRELATIONAL_H
#define MATRIXRELATIONAL_H

#include "Markov_LA/Matrix.h"


namespace Markov_LA
{

    template<typename T>
    bool operator<(const M_Matrix<T>& x, T f);

    template<typename T>
    bool operator>(const M_Matrix<T>& x, T f);


    template<typename T>
    bool operator>=(const M_Matrix<T>& x, T f);


    template<typename T>
    bool operator<=(const M_Matrix<T>& x, T f);


    template<typename T>
    bool operator==(const M_Matrix<T>& x, T f);


    template<typename T>
    bool operator!=(const M_Matrix<T>& x, T f);

}





#endif // MATRIXRELATIONAL_H
