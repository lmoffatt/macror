#ifndef LIKELIHOODEVALUATION_H
#define LIKELIHOODEVALUATION_H
#include "Markov_IO/ABC_Saveable.h"
#include "Markov_LA/Matrix.h"
#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_IO/ABC_Use_Options.h"
#include "Markov_IO/Options.h"
#include "Markov_Bay/ABC_Result.h"

namespace Markov_Bay
{

class LikelihoodEvaluation: public ABC_Result

{
public:
       ///virtual copy constructors
       virtual LikelihoodEvaluation* clone() const;
       ///virtual default constructors
       virtual LikelihoodEvaluation* create() const;


	virtual Markov_IO::ClassDescription GetDescription()const;

	virtual bool LoadFromDescription(const Markov_IO::ClassDescription& classDes);

    static std::string ClassName();
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

    virtual std::string myName()const;
	virtual std::string myClass()const;



	virtual double logL()const;
	virtual double elogL()const;
	virtual double s2logL()const;
	virtual std::size_t nsamples()const;

	virtual double zScore()const;

	virtual double pzScore()const;

	virtual double zs2Score()const;

	virtual double pzs2Score()const;


	LikelihoodEvaluation(const LikelihoodEvaluation& other);
	LikelihoodEvaluation();
	LikelihoodEvaluation(const std::string& name,
			     double logL,
			     double elogL,
			     std::size_t ns,
			     double s2logL);

	LikelihoodEvaluation& operator=(const LikelihoodEvaluation& other);

	friend void swap(LikelihoodEvaluation& oner,LikelihoodEvaluation& other);

protected:
	std::string name_;
	double logL_;
	double elogL_;
	std::size_t nsamples_;
	double s2logL_;
};

}

#endif // LIKELIHOODEVALUATION_H
