#ifndef ABSTRACT_REFERS_ENVIRONMENT_H
#define ABSTRACT_REFERS_ENVIRONMENT_H
#include "Macror_Var/Abstract_Object.h"

namespace Macror_Var {
  class Environment;
  class Abstract_Refers_Environment: public virtual Abstract_Object
  {


    // Abstract_Object interface
  public:

    // reflection statics
    static std::string ClassName()
    {
      return "Abstract_Refers_Environment";
    }

    static std::set<std::string> SuperClasses()
    {
      auto sc=Abstract_Object::SuperClasses();
      sc.insert(ClassName());
      return sc;
    }


    virtual std::set<std::string> mySuperClasses() const override
    {
      return SuperClasses();
    }
    virtual std::string myClass() const override
    {
      return ClassName();
    }


    virtual Abstract_Refers_Environment* create()const override=0 ;

    // new implemented virtual methods
    // Environment
    virtual Environment* getEnvironment() const=0;

    virtual ~Abstract_Refers_Environment(){}

    friend class Environment;
 protected:
    virtual void setEnvironment(Environment *E)=0;



  };

}



#endif // ABSTRACT_REFERS_ENVIRONMENT_H
