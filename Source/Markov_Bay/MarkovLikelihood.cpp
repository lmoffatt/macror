#include "Markov_Bay/MarkovLikelihood.h"

#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixRounding.h"  //isfinite
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_Bay/MacroDRStep.h"
#include "Markov_Bay/MacroRStep.h"
#include "Markov_Bay/MacroNRStep.h"
//#include "Markov_Bay/MacroAproxStep.h"



#include "Markov_LA/auxiliarMath.h"






#include "Markov_Bay/MarkovLikelihood.h"

#include "Markov_LA/matrixMath.h"
#include "Markov_LA/matrixRounding.h"  //isfinite
#include "Markov_LA/matrixMaxMin.h"
#include "Markov_LA/matrixRelational.h"
#include "Markov_LA/matrixProduct.h"
#include "Markov_LA/matrixAritmetic.h"
#include "Markov_Bay/MacroDRStep.h"
#include "Markov_Bay/MacroRStep.h"
#include "Markov_Bay/MacroNRStep.h"
//#include "Markov_Bay/MacroAproxStep.h"



#include "Markov_LA/auxiliarMath.h"

namespace Markov_Bay_New
{





  LikelihoodEvaluation* Markov_Likelihood::run(
      const Markov_Mol_New::ABC_PatchModel * P,

      const Markov_IO_New::ABC_Experiment* E_A,
      const std::string& Likelihood_Algorithm,
      bool Is_Averaging,
      bool Use_Zero_Guard)
  {
    double logL=0;
    double elogL=0;
    std::size_t ns=0;
    double s2logL=0;
    ABC_Markov_Likelihood_step* L_A;
    if (Likelihood_Algorithm=="MacroNR")
      {
        L_A= new Macro_NR_step(P,Is_Averaging);
      }
    else if (Likelihood_Algorithm=="MacroR")
      {
        L_A= new Macro_R_step(P,Is_Averaging,Use_Zero_Guard);
      }
    else if (Likelihood_Algorithm=="MacroDR")
      {
        L_A= new Macro_DR_step(P,Use_Zero_Guard);
      }


    for (std::size_t i_r=0; i_r<E_A->num_replicates(); i_r++)
      {
        E_A->replicate(i_r);
        L_A->start(E_A->trace(0)[0].sub_step(0).x());
        for (std::size_t i=0; i<E_A->num_traces(); i++)
          {
            E_A->trace(i);
            for (std::size_t j=0; j<E_A->num_measures(); j++)
              {
                L_A->run((*E_A)[j]);
                if (!((L_A->P_mean())>=0.0)||(!Markov_LA::isFinite(L_A->plogL())))
                  if (!Markov_LA::isFinite(L_A->plogL()))
                    {
//                      std::cerr<<"\n (!isfinite(L_A->plogL()))\n";
//                      std::coerr<<" \nreplicate "<<i_r<<" trace "<<i<<" j "<<j<<" t "<<E_A->t();
//                      std::cout<<" dt "<<E_A->dt()<<" x "<<E_A->x()<<" y "<<E_A->y()<<"\n";
//                      std::cout<<*L_A;
//                      std::cout<<this->patch();
//                      return infinity();
//                      //    press_any_key_to_continue();
                    };
                logL+=L_A->plogL();
                elogL+=L_A->eplogL();
                s2logL+=std::pow((L_A->plogL()-L_A->eplogL()),2);
                ns++;

              };
            L_A->run(E_A->trace_interval());
          };


      }

    return new LikelihoodEvaluation(logL,elogL,ns,s2logL);

  }


}
