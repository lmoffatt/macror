#include "Markov_Mol/SimulationOptions.h"

namespace Markov_Mol{


SimulationOptions::SimulationOptions():
    BaseOptions("default")
{
    push_back("num_steps",std::size_t(10));
    push_back("time_step",1e-5);

}
SimulationOptions::SimulationOptions(const std::string& myname,
				     const std::size_t numSteps,
				     double timestep):
    BaseOptions(myname)
{
    push_back("num_steps",numSteps);
    push_back("time_step",timestep);

}


SimulationOptions* SimulationOptions::create()const
{
  return new SimulationOptions();
}

std::string SimulationOptions::myClass()const
{
    return ClassName();
}

std::string SimulationOptions::ClassName()
{
    return "Simulation_Options";
}




}
