#include "Markov_LA/matrixCholesky.h"
#include "Markov_LA/matrixOperators.h"

#include <iostream>

namespace Markov_LA
{

  /**

 SUBROUTINE DPOTRF( UPLO, N, A, LDA, INFO )
*
*  -- LAPACK routine (version 3.3.1) --
*  -- LAPACK is a software package provided by Univ. of Tennessee,    --
*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
*  -- April 2011                                                      --
*
*     .. Scalar Arguments ..
      CHARACTER          UPLO
      INTEGER            INFO, LDA, N
*     ..
*     .. Array Arguments ..
      DOUBLE PRECISION   A( LDA, * )
*     ..
*
*  Purpose
*  =======
*
*  DPOTRF computes the Cholesky factorization of a real symmetric
*  positive definite matrix A.
*
*  The factorization has the form
*     A = U**T * U,  if UPLO = 'U', or
*     A = L  * L**T,  if UPLO = 'L',
*  where U is an upper triangular matrix and L is lower triangular.
*
*  This is the block version of the algorithm, calling Level 3 BLAS.
*
*  Arguments
*  =========
*
*  UPLO    (input) CHARACTER*1
*          = 'U':  Upper triangle of A is stored;
*          = 'L':  Lower triangle of A is stored.
*
*  N       (input) INTEGER
*          The order of the matrix A.  N >= 0.
*
*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
*          On entry, the symmetric matrix A.  If UPLO = 'U', the leading
*          N-by-N upper triangular part of A contains the upper
*          triangular part of the matrix A, and the strictly lower
*          triangular part of A is not referenced.  If UPLO = 'L', the
*          leading N-by-N lower triangular part of A contains the lower
*          triangular part of the matrix A, and the strictly upper
*          triangular part of A is not referenced.
*
*          On exit, if INFO = 0, the factor U or L from the Cholesky
*          factorization A = U**T*U or A = L*L**T.
*
*  LDA     (input) INTEGER
*          The leading dimension of the array A.  LDA >= max(1,N).
*
*  INFO    (output) INTEGER
*          = 0:  successful exit
*          < 0:  if INFO = -i, the i-th argument had an illegal value
*          > 0:  if INFO = i, the leading minor of order i is not
*                positive definite, and the factorization could not be
*                completed.
*
*  =====================================================================


  */
  namespace{

    extern "C" void dpotrf_(char * 	UPLO,
                            int * N,
                            double * A,
                            int * LDA,
                            int * INFO);

    M_Matrix<double> UT(const M_Matrix<double>& x)
    {
      M_Matrix<double> y(nrows(x),ncols(x));
      for (std::size_t i=0;i<nrows(x);i++)
        {
          for (std::size_t j=0;j<i; j++)
            y(j,i)=0;
          for (std::size_t j=i;j<ncols(x); j++)
            y(j,i)=x(i,j);
        }
      return y;
    }

    M_Matrix<double> LT(const M_Matrix<double>& x)
    {
      M_Matrix<double> y(nrows(x),ncols(x));
      for (std::size_t i=0;i<nrows(x);i++)
        {
          for (std::size_t j=0;j<i+1; j++)
            y(j,i)=x(i,j);
          for (std::size_t j=i+1;j<ncols(x); j++)
            y(j,i)=0;
        }
      return y;
    }



  }

  M_Matrix<double> chol(const M_Matrix<double>& x,const std::string& kind)
  {

    if ((nrows(x)!=ncols(x))||size(x)==0)
      return M_Matrix<double>();
    char UPLO='L';
    M_Matrix<double> res;
    if (kind!="lower")
      {
        UPLO='U';
        res=UT(x);
      }
    else
      {
        res=LT(x);
      }
    int N=nrows(x);
    int LDA=N;
    int INFO;
    double* A=new double[size(x)];
    for (std::size_t i=0; i<size(x); i++)
      A[i]=res[i];

    if (LDA==0)
      return M_Matrix<double>();
    try
    {
      dpotrf_(&UPLO,&N,A,&LDA,&INFO);
    }
    catch (...)
    {
      std::cerr<<" error";
    };
    for (std::size_t i=0; i<size(x); i++)
      res[i]=A[i];
    res=Transpose(res);
    delete [] A;
    return res;

  }
}
