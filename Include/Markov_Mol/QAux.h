#ifndef QAUX_H
#define QAUX_H

#include <cstddef>


#include "Markov_LA/Matrix.h"

#include "Borrowed/MersenneTwister.h"

#include "Markov_Mol/MarkovTransitionStep.h"

#include <random>
namespace Markov_Mol_New
{
//diag(Q) has to be zero
Markov_LA::M_Matrix<size_t> random_N_sample(const Markov_LA::M_Matrix<double>& p,
				 std::size_t Nchannels,
				 std::mt19937_64& sto);


Markov_LA::M_Matrix<size_t>& random_P_on_N(const Markov_Transition_step& Qdt,
				Markov_LA::M_Matrix<size_t>& N_run,
				std::mt19937_64& sto);

bool get_states_from_kij_Label(std::string kij,
			       std::size_t& i,
			       std::size_t& j);
}




#include <cstddef>


#include "Markov_LA/Matrix.h"

#include "Borrowed/MersenneTwister.h"

#include "Markov_Mol/MarkovTransitionStep.h"

namespace Markov_Mol
{
//diag(Q) has to be zero
Markov_LA::M_Matrix<size_t> random_N_sample(const Markov_LA::M_Matrix<double>& p,
				 std::size_t Nchannels,
				 Borrowed::MersenneTwister::MTRand& sto);


Markov_LA::M_Matrix<size_t>& random_P_on_N(const Markov_Transition_step& Qdt,
				Markov_LA::M_Matrix<size_t>& N_run,
				Borrowed::MersenneTwister::MTRand& sto);

bool get_states_from_kij_Label(std::string kij,
			       std::size_t& i,
			       std::size_t& j);
}




#endif // QAUX_H
