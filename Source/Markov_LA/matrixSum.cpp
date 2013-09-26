/*!
 * @file matrixSum.cpp @brief Implementation of Sum, mean and differences in the
 elements of the Matrix

 */

#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixAritmetic.h"

namespace Markov_LA
{
    /**
    Sum of all the values in each Row or in each Column
    @param eachRow true: Sum all the values in each row
    @param eachRow false: sum all the values in each column
    */
    template<typename T>
    M_Matrix<T> sum(const M_Matrix<T>& x,bool eachRow)
    {
	if (eachRow)
	{
	    M_Matrix<T> sum_M=zeros<T>(nrows(x),1 );
	    for (std::size_t i=0; i < nrows(x) ; ++i)
		for (std::size_t j=0; j < ncols(x) ; ++j)
		    sum_M(i,0)+=x(i,j);
	    return sum_M;
	}
	else
	{
	    M_Matrix<T> sum_M=zeros<T>(size_t(1),ncols(x));
	    for (size_t i=0; i < nrows(x) ; i++)
		for (size_t j=0; j < ncols(x) ; j++)
		    sum_M(0,j)+=x(i,j);
	    return sum_M;
	};
    }

    /**
    Mean of a Matrix
    @param eachRow true  -> takes the mean of each row
    @param eachRow false -> takes the mean of each column
    */
    template<typename T>
    M_Matrix<double>  mean(const M_Matrix<T>& x, bool eachRow)
    {
	if (eachRow)
	    return sum(x,eachRow)/ncols(x);
	else
	    return sum(x,eachRow)/nrows(x);
    }





    /**
    Diference between contigous elements of  a Matrix
    @param eachRow true  -> takes the difference
    between consecutive elements of the same row
    @param eachRow false -> takes the difference
    between consecutive elements of the same column
    */
    template<typename T>
    M_Matrix<T> diff(const M_Matrix<T>& x,
		     bool eachRow)
    {
	M_Matrix<T> d(nrows(x),ncols(x));
	if (eachRow)
	{
	    for (std::size_t i=0; i<nrows(x); i++)
	    {
		d(i,0)=x(i,0);
		for (std::size_t j=1; j<ncols(x); j++)
		{
		    d(i,j)=x(i,j)-x(i,j-1);
		}
	    }
	}
	else
	{
	    for (std::size_t j=0; j<ncols(x); j++)
	    {
		d(0,j)=x(0,j);
		for (std::size_t i=1; i<nrows(x); i++)
		{
		    d(i,j)=x(i,j)-x(i-1,j);
		}
	    }
	}
	return d;
    }


    /**
    Cumulative sum over the contigous elements of  a Matrix
    @param eachRow true  -> acummulates the sum over consecutive
    elements of the same row
    @param eachRow false -> acummulates the sum over consecutive
    elements of the same column
    @invariant cumsum(diff(x))==x
    */
    template<typename T>
    M_Matrix<T> cumsum(const M_Matrix<T>& x,bool eachRow)
    {
	M_Matrix<T> d(nrows(x),ncols(x));
	if (eachRow)
	{
	    for (std::size_t i=0; i<nrows(x); i++)
	    {
		d(i,0)=x(i,0);
		for (std::size_t j=1; j<ncols(x); j++)
		{
		    d(i,j)=x(i,j)+d(i,j-1);
		}
	    }
	}
	else
	{
	    for (std::size_t j=0; j<ncols(x); j++)
	    {
		d(0,j)=x(0,j);
		for (std::size_t i=1; i<nrows(x); i++)
		{
		    d(i,j)=x(i,j)+d(i-1,j);
		}
	    }
	 }
	return d;

    }


    /**
      Sum of all the elements of a Matrix
    */

    template<typename T>
    T totalsum(const M_Matrix<T>& x)
    {
	T total(0);
	for (size_t i=0; i < size(x) ; ++i)
	    total+=x[i];
	return total;
    }


    /**
      Mean of all the elements of a Matrix
    */

    template<typename T>
    double totalmean(const M_Matrix<T>& x)
    {
	return double(totalsum(x))/size(x);
    }


    /**
      count non-zeroelements of a Matrix
    */

    template<typename T>
    std::size_t count(const M_Matrix<T>& x)
    {
	std::size_t count_=0;
	for (std::size_t i=0; i<size(x);i++)
	    if (x[i]!=T(0)) count_++;
	return count_;
    }





    template
    M_Matrix<double> sum(const M_Matrix<double>& x,
			 bool eachRow);


    template
    M_Matrix<double>  mean(const M_Matrix<double>& x,
			   bool eachRow);


    template
    M_Matrix<double> diff(const M_Matrix<double>& x,
		     bool eachRow);


    template
    M_Matrix<double> cumsum(const M_Matrix<double>& x,
			    bool eachRow);


    template
    double totalsum(const M_Matrix<double>& x);

    template
    double totalmean(const M_Matrix<double>& x);





    template
    M_Matrix<std::size_t> sum(const M_Matrix<std::size_t>& x,
			      bool eachRow);


    template
    M_Matrix<double>  mean(const M_Matrix<std::size_t>& x,
			   bool eachRow);


    template
    M_Matrix<std::size_t> diff(const M_Matrix<std::size_t>& x,
		     bool eachRow);


    template
    M_Matrix<std::size_t> cumsum(const M_Matrix<std::size_t>& x,
				 bool eachRow);


    template
    std::size_t totalsum(const M_Matrix<std::size_t>& x);

    template
    double totalmean(const M_Matrix<std::size_t>& x);

    template
    std::size_t count(const M_Matrix<std::size_t>& x);

    template
    std::size_t count(const M_Matrix<double>& x);





}

