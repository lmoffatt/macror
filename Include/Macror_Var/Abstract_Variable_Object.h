#ifndef ABSTRACT_VARIABLE_OBJECT_H
#define ABSTRACT_VARIABLE_OBJECT_H

#include "Macror_Var/Abstract_Named_Object.h"

namespace Macror_Var {

  class Abstract_Value_Object;

  class Abstract_Variable_Object: public Abstract_Named_Object
  {
  public:

    class Abstract_Data:public Abstract_Refers_Environment
    {
    public:
      static std::string ClassName()
      {
        return "Abstract_Variable_Object::Data";
      }

      static std::set<std::string> SuperClasses();


      virtual std::set<std::string> mySuperClasses()const override
      {
        return SuperClasses();
      }
      virtual std::string myClass()const override
      {
        return ClassName();
      }



      // Abstract_Object interface
    public:
      virtual bool empty() const=0;
      virtual Abstract_Object *create() const=0;
      virtual std::string ToString() const=0;
      virtual Abstract_Object *CreateObject(const std::string &text, std::size_t &cursor) const;

    protected:
      virtual Abstract_Object *ToObject(const std::string &text, std::size_t &cursor);

      // Abstract_Refers_Environment interface
    public:
      virtual Environment *getEnvironment() const;

    protected:
      virtual void setEnvironment(Environment *E);
    };

    static std::string ClassName();

    static std::set<std::string> SuperClasses();


    virtual std::set<std::string> mySuperClasses()const override;
    virtual std::string myClass()const override;


    virtual ~Abstract_Variable_Object();


    virtual Abstract_Variable_Object* create() const override=0;


    virtual Abstract_Variable_Object* defaultValue()const=0;

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
