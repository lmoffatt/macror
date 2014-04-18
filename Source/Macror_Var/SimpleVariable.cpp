#include <cmath>

#include "Macror_Var/SimpleVariable.h"
#include "Macror_Var/Measurement_Unit.h"
#include "Macror_Var/Environment.h"
#include "Macror_Var/IdentifierName.h"

namespace Macror_Var {
  template<typename T>
  std::string SimpleVariable<T>::myClass()const{
    return ClassName();
  }



  template<>
  std::string SimpleVariable<double>::ClassName(){
    return "DoubleVariable";

  }

  template<>
  std::string SimpleVariable<std::size_t>::ClassName(){
    return "CountVariable";

  }



  template<typename T>
  std::set<std::string> SimpleVariable<T>::mySuperClasses() const
  {
    return SuperClasses();
  }

  template<typename T>
  std::set<std::string> SimpleVariable<T>:: SuperClasses()
  {
    //Variable_Object,public Valued_Object,public Named_Object
    auto vo=Abstract_Variable_Object::SuperClasses();
    vo.insert(ClassName());
    return vo;

  }

  template<typename T>
  bool SimpleVariable<T>::empty() const
  {
    return (getEnvironment()==nullptr)&&
        (idName().empty())&&
        (defautValue_==T())&&
        (quantityId_.empty());

  }



  template<typename T>
  std::string SimpleVariable<T>::myQuantity()const{
    return quantityId_;
  }


  template<typename T>
  SimpleVariable<T>::SimpleVariable(std::string name,
                                    T defaultValue,
                                    std::string unit,
                                    Environment*  E,
                                    std::string tip,
                                    std::string whatthis):
    Implement_Named_Object(name,tip,whatthis),
    Implement_Refer_Environment(E),
    defautValue_(defaultValue),
    quantityId_(unit)
  {

  }



  template<typename T>
  SimpleVariable<T>::SimpleVariable()
    :
      Abstract_Variable_Object(),
      defautValue_{T()},
      quantityId_{}
  {}


  template<typename T>
  typename SimpleVariable<T>::Data *SimpleVariable<T>::defaultValue() const
  {
    return new Data(getEnvironment(),
                    idName(),
                    defautValue_);
  }

  template<typename T>
  typename SimpleVariable<T>::Data *SimpleVariable<T>::unKnownValue() const
  {
    return new Data(getEnvironment(),
                    idName(),
                    Data::unknown());

  }


  template<typename T>
  std::set<std::string> SimpleVariable<T>::referencedObjects() const
  {
    return {quantityId_};
  }

  template<typename T>
  bool SimpleVariable<T>::isValidValue(const Abstract_Variable_Object::Abstract_Data *ob) const
  {
    return ob->variableName()==idName();
  }



  template<typename T>
  std::string SimpleVariable<T>::ToString()const
  {
    std::string out=Implement_Named_Object::ToString();
    if (out.empty()&&quantityId_.empty())
      return "";
    out+=getEnvironment()->ToString(defautValue_);
    out+=quantityId_+"\n";
    return out;
  }

  template<typename T>
  std::deque<Token> SimpleVariable<T>::BodyTokens() const
  {
    return std::deque<Token> ({
                                {"DefaultValue"},{":"},{defautValue_},{"\n"},
                                {"Quantity"},{":"},{quantityId_},{"\n"}
                              });

  }



