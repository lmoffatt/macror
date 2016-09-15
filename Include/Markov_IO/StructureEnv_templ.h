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


  template<typename R>
  const Implements_Closure_Type<R,void *> *StructureEnv_New::idTo_R_Func(const std::__cxx11::string &name,const std::string &typeName,std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
{
    const std::string objective=masterObjective+": "+name+" is not a type";
    auto it=R_funcs_.find(typeName);
    if (it!=R_funcs_.end())
      {
        auto it2= it->second.find(name);
        if (it2!=it->second.end())
          return dynamic_cast<const Implements_Closure_Type<R,void *> *>(it2->second);
        else
          {
            if (whyNot!=nullptr)
              *whyNot=objective;
            return nullptr;
          }
      }
    else
      {
        if (whyNot!=nullptr)
          *whyNot=objective;
        return nullptr;
      }

  }





}
#endif // STRUCTUREENV_TEMPL_H
