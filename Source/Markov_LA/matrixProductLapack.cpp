/*!
 * @file matrixProduct.cpp @brief Matrix Transpose and/or Multiplication
 */
#include "Markov_LA/matrixProduct.h"
#include "Tests/AssertPlain.h"
#include <iostream>

#if  USE_LAPACK_FOR_MATRIX_PRODUCT

namespace Markov_LA
{



  /**
  Blas

SUBROUTINE DGEMM(TRANSA,TRANSB,M,N,K,ALPHA,A,LDA,B,LDB,BETA,C,LDC)
*     .. Scalar Arguments ..
      DOUBLE PRECISION ALPHA,BETA
      INTEGER K,LDA,LDB,LDC,M,N
      CHARACTER TRANSA,TRANSB
*     ..
*     .. Array Arguments ..
      DOUBLE PRECISION A(LDA,*),B(LDB,*),C(LDC,*)
*     ..
*
*  Purpose
*  =======
*
*  DGEMM  performs one of the matrix-matrix operations
*
*     C := alpha*op( A )*op( B ) + beta*C,
*
*  where  op( X ) is one of
*
*     op( X ) = X   or   op( X ) = X',
*
*  alpha and beta are scalars, and A, B and C are matrices, with op( A )
*  an m by k matrix,  op( B )  a  k by n matrix and  C an m by n matrix.
*
*  Arguments
*  ==========
*
*  TRANSA - CHARACTER*1.
*           On entry, TRANSA specifies the form of op( A ) to be used in
*           the matrix multiplication as follows:
*
*              TRANSA = 'N' or 'n',  op( A ) = A.
*
*              TRANSA = 'T' or 't',  op( A ) = A'.
*
*              TRANSA = 'C' or 'c',  op( A ) = A'.
*
*           Unchanged on exit.
*
*  TRANSB - CHARACTER*1.
*           On entry, TRANSB specifies the form of op( B ) to be used in
*           the matrix multiplication as follows:
*
*              TRANSB = 'N' or 'n',  op( B ) = B.
*
*              TRANSB = 'T' or 't',  op( B ) = B'.
*
*              TRANSB = 'C' or 'c',  op( B ) = B'.
*
*           Unchanged on exit.
*
*  M      - INTEGER.
*           On entry,  M  specifies  the number  of rows  of the  matrix
*           op( A )  and of the  matrix  C.  M  must  be at least  zero.
*           Unchanged on exit.
*
*  N      - INTEGER.
*           On entry,  N  specifies the number  of columns of the matrix
*           op( B ) and the number of columns of the matrix C. N must be
*           at least zero.
*           Unchanged on exit.
*
*  K      - INTEGER.
*           On entry,  K  specifies  the number of columns of the matrix
*           op( A ) and the number of rows of the matrix op( B ). K must
*           be at least  zero.
*           Unchanged on exit.
*
*  ALPHA  - DOUBLE PRECISION.
*           On entry, ALPHA specifies the scalar alpha.
*           Unchanged on exit.
*
*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, ka ), where ka is
*           k  when  TRANSA = 'N' or 'n',  and is  m  otherwise.
*           Before entry with  TRANSA = 'N' or 'n',  the leading  m by k
*           part of the array  A  must contain the matrix  A,  otherwise
*           the leading  k by m  part of the array  A  must contain  the
*           matrix A.
*           Unchanged on exit.
*
*  LDA    - INTEGER.
*           On entry, LDA specifies the first dimension of A as declared
*           in the calling (sub) program. When  TRANSA = 'N' or 'n' then
*           LDA must be at least  max( 1, m ), otherwise  LDA must be at
*           least  max( 1, k ).
*           Unchanged on exit.
*
*  B      - DOUBLE PRECISION array of DIMENSION ( LDB, kb ), where kb is
*           n  when  TRANSB = 'N' or 'n',  and is  k  otherwise.
*           Before entry with  TRANSB = 'N' or 'n',  the leading  k by n
*           part of the array  B  must contain the matrix  B,  otherwise
*           the leading  n by k  part of the array  B  must contain  the
*           matrix B.
*           Unchanged on exit.
*
*  LDB    - INTEGER.
*           On entry, LDB specifies the first dimension of B as declared
*           in the calling (sub) program. When  TRANSB = 'N' or 'n' then
*           LDB must be at least  max( 1, k ), otherwise  LDB must be at
*           least  max( 1, n ).
*           Unchanged on exit.
*
*  BETA   - DOUBLE PRECISION.
*           On entry,  BETA  specifies the scalar  beta.  When  BETA  is
*           supplied as zero then C need not be set on input.
*           Unchanged on exit.
*
*  C      - DOUBLE PRECISION array of DIMENSION ( LDC, n ).
*           Before entry, the leading  m by n  part of the array  C must
*           contain the matrix  C,  except when  beta  is zero, in which
*           case C need not be set on entry.
*           On exit, the array  C  is overwritten by the  m by n  matrix
*           ( alpha*op( A )*op( B ) + beta*C ).
*
*  LDC    - INTEGER.
*           On entry, LDC specifies the first dimension of C as declared
*           in  the  calling  (sub)  program.   LDC  must  be  at  least
*           max( 1, m ).
*           Unchanged on exit.
*
*/

