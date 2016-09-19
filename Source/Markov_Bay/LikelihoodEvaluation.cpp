#include <cmath>
#include "Markov_Bay/LikelihoodEvaluation.h"
namespace Markov_Bay_New
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


  std::string LikelihoodEvaluation::ClassName()
  {
    return "Likelihood_Evaluation";
  }




  std::string LikelihoodEvaluation::myClass()const
  {
    return ClassName();

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
    std::swap(one.experimentName_,other.experimentName_);
    std::swap(one.logL_,other.logL_);
    std::swap(one.elogL_,other.elogL_);
    std::swap(one.nsamples_,other.nsamples_);
    std::swap(one.s2logL_,other.s2logL_);

    return;
  }


  LikelihoodEvaluation::LikelihoodEvaluation():
    name_(),
    experimentName_(),
    logL_(0),
    elogL_(0),
    nsamples_(0),
    s2logL_(0)
  {
  }


  LikelihoodEvaluation::LikelihoodEvaluation(const std::string &name,
                                             std::string experimentName,
                                             double logL,
                                             double elogL,
                                             std::size_t ns,
                                             double s2logL):
    name_(name),
    experimentName_(experimentName),
    logL_(logL),
    elogL_(elogL),
    nsamples_(ns),
    s2logL_(s2logL)
  {
  }
}




