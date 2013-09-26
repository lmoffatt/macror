/*!
 * @file matrixExp.cpp @brief Implements the Exponential of a Matrix

 */
#include <cmath>
#include <iostream>  //cout



#include "Markov_LA/matrixExp.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/matrixIO.h"

#include "Tests/AssertPlain.h"

namespace Markov_LA
{

/**
Returns the exponential of a Matrix
@remarks  uses the Pade approximation
@pre the matrix has to be square, ncols()==nrows
@post assert the precondition

*/

template<typename T>
M_Matrix<T>  expm(const M_Matrix<T>& x)
{
    assert(ncols(x)==nrows(x));
    assert(size(x)>0);

    // Scale A by power of 2 so that its norm is < 1/2 .
    double e = std::ceil(log(norm_inf(x))/log(2));
    std::size_t s = std::max(0.0,e+1);

    M_Matrix<T> A = x/std::pow(2.0,int(s));



    // Pade approximation for exp(A)
    M_Matrix<T> X = A;
    double c = 0.5;
    M_Matrix<T> E = eye<T>(nrows(A)) + c*A;
    M_Matrix<T> D = eye<T>(nrows(A)) - c*A;


    std::size_t q = 6;
    bool p = true;
    for (std::size_t k = 2; k<q+1;++k)
    {
	c = c * (1.0*q-1.0*k+1) / (1.0*k*(2.0*q-k+1.0));
	X = A*X;
	M_Matrix<T> cX = c*X;
	E += cX;
	if (p)
	    D += cX;
	else
	    D -= cX;
	p = !p;
    }
    E = invSafe(D)*E;

    // Undo scaling by repeated squaring
    for (std::size_t k=0; k<s;k++)
	 E = E*E;
    return E;



}

template M_Matrix<double> expm<double>(const M_Matrix<double>& x);



}


