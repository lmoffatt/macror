#ifndef MARKOVLIKELIHOOD_H
#define MARKOVLIKELIHOOD_H

#include "Markov_LA/Matrix.h"

#include "Markov_IO/ABC_Experiment.h"

#include "Markov_Mol/ABC_PatchModel.h"

#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"

#include "Markov_Bay/LikelihoodEvaluation.h"



#include <memory>
namespace Markov_Bay_New
{

  class Markov_Likelihood
  {
  public:

     static LikelihoodEvaluation *run(const Markov_Mol_New::ABC_PatchModel *P, const Markov_IO_New::ABC_Experiment *E_A, const std::string &Likelihood_Algorithm, bool Is_Averaging, bool Use_Zero_Guard);
  };
}

#endif // MARKOVLIKELIHOOD_H
