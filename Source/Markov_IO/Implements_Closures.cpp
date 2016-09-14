#include "Markov_IO/Implements_Closures.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/StructureEnv_templ.h"

namespace Markov_IO_New
{
  namespace _private
  {

    const Type_Union *Implements_Closure_Type_Function::myResultType(const StructureEnv_New *cm) const
    {
      return overloadTypes_->myResultType(cm);
    }

    Implements_Closure_Type_Function::Implements_Closure_Type_Function(const Implements_Closure_Type_Function &other)
      :functionName_(other.functionName_),funIdType_(other.funIdType_->clone()),
        overloadTypes_(other.overloadTypes_->clone()){}

    void Implements_Closure_Type_Function::push_overload(const StructureEnv_New *cm, ABC_Function_Overload *g)
    {
      overloadTypes_->push_Closure(cm,g);
    }


  }



}
