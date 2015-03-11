#ifndef MACRODRSTEP_H
#define MACRODRSTEP_H

#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"
namespace Markov_Bay
{


class Macro_DR_step: public ABC_Markov_Likelihood_step
{
public:
    virtual Macro_DR_step* clone()const override;
    virtual Macro_DR_step* create()const override;

    virtual const  Markov_LA::M_Matrix<double>& P_mean()const override;
    virtual  const Markov_LA::M_Matrix<double>& P_cov()const override;

    virtual  std::string myVar()const override;
    static  std::string ClassName();


    virtual   double y()const override;

    virtual   double y_mean()const override;

    virtual   double y_var()const override;

    virtual   double y_std()const override;

    virtual  double plogL()const override;

    virtual  double eplogL()const override;


    virtual  double N_channels()const override;

    virtual const Markov_Mol::ABC_Markov_Model& model()const override;

    virtual const Markov_Mol::ABC_PatchModel& patch()const override;

    virtual const Markov_Mol::ABC_noise& noise()const override;

    virtual void apply_parameters(const Markov_IO::Parameters& beta) override;

    virtual const Markov_IO::Parameters& get_parameters()const override;

    virtual Macro_DR_step& start(double x) override;

    virtual Macro_DR_step& run(const Markov_IO::ABC_measure_step& Y) override;


    Macro_DR_step(const Markov_Mol::ABC_PatchModel& P,
                  bool p_zero_guard);

    Macro_DR_step(const Macro_DR_step& other);


      Macro_DR_step();

    ~Macro_DR_step();

protected:
    Markov_IO::Parameters& buildParameters() ;

private:
    Markov_Mol::ABC_PatchModel* model_A;
    Markov_Mol::Markov_Transition_step Q_dt;

    Markov_LA::M_Matrix<double> P_mean_M;
    Markov_LA::M_Matrix<double> P_cov_M;

    double  y_d;
    double  y_mean_d;
    double  y_var_d;
    double  y_std_d;

    double  plogL_d;
    double  eplogL_d;
    double  chi2_d;
    bool p_zero_guard_b;
};
}
#endif // MACRODRSTEP_H
