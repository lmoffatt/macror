#include "Markov_LA/matrixOperators.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/Matrix.h"

namespace Markov_LA
{
/**
    Transpose
    @post (Transpose(x))(i,j)==x(j,i)
    @returns the Transpose of the Matrix
    */

template<class T>
M_Matrix<T>  Transpose(const M_Matrix<T>& X)
{
    M_Matrix<T> tr(ncols(X),nrows(X));
    for (size_t i=0; i<nrows(tr); i++)
	for (size_t j=0; j<ncols(tr); j++)
	    tr(i,j)=X(j,i);
    return tr;
}



/**
     Diagonal of Matrix or Diagonal Matrix
     It has two behaviors:
     - If the input is a single column or a single row, it builds a diagonal
     Matrix with it
     - If the input is a Matrix, it returns the values of its diagonal

    */
template<typename T>
M_Matrix<T> diag(const M_Matrix<T>& x)
{
    size_t nr=nrows(x);
    size_t nc=ncols(x);
    if ((nr>1)&(nc>1))
    {
	std::size_t n=std::min(nr,nc);
	M_Matrix<T> diagM= zeros<T> ( 1,n);
	for (size_t i=0; i<n; ++i)
	    diagM(0,i)=x(i,i);
	return diagM;
    }
    else
    {
	nr=std::max(nr,nc);
	M_Matrix<T> diagM=zeros<T>(nr,nr);
	for (size_t i=0; i<nr; ++i)
	    diagM(i,i)=x[i];
	return diagM;
    }

}

/**
     Product of the Diagonal of a Matrix

    */
template<typename T>
T diagProduct(const M_Matrix<T>& x)
{
    size_t nr=nrows(x);
    size_t nc=ncols(x);
    double diagprod=1;
    std::size_t n=std::min(nr,nc);
    for (size_t i=0; i<n; ++i)
	diagprod*=x(i,i);
    return diagprod;


}




template<typename T>
M_Matrix<T> col_vector(const M_Matrix<T>& x)
{
    M_Matrix<T> colvec(size(x),1);
    for (std::size_t i=0; i<size(x); ++i)
	colvec[i]=x[i];
    return colvec;
}
template<typename T>
M_Matrix<T> row_vector(const M_Matrix<T>& x)
{
    M_Matrix<T> rowvec(1,size(x));
    for (std::size_t i=0; i<size(x); ++i)
	rowvec[i]=x[i];
    return rowvec;
}


template
M_Matrix<double>  Transpose(const M_Matrix<double>& X);



template
M_Matrix<std::size_t> diag(const M_Matrix<std::size_t>& x);
template
M_Matrix<double> diag(const M_Matrix<double>& x);

template
std::size_t diagProduct(const M_Matrix<std::size_t>& x);
template
double diagProduct(const M_Matrix<double>& x);


template
M_Matrix<double> col_vector(const M_Matrix<double>& x);

template
M_Matrix<std::size_t> col_vector(const M_Matrix<std::size_t>& x);

template
M_Matrix<double> row_vector(const M_Matrix<double>& x);

template
M_Matrix<std::size_t> row_vector(const M_Matrix<std::size_t>& x);


}

