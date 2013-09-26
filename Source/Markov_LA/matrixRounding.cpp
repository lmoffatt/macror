/*!
 * @file matrixRounding.cpp @brief rounding Matrices

 */
#include <cmath>
#include "Markov_LA/matrixRounding.h"
#include "Markov_LA/ToleranceComparison.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/auxiliarMath.h"

namespace Markov_LA
{
    /**
      Force to zero all the elements close to it.
      @post tol.isEqual(data[i],T(0))->data[i]==0
     */
    template<typename T>
    void round_to_zero(M_Matrix<T>& data)
    {
	ToleranceComparison<T> tol(
		std::numeric_limits<T>::epsilon()*norm_inf(data),
		std::numeric_limits<T>::epsilon());

	for (std::size_t i=0; i<size(data); i++)
	    if (tol.isEqual(data[i],T(0)))
		data[i]=T(0);
    }


    /**
      checks that all the values in the matrix are finite
    */
    template<typename T>
    bool isfinite(const M_Matrix<T>& x)
    {
	for (std::size_t i=0; i<size(x); i++)
	  if (!isFinite(x[i])) return false;
	return true;
    }


    template
    void round_to_zero(M_Matrix<double>& data);


    template
    bool isfinite<double>(const M_Matrix<double>& x);



};

