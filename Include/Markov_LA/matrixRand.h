/*!
 * @file matrixRand.h @brief Custom size Matrices of Random numbers
 */
#ifndef MATRIXRAND_H
#define MATRIXRAND_H

#include "Markov_LA/Matrix.h"
#include "Borrowed/MersenneTwister.h"

namespace Markov_LA
{

    template<typename T>
    M_Matrix<T>  Rand(std::size_t nrows_,
		      std::size_t ncols_,
		      Borrowed::MersenneTwister::MTRand& TR);

    template<typename T>
    M_Matrix<T>  Rand(std::size_t nrows_,std::size_t ncols_, long seed=0);

    template<typename T>
    M_Matrix<T>  Rand(M_Matrix<T> x, long seed=0);

}

#endif // MATRIXRAND_H
