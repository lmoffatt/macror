#ifndef MARKOVLIKELIHOOD_H
#define MARKOVLIKELIHOOD_H

#include "Markov_LA/Matrix.h"

#include "Markov_IO/ABC_Put.h"
#include "Markov_IO/ABC_Experiment.h"

#include "Markov_Mol/ABC_PatchModel.h"

#include "Markov_Bay/ABC_MarkovLikelihoodStep.h"

#include "Markov_IO/ABC_Use_Options.h"

#include "Markov_Bay/YfitLikelihoodEvaluation.h"

#include "Markov_IO/ABC_Environment.h"

namespace Markov_Bay
{

class Markov_Likelihood: public Markov_IO::ABC_Use_Options
{
public:
    virtual Markov_Likelihood* clone() const;

    virtual Markov_Likelihood* create() const;

    virtual ~Markov_Likelihood();

    virtual std::ostream& put(std::ostream& s) const;

    virtual bool operator==(const Markov_Likelihood& other)const;


    virtual const Markov_IO::ABC_Experiment* experiment()const;

    virtual const Markov_Mol::ABC_PatchModel* patch()const;

    virtual const Markov_Mol::ABC_Markov_Model& model()const;

    virtual const Markov_IO::ABC_Options& getOptions()const;
    virtual bool setOptions(const Markov_IO::ABC_Options &options);

    virtual LikelihoodEvaluation run(const Markov_IO::Parameters& beta);

    virtual LikelihoodEvaluation infinity();

    virtual PartialLikelihoodEvaluation run(const Markov_IO::Parameters& beta,
                                            const std::string& /*dummyString*/);

    virtual YfitLikelihoodEvaluation run(const Markov_IO::Parameters& beta,
                                            const std::string& /*dummyString0*/,
                                         const std::string& /*dummyString1*/);

    virtual LikelihoodEvaluation run();




    virtual Markov_LA::M_Matrix<double> score(const Markov_IO::Parameters& beta);


    virtual double score(const Markov_IO::Parameters& beta,
			 const Markov_LA::M_Matrix<double>&  direction);


    virtual Markov_LA::M_Matrix<double>
    FisherInformationMatrix(const Markov_IO::Parameters& beta);


  virtual Markov_LA::M_Matrix<double>
  HessianAproximationMatrix(const Markov_IO::Parameters& beta);


    virtual PartialLikelihoodEvaluation run(const std::string&);

    virtual YfitLikelihoodEvaluation run(const std::string& /*dummyString0*/,
                                         const std::string& /*dummyString1*/);




    Markov_Likelihood(Markov_IO::ABC_Environment* e,
                      const std::string patch,
                      const std::string experiment,
                      const Markov_IO::ABC_Options& O);



    Markov_Likelihood(const Markov_Likelihood& ML);


    Markov_Likelihood();

    Markov_Likelihood& operator=(const Markov_Likelihood& other);
    friend void swap(Markov_Likelihood& x,Markov_Likelihood& y);

    class Options:public Markov_IO::BaseOptions
    {
    public:
	Options();
	Options(const std::string& myname,
		const std::string algorithm,
		bool isaveraging,
		bool zeroGuard,
		double dxForScore,
		bool showPartialLikelihood=false,
		bool showPredictedValue=false,
		bool runApproximation=false,
		std::size_t numSteps=100,
		std::size_t numSamples=1000);
	Options(const Markov_IO::ABC_Options& options);
	virtual std::string myClass()const;
	static std::string ClassName();


    };


    private:

    std::string name_;
    Markov_IO::ABC_Environment* E_;
    std::string experimentName_;
    std::string patchName_;
    ABC_Markov_Likelihood_step* L_A;
    const Markov_IO::ABC_Experiment* E_A;
    Options Options_;

   };
}
#endif // MARKOVLIKELIHOOD_H
