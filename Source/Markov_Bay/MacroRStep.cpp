#include "Markov_Bay/MacroRStep.h"

#include "Markov_Mol/QMarkovModel.h"

#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixOperators.h"

#include "Markov_LA/auxiliarMath.h"

namespace Markov_Bay
{


  using Markov_LA::isNaN;
  using Markov_LA::NaN;

  Macro_R_step* Macro_R_step::clone()const
  {
    return new Macro_R_step(*this);
  }

  Macro_R_step* Macro_R_step::create()const
  {
    return new Macro_R_step();
  }

  std::string Macro_R_step::myVar()const
  {
    return ClassName();
  }
  std::string Macro_R_step::ClassName()
  {
    return "Macro_R_step";
  }




  const  Markov_LA::M_Matrix<double>& Macro_R_step::P_mean()const
  {
    return P_mean_M;
  };
  const Markov_LA::M_Matrix<double>& Macro_R_step::P_cov()const
  {
    return P_cov_M;
  };
  double Macro_R_step::y_mean()const
  {
    return y_mean_d;
  };
  double Macro_R_step::y()const
  {
    return y_d;
  };
  double Macro_R_step::y_var() const
  {
    return y_var_d;
  };
  double Macro_R_step::y_std()const
  {
    return y_std_d;
  };
  double Macro_R_step::plogL()const
  {
    return plogL_d;
  };
  double Macro_R_step::eplogL()const
  {
    return eplogL_d;
  };
  double Macro_R_step::N_channels()const
  {
    return model_A->AverageNumberOfChannels();
  }
  const Markov_Mol::ABC_PatchModel& Macro_R_step::patch()const
  {
    return *model_A;
  }



  const Markov_Mol::ABC_Markov_Model& Macro_R_step::model()const
  {
    return model_A->Model();
  }
  const Markov_Mol::ABC_noise& Macro_R_step::noise()const
  {
    return model_A->Noise();
  }
  void Macro_R_step::apply_parameters(const Markov_IO::Parameters& beta)
  {
    model_A->apply_parameters(beta);

  }

  const Markov_IO::Parameters& Macro_R_step::get_parameters()const
  {
    return model_A->get_parameters();
  }



  Macro_R_step::Macro_R_step(const std::string& id,
                             const Markov_Mol::ABC_PatchModel& P,
                             bool is_averaging,
                             bool p_zero_guard,
                             const std::string &tip,
                             const std::string &whatthis):
    ABC_Markov_Likelihood_step(id,ClassName(),tip,whatthis),
    model_A(P.clone()),
    Q_dt(),
    P_mean_M(Markov_LA::M_Matrix<double>(1,P.Model().k())),
    P_cov_M(Markov_LA::M_Matrix<double>(P.Model().k(),P.Model().k())),
    y_d(Markov_LA::NaN()),
    y_mean_d(Markov_LA::NaN()),
    y_var_d(Markov_LA::NaN()),
    y_std_d(Markov_LA::NaN()),

    plogL_d(Markov_LA::NaN()),
    eplogL_d(Markov_LA::NaN()),
    chi2_d(Markov_LA::NaN()),

    isaveraging_b(is_averaging),
    p_zero_guard_b(p_zero_guard)
  {}

  Macro_R_step::Macro_R_step(const Macro_R_step& other):
    Implements_ValueId(other),
    ABC_Markov_Likelihood_step(other),
    model_A(other.model_A->clone()),
    Q_dt(other.Q_dt),
    P_mean_M(other.P_mean_M),
    P_cov_M(other.P_cov_M),
    y_d(other.y_d),
    y_mean_d(other.y_mean_d),
    y_var_d(other.y_var_d),
    y_std_d(other.y_std_d),

    plogL_d(other.plogL_d),
    eplogL_d(other.eplogL_d),
    chi2_d(other.chi2_d),
    isaveraging_b(other.isaveraging_b),
    p_zero_guard_b(other.p_zero_guard_b)

  {}

  Macro_R_step::Macro_R_step() {}
  Macro_R_step::~Macro_R_step()
  {
    delete model_A;
  }

  Macro_R_step& Macro_R_step::start(double x)
  {
    P_mean_M=model().Peq(x);
    P_cov_M=diag(P_mean_M)-TranspMult(P_mean_M,P_mean_M);
    return *this;
  }

  Macro_R_step& Macro_R_step::run(const Markov_IO::ABC_measure_step& Y)
  {
    Q_dt=this->model().Q_step(Y,isaveraging_b,false);
    Markov_LA::M_Matrix<double> gS(TranspMult(Q_dt.gmean_i,P_cov_M));// product of S and g, used several places
    y_d=Y.y();
    if (isNaN(Y.y()))
      {
        plogL_d=NaN();
        chi2_d=NaN();
      }
    else
      {

        if (isaveraging_b)
          {
            y_mean_d=(P_mean_M*Q_dt.gmean_i)[0]*model_A->AverageNumberOfChannels();
            y_var_d=model_A->Noise().var(Y.dt())+
                ((gS*Q_dt.gmean_i)[0]+(P_mean_M*Q_dt.gvar_i)[0])*
                model_A->AverageNumberOfChannels();
          }
        else
          {
            y_mean_d=(P_mean_M*Q_dt.gmean_i)[0]*model_A->AverageNumberOfChannels();
            y_var_d=model_A->Noise().var(Y.dt())+
                ((gS*Q_dt.gmean_i)[0])*
                model_A->AverageNumberOfChannels();
          };

        y_std_d=sqrt(y_var_d);

        double dy=Y.y()-y_mean_d;

        chi2_d=dy*dy/y_var_d;

        plogL_d=-0.5*log(2*PI*y_var_d)-0.5*chi2_d;

        eplogL_d=-0.5*(1+log(2*PI*y_var_d));
        P_mean_M+=gS*(dy/y_var_d);

        if (p_zero_guard_b &&(!(P_mean_M>=0.0)))
          {
            double summ=0.0;
            for (std::size_t i=0;i<size(P_mean_M);i++)
              {
                if (P_mean_M[i]<0.0)
                  P_mean_M[i]=0.0;
                else if (P_mean_M[i]>1)
                  P_mean_M[i]=1;
                summ+=P_mean_M[i];
              }
            P_mean_M/=summ;

          }

        P_cov_M-=TranspMult(gS,gS)*(model_A->AverageNumberOfChannels()/y_var_d);
        if (p_zero_guard_b&&(!(diag(P_cov_M)>=0.0)||!(diag(P_cov_M)<=1.0)))
          {
            for (std::size_t i=0;i<size(P_cov_M);i++)
              {
                if (P_cov_M(i,i)<0.0)
                  P_cov_M(i,i)=abs(P_cov_M(i,i));
                else if (P_cov_M(i,i)>1.0)
                  P_cov_M(i,i)=1.0;
              }
          }

      }

    P_cov_M=TranspMult(Q_dt.P,(P_cov_M-diag(P_mean_M))*Q_dt.P);

    P_mean_M = P_mean_M*Q_dt.P;

    P_cov_M+=diag(P_mean_M);
    return *this;
  }


}
