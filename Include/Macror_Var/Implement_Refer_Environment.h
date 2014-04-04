#ifndef IMPLEMENT_REFER_ENVIRONMENT_H
#define IMPLEMENT_REFER_ENVIRONMENT_H

#include "Macror_Var/Abstract_Refers_Environment.h"
#include "Macror_Var/Environment.h"

namespace Macror_Var {

  class Implement_Refer_Environment: public Abstract_Refers_Environment
  {


    // Abstract_Refers_Environment interface
  public:
    virtual Environment *getEnvironment() const
    {
      return E;
    }
    Implement_Refer_Environment(Environment* E):
      E_(E){}
    Implement_Refer_Environment():
      E_(nullptr){}
    virtual ~Implement_Refer_Environment(){}
  protected:
    virtual void setEnvironment(Environment *E)
    {
      E_=E;
    }

  private:
    Environment* E_;
  };

}

#endif // IMPLEMENT_REFER_ENVIRONMENT_H
