#include <iostream>
#include "Markov_IO/ABC_Options.h"
#include "Markov_Mol/SimulationOptions.h"
#include "Markov_Bay/MarkovLikelihood.h"


namespace Markov_IO
{
ABC_Options::~ABC_Options(){}

std::string ABC_Options::mySuperClass()const{
    return ClassName();
}

std::string ABC_Options::ClassName()
{
    return "Options";
}




bool  create(ABC_Options*& option,const std::string& childClass)

{
    BaseOptions* o;
    if (create(o,childClass))
    {
       option=o;
       return true;
    }
    else
	return false;

}




bool LoadFromDescription(ABC_Options*& option,
			 const Markov_IO::ClassDescription& classDes)
{
    if (create(option,classDes.ClassName()))
	return option->LoadFromDescription(classDes);
    return false;
}

std::istream& operator>> (std::istream& stream,ABC_Options*& x)
{
    ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!LoadFromDescription(x,classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}

}
