#ifndef MACRORSTEP_H
#define MACRORSTEP_H

#include "Markov_LA/Matrix.h"

#include"Markov_Bay/ABC_MarkovLikelihoodStep.h"
namespace Markov_Bay
{

class Macro_R_step: public ABC_Markov_Likelihood_step
{
public:
     Macro_R_step* clone()const;

     Macro_R_step* create()const;

     virtual  std::string myClass()const;
     static  std::string ClassName();

     const  Markov_LA::M_Matrix<double>& P_mean()const;

     const Markov_LA::M_Matrix<double>& P_cov()const;

     double y_mean()const;

     double y()const;

     double y_var() const;

     double y_std()const;

     double plogL()const;

     double eplogL()const;

     double N_channels()const;

     const Markov_Mol::ABC_PatchModel& patch()const;

     const Markov_Mol::ABC_Markov_Model& model()const;

     const Markov_Mol::ABC_noise& noise()const;

     void apply_parameters(const Markov_IO::Parameters& beta);

     const Markov_IO::Parameters& get_parameters()const;

     Macro_R_step& start(double x);

     Macro_R_step& run(const Markov_IO::ABC_measure_step& Y);


     Macro_R_step(Markov_IO::ABC_Data* e,
                  const std::string &id,const Markov_Mol::ABC_PatchModel& P,
		  bool is_averaging,
		 bool p_zero_guard,
		  const std::string &tip="",
		  const std::string &whatthis="");




    Macro_R_step(const Macro_R_step& other);

    Macro_R_step();
    ~Macro_R_step();

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
    bool isaveraging_b;
    bool p_zero_guard_b;
};
}

#endif // MACRORSTEP_H
