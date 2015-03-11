#ifndef MACROAPROXSTEP_H
#define MACROAPROXSTEP_H

#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"
#include "Markov_Bay/MacroscopicGaussianDistribution.h"
namespace Markov_Bay
{


class Macro_Aprox_step: public ABC_Markov_Likelihood_step
{
public:
    virtual Macro_Aprox_step* clone()const;
    virtual Macro_Aprox_step* create()const;

    virtual  std::string myVar()const;
    static  std::string ClassName();


    virtual const  Markov_LA::M_Matrix<double>& P_mean()const;
    virtual const Markov_LA::M_Matrix<double>& P_cov()const;

    virtual double y()const;

    virtual  double y_mean()const;

    virtual   double y_var()const;

    virtual   double y_std()const;

    virtual  double plogL()const;

    virtual  double eplogL()const;


    virtual  double N_channels()const;

    virtual const Markov_Mol::ABC_Markov_Model& model()const;

    virtual const Markov_Mol::ABC_PatchModel& patch()const;

    virtual const Markov_Mol::ABC_noise& noise()const;

    virtual void apply_parameters(const Markov_IO::Parameters& beta);

    virtual const Markov_IO::Parameters& get_parameters()const;

    virtual Macro_Aprox_step& start(double x);

    virtual Macro_Aprox_step& run(const Markov_IO::ABC_measure_step& Y);


    Macro_Aprox_step(const std::string& id,
                     const ABC_Markov_Likelihood_step& step,
                     std::size_t numSamples,
                     std::size_t numSteps,
                     std::size_t seed,
                     const std::string &tip="",
                     const std::string &whatthis="");

    Macro_Aprox_step(const Macro_Aprox_step& other);

    virtual double NumSamples()const;
    virtual double df()const;
    virtual std::size_t NumVaryingStates()const;

    virtual double Pr_P_mean()const;
    virtual double Pr_P_cov(std::size_t i,
                            std::size_t j)const;
    virtual double Pr_y_var()const;
    virtual double Pr_y_mean()const;
    virtual double Pr_pLogL()const;

    virtual double Chi2_P_mean()const;
    virtual double Chi2_P_cov(std::size_t i,
                            std::size_t j)const;
    virtual double Chi2_y_var()const;
    virtual double Chi2_y_mean()const;
    virtual double Chi2_pLogL()const;




    virtual const ABC_Markov_Likelihood_step& TestedStep()const;


    Macro_Aprox_step();

    ~Macro_Aprox_step();

protected:
    Markov_IO::Parameters& buildParameters();

private:
    ABC_Markov_Likelihood_step* step_;
    Markov_Mol::ABC_PatchModel* model_A;
    Markov_Mol::Markov_Transition_step Q_dt;

    MacroscopicGaussianDistribution D_;
    MacroscopicGaussianDistribution D_step_;


    Markov_LA::M_Matrix<double> P_mean_M;
    Markov_LA::M_Matrix<double> P_cov_M;

    Markov_LA::M_Matrix<double> P_mean_prior_M;
    Markov_LA::M_Matrix<double> P_cov_prior_M;

    double  y_d;
    double  y_mean_d;
    double  y_var_d;
    double  y_std_d;

    double  plogL_d;
    double  eplogL_d;

    double df_;
    std::size_t  NumSamples_;
    std::size_t NumSteps_;
    Borrowed::MersenneTwister::MTRand sto_;
};
}
#endif // MACROAPROXSTEP_H
