/*!
 * @file matrixAssigmentOp.h @brief Assigment Operators

Assigment aritmetic operators on single values or on another Matrix.

 */



#ifndef ASSIGMENTTOVALUES_H
#define ASSIGMENTTOVALUES_H

#include "Markov_LA/Matrix.h"




namespace Markov_LA
{
   template<typename T>
    M_Matrix<T>& operator+=(M_Matrix<T>& itself, T x);

    template<typename T>
    M_Matrix<T>& operator-=(M_Matrix<T>& itself, T x);

    template<typename T>
    M_Matrix<T>& operator*=(M_Matrix<T>& itself, T x);

    template<typename T>
    M_Matrix<T>& operator/=(M_Matrix<T>& itself, T x);


    template<typename T>
    M_Matrix<T>& operator+=(M_Matrix<T>& itself,
			    const M_Matrix<T>& other);

    template<typename T>
    M_Matrix<T>& operator-=(M_Matrix<T>& itself,
			    const M_Matrix<T>& other);


    template<typename T,typename S>
    M_Matrix<T>& operator+=(M_Matrix<T>& itself,
			    const M_Matrix<S>& other);

    template<typename T,typename S>
    M_Matrix<T>& operator-=(M_Matrix<T>& itself,
			    const M_Matrix<S>& other);


}

#endif // ASSIGMENTTOVALUES_H
