#ifndef SIMULATIONOPTIONS_H
#define SIMULATIONOPTIONS_H
#include "Markov_IO/Options.h"

namespace Markov_Mol
{

class SimulationOptions:public Markov_IO::BaseOptions
{
public:
    virtual SimulationOptions* create() const;

    SimulationOptions();
    SimulationOptions(const std::string& myname,
		      const std::size_t numSteps,
		      double timestep);

    virtual std::string myClass()const;
    static std::string ClassName();


};


}




#endif // SIMULATIONOPTIONS_H

