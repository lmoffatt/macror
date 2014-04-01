#ifndef ABSTRACT_VARIABLE_OBJECT_H
#define ABSTRACT_VARIABLE_OBJECT_H

#include "Markov_Object/Abstract_Named_Object.h"

namespace Markov_Object {

  class Abstract_Value_Object;

  class Abstract_Variable_Object: public Abstract_Named_Object
  {
  public:

    static std::string ClassName();

    static std::set<std::string> SuperClasses();


    virtual std::set<std::string> mySuperClasses()const override;
    virtual std::string myClass()const override;


    virtual ~Abstract_Variable_Object();


    virtual Abstract_Variable_Object* create() const override=0;


    virtual Abstract_Value_Object* defaultValue()const=0;

    virtual Abstract_Value_Object* unKnownValue()const=0;

    virtual bool isValidValue(const Abstract_Value_Object* v)const=0;


    Abstract_Variable_Object(Environment*  e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis);

    Abstract_Variable_Object(Environment*  e);

    Abstract_Variable_Object(){}

    Abstract_Variable_Object(const Abstract_Variable_Object& other);


   };

}

#endif // ABSTRACT_VARIABLE_OBJECT_H
