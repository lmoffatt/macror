#include "Markov_IO/Implements_Closures.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/StructureEnv_templ.h"
#include "Markov_IO/buildClosureByToken_Templ.h"

namespace Markov_IO_New
{
  namespace _private
  {

    const Type_Union<typename Implements_Closure_Type_Function::myType_of_Value> *Implements_Closure_Type_Function::myResultType(const StructureEnv_New *cm) const
    {
      return overloadTypes_->myResultType(cm);
    }

    Implements_Closure_Type_Function::Implements_Closure_Type_Function():
      functionName_("")
    ,funIdType_(Identifier::types::idFunct::varType("")),
      overloadTypes_(nullptr)
    {}

    Implements_Closure_Type_Function::Implements_Closure_Type_Function(const std::__cxx11::string functionName, Implements_Identifier *idType)
      : functionName_(functionName)
      ,funIdType_(idType)
      ,overloadTypes_(nullptr)
    {

    }

    Implements_Closure_Type_Function::Implements_Closure_Type_Function(const Implements_Closure_Type_Function &other)
      :functionName_(other.functionName_),funIdType_(other.funIdType_->clone()),
        overloadTypes_(other.overloadTypes_?other.overloadTypes_->clone():nullptr){}

    void Implements_Closure_Type_Function::push_overload(const StructureEnv_New *cm, ABC_Function_Overload *g)
    {

      if (overloadTypes_==nullptr)
        overloadTypes_.reset(new ClosureType_Union<ABC_Function_Overload>);
      g->setFunction(this);
      overloadTypes_->push_Closure(cm,g);
    }

    Implements_Data_Type_New_Implements_Var_Closure::Implements_Data_Type_New_Implements_Var_Closure(const std::__cxx11::string &id, Implements_Data_Type_New_Implements_Var_Closure::selfType * const typeType, Implements_Identifier *idType, Implements_Data_Type_New_Implements_Var_Closure::clType *clType, Implements_Data_Type_New_Implements_Var_Closure::typePredicate comply, Implements_Data_Type_New_Implements_Var_Closure::elemType getElement, Implements_Data_Type_New_Implements_Var_Closure::keyType getKey):

      typeId_(id),
      typeType_(typeType),
      idType_(idType),
      clType_(clType),
      comply_(comply),
      getElement_(getElement),
      getKey_(getKey){}


  }



}
