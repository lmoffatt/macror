#include "Markov_Mol/ABC_PatchModel.h"
#include "Markov_Mol/PatchModel.h"

namespace Markov_Mol_New
{


std::string ABC_PatchModel::ClassName()
{
    return "Patch_Model";
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





}

