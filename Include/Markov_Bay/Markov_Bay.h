#ifndef MARKOV_BAY_H_INCLUDED
#define MARKOV_BAY_H_INCLUDED

#include <iostream>
#include <iomanip>
#include "Markov_LA/matrixInverse.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_LA/matrixExp.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixInit.h"
#include "Markov_LA/matrixRounding.h"

using Markov_LA::M_Matrix;
using Markov_LA::eye;
/*
class ABC_Markov_Analisis_step
{
public:

    virtual  ABC_Markov_Model& model()const=0;
    virtual  double N_channels()const=0;
    virtual ABC_noise& noise()const=0;

    virtual ABC_Markov_Analisis_step& run(const ABC_measure_step& Y)=0;
};



class ABC_Markov_Analisis
{
public:
//    virtual ABC_Experiment operator()(ABC_Experiment& x)const=0;

    virtual const ABC_Markov_Model& model()const=0;
    virtual double N_channels()const=0;
    virtual const ABC_noise& noise()const=0;

    virtual const ABC_Markov_Analisis_step& begin()const=0;
};

*/

/*
class ABC_Markov_Simulation_step:public ABC_Markov_Analisis_step
{
public:

    virtual  const M_Matrix<std::size_t>& N()const=0;

    virtual double ymean()const=0;

    virtual  const M_Matrix<double>& N_mean()const=0;

    virtual double ystd()const=0;

    virtual  const M_Matrix<double>& N_std()const=0;

    virtual  ABC_Markov_Model& model()const=0;
    virtual  double N_channels()const=0;
    virtual ABC_noise& noise()const=0;

    virtual ABC_Markov_Simulation_step& run(const ABC_measure_step& Y)=0;
};


class ABC_Markov_Likelihood //: public ABC_Markov_Analisis
{
    virtual double operator()(const Parameters& beta)const=0;
    virtual const M_Matrix<double>& plogL()const=0;

    virtual const ABC_Experiment& experiment()const=0;
    virtual const ABC_Markov_Model& model()const=0;
    virtual double N_channels()const=0;
    virtual const ABC_noise& noise()const=0;
    virtual const ABC_Markov_Likelihood_step& Likelihood_begin()const=0;
};

*/




#endif // MARKOV_BAY_H_INCLUDED
