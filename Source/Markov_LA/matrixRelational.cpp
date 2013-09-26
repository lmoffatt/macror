/*!
 * @file matrixRelational.cpp
   @brief Implementation of relational operators between a Matrix and a single
value

Template generalization of relational operators for any Type with epsilon check

 */
#include <limits>
#include <cmath>
#include <vector>

#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/ToleranceComparison.h"
#include "Markov_LA/matrixMaxMin.h"

namespace Markov_LA
{

    /**
@name Relational operators between a container and a value
@returns true if all the elements of the container follow the tested relation
@returns false if \b any of the elements fails to follow the tested relation
@warning therefore, these relational operators do not have the same logical
content i.e, that if it is false that V>x does not mean that it is true that
      V<=x
  */

    //{@


    /**
  Every element of the matrix is less than a given value
  @returns true if every element of the matrix is less than the value
  @returns false if any element of the matrix is greater or equal to the value
*/

    template<typename T>
    bool operator<(const M_Matrix<T>& x, T f){
	ToleranceComparison<T> tol(
		std::numeric_limits<T>::epsilon()*norm_inf(x),
		std::numeric_limits<T>::epsilon());
	for (size_t i=0;i<size(x); ++i)
	{
	    if (! tol.isLess(x[i], f))
		return false;
	}
	return true;
    }

    /**
  Every element of the matrix is greater than a given value
  @returns true if every element of the matrix is greater than the value
  @returns false if any element of the matrix is less than or equal to the value
*/

    template<typename T>
    bool operator>(const M_Matrix<T>& x, T f)
    {
	ToleranceComparison<T> tol(
		std::numeric_limits<T>::epsilon()*norm_inf(x),
		std::numeric_limits<T>::epsilon());
	for (size_t i=0;i<size(x); ++i)
	{
	    if (!tol.isGreater(x[i],f)) return false;
	}
	return true;
    }

    /**
  Every element of the matrix is greater than or equal to a given value
  @returns true if every element of the matrix is greater than or equal to the value
  @returns false if any element of the matrix is less than the value
*/
    template<typename T>
    bool operator>=(const M_Matrix<T>& x, T f){
	ToleranceComparison<T> tol(
		std::numeric_limits<T>::epsilon()*norm_inf(x)*100,
		std::numeric_limits<T>::epsilon()*100);
	for (size_t i=0;i<size(x); ++i)
	{
	    if (tol.isLess(x[i],f)) return false;
	}
	return true;
    }

    /**
  Every element of the matrix is less than or equal to a given value
  @returns true if every element of the matrix is less than or equal to the value
  @returns false if any element of the matrix is greater than value
*/
    template<typename T>
    bool operator<=(const M_Matrix<T>& x, T f){
	ToleranceComparison<T> tol(
		std::numeric_limits<T>::epsilon()*norm_inf(x),
		std::numeric_limits<T>::epsilon());
	for (size_t i=0;i<size(x); ++i)
	{
	    if (tol.isGreater(x[i],f)) return false;
	}
	return true;
    }

    /**
  Every element of the matrix is equal to a given value
  @returns true if every element of the matrix is  equal to the value
  @returns false if any element of the matrix is greater than or less than the
  value
*/
    template<typename T>
    bool operator==(const M_Matrix<T>& x, T f){
	ToleranceComparison<T> tol(
                std::numeric_limits<T>::epsilon()*norm_inf(x),
                std::numeric_limits<T>::epsilon());
	for (size_t i=0;i<size(x); ++i)
	{
	    if (!tol.isEqual(x[i],f)) return false;
	}
	return true;
    }

    /**
  Every element of the matrix is not equal to a given value
  @returns true if every element of the matrix is greater of less than the value
  @returns false if any element of the matrix is equal to the
  value
  example if (v!=0) it is safe to divide by each one of the values of v.
  @warning the thrichotomy law does not apply, since the fact that neither of
the values of a matrix are equal to the tested value does not means that all of
them are greater than it or less than it.
*/
    template<typename T>
    bool operator!=(const M_Matrix<T>& x, T f){
	ToleranceComparison<T> tol(
		std::numeric_limits<T>::epsilon()*norm_inf(x),
		std::numeric_limits<T>::epsilon());
	for (size_t i=0;i<size(x); ++i)
	{
	    if (tol.isEqual(x[i],f)) return false;
	}
	return true;
    }

    //@}



    template
    bool operator<(const M_Matrix<double >& x, double  f);

    template
    bool operator>(const M_Matrix<double >& x, double  f);


    template
    bool operator>=(const M_Matrix<double >& x, double  f);


    template
    bool operator<=(const M_Matrix<double >& x, double  f);


    template
    bool operator==(const M_Matrix<double >& x, double  f);


    template
    bool operator!=(const M_Matrix<double >& x, double  f);





    template
    bool operator<(const M_Matrix<std::size_t >& x, std::size_t  f);


    template
    bool operator>(const M_Matrix<std::size_t >& x, std::size_t  f);


    template
    bool operator>=(const M_Matrix<std::size_t >& x, std::size_t  f);


    template
    bool operator<=(const M_Matrix<std::size_t >& x, std::size_t  f);


    template
    bool operator==(const M_Matrix<std::size_t >& x, std::size_t  f);


    template
    bool operator!=(const M_Matrix<std::size_t >& x, std::size_t  f);



}




