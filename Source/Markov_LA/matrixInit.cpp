/*!
 * @file matrixInit.cpp
@brief Implementation of Diagonal Operator and Zero and Ones initializers

 */
#include "Markov_LA/matrixInit.h"

namespace Markov_LA
{
    /**
     Returns a custom sized Matrix filled with ones
    @post (ones(n,m))(i,j)==T(1)
     */
    template<typename T>
    M_Matrix<T>  ones(size_t nrows_, size_t ncols_)
    {
	M_Matrix<T> A(nrows_,ncols_);
	for (size_t i=0; i<size(A); ++i)
	    A[i]=1;
	return A;
    }

    /**
     Matrix filled with ones with the shape of the provided Matrix
     @post nrows(ones(x))==nrows(x)   ncols(ones(x))=ncols(x)
     */
    template<typename T>
    M_Matrix<T>  ones(const M_Matrix<T>& x)
    {
	M_Matrix<T> A(nrows(x),ncols(x));
	for (size_t i=0; i<size(A); ++i)
	    A[i]=1;

	return A;
    }
    /**
      Custom sized Matrix filled with zeros
    */
    template<typename T>
    M_Matrix<T>  zeros(std::size_t nrows_, std::size_t ncols_)
    {
	M_Matrix<T> A(nrows_,ncols_);
	for (std::size_t i=0; i<size<T>(A); ++i)
	    A[i]=0;
	return A;
    }

    /**
    Matrix of zeros with the shape of the provided Matrix
     @post nrows(ones(x))==nrows(x)   ncols(ones(x))=ncols(x)

    */
    template<typename T>
    M_Matrix<T>  zeros(const M_Matrix<T>& x)
    {
	M_Matrix<T> A(nrows(x),ncols(x));
	for (std::size_t i=0; i<size(A); ++i)
	    A[i]=0;

	return A;
    }

    /**
     Identity Matrix of the specified size
    */
    template<typename T>
    M_Matrix<T> eye(std::size_t n)
    {
	M_Matrix<T> A=zeros<T>(n,n);
	for (size_t i=0; i<n; ++i)
	    A(i,i)=T(1);
	return A;
    }


    /**
      Template Instantiations
      */

    template
	    M_Matrix<double>  ones(size_t nrows_, size_t ncols_);

    template
	    M_Matrix<double>  ones(const M_Matrix<double>& x);

    template
	    M_Matrix<double>  zeros(std::size_t nrows_, std::size_t ncols_);

    template
	    M_Matrix<double>  zeros(const M_Matrix<double>& x);

    template
	    M_Matrix<double> eye(std::size_t n);



    template
	    M_Matrix<std::size_t>  ones(size_t nrows_, size_t ncols_);

    template
	    M_Matrix<std::size_t>  ones(const M_Matrix<std::size_t>& x);

    template
	    M_Matrix<std::size_t>  zeros(std::size_t nrows_, std::size_t ncols_);

    template
	    M_Matrix<std::size_t>  zeros(const M_Matrix<std::size_t>& x);

    template
	    M_Matrix<std::size_t> eye(std::size_t n);



}

