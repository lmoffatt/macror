#include "Markov_Bay/ABC_Distribution.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"


namespace Markov_Bay
{

std::string ABC_Distribution::mySuperClass()const
{
    return ClassName();
}

std::string ABC_Distribution::ClassName()
{
    return "Distribution";
}



ABC_Distribution::~ABC_Distribution()
{}



bool  create(ABC_Distribution*& distribution,const std::string& childClass)

{
    if (childClass==Markov_Mol::PatchModelNormalDistribution::ClassName())
   {
       Markov_Mol::PatchModelNormalDistribution* d;
       d=new Markov_Mol::PatchModelNormalDistribution();
       distribution=d;
       return true;
   }
   else
	return false;

}


bool LoadFromDescription(ABC_Distribution*& a,
			 const Markov_IO::ClassDescription& classDes)
{
    if (create(a,classDes.ClassName()))
	return a->LoadFromDescription(classDes);
    return false;
}




std::istream& operator>> (std::istream& stream,ABC_Distribution*& x)
{
    Markov_IO::ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!LoadFromDescription(x,classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}

}



