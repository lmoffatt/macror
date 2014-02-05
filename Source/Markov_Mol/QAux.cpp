#include "Markov_Mol/QAux.h"

#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/matrixRelational.h"

namespace Markov_Mol
{

Markov_LA::M_Matrix<size_t> random_N_sample(const Markov_LA::M_Matrix<double>& p,
				 std::size_t Nchannels,
				 Borrowed::MersenneTwister::MTRand& sto)
{
    Markov_LA::M_Matrix<size_t> N=sto.Multinomial (p,Nchannels);
 //   std::cout<<"p "<<p<<"N "<<N;
//  press_any_key_to_continue();
    return N;
}

/// It does not change the ymean, only the N
Markov_LA::M_Matrix<size_t>& random_P_on_N(const Markov_Transition_step& Qdt,
				Markov_LA::M_Matrix<size_t>& N_run,
				Borrowed::MersenneTwister::MTRand& sto)
{
    //std::cout<<"P "<<Qdt.P<<"N_run"<<N_run;
  if (Qdt.P<0.0)
    std::cerr<<"negative Qdt.P"<<Qdt.P<<"\n";

  N_run=sto.Markov_run(Qdt.P,N_run);
  //  std::cout<<"N_run now "<<N_run;
  //   press_any_key_to_continue();
  return N_run;
}

bool get_states_from_kij_Label (std::string kij,std::size_t& i,std::size_t& j)
{
    if (kij.find("k_")!=0) return false;
    std::size_t pos=kij.find("_to_");
    if (pos==std::string::npos) return false;
    std::string s=kij.substr(2,pos-2);
    if (!Markov_IO::ToValue<std::size_t>(s,i))
	return false;
    s=kij.substr(pos+4);
    if (!Markov_IO::ToValue(s,j))
	return false;
    return true;
}

}
