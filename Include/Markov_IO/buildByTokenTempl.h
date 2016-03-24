#ifndef BUILDBYTOKENTEMPL_H
#define BUILDBYTOKENTEMPL_H


#include "Markov_IO/buildByToken.h"
#include "Markov_IO/Implements_ComplexVar_New.h"



namespace Markov_IO_New {

  template<typename T>
    bool buildByToken<T>::pushToken(Token_New t, std::string *whyNot, const std::string &masterObjective)
  {
    const std::string objective=masterObjective+": "+"Token "+t.str()+" was not accepted by "+ClassName();
    T d;
    if (!t.toValue(d, whyNot,objective))
      {
        return false;
      }
    else if (varType_->isVarInDomain(this->parent(),d,whyNot,objective))
      {
        x_=d;
        isComplete_=true;
        return true;
      }
    else
      return false;
  }






}
#endif // BUILDBYTOKENTEMPL_H
