#include "Macror_Var/Implement_Refer_Environment.h"
#include "Macror_Var/Environment.h"

namespace Macror_Var {

  Environment *Implement_Refer_Environment::getEnvironment() const
  {
    return E_;
  }

  void Implement_Refer_Environment::setEnvironment(Environment *E)
  {
    E_=E;
  }




}
