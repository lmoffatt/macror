#ifndef MARKOVTRANSITIONRATE_H
#define MARKOVTRANSITIONRATE_H


#include "Markov_IO/ABC_Put.h"

#include "Markov_LA/Matrix.h"


namespace Markov_Mol_New
{
using Markov_LA::M_Matrix;

class Markov_Transition_rate: public Markov_IO::ABC_Put
{
public:

    M_Matrix<double> Qrun;// transition rate matrix at time zero
    M_Matrix<double> V;// eigenvector of Qrun
    M_Matrix<double> W;// eigenvector of Qrun
    M_Matrix<double> landa; // eigenvalues

    M_Matrix<double> Wg;
    M_Matrix<double> WgV;

    ~Markov_Transition_rate();
    ///virtual copy constructors
    virtual Markov_Transition_rate* clone() const;

    virtual Markov_Transition_rate* create() const;

    Markov_Transition_rate(const Markov_Transition_rate& other);

    Markov_Transition_rate(const M_Matrix<double>& Qrun_,
                           const M_Matrix<double>& V_,
                           const M_Matrix<double>& W_,
                           const M_Matrix<double>& landa_);

    Markov_Transition_rate(const M_Matrix<double>& Qrun_,
                           const M_Matrix<double>& V_,
                           const M_Matrix<double>& W_,
                           const M_Matrix<double>& landa_,
                           const M_Matrix<double>& Wg_,
                           const M_Matrix<double>& WgV_);

    Markov_Transition_rate& operator=(const Markov_Transition_rate& other);

    friend void swap(Markov_Transition_rate& one, Markov_Transition_rate& other);

    explicit Markov_Transition_rate(std::size_t n, bool is_averaging);

    Markov_Transition_rate();

    std::ostream& put(std::ostream& s) const;
};



std::ostream& operator<< (std::ostream& s,const Markov_Transition_rate& x);
};



#include "Markov_IO/ABC_Put.h"

#include "Markov_LA/Matrix.h"


namespace Markov_Mol
{
using Markov_LA::M_Matrix;

class Markov_Transition_rate: public Markov_IO::ABC_Put
{
public:

    M_Matrix<double> Qrun;// transition rate matrix at time zero
    M_Matrix<double> V;// eigenvector of Qrun
    M_Matrix<double> W;// eigenvector of Qrun
    M_Matrix<double> landa; // eigenvalues

    M_Matrix<double> Wg;
    M_Matrix<double> WgV;

    ~Markov_Transition_rate();
    ///virtual copy constructors
    virtual Markov_Transition_rate* clone() const;

    virtual Markov_Transition_rate* create() const;

    Markov_Transition_rate(const Markov_Transition_rate& other);

    Markov_Transition_rate(const M_Matrix<double>& Qrun_,
			   const M_Matrix<double>& V_,
			   const M_Matrix<double>& W_,
			   const M_Matrix<double>& landa_);

    Markov_Transition_rate(const M_Matrix<double>& Qrun_,
			   const M_Matrix<double>& V_,
			   const M_Matrix<double>& W_,
			   const M_Matrix<double>& landa_,
			   const M_Matrix<double>& Wg_,
			   const M_Matrix<double>& WgV_);

    Markov_Transition_rate& operator=(const Markov_Transition_rate& other);

    friend void swap(Markov_Transition_rate& one, Markov_Transition_rate& other);

    explicit Markov_Transition_rate(std::size_t n, bool is_averaging);

    Markov_Transition_rate();

    std::ostream& put(std::ostream& s) const;
};



std::ostream& operator<< (std::ostream& s,const Markov_Transition_rate& x);
};
#endif // MARKOVTRANSITIONRATE_H
