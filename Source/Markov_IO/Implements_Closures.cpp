#include "Markov_IO/Implements_Closures.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/StructureEnv_templ.h"

namespace Markov_IO_New
{
  namespace _private
  {

    std::vector<std::unique_ptr<ABC_BuildClosure> > Implements_Closure_Type_Function::getOverloadBuild
    (const StructureEnv_New *cm, const ABC_Type_of_Value *vt) const
    {
      std::vector<std::unique_ptr<ABC_BuildClosure>> out;
      if (vt==nullptr)
        {
          for (auto& t:getOverloads(cm))
            {
                out.emplace_back(t->getBuildClosureByToken(cm));
            }
        }
      else
        {
          for (auto& t:getOverloads(cm))
            {
              if (t->myResultType(cm)->isOfThisType(cm,vt->typeId()) )
                out.emplace_back(t->getBuildClosureByToken(cm));
            }
        }
      return out;
    }

  }



}
