#include <cmath>
#include <string>
#include "Markov_Object/Measurement.h"
#include "Markov_Object/Environment.h"

namespace Markov_Object {
/*
  template<typename T>
  std::string Measurement<T>::ClassName()
  {
    return "Measurement";
  }
  
  template<typename T>
  Class_info Measurement<T>::classInfo()
  {
    return {ClassName(),SuperClasses(),true,false,true};
  }
  
  template<typename T>
  Class_info Measurement<T>::myClassInfo() const
  {
    return classInfo();
  }
  
  template<typename T>
  std::string Measurement<T>::myClass() const
  {
    return ClassName();
    
  }
  

  

  template<typename T>
  std::string Measurement<T>::ToString() const
  {
    std::string out;
    out=std::to_string(value())+" "+unit();
    return out;
  }




  template<typename T>
  bool Measurement<T>::ToObject(const std::string &text, std::size_t &cursor)
  {
    if (is(text))
      {
        T v=get(text,cursor);
        std::string u=Measurement_Unit::getUnit(text,cursor);
        if(!u.empty())
          {
            value_=v;
            unitId_=u;
            return true;
          }
        return false;
      }
    return false;
  }

  template<typename T>
  T Measurement<T>::value() const
  {
    return value_;
  }

  template<typename T>
  std::string Measurement<T>::unit() const
  {
    return unitId_;

  }

  template<typename T>
  Measurement<T> *Measurement<T>::pow(int n) const
  {
    if (invalid())
      {
        T v=std::pow(value_,n);
        }
  }

  template<typename T>
  Measurement<T> *Measurement<T>::times(const Measurement *other) const
  {
    if (invalid()&&other->invalid())
      {
      }
    else return nullptr;
  }

  template<typename T>
  Measurement<T> *Measurement<T>::over(const Measurement *other) const
  {
    if (invalid()&&other->invalid())
      {
      }
    else return nullptr;
  }



  
  template<typename T>
  Measurement<T>::Measurement(T value, std::string unit):
    Abstract_Object(),
    value_(value),
    unitId_(unit){}


  template<>
  bool Measurement<std::size_t>::is(const std::string &singleLine)
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
  bool Measurement<double>::is(const std::string &singleLine)
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
  std::size_t Measurement<std::size_t>::get(const std::string& singleLine,std::size_t* pos)
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
  bool Measurement<double>::isUnknown()const
  {
    return std::isnan(value_);
  }


  template<>
  bool Measurement<std::size_t>::isUnknown()const
  {
    return value_==std::numeric_limits<std::size_t>::max();
  }

  template<>
  double Measurement<double>::unknownValue()
  {
    return std::numeric_limits<double>::quiet_NaN();
  }



  template<>
  std::size_t Measurement<std::size_t>::unknownValue()
  {
    return std::numeric_limits<std::size_t>::max();
  }




  template<>
  double Measurement<double>::get(const std::string& singleLine,std::size_t* pos)
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




  
  */
  
  
  
  
  
  
  
}
