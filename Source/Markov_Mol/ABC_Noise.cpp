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



#include "Markov_Mol/ABC_Noise.h"
#include "Markov_Mol/GaussianNoise.h"


namespace Markov_Mol
{
ABC_noise::~ABC_noise()
{}

std::string ABC_noise::mySuperClass()const
{
    return ClassName();
}

std::string ABC_noise::ClassName()
{
    return "Noise";
}








bool  create(ABC_noise*& model,const std::string& childClass)

{
    if (childClass==gaussian_noise::ClassName())
   {
       gaussian_noise* m;
       m=new gaussian_noise();
       model=m;
       return true;
   }
        return false;

}


bool LoadFromDescription(ABC_noise*& a,
                         const Markov_IO::ClassDescription& classDes)
{
    if (create(a,classDes.ClassName()))
        return a->LoadFromDescription(classDes);
    return false;
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



std::istream& operator>> (std::istream& stream,ABC_noise*& x)
{
    ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
        if(!LoadFromDescription(x,classDes))
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}

}

