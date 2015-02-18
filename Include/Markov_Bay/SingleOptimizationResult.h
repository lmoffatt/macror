#ifndef SINGLEOPTIMIZATIONRESULT_H
#define SINGLEOPTIMIZATIONRESULT_H

#include "Markov_Bay/ABC_Result.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_IO/ABC_Experiment.h"

namespace Markov_Bay
{

class SingleOptimizationResult: public ABC_Result

{
public:
    ///virtual copy constructors
    virtual SingleOptimizationResult* clone() const;
    ///virtual default constructors
    virtual SingleOptimizationResult* create() const;


    virtual Markov_IO::ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const Markov_IO::ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string id()const;
    virtual std::string myClass()const;

    virtual const Markov_Mol::ABC_PatchModel& Start()const;

    virtual const Markov_Mol::PatchModelNormalDistribution& Result()const;

    virtual const LikelihoodEvaluation& MaximumLikelihood()const;

/*    struct step
    {
	Markov_LA::M_Matrix<double> beta;
	double logL;
	double elogL;
	Markov_LA::M_Matrix<double> score;
    };
    virtual const std::vector<step>& Evolution()const;
*/
    virtual  std::string Experiment()const;

    virtual std::size_t nLikelihoodEvaluations()const;
    virtual std::string TerminationMessage()const;


    SingleOptimizationResult(const SingleOptimizationResult& other);
    SingleOptimizationResult();
    SingleOptimizationResult(const std::string& name,
			     const Markov_Mol::ABC_PatchModel& start,
			     const std::string& experimentName,
			     const Markov_Mol::PatchModelNormalDistribution& result,
			     const LikelihoodEvaluation& maximumlikelihood,
			     std::size_t nFunctionEvaluations,
			     const std::string& termination);

    SingleOptimizationResult& operator=(const SingleOptimizationResult& other);

    friend void swap(SingleOptimizationResult& oner,SingleOptimizationResult& other);
    virtual ~SingleOptimizationResult();

protected:
    std::string name_;
    const Markov_Mol::ABC_PatchModel* start_;
    std::string experimentName_;

     Markov_Mol::PatchModelNormalDistribution result_;
     LikelihoodEvaluation maximumlikelihood_;
     std::size_t nFunctionEvaluations_;
     std::string termination_;
    };

std::istream& operator>> (std::istream& stream,SingleOptimizationResult*& x);



}



#endif // SINGLEOPTIMIZATIONRESULT_H
