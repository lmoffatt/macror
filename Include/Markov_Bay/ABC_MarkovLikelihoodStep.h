#ifndef ABC_MARKOVLIKELIHOODSTEP_H
#define ABC_MARKOVLIKELIHOODSTEP_H

#include "Markov_IO/ABC_Var.h"

#include "Markov_LA/Matrix.h"

#include "Markov_Mol/ABC_PatchModel.h"

namespace Markov_Bay
{

class ABC_Markov_Likelihood_step:public Markov_IO::Implements_Class_Reflection<ABC_Markov_Likelihood_step>
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

    virtual const Markov_Mol::ABC_PatchModel& patch()const=0;
    virtual  const Markov_Mol::ABC_Markov_Model& model()const=0;
    virtual  double N_channels()const=0;
    virtual const Markov_Mol::ABC_noise& noise()const=0;

    virtual ABC_Markov_Likelihood_step& start(double x)=0;
    virtual ABC_Markov_Likelihood_step& run(const Markov_IO::ABC_measure_step& Y)=0;

    virtual void apply_parameters(const Markov_IO::Parameters& beta)=0;
    virtual const Markov_IO::Parameters&  get_parameters()const=0;

    virtual std::ostream& put(std::ostream& s)const;


  ABC_Markov_Likelihood_step(
      const std::string& id,
      const std::string varName,
      const std::string & tip,
      const std::string& whatthis):
    //Implements_ValueId(id,varName,tip,whatthis),
    Implements_Class_Reflection<ABC_Markov_Likelihood_step>(id,varName,this,tip,whatthis)
  {
    push_backRefMethod("P_mean",
                       &ABC_Markov_Likelihood_step::P_mean,{},"MeanStateProbabilityVector",
                       "mean probability vector",
                       "Mean probability of being on each state"
                       );
    push_backRefMethod("P_cov",
                       &ABC_Markov_Likelihood_step::P_cov,{},"CovarianceStateProbabilityMatrix",
                       "covariance probability matrix",
                       "matrix of the covariance of being on each state"
                       );

    push_backValMethod("y",
                       &ABC_Markov_Likelihood_step::y, {},"current",
                       "measured or simulated current",
                       "mean current measured during the time interval");

    push_backValMethod("y_var",
                       &ABC_Markov_Likelihood_step::y_var, {},"current_variance",
                       "variance of the expected current",
                       "variance of the expected current measured during the time interval");

    push_backValMethod("y_std",
                       &ABC_Markov_Likelihood_step::y_std, {},"current",
                       "standard deviation of the expected current",
                       "standard deviation of the expected current measured during the time interval");
    push_backValMethod("y_mean",
                       &ABC_Markov_Likelihood_step::y_mean, {},"current",
                       "expected current",
                       "mean expected current measured during the time interval");
    push_backValMethod("plogL",
                       &ABC_Markov_Likelihood_step::plogL, {},"logLikelihood",
                       "partial log Likelihood",
                       "increase in the logarithm of the likelihood of the current measured "
                       "during the time interval");
    push_backValMethod("elogL",
                       &ABC_Markov_Likelihood_step::eplogL, {},"logLikelihood",
                       "expected partial log Likelihood",
                       "expected increase in the logarithm of the likelihood of the current measured "
                       "during the time interval");

    }





  ABC_Markov_Likelihood_step(const ABC_Markov_Likelihood_step& other):
    //Implements_ValueId(other),
    Implements_Class_Reflection<ABC_Markov_Likelihood_step>(other){}


 ABC_Markov_Likelihood_step()=default;

};


}
#endif // ABC_MARKOVLIKELIHOODSTEP_H
