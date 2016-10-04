#ifndef MACRONRSTEP_H
#define MACRONRSTEP_H

#include "Markov_LA/Matrix.h"

#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/ABC_Noise.h"

#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"

namespace Markov_Bay_New
{

  class Macro_NR_step: public ABC_Markov_Likelihood_step
  {
  public:
    virtual Macro_NR_step* clone()const;

    virtual Macro_NR_step* create()const;

    virtual  std::string myVar()const;
    static  std::string ClassName();

    virtual const  Markov_LA::M_Matrix<double>& P_mean()const;

    virtual  const Markov_LA::M_Matrix<double>& P_cov()const;

    virtual   double y_mean()const;

    virtual   double y()const;

    virtual   double y_var()const;

    virtual   double y_std()const;

    virtual  double plogL()const;

    virtual  double eplogL()const;

    virtual  double N_channels()const;

    virtual const Markov_Mol_New::ABC_PatchModel& patch()const;

    virtual const Markov_Mol_New::ABC_Markov_Model& model()const;

    virtual const Markov_Mol_New::ABC_noise& noise()const;


    virtual Macro_NR_step& start(double x);

    virtual Macro_NR_step& run(const Markov_IO_New::ABC_measure_step& Y);

    Macro_NR_step(const Markov_Mol_New::ABC_PatchModel* M,
                  bool is_averaging);

    Macro_NR_step(const Macro_NR_step& other);
    Macro_NR_step();

    ~Macro_NR_step();

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

  };
}
#endif // MACRONRSTEP_H
