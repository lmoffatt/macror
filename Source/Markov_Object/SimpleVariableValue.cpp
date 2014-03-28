#include <cmath>


#include "Markov_Object/SimpleVariableValue.h"
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/SimpleVariable.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/Environment.h"



namespace Markov_Object {




  template<typename T>
  std::string SimpleVariableValue<T>::variable()const
  {
    return variableId_;
  }








  template<typename T>
  std::set<std::string> SimpleVariableValue<T>:: SuperClasses()
  {
    //Variable_Object,public Valued_Object,public Named_Object
    auto vo=Abstract_Value_Object::SuperClasses();
    vo.insert(ClassName());
    return vo;

  }





  template<typename T>
  std::set<std::string> SimpleVariableValue<T>::mySuperClasses() const
  {
    return SuperClasses();
  }






  template<typename T>
  SimpleVariableValue<T> *SimpleVariableValue<T>::create() const
  {
    return new SimpleVariableValue<T>;
  }




  template<typename T>
  std::string SimpleVariableValue<T>::myClass()const
  {
    return ClassName();
  }

  template<>
  std::string SimpleVariableValue<std::size_t>::ClassName()
  {
    return "count_value";
  }

  template<>
  std::string SimpleVariableValue<double>::ClassName()
  {
    return "real_value";
  }



  template<typename T>
  std::string SimpleVariableValue<T>::myUnit()const
  {
    return unitId_;
  }



  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue(std::string variablename,
                                              T v,
                                              std::string unit)
    : Abstract_Object(),
      variableId_(variablename),
      unitId_(unit),
      value_(v)
  {
  }


  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue()
    : variableId_(),
      unitId_(),
      value_()
  {  }



  template<typename T>
  SimpleVariableValue<T>::~SimpleVariableValue(){}

  template<>
  bool SimpleVariableValue<std::size_t>::is(const std::string &singleLine)
  {
    std::size_t firstNotNumber=singleLine.find_first_not_of(" 0123456789\t");
    std::size_t firstNumber=singleLine.find_first_of("0123456789");
    if (firstNotNumber<firstNumber)
      return false;
    std::size_t lastnumber=singleLine.find_last_of("0123456789");
    std::size_t firstNumberInterr=singleLine.find_first_not_of("0123456789",firstNumber);
    if (firstNumberInterr==std::string::npos)
      return true;
    if (lastnumber!=firstNumberInterr-1)
      return false;
    return true;
  }

  template<>
  bool SimpleVariableValue<double>::is(const std::string &singleLine)
  {
    try
    {
      std::stod(singleLine);
    }
    catch (...)
    {
      return false;
    }
    return true;
  }

  template<>
  std::size_t SimpleVariableValue<std::size_t>::get(const std::string& singleLine,std::size_t* pos)
  {
    std::size_t out;
    try
    {
      out=std::stoul(singleLine,pos);
    }
    catch (...)
    {
      return 0;
    }
    return out;
  }


  template<>
  bool SimpleVariableValue<double>::isUnknown()const
  {
    return std::isnan(value_);
  }


  template<>
  bool SimpleVariableValue<std::size_t>::isUnknown()const
  {
    return value_==std::numeric_limits<std::size_t>::max();
  }

  template<>
  double SimpleVariableValue<double>::unknownValue()
  {
    return std::numeric_limits<double>::quiet_NaN();
  }



  template<>
  std::size_t SimpleVariableValue<std::size_t>::unknownValue()
  {
    return std::numeric_limits<std::size_t>::max();
  }



  template<>
  double SimpleVariableValue<double>::get(const std::string& singleLine,std::size_t* pos)
  {
    double out;
    try
    {
      out=std::stod(singleLine,pos);
    }
    catch (...)
    {
      return 0;
    }
    return out;
  }





  template<typename T>
  T SimpleVariableValue<T>::value()const{
    return value_;
  }

  template<typename T>
  std::string SimpleVariableValue<T>::ToString()const
  {
    if (variableId_.empty()&&unitId_.empty())
      return "";
    std::string out=variableId_+"\n";
    out+=std::to_string(value());
    out+=unitId_+"\n";
    return out;
  }


  template<typename T>
  SimpleVariableValue<T> *SimpleVariableValue<T>::
  ToObject(const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    variableId_=IdentifierName::get(multipleLines,pos);
    ++pos;
    std::string line=Abstract_Named_Object::nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return nullptr;
      }
    std::size_t posline=0;
    value_=SimpleVariableValue<T>::get(line,&posline);
    unitId_=IdentifierName::get(line.substr(posline));
    return this;
  }


  template
  class SimpleVariableValue<std::size_t>;

  template
  class SimpleVariableValue<double>;



}
