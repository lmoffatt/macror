#ifndef VARTEMPL_H
#define VARTEMPL_H
#include "Markov_IO/Var.h"
#include "Markov_IO/buildByToken.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
namespace Markov_IO_New {
  template<typename T>
  bool Implements_Value_New<T>::isOfThisType(const StructureEnv_New* cm,
                                 const std::string& generalType,
                                 std::string* whyNot
                                 ,const std::string &masterObjective)const
  {
    if ((generalType.empty()||myType()==generalType))
      return true;
    else
      {
        auto gTp
            =cm->idToType(generalType,whyNot,masterObjective);
        if (gTp==nullptr)
          return false;
        else
          return gTp->includesThisType(cm,generalType,whyNot,masterObjective);
      }
  }



}

#endif // VARTEMPL_H
