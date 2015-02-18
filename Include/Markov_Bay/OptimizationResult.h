#ifndef OPTIMIZATIONRESULT_H
#define OPTIMIZATIONRESULT_H
#include "Markov_Bay/ABC_Result.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_Bay/SingleOptimizationResult.h"

namespace Markov_Bay
{

class OptimizationResult: public ABC_Result
{
public:
    ///virtual copy constructors
    virtual OptimizationResult* clone() const;
    ///virtual default constructors
    virtual OptimizationResult* create() const;

  virtual ~OptimizationResult();

    virtual Markov_IO::ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const Markov_IO::ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;

    virtual const Markov_Mol::PatchModelNormalDistribution& Prior()const;

    virtual const Markov_Mol::PatchModelNormalDistribution& Posterior()const;
    virtual const Markov_Mol::PatchModelNormalDistribution& PosteriorMean()const;

    virtual double Reach_ML_ratio()const;
    virtual Markov_LA::M_Matrix<std::size_t> Reach_ML_indexes()const;

    virtual const Markov_IO::ABC_Experiment& Experiment()const;

    virtual const LikelihoodEvaluation& MaximumLikelihood()const;


    OptimizationResult(const OptimizationResult& other);
    OptimizationResult();
    OptimizationResult(	const std::string& name,
	const Markov_IO::ABC_Experiment& experiment,
	const Markov_Mol::PatchModelNormalDistribution& priorD,
	std::vector<SingleOptimizationResult> optRuns,
			double resLogL=0.01);

    OptimizationResult& operator=(const OptimizationResult& other);

    friend void swap(OptimizationResult& oner,OptimizationResult& other);



protected:
    void calc();
    std::string name_;
    const Markov_IO::ABC_Experiment* E_;
    Markov_Mol::PatchModelNormalDistribution priorPatchDist_;
    std::vector<SingleOptimizationResult> optRuns_;
    double resLogL_;
    std::vector<std::size_t> reachMaxLik_;
    LikelihoodEvaluation maxLik_;
    Markov_Mol::PatchModelNormalDistribution posteriorModeDist_;
    Markov_Mol::PatchModelNormalDistribution posteriorMeanDist_;

    };

std::istream& operator>> (std::istream& stream,OptimizationResult*& x);



}


#endif // OPTIMIZATIONRESULT_H
