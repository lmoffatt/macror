/*!
 * @file matrixInverse.cpp @brief Implementation of the Inverse of a Matrix

 */

#include <stdexcept> // for std::runtime_error

#include <iostream>
#include "Markov_LA/matrixInverse.h"

#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixRand.h"
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixAssigmentOp.h"
#include  "Markov_LA/matrixRelational.h"

#include "Markov_LA/auxiliarMath.h"

namespace
{
extern "C" void dgetrf_(int *M,
			 int* N,
			 double *A,
			 int* LDA,
			 int* IPIV,
			 int * INFO );

extern "C" void dgetri_(int* n,
			double *B,
			int* dla,
			int* ipiv,
			double* work1,
			int* lwork,
			int* info);

}


namespace Markov_LA
{



/**
Constructor
*/
SingularMatrix_error::SingularMatrix_error(const char* msg)
    : std::runtime_error(msg) { }

template<typename T>
M_Matrix<T> inv(const M_Matrix<T>& a)
{
  if ((size(a)>0)&&(nrows(a)==ncols(a)))
    {
	double *A, *work, *work1;
	int info=0;
	//  char msg[101];
	int *ipiv;
	int lwork;
	int n =ncols(a);
	int m=n;
	M_Matrix<T> B(a);
	int dla=n;
	//A=new double[n*n];
	A= new double[n*n]; //more efficient code
	for (size_t k = 0; k < size_t(n*n); k++)
	    *(A+k) = a[k];

	ipiv = new int[n];
	try{
	dgetrf_(&n, &m, A, &dla,ipiv,&info);
	}
	catch(...)
	{
	  std::cerr<<" degetrf_ error";
	}

	lwork= -1;
	work1 = new double[2];
	try
	{
	dgetri_(&n,A,&dla,ipiv,work1,&lwork,&info);
	lwork = (int)(work1[0]);
	work = new double [2*lwork];
	dgetri_(&n,A,&dla,ipiv,work,&lwork,&info);
	}
	catch (...)
	{
	  std::cerr<<" dgetri_ error";
	}

	for (size_t k = 0; k < size_t(n*n); k++)
	    B[k] = *(A+k);
	delete [] ipiv;
	delete [] work;
	delete [] work1;
	if (info!=0)
	{
	    throw SingularMatrix_error("cannot invert a singular matrix");
	}
	return B;
    }
    else
	return a;
}


M_Matrix<double> invSafe(const M_Matrix<double>& matrix)
{
  if ((matrix==0.0)||(!isFinite(matrix)))
      return matrix;
    M_Matrix<double> inverse;
    try
    {
	inverse=inv(matrix);
    }
    catch (SingularMatrix_error)
    {
	std::cerr<<" singular matrix\n"<<matrix;
	M_Matrix<double>
		noise=Rand(matrix)*(1e-7*norm_inf(matrix));
	std::cerr<<" noise\n"<<noise;


		inverse=inv(matrix+noise);
		std::cerr<<" inverse\n"<<inverse;
    }
return inverse;
}




template M_Matrix<double> inv(const M_Matrix<double>& a);


}



