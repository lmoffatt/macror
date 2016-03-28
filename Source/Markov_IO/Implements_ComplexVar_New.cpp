#include "Markov_IO/Implements_ComplexVar_New.h"

namespace Markov_IO_New {

//  bool Implements_Data_Type_New<std::map<std::string, ABC_Var_New *> >::get(std::map<std::string, ABC_Var_New *> &v, ABC_Input *istream, const Implements_ComplexVar_New *cm, std::string *whyNot, const std::string &masterObjective) const
//  {
//    char c;
//    const Implements_Data_Type_New<ABC_Var_New*>* etype=this->getElementDataType(cm);
//    if (etype==nullptr)
//      return false;
//    while (!istream->nextCharIs('\n',c)){}
//    if (!istream->nextCharIs('{',c))
//      {
//        *whyNot= masterObjective+": expected { found"+c;
//        return false;
//      }
//    else
//      {
//        while (!istream->nextCharIs('}'))
//          {
//            ABC_Var_New* d;
//            if (etype->get(d,istream,cm,whyNot,masterObjective))
//              {
//                v.insert({d->id(),d});
//              }
//            else
//              return false;
//          }
//        if (isVarInDomain(cm,v,whyNot,masterObjective))
//          return true;
//        else
//          return false;
//      }

//  }

  buildByToken<std::__cxx11::string> *Implements_String_Data_Type_New::getBuildByToken(const Implements_ComplexVar_New *cm) const
  {
    return new buildByToken<std::string>(cm,this);
  }





}
