#ifndef MARKOVSTATEEXT_H
#define MARKOVSTATEEXT_H


#include "Markov_LA/Matrix.h"

namespace Markov_Mol_New
{

using Markov_LA::M_Matrix;

struct Markov_state_ext
{
    M_Matrix<std::size_t> N;
    M_Matrix<double> N_mean;
    M_Matrix<double> N_std;
    double ymean;
    double ystd;
    M_Matrix<double> P;
    M_Matrix<double> N_sqr;
    double ysqr;

    virtual Markov_state_ext* clone() const;

    virtual Markov_state_ext* create() const;

    Markov_state_ext(const Markov_state_ext& other);

    explicit Markov_state_ext(std::size_t n);

    Markov_state_ext();

    virtual ~Markov_state_ext();


    ///asignment
    Markov_state_ext& operator=(const Markov_state_ext& other);

 };
};


#endif // MARKOVSTATEEXT_H
