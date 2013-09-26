#ifndef MARKOVOPTIMIZATION_H
#define MARKOVOPTIMIZATION_H

#include "Markov_IO/ABC_Use_Options.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_Mol/ABC_PatchModel.h"

#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_Bay/LikelihoodEvaluation.h"


namespace Markov_Bay
{

class Markov_Optimization: public Markov_IO::ABC_Use_Options
{
public:
    virtual Markov_Optimization* clone() const;

    virtual Markov_Optimization* create() const;

    virtual ~Markov_Optimization();

    virtual std::ostream& put(std::ostream& s) const;

    virtual bool operator==(const Markov_Optimization& other)const;


    virtual const Markov_IO::ABC_Experiment& experiment()const;

    virtual const Markov_Mol::PatchModelNormalDistribution& prior()const;

    virtual const Markov_Mol::PatchModelNormalDistribution& posterior()const;

    virtual const Markov_IO::ABC_Options& getOptions()const;
    virtual bool setOptions(const Markov_IO::ABC_Options &options);

    virtual LikelihoodEvaluation MaximumLikelihood();

    virtual PartialLikelihoodEvaluation run(const Markov_IO::Parameters& beta,
					    const std::string& dummyString);

    virtual YfitLikelihoodEvaluation run(const Markov_IO::Parameters& beta,
					    const std::string& dummyString0,
					 const std::string& dummyString1);

    virtual LikelihoodEvaluation run();

    virtual PartialLikelihoodEvaluation run(const std::string& dummyString);

    virtual YfitLikelihoodEvaluation run(const std::string& dummyString0,
					 const std::string& dummyString1);



    Markov_Optimization(const Markov_Mol::ABC_PatchModel& P,
		      const Markov_IO::ABC_Experiment& E,
		      const Markov_IO::ABC_Options& O);



    Markov_Optimization(const Markov_Optimization& ML);


    Markov_Optimization();


private:
    std::string name_;
    ABC_Markov_Optimization_step* L_A;
    const Markov_IO::ABC_Experiment* E_A;
   // Markov_Bay::LikelihoodOptions Options_;

   };

}

#endif // MARKOVOPTIMIZATION_H
