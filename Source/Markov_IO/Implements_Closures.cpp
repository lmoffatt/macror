#include "Markov_IO/Implements_Closures.h"
#include "Markov_IO/Implements_ComplexVar_New.h"

namespace Markov_IO_New
{
  namespace _private
  {

  std::vector<std::unique_ptr<ABC_BuildClosure> > Implements_Closure_Type_Function::getOverloadBuild(const StructureEnv_New *cm, const ABC_Type_of_Value *vt) const
  {
    std::vector<std::unique_ptr<ABC_BuildClosure>> out;
    for (auto& t:getOverloads(cm))
      {
        if (vt==nullptr|| t->myResultType(cm)->isOfThisType(cm,vt->typeId()) )
          out.emplace_back(t->getBuildClosureByToken(cm));
      }
    return out;
  }

  }



}
