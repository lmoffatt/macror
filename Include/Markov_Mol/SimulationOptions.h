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
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;


};


}




#endif // SIMULATIONOPTIONS_H

