#ifndef IMPLEMENT_REFER_ENVIRONMENT_H
#define IMPLEMENT_REFER_ENVIRONMENT_H

#include "Macror_Var/Abstract_Refers_Environment.h"

namespace Macror_Var {

  class Environment;
  class Implement_Refer_Environment: public virtual Abstract_Refers_Environment
  {
    // Abstract_Refers_Environment interface
  public:
    virtual Environment *getEnvironment() const override;
    Implement_Refer_Environment(Environment* E):
      E_(E){}
    Implement_Refer_Environment():
      E_(nullptr){}
    virtual ~Implement_Refer_Environment(){}
  protected:
    virtual void setEnvironment(Environment *E)override;

  private:
    Environment* E_;
  };

}

#endif // IMPLEMENT_REFER_ENVIRONMENT_H
