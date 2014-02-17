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

    virtual SimpleVariableValue<T> *create() const;

    virtual bool isInternallyValid() const;



    virtual bool refersToValidObjects() const override;
    virtual std::set<std::string> referencedObjects() const;
    static T get(const std::string &singleLine,std::size_t* pos);
    static bool is(const std::string& singleLine);

    virtual std::string myClass()const override;

    static std::string ClassName();
    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to SimpleVariableValue<T>
    virtual SimpleVariableValue<T> * dynamicCast(Abstract_Object* o)const override;
    virtual const SimpleVariableValue<T> * dynamicCast(const Abstract_Object* o)const override;


    virtual const Measurement_Unit* myUnit()const override;

    virtual const SimpleVariable<T>* variable()const override;

    virtual T value() const;

    virtual std::string ToString()const override;
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos)override;


    static T unknownValue();

    virtual bool isUnknown()const override;


    SimpleVariableValue();
    SimpleVariableValue(std::string variablename,
                        T defaultValue,
                        std::string unit,
                        Environment *e);
    ~SimpleVariableValue();

  private:
    std::string variableId_;
     std::string unitId_;
     T value_;

  };



}

#endif // SIMPLEVARIABLEVALUE_H
