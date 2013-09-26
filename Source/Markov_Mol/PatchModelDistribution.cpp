#include "Markov_Mol/PatchModelDistribution.h"
#include "Markov_IO/auxiliarIO.h"


namespace Markov_Mol
{
using Markov_IO::ParametersMoments;
using Markov_IO::ClassDescription;

std::string ABC_Distribution::mySuperClass()const
{
    return ClassName();
}

std::string ABC_Distribution::ClassName()
{
    return "Distribution";
}


PatchModelDistribution* PatchModelDistribution::clone() const{
    return new PatchModelDistribution(*this);
}

/// default constructors
PatchModelDistribution* PatchModelDistribution::create() const{
    return new PatchModelDistribution();
}

PatchModel* PatchModelDistribution::Sample()const
{
    return static_cast<PatchModel*>(NormalDistributed::Sample());
}



PatchModel* PatchModelDistribution::Mean()const
{
    return static_cast<PatchModel*>(NormalDistributed::Mean());
}



PatchModelDistribution::~PatchModelDistribution(){}

ClassDescription PatchModelDistribution::GetDescription()const
{
    ClassDescription desc(myClass(),mySuperClass());;
    desc.push_back("name",name_);
    desc.push_back("Patch_Model",*Mean());
    desc.push_back("Patch_Model_Parameters",get_parameters_moments());
    desc.push_back("Number_of_samples",nsamples_);

    return desc;
}

bool PatchModelDistribution::LoadFromDescription(const ClassDescription& classDes)
{     if (classDes.ClassName()!=myClass())
    {

	return false;
    }
    std::string name;
      if (!ToValue(classDes["name"],name_))
	  return false;

	ABC_PatchModel *model;
	if (!Markov_IO::ToValue(classDes["Patch_Model"],model))
	    return false;
	Markov_IO::ParametersMoments *pm;
	  if (!Markov_IO::ToValue(classDes["Patch_Model_Parameters"],pm))
	      return false;
	  std::size_t nsamples;
	    if (!ToValue(classDes["Number_of_samples"],nsamples))
		return false;


	      *this=PatchModelDistribution(name,
			     *model,
			     *pm,
			     nsamples);

		  return true;
}
std::string PatchModelDistribution::ClassName(){
    return "Patch_Model_Distribution";

}


std::string PatchModelDistribution::myName()const{
    return name_;

}
std::string PatchModelDistribution::myClass()const{
    return ClassName();
}




PatchModelDistribution::PatchModelDistribution(
    const std::string& name,
    const ABC_PatchModel& patch,
    const Markov_IO::ParametersMoments& paramMoments,
    std::size_t nsamples):
    NormalDistributed(patch,paramMoments),
    name_(name),
    nsamples_(nsamples)
{}

PatchModelDistribution::PatchModelDistribution(
    const PatchModelDistribution& other):
    NormalDistributed(other),
    name_(other.name_),
    nsamples_(other.nsamples_){}


PatchModelDistribution& PatchModelDistribution::operator=(const PatchModelDistribution& other){
    if (this!=&other)
    {
	PatchModelDistribution tmp(other);
	swap(*this, tmp);
    }
    return *this;
}



 void swap(PatchModelDistribution& one, PatchModelDistribution& other)
{
     Markov_Bay::NormalDistributed * oneB=&one;
     Markov_Bay::NormalDistributed * otherB=&other;
     swap(*oneB,*otherB);
     std::swap(one.name_, other.name_);
     std::swap(one.nsamples_,other.nsamples_);
  }




PatchModelDistribution::PatchModelDistribution(){}

}


