#include <cmath>


#include "Markov_Object/SimpleVariableValue.h"
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/SimpleVariable.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/Environment.h"



namespace Markov_Object {




  template<typename T>
  const SimpleVariable<T>* SimpleVariableValue<T>::variable()const
  {

    if (getEnvironment()!=nullptr)
      return dynamic_cast<const SimpleVariable<T>*>(getEnvironment()->V(variableId_));
    else
      return nullptr;
  }








  template<typename T>
  std::set<std::string> SimpleVariableValue<T>:: SuperClasses()
  {
    //Variable_Object,public Valued_Object,public Named_Object
    auto vo=Abstract_Value_Object::SuperClasses();

    auto va=Abstract_Valued_Object::SuperClasses();
    vo.insert(va.begin(),va.end());


    vo.insert(ClassName());
    return vo;

  }



  template<typename T>
  Class_info SimpleVariableValue<T>::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        true,
        false,
        false
      };

  }
  template<typename T>
  Class_info SimpleVariableValue<T>::myClassInfo() const
  {
    return classInfo();
  }


  template<typename T>
  SimpleVariableValue<T> *SimpleVariableValue<T>::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<  SimpleVariableValue<T> *> (o);
  }

  template<typename T>
  const SimpleVariableValue<T> *SimpleVariableValue<T>::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<  const SimpleVariableValue<T> *> (o);
  }




  template<typename T>
  SimpleVariableValue<T> *SimpleVariableValue<T>::create() const
  {
    return new SimpleVariableValue<T>;
  }

  template<typename T>
  bool SimpleVariableValue<T>::isInternallyValid() const
  {
    bool validVariableId=!variableId_.empty()&&
        (variableId_==Abstract_Named_Object::getName(variableId_));
    bool validUnit=!unitId_.empty()&&(unitId_==Measurement_Unit::getUnit(unitId_));
    return validUnit&&validVariableId;
  }

  template<typename T>
  bool SimpleVariableValue<T>::refersToValidObjects() const
  {
    bool validUnit=myUnit()!=nullptr;
    bool validVar=variable()!=nullptr;
    return validUnit&& validVar;
  }

  template<typename T>
  std::set<std::string> SimpleVariableValue<T>::referencedObjects() const
  {
    std::set<std::string> s;
    s.insert(unitId_);
    s.insert(variableId_);
    return s;
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
  const Measurement_Unit* SimpleVariableValue<T>::myUnit()const
  {
    if (getEnvironment()!=nullptr)
      return getEnvironment()->U(unitId_);
    else
      return nullptr;
  }



  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue(std::string variablename,
                                              T v,
                                              std::string unit,
                                              Environment *e)
    : Abstract_Object(e),
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
  bool SimpleVariableValue<T>::ToObject(Environment* e,const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    variableId_=Abstract_Named_Object::getName(multipleLines,pos);
    const Abstract_Named_Object* p=e->V(variableId_);
    if (p!=nullptr)
      {
        if (dynamic_cast<const SimpleVariable<T>*>(p)==nullptr)
          {
            pos=pos0;
            return false;
          }
      }
    ++pos;
    std::string line=Abstract_Named_Object::nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return false;
      }
    std::size_t posline=0;
    value_=SimpleVariableValue<T>::get(line,&posline);
    unitId_=Measurement_Unit::getUnit(line.substr(posline));
    if (this->isInternallyValid())
      {
        setEnvironment(e);
        return true;
      }
    else
      return false;

  }


  template
  class SimpleVariableValue<std::size_t>;

  template
  class SimpleVariableValue<double>;



}
