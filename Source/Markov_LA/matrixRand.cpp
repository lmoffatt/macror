/*!
 * @file matrixRand.cpp @brief Implementation of Random Matrices
 */
#include "Markov_LA/matrixRand.h"

namespace Markov_LA
{
    using Borrowed::MersenneTwister::seedinit;

    /**
    *  Custom size Random Matrix using provided Random engine
    @param TR Reference to a previously initialized Random generator
    @post 0<=Rand(n,m)<=1
    @post the internal state of the random generator changes
    */
    template<typename T>
    M_Matrix<T>  Rand(std::size_t nrows_,
		      std::size_t ncols_,
		      Borrowed::MersenneTwister::MTRand& TR)
    {
	M_Matrix<T> A(nrows_,ncols_);
	for (std::size_t i=0; i<size(A); i++)
	{
	    A[i]=TR.rand();
	}
	return A;
    }

    /**
    *  Custom size Random Matrix using internal Random engine initialized by a
    seed number
    @param seed 0, it uses seedinit() to get the seed
    @post 0<=Rand(n,m)<=1

    */
    template<typename T>
    M_Matrix<T>  Rand(std::size_t nrows_,std::size_t ncols_, long seed)
    {
	Borrowed::MersenneTwister::MTRand TR(seedinit(seed));
	M_Matrix<T> r(nrows_,ncols_);
	for (std::size_t i=0; i<size(r); i++)
	    r[i]=TR.rand();
	return r;
    }






    /**
      Random Matrix with the same size as the input matrix
     */
    template<typename T>
    M_Matrix<T>  Rand(M_Matrix<T> x, long seed)
    {
	return Rand<T>(nrows(x),ncols(x),seed);
    }




    template M_Matrix<double>  Rand(std::size_t nrows_,
				    std::size_t ncols_,
				    Borrowed::MersenneTwister::MTRand& TR);

    template
	    M_Matrix<double>  Rand(std::size_t nrows_,std::size_t ncols_, long seed);

    template
	    M_Matrix<double>  Rand(M_Matrix<double> x, long seed);


} // end of namespace Markov_LA
