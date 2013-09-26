#include <cmath>
#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_Bay/PartialLikelihoodEvaluation.h"
namespace Markov_Bay
{


/// copy constructors
LikelihoodEvaluation* LikelihoodEvaluation::clone() const
{
    return new LikelihoodEvaluation(*this);
}


/// default constructors
LikelihoodEvaluation* LikelihoodEvaluation::create() const{
    return new LikelihoodEvaluation();
}

Markov_IO::ClassDescription LikelihoodEvaluation::GetDescription()const
{

    Markov_IO::ClassDescription desc(myClass(),mySuperClass());;
    desc.push_back("name",myName());

    desc.push_back("Log_Likelihood",logL());

    desc.push_back("Expected_Log_Likelihood",elogL());

    desc.push_back("Number_of_samples",nsamples());

    desc.push_back("Variance_of_partial_Log_Likelihood",s2logL());

    desc.push_back("Normalized_Log_Likelihood_difference",zScore());

    desc.push_back("Probability_of_Normalized_Log_Likelihood_difference",pzScore());

    desc.push_back("Normalized_variance_of_Log_Likelihood",zs2Score());

    desc.push_back("Probability_of_Normalized_variance",pzs2Score());

    return desc;

}

bool LikelihoodEvaluation::LoadFromDescription(const Markov_IO::ClassDescription& classDes)

{
    if (classDes.ClassName()!=myClass())
	return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
	return false;

    double Log_Likelihood;
    if (!ToValue(classDes["Log_Likelihood"],Log_Likelihood))
	return false;

    double Expected_Log_Likelihood;
    if (!ToValue(classDes["Expected_Log_Likelihood"],Expected_Log_Likelihood))
	return false;

    std::size_t Number_of_samples;
    if (!ToValue(classDes["Number_of_samples"],Number_of_samples))
	return false;

    double Variance_of_partial_Log_Likelihood;
    if (!ToValue(classDes["Variance_of_partial_Log_Likelihood"],
		 Variance_of_partial_Log_Likelihood))
	return false;


    *this=LikelihoodEvaluation(name,
			       Log_Likelihood,
			       Expected_Log_Likelihood,
			       Number_of_samples,
			       Variance_of_partial_Log_Likelihood
			       );

    return true;
}

std::string LikelihoodEvaluation::ClassName()
{
    return "Likelihood_Evaluation";
}
std::string LikelihoodEvaluation::myName()const
{
    return this->name_;
}
std::string LikelihoodEvaluation::myClass()const
{
    return ClassName();

}



std::vector<std::string> LikelihoodEvaluation::parentClasses()
{
    std::vector<std::string> v;
    v.push_back(ABC_Result::ClassName());

   return v;

}

std::vector<std::string> LikelihoodEvaluation::childClasses()
{
    std::vector<std::string> v;
    v.push_back(PartialLikelihoodEvaluation::ClassName());
    return v;
}

 bool LikelihoodEvaluation::amIAbstract()const
{
    return false;
}

 std::vector<std::string>  LikelihoodEvaluation::myParentClasses()const
{
    return parentClasses();
}
 std::vector<std::string>  LikelihoodEvaluation::myChildClasses()const
{
    return childClasses();
}




double LikelihoodEvaluation::logL()const
{
    return this->logL_;
}


double LikelihoodEvaluation::elogL()const
{

    return elogL_;
}

std::size_t LikelihoodEvaluation::nsamples()const
{

    return nsamples_;
}

double LikelihoodEvaluation::s2logL()const
{
    return s2logL_;

}




 double LikelihoodEvaluation::zScore()const
 {
     return (logL()-elogL())/std::sqrt(nsamples()/2);
 }

 double LikelihoodEvaluation::pzScore()const
 {
     return 1-erf(std::abs(zScore()/std::sqrt(2.)));
 }

 double LikelihoodEvaluation::zs2Score()const
 {
 //    return (2.*s2logL()-nsamples())/std::sqrt(2.*nsamples());
     return (std::sqrt(4.*s2logL())-std::sqrt(2*nsamples()-1));
  //   return std::pow((2.*s2logL()/nsamples()),1./3.)-
  //           (1.-2./(9.0*nsamples()))/(2./(9.*nsamples()));
 }

 double LikelihoodEvaluation::pzs2Score()const
 {
     return 1.-erf(std::abs(zs2Score()/std::sqrt(2.)));
 }


LikelihoodEvaluation& LikelihoodEvaluation::operator=(const LikelihoodEvaluation& other)
{
    if (this!=&other)
    {
	LikelihoodEvaluation tmp(other);
	swap(*this, tmp);
    }
    return *this;
}

void swap(LikelihoodEvaluation& one, LikelihoodEvaluation& other)
{
    std::swap(one.name_,other.name_);
    std::swap(one.logL_,other.logL_);
    std::swap(one.elogL_,other.elogL_);
    std::swap(one.nsamples_,other.nsamples_);
    std::swap(one.s2logL_,other.s2logL_);

    return;
}


LikelihoodEvaluation::LikelihoodEvaluation():
    name_(),
    logL_(0),
    elogL_(0),
    nsamples_(0),
    s2logL_(0)
{
}

LikelihoodEvaluation::LikelihoodEvaluation(const LikelihoodEvaluation &other):
    name_(other.name_),
    logL_(other.logL_),
    elogL_(other.elogL_),
    nsamples_(other.nsamples_),
    s2logL_(other.s2logL_)

{}


LikelihoodEvaluation::LikelihoodEvaluation(const std::string &name,
					   double logL,
					   double elogL,
					   std::size_t ns,
					   double s2logL):
    name_(name),
    logL_(logL),
    elogL_(elogL),
    nsamples_(ns),
    s2logL_(s2logL)
{
}
}
