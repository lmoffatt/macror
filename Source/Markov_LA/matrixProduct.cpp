/*!
 * @file matrixProduct.cpp @brief Matrix Transpose and/or Multiplication
 */
#include "Markov_LA/matrixProduct.h"
#include "Tests/AssertPlain.h"
#if ! USE_LAPACK_FOR_MATRIX_PRODUCT

namespace Markov_LA
{

    /**
     Transpose the first and multiply by the second
     @post transpMult(x,y)==Transpose(x)*y
     @remarks It is faster, since we save copying matrices
    */
    template<typename T>
    M_Matrix<T> TranspMult(const M_Matrix<T>& x,const M_Matrix<T>& y)
    {
	// First it has to find out if the last dimension of x matches the first of y
	ASSERT_EQ(nrows(x),nrows(y));
	// now we build the M_Matrix result
	M_Matrix<T> z=zeros<T> (ncols(x),ncols(y));
	// we build the dimensions std::vector of the result
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		for (size_t k=0; k<nrows(x); k++)
		    z(i,j)+=x(k,i)*y(k,j);
	return z;
    }

    /**
     Multiply by the Transpose of the second matrix
     @post MultTransp(x,y)==x*Transpose(y)
     @remarks It is faster, since we save copying matrices
    */
    template<typename T>
    M_Matrix<T> multTransp(const M_Matrix<T>& x,const M_Matrix<T>& y)
    {
	// First it has to find out if the last dimension of x matches the first of y
	ASSERT_EQ(ncols(x),ncols(y));
	// now we build the M_Matrix result
	M_Matrix<T> z=zeros<T> (nrows(x),nrows(y));
	// we build the dimensions std::vector of the result
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		for (size_t k=0; k<ncols(x); k++)
		    z(i,j)+=x(i,k)*y(j,k);
	return z;
    }



    /**
    Matrix multiplication.
    @pre \p ncols(x)==nrows(y)
    @returns z=x*y
    @post nrows(z)=rows(x), ncols(z)=ncols(y)
    @post z(i,j)= sum on k of x(i,k)*y(k,j)
    @post assert(ncols(x)==nrows(y))
    */
    template<typename T>
    M_Matrix<T> operator*(const M_Matrix<T>& x,const M_Matrix<T>& y)
    {
	// First it has to find out if the last dimension of x matches the
	//first of y
	ASSERT_EQ(ncols(x),nrows(y));
	// now we build the M_Matrix result
	M_Matrix<T> z=zeros<T> (nrows(x),ncols(y));
	// we build the dimensions std::vector of the result
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		for (size_t k=0; k<ncols(x); k++)
		    z(i,j)+=x(i,k)*y(k,j);
	return z;
    }

    M_Matrix<double> operator*(const M_Matrix<std::size_t>& x,
			       const M_Matrix<double>& y)
    {
	// First it has to find out if the last dimension of x matches the
	//first of y
	ASSERT_EQ(ncols(x),nrows(y));
	// now we build the M_Matrix result
	M_Matrix<double> z=zeros<double> (nrows(x),ncols(y));
	// we build the dimensions std::vector of the result
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		for (size_t k=0; k<ncols(x); k++)
		    z(i,j)+=x(i,k)*y(k,j);
	return z;
    }



    M_Matrix<double> operator*(const M_Matrix<double>& x,
			       const M_Matrix<std::size_t>& y)
    {
	// First it has to find out if the last dimension of x matches the
	//first of y
	ASSERT_EQ(ncols(x),nrows(y));
	// now we build the M_Matrix result
	M_Matrix<double> z=zeros<double> (nrows(x),ncols(y));
	// we build the dimensions std::vector of the result
	for (size_t i=0; i<nrows(z); i++)
	    for (size_t j=0; j<ncols(z); j++)
		for (size_t k=0; k<ncols(x); k++)
		    z(i,j)+=x(i,k)*y(k,j);
	return z;
    }





    template
    M_Matrix<double> TranspMult(const M_Matrix<double>& x,const M_Matrix<double>& y);

    template
    M_Matrix<double> multTransp(const M_Matrix<double>& x,const M_Matrix<double>& y);

    template
    M_Matrix<double> operator*(const M_Matrix<double>& x,const M_Matrix<double>& y);



}//end of namespace Markov_LA

#endif // end of USE_LAPACK_FOR_MATRIX_PRODUCT
