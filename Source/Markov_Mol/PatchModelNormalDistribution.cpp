#include "Markov_Mol/PatchModelNormalDistribution.h"
#include "Markov_IO/auxiliarIO.h"


namespace Markov_Mol
{
using Markov_IO::ParametersMoments;
using Markov_IO::ClassDescription;



PatchModelNormalDistribution*
PatchModelNormalDistribution::clone() const{
    return new PatchModelNormalDistribution(*this);
}

/// default constructors
PatchModelNormalDistribution*
PatchModelNormalDistribution::create() const{
    return new PatchModelNormalDistribution();
}

PatchModel*
PatchModelNormalDistribution::Sample()const
{
    return dynamic_cast<PatchModel*>(NormalDistributed::Sample());
}



PatchModel* PatchModelNormalDistribution::Mean()const
{
    return dynamic_cast<PatchModel*>(NormalDistributed::Mean());
}



std::size_t PatchModelNormalDistribution::nSamples()const
{
  return nsamples_;
}




PatchModelNormalDistribution::~PatchModelNormalDistribution(){}

ClassDescription PatchModelNormalDistribution::GetDescription()const
{
    ClassDescription desc(myClass(),mySuperClass());;
    desc.push_back("name",name_);
    if (nsamples_>0)
    desc.push_back("Patch_Model",*Mean());
    else
    {
	desc.push_back("Patch_Model",PatchModel());
    }
    desc.push_back("Patch_Model_Parameters",get_parameters_moments());
    desc.push_back("Number_of_samples",nsamples_);

    return desc;
}

bool PatchModelNormalDistribution::LoadFromDescription(const ClassDescription& classDes)
{     if (classDes.ClassName()!=myClass())
    {

	return false;
    }
    std::string name;
      if (!ToValue(classDes["name"],name))
	  return false;

	ABC_PatchModel *model;
	if (!Markov_IO::ToValue(classDes["Patch_Model"],model))
	    return false;
	  Markov_IO::Parameters *pm;
	  if (!Markov_IO::ToValue(classDes["Patch_Model_Parameters"],pm))
	      return false;
	  Markov_IO::ParametersMoments P;
	  P.apply_parameters(*pm);
	  std::size_t nsamples;
	    if (!ToValue(classDes["Number_of_samples"],nsamples))
		return false;


	      *this=PatchModelNormalDistribution(name,
			     *model,
			     P,
			     nsamples);

		  return true;
}
std::string PatchModelNormalDistribution::ClassName(){
    return "Patch_Model_Normal_Distribution";

}


std::string PatchModelNormalDistribution::myName()const{
    return name_;

}
std::string PatchModelNormalDistribution::myClass()const{
    return ClassName();
}




PatchModelNormalDistribution::PatchModelNormalDistribution(
    const std::string& name,
    const ABC_PatchModel& patch,
    const Markov_IO::ParametersMoments& paramMoments,
    std::size_t nsamples):
    NormalDistributed(patch,paramMoments),
    name_(name),
    nsamples_(nsamples)
{}

PatchModelNormalDistribution::PatchModelNormalDistribution(
    const PatchModelNormalDistribution& other):
    NormalDistributed(other),
    name_(other.name_),
    nsamples_(other.nsamples_){}


PatchModelNormalDistribution& PatchModelNormalDistribution::operator=(const PatchModelNormalDistribution& other){
    if (this!=&other)
    {
	PatchModelNormalDistribution tmp(other);
	swap(*this, tmp);
    }
    return *this;
}



 void swap(PatchModelNormalDistribution& one, PatchModelNormalDistribution& other)
{
     Markov_Bay::NormalDistributed * oneB=&one;
     Markov_Bay::NormalDistributed * otherB=&other;
     swap(*oneB,*otherB);
     std::swap(one.name_, other.name_);
     std::swap(one.nsamples_,other.nsamples_);
  }




PatchModelNormalDistribution::PatchModelNormalDistribution():
    NormalDistributed(),
    name_(),
    nsamples_(0)
{}





}



