#ifndef MARKOVTRANSITIONSTEP_H
#define MARKOVTRANSITIONSTEP_H

#include "Markov_IO/ABC_Put.h"

#include "Markov_LA/Matrix.h"

namespace Markov_Mol_New
{


class Markov_Transition_step
{
public:
    virtual ~Markov_Transition_step();

    Markov_LA::M_Matrix<double> P;// transition matrix

    /// mean conductance for each starting state i
    Markov_LA::M_Matrix<double> gmean_i; // conductance matrix
    ///total conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gtotal_ij; // conductance matrix
    ///mean conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gmean_ij; // conductance matrix

    /// squared mean conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gtotal_sqr_ij; // conductance matrix

    /// squared mean conductance for each starting state i
    Markov_LA::M_Matrix<double> gsqr_i; // conductance matrix

    /// variance of the mean conductance for each starting state i
    Markov_LA::M_Matrix<double> gvar_i; //variance of the conductance matrix
    /// variance of the mean conductance for each starting state i contributed by the ones ending at state j
    Markov_LA::M_Matrix<double> gtotal_var_ij; //variance of the conductance matrix

    /// variance of the mean conductance for each starting state i summed all over  j
    Markov_LA::M_Matrix<double> gtotal_var_i; //variance of the conductance matrix

    /// variance of the mean conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gvar_ij; //variance of the conductance matrix

    Markov_Transition_step(std::size_t n,
                           bool is_averaging_=false,
                           bool varying_=false,
                           bool two_anchor_=false);

    Markov_Transition_step()=default;
    ///copy constructor
    Markov_Transition_step(const Markov_Transition_step& other)=default;

    Markov_Transition_step( Markov_Transition_step&& other)=default;
    ///asignment
    Markov_Transition_step& operator=(const Markov_Transition_step& other)=default;
    Markov_Transition_step& operator=( Markov_Transition_step&& other)=default;

};

}







#include "Markov_IO/ABC_Put.h"

#include "Markov_LA/Matrix.h"

namespace Markov_Mol
{


class Markov_Transition_step: public Markov_IO::ABC_Put
{
public:
    virtual Markov_Transition_step* clone() const;

    virtual Markov_Transition_step* create() const;

    virtual ~Markov_Transition_step();

    Markov_LA::M_Matrix<double> P;// transition matrix
    /// mean conductance for each starting state i
    Markov_LA::M_Matrix<double> gmean_i; // conductance matrix
    ///total conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gtotal_ij; // conductance matrix
    ///mean conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gmean_ij; // conductance matrix

    /// squared mean conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gtotal_sqr_ij; // conductance matrix

    /// squared mean conductance for each starting state i
    Markov_LA::M_Matrix<double> gsqr_i; // conductance matrix

    /// variance of the mean conductance for each starting state i
    Markov_LA::M_Matrix<double> gvar_i; //variance of the conductance matrix
    /// variance of the mean conductance for each starting state i contributed by the ones ending at state j
    Markov_LA::M_Matrix<double> gtotal_var_ij; //variance of the conductance matrix

    /// variance of the mean conductance for each starting state i summed all over  j
    Markov_LA::M_Matrix<double> gtotal_var_i; //variance of the conductance matrix

    /// variance of the mean conductance for each starting state i and ending state j
    Markov_LA::M_Matrix<double> gvar_ij; //variance of the conductance matrix

    Markov_Transition_step(std::size_t n,
			   bool is_averaging_=false,
			   bool varying_=false,
			   bool two_anchor_=false);

    Markov_Transition_step()=default;
    ///copy constructor
    Markov_Transition_step(const Markov_Transition_step& other)=default;

    Markov_Transition_step( Markov_Transition_step&& other)=default;
    ///asignment
    Markov_Transition_step& operator=(const Markov_Transition_step& other)=default;
    Markov_Transition_step& operator=( Markov_Transition_step&& other)=default;

    virtual std::ostream& put(std::ostream& s) const;
};

}
#endif // MARKOVTRANSITIONSTEP_H
