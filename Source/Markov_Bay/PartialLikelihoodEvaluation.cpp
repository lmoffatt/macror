

#include "Markov_Bay/PartialLikelihoodEvaluation.h"
#include "Markov_IO/auxiliarIO.h" //ToValue
#include "Markov_Bay/YfitLikelihoodEvaluation.h"

namespace Markov_Bay
{

  /// copy constructors
  PartialLikelihoodEvaluation* PartialLikelihoodEvaluation::clone() const
  {
    return new PartialLikelihoodEvaluation(*this);
  }


  /// default constructors
  PartialLikelihoodEvaluation* PartialLikelihoodEvaluation::create() const{
    return new PartialLikelihoodEvaluation();
  }

  Markov_IO::ClassDescription PartialLikelihoodEvaluation::GetDescription()const
  {

    Markov_IO::ClassDescription desc(myClass(),mySuperClass());
    desc.setEnvironment(getEnvironment());

    desc.push_back("name",id());

    desc.push_back("Experiment",experimentName());

    desc.push_back("Log_Likelihood",logL());

    desc.push_back("Expected_Log_Likelihood",elogL());

    desc.push_back("Variance_of_partial_Log_Likelihood",s2logL());

    desc.push_back("Partial_Log_Likelihoods",plogL());

    return desc;

  }

  bool PartialLikelihoodEvaluation::LoadFromDescription(const Markov_IO::ClassDescription& classDes)

  {
    if (classDes.ClassName()!=myClass())
      return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
      return false;
    std::string experimentName;
    if (!ToValue(classDes["Experiment"],name))
      return false;

    double Log_Likelihood;
    if (!ToValue(classDes["Log_Likelihood"],Log_Likelihood))
      return false;

    double Expected_Log_Likelihood;
    if (!ToValue(classDes["Expected_Log_Likelihood"],Expected_Log_Likelihood))
      return false;

    double Variance_of_partial_Log_Likelihood;
    if (!ToValue(classDes["Variance_of_partial_Log_Likelihood"],
                 Variance_of_partial_Log_Likelihood))
      return false;


    Markov_LA::M_Matrix<double> Partial_Log_Likelihood;
    if (!ToValue(classDes["Partial_Log_Likelihoods"],Partial_Log_Likelihood))
      return false;


    *this=PartialLikelihoodEvaluation(classDes.getEnvironment(),
                                      name,
                                      experimentName,
                                      Log_Likelihood,
                                      Expected_Log_Likelihood,
                                      Variance_of_partial_Log_Likelihood,
                                      Partial_Log_Likelihood);

    return true;
  }

  PartialLikelihoodEvaluation::PartialLikelihoodEvaluation(Markov_IO::ABC_Environment* e,
                                                           const std::string& name,
                                                           const std::string& experimentName,
                                                           double Log_Likelihood,
                                                           double expectedLogLikelihood,
                                                           double s2logLikelihood,
                                                           const Markov_LA::M_Matrix<double>& PartialLogL):
    LikelihoodEvaluation(e,
                         name,
                         experimentName,
                         Log_Likelihood,
                         expectedLogLikelihood,
                         size(PartialLogL),
                         s2logLikelihood),
    plogL_(PartialLogL){}

  PartialLikelihoodEvaluation::PartialLikelihoodEvaluation(const PartialLikelihoodEvaluation& other):
    LikelihoodEvaluation(other),
    plogL_(other.plogL_)
  { }

  PartialLikelihoodEvaluation::PartialLikelihoodEvaluation():
    LikelihoodEvaluation(),
    plogL_(){}

  PartialLikelihoodEvaluation&  PartialLikelihoodEvaluation::operator=(
      const PartialLikelihoodEvaluation& other)
  {
    if (this!=&other)
      {
        PartialLikelihoodEvaluation tmp(other);
        swap(*this,tmp);
      }
    return *this;
  }

  void swap(PartialLikelihoodEvaluation& one,PartialLikelihoodEvaluation& other)
  {
    LikelihoodEvaluation *oneB=&one;
    LikelihoodEvaluation *otherB=&other;
    swap(*oneB,*otherB);
    swap(one.plogL_,other.plogL_);
    return;
  }

  PartialLikelihoodEvaluation::~PartialLikelihoodEvaluation(){}

  std::string PartialLikelihoodEvaluation::ClassName(){
    return "Partial_Likelihood_Evaluation";
  }

  std::string PartialLikelihoodEvaluation::id()const
  {
    return LikelihoodEvaluation::id();
  }
  std::string PartialLikelihoodEvaluation::myClass()const
  {
    return ClassName();
  }




  const Markov_LA::M_Matrix<double>& PartialLikelihoodEvaluation::plogL()const
  {
    return plogL_;
  }




}

