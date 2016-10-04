#ifndef MACRORSTEP_H
#define MACRORSTEP_H

#include "Markov_LA/Matrix.h"

#include"Markov_Bay/ABC_MarkovLikelihoodStep.h"
namespace Markov_Bay_New
{

class Macro_R_step: public ABC_Markov_Likelihood_step
{
public:
     Macro_R_step* clone()const;

     Macro_R_step* create()const;

     virtual  std::string myVar()const;
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

     const Markov_Mol_New::ABC_PatchModel& patch()const;

     const Markov_Mol_New::ABC_Markov_Model& model()const;

     const Markov_Mol_New::ABC_noise& noise()const;


     Macro_R_step& start(double x);



     Macro_R_step(const Markov_Mol_New::ABC_PatchModel* P,
                  bool is_averaging,
                 bool p_zero_guard);




    Macro_R_step(const Macro_R_step& other);

    Macro_R_step();
    ~Macro_R_step();

    Macro_R_step &run(const Markov_IO_New::ABC_measure_step &Y) override;
private:
    const Markov_Mol_New::ABC_PatchModel* model_A;

    Markov_Mol_New::Markov_Transition_step Q_dt;

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
