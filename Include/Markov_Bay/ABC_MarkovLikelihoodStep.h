#ifndef ABC_MARKOVLIKELIHOODSTEP_H
#define ABC_MARKOVLIKELIHOODSTEP_H

#include "Markov_LA/Matrix.h"

#include "Markov_Mol/ABC_PatchModel.h"

namespace Markov_Bay_New
{

class ABC_Markov_Likelihood_step
{
public:
    virtual ABC_Markov_Likelihood_step* clone()const=0;
    virtual ABC_Markov_Likelihood_step* create()const=0;

    virtual  std::string myVar()const=0;
    virtual  const Markov_LA::M_Matrix<double>& P_mean()const=0;
    virtual  const Markov_LA::M_Matrix<double>& P_cov()const=0;

    virtual  double y()const=0;
    virtual  double y_mean()const=0;
    virtual  double y_var()const=0;
    virtual  double y_std()const=0;

    virtual  double plogL()const=0;
    virtual  double eplogL()const=0;

    virtual const Markov_Mol_New::ABC_PatchModel& patch()const=0;
    virtual  const Markov_Mol_New::ABC_Markov_Model& model()const=0;
    virtual  double N_channels()const=0;
    virtual const Markov_Mol_New::ABC_noise& noise()const=0;

    virtual ABC_Markov_Likelihood_step& start(double x)=0;
    virtual ABC_Markov_Likelihood_step& run(const Markov_IO_New::ABC_measure_step& Y)=0;


};


}







#endif // ABC_MARKOVLIKELIHOODSTEP_H
