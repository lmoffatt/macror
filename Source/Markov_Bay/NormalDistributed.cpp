#include "Markov_Bay/NormalDistributed.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"

namespace Markov_Bay
{
/// copy constructors
NormalDistributed* NormalDistributed::clone() const{

    return new NormalDistributed(*this);

}
/// default constructors
NormalDistributed* NormalDistributed::create() const{
    return new NormalDistributed();
}

NormalDistributed::~NormalDistributed(){
    delete sample_;
}

NormalDistributed::NormalDistributed():
    sample_(0),
    parMoments_(),
    gaussian_()
{}

// std::ostream& put(std::ostream&) const=0{}

/// Apply the matching parameters
int NormalDistributed::apply_parameters(const Markov_IO::Parameters& p){
    int numUsed=parMoments_.apply_parameters(p);
    gaussian_.setMoments(parMoments_);
    return numUsed;

}

int NormalDistributed::apply_parameters_moments(const Markov_IO::ParametersMoments& p){
    int numUsed= parMoments_.apply_parameters(p.get_parameters());
    gaussian_.setMoments(parMoments_);
    return numUsed;


}


// object inspectors
const Markov_IO::Parameters& NormalDistributed::get_parameters()const{
    return parMoments_.get_parameters();
}


/// Returns the parameters of the object
const Markov_IO::ParametersMoments& NormalDistributed::get_parameters_moments()const{
    return parMoments_;

}

std::string NormalDistributed::id()const
{
    return "Normal_Distribution_build_with_"+this->parMoments_.id();
}
std::string NormalDistributed::ClassName()
{
    return "Normal_Distributed";
}




std::string NormalDistributed::myClass()const
{
    return ClassName()
	    ;     }

Markov_IO::ClassDescription NormalDistributed::GetDescription()const
{
 return {};
}

bool NormalDistributed::LoadFromDescription(const Markov_IO::ClassDescription &)
{
    return false;
}




/*    /// It returns a name for the object that identifies its architecture
  std::string name()const=0{} */


Markov_IO::ABC_Parametrizable* NormalDistributed::Sample()const
{
    Markov_IO::ABC_Parametrizable* o=sample_->clone();
    Markov_IO::Parameters p=o->get_parameters();
    p.transformed_values(gaussian_.sample());

    o->apply_parameters(p);
    return o;
}

Markov_IO::ABC_Parametrizable* NormalDistributed::Mean()const{
    Markov_IO::ABC_Parametrizable* o=sample_->clone();
    o->apply_parameters(parMoments_);
    return o;
}

Markov_IO::ABC_Parametrizable* NormalDistributed::Mode()const{
    return Mean();
}

double NormalDistributed::Probability(const Markov_IO::ABC_Parametrizable& sample)const
{
    Markov_IO::Parameters p=sample_->get_parameters();
    p.apply_parameters(sample.get_parameters());
    return gaussian_.P(p.transformed_values());
}

double NormalDistributed::Density(const Markov_IO::ABC_Parametrizable& )const{
    return 0.0;}


NormalDistributed::NormalDistributed(const Markov_IO::ABC_Parametrizable& sample,
				     const Markov_IO::ParametersMoments& parMoments):
    sample_(sample.clone()),
    parMoments_(parMoments),
    gaussian_(parMoments_)
{}

NormalDistributed::NormalDistributed(const NormalDistributed& other):
    sample_(other.sample_!=0?other.sample_->clone():0),
    parMoments_(other.parMoments_),
    gaussian_(other.gaussian_)
{}


NormalDistributed& NormalDistributed::operator=(const NormalDistributed& other)
{
    if (this!=&other)
    {
	NormalDistributed tmp(other);
	swap(*this,tmp);
    }
    return *this;
}

void swap(NormalDistributed& one, NormalDistributed& other)
{
    std::swap(one.sample_,other.sample_);
    swap(one.parMoments_,other.parMoments_);
    swap(one.gaussian_,other.gaussian_);
}


NormalDistributed NormalDistributed::meanDistribution(const std::vector<Markov_IO::ABC_Parametrizable*>& samples)
{
  if (samples.empty())
    return NormalDistributed();
  return NormalDistributed(*samples[0],Markov_IO::ParametersMoments::getMoments(samples));


}







}