  template<typename T>
  SimpleVariable<T> *SimpleVariable<T>::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }

  template<typename T>
  typename SimpleVariable<T>::Data *
  SimpleVariable<T>::emptyValue() const
  {
    return new Data;
  }

  template<typename T>
  SimpleVariable<T> *SimpleVariable<T>::
  ToObject(const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    if (Implement_Named_Object::ToObject(multipleLines,pos)==nullptr)
      {
        pos=pos0;
        return nullptr;
      }
    std::string line=nextLine(multipleLines,pos);
    if (!SimpleVariable<T>::Data::is(line))
      {
        pos=pos0;
        return nullptr;
      }
    std::size_t posline=0;
    defautValue_=SimpleVariable<T>::Data::get(line,&posline);
    quantityId_=IdentifierName::get(line.substr(posline));

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




  template<>
  std::string SimpleVariable<double>::Data::ClassName()
  {
    return "Variable::DataDouble";
  }
  template<>
  std::string SimpleVariable<std::size_t>::Data::ClassName()
  {
    return "Variable::DataCount";
  }
  template<typename T>
  std::string SimpleVariable<T>::Data::myClass() const
  {
    return ClassName();
  }

  template<typename T>
  std::set<std::string> SimpleVariable<T>::Data::mySuperClasses() const
  {
    return SuperClasses();
  }


  template<>
  double SimpleVariable<double>::Data::unknown()
  {
    return std::numeric_limits<double>::quiet_NaN();
  }



  template<>
  std::size_t SimpleVariable<std::size_t>::Data::unknown()
  {
    return std::numeric_limits<std::size_t>::max();
  }


  template<typename T>
  std::set<std::string> SimpleVariable<T>::Data::SuperClasses()
  {
    auto out= Abstract_Variable_Object::Abstract_Data::SuperClasses();
    out.insert(ClassName());
    return out;
  }

  template<typename T>
  bool SimpleVariable<T>::Data::empty() const
  {
    return (getEnvironment()==nullptr)&&
        (variableName().empty())&&
        (getValue()==T());
  }

  template<>
  double SimpleVariable<double>::Data::get(const std::string& singleLine,std::size_t* pos)
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
  std::string SimpleVariable<T>::Data::ToString()const
  {
    if (empty())
      return "";
    std::string out=variableName()+" : ";
    auto d=printData();
    if (d.find_first_of("\n\r")!=d.npos)
      out+="\n";
    return out+d;
  }

  template<typename T>
  std::deque<Token> SimpleVariable<T>::Data::toTokens() const
  {
    return {{variableName()},{":"},{printData()}};

  }



  template<>
  bool SimpleVariable<double>::Data::isUnknown(const double & value)
  {
    return std::isnan(value);
  }

  template<>
  std::size_t SimpleVariable<std::size_t>::Data::get(const std::string& singleLine,std::size_t* pos)
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
  bool SimpleVariable<double>::Data::is(const std::string &singleLine)
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
  bool SimpleVariable<std::size_t>::Data::is(const std::string &singleLine)
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

  template<typename T>
  typename SimpleVariable<T>::Data *
  SimpleVariable<T>::Data::ToObject(const std::string& multipleLines,
                                    std::size_t &pos)
  {
    std::size_t pos0=pos;
    std::string variableId=IdentifierName::get(multipleLines,pos);
    ++pos;
    std::string line=Implement_Named_Object::nextLine(multipleLines,pos);
    if (!SimpleVariable<T>::Data::is(line))
      {
        pos=pos0;
        return nullptr;
      }
    varName_=variableId;
    std::size_t posline=0;
    data_=SimpleVariable<T>::Data::get(line,&posline);
    return this;
  }




  template<typename T>
  typename SimpleVariable<T>::Data *SimpleVariable<T>::Data::create() const
  {
    return new Data;
  }

  template<typename T>
  typename SimpleVariable<T>::Data *SimpleVariable<T>::Data::CreateObject(
      const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }

  template<typename T>
  std::string SimpleVariable<T>::Data::variableName() const
  {
    return varName_;
  }

  template<typename T>
  const T &SimpleVariable<T>::Data::getValue() const
  {
    return data_;
  }

  template<typename T>
  void SimpleVariable<T>::Data::setValue(T value)
  {
    data_=value;
  }

  template<typename T>
  std::string SimpleVariable<T>::Data::printData() const
  {
    return getEnvironment()->ToString(getValue());
  }

  template<typename T>
  bool SimpleVariable<T>::Data::readPrintData(const std::string &printedData)
  {
    if (!SimpleVariable<T>::Data::is(printedData))
      {
        data_=unknown();
        return false;
      }
    std::size_t posline=0;
    data_=SimpleVariable<T>::Data::get(printedData,&posline);

  }






  template<typename T>
  SimpleVariable<T>::Data::Data():
    Implement_Refer_Environment(),
    varName_{},
    data_{T()}
  {}

  template<typename T>
  SimpleVariable<T>::Data::Data(Environment *E, std::string varName, T value):
    Implement_Refer_Environment(E),
    varName_(varName),
    data_(value){}


  template
  class SimpleVariable<std::size_t>;

  template
  class SimpleVariable<double>;














}
