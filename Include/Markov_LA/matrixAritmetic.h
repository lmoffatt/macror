/*!
 * @file matrixAritmetic.h @brief Aritmetic Operators
   Aritmetic operators,addition, subtraction, multiplication or division,
  applied between 1. Each element of the matrix and a scalar. Or 2. Between
  homologous positions in the matrix.

  @warning all the divisions returned Matrix of doubles, irrespective of the
type of the divided entities.



 */



#ifndef MATRIXARITMETIC_H
#define MATRIXARITMETIC_H
#include "Markov_LA/Matrix.h"



/*


namespace Markov_LA
{

    template<typename T>
    M_Matrix<T> operator+(const M_Matrix<T>& x,T t);

    template<typename T>
    M_Matrix<T> operator+(T t,const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T> operator-(const M_Matrix<T>& x,T t);

    template<typename T>
    M_Matrix<T> operator-(T t,const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T> operator*(const M_Matrix<T>& x,T t);

    template<typename T>
    M_Matrix<T> operator*(T t,const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<double> operator/(const M_Matrix<T>& x,T t);

    template<typename T,typename S>
    M_Matrix<double> operator/(const M_Matrix<T>& x,S t);


    template<typename T>
    M_Matrix<double> operator/(T t,const M_Matrix<T>& x);

    template<typename T>
    M_Matrix<T> operator+(const M_Matrix<T>& x,const M_Matrix<T>& y);

    template<typename T>
    M_Matrix<T> operator-(const M_Matrix<T>& x,const M_Matrix<T>& y);

    template<typename T>
    M_Matrix<T> elemMult(const M_Matrix<T>& x,const M_Matrix<T>& y);

    template<typename T,typename S>
    M_Matrix<double> elemDiv(const M_Matrix<T>& x,const M_Matrix<S>& y);

    template<typename T,typename S>
    M_Matrix<double> elemDivSafe(const M_Matrix<T>& x,const M_Matrix<S>& y);


}

*/

#endif // MATRIXARITMETIC_H

