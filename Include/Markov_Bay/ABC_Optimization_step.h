#ifndef ABC_OPTIMIZATION_STEP_H
#define ABC_OPTIMIZATION_STEP_H
#include "Markov_IO/ABC_Put.h"
#include "Markov_LA/Matrix.h"
#include "Markov_IO/Parameters.h"
#include "Markov_IO/ParametersMoments.h"
#include "Markov_Bay/MarkovLikelihood.h"



namespace Markov_Bay
{
class ABC_OptimizationStep
{
public:
    virtual ABC_OptimizationStep* clone()const=0;
    virtual ABC_OptimizationStep* create()const=0;

    virtual ~ABC_OptimizationStep();


    virtual ABC_OptimizationStep& next()=0;

    virtual ABC_OptimizationStep& start(const Markov_IO::Parameters& x0)=0;

    virtual const Markov_IO::Parameters& CurrentParameters()const=0;

    virtual const LikelihoodEvaluation& Likelihood()const=0;

    virtual const Markov_LA::M_Matrix<double>& Score()const=0;

    virtual const Markov_LA::M_Matrix<double>& HessianInv()const=0;

    virtual const Markov_LA::M_Matrix<double>& Hessian()const=0;

    virtual const Markov_LA::M_Matrix<double>& FisherInformation()=0;

    virtual const Markov_LA::M_Matrix<double>& HessianApprox()=0;


    virtual const Markov_LA::M_Matrix<double>& SearchDirection()const=0;

    virtual const Markov_LA::M_Matrix<double>& LastParametersChange()const=0;

    virtual size_t NumEvaluationsInStep()const=0;

    virtual double AdaptiveStepLength()const=0;

    virtual double LastLogLikelihoodChange()const=0;

    virtual double ExpectedLogLikelihoodChange()const=0;


    virtual Markov_IO::ParametersMoments moments()=0;


 };

}


#endif // ABC_OPTIMIZATION_STEP_H
