#ifndef SIMPLEVARIABLE_H
#define SIMPLEVARIABLE_H
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Abstract_Variable_Object.h"
#include "Markov_Object/SimpleVariableValue.h"

namespace Markov_Object {

  template<typename T>
  class SimpleVariable: public Abstract_Variable_Object,public Abstract_Valued_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to SimpleVariable<T>
    virtual SimpleVariable<T> * dynamicCast(Abstract_Object* o)const override;
    virtual const SimpleVariable<T> * dynamicCast(const Abstract_Object* o)const override;


    virtual bool empty()const override
     {
       return Abstract_Variable_Object::empty()&&
           unitId_.empty()&&
           defautValue_==T();

     }

     virtual bool invalid()const override
      {
        return !empty()&&
            (Abstract_Variable_Object::empty()||
             unitId_.empty());

      }



    virtual std::string myUnit()const ;

    virtual std::string ToString()const override;
    virtual bool ToObject(const std::string& multipleLines,std::size_t& pos) override;

    virtual SimpleVariableValue<T>* defaultValue()const override;

    virtual SimpleVariableValue<T>* unKnownValue()const override;


    virtual std::set<std::string> referencedObjects()const;

      virtual bool isValidValue(const Abstract_Value_Object* ob)const;

    virtual bool isCreateable()const;
    virtual SimpleVariable<T>* create()const;

    SimpleVariable( Environment*  e);


    SimpleVariable();

    SimpleVariable(const SimpleVariable<T>& other):
      Abstract_Object(),
      Abstract_Variable_Object(other),
      Abstract_Valued_Object(),
      defautValue_(other.defautValue_),
      unitId_(other.unitId_){}






    SimpleVariable(std::string name,
                   T defaultValue,
                   std::string unit,
                   Environment* E,
                   std::string tip,
                   std::string whatthis);
    ~SimpleVariable();
  private:
    T defautValue_;
    std::string unitId_;

    // Abstract_Object interface
  public:
    virtual std::size_t numFields() const
    {
      return 0;
    }

  };



}



#endif // SIMPLEVARIABLE_H
