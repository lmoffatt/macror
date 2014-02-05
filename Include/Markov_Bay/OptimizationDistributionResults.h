#ifndef OPTIMIZATIONDISTRIBUTIONRESULTS_H
#define OPTIMIZATIONDISTRIBUTIONRESULTS_H

#include "Markov_Bay/ABC_Result.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_IO/ABC_Experiment.h"

namespace Markov_Bay
{

class OptimizationDistributionResult: public ABC_Result

{
public:
    ///virtual copy constructors
    virtual OptimizationDistributionResult* clone() const;
    ///virtual default constructors
    virtual OptimizationDistributionResult* create() const;


    virtual Markov_IO::ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const Markov_IO::ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string myName()const;
    virtual std::string myClass()const;

    virtual const Markov_Mol::PatchModelNormalDistribution& Prior()const;

    virtual const Markov_Mol::PatchModelNormalDistribution& Posterior()const;

    virtual const Markov_IO::ABC_Experiment& Experiment()const;

    virtual const LikelihoodEvaluation& MaximumLikelihood()const;

    virtual std::size_t nLikelihoodEvaluations()const;

    OptimizationDistributionResult(const OptimizationDistributionResult& other);
    OptimizationDistributionResult();
    OptimizationDistributionResult(	const std::string& name,
        const Markov_IO::ABC_Experiment& experiment,
        const Markov_Mol::PatchModelNormalDistribution& priorD,
        const Markov_Mol::PatchModelNormalDistribution& posteriorD,
        const LikelihoodEvaluation& maxLikelihood,
        std::size_t nFunctionEvaluations);

    OptimizationDistributionResult& operator=(const OptimizationDistributionResult& other);

    friend void swap(OptimizationDistributionResult& oner,OptimizationDistributionResult& other);

protected:
    std::string name_;
    const Markov_IO::ABC_Experiment* E_;
    Markov_Mol::PatchModelNormalDistribution priorPatchDist_;
    LikelihoodEvaluation maxLik_;
    Markov_Mol::PatchModelNormalDistribution posteriorPatchDist_;
    std::size_t numfevals_;
    };

}


#endif // OPTIMIZATIONDISTRIBUTIONRESULTS_H
