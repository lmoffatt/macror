#ifndef MARKOVLIKELIHOOD_H
#define MARKOVLIKELIHOOD_H

#include "Markov_LA/Matrix.h"

#include "Markov_IO/ABC_Experiment.h"

#include "Markov_Mol/ABC_PatchModel.h"

#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"




namespace Markov_Bay_New
{

class Markov_Likelihood
{
public:
    virtual Markov_Likelihood* clone() const;

    virtual Markov_Likelihood* create() const;

    virtual ~Markov_Likelihood();

    virtual const Markov_IO_New::ABC_Experiment* experiment()const;

    virtual const Markov_Mol_New::ABC_PatchModel* patch()const;

    virtual const Markov_Mol_New::ABC_Markov_Model& model()const;







    Markov_Likelihood(Markov_Mol_New::ABC_PatchModel *patch,
                      Markov_IO_New::ABC_Experiment* experiment,
                      const std::string algorithm,
                      bool isaveraging,
                      bool zeroGuard,
                      double dxForScore,
                      bool showPartialLikelihood=false,
                      bool showPredictedValue=false,
                      bool runApproximation=false,
                      std::size_t numSteps=100,
                      std::size_t numSamples=1000);



    Markov_Likelihood(const Markov_Likelihood& ML)=default;


    Markov_Likelihood()=default;

    Markov_Likelihood& operator=(const Markov_Likelihood& other)=default;



    private:


    std::string experimentName_;
    std::string patchName_;
    ABC_Markov_Likelihood_step* L_A;
    const Markov_IO_New::ABC_Experiment* E_A;

   };
}

#endif // MARKOVLIKELIHOOD_H
