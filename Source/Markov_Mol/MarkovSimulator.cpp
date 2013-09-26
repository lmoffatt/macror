#include "Markov_Mol/MarkovSimulator.h"

/// copy constructors

namespace Markov_Mol
{

Markov_Simulator* Markov_Simulator::clone()const
{
    return new Markov_Simulator(*this);
};
 Markov_Simulator* Markov_Simulator::create()const
{
    return new Markov_Simulator();
};
 std::ostream& Markov_Simulator::put(std::ostream& s) const
{
    s<<model();
    s<<N_channels();
    s<<noise();
    s<<"\time step\n"<<time_step_d<<"\n";
    return s;
};


 const ABC_Markov_Model& Markov_Simulator::model()const
{
    return this->Patch().Model();
};
 double Markov_Simulator::N_channels()const
{
    return Patch().AverageNumberOfChannels();
};
 const ABC_noise& Markov_Simulator::noise()const
{
    return Patch().Noise();
};

Markov_Simulator::Markov_Simulator(const ABC_PatchModel& P,
				   double time_step,
				   int32_t seed):
	patch_(P.clone()),
	time_step_d(time_step),
	sto(Borrowed::MersenneTwister::MTRand(
		Borrowed::MersenneTwister::seedinit(seed))
	    )
{
   patch_->Noise().set_random_generator(&sto);
};

Markov_Simulator::Markov_Simulator():
	patch_(),
time_step_d(0),
sto()
{}

 const ABC_PatchModel& Markov_Simulator::Patch()const
{
    return *this->patch_;
}





Experiment_simulation Markov_Simulator::run(const Markov_IO::ABC_Experiment& x,
					    std::size_t num_replicate)
{

    Experiment_simulation ES("my sim", x,this->Patch(),num_replicate);
    for (std::size_t i_r=0; i_r<num_replicate; i_r++)
    {
	ES.replicate(i_r);
	double x0=x.trace(0)[0].x();
	Markov_state S=model().start(x0,N_channels(),sto);
	//sstd::cerr<<"valor inicial de x ="<<x0<<"\n";
	for (std::size_t itrace=0; itrace<x.num_traces(); itrace++)
	{
	    x.trace(itrace);
	    for (std::size_t i=0; i<x.num_measures(); i++)
	    {
		//(x[i]).printSelf(std::cerr);
		S=model().run(x[i],S,time_step_d,sto);
		ES.y(S.ymean()+this->noise().sample(x.dt()));
	       // std::cout<<"\r \t"<<i;
	    };
	    S=model().run(x[x.num_measures()],S,x.dt(),sto);
	};
	std::cout<<" "<<i_r;
    };
    return ES;
}
}
