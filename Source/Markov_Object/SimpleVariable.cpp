
#include "Markov_Object/SimpleVariable.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/Environment.h"

namespace Markov_Object {
  template<typename T>
  std::string SimpleVariable<T>::myClass()const{
    return ClassName();
  }



  template<>
  std::string SimpleVariable<double>::ClassName(){
    return "double";

  }

  template<>
  std::string SimpleVariable<std::size_t>::ClassName(){
    return "count";

  }


  template<typename T>
  Class_info SimpleVariable<T>::classInfo()
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
  Class_info SimpleVariable<T>::myClassInfo() const
  {
    return classInfo();
  }

  template<typename T>
  std::set<std::string> SimpleVariable<T>:: SuperClasses()
  {
    //Variable_Object,public Valued_Object,public Named_Object
    auto vo=Abstract_Variable_Object::SuperClasses();

    auto va=Abstract_Valued_Object::SuperClasses();
    vo.insert(va.begin(),va.end());


    vo.insert(ClassName());
    return vo;

  }

  template<typename T>
  SimpleVariable<T> *SimpleVariable<T>::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast< SimpleVariable<T> *>(o);
  }

  template<typename T>
  const SimpleVariable<T> *SimpleVariable<T>::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast< const SimpleVariable<T> *>(o);
  }


  template<typename T>
   std::string SimpleVariable<T>::myUnit()const{
     return unitId_;
  }


  template<typename T>
  SimpleVariable<T>::SimpleVariable(std::string name,
                                    T defaultValue,
                                    std::string unit,
                                    Environment*  E,
                                    std::string tip,
                                    std::string whatthis)
    :
      Abstract_Object(),
      Abstract_Variable_Object(E,name,tip,whatthis),
      defautValue_(defaultValue),
      unitId_(unit)
   {

  }

  template<typename T>
  SimpleVariable<T>::SimpleVariable(Environment*  e)
    :
      Abstract_Object(),
      Abstract_Variable_Object(e),
      defautValue_{T()},
      unitId_{}
  {}

  template<typename T>
  SimpleVariable<T>::SimpleVariable()
    :
      Abstract_Object(),
      Abstract_Variable_Object(),
      defautValue_{T()},
      unitId_{}
  {}


  template<typename T>
  SimpleVariableValue<T>* SimpleVariable<T>::defaultValue() const
  {
    return new SimpleVariableValue<T>(idName(),
                                      defautValue_,
                                      unitId_);
  }

  template<typename T>
  SimpleVariableValue<T> *SimpleVariable<T>::unKnownValue() const
  {
    return new SimpleVariableValue<T>(idName(),
                                      SimpleVariableValue<T>::unknownValue(),
                                      myUnit());

  }

  template<typename T>
  std::set<std::string> SimpleVariable<T>::referencedObjects() const
  {
    return {unitId_};
  }

  template<typename T>
  bool SimpleVariable<T>::isValidValue(const Abstract_Value_Object *ob) const
  {
    return ob->variable()==idName();
  }



  template<typename T>
  std::string SimpleVariable<T>::ToString()const
  {
    std::string out=Abstract_Named_Object::ToString();
    if (out.empty()&&unitId_.empty())
      return "";
    out+=std::to_string(defautValue_);
    out+=unitId_+"\n";
    return out;
  }

  template<typename T>
  SimpleVariable<T> *SimpleVariable<T>::
  ToObject(const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    if (Abstract_Named_Object::ToObject(multipleLines,pos)==nullptr)
      {
        pos=pos0;
        return nullptr;
      }
    std::string line=nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return nullptr;
      }
     std::size_t posline=0;
    defautValue_=SimpleVariableValue<T>::get(line,&posline);
    unitId_=Measurement_Unit::getUnit(line.substr(posline));

    return this;
  }







  template<typename T>
  bool SimpleVariable<T>::isCreateable()const
  {
    return true;
  }

  template<typename T>
  SimpleVariable<T>* SimpleVariable<T>::create()const
  {
    return new SimpleVariable<T>;
  }


  template<typename T>
  SimpleVariable<T>::~SimpleVariable(){}



  template
  class SimpleVariable<std::size_t>;

  template
  class SimpleVariable<double>;




}
