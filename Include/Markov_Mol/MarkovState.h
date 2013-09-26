#ifndef MARKOVSTATE_H
#define MARKOVSTATE_H


#include "Markov_IO/ABC_Put.h"

#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixIO.h"

namespace Markov_Mol
{

using Markov_LA::M_Matrix;

class Markov_state:public Markov_IO::ABC_Put
{
public:
    virtual Markov_state* clone() const;

    virtual Markov_state* create() const;

    Markov_state(const Markov_state& other);

    Markov_state(M_Matrix<std::size_t> N_,double ymean_);
    explicit Markov_state(std::size_t n);

    Markov_state();

    Markov_state& operator=(const Markov_state& other);
    virtual ~Markov_state();

    M_Matrix<std::size_t>& N();
    const M_Matrix<std::size_t>& N()const;

    double& ymean();
    const double& ymean()const;

    M_Matrix<double>& P();
    const M_Matrix<double>& P()const;


    virtual std::ostream& put(std::ostream& s) const;

    friend void swap(Markov_state& one, Markov_state& other);

private:
    M_Matrix<std::size_t> N_;
    double ymean_;
    M_Matrix<double> P_;

};



};

#endif // MARKOVSTATE_H
