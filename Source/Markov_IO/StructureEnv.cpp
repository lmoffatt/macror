#include "Markov_IO/StructureEnv.h"
#include"Markov_IO/Implements_ComplexVar_New.h"
#include "Markov_IO/StructureEnv_templ.h"

namespace Markov_IO_New
{

  void StructureEnv_New::pushVoidType()
  {
    std::string id=Cls<void>::name();
    idTypes_.push_back(id);
    types_[id]=new Implements_Data_Type_New<void>();


  }

  StructureEnv_New::StructureEnv_New(const StructureEnv_New *parent, const std::__cxx11::string &idType):
    StructureEnv_New(parent,parent->idToTyped<StructureEnv_New*>(idType)){}

}
