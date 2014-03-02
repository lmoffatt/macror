#ifndef ABSTRACT_VARIABLE_OBJECT_H
#define ABSTRACT_VARIABLE_OBJECT_H

#include "Markov_Object/Abstract_Named_Object.h"

namespace Markov_Object {

  class Abstract_Value_Object;

  class Abstract_Variable_Object: public Abstract_Named_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();
    virtual ~Abstract_Variable_Object();
    /// cast an Abstract_Object to Abstract_Variable_Object
    virtual Abstract_Variable_Object * dynamicCast(Abstract_Object* o)const override;
    virtual const Abstract_Variable_Object * dynamicCast(const Abstract_Object* o)const override;


    virtual Abstract_Variable_Object* create() const=0;


    virtual Abstract_Value_Object* defaultValue()const=0;

    virtual Abstract_Value_Object* unKnownValue()const=0;


    virtual bool isValidValue(const Abstract_Value_Object* v)const=0;



    Abstract_Variable_Object(Environment*  e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis)
      : Abstract_Object(),
        Abstract_Named_Object(e,variablename,tip,whatthis)
    {}

    Abstract_Variable_Object(Environment*  e)
      :
        Abstract_Named_Object(e){}

    Abstract_Variable_Object(){}

    Abstract_Variable_Object(const Abstract_Variable_Object& other):
      Abstract_Object(),
      Abstract_Named_Object(other)
    {}


   };

}

#endif // ABSTRACT_VARIABLE_OBJECT_H
