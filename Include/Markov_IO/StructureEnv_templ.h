#ifndef STRUCTUREENV_TEMPL_H
#define STRUCTUREENV_TEMPL_H
#include "Markov_IO/StructureEnv.h"
#include "Markov_IO/Implements_Closures.h"
namespace Markov_IO_New
{

  template <typename T>
  void StructureEnv_New::pushType(const std::string& id
                ,Implements_Data_Type_New<T>* var
                , std::string tip
                , std::string whatthis)
  {
    idTypes_.push_back(id);
    types_[id]=var;
    idTipWt_[id]={tip,whatthis};
    typeC_[id]=new Implements_Closure_Type<T>(var);

  }


}
#endif // STRUCTUREENV_TEMPL_H
