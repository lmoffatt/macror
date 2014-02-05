#include "Markov_Bay/YfitLikelihoodEvaluation.h"
#include "Markov_IO/auxiliarIO.h" //ToValue

namespace Markov_Bay
{

/// copy constructors
YfitLikelihoodEvaluation* YfitLikelihoodEvaluation::clone() const
{
    return new YfitLikelihoodEvaluation(*this);
}


/// default constructors
 YfitLikelihoodEvaluation* YfitLikelihoodEvaluation::create() const{
    return new YfitLikelihoodEvaluation();
}

 Markov_IO::ClassDescription YfitLikelihoodEvaluation::GetDescription()const
{

	Markov_IO::ClassDescription desc(myClass(),mySuperClass());;
	desc.push_back("name",myName());

	desc.push_back("Log_Likelihood",logL());

	desc.push_back("Expected_Log_Likelihood",elogL());

	desc.push_back("Variance_of_partial_Log_Likelihood",s2logL());


	desc.push_back("Partial_Log_Likelihoods",plogL());

	desc.push_back("Expected_Y_values",yfit());

	desc.push_back("Observed_Y_values",y());

	desc.push_back("Expected_variances",s2());


	return desc;

}

 bool YfitLikelihoodEvaluation::LoadFromDescription(const Markov_IO::ClassDescription& classDes)

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

     double Variance_of_partial_Log_Likelihood;
     if (!ToValue(classDes["Variance_of_partial_Log_Likelihood"],
		  Variance_of_partial_Log_Likelihood))
	 return false;


     Markov_LA::M_Matrix<double> Partial_Log_Likelihood;
     if (!ToValue(classDes["Partial_Log_Likelihoods"],Partial_Log_Likelihood))
	 return false;

     Markov_LA::M_Matrix<double> Expected_Y_values;
     if (!ToValue(classDes["Expected_Y_values"],Expected_Y_values))
	 return false;
     Markov_LA::M_Matrix<double> Observed_Y_values;
     if (!ToValue(classDes["Observed_Y_values"],Observed_Y_values))
	 return false;
     Markov_LA::M_Matrix<double> Expected_variances;
     if (!ToValue(classDes["Expected_variances"],Expected_variances))
	 return false;


     *this=YfitLikelihoodEvaluation(name,
				       Log_Likelihood,
				       Expected_Log_Likelihood,
				    Variance_of_partial_Log_Likelihood,
				       Partial_Log_Likelihood,
				    Expected_Y_values,
				    Observed_Y_values,
				    Expected_variances);

     return true;
 }



 YfitLikelihoodEvaluation::YfitLikelihoodEvaluation(const std::string& name,
			  double Log_Likelihood,
			  double expectedLogLikelihood,
			  double varianceLogLikelihood,
			  const Markov_LA::M_Matrix<double>& PartialLogL,
			  const Markov_LA::M_Matrix<double>& Yfit,
			  const Markov_LA::M_Matrix<double>& YObserved,
			  const Markov_LA::M_Matrix<double>& s2exp):
     PartialLikelihoodEvaluation(name,
	 Log_Likelihood,
	 expectedLogLikelihood,
	 varianceLogLikelihood,
	 PartialLogL),
     s2_(s2exp),
     yfit_(Yfit),
     y_(YObserved)
 {}

  YfitLikelihoodEvaluation::YfitLikelihoodEvaluation(const YfitLikelihoodEvaluation& other):
     PartialLikelihoodEvaluation(other),
      s2_(other.s2_),
      yfit_(other.yfit_),
      y_(other.y_)
 { }

  YfitLikelihoodEvaluation::YfitLikelihoodEvaluation():
      PartialLikelihoodEvaluation(),
      s2_()
,
       yfit_(),
       y_(){}
 YfitLikelihoodEvaluation&  YfitLikelihoodEvaluation::operator=(
     const YfitLikelihoodEvaluation& other)
 {
     if (this!=&other)
     {
	 YfitLikelihoodEvaluation tmp(other);
	 swap(*this,tmp);
     }
     return *this;
 }

 void swap(YfitLikelihoodEvaluation& one,YfitLikelihoodEvaluation& other)
{
   PartialLikelihoodEvaluation *oneB=&one;
   PartialLikelihoodEvaluation *otherB=&other;
   swap(*oneB,*otherB);
   swap(one.yfit_,other.yfit_);
 swap(one.y_,other.y_);
   swap(one.s2_,other.s2_);

   return;
 }

  YfitLikelihoodEvaluation::~YfitLikelihoodEvaluation(){}

     std::string YfitLikelihoodEvaluation::ClassName(){
	 return "Y_Expected_Likelihood_Evaluation";
     }






     std::string YfitLikelihoodEvaluation::myName()const
     {
	 return LikelihoodEvaluation::myName();
     }
     std::string YfitLikelihoodEvaluation::myClass()const
     {
	 return ClassName();
     }




const Markov_LA::M_Matrix<double>& YfitLikelihoodEvaluation::y()const
{
    return y_;
}

const Markov_LA::M_Matrix<double>& YfitLikelihoodEvaluation::yfit()const
{
    return yfit_;
}
const Markov_LA::M_Matrix<double>& YfitLikelihoodEvaluation::s2()const
{
    return s2_;
}



}


