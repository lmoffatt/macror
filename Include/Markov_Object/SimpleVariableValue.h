#ifndef SIMPLEVARIABLEVALUE_H
#define SIMPLEVARIABLEVALUE_H

#include "Markov_Object/Abstract_Value_Object.h"

namespace Markov_Object {

  template<typename T>
  class SimpleVariable;

  template<typename T>
  class SimpleVariableValue: public Abstract_Value_Object,public Abstract_Valued_Object
  {
  public:

    static T get(const std::string &singleLine,std::size_t* pos);
    static bool is(const std::string& singleLine);
    static std::string ClassName();
    static Class_info classInfo();
    static std::set<std::string> SuperClasses();
    static T unknownValue();

    virtual std::string myClass()const override;
    virtual SimpleVariableValue<T> *create() const override;
    virtual bool isValid() const override;
    virtual Class_info myClassInfo()const override;

    /// cast an Abstract_Object to SimpleVariableValue<T>
    virtual SimpleVariableValue<T> * dynamicCast(Abstract_Object* o)const override;
    virtual const SimpleVariableValue<T> * dynamicCast(const Abstract_Object* o)const override;
    virtual std::string myUnit()const override;

    virtual std::string variable()const override;


    virtual std::string ToString()const override;
    virtual bool ToObject(const std::string& multipleLines,std::size_t& pos)override;
    virtual bool isUnknown()const override;


    virtual T value() const;

    
    
    
    
    SimpleVariableValue();
    SimpleVariableValue(std::string variablename,
                        T defaultValue,
                        std::string unit);
    ~SimpleVariableValue();

  private:
    std::string variableId_;
     std::string unitId_;
     T value_;

  };



}

#endif // SIMPLEVARIABLEVALUE_H
