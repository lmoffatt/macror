#include "Markov_Mol/ABC_Noise.h"
#include "Markov_Mol/GaussianNoise.h"


namespace Markov_Mol_New
{
ABC_noise::~ABC_noise()
{}


std::string ABC_noise::ClassName()
{
    return "Noise";
}








/*
bool LoadFromStringDescription(ABC_noise*& a,
                         const Markov_IO::ClassDescription& classDes)
{
    if (create(a,classDes.ClassName()))
        return a->LoadFromStringDescription(classDes);
    return false;
}
*/

bool operator==(const ABC_noise& x,const ABC_noise& y)
{
    return x.std(1.0)==y.std(1.0);
};




}



