#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/QMarkovModel.h"


namespace Markov_Mol_New
{

std::string num_channels_label()
{
    return "Number_of_channels";
}



std::string ABC_Markov_Model::ClassName()
{
    return "Channel_Model";
}






inline bool operator==(const ABC_Markov_Model& x,
                       const ABC_Markov_Model& y)
{
    if (!(x.k()==y.k())) return false;
    if (!((x.Q0()==y.Q0()))) return false;
    if (!((x.Q1()==y.Q1()))) return false;
    if (!(x.g()==y.g())) return false;
    return true;
}




}



