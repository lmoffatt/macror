#include "Markov_Bay/ABC_Result.h"
#include "Markov_Bay/YfitLikelihoodEvaluation.h"
#include "Markov_IO/ClassDescription.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/OptimizationResult.h"

namespace Markov_Bay
{
ABC_Result::~ABC_Result()
{}

std::string ABC_Result::mySuperClass()const
{
    return ClassName();
}

std::string ABC_Result::ClassName()
{
    return "Result";
}







bool  create(ABC_Result*& result,const std::string& childClass)

{
    if (childClass==LikelihoodEvaluation::ClassName())
   {
       LikelihoodEvaluation* r;
       r=new LikelihoodEvaluation();
       result=r;
       return true;
   }
   else  if (childClass==PartialLikelihoodEvaluation::ClassName())
   {
       PartialLikelihoodEvaluation* r;
       r=new PartialLikelihoodEvaluation();
       result=r;
       return true;
   }
    else  if (childClass==YfitLikelihoodEvaluation::ClassName())
    {
	YfitLikelihoodEvaluation* r;
	r=new YfitLikelihoodEvaluation();
	result=r;
	return true;
    }
    else  if (childClass==SingleOptimizationResult::ClassName())
    {
	SingleOptimizationResult* r;
	r=new SingleOptimizationResult();
	result=r;
	return true;
    }
    else  if (childClass==OptimizationResult::ClassName())
    {
        OptimizationResult* r;
        r=new OptimizationResult();
        result=r;
        return true;
    }
    else
	return false;

}


bool LoadFromDescription(ABC_Result*& a,
			 const Markov_IO::ClassDescription& classDes)
{
    if (create(a,classDes.ClassName()))
	return a->LoadFromDescription(classDes);
    return false;
}




std::istream& operator>> (std::istream& stream,ABC_Result*& x)
{
    Markov_IO::ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!LoadFromDescription(x,classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}

}


