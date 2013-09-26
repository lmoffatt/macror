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

std::string SimulationOptions::myClass()const
{
    return ClassName();
}

std::string SimulationOptions::ClassName()
{
    return "Simulation_Options";
}


std::vector<std::string> SimulationOptions::parentClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_IO::BaseOptions::ClassName());

   return v;

}

std::vector<std::string> SimulationOptions::childClasses()
{
    std::vector<std::string> v;
    return v;
}

 bool SimulationOptions::amIAbstract()const
{
    return false;
}

 std::vector<std::string>  SimulationOptions::myParentClasses()const
{
    return parentClasses();
}
 std::vector<std::string>  SimulationOptions::myChildClasses()const
{
    return childClasses();
}



}
