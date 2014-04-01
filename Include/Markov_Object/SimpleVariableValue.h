#ifndef SIMPLEVARIABLEVALUE_H
#define SIMPLEVARIABLEVALUE_H

#include "Markov_Object/Abstract_Value_Object.h"

namespace Markov_Object
{

  template<typename T>
  class SimpleVariable;

  template<typename T>
  class SimpleVariableValue: public Abstract_Value_Object
  {
  public:

    static T get(const std::string &singleLine,std::size_t* pos);
    static bool is(const std::string& singleLine);
    static std::string ClassName();

    static std::set<std::string> SuperClasses();
    static T unknownValue();

    virtual std::string myClass()const override;
    virtual SimpleVariableValue<T> *create() const override;
    virtual std::set<std::string> mySuperClasses()const override;


    virtual std::string myUnit()const ; 

    virtual std::string variable()const override;


    virtual std::string ToString()const override;

    virtual SimpleVariableValue<T> *
    CreateObject(const std::string &text, std::size_t &cursor) const override;

    virtual bool isUnknown()const override;


    virtual T value() const;

    virtual bool empty()const override;


    SimpleVariableValue();
    SimpleVariableValue(std::string variablename,
                        T defaultValue,
                        std::string unit);
    ~SimpleVariableValue();

  protected:
    virtual SimpleVariableValue<T> *
    ToObject(const std::string& multipleLines,std::size_t& pos)override;


  private:
     std::string variableId_;
     std::string unitId_;
     T value_;


  };



}

#endif // SIMPLEVARIABLEVALUE_H
