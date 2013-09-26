#include <iostream>

#include "Markov_Plot/abc_plotable.h"

namespace Markov_Plot
{

std::string ABC_Plotable::mySuperClass()const
{
    return ClassName();
}

std::string ABC_Plotable::ClassName()
{
    return "Plottable";
}


}

