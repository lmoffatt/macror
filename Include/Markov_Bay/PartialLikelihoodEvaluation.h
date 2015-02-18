#ifndef PARTIALLIKELIHOODEVALUATION_H
#define PARTIALLIKELIHOODEVALUATION_H
#include "Markov_Bay/LikelihoodEvaluation.h"

namespace Markov_Bay
{
   class PartialLikelihoodEvaluation:
	   public LikelihoodEvaluation
   {
   public:
       ///virtual copy constructors
       virtual PartialLikelihoodEvaluation* clone() const;
       ///virtual default constructors
       virtual PartialLikelihoodEvaluation* create() const;


       virtual Markov_IO::ClassDescription GetDescription()const;

       virtual bool LoadFromDescription(const Markov_IO::ClassDescription& classDes);

       static std::string ClassName();

       virtual std::string id()const;
	   virtual std::string myClass()const;


	   virtual const Markov_LA::M_Matrix<double>& plogL()const;


	   PartialLikelihoodEvaluation(Markov_IO::ABC_Environment *e,
				       const std::string& name,
				       const std::string& experimentName,
				       double Log_Likelihood,
				       double expectedLogLikelihood,
				       double varianceLogLikelihood,
				       const Markov_LA::M_Matrix<double>& PartialLogL);

	   PartialLikelihoodEvaluation(const PartialLikelihoodEvaluation& other);

	   PartialLikelihoodEvaluation();

	   PartialLikelihoodEvaluation& operator=(const PartialLikelihoodEvaluation& other);

	   friend void swap(PartialLikelihoodEvaluation& one, PartialLikelihoodEvaluation& other);

	   virtual ~PartialLikelihoodEvaluation();
protected:
	  Markov_LA::M_Matrix<double> plogL_;

   };




}


#endif // PARTIALLIKELIHOODEVALUATION_H
