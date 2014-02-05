#include  "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_IO/auxiliarIO.h"


namespace Markov_Bay
{

/// copy constructors
SingleOptimizationResult* SingleOptimizationResult::clone() const
{
    return new SingleOptimizationResult(*this);
}
/// default constructors
SingleOptimizationResult* SingleOptimizationResult::create() const{
    return new SingleOptimizationResult();
}


Markov_IO::ClassDescription SingleOptimizationResult::GetDescription()const
{
    Markov_IO::ClassDescription desc(myClass(),mySuperClass());;

    desc.push_back("name",name_);
    desc.push_back("Experiment",this->Experiment());
    desc.push_back("Start_Patch",Start());
    desc.push_back("Result_Distribution",Result());
    desc.push_back("Maximum_Likelihood",MaximumLikelihood());
    desc.push_back("Number_of_evaluations",nLikelihoodEvaluations());
    desc.push_back("Termination_message",TerminationMessage());

    return desc;

}

bool SingleOptimizationResult::LoadFromDescription(const Markov_IO::ClassDescription& classDes)
{
    if (classDes.ClassName()!=myClass())
	return false;
    std::string name;
    if (!ToValue(classDes["name"],name))
	return false;

    Markov_Mol::ABC_PatchModel* start;
    if (!ToValue(classDes["Start_Patch"],start))
	return false;

    std::string experimentname;
    if (!ToValue(classDes["Experiment"],experimentname))
	return false;

    Markov_Mol::PatchModelNormalDistribution* result;
    if (!ToValue(classDes["Result_Distribution"],result))
	return false;


    LikelihoodEvaluation* maximumlikelihood;
    if (!ToValue(classDes["Maximum_Likelihood"],
		 maximumlikelihood))
	return false;

    std::size_t nFunctionEvaluations;
    if (!ToValue(classDes["Number_of_evaluations"],
		 nFunctionEvaluations))
	return false;

     std::string termination;
    if (!ToValue(classDes["Termination_message"],
		 termination))
	return false;

    *this=SingleOptimizationResult(
		name,
		*start,
		experimentname,
		*result,
		*maximumlikelihood,
		nFunctionEvaluations,
		termination);
    delete start;
    delete result;
    delete maximumlikelihood;
    return true;
}

std::string SingleOptimizationResult::ClassName()
{
    return "Single_Optimization_Result";
}
std::string SingleOptimizationResult::myName()const
{
    return name_;
}
std::string SingleOptimizationResult::myClass()const
{
    return ClassName();
}





const Markov_Mol::ABC_PatchModel& SingleOptimizationResult::Start()const
{
  if (start_!=0)
    return *start_;
  else
    return Markov_Mol::PatchModel();
}

const Markov_Mol::PatchModelNormalDistribution& SingleOptimizationResult::Result()const
{
    return result_;
}

const LikelihoodEvaluation& SingleOptimizationResult::MaximumLikelihood()const
{
    return maximumlikelihood_;
}
/*
     const std::vector<SingleOptimizationResult::step>&
     SingleOptimizationResult::Evolution()const
     {
  return evolution_;
     }
*/
std::string SingleOptimizationResult::Experiment()const{
    return experimentName_;
}

std::size_t SingleOptimizationResult::nLikelihoodEvaluations()const{
    return nFunctionEvaluations_;
}

std::string SingleOptimizationResult::TerminationMessage()const
{
    return termination_;
}

SingleOptimizationResult::SingleOptimizationResult(const SingleOptimizationResult& other):
    name_(other.name_),
    start_(other.start_!=0?other.start_->clone():0),
    experimentName_(other.experimentName_),
    result_(other.result_),
    maximumlikelihood_(other.maximumlikelihood_),
    nFunctionEvaluations_(other.nFunctionEvaluations_),
    termination_(other.termination_)
{}
SingleOptimizationResult::SingleOptimizationResult():
    name_(),
    start_(new Markov_Mol::PatchModel()),
    experimentName_(),
    result_(),
    maximumlikelihood_(),
    nFunctionEvaluations_(0),
    termination_()
{}
 SingleOptimizationResult::~SingleOptimizationResult()
 {
   delete start_;
 }

SingleOptimizationResult::SingleOptimizationResult(
    const std::string& name,
    const Markov_Mol::ABC_PatchModel& start,
    const std::string& experimentName,
    const Markov_Mol::PatchModelNormalDistribution& result,
    const LikelihoodEvaluation& maximumlikelihood,
    std::size_t nFunctionEvaluations,
    const std::string& termination):
    name_(name),
    start_(start.clone()),
    experimentName_(experimentName),
    result_(result),
    maximumlikelihood_(maximumlikelihood),
    nFunctionEvaluations_(nFunctionEvaluations),
    termination_(termination)
{}

SingleOptimizationResult& SingleOptimizationResult::operator=(
    const SingleOptimizationResult& other)
{
    if (this!=&other)
    {
	SingleOptimizationResult tmp(other);
	swap(*this, tmp);
    }
    return *this;
}

void swap(SingleOptimizationResult& one,SingleOptimizationResult& other)
{
    std::swap(one.name_,other.name_);
    std::swap(one.start_,other.start_);
    std::swap(one.experimentName_,other.experimentName_);
    swap(one.result_,other.result_);
    swap(one.maximumlikelihood_,other.maximumlikelihood_);
    std::swap(one.nFunctionEvaluations_,other.nFunctionEvaluations_);
    std::swap(one.termination_,other.termination_);
}


std::istream& operator>> (std::istream& stream,SingleOptimizationResult*& x)
{
    Markov_IO::ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
        if(!x->LoadFromDescription(classDes))
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}


}


