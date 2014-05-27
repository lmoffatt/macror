#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/QMarkovModel.h"
#include "Markov_Mol/GaussianNoise.h"

namespace Markov_Mol
{

PatchModel* PatchModel::clone() const
{
    return new PatchModel(*this);
}

/// default constructors
PatchModel* PatchModel::create() const
{
    return new PatchModel();
}





PatchModel::~PatchModel()
{
    delete model_;
    delete noise_;
}

int PatchModel::apply_parameters(const Parameters& p)
{
    int usedPar=this->model_->apply_parameters(p);
    if (p.HasName(num_channels_label()))
    {
	this->nChannels_=p[num_channels_label()];
//	parameters_[num_channels_label()]=nChannels_;
	usedPar++;
    }
    usedPar+=noise_->apply_parameters(p);
  //  this->BuildParameters();
    return usedPar;
}

/// It returns the parameters of the object
const Parameters& PatchModel::get_parameters()const
{
 parameters_=BuildParameters();

  return parameters_;
}

const ABC_Markov_Model& PatchModel::Model()const{return *model_;}

std::size_t PatchModel::ChannelsCount()const {return nChannels_;}

double PatchModel::AverageNumberOfChannels()const {return nChannels_;}

const ABC_noise& PatchModel::Noise()const {return *noise_;}

ABC_noise& PatchModel::Noise() {return *noise_;}

Markov_IO::ClassDescription PatchModel::GetDescription()const
{
    //std::cout<<ClassName();
    //std::cout<<mySuperClass();
    Markov_IO::ClassDescription desc(myClass(),mySuperClass());
    desc.push_back("name",this->myName());
    // std::cout<<Model();
    desc.push_back("Channel_Model",Model());
    desc.push_back("Number_of_Channels",
                   this->AverageNumberOfChannels(),
                   "[mean number of channels]",
                   "expected mean number of channels, can be a fractional number",
                   "it indicates the average number of channels that we hope "
                   "to find in the preparation");
    desc.push_back("Noise", Noise(),
                   "intrumental noise not related to the behavior of the ion channel",
                   "it describes the measuring noise");
    return desc;
};


std::string PatchModel::ClassName()
{
    return "Simple_Patch_Model";
}

std::string PatchModel::myName()const
{
    return name_;
}

std::string PatchModel::myClass()const
{
    return ClassName();
}



bool PatchModel::LoadFromDescription(const ClassDescription& classDes)
{
    if (classDes.ClassName()!=myClass())
    {

	return false;
    }
    std::string name;
    if (!ToValue(classDes["name"],name))
	return false;

    ABC_Markov_Model* model;
    if (!ToValue(classDes["Channel_Model"],model))
	return false;
    double numChannels;
    if (!ToValue(classDes["Number_of_Channels"],numChannels))
	return false;

    ABC_noise* noise;

    const ABC_Object* noiseO=classDes["Noise"];

    if (!ToValue(noiseO,noise))
	return false;

    PatchModel tmp(name,
		   *model,
		   numChannels,
		   *noise,
		   sto);

    swap(*this,tmp);
    return true;

}



PatchModel::PatchModel(const std::string& name,
		       const ABC_Markov_Model& model,
		       std::size_t nChannels,
		       const ABC_noise& noise,
		       const Borrowed::MersenneTwister::MTRand& mtrand):
    name_(name),
    model_(model.clone()),
    nChannels_(nChannels),
    noise_(noise.clone()),
    parameters_(),
    sto(mtrand)
{
    BuildParameters();
}

PatchModel::PatchModel():
    name_(),
    model_(new Q_Markov_Model()),
    nChannels_(0),
    noise_(new gaussian_noise()),
    parameters_(),
    sto()
{
}



PatchModel::PatchModel(const PatchModel& other):
    name_(other.name_),
    model_(other.Model().clone()),
    nChannels_(other.nChannels_),
    noise_(other.Noise().clone()),
    parameters_(),
    sto(other.sto)
{
    BuildParameters();
}



Markov_IO::Parameters PatchModel::BuildParameters() const
{
  Markov_IO::Parameters p=Model().get_parameters();
    p.push_back(num_channels_label(),
			  AverageNumberOfChannels(),
			  Markov_IO::Parameters::LOG);
    p+=Noise().get_parameters();
    return p;
}

void swap(PatchModel& one, PatchModel& two)
{
    std::swap(one.name_,two.name_);
    std::swap(one.model_,two.model_);

    std::swap(one.nChannels_,two.nChannels_);
    std::swap(one.noise_,two.noise_);
    Borrowed::MersenneTwister::MTRand sto2=one.sto;
    one.sto=two.sto;
    two.sto=sto2;
    swap(one.parameters_,two.parameters_);
}

Experiment_simulation PatchModel::run(const Markov_IO::ABC_Experiment& x,
				      std::size_t n_replicates,
				      const Markov_IO::ABC_Options& opt)
{
    Experiment_simulation ES(myName()+"_on_"+x.myName(),
			     x,
			     *this,
			     n_replicates);

    this->Noise().set_random_generator(&sto);
    double time_step=opt.real("time_step");
    std::size_t num_steps=opt.count("num_steps");

//#pragma omp parallel for
    for (std::size_t i_r=0; i_r<n_replicates; i_r++)
    {
	ES.replicate(i_r);
	double x0=x.trace(0)[0].sub_step(0).x();

	Markov_state S=this->Model().start(x0,this->ChannelsCount(),sto);
	for (std::size_t itrace=0; itrace<x.num_traces(); itrace++)
	{
	    x.trace(itrace);
	    for (std::size_t i=0; i<x.num_measures(); i++)
	    {
		//(x[i]).printSelf(std::cerr);
		std::size_t nSteps;
		if (x.dt()>time_step)
		  nSteps=std::ceil(x.dt()/time_step-0.5);
		else nSteps=1;
		nSteps=std::max(nSteps,num_steps);
		S=Model().run(x[i],S,nSteps,sto);
		double yval=S.ymean()+this->Noise().sample(x.dt());
		ES.y(yval);
		// std::cout<<"\r \t"<<i;
	    };
	    S=Model().run(x[x.num_measures()],S,x.dt(),sto);
	};
	std::cerr<<" "<<i_r;
    };
    return ES;
}

bool LoadFromDescription(ABC_Environment*e,
    PatchModel*& p,
			 const Markov_IO::ClassDescription& classDes)
{
    p=new PatchModel();
    return p->LoadFromDescription(classDes);
}
/*
bool LoadFromStringDescription(PatchModel*& p,
                         const Markov_IO::ClassDescription& classDes)
{
    p=new PatchModel();
    return p->LoadFromStringDescription(classDes);
}
*/
bool  create(PatchModel*& p,const std::string& childClass)
{
    if (childClass==PatchModel::ClassName())
    {
	PatchModel* m;
	m=new PatchModel();
	p=m;
	return true;
    }
    return false;

}

}






