/*!
 * @file matrixRand.cpp @brief Implementation of Random Matrices
 */
#include "Markov_LA/matrixRand.h"

namespace Markov_LA
{

    /**
    *  Custom size Random Matrix using provided Random engine
    @param TR Reference to a previously initialized Random generator
    @post 0<=Rand(n,m)<=1
    @post the internal state of the random generator changes
    */
    template<typename T>
    M_Matrix<T>  Rand(std::size_t nrows_,
		      std::size_t ncols_,
		      std::mt19937_64& sto)
    {
        auto rand=std::uniform_real_distribution<>(0,1);
      M_Matrix<T> A(nrows_,ncols_);
	for (std::size_t i=0; i<size(A); i++)
	{
	    A[i]=rand(sto);
	}
	return A;
    }







    template class multinomial_distribution<My_vec,std::size_t>;


    template class multinomial_distribution<M_Matrix,std::size_t>;


    template M_Matrix<double>  Rand(std::size_t nrows_,
				    std::size_t ncols_,
				    std::mt19937_64& TR);


} // end of namespace Markov_LA
