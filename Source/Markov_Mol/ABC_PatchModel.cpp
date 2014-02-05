#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_Mol/PatchModel.h"

namespace Markov_Mol
{

std::string ABC_PatchModel::mySuperClass()const
{
    return ClassName();
}

std::string ABC_PatchModel::ClassName()
{
    return "Patch_Model";
}


std::vector<std::string> ABC_PatchModel::parentClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_IO::ABC_Parametrizable::ClassName());

   return v;

}

std::vector<std::string> ABC_PatchModel::childClasses()
{
    std::vector<std::string> v;
    v.push_back(Markov_Mol::PatchModel::ClassName());

    return v;
}

 bool ABC_PatchModel::amIAbstract()const
{
    return true;
}

 std::vector<std::string>  ABC_PatchModel::myParentClasses()const
{
    return parentClasses();
}
 std::vector<std::string>  ABC_PatchModel::myChildClasses()const
{
    return childClasses();
}




ABC_PatchModel::~ABC_PatchModel()
{
}


inline bool operator==(const ABC_PatchModel& x,
		       const ABC_PatchModel& y)
{
    if (!(x.Model()==y.Model())) return false;
    if (!((x.AverageNumberOfChannels()==y.AverageNumberOfChannels())))
	return false;
    if (!((x.Noise()==y.Noise()))) return false;
    return true;
}



bool  create(ABC_PatchModel*& model,const std::string& childClass)

{
    if (childClass==PatchModel::ClassName())
   {
       PatchModel* m;
       m=new PatchModel();
       model=m;
       return true;
   }
	return false;

}

bool LoadFromDescription(ABC_PatchModel*& model,
			 const Markov_IO::ClassDescription& classDes)
{
    if (create(model,classDes.ClassName()))
	return model->LoadFromDescription(classDes);
    return false;
}

//bool LoadFromStringDescription(ABC_PatchModel*& model,
//			 const Markov_IO::ClassDescription& classDes)
//{
//    if (create(model,classDes.ClassName()))
//	return model->LoadFromStringDescription(classDes);
//    return false;
//}



std::istream& operator>> (std::istream& stream,ABC_PatchModel*& x)
{
    ClassDescription classDes;
    stream>>classDes;
    if (stream.good())
	if(!LoadFromDescription(x,classDes))
	    stream.setstate(stream.rdstate() | std::ios_base::failbit);
    return stream;
}






}
