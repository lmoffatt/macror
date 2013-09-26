#ifndef MARKOVMOL_H_INCLUDED
#define MARKOVMOL_H_INCLUDED

#include "Markov_LA/auxiliarMath.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixInit.h"

#include "Borrowed/MersenneTwister.h"
#include "Markov_IO/Markov_ABC.h"
#include "Markov_IO/Markov_IO.h"


#include <map>
#include <iterator>

/**
 \file
The Module Markov_Mol is capable to create, read and run \ref kinetic_model_page "Kinetic Models".
 It accepts as inputs any arbitrary \ref kinetic_model_page "Kinetic Model" with its set of
 \ref kinetic_parameters_page "Kinetic Parameters" and a \ref pattern_of_stimulation_page "pattern of stimulation" an.

    As output it can provide a \ref simulated_electrophysiological_recording_page "Simulated Electrophysiological Recording"
    of an ion channel preparation that behaves accordingly with the proposed kinetic model, as well as the \ref
    probability_transition_matrix_page "matrix of probabilities of state-state transitions"for the particular

*/

using Markov_LA::zeros;
using Markov_LA::M_Matrix;
















/**
//////////////////////////////////////////////////////////////////////////

                   CLASS DECLARATIONS

//////////////////////////////////////////////////////////////////////////
**/







/** ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo

                                      ALL IMPLEMENTATIONS below this LINE
______________________________________________________________________________________________________________________________
_____________________________________________________________________________________________________________________________
______________________________________________________________________________________________________________________________
_____________________________________________________________________________________________________________________________
______________________________________________________________________________________________________________________________
_____________________________________________________________________________________________________________________________
/

/000000000000000000000000000000000000000000000000

 TEMPLATE IMPLEMENTATIONS
 888888888888888888888888888888888888888888888
 */


/***
///////////////////////////////////////////////////////////////////

                      INLINE IMPLEMENTATIONS

///////////////////////////////////////////////////////////////////

*/

/**
_____________________________________________________

                ABC_Markov Model
___________________________________________________________

**/

inline
std::size_t Q_Markov_Model::k()const
{
    return k_u;
}

inline
const M_Matrix<double>& Q_Markov_Model::Q() const
{
    return Q_M;
}

inline
const M_Matrix<double>& Q_Markov_Model::Q0() const
{
    return Q0_M;
}

inline
const M_Matrix<double>& Q_Markov_Model::Q1() const
{
    return Q1_M;
}

inline
const M_Matrix<size_t>& Q_Markov_Model::n_bound_agonists() const
{
    return a_M;
}

inline
const M_Matrix<double>& Q_Markov_Model::g() const
{

    return g_M;//*gamma_d;
}

inline
double Q_Markov_Model::gamma() const
{
    return gamma_d;
}


inline
std::string Q_Markov_Model::kij_Label(std::size_t i,std::size_t j)
{
    if ((i<k_u)&&(j<k_u))
    {
	std::string kij="k_"+ToString(i)+"_to_"+ToString(j);
        return kij;
    }
    else
    {
        std::string msg="i or j too big";
        return msg;
    };
}



#endif // MARKOVMOL_H_INCLUDED
