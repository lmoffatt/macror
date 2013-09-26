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


std::vector<std::string> ABC_Distribution::parentClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_Bay::ABC_ParametricDistributable::ClassName());

   return v;

}

std::vector<std::string> ABC_Distribution::childClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_Bay::NormalDistributed::ClassName());

    return v;
}

 bool ABC_Distribution::amIAbstract()const
{
    return true;
}

 std::vector<std::string>  ABC_Distribution::myParentClasses()const
{
    return parentClasses();
}
 std::vector<std::string>  ABC_Distribution::myChildClasses()const
{
    return childClasses();
}


ABC_Distribution::~ABC_Distribution()
{}

std::vector<std::string> GetChilds(const ABC_Distribution* d)
{
    std::vector<std::string> v;
    v.push_back(Markov_Mol::PatchModelNormalDistribution::ClassName());
    return v;
 }


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



