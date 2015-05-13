/*!
 * @file matrixMaxMin.cpp
@brief Implementation of Elementary Statistics on Matrices. Max,min, sum, cumsum
 and diff

 */

#include <cmath>

#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/auxiliarMath.h"
namespace Markov_LA
{
    /**
    Maximum absolute value of the elements of a Matrix
    @post abs(matrix)<MaxAbs(matrix)

    */
    template<class T>
    T maxAbs(const M_Matrix<T>& x)
    {
	using std::abs;
	T maxval=x[0];

	for (size_t i=1; i<size(x); ++i)
	    if (abs(x[i])>maxval)
		maxval=abs(x[i]);
	return maxval;
    }

    /**
    Minimum absolute value of the elements of a Matrix
    @post abs(matrix)<MaxAbs(matrix)

    */
    template<class T>
    T minAbs(const M_Matrix<T>& x)
    {
	using std::abs;
	T minval=abs(x[0]);

	for (size_t i=1; i<size(x); ++i)
	    if (abs(x[i])<minval)
		minval=abs(x[i]);
	return minval;
    }

    /**
    Maximum value of all the elements of the matrix
    @post matrix<max(matrix)
    */
    template<class T>
    T max(const M_Matrix<T> & x)
    {
	T maxval=x[0];
	for (size_t i=1; i<size(x); ++i)
	    if (x[i]>maxval)
		maxval=x[i];
	return maxval;
    }

    /**
    Minimum value of all the elements of the matrix
    @post matrix>min(matrix)
    */
    template<class T>
    T min(const M_Matrix<T> & x)
    {
	T minval=x[0];
	for (size_t i=1; i<size(x); ++i)
	    if (x[i]<minval)
		minval=x[i];
	return minval;
    }


    /**
    Minimum value of all the elements of the matrix
    that is greater than zero
    @post matrix>min(matrix)
    */
    template<class T>
    T minPositive(const M_Matrix<T> & x)
    {
        std::size_t j=0;
        while (j<size(x)&&(x[j]<=0))
            ++j;
        double minval=x[j];
        for (size_t i=j; i<size(x); ++i)
            if ((x[i]>0.0)&&(x[i]<minval))
                minval=x[i];
        return minval;
    }





    /**
      Maximum Value of the Sum of the absolute values in each row
     */
     template<typename T>
    T norm_inf(const M_Matrix<T>& x)
    {
	T n(0);
	for (size_t i=0; i<nrows(x); ++i)
	{
	    T sum(0);
	    for (size_t j=0; j<ncols(x); ++j)
		if (x(i,j)>0)
		    sum+=x(i,j);
	    else
		sum-=x(i,j);

	    n=std::max(n,sum);
	}
	return n;
    }


    /**
      Norm of the vector composed by all the elements of the Matrix
    */
    template<typename T>
    T norm(const M_Matrix<T>& x)
    {
	T n(0);
	for (size_t i=0; i<size(x); ++i)
	{
	    n+=x[i]*x[i];
	}
	return std::sqrt(n);
    }





    template
    double maxAbs(const M_Matrix<double>& x);

    template
    double minAbs(const M_Matrix<double>& x);

    template
    double max(const M_Matrix<double> & x);

    template
    double min(const M_Matrix<double> & x);

    template
    double minPositive(const M_Matrix<double> & x);

    template
    double norm_inf(const M_Matrix<double>& x);

    template
    double norm(const M_Matrix<double>& x);



    template
    int maxAbs(const M_Matrix<int>& x);

    template
    int minAbs(const M_Matrix<int>& x);

    template
    int max(const M_Matrix<int> & x);

    template
    int min(const M_Matrix<int> & x);

    template
    int minPositive(const M_Matrix<int> & x);

    template
    int norm_inf(const M_Matrix<int>& x);

    template
    int norm(const M_Matrix<int>& x);





    template
    std::size_t max(const M_Matrix<std::size_t> & x);

    template
    std::size_t min(const M_Matrix<std::size_t> & x);

    template
    std::size_t minPositive(const M_Matrix<std::size_t> & x);

    template
    std::size_t norm_inf(const M_Matrix<std::size_t>& x);

    template
    std::size_t norm(const M_Matrix<std::size_t>& x);



}
