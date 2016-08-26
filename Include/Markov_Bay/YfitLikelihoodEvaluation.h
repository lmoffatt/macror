#ifndef YFITLIKELIHOODEVALUATION_H
#define YFITLIKELIHOODEVALUATION_H

#include "Markov_Bay/PartialLikelihoodEvaluation.h"

namespace Markov_Bay
{
   class YfitLikelihoodEvaluation:
           public PartialLikelihoodEvaluation
   {
   public:
       ///virtual copy constructors
       virtual YfitLikelihoodEvaluation* clone() const;
       ///virtual default constructors
       virtual YfitLikelihoodEvaluation* create() const;


       virtual Markov_IO::ClassDescription GetDescription()const;

       virtual bool LoadFromDescription(const Markov_IO::ClassDescription& classDes);

       static std::string ClassName();

       virtual std::string id()const;
           virtual std::string myClass()const;

	   virtual const Markov_LA::M_Matrix<double>& s2()const;
	   virtual const Markov_LA::M_Matrix<double>& yfit()const;
	   virtual const Markov_LA::M_Matrix<double>& y()const;

	   YfitLikelihoodEvaluation();
	   YfitLikelihoodEvaluation(const YfitLikelihoodEvaluation& other);
	   ~YfitLikelihoodEvaluation();
	   YfitLikelihoodEvaluation& operator=(const YfitLikelihoodEvaluation& other);

	   YfitLikelihoodEvaluation(Markov_IO::ABC_Environment *e,
				    const std::string& name,
				    const std::string& experimentName,
				    double Log_Likelihood,
				    double expectedLogLikelihood,
				    double varianceLogLikelihood,
				    const Markov_LA::M_Matrix<double>& PartialLogL,
				    const Markov_LA::M_Matrix<double>& Yfit,
				    const Markov_LA::M_Matrix<double>& YObserved,
				    const Markov_LA::M_Matrix<double>& s2);

	   friend void swap(YfitLikelihoodEvaluation& one, YfitLikelihoodEvaluation& other);



   protected:
          Markov_LA::M_Matrix<double> s2_;
          Markov_LA::M_Matrix<double> yfit_;
          Markov_LA::M_Matrix<double> y_;
   };




}



#endif // YFITLIKELIHOODEVALUATION_H