  extern "C" void dgemm_(char * 	TRANSA,
                         char * 	TRANSB,
                         int * 	M,
                         int * 	N,
                         int * 	K,
                         double * ALPHA,
                         double * A,
                         int * 	LDA,
                         double * B,
                         int * 	LDB,
                         double * BETA,
                         double * C,
                         int * 	LDC
                         );

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
    ASSERT_NE(size(x),0);


    // now we build the M_Matrix result
    M_Matrix<T> z=zeros<T> (ncols(x),ncols(y));


    /***  as fortran uses the reverse order for matrices and we want to
              avoid a copying operation, we calculate
                  Transpose(Z)=Transpose(y)*Transpose(x)

                  Transpose(matrix)=just plain matrix in C++ format


              */
    char  	TRANSA='N';
    char  	TRANSB='T';
    int  	M=ncols(y);
    int  	N=ncols(x);
    int  	K=nrows(x);
    double  ALPHA=1.0;
    double*  A=const_cast<double*> (&y[0]);
    int  	LDA=M;
    double*  B=const_cast<double*> (&x[0]);
    int  	LDB=N;
    double BETA=0.0;
    double * C=&z[0];
    int  	LDC=M;



    try{
      dgemm_(&TRANSA,&TRANSB,&M,&N,&K,&ALPHA,A,&LDA,B,&LDB,&BETA,C,&LDC);
    }
    catch (...)
    {
      std::cerr<<" dgemm_error";
    }
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
    ASSERT_NE(size(x),0);
    ASSERT_EQ(ncols(x),ncols(y));
    // now we build the M_Matrix result
    M_Matrix<T> z=zeros<T> (nrows(x),nrows(y));
    char  	TRANSA='T';
    char  	TRANSB='N';
    int  	M=nrows(y);
    int  	N=nrows(x);
    int  	K=ncols(x);
    double  ALPHA=1.0;
    double*  A=const_cast<double*> (&y[0]);
    int  	LDA=K;
    double*  B=const_cast<double*> (&x[0]);
    int  	LDB=K;
    double BETA=0.0;
    double * C=&z[0];
    int  	LDC=M;

    try
    {
      dgemm_(&TRANSA,&TRANSB,&M,&N,&K,&ALPHA,A,&LDA,B,&LDB,&BETA,C,&LDC);
    }
    catch(...)
    {
      std::cerr<<" dgemm_ error";
    }

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
    ASSERT_NE(size(x),0);
    // now we build the M_Matrix result
    M_Matrix<T> z=zeros<T> (nrows(x),ncols(y));

    /***  as fortran uses the reverse order for matrices and we want to
          avoid a copying operation, we calculate
              Transpose(Z)=Transpose(y)*Transpose(x)

              Transpose(matrix)=just plain matrix in C++ format


          */
    char  	TRANSA='N';
    char  	TRANSB='N';
    int  	M=ncols(y);
    int  	N=nrows(x);
    int  	K=ncols(x);
    double  ALPHA=1.0;
    double*  A=const_cast<double*> (&y[0]);
    int  	LDA=M;
    double*  B=const_cast<double*> (&x[0]);
    int  	LDB=K;
    double BETA=0.0;
    double * C=&z[0];
    int  	LDC=M;


    try
    {
      dgemm_(&TRANSA,&TRANSB,&M,&N,&K,&ALPHA,A,&LDA,B,&LDB,&BETA,C,&LDC);
    }
    catch (...)
    {
      assert(false);
    }
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
