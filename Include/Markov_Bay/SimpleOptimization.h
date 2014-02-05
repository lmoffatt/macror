#ifndef SIMPLEOPTIMIZATION_H
#define SIMPLEOPTIMIZATION_H

#include "Markov_IO/ABC_Use_Options.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_IO/ABC_IO.h"

#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/OptimizationResult.h"
#include "Markov_Bay/MarkovLikelihood.h"


namespace Markov_Bay
{

class SimpleOptimization: public Markov_IO::ABC_Use_Options
{
public:
    virtual SimpleOptimization* clone() const;

    virtual SimpleOptimization* create() const;




    virtual ~SimpleOptimization();

    virtual std::ostream& put(std::ostream& s) const;

    virtual bool operator==(const SimpleOptimization& other)const;




    virtual const Markov_IO::ABC_Experiment& experiment()const;



    virtual SingleOptimizationResult run(const Markov_IO::Parameters& beta);

    virtual OptimizationResult run(const Markov_Mol::PatchModelNormalDistribution& betaDist,
                                         std::size_t numStarts);


    SimpleOptimization(const std::string& name,
                       const Markov_Mol::ABC_PatchModel& P,
		      const Markov_IO::ABC_Experiment& E,
              const Markov_IO::ABC_Options& O,
                       Markov_IO::ABC_IO* io);



    SimpleOptimization(const SimpleOptimization& other);


    SimpleOptimization();
    class Options:public Markov_IO::BaseOptions
    {
    public:
	Options();
	Options(const std::string& name);
	Options(const Markov_IO::ABC_Options& options);

	Options(const Options& other);
	Options& operator=(const Options& other);

	friend void swap(Options& x,Options& y);

	Options(const std::string& myname,
		const std::string& HessianUpdate,
		const std::string& Termination,
		std::size_t maxEval,
		std::size_t maxIter,
		const Markov_IO::ABC_Options& likelihoodOptions,
		const Markov_IO::ABC_Options& stepOptions,
		const Markov_IO::ABC_Options& terminationOptions
		);
	virtual std::string myClass()const;
	static std::string ClassName();

    };
    virtual const Options& getOptions()const;
    virtual bool setOptions(const Markov_IO::ABC_Options &options);



private:
    std::string name_;
    Markov_IO::Parameters par_;
    Markov_Likelihood ML_;
    Options O_;
    std::size_t maxfeval_;
    std::size_t maxiter_;
    Markov_IO::ABC_IO* io_;

   };




}




#endif // SIMPLEOPTIMIZATION_H
