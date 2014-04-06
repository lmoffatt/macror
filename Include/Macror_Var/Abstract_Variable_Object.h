#ifndef ABSTRACT_VARIABLE_OBJECT_H
#define ABSTRACT_VARIABLE_OBJECT_H

#include "Macror_Var/Implement_Named_Object.h"
#include "Macror_Var/Implement_Refer_Environment.h"

namespace Macror_Var {

  class Abstract_Variable_Object: public virtual Abstract_Named_Object
  {
  public:

    class Abstract_Data:public virtual Abstract_Refers_Environment
    {
    public:
      static std::string ClassName()
      {
        return "Abstract_Variable_Object::Data";
      }

      static std::set<std::string> SuperClasses()
      {
        auto out=Abstract_Refers_Environment::SuperClasses();
        out.insert(ClassName());
        return out;
      }


      virtual std::set<std::string> mySuperClasses()const override
      {
        return SuperClasses();
      }

      virtual std::string myClass()const override
      {
        return ClassName();
      }

      // Abstract_Object interface
      virtual Abstract_Data *create() const override=0;
      virtual Abstract_Data *CreateObject(const std::string &text,
                                          std::size_t &cursor) const override=0;

      virtual ~Abstract_Data(){}


      virtual std::string ToString()const
      {
        std::string out=variableName()+" : ";
        auto d=printData();
        if (d.find_first_of("\n\r")!=d.npos)
          out+="\n";
        return out+d;
      }


      // new methods


      virtual  Abstract_Data *CreateUnknown()const =0;

      virtual std::string variableName()const=0;

      virtual std::string printData()const=0;

      virtual bool readPrintData(const std::string& printedData)=0;




    protected:
      virtual Abstract_Data *ToObject(const std::string &text, std::size_t &cursor)override=0;

    };

    static std::string ClassName()
    {
      return "Abstract_Variable_Object";
    }

    static std::set<std::string> SuperClasses()
    {
      auto out =Abstract_Named_Object::SuperClasses();
      out.insert(ClassName());
      return out;
    }


    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }
    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual ~Abstract_Variable_Object(){}


    virtual Abstract_Variable_Object* create() const override=0;
    virtual Abstract_Variable_Object *CreateObject(const std::string &text,
                                                   std::size_t &cursor)const override=0;


    virtual Abstract_Data* emptyValue()const=0;

    virtual Abstract_Data* defaultValue()const=0;

    virtual Abstract_Data* unKnownValue()const=0;

    virtual bool isValidValue(const Abstract_Data* v)const=0;

   };

}

#endif // ABSTRACT_VARIABLE_OBJECT_H
